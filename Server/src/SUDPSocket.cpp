#include "SUDPSocket.h"

SUDPSocket::SUDPSocket()
{
}

SUDPSocket::~SUDPSocket()
{
}

int			SUDPSocket::startNetwork(std::string const &ip, std::string const &port, addrinfo *hints)
{
  ConnectionData *addr = NULL;
  int result;

  hints->ai_flags = AI_PASSIVE;
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_DGRAM;
  hints->ai_protocol = IPPROTO_UDP;
  hints->ai_addr = INADDR_ANY;
  result = getaddrinfo(ip.c_str(), port.c_str(), hints, &addr);
  if (result != 0) {
    throw Exceptions::NetworkExcept("GETADDRINFO ERROR", errno);
  }

  if ((_listen = socket(addr->ai_family, addr->ai_socktype,
			addr->ai_protocol)) == INVALID_SOCKET)
    throw Exceptions::NetworkExcept("SOCKET ERROR", errno);

  if (bind(_listen, addr->ai_addr, (int)addr->ai_addrlen) == SOCKET_ERROR)
    {
      freeaddrinfo(addr);
      throw Exceptions::NetworkExcept("BIND ERROR", errno);
    }
  return _listen;
}

void			SUDPSocket::sendData(const void *buffer, int size, SOCKET sock, ClientDatas *addr)
{
  socklen_t			addr_len = sizeof(*addr);

  int res = sendto(_listen, (char *)buffer, sizeof(ServerUDPHeader), 0, (sockaddr *)addr, addr_len);
  if (res == -1)
    throw Exceptions::NetworkExcept("SENDTO ERROR", errno);
  if (res == 0)
    throw Exceptions::ConnectionExcept("DISCONNECTED CLIENT");
  if (size > sizeof(ServerUDPHeader))
    {
      res = sendto(_listen, (char *)buffer + sizeof(ServerUDPHeader), size - sizeof(ServerUDPHeader), 0, (sockaddr *)addr, addr_len);
      if (res == -1)
	throw Exceptions::NetworkExcept("SENDTO ERROR", errno);
      if (res == 0)
	throw Exceptions::ConnectionExcept("DISCONNECTED CLIENT");
    }
}

void			SUDPSocket::rcvData(void* buffer, int size, SOCKET sock, ClientDatas *addr)
{
  socklen_t			addr_len = sizeof(*addr);
  int				res;

  res = recvfrom(_listen, (char *)buffer, size, 0, (sockaddr *)addr, &addr_len);
  if (res == -1)
    throw Exceptions::NetworkExcept("RECEIVEFROM ERROR", errno);
  if (res == 0)
    throw Exceptions::ConnectionExcept("DISCONNECTED CLIENT");
}

SOCKET				SUDPSocket::acceptClient()
{
  return -1;
}
