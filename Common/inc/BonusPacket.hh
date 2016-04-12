#ifndef BONUSPACKET_H_
# define BONUSPACKET_H_

# include "AServerPacket.hh"

class BonusPacket : public AServerPacket<ServerUDPResponse>
{
 public:
  BonusPacket(ServerUDPResponse, ObjectInfo::WaveType, int, int, float, float, float);
  BonusPacket(ServerUDPHeader*);
  ~BonusPacket();

  char*				deserialize();
  bool				checkHeader();
  void				setRawData(char *);
  BonusData*			getData() const;

 private:
  BonusData*			_data;
  ServerUDPHeader*		_header;
};

#endif /* !BONUSPACKET_H_ */
