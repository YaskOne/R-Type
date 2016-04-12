#ifndef CLIENTINFO_H_
# define CLIENTINFO_H_

# include <string>
# include "NetworkDefines.h"
# include "IClientPacket.hh"

template class	IClientPacket<ClientTCPCommand>;

class ClientInfo
{
 public:
  ClientInfo(SOCKET socket);
  ClientInfo(SOCKET socket, std::string const& nick);
  ~ClientInfo();

 public:
  bool					isInGame() const;
  void					setInGame(bool inGame);
  void					setPacket(IClientPacket<ClientTCPCommand>*);
  IClientPacket<ClientTCPCommand>*	getPacket() const;
  SOCKET				getSocket() const;
  std::string				getNickname() const;
  void					setNickname(std::string const& nick);
  bool					getDisconnected() const;
  void					setDisconnected(bool);

 private:
  bool					_isInGame;
  bool					_disconnected;
  SOCKET				_socket;
  std::string				_nickname;
  IClientPacket<ClientTCPCommand>*	_packet;
};

#endif
