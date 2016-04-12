#ifndef TCPSOCKET_H_
# define TCPSOCKET_H_

# include "NetworkDefines.h"
# include "INetwork.hh"

# pragma comment(lib, "ws2_32.lib")

class							TCPSocket
{
private:
	std::string					_ip;
	std::string					_port;

public:
	TCPSocket();
	~TCPSocket();

	SOCKET						startNetwork(std::string const &ip, std::string const &port, addrinfo*);
	TransmitStatus				sendData(const void *buffer, int size, SOCKET socket, ConnectionData *addr);
	TransmitStatus				rcvData(void*, int size, SOCKET socket, ConnectionData *addr);
};

#endif
