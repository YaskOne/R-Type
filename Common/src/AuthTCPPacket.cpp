# include <string.h>
# include "AuthTCPPacket.h"

AuthTCPPacket::AuthTCPPacket(ServerTCPResponse resp, Bool success) : AServerPacket<ServerTCPResponse>(resp, sizeof(*_data) + sizeof(*_header)), _header(new ServerTCPHeader), _data(new AuthTCPData)
{
  _header->size = sizeof(*_data);
  _header->magic = MAGIC;
  _header->command = resp;
  _data->success = success;
  _data->magic = MAGIC;
}

AuthTCPPacket::AuthTCPPacket(ServerTCPHeader* header)
  : AServerPacket<ServerTCPResponse>(header->command, header->size + sizeof(*_header)), _data(new AuthTCPData), _header(header)
{
}

AuthTCPPacket::~AuthTCPPacket()
{
}

char*				AuthTCPPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}

bool				AuthTCPPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH || _header->command > FAIL)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

void				AuthTCPPacket::setRawData(char *data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

AuthTCPData*			AuthTCPPacket::getData() const
{
  return _data;
}
