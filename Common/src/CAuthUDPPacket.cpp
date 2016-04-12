# include <string.h>
# include "CAuthUDPPacket.h"

CAuthUDPPacket::CAuthUDPPacket(ClientUDPCommand resp, int idx, std::string const& name) : AClientPacket<ClientUDPCommand>(resp, sizeof(*_data) + sizeof(*_header)), _data(new CAuthUDPData), _header(new ClientUDPHeader)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = sizeof(*_data);
  _header->idx = idx;
  memset(_data->data, 0, sizeof(*_data));
  memcpy(_data->data, name.c_str(), name.size());
  _data->magic = MAGIC;
}

CAuthUDPPacket::CAuthUDPPacket(ClientUDPHeader* header)
  : AClientPacket<ClientUDPCommand>(header->command, header->size + sizeof(*_header)), _data(new CAuthUDPData), _header(header)
{
}

CAuthUDPPacket::~CAuthUDPPacket()
{
}

void			CAuthUDPPacket::setRawData(char *data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

CAuthUDPData*		CAuthUDPPacket::getData() const
{
  return _data;
}

bool			CAuthUDPPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < CAUTH_UDP || _header->command > DISCONNECT)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				CAuthUDPPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}
