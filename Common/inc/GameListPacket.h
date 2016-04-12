#ifndef GAMELISTPACKET_H_
# define GAMELISTPACKET_H_

# include "AServerPacket.hh"

class GameListPacket : public AServerPacket<ServerTCPResponse>
{
 public:
  GameListPacket(ServerTCPResponse);
  GameListPacket(ServerTCPHeader*);
  ~GameListPacket();

  char*				deserialize();
  bool				checkHeader();
  void				setRawData(char *);


 private:
  ServerTCPHeader*		_header;

};

#endif /* !GAMELISTPACKET_H_ */
