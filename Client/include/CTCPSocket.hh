#ifndef TCPSOCKET_H_
# define TCPSOCKET_H_

# include "NetworkDefines.h"
# include "CINetwork.hh"

class					CTCPSocket
{
private:
  std::string				_ip;
  std::string				_port;

public:
  CTCPSocket();
  ~CTCPSocket();

  SOCKET				startNetwork(std::string const &ip, std::string const &port, ConnectionData*);
  void					sendData(const void *buffer, int size, SOCKET socket, ClientDatas *addr);
  void					rcvData(void*, int size, SOCKET socket, ClientDatas *addr);
};

#endif
