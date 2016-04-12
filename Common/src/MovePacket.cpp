# include <string.h>
# include "MovePacket.h"

MovePacket::MovePacket(ServerUDPResponse resp, int idx, int id, float x, float y, uint32_t score) : AServerPacket<ServerUDPResponse>(resp, sizeof(*_data) + sizeof(*_header)), _data(new MoveData), _header(new ServerUDPHeader)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = sizeof(*_data);
  _header->idx = idx;
  _data->id = id;
  _data->x = x;
  _data->y = y;
  _data->score = score;
  _data->magic = MAGIC;
}

MovePacket::MovePacket(ServerUDPHeader *header)
  : AServerPacket<ServerUDPResponse>(header->command, header->size + sizeof(*_header)), _data(new MoveData), _header(header)
{
}

MovePacket::~MovePacket()
{
}

void			MovePacket::setRawData(char *data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

MoveData*		MovePacket::getData() const
{
  return _data;
}

bool			MovePacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH_UDP || _header->command > MOVE)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				MovePacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data)];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  return buff;
}
