#include <algorithm>
#include "GameCore.hh"

GameCore::GameCore(std::string const&ip, std::string const& port, CUMutex* mutex, bool* endGame)
  : _clients(new std::vector<GamerInfo*>()),
    _network(new UDPNetworkHandler(ip, port, _clients)),
    _map(new MapController()),
    _factory(new FactoryManager(_map)),
    _referential(sf::Time(sf::microseconds(20000))),
    _running(true),
    _firstClient(false),
    _currentLevel(0),
    _mutex(mutex),
    _end(endGame)
{
  _factory->changeLevel(0);
  this->run();
}

GameCore::~GameCore()
{
  for (auto& client : *_clients)
    {
      delete client;
    }
  delete _network;
  delete _map;
  delete _clients;
  delete _factory;
}

void				GameCore::run()
{
  sf::Time			elapsed;

  if (!_network->initSocket())
    return ;

  _clock.restart();
  while (_running)
    {
      _clockAlive.restart();
      this->updateMap();
      while (_running && ((elapsed = getElapsedTimeSinceLoop()) > sf::microseconds(0)))
       	{
	  receivePacket();
	}
      if (_firstClient)
      	this->updateAliveClients(_clockAlive.getElapsedTime());
    }
  _mutex->LockMutex();
  *_end = true;
  _mutex->UnlockMutex();
}

void				GameCore::updateAliveClients(sf::Time const& count)
{
  std::vector<GamerInfo*>::iterator	it = _clients->begin();

  while (it != _clients->end())
    {
      bool res = (*it)->updateAlive(count);
      if (!res)
	{
	  _map->deletePlayer((*it)->getID());
	  _clients->erase(it);
	  break ;
	}
      ++it;
    }
  if (_clients->empty())
    _running = false;
}

void				GameCore::updateMap()
{
  std::vector<IObject*>		*aliens;
  std::vector<IServerPacket<ServerUDPResponse>*>	*toSend = new std::vector<IServerPacket<ServerUDPResponse>*>;

  if (_map->getAlienCount() == 0
      && _factory->remainingAliens())
    {
      if (_currentLevel == 3)
	{
	  exit(0);
	}
      _clock.restart();
      _map->resetClockPlayer();
      _network->broadcast(new NextLvlPacket(NEXT_LVL, 0, ++_currentLevel));
      _factory->changeLevel(_currentLevel);
    }
  try
    {
      aliens = _factory->update(_clock);
    }
  catch (Exceptions::FactoryExcept e)
    {
      std::cerr << e.what() << std::endl;
    }
  if (aliens->size() > 0)
    for (auto it = aliens->begin(); it != aliens->end(); ++it)
      {
	if ((*it)->getObjType() == ObjectInfo::BONUS)
	  {
	    _map->addObject(*it);
	    toSend->push_back(new BonusPacket(BONUS_PACKET, static_cast<ABonus*>(*it)->getBonusType(), 0, (*it)->getId(), (*it)->getPos().x, (*it)->getPos().y, (*it)->getSpeed().x));
	  }
	else
	  {
	    _map->addAlien(*it);
	    toSend->push_back(new CreIAPacket(CRE_IA, 0, (*it)->getId(), (*it)->getPos().x, (*it)->getPos().y, (*it)->getSpeed().x, static_cast<Alien*>((*it))->getCoeff(), static_cast<Alien*>((*it))->getRealType()));
	  }
      }
  _map->updateMap(_clock);
  toSend->insert(toSend->begin(), _map->getMap()->begin(), _map->getMap()->end());
  this->sendMap(NULL, toSend);
  delete aliens;
  delete toSend;
}

sf::Time			GameCore::getElapsedTimeSinceLoop()
{
  sf::Time			ret;

  ret = sf::microseconds(_clock.getElapsedTime().asMicroseconds() % _referential.asMicroseconds());
  return ret;
}

std::vector<IServerPacket<ServerUDPResponse>*>*		GameCore::generatePackets(std::vector<IObject*>* aliens)
{
  std::vector<IServerPacket<ServerUDPResponse>*>*	ret = new std::vector<IServerPacket<ServerUDPResponse>*>;

  for (std::vector<IObject*>::iterator it = aliens->begin(); it != aliens->end(); ++it)
    {
      ret->push_back(new CreIAPacket(CRE_IA, 0, (*it)->getId(), (*it)->getPos().x, (*it)->getPos().y, (*it)->getSpeed().x, static_cast<Alien*>(*it)->getCoeff(), static_cast<Alien*>((*it))->getRealType()));
    }
    return ret;
}

void				GameCore::sendMap(GamerInfo* client, std::vector<IServerPacket<ServerUDPResponse>*> *toSendMap)
{
  IServerPacket<ServerUDPResponse>*	packetToSend;

  while (!toSendMap->empty())
    {
      packetToSend = toSendMap->back();
      if (client)
	_network->sendTo(client, packetToSend);
      else
	_network->broadcast(packetToSend);
      delete packetToSend;
      toSendMap->pop_back();
    }
}

void					GameCore::receivePacket()
{
  GamerInfo*				client;
  IClientPacket<ClientUDPCommand>*	packet;

  if ((client = _network->selectClient()))
    {
      _firstClient = true;
      packet = _network->receiveFrom(client);
      if (packet)
	processPacket(client, packet);
    }
}

void					GameCore::processPacket(GamerInfo* client,
								IClientPacket<ClientUDPCommand>* packet)
{
  switch (packet->getCommandType())
    {
    case CAUTH_UDP:
      setAlive(client, packet);
      authGamer(client, packet);
      break;
    case FIRE:
      setAlive(client, packet);
      gamerTryShoot(client, packet);
      break;
    case SEND_MOVE:
      setAlive(client, packet);
      gamerMove(client, packet);
      break;
    case ALIVE:
      setAlive(client, packet);
      break;
    case DISCONNECT:
      gamerDisconnect(client, packet);
      break;
    default:
      break;
    }
}

void					GameCore::authGamer(GamerInfo* client, IClientPacket<ClientUDPCommand>* packet)
{
  Player*				player;

  if (!client->isAuth())
    {
      client->setName(static_cast<CAuthUDPPacket*>(packet)->getData()->data);
      client->setAuth(true);
      client->setID(_maxId++);
      _map->addObject(new Player(sf::Vector2f(10,10), sf::Vector2f(100, 400), client->getID()));
    }
   player = static_cast<Player*>(_map->getPlayer(client->getID()));
   _map->generatePacketsMap(player);
   _network->sendTo(client, new AuthUDPPacket(AUTH_UDP, 0, SUCCESS, _clock.getElapsedTime().asSeconds()));
   this->sendMap(client, _map->getMap());
   _network->broadcast(new CrePlayPacket(CRE_PLAY, 0, player->getId(), player->getPos().x, player->getPos().y));
}

void					GameCore::gamerTryShoot(GamerInfo* client, IClientPacket<ClientUDPCommand>* packet)
{
  Player*				player = static_cast<Player*>(_map->getPlayer(client->getID()));

  if (player && client->isAuth())
    player->tryShoot();
}

void					GameCore::gamerMove(GamerInfo* client, IClientPacket<ClientUDPCommand>* packet)
{
  Player*				player = static_cast<Player*>(_map->getPlayer(client->getID()));

  if (player && client->isAuth())
    {
      player->setDirection(static_cast<SendMovePacket*>(packet)->getData()->dir);
      _map->updatePlayer(player, _clock);
      _network->broadcast(new MovePacket(MOVE, 0, client->getID(), player->getPos().x, player->getPos().y, player->getScore()));
    }
}

void					GameCore::gamerDisconnect(GamerInfo* client, IClientPacket<ClientUDPCommand>* packet)
{
  auto it = std::find(_clients->begin(), _clients->end(), client);

  if (it != _clients->end())
    {
      _map->deletePlayer(client->getID());
      _clients->erase(it);
      delete (client);
    }
}

void					GameCore::setAlive(GamerInfo* client, IClientPacket<ClientUDPCommand>* packet)
{
  client->resetAlive();
}
