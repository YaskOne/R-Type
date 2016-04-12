#ifndef NEXTLVLPACKET_H_
# define NEXTLVLPACKET_H_

# include "AServerPacket.hh"

class NextLvlPacket : public AServerPacket<ServerUDPResponse>
{
 public:
  NextLvlPacket(ServerUDPResponse, int, int);
  NextLvlPacket(ServerUDPHeader*);
  ~NextLvlPacket();

  char*				deserialize();
  bool				checkHeader();
  void				setRawData(char *);
  NextLvlData*			getData() const;

 private:
  ServerUDPHeader*		_header;
  NextLvlData*			_data;
};

#endif /* !NEXTLVLPACKET_H_ */
