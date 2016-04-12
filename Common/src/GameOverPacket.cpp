# include <string.h>
# include "GameOverPacket.h"

GameOverPacket::GameOverPacket(ServerTCPResponse resp, int data) : AServerPacket<ServerTCPResponse>(resp, sizeof(*_data) + sizeof(*_header)), _header(new ServerTCPHeader), _data(new GameOverData)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = sizeof(*_data);
  _data->data = data;
  _data->magic = MAGIC;
}

GameOverPacket::GameOverPacket(ServerTCPHeader* header)
  : AServerPacket<ServerTCPResponse>(header->command, header->size + sizeof(*_header)), _data(new GameOverData), _header(header)
{
}

GameOverPacket::~GameOverPacket()
{
}

char*				GameOverPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}

bool				GameOverPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH || _header->command > FAIL)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

void				GameOverPacket::setRawData(char *data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

GameOverData*			GameOverPacket::getData() const
{
  return _data;
}
