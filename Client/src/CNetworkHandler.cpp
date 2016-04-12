#include <iostream>
#include "CNetworkHandler.hh"

CNetworkHandler::CNetworkHandler(std::string const & ip, std::string const & port)
	: _ip(ip),
	  _port(port),
	  _network(getNetworkInstance<CTCPSocket>()),
	  _factory(new PacketFactory())
{
}

CNetworkHandler::~CNetworkHandler()
{
  delete _network;
  delete _network;
}

bool CNetworkHandler::initSocket()
{
  if (_network->initClientSocket(_ip, _port))
    {
      _listen = _network->getFd();
      return true;
    }
  return false;
}

bool CNetworkHandler::selectSockets()
{
  _activeFD.clear();
  _activeFD.push_back(_listen);
  _network->selectFD(_activeFD, NULL);
  if (_activeFD.size() < 1)
    return false;
  return true;
}

// void	CNetworkHandler::broadcast(IClientPacket* packet)
// {
//   for (std::vector<ClientInfo*>::iterator it = _clientList.begin(); it != _clientList.end(); ++it)
//     {
//       sendToClient((*it), packet);
//     }
// }

IServerPacket<ServerTCPResponse>*	CNetworkHandler::receiveFromServer()
{
  ServerTCPHeader*			header = new ServerTCPHeader;
  char*					buff;
  IServerPacket<ServerTCPResponse>*	packet;

  if (!tryReceive((char*)header, sizeof(ServerTCPHeader)))
    return NULL;
  packet = _factory->build(header);
  if (!packet || !packet->checkHeader())
    return NULL;
  if (header->size == 0)
    return packet;
  buff = new char[header->size];
  if (!tryReceive(buff, header->size))
    return NULL;
  packet->setRawData(buff);
  return packet;
}

bool			CNetworkHandler::tryReceive(char* header, int size)
{
  memset(header, 0, size);
  try
    {
      _network->recvData(header, size, _listen, NULL);
    }
  catch (Exceptions::NetworkExcept e)
    {
      std::cerr << e.what() << std::endl;
      closeConnection();
      return false;
    }
  catch (Exceptions::ConnectionExcept e)
    {
      std::cerr << e.what() << std::endl;
      closeConnection();
      return false;
    }
  return true;
}

bool			CNetworkHandler::sendToServer(IClientPacket<ClientTCPCommand>* packet)
{
  char*			toSend = packet->deserialize();

  try
    {
      _network->sendData(toSend, packet->getPacketSize(), _listen, NULL);
    }
  catch (Exceptions::NetworkExcept e)
    {
      std::cerr << e.what() << std::endl;
      closeConnection();
      return false;
    }
  catch (Exceptions::ConnectionExcept e)
    {
      std::cerr << e.what() << std::endl;
      closeConnection();
      return false;
    }
  return true;
}

void CNetworkHandler::closeConnection()
{
  _network->closeConnection(_listen);
}

std::string CNetworkHandler::getPacket() const
{
  return _packet;
}
