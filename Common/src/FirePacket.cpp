# include <string.h>
# include "FirePacket.h"

FirePacket::FirePacket(ClientUDPCommand resp, int idx, float x, float y) : AClientPacket<ClientUDPCommand>(resp, sizeof(*_data) + sizeof(*_header)), _data(new FireData), _header(new ClientUDPHeader)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = sizeof(*_data);
  _header->idx = idx;
  _data->x = x;
  _data->y = y;
  _data->magic = MAGIC;
}

FirePacket::FirePacket(ClientUDPHeader* header)
  : AClientPacket<ClientUDPCommand>(header->command, header->size + sizeof(*_header)), _data(new FireData), _header(header)
{
}

FirePacket::~FirePacket()
{
}

void			FirePacket::setRawData(char *data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

FireData*		FirePacket::getData() const
{
  return _data;
}

bool			FirePacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < CAUTH_UDP || _header->command > DISCONNECT)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				FirePacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}
