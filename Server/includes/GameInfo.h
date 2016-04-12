#ifndef GAMEINFO_H_
# define GAMEINFO_H_

# include <string>
# include <vector>
# include "UThread.h"
# include "ClientInfo.h"
# include "UMutex.h"

class GameInfo
{
 public:
  GameInfo(std::string const& name, int id, int port, std::string const& ip);
  ~GameInfo();

 private:
  std::string	       		_name;
  int				_id;
  int				_port;
  std::vector<ClientInfo*>	_clients;
  bool				_endGame;
  CUMutex			_mutex;
  IThread*			_thread;

 public:
  std::string const&		getName() const;
  int				getID() const;
  int				getPort() const;
  int				getPlayerNb() const;
  bool				addClient(ClientInfo* client);
  std::string const&		getClients();
  bool				isFinished() const;
  bool				joinGameThread();
};

#endif
