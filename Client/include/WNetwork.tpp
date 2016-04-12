#ifdef _WIN32

#include <string>
#include <iostream>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include "TCPSocket.h"
#include "UDPSocket.h"
#include "INetwork.hh"
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
	std::vector<SOCKET> buffer;
	FD_ZERO(_readSet);
	for (std::vector<SOCKET>::iterator it = fd.begin(); it != fd.end(); ++it)
	{
		FD_SET((*it), _readSet);
	}
	if (select(_listen + 1, _readSet, NULL, NULL, to) == -1) {
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
TransmitStatus WNetwork<T>::sendData(void *data, int size, SOCKET sock, ConnectionData *addr)
{
	return _socket->sendData(data, size, sock, addr);
}

template <typename T>
TransmitStatus WNetwork<T>::recvData(void *data, int size, SOCKET sock, ConnectionData *addr)
{
	return _socket->rcvData(data, size, sock, addr);
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
INetwork<T>*		getNetworkInstance()
{
	return new WNetwork<T>();
}

#endif
