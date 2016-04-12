#ifdef __linux__

#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "CTCPSocket.hh"
#include "CUDPSocket.hh"
#include "CINetwork.hh"

template <typename T>
CUNetwork<T>::CUNetwork()
	: _socket(new T()), _readSet(new fd_set)
{
}

template <typename T>
CUNetwork<T>::~CUNetwork()
{
	delete _socket;
}

template <typename T>
bool CUNetwork<T>::initClientSocket(std::string const &ip, std::string const &port)
{
  addrinfo *hints = new addrinfo;

  bzero(hints, sizeof(hints));
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
void		CUNetwork<T>::selectFD(std::vector<int>& fd, struct timeval *to)
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
      if (FD_ISSET((*it), _readSet))
	buffer.push_back((*it));
    }
  fd.clear();
  fd = buffer;
}

template <typename T>
void CUNetwork<T>::recvData(void *data, int size, SOCKET sock, ClientDatas *addr)
{
  _socket->rcvData(data, size, sock, addr);
}

template <typename T>
void  CUNetwork<T>::getServAddr(std::string const& ip, std::string const& port, struct sockaddr_in *addr)
{
  memset((void *)addr, 0, sizeof(*addr));
  addr->sin_family = AF_INET;
  addr->sin_port = htons(std::atoi(port.c_str()));
  inet_aton(ip.c_str(), &(addr->sin_addr));
}

template <typename T>
void CUNetwork<T>::sendData(void *data, int size, SOCKET sock, ClientDatas *addr)
{
  _socket->sendData(data, size, sock, addr);
}

template <typename T>
bool CUNetwork<T>::closeConnection(SOCKET socket)
{
	close(socket);
	return true;
}

template <typename T>
SOCKET CUNetwork<T>::getFd() const
{
	return (_listen);
}

template <typename T>
CINetwork<T>*		getNetworkInstance()
{
	return new CUNetwork<T>();
}

#endif
