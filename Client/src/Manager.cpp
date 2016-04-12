#include "Manager.hh"

Manager::Manager(CUDPNetworkHandler *udpHand)
  : _udpHand(udpHand),
    _refAlive(sf::Time(sf::milliseconds(50))),
    _lastAliveSent(_refAlive),
    _lvl(1)
{
  _itemCtrl = new ItemController;
  _referential = sf::Time(sf::microseconds(20000));
}

Manager::~Manager()
{
}

void					Manager::loop()
{
  sf::Time elapsed;
  sf::Time lastTime;

  vc->startSoundtrack();
  _itemCtrl->setBackground(BACKGROUND_ONE);
  _itemCtrl->addSplash("GOOOOO !!!");
  _clock.restart();
  while (1)
    {
      vc->clear();
      _itemCtrl->draw();
      vc->refresh();

      _itemCtrl->update();
      _keyboardStatus =  vc->getKeyboardStatus();
      sendAlive(_referential);
      if (treatEventsFromKeyboard() == 1)
	return ;
      lastTime = sf::microseconds(0);

      while ((elapsed = getElapsedTimeSinceLoop()) > lastTime)
	{
	  lastTime = elapsed;
	  treatEventsFromNetwork();
	}
    }
}

void	Manager::sendAlive(sf::Time const& count)
{
  _lastAliveSent -= count;
  if (_lastAliveSent <= sf::Time(sf::milliseconds(0)))
    {
      _lastAliveSent = sf::Time(sf::milliseconds(500));
      _udpHand->send(new AlivePacket(ALIVE, 0, true));
    }
}

sf::Time Manager::getElapsedTimeSinceLoop()
{
  sf::Time ret;

  ret = sf::microseconds(_clock.getElapsedTime().asMicroseconds() % _referential.asMicroseconds());
  return ret;
}

int Manager::treatEventsFromKeyboard()
{
  if (_keyboardStatus.up)
    _udpHand->send(new SendMovePacket(SEND_MOVE, 0, UP));
  if (_keyboardStatus.down)
    _udpHand->send(new SendMovePacket(SEND_MOVE, 0, DOWN));
  if (_keyboardStatus.left)
    _udpHand->send(new SendMovePacket(SEND_MOVE, 0, LEFT));
  if (_keyboardStatus.right)
    _udpHand->send(new SendMovePacket(SEND_MOVE, 0, RIGHT));
  if (_keyboardStatus.ctrl)
    _udpHand->send(new FirePacket(FIRE, 0, 0, 0));
  if (_keyboardStatus.echap)
    {
      _udpHand->send(new DisconnectPacket(DISCONNECT, 0));
      return 1;
    }
  return 0;
}

void Manager::treatPacket(IServerPacket<ServerUDPResponse>* res)
{
  ServerUDPResponse		packetType = res->getCommandType();

  switch (packetType)
    {
    case CRE_PLAY:
      _itemCtrl->addShip(static_cast<CrePlayPacket*>(res));
      break;
    case CRE_OBJ:
      _itemCtrl->addObj(static_cast<CreObjPacket*>(res));
      break;
    case CRE_IA:
      _itemCtrl->addAlien(static_cast<CreIAPacket*>(res));
      break;
    case BONUS_PACKET:
      _itemCtrl->addObj(static_cast<BonusPacket*>(res));
      break;
    case DEL_ITEM:
      _itemCtrl->deleteObject(static_cast<DelItemPacket*>(res));
      break;
    case MOVE:
      _itemCtrl->moveShip(static_cast<MovePacket*>(res));
      break;
    case NEXT_LVL:
      _itemCtrl->levelUp(++_lvl);
      break;
    default:
      break;
    }
}

void Manager::treatEventsFromNetwork()
{
  struct timeval to;
  to.tv_sec = 0;
  to.tv_usec = 1;
  IServerPacket<ServerUDPResponse> *res;

  if (_udpHand->selectServer(&to))
    {
      if (res = _udpHand->receive())
	treatPacket(res);
    }
}
