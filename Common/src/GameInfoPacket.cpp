# include <string.h>
# include "GameInfoPacket.h"

GameInfoPacket::GameInfoPacket(ServerTCPResponse resp, std::string const& ip, int port) : AServerPacket<ServerTCPResponse>(resp, sizeof(*_data) + sizeof(*_header)), _header(new ServerTCPHeader), _data(new GameInfoData)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = sizeof(*_data);
  memset(_data->ip, 0, sizeof(_data->ip));
  memcpy(_data->ip, ip.c_str(), ip.size());
  _data->port = port;
  _data->magic = MAGIC;
}

GameInfoPacket::GameInfoPacket(ServerTCPHeader* header)
  : AServerPacket<ServerTCPResponse>(header->command, header->size + sizeof(*_header)), _data(new GameInfoData), _header(header)
{
}

GameInfoPacket::~GameInfoPacket()
{
}

char*				GameInfoPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}

bool				GameInfoPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH || _header->command > FAIL)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

void				GameInfoPacket::setRawData(char *data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

GameInfoData*			GameInfoPacket::getData() const
{
  return _data;
}
