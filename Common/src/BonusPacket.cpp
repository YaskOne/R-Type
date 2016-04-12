# include <string.h>
# include "BonusPacket.hh"

BonusPacket::BonusPacket(ServerUDPResponse resp,
			 ObjectInfo::WaveType bonusType,
			 int idx,
			 int id,
			 float x,
			 float y,
			 float speed)
  : AServerPacket<ServerUDPResponse>(resp, sizeof(*_data) + sizeof(*_header)),
    _data(new BonusData),
    _header(new ServerUDPHeader)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = sizeof(*_data);
  _header->idx = idx;
  _data->id = id;
  _data->x = x;
  _data->y = y;
  _data->speed = speed;
  _data->type = bonusType;
  _data->magic = MAGIC;
}

BonusPacket::BonusPacket(ServerUDPHeader *header)
  : AServerPacket<ServerUDPResponse>(header->command, header->size + sizeof(*_header)), _data(new BonusData), _header(header)
{
}

BonusPacket::~BonusPacket()
{
}

void			BonusPacket::setRawData(char *data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

BonusData*		BonusPacket::getData() const
{
  return _data;
}

bool			BonusPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH_UDP || _header->command > MOVE)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				BonusPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}
