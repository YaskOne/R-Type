# include <string.h>
# include "FailPacket.h"

FailPacket::FailPacket(ServerTCPResponse resp)
  : AServerPacket<ServerTCPResponse>(resp, sizeof(*_header)), _header(new ServerTCPHeader)
{
  _header->command = resp;
  _header->magic = MAGIC;
  _header->size = 0;
}

FailPacket::FailPacket(ServerTCPHeader* header)
  : AServerPacket<ServerTCPResponse>(header->command, 0), _header(header)
{
}

FailPacket::~FailPacket()
{
}

char*				FailPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header)];

  memcpy(buff, _header, sizeof(*_header));
  return buff;
}

bool				FailPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH || _header->command > FAIL)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

void				FailPacket::setRawData(char *data)
{
}
