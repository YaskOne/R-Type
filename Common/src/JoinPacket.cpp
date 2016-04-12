#include "JoinPacket.hh"

JoinPacket::JoinPacket(ClientTCPCommand command, int id)
  : AClientPacket(command, sizeof(*_data) + sizeof(*_header)), _data(new JoinData), _header(new ClientTCPHeader)
{
  _header->magic = MAGIC;
  _header->command = command;
  _header->size = sizeof(*_data);
  _data->id = id;
}

JoinPacket::JoinPacket(ClientTCPHeader* header)
  : AClientPacket(header->command, header->size + sizeof(*_header)), _data(new JoinData), _header(header)
{
}

JoinPacket::~JoinPacket()
{
}

void			JoinPacket::setRawData(char *data)
{
  memcpy(_data, (void *)data, sizeof(*_data));
}

JoinData*		JoinPacket::getData() const
{
  return _data;
}

bool			JoinPacket::checkHeader()
{
  if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH_TCP|| _header->command > QUIT)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				JoinPacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}
