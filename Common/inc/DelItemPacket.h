#ifndef DELITEMPACKET_H_
# define DELITEMPACKET_H_

# include "AServerPacket.hh"

class DelItemPacket : public AServerPacket<ServerUDPResponse>
{
 public:
  DelItemPacket(ServerUDPResponse, int, int);
  DelItemPacket(ServerUDPHeader*);
  ~DelItemPacket();

  char*				deserialize();
  bool				checkHeader();
  void				setRawData(char *);
  DelItemData*			getData() const;

 private:
  DelItemData*			_data;
  ServerUDPHeader*		_header;
};


#endif /* !DELIAPACKET_H_ */
