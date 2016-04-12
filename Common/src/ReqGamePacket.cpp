#include <string.h>
#include "ReqGamePacket.h"

ReqGamePacket::ReqGamePacket(ClientTCPCommand command)
  : AClientPacket<ClientTCPCommand>(command, sizeof(*_header)), _header(new ClientTCPHeader)
{
  _header->magic = MAGIC;
  _header->command = command;
  _header->size = 0;
}

ReqGamePacket::ReqGamePacket(ClientTCPHeader* header)
  : AClientPacket<ClientTCPCommand>(header->command, sizeof(*_header)), _header(header)
{
}

ReqGamePacket::~ReqGamePacket()
{
}

void			ReqGamePacket::setRawData(char *data)
{
}


bool			ReqGamePacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH_TCP|| _header->command > QUIT)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				ReqGamePacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + 1];

  memcpy(buff, _header, sizeof(*_header));
  buff[sizeof(*_header)] = 0;
  return buff;
}
