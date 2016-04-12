#ifndef FIREPACKET_H_
# define FIREPACKET_H_

# include "AClientPacket.hh"

class FirePacket : public AClientPacket<ClientUDPCommand>
{
 public:
  FirePacket(ClientUDPCommand, int, float, float);
  FirePacket(ClientUDPHeader*);
  ~FirePacket();

  char*				deserialize();
  bool				checkHeader();
  void				setRawData(char *);
  FireData*			getData() const;

 private:
  FireData*			_data;
  ClientUDPHeader*		_header;
};

#endif
