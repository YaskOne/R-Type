#ifndef CAUTCHUDPPACKET_H_
# define CAUTCHUDPPACKET_H_

# include "AClientPacket.hh"

class CAuthUDPPacket : public AClientPacket<ClientUDPCommand>
{
 public:
  CAuthUDPPacket(ClientUDPCommand, int, std::string const&);
  CAuthUDPPacket(ClientUDPHeader*);
  ~CAuthUDPPacket();

  char*				deserialize();
  bool				checkHeader();
  void				setRawData(char *);
  CAuthUDPData*			getData() const;

 private:
  CAuthUDPData*			_data;
  ClientUDPHeader*		_header;
};

#endif
