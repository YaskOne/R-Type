#include "AlivePacket.hh"

AlivePacket::AlivePacket(ClientUDPCommand cmd, int idx, bool isAlive)
  : AClientPacket<ClientUDPCommand>(cmd, sizeof(*_data) + sizeof(*_header)),
    _data(new AliveData),
    _header(new ClientUDPHeader)
{
  _header->magic = MAGIC;
  _header->command = cmd;
  _header->size = sizeof(*_data);
  _header->idx = idx;
  _data->isAlive = isAlive;
  _data->magic = MAGIC;
}

AlivePacket::AlivePacket(ClientUDPHeader* header)
  : AClientPacket<ClientUDPCommand>(header->command, header->size + sizeof(*_header)),
    _data(new AliveData),
    _header(header)
{
}

AlivePacket::~AlivePacket()
{
}

void		AlivePacket::setRawData(char* data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

AliveData*	AlivePacket::getData() const
{
  return _data;
}

bool		AlivePacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < CAUTH_UDP || _header->command > DISCONNECT)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*		AlivePacket::deserialize()
{
  char*                         buff = new char[sizeof(*_header) + sizeof(*_data)];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  return buff;
}
