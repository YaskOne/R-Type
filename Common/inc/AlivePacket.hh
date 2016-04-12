#ifndef ALIVEPACKET_H_
# define ALIVEPACKET_H_

# include "AClientPacket.hh"
# include "NetworkDefines.h"

class	AlivePacket : public AClientPacket<ClientUDPCommand>
{
public :
  AlivePacket(ClientUDPCommand, int, bool);
  AlivePacket(ClientUDPHeader*);
  ~AlivePacket();

  char*			deserialize();
  bool			checkHeader();
  void			setRawData(char *);
  AliveData*		getData() const;

private :
  AliveData*		_data;
  ClientUDPHeader*	_header;
};

#endif /* !ALIVEPACKET_H_ */
