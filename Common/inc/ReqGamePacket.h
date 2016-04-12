#ifndef REQGAMEPACKET_H_
# define REQGAMEPACKET_H_

# include "AClientPacket.hh"

class ReqGamePacket : public AClientPacket<ClientTCPCommand>
{
public:
  ReqGamePacket(ClientTCPCommand);
  ReqGamePacket(ClientTCPHeader*);
  ~ReqGamePacket();

private:
  ClientTCPHeader	*_header;

public:
  void			setRawData(char *);
  bool			checkHeader();
  char*			deserialize();
};

#endif
