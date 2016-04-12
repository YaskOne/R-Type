#ifndef INETWORK_H_
# define INETWORK_H_

# include <vector>
# include "NetworkDefines.h"

typedef enum	e_TransmitStatus
{
	ERR = -1,
	DISCONNECTED = 0,
	PASSED = 1,
}				TransmitStatus;

template <class T>
class									INetwork
{
public:
	virtual bool					initClientSocket(std::string const &ip, std::string const &port) = 0;
	virtual TransmitStatus			recvData(void *data, int size, SOCKET, ConnectionData *addr) = 0;
	virtual TransmitStatus			sendData(void *data, int size, SOCKET, ConnectionData *addr) = 0;
	virtual SOCKET					getFd() const = 0;
	virtual void					selectFD(std::vector<SOCKET>& fd, struct timeval *to) = 0;
	virtual bool					closeConnection(SOCKET) = 0;
};

template <typename T>
INetwork<T>*								getNetworkInstance();

#endif