# include <string.h>
# include "DesGamePacket.h"

DesGamePacket::DesGamePacket(ServerTCPResponse resp, int id, std::string const& gameName, std::string const& players) : AServerPacket<ServerTCPResponse>(resp, sizeof(*_data) + sizeof(*_header)), _header(new ServerTCPHeader), _data(new DesGameData)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = sizeof(*_data);
  _data->id = id;
  memset(_data->gameName, 0, 256);
  memset(_data->players, 0, 256);
  memcpy(&(_data->gameName), gameName.c_str(), gameName.size());
  // memcpy(&(_data->players), players.c_str(), players.size());
  _data->magic = MAGIC;
}

DesGamePacket::DesGamePacket(ServerTCPHeader* header) :
  AServerPacket<ServerTCPResponse>(header->command, header->size + sizeof(*_header)), _data(new DesGameData), _header(header)
{
}

DesGamePacket::~DesGamePacket()
{
}

char*				DesGamePacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}

bool				DesGamePacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH || _header->command > FAIL)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

void				DesGamePacket::setRawData(char *data)
{
  memcpy(_data, (void*)data, sizeof(*_data));
}

DesGameData*			DesGamePacket::getData() const
{
  return _data;
}
