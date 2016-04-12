#include "CUDPNetworkHandler.hh"
#include "PacketFactory.hh"

CUDPNetworkHandler::CUDPNetworkHandler(std::string const& ip,
				       std::string const& port)
  : _ip(ip),
    _port(port),
    _network(getNetworkInstance<CUDPSocket>()),
    _factory(new PacketFactory()),
    _header(NULL)
{
  _network->getServAddr(ip, port, &_serveraddr);
}

CUDPNetworkHandler::~CUDPNetworkHandler()
{
  delete _network;
  delete _factory;
}

bool		CUDPNetworkHandler::initSocket()
{
  if (_network->initClientSocket(_ip, _port))
    {
      _socket = _network->getFd();
      return true;
    }
  return false;
}

IServerPacket<ServerUDPResponse>*	CUDPNetworkHandler::receive()
{
  char*					buff;
  IServerPacket<ServerUDPResponse>*	packet;

  if (_header)
    {
      packet = _factory->build(_header);
      if (!packet || !packet->checkHeader())
	return NULL;
      buff = new char[_header->size];
      memset(buff, 0, _header->size);
      try
	{
	  _network->recvData((void *)buff, _header->size, _socket, &_serveraddr);
	}
      catch (Exceptions::NetworkExcept e)
	{
	  std::cerr << e.what() << std::endl;
	  _header = NULL;
	  return NULL;
	}
      packet->setRawData(buff);
      _header = NULL;
      return packet;
    }
  return NULL;
}

bool					CUDPNetworkHandler::send(IClientPacket<ClientUDPCommand>* response)
{
  char*					buff = response->deserialize();

  try
    {
      _network->sendData(buff,
			 response->getPacketSize(),
			 _socket,
			 &_serveraddr);
    }
  catch (Exceptions::NetworkExcept e)
    {
      std::cerr << e.what() << std::endl;
      return false;
    }
  return true;
}

bool					CUDPNetworkHandler::selectServer(struct timeval *to)
{
  std::vector<SOCKET>			fdList;

  fdList.push_back(_socket);
  _network->selectFD(fdList, to);
  if (!fdList.empty())
    {
      ServerUDPHeader*	header = new ServerUDPHeader();
      ClientDatas	datas;

      try
	{
	  _network->recvData(header, sizeof(*header), _socket, &datas);
	}
      catch (Exceptions::NetworkExcept e)
	{
	  std::cerr << e.what() << std::endl;
	  return false;
	}
      _header = header;
      return true;
    }
  return false;
}

bool		operator==(ClientDatas left, ClientDatas right)
{
  if (left.sin_family == right.sin_family
      && left.sin_port == right.sin_port
      && left.sin_addr.s_addr == right.sin_addr.s_addr)
    return true;
  return false;
}

float						CUDPNetworkHandler::getStartTime() const
{
  return _startTime;
}

void						CUDPNetworkHandler::setStartTime(float time)
{
  _startTime = time;
}
