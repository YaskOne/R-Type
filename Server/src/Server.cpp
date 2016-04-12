#include <iostream>
#include "Server.hh"
#include "NetworkDefines.h"
#include "SWNetwork.hh"
#include "NewGamePacket.h"
#include "JoinPacket.hh"
#include "GameListPacket.h"
#include "DesGamePacket.h"
#include "GameListPacket.h"
#include "AuthTCPPacket.h"
#include "GameInfoPacket.h"
#include "GameOverPacket.h"
#include "FailPacket.h"
#include "IServerPacket.hh"

Server::Server(std::string const & ip, std::string const & port)
 : _network(new NetworkHandler(ip, port)),
   _games(new GameHandler(ip)),
    _ip(ip)
{
  if (_network->initSocket())
    start();
}

Server::~Server()
{
  delete _games;
  delete _network;
}

void			Server::start()
{
  while (1)
    {
      if (_network->selectClient())
	{
	  _games->checkEndGames();
	  answerClients();
	}
    }
}

void			Server::answerClients()
{
  ClientInfo*		client;

  while ((client = _network->getActiveClient()))
    {
      parser(client);
    }
}

void			Server::parser(ClientInfo* client)
{
  if (!client->isInGame())
    switch (client->getPacket()->getCommandType())
      {
      case JOIN_GAME:
	{
	  joinGame(client);
	  break;
	}
      case ADD_GAME:
	{
	  createGame(client);
	  break;
	}
      case AUTH_TCP:
	{
	  setNick(client);
	  break;
	}
      case REQ_GAME:
	{
	  describeGame(client);
	  break;
	}
      default:
	{
	  std::cerr << "no match..." << std::endl;
	  break;
	}
      }
  else
    {
      std::cerr << "unknown command" << std::endl;
      _network->sendToClient(client, new FailPacket(FAIL));
    }
}

void			Server::describeGame(ClientInfo* client)
{
  _network->sendToClient(client, new GameListPacket(START_GAME_LIST));
  for (std::vector<GameInfo*>::iterator it = _games->getGameList().begin(); it != _games->getGameList().end(); ++it)
    {
      _network->sendToClient(client, new DesGamePacket(DES_GAME, (*it)->getID(), (*it)->getName(), ""));
    }
  _network->sendToClient(client, new GameListPacket(END_GAME_LIST));
}

void			Server::createGame(ClientInfo* client)
{
  int			id;

  if (client->isInGame() || (id = _games->startNewGame(static_cast<NewGamePacket*>(client->getPacket())->getData()->data)) == -1)
    {
      _network->sendToClient(client, new FailPacket(FAIL));
    }
  else
    {
      joinGame(client, id);
    }
}

void			Server::joinGame(ClientInfo* client)
{
  GameInfo*		game;

  if ((game = _games->addClientInGame(client, static_cast<JoinPacket*>(client->getPacket())->getData()->id)) != NULL)
    _network->sendToClient(client, new GameInfoPacket(GAME_INFO, _ip, game->getPort()));
  else
    _network->sendToClient(client, new FailPacket(FAIL));
}

void			Server::joinGame(ClientInfo* client, int id)
{
  GameInfo*		game;

  if ((game = _games->addClientInGame(client, id)) != NULL)
    _network->sendToClient(client, new GameInfoPacket(GAME_INFO, _ip, game->getPort()));
  else
    _network->sendToClient(client, new FailPacket(FAIL));
}

void			Server::setNick(ClientInfo* client)
{
  client->setNickname(static_cast<NickPacket*>(client->getPacket())->getData()->data);
  _network->sendToClient(client, new AuthTCPPacket(AUTH, SUCCESS));
}
