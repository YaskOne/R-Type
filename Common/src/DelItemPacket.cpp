# include <string.h>
# include "DelItemPacket.h"

DelItemPacket::DelItemPacket(ServerUDPResponse resp, int idx, int data) : AServerPacket<ServerUDPResponse>(resp, sizeof(*_data) + sizeof(*_header)), _data(new DelItemData), _header(new ServerUDPHeader)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = sizeof(*_data);
  _header->idx = idx;
  _data->data = data;
  _data->magic = MAGIC;
}

DelItemPacket::DelItemPacket(ServerUDPHeader *header)
  : AServerPacket<ServerUDPResponse>(header->command, header->size + sizeof(*_header)), _data(new DelItemData), _header(header)
{
}

DelItemPacket::~DelItemPacket()
{
}

void			DelItemPacket::setRawData(char *data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

DelItemData*		DelItemPacket::getData() const
{
  return _data;
}

bool			DelItemPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH_UDP || _header->command > MOVE)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				DelItemPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}
