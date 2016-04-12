#ifndef NICKPACKET_H_
# define NICKPACKET_H_

# include "AClientPacket.hh"

class NickPacket : public AClientPacket<ClientTCPCommand>
{
public:
  NickPacket(ClientTCPCommand, std::string const&);
  NickPacket(ClientTCPHeader*);
  ~NickPacket();

private:
  ClientTCPHeader	*_header;
  NickData*		_data;

public:
  void			setRawData(char *);
  NickData*		getData() const;
  bool			checkHeader();
  char*			deserialize();
};

#endif
