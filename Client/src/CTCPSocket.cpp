#include <string.h>
#include <stdio.h>
#include "CTCPSocket.hh"
#include "Exceptions.hpp"

CTCPSocket::CTCPSocket()
{
}

CTCPSocket::~CTCPSocket()
{
}

SOCKET			CTCPSocket::startNetwork(std::string const &ip, std::string const &port, addrinfo *hint)
{
  ConnectionData *addr = NULL, hints;
  memset(&hints, 0, sizeof(hints));
  int result;
  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_addr = NULL;

  result = getaddrinfo(ip.c_str(), port.c_str(), &hints, &addr);
  if (result != 0) {
    throw Exceptions::NetworkExcept("GETADDRINFO ERROR", errno);
  }

  SOCKET	listen;
  if ((listen = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol)) == INVALID_SOCKET)
    throw Exceptions::NetworkExcept("SOCKET ERROR", errno);
  if (connect(listen, (struct sockaddr*)addr->ai_addr, (int)addr->ai_addrlen) == INVALID_SOCKET)
    throw Exceptions::NetworkExcept("CONNECT ERROR", errno);
  return listen;
}

void	CTCPSocket::sendData(const void *buffer, int size, SOCKET socket, ClientDatas *addr)
{
  int res = send(socket, (char*)buffer, size, 0);

  if (res == -1)
    throw Exceptions::NetworkExcept("SEND FAILED", errno);
  if (res == 0)
    throw Exceptions::ConnectionExcept("DISCONNECTED CLIENT");
}

void			CTCPSocket::rcvData(void* buffer, int size, SOCKET socket, ClientDatas *addr)
{
  int			addr_len = sizeof(addr);
  int			res;

  res = recv(socket, (char*)buffer, size, 0);
  if (res == -1)
    throw Exceptions::NetworkExcept("RECEIVE FAILED", errno);
  if (res == 0)
    throw Exceptions::ConnectionExcept("DISCONNECTED CLIENT");
}
