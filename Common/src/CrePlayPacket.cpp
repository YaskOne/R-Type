# include <string.h>
# include "CrePlayPacket.h"

CrePlayPacket::CrePlayPacket(ServerUDPResponse resp, int idx, int id, float x, float y) : AServerPacket<ServerUDPResponse>(resp, sizeof(*_data) + sizeof(*_header)), _data(new CrePlayData), _header(new ServerUDPHeader)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = sizeof(*_data);
  _header->idx = idx;
  _data->id = id;
  _data->x = x;
  _data->y = y;
  _data->magic = MAGIC;
}

CrePlayPacket::CrePlayPacket(ServerUDPHeader *header)
  : AServerPacket<ServerUDPResponse>(header->command, header->size + sizeof(*_header)), _data(new CrePlayData), _header(header)
{
}

CrePlayPacket::~CrePlayPacket()
{
}

void			CrePlayPacket::setRawData(char *data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

CrePlayData*		CrePlayPacket::getData() const
{
  return _data;
}

bool			CrePlayPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH_UDP || _header->command > MOVE)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				CrePlayPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}
