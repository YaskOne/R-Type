#ifndef UNETWORK_H_
# define UNETWORK_H_

# ifndef _WIN32

# include "SINetwork.hh"

template <class T>
class SUNetwork : public SINetwork<T>
{
private:
  T*							_socket;
  SOCKET						_listen;
  struct addrinfo*					_addr;
  fd_set*						_readSet;

public:
  SUNetwork();
  ~SUNetwork();

public:
  bool					initServerSocket(std::string const &, std::string const &);
  SOCKET				acceptSocket();
  void					recvData(void *data, int, SOCKET, ClientDatas *addr);
  void					sendData(void *data, int size, SOCKET, ClientDatas *addr);
  SOCKET				getFd() const;
  void					selectClients(std::vector<SOCKET>& fd, struct timeval *to);
  bool					closeConnection(SOCKET);
};

# include "SUNetwork.tpp"

# endif

#endif
