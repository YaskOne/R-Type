#ifndef NETWORKHANDLER_H_
# define NETWORKHANDLER_H_

# include <string>
# include <vector>
# include "CTCPSocket.hh"
# include "CUDPSocket.hh"
# include "NetworkDefines.h"
# include "CINetwork.hh"
# include "CUNetwork.hh"
# include "CWNetwork.hh"
# include "PacketFactory.hh"

template class				CINetwork<CTCPSocket>;

class CNetworkHandler
{
public:
  CNetworkHandler(std::string const& ip, std::string const& port);
  ~CNetworkHandler();

private:
  std::string				_ip;
  std::string				_port;
  CINetwork<CTCPSocket>*			_network;
  std::vector<SOCKET>			_activeFD;
  PacketFactory*			_factory;
  std::string				_packet;
  SOCKET				_listen;

public:
  bool						initSocket();
  bool						selectSockets();
  bool						sendToServer(IClientPacket<ClientTCPCommand>*);
  IServerPacket<ServerTCPResponse>*		receiveFromServer();
  bool						tryReceive(char* header, int size);
  void						closeConnection();
  std::string					getPacket() const;
};

#endif
