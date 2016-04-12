#ifndef WNETWORK_H_
# define WNETWORK_H_

# ifdef _WIN32

# include <winsock2.h>
# include <ws2tcpip.h>

# include "SINetwork.hh"

# pragma comment(lib, "Ws2_32.lib")

template <class T>
class SWNetwork : public SINetwork<T>
{
private:
  T*					_socket;
  SOCKET				_listen;
  struct addrinfo*			_addr;
  fd_set*				_readSet;

public:
  SWNetwork();
  ~SWNetwork();

public:
  bool					initServerSocket(std::string const &ip, std::string const &port);
  SOCKET				acceptSocket();
  void					recvData(void *data, int size, SOCKET, ClientDatas *addr);
  void					sendData(void *data, int size, SOCKET, ClientDatas *addr);
  SOCKET				getFd() const;
  void					selectClients(std::vector<SOCKET>& fd, struct timeval *to);
  bool					closeConnection(SOCKET);
};

# include "SWNetwork.tpp"

#endif

#endif
