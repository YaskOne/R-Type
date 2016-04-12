#include "ClientInfo.h"

ClientInfo::ClientInfo(SOCKET socket)
  : _isInGame(false),
    _disconnected(false),
    _socket(socket),
    _packet(NULL)
{
}

ClientInfo::ClientInfo(SOCKET socket, std::string const & nick)
  : _isInGame(false), _disconnected(false), _socket(socket), _nickname(nick), _packet(NULL)
{
}

ClientInfo::~ClientInfo()
{
}

bool					ClientInfo::isInGame() const
{
  return _isInGame;
}

void					ClientInfo::setInGame(bool inGame)
{
  _isInGame = inGame;
}

void					ClientInfo::setPacket(IClientPacket<ClientTCPCommand>* packet)
{
  if (!_packet)
    delete (_packet);
  _packet = packet;
}

IClientPacket<ClientTCPCommand>*	ClientInfo::getPacket() const
{
  return _packet;
}

SOCKET					ClientInfo::getSocket() const
{
  return _socket;
}

void					ClientInfo::setDisconnected(bool disc)
{
  _disconnected = disc;
}

bool					ClientInfo::getDisconnected() const
{
  return _disconnected;
}

std::string				ClientInfo::getNickname() const
{
  return _nickname;
}

void					ClientInfo::setNickname(std::string const& nick)
{
  if (nick.size() > 19)
    _nickname = nick.substr(0, 19);
  else
    _nickname = nick;
}
