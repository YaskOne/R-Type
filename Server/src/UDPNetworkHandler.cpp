#include "UDPNetworkHandler.hh"
#include "PacketFactory.hh"

UDPNetworkHandler::UDPNetworkHandler(std::string const& ip,
				     std::string const& port,
				     std::vector<GamerInfo*>* clients)
  : _ip(ip),
    _port(port),
    _network(getNetworkInstance<SUDPSocket>()),
    _clients(clients),
    _factory(new PacketFactory())
{
  _tv.tv_sec = 0;
  _tv.tv_usec = 1;
}

UDPNetworkHandler::~UDPNetworkHandler()
{
  std::vector<GamerInfo*>::iterator it;

  for (it = _clients->begin(); it != _clients->end(); ++it)
    delete (*it);
  delete _network;
  delete _factory;
}

bool			UDPNetworkHandler::initSocket()
{
  if (_network->initServerSocket(_ip, _port))
    {
      _socket = _network->getFd();
      return true;
    }
  return false;
}

GamerInfo*		UDPNetworkHandler::getClient(ClientDatas* datas)
{
  for (std::vector<GamerInfo*>::iterator it = _clients->begin(); it != _clients->end(); ++it)
    {
      if (*((*it)->getClientInfos()) == *datas)
	{
	  delete datas;
	  return *it;
	}
    }
  if (_clients->size() < 4)
    {
      GamerInfo*	newPlayer = new GamerInfo(datas);
      _clients->push_back(newPlayer);
      return newPlayer;
    }
  return NULL;
}

ClientDatas*				UDPNetworkHandler::copyClientAddr(ClientDatas* datas)
{
  ClientDatas				*cpy = new ClientDatas;

  memcpy(cpy, datas, sizeof(*datas));
  return cpy;
}

IClientPacket<ClientUDPCommand>*	UDPNetworkHandler::receiveFrom(GamerInfo *client)
{
  char*					buff;
  IClientPacket<ClientUDPCommand>*	packet;
  ClientUDPHeader*			header;

  if ((header = client->getHeader()))
    client->setHeader(NULL);
  else
    return NULL;
  packet = _factory->build(header);
  if (!packet)
    std::cerr << "Packet NULL" << std::endl;
  if (!packet || !packet->checkHeader())
    return NULL;
  //throw Exceptions::BadHeaderRequest("Error, received bad Header from known client ");
  buff = new char[header->size];
  memset(buff, 0, header->size);
  if (header->size != 0)
    {
      try
	{
	  _network->recvData(buff, header->size, _socket, this->copyClientAddr(client->getClientInfos()));
	}
      catch (Exceptions::NetworkExcept e)
	{
	  std::cerr << e.what() << std::endl;
	  return NULL;
	}
      packet->setRawData(buff);
    }
  return packet;
}

bool					UDPNetworkHandler::sendTo(GamerInfo *client,
								  IServerPacket<ServerUDPResponse>* response)
{
  char*					buff = response->deserialize();

  try
    {
      _network->sendData(buff,
			 response->getPacketSize(),
			 _socket,
			 client->getClientInfos());
    }
  catch (Exceptions::NetworkExcept e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  return true;
}

void					UDPNetworkHandler::broadcast(IServerPacket<ServerUDPResponse>* msg)
{
  std::vector<GamerInfo*>::iterator	it;

  for (it = _clients->begin(); it != _clients->end(); ++it)
    {
      this->sendTo(*it, msg);
    }
}

GamerInfo*				UDPNetworkHandler::selectClient()
{
  std::vector<SOCKET>			fdList;
  GamerInfo*				client;

  fdList.push_back(_socket);
  _network->selectClients(fdList, &_tv);
  if (!fdList.empty())
    {
      ClientDatas*	clientDatas = new ClientDatas();
      ClientUDPHeader*	header = new ClientUDPHeader();

      try
	{
	  _network->recvData(header, sizeof(*header), _socket, clientDatas);
	}
      catch (Exceptions::NetworkExcept e)
	{
	  std::cerr << e.what() << std::endl;
	  return NULL;
	}
      catch (Exceptions::ConnectionExcept e)
	{
	  return NULL;
	}
      if ((client = this->getClient(clientDatas)))
	{
	  client->setHeader(header);
	  return client;
	}
    }
  return NULL;
}

bool		operator==(ClientDatas left, ClientDatas right)
{
  return (left.sin_family == right.sin_family
  	  && left.sin_port == right.sin_port
  	  && left.sin_addr.s_addr == right.sin_addr.s_addr);
}
