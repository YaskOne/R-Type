#include <algorithm>
#include "GameHandler.h"

GameHandler::GameHandler(std::string const& ip)
  : _maxID(13), _ip(ip), _maxPort(BASE_PORT)
{
}

GameHandler::~GameHandler()
{
}

GameInfo*				GameHandler::addClientInGame(ClientInfo* client, int id)
{
  for (std::vector<GameInfo*>::iterator it = _gameList.begin(); it != _gameList.end(); ++it)
    {
      if ((*it)->getID() == id && (*it)->addClient(client))
	{
	  return (*it);
	}
    }
  return NULL;
}

int					GameHandler::startNewGame(std::string const &name)
{
  if (_gameList.size() >= MAX_GAME)
    return -1;
  _gameList.push_back(new GameInfo(name, _maxID++, _maxPort++, _ip));
  return _maxID - 1;
}

std::vector<GameInfo*>&			GameHandler::getGameList()
{
  checkEndGames();
  return _gameList;
}

void					GameHandler::checkEndGames()
{
  std::vector<GameInfo*>::iterator	it = _gameList.begin();

  while (it != _gameList.end() && _gameList.size() > 0)
    {
      if ((*it)->isFinished())
	{
	  (*it)->joinGameThread();
	  delete (*it);
	  _gameList.erase(it);
	  return ;
	}
      else
	++it;
    }
}
