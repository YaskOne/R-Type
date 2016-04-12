#include <string.h>
#include "NewGamePacket.h"

NewGamePacket::NewGamePacket(ClientTCPCommand command, std::string const& data)
  : AClientPacket<ClientTCPCommand>(command, sizeof(*_data) + sizeof(*_header)), _data(new NewGameData), _header(new ClientTCPHeader)
{
  _header->magic = MAGIC;
  _header->command = command;
  _header->size = sizeof(*_data);
  memset(_data->data, 0, sizeof(*_data));
  memcpy(&(_data->data), data.c_str(), data.size());
}

NewGamePacket::NewGamePacket(ClientTCPHeader* header)
  : AClientPacket<ClientTCPCommand>(header->command, header->size + sizeof(*_header)), _data(new NewGameData), _header(header)
{
}

NewGamePacket::~NewGamePacket()
{
}

void			NewGamePacket::setRawData(char *data)
{
  void*			buff;

  memcpy(_data, (void *)data, sizeof(*_data));
}

NewGameData*		NewGamePacket::getData() const
{
  return _data;
}

bool			NewGamePacket::checkHeader()
{
    if (_header->magic != MAGIC)
    return false;
  else if (_header->command < AUTH_TCP|| _header->command > QUIT)
    return false;
  else if (_header->size < 0)
    return false;
  return true;
}

char*				NewGamePacket::deserialize()
{
  char*				buff = new char[sizeof(*_header) + sizeof(*_data) + 1];

  memcpy(buff, _header, sizeof(*_header));
  memcpy(buff + sizeof(*_header), _data, sizeof(*_data));
  buff[sizeof(*_header) + sizeof(*_data)] = 0;
  return buff;
}
