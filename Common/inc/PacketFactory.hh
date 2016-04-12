#ifndef PACKETFACTORY_H_
# define PACKETFACTORY_H_

#include "IClientPacket.hh"
#include "IServerPacket.hh"
#include "NewGamePacket.h"
#include "ReqGamePacket.h"
#include "NickPacket.h"
#include "JoinPacket.hh"
#include "AuthTCPPacket.h"
#include "GameInfoPacket.h"
#include "GameListPacket.h"
#include "DesGamePacket.h"
#include "FailPacket.h"
#include "GameOverPacket.h"
#include "AuthUDPPacket.h"
#include "NextLvlPacket.hh"
#include "CrePlayPacket.h"
#include "CreObjPacket.h"
#include "CreIAPacket.h"
#include "FirePacket.h"
#include "MovePacket.h"
#include "SendMovePacket.h"
#include "DisconnectPacket.h"
#include "DelItemPacket.h"
#include "CAuthUDPPacket.h"
#include "NetworkDefines.h"
#include "AlivePacket.hh"
#include "BonusPacket.hh"

class PacketFactory
{
public:
  PacketFactory();
  virtual ~PacketFactory();

  IClientPacket<ClientTCPCommand>*		build(ClientTCPHeader*);
  IClientPacket<ClientUDPCommand>*		build(ClientUDPHeader*);
  IServerPacket<ServerTCPResponse>*		build(ServerTCPHeader*);
  IServerPacket<ServerUDPResponse>*		build(ServerUDPHeader*);
};

#endif
