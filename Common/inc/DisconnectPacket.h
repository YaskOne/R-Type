#ifndef DISCONNECTPACKET_H_
# define  DISCONNECTACKET_H_

# include "AClientPacket.hh"

class DisconnectPacket : public AClientPacket<ClientUDPCommand>
{
 public:
  DisconnectPacket(ClientUDPCommand, int);
  DisconnectPacket(ClientUDPHeader*);
  ~DisconnectPacket();

  char*				deserialize();
  bool				checkHeader();
  void				setRawData(char *);

 private:
  ClientUDPHeader*		_header;
};

#endif
