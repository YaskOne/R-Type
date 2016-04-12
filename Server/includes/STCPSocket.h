#ifndef STCPSOCKET_H_
# define STCPSOCKET_H_

# include "NetworkDefines.h"
# include "SINetwork.hh"

class					STCPSocket
{
private:
  std::string				_ip;
  std::string				_port;
  SOCKET				_listen;

public:
  STCPSocket();
  ~STCPSocket();

  SOCKET				startNetwork(std::string const &ip, std::string const &port, ConnectionData*);
  SOCKET				acceptClient();
  void					sendData(const void *buffer, int size, SOCKET socket, ClientDatas *addr);
  void					rcvData(void*, int size, SOCKET socket, ClientDatas *addr);
};

#endif
