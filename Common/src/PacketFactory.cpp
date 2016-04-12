#include "PacketFactory.hh"

PacketFactory::PacketFactory()
{}

PacketFactory::~PacketFactory()
{}

IServerPacket<ServerUDPResponse>*	PacketFactory::build(ServerUDPHeader *header)
{
  switch(header->command)
    {
    case AUTH_UDP:
      return new AuthUDPPacket(header);
      break;
    case CRE_PLAY:
      return new CrePlayPacket(header);
      break;
    case CRE_OBJ:
      return new CreObjPacket(header);
      break;
    case CRE_IA:
      return new CreIAPacket(header);
      break;
    case DEL_ITEM:
      return new DelItemPacket(header);
      break;
    case NEXT_LVL:
      return new NextLvlPacket(header);
      break;
    case MOVE:
      return new MovePacket(header);
      break;
    case BONUS_PACKET:
      return new BonusPacket(header);
      break;
    default:
      return NULL;
    }
}

IServerPacket<ServerTCPResponse>*	PacketFactory::build(ServerTCPHeader *header)
{
  switch(header->command)
    {
    case AUTH:
      return new AuthTCPPacket(header);
      break;
    case GAME_OVER:
      return new GameOverPacket(header);
      break;
    case GAME_INFO:
      return new GameInfoPacket(header);
      break;
    case START_GAME_LIST:
      return new GameListPacket(header);
      break;
    case DES_GAME:
      return new DesGamePacket(header);
      break;
    case END_GAME_LIST:
      return new GameListPacket(header);
      break;
    case FAIL:
      return new FailPacket(header);
      break;
    default:
      return NULL;
    }
}

IClientPacket<ClientUDPCommand>*		PacketFactory::build(ClientUDPHeader *header)
{
  switch(header->command)
    {
    case CAUTH_UDP:
      return new CAuthUDPPacket(header);
      break;
    case FIRE:
      return new FirePacket(header);
      break;
    case SEND_MOVE:
      return new SendMovePacket(header);
      break;
    case ALIVE:
      return new AlivePacket(header);
      break;
    case DISCONNECT:
      return new DisconnectPacket(header);
      break;
    default:
      return NULL;
      break;
    }
}

IClientPacket<ClientTCPCommand>*		PacketFactory::build(ClientTCPHeader* header)
{
  switch(header->command)
    {
    case AUTH_TCP:
      return new NickPacket(header);
      break;
    case JOIN_GAME:
      return new JoinPacket(header);
      break;
    case REQ_GAME:
      return new ReqGamePacket(header);
      break;
    case ADD_GAME:
      return new NewGamePacket(header);
      break;
    default:
      return NULL;
      break;
    }
}
