#ifndef SENDMOVEPACKET_H_
# define SENDMOVEPACKET_H_

# include "AClientPacket.hh"

class SendMovePacket : public AClientPacket<ClientUDPCommand>
{
 public:
  SendMovePacket(ClientUDPCommand, int, Direction);
  SendMovePacket(ClientUDPHeader*);
  ~SendMovePacket();

  char*				deserialize();
  bool				checkHeader();
  void				setRawData(char *);
  SendMoveData*			getData() const;

 private:
  SendMoveData*			_data;
  ClientUDPHeader*		_header;
};

#endif
