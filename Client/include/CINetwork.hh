#ifndef CINETWORK_H_
# define CINETWORK_H_

# include <vector>
# include "NetworkDefines.h"

template <class T>
class									CINetwork
{
public:
  virtual bool					initClientSocket(std::string const &ip, std::string const &port) = 0;
  virtual void					recvData(void *data, int size, SOCKET, ClientDatas *addr) = 0;
  virtual void					sendData(void *data, int size, SOCKET, ClientDatas *addr) = 0;
  virtual SOCKET				getFd() const = 0;
  virtual void					selectFD(std::vector<SOCKET>& fd, struct timeval *to) = 0;
  virtual bool					closeConnection(SOCKET) = 0;
  virtual void					getServAddr(std::string const&, std::string const&, struct sockaddr_in*) = 0;
};

template <typename T>
CINetwork<T>*					getNetworkInstance();

#endif
