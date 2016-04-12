# include <string.h>
# include "SendMovePacket.h"

SendMovePacket::SendMovePacket(ClientUDPCommand resp, int idx, Direction dir) : AClientPacket<ClientUDPCommand>(resp, sizeof(*_data) + sizeof(*_header)), _data(new SendMoveData), _header(new ClientUDPHeader)
{
  _header->magic = MAGIC;
  _header->command = resp;
  _header->size = sizeof(*_data);
  _header->idx = idx;
  _data->dir = dir;
  _data->magic = MAGIC;
}

SendMovePacket::SendMovePacket(ClientUDPHeader* header)
  : AClientPacket<ClientUDPCommand>(header->command, header->size + sizeof(*_header)), _data(new SendMoveData), _header(header)
{
}

SendMovePacket::~SendMovePacket()
{
}

void			SendMovePacket::setRawData(char *data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

SendMoveData*		SendMovePacket::getData() const
{
  return _data;
}

bool			SendMovePacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < CAUTH_UDP || _header->command > DISCONNECT)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				SendMovePacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data)];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  return buff;
}
