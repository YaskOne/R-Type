# include <string.h>
# include "CreIAPacket.h"

CreIAPacket::CreIAPacket(ServerUDPResponse resp, int idx, int id, float x, float y, float speed, float coeff, ObjectInfo::WaveType type) :
AServerPacket<ServerUDPResponse>(resp, sizeof(*_data) + sizeof(*_header)), _data(new CreIAData), _header(new ServerUDPHeader)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = sizeof(*_data);
  _header->idx = idx;
  _data->id = id;
  _data->x = x;
  _data->y = y;
  _data->speed = speed;
  _data->coeff = coeff;
  _data->iatype = type;
  _data->magic = MAGIC;
}

CreIAPacket::CreIAPacket(ServerUDPHeader *header)
  : AServerPacket<ServerUDPResponse>(header->command, header->size + sizeof(*_header)), _data(new CreIAData), _header(header)
{
}

CreIAPacket::~CreIAPacket()
{
}

void			CreIAPacket::setRawData(char *data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

CreIAData*		CreIAPacket::getData() const
{
  return _data;
}

bool			CreIAPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH_UDP || _header->command > MOVE)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				CreIAPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}
