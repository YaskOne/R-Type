#ifndef DESGAMEPACKET_H_
# define DESGAMEPACKET_H_

# include <string.h>
# include "AServerPacket.hh"

class DesGamePacket : public AServerPacket<ServerTCPResponse>
{
 public:
  DesGamePacket(ServerTCPResponse, int, std::string const&, std::string const&);
  DesGamePacket(ServerTCPHeader*);
  ~DesGamePacket();

  char*				deserialize();
  bool				checkHeader();
  void				setRawData(char *);
  DesGameData*			getData() const;

 private:
  DesGameData*			_data;
  ServerTCPHeader*		_header;
};

#endif /* !DESGAMEPACKET_H_ */
