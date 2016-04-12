# include <string.h>
# include "DisconnectPacket.h"

DisconnectPacket::DisconnectPacket(ClientUDPCommand resp, int idx) : AClientPacket<ClientUDPCommand>(resp, sizeof(*_header)), _header(new ClientUDPHeader)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = 0;
  _header->idx = idx;
}

DisconnectPacket::DisconnectPacket(ClientUDPHeader* header)
  : AClientPacket<ClientUDPCommand>(header->command, sizeof(*_header)), _header(header)
{
}

DisconnectPacket::~DisconnectPacket()
{
}

void			DisconnectPacket::setRawData(char *data)
{
}

bool			DisconnectPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < CAUTH_UDP || _header->command > DISCONNECT)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				DisconnectPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + 1];

  memcpy(buff, _header, sizeof(*_header));
  buff[sizeof(*_header)] = 0;
  return buff;
}
