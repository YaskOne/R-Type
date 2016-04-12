#include "CUDPSocket.hh"

CUDPSocket::CUDPSocket()
{
}

CUDPSocket::~CUDPSocket()
{
}

int			CUDPSocket::startNetwork(std::string const &ip, std::string const &port, addrinfo *hints)
{
  ConnectionData *addr = NULL;
  int result;

  memset(hints, 0, sizeof(*hints));
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
  return _listen;
}

void			CUDPSocket::sendData(const void *buffer, int size, SOCKET sock, ClientDatas *addr)
{
  socklen_t			addr_len = sizeof(*addr);

  int res = sendto(_listen, (char*)buffer, sizeof(ClientUDPHeader), 0, (sockaddr *)addr, addr_len);
  if (res == -1)
    throw Exceptions::NetworkExcept("SENDTO ERROR", errno);
  if (res == 0)
    throw Exceptions::ConnectionExcept("DISCONNECTED CLIENT");
  if (size > sizeof(ClientUDPHeader))
    {
      res = sendto(_listen, (char*)buffer + sizeof(ClientUDPHeader), size - sizeof(ClientUDPHeader), 0, (sockaddr *)addr, addr_len);
      if (res == -1)
	throw Exceptions::NetworkExcept("SENDTO ERROR", errno);
      if (res == 0)
	throw Exceptions::ConnectionExcept("DISCONNECTED CLIENT");
    }
}

void			CUDPSocket::rcvData(void* buffer, int size, SOCKET sock, ClientDatas *addr)
{
  socklen_t			addr_len = sizeof(*addr);
  int				res;

  res = recvfrom(_listen, (char *)buffer, size, 0, (sockaddr *)addr, &addr_len);
  if (res == -1)
    throw Exceptions::NetworkExcept("RECEIVEFROM ERROR", errno);
  if (res == 0)
    throw Exceptions::ConnectionExcept("DISCONNECTED CLIENT");
}
