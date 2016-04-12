#ifdef _WIN32

#include <string>
#include <iostream>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "STCPSocket.h"
#include "SUDPSocket.h"
#include "SINetwork.hh"
#define _WINSOCK_DEPRECATED_NO_WARNINGS

template <typename T>
SWNetwork<T>::SWNetwork()
  : _socket(new T()), _readSet(new fd_set)
{
}

template <typename T>
SWNetwork<T>::~SWNetwork()
{
  delete _socket;
}

template <typename T>
bool SWNetwork<T>::initServerSocket(std::string const &ip, std::string const &port)
{
  WSADATA wsaData;
  ConnectionData *hints = new ConnectionData;

  int result;
  result = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (result != 0)
    {
      std::cerr << "WSAStartup failed: " << result << std::endl;;
      return false;
    }
  ZeroMemory(hints, sizeof(*hints));
  if ((_listen = _socket->startNetwork(ip, port, hints)) == INVALID_SOCKET)
    {
      WSACleanup();
      return false;
    }
  return true;
}

template <typename T>
void		SWNetwork<T>::selectClients(std::vector<SOCKET>& fd, struct timeval *to)
{
  std::vector<SOCKET> buffer;
  FD_ZERO(_readSet);

  for (std::vector<SOCKET>::iterator it = fd.begin(); it != fd.end(); ++it)
    {
      FD_SET((*it), _readSet);
    }
  if (select(_listen + 1, _readSet, NULL, NULL, to) == -1)
    {
    perror("select error");
    fd.clear();
    return;
  }
  for (std::vector<SOCKET>::iterator it = fd.begin(); it != fd.end(); ++it)
    {
      if (FD_ISSET((*it), _readSet))
	buffer.push_back((*it));
    }
  fd = buffer;
}

template <typename T>
SOCKET SWNetwork<T>::acceptSocket()
{
  SOCKET accept = _socket->acceptClient();
  if (accept == INVALID_SOCKET)
    {
      WSACleanup();
      closeConnection(_listen);
    }
  return accept;
}

template <typename T>
void	SWNetwork<T>::sendData(void *data, int size, SOCKET sock, ClientDatas *addr)
{
  _socket->sendData(data, size, sock, addr);
}

template <typename T>
void	SWNetwork<T>::recvData(void *data, int size, SOCKET sock, ClientDatas *addr)
{
  _socket->rcvData(data, size, sock, addr);
}

template <typename T>
bool SWNetwork<T>::closeConnection(SOCKET socket)
{
  closesocket(socket);
  return false;
}

template <typename T>
SOCKET SWNetwork<T>::getFd() const
{
  return (_listen);
}

template <typename T>
SINetwork<T>*		getNetworkInstance()
{
  return new SWNetwork<T>();
}

#endif
