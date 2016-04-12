#ifndef ISOCKET_H_
# define ISOCKET_H_

# include <string>
# include "SINetwork.h"
# include "NetworkDefines.h"

typedef enum
{
	TCP,
	UDP
} Proto;

class							ISocket
{
public:
	virtual ~ISocket() {};

public:

	virtual bool				initServerSocket(std::string const &host, std::string const &) = 0;
	virtual bool				initClientSocket(std::string const &, std::string const &) = 0;
	virtual SOCKET			acceptSocket() = 0;
	virtual TransmitStatus		recvData(SOCKET, void *data, int) = 0;
	virtual TransmitStatus		sendData(SOCKET, void *data, int) = 0;
	virtual SOCKET			getFd() const = 0;
	virtual void				selectFunc(struct timeval *to) = 0;
	virtual void				zeroFD() = 0;
	virtual void				setFD(SOCKET) = 0;
	virtual bool				checkFdIsSet(SOCKET) = 0;
	virtual bool				closeConnection(SOCKET) = 0;
};

#endif