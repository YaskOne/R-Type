#include "GameInfo.h"
#include "GameCore.hh"

void		routine(std::string const&, std::string const&, CUMutex*, bool*);

void		routine(std::string const& port, std::string const& ip, CUMutex* mutex, bool* endGame)
{
  GameCore*	gameCore = new GameCore(ip, port, mutex, endGame);
}

GameInfo::GameInfo(std::string const& name, int id, int port, std::string const& ip)
  : _name(name),
    _id(id),
    _port(port),
    _endGame(false),
    _thread(new UThread(std::to_string(port), ip, &_mutex, &_endGame))
{
  _thread->InitThread(&routine);
  _thread->StartThread();
}

GameInfo::~GameInfo()
{
  delete (_thread);

  for (std::vector<ClientInfo*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    (*it)->setInGame(false);
}

std::string const&		GameInfo::getName() const
{
  return _name;
}

int				GameInfo::getPort() const
{
  return _port;
}

int				GameInfo::getPlayerNb() const
{
  return _clients.size();
}

int				GameInfo::getID() const
{
  return _id;
}

bool				GameInfo::addClient(ClientInfo * client)
{
  if (_clients.size() < MAX_PLAYERS)
    _clients.push_back(client);
  else
    return false;
  client->setInGame(true);
  return true;
}

std::string const&		GameInfo::getClients()
{
  static std::string	buffer = "";

  for (std::vector<ClientInfo*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
    {
      if (*it == NULL)
	it = _clients.erase(it);
      else
	buffer += (*it)->getNickname() + "\n";
    }
  return buffer;
}

bool				GameInfo::isFinished() const
{
  return _endGame;
}

bool				GameInfo::joinGameThread()
{
  return (_thread->WaitThread());
}
