#ifndef SERVER_H_
# define SERVER_H_

# include <vector>
# include "GameInfo.h"
# include "SNetworkHandler.h"
# include "GameHandler.h"

class					Server
{
 public:
  Server(std::string const& ip, std::string const& port);
  ~Server();

 private:
  NetworkHandler*			_network;
  GameHandler*				_games;
  std::string				_ip;

private:
  void					start();
  void					answerClients();
  void					parser(ClientInfo* client);
  void					describeGame(ClientInfo* client);
  void					createGame(ClientInfo* client);
  void					setNick(ClientInfo* client);
  void					joinGame(ClientInfo* client);
  void					joinGame(ClientInfo* client, int id);
};

#endif
