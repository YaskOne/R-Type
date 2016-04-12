#include <stdio.h>
#include <errno.h>
#include <cerrno>
#include "STCPSocket.h"
#include "Exceptions.hpp"

STCPSocket::STCPSocket()
{
}

STCPSocket::~STCPSocket()
{
}

SOCKET			STCPSocket::startNetwork(std::string const &ip, std::string const &port, ConnectionData *hints)
{
  ConnectionData	*addr = NULL;
  int			result;

  hints->ai_flags = AI_PASSIVE;
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM;
  hints->ai_protocol = IPPROTO_TCP;
  hints->ai_addr = INADDR_ANY;
  std::cout << ip << "   " << port << std::endl;
  result = getaddrinfo(ip.c_str(), port.c_str(), hints, &addr);
  if (result != 0)
    {
      throw Exceptions::NetworkExcept("GETADDRINFO ERROR", errno);
    }

  SOCKET		Thatsocket = INVALID_SOCKET;

  if ((Thatsocket = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol)) == -1)
    throw Exceptions::NetworkExcept("SOCKET ERROR", errno);
  if (bind(Thatsocket, addr->ai_addr, (int)addr->ai_addrlen) == SOCKET_ERROR)
    {
      freeaddrinfo(addr);
      throw Exceptions::NetworkExcept("BIND ERROR", errno);
    }
  if (listen(Thatsocket, SOMAXCONN) == SOCKET_ERROR)
    throw Exceptions::NetworkExcept("LISTEN ERROR", errno);
  _listen = Thatsocket;
  return _listen;
}

SOCKET			STCPSocket::acceptClient()
{
  SOCKET		socket = INVALID_SOCKET;

  if ((socket = accept(_listen, NULL, NULL)) == INVALID_SOCKET)
    throw Exceptions::NetworkExcept("ACCEPT FAILED", errno);
  return socket;
}

void			STCPSocket::sendData(const void *buffer, int size, SOCKET socket, ClientDatas *addr)
{
  int			res = send(socket, (const char *)buffer, size, 0);

  if (res == -1)
    throw Exceptions::NetworkExcept("SEND FAILED", errno);
  if (res == 0)
    throw Exceptions::ConnectionExcept("DISCONNECTED CLIENT");
}

void			STCPSocket::rcvData(void* buffer, int size, SOCKET socket, ClientDatas *addr)
{
  int			addr_len = sizeof(addr);
  int			res;

  res = recv(socket, (char*)buffer, size, 0);
  if (res == -1)
    throw Exceptions::NetworkExcept("RECEIVE FAILED", errno);
  if (res == 0)
    throw Exceptions::ConnectionExcept("DISCONNECTED CLIENT");
}
