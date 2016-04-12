#ifndef CUDPSOCKET_H_
# define CUDPSOCKET_H_

# include "NetworkDefines.h"
# include "IClientPacket.hh"
# include "CINetwork.hh"
# include "Exceptions.hpp"

class			CUDPSocket
{
private:
  int			_listen;

public:
  CUDPSocket();
  ~CUDPSocket();

  int			startNetwork(std::string const &ip, std::string const &port, ConnectionData*);
  void			sendData(const void *buffer, int size, SOCKET sock, ClientDatas *addr);
  void			rcvData(void* buffer, int size, SOCKET sock, ClientDatas *addr);
};

#endif
