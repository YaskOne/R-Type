#ifndef NETWORKHANDLER_H_
# define NETWORKHANDLER_H_

# include <string>
# include <vector>
# include "STCPSocket.h"
# include "SUDPSocket.h"
# include "NetworkDefines.h"
# include "SINetwork.hh"
# include "SUNetwork.hh"
# include "SWNetwork.hh"
# include "ClientInfo.h"
# include "PacketFactory.hh"
# include "IServerPacket.hh"
# include "IClientPacket.hh"

extern	SOCKET					_listen;
extern  std::vector<ClientInfo*>		_clientList;
template class					SINetwork<STCPSocket>;

class						NetworkHandler
{
 public:
  NetworkHandler(std::string const& ip, std::string const& port);
  ~NetworkHandler();
 void						broadcast(IServerPacket<ServerTCPResponse>*);
  void						broadcast(IServerPacket<ServerUDPResponse>*);
  bool						sendToClient(ClientInfo *, IServerPacket<ServerTCPResponse> *);
  bool						receiveFromClient(ClientInfo *);
  bool						tryReceive(ClientInfo *, char*, int size);
  bool						initSocket();
  bool						selectClient();
  ClientInfo*					getActiveClient();

 private:
  bool						acceptNewClient();
  void						closeConnection(ClientInfo *);

 private:
  std::string					_ip;
  std::string					_port;
  SINetwork<STCPSocket>*				_network;
  std::vector<ClientInfo*>			_activeClients;
  PacketFactory*				_factory;
  struct timeval				_to;

};

#endif
