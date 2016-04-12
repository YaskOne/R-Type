#ifndef UDPNETWORKHANDLER_H_
# define UDPNETWORKHANDLER_H_

# include <string>
# include <vector>
# include "SUDPSocket.h"
# include "NetworkDefines.h"
# include "SINetwork.hh"
# include "SUNetwork.hh"
# include "SWNetwork.hh"
# include "GamerInfo.hh"
# include "PacketFactory.hh"
# include "IServerPacket.hh"
# include "IClientPacket.hh"
# include "Exceptions.hpp"

template class					SINetwork<SUDPSocket>;

class						UDPNetworkHandler
{
public:
  UDPNetworkHandler(std::string const&, std::string const&, std::vector<GamerInfo*>*);
  virtual ~UDPNetworkHandler();

private:
  UDPNetworkHandler(const UDPNetworkHandler &);
  UDPNetworkHandler				&operator=(const UDPNetworkHandler &);
  GamerInfo*					getClient(ClientDatas*);

public:
  bool						initSocket();
  GamerInfo*					selectClient();
  IClientPacket<ClientUDPCommand>*		receiveFrom(GamerInfo*);
  ClientDatas*					copyClientAddr(ClientDatas* datas);
  bool						sendTo(GamerInfo*, IServerPacket<ServerUDPResponse>*);
  void						broadcast(IServerPacket<ServerUDPResponse>*);

private:
  std::string					_ip;
  std::string					_port;
  SINetwork<SUDPSocket>*			_network;
  std::vector<GamerInfo*>*			_clients;
  PacketFactory*				_factory;
  SOCKET					_socket;
  struct timeval				_tv;
};

bool						operator==(ClientDatas left, ClientDatas right);

#endif /* !UDPNETWORKHANDLER_H_ */
