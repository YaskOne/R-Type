# include <string.h>
# include "CreObjPacket.h"

CreObjPacket::CreObjPacket(ServerUDPResponse resp, int idx, int id, float x, float y, float speedX, float speedY, ObjectInfo::ShotType type):
AServerPacket<ServerUDPResponse>(resp, sizeof(*_data) + sizeof(*_header)), _data(new CreObjData), _header(new ServerUDPHeader)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = sizeof(*_data);
  _header->idx = idx;
  _data->id = id;
  _data->x = x;
  _data->y = y;
  _data->speedX = speedX;
  _data->speedY = speedY;
  _data->type = type;
  _data->magic = MAGIC;
}

CreObjPacket::CreObjPacket(ServerUDPHeader *header)
  : AServerPacket<ServerUDPResponse>(header->command, header->size + sizeof(*_header)), _data(new CreObjData), _header(header)
{
}

CreObjPacket::~CreObjPacket()
{
}

void			CreObjPacket::setRawData(char *data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

CreObjData*		CreObjPacket::getData() const
{
  return _data;
}

bool			CreObjPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH_UDP || _header->command > MOVE)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				CreObjPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}
