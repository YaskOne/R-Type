#ifndef UNETWORK_H_
# define UNETWORK_H_

# ifdef __linux__

# include "CINetwork.hh"

template <class T>
class CUNetwork : public CINetwork<T>
{
private:
  T*						_socket;
  SOCKET						_listen;
  ConnectionData*					_addr;
  fd_set*						_readSet;

public:
  CUNetwork();
  ~CUNetwork();

public:
  bool					initClientSocket(std::string const &, std::string const &);
  void					recvData(void *data, int size, SOCKET, ClientDatas *addr);
  void					sendData(void *data, int size, SOCKET, ClientDatas *addr);
  SOCKET				getFd() const;
  void					selectFD(std::vector<SOCKET>& fd, struct timeval *to);
  bool					closeConnection(SOCKET);
  void					getServAddr(std::string const&, std::string const&, struct sockaddr_in*);
};

# include "CUNetwork.tpp"

# endif

#endif
