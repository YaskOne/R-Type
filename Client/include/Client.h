#ifndef CLIENT_H_
# define CLIENT_H_

# include <vector>
# include "CNetworkHandler.hh"

class Client
{
public:
  Client(std::string const& ip, std::string const& port);
  ~Client();

 private:
  CNetworkHandler*				_network;
  SOCKET					_listen;

 public:
  void						start();
};

#endif
