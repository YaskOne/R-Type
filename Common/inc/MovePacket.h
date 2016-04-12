#ifndef MOVEPACKET_H_
# define MOVEPACKET_H_

# include "AServerPacket.hh"

class MovePacket : public AServerPacket<ServerUDPResponse>
{
 public:
  MovePacket(ServerUDPResponse, int, int, float, float, uint32_t);
  MovePacket(ServerUDPHeader*);
  ~MovePacket();

  char*				deserialize();
  bool				checkHeader();
  void				setRawData(char *);
  MoveData*			getData() const;

 private:
  MoveData*			_data;
  ServerUDPHeader*		_header;
};


#endif /* !MOVEPACKET_H_ */
