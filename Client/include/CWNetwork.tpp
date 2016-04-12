#ifdef _WIN32

#include <string>
#include <iostream>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "CTCPSocket.hh"
#include "CUDPSocket.hh"
#include "CINetwork.hh"
#define _WINSOCK_DEPRECATED_NO_WARNINGS

template <typename T>
WNetwork<T>::WNetwork()
	: _socket(new T()), _readSet(new fd_set)
{
}

template <typename T>
WNetwork<T>::~WNetwork()
{
  delete _socket;
}

template <typename T>
bool WNetwork<T>::initClientSocket(std::string const &ip, std::string const &port)
{
  WSADATA wsaData;
  addrinfo *hints = new addrinfo;

  int result;
  result = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (result != 0)
    {
      printf("WSAStartup failed: %d\n", result);
      return false;
    }
  ZeroMemory(hints, sizeof(hints));
  if ((_listen = _socket->startNetwork(ip, port, hints)) == INVALID_SOCKET)
    {
      WSACleanup();
      return false;
    }
  return true;
}

template <typename T>
void		WNetwork<T>::selectFD(std::vector<SOCKET>& fd, struct timeval *to)
{
  std::vector<unsigned int>	buffer;
  SOCKET			maxFd = 0;

  FD_ZERO(_readSet);
  for (std::vector<unsigned int>::iterator it = fd.begin(); it != fd.end(); ++it)
    {
      FD_SET((*it), _readSet);
      if ((unsigned int)*it > maxFd)
	maxFd = *it;
    }
  if (select(maxFd + 1, _readSet, NULL, NULL, to) < 0) {
    throw Exceptions::NetworkExcept("SELECT ERROR", errno);
  }
  for (std::vector<unsigned int>::iterator it = fd.begin(); it != fd.end(); ++it)
    {
      if (FD_ISSET((*it), _readSet))
	buffer.push_back((*it));
    }
  fd.clear();
  fd = buffer;
}

template <typename T>
void WNetwork<T>::sendData(void *data, int size, SOCKET sock, ClientDatas *addr)
{
  _socket->sendData(data, size, sock, addr);
}

template <typename T>
void WNetwork<T>::recvData(void *data, int size, SOCKET sock, ClientDatas *addr)
{
  _socket->rcvData(data, size, sock, addr);
}

template <typename T>
void			WNetwork<T>::getServAddr(std::string const& ip, std::string const& port, struct sockaddr_in* addr)
{
  struct hostent	*he;

  he = gethostbyname(ip.c_str());
  memcpy(&(addr->sin_addr), he->h_addr_list[0], he->h_length);
  addr->sin_family = AF_INET;
  addr->sin_port = htons(atoi(port.c_str()));
}

template <typename T>
bool WNetwork<T>::closeConnection(SOCKET socket)
{
  closesocket(socket);
  return false;
}

template <typename T>
SOCKET WNetwork<T>::getFd() const
{
  return (_listen);
}

template <typename T>
CINetwork<T>*		getNetworkInstance()
{
  return new WNetwork<T>();
}

#endif
