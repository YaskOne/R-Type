#ifndef CREIAPACKET_H_
# define CREIAPACKET_H_

# include "AServerPacket.hh"

class CreIAPacket : public AServerPacket<ServerUDPResponse>
{
 public:
  CreIAPacket(ServerUDPResponse, int, int, float, float, float, float, ObjectInfo::WaveType);
  CreIAPacket(ServerUDPHeader*);
  ~CreIAPacket();

  char*				deserialize();
  bool				checkHeader();
  void				setRawData(char *);
  CreIAData*			getData() const;

 private:
  CreIAData*			_data;
  ServerUDPHeader*		_header;
};


#endif /* !CREIAPACKET_H_ */
