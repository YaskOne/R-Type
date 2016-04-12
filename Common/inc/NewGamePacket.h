#ifndef NEWGAMEPACKET_H_
# define NEWGAMEPACKET_H_

# include "AClientPacket.hh"

class NewGamePacket : public AClientPacket<ClientTCPCommand>
{
public:
  NewGamePacket(ClientTCPCommand, std::string const&);
  NewGamePacket(ClientTCPHeader*);
  ~NewGamePacket();

private:
  NewGameData*		_data;
  ClientTCPHeader*	_header;

public:
  void			setRawData(char *);
  NewGameData*		getData() const;
  bool			checkHeader();
  char*			deserialize();
};

#endif
