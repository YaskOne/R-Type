#ifndef AUTHUDPPACKET_H_
# define AUTHUDPPACKET_H_

# include "AServerPacket.hh"

class AuthUDPPacket : public AServerPacket<ServerUDPResponse>
{
 public:
  AuthUDPPacket(ServerUDPResponse, int, Bool, float);
  AuthUDPPacket(ServerUDPHeader*);
  ~AuthUDPPacket();

  char*				deserialize();
  bool				checkHeader();
  void				setRawData(char *);
  AuthUDPData*		getData() const;

 private:
  AuthUDPData*			_data;
  ServerUDPHeader*		_header;
};

#endif
