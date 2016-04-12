#ifndef _WIN32

#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <unistd.h>
#include "STCPSocket.h"
#include "SUDPSocket.h"
#include "SINetwork.hh"
#include "Exceptions.hpp"

template <typename T>
SUNetwork<T>::SUNetwork()
  : _socket(new T()), _readSet(new fd_set)
{
}

template <typename T>
SUNetwork<T>::~SUNetwork()
{
  delete _socket;
}

template <typename T>
bool SUNetwork<T>::initServerSocket(std::string const &ip, std::string const &port)
{
  ConnectionData *hints = new ConnectionData;

  bzero(hints, sizeof(*hints));
  try
    {
      _listen = _socket->startNetwork(ip, port, hints);
    }
  catch (Exceptions::NetworkExcept e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  return true;
}

template <typename T>
void		SUNetwork<T>::selectClients(std::vector<int>& fd, struct timeval *to)
{
  std::vector<int>	buffer;
  SOCKET			maxFd = 0;

  FD_ZERO(_readSet);
  for (std::vector<int>::iterator it = fd.begin(); it != fd.end(); ++it)
    {
      FD_SET((*it), _readSet);
      if (*it > maxFd)
	maxFd = *it;
    }
  if (select(maxFd + 1, _readSet, NULL, NULL, to) < 0) {
    throw Exceptions::NetworkExcept("SELECT ERROR", errno);
  }
  for (std::vector<int>::iterator it = fd.begin(); it != fd.end(); ++it)
    {
      if (FD_ISSET((*it), _readSet)){
	buffer.push_back((*it));
      }
    }
  fd.clear();
  fd = buffer;
}

template <typename T>
SOCKET	SUNetwork<T>::acceptSocket()
{
  SOCKET accept = _socket->acceptClient();
  if (accept == INVALID_SOCKET)
    {
      closeConnection(_listen);
    }
  return accept;
}

template <typename T>
void	SUNetwork<T>::recvData(void *data, int size, SOCKET sock, ClientDatas *addr)
{
  _socket->rcvData(data, size, sock, addr);
}

template <typename T>
void	SUNetwork<T>::sendData(void *data, int size, SOCKET sock, ClientDatas *addr)
{
  _socket->sendData(data, size, sock, addr);
}

template <typename T>
bool SUNetwork<T>::closeConnection(SOCKET socket)
{
  close(socket);
  return true;
}

template <typename T>
SOCKET SUNetwork<T>::getFd() const
{
  return (_listen);
}

template <typename T>
SINetwork<T>*		getNetworkInstance()
{
  return new SUNetwork<T>();
}

#endif
