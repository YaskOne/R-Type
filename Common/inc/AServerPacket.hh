#ifndef ASERVERPACKET_H_
# define ASERVERPACKET_H_

# include "IServerPacket.hh"

template <typename T>
class AServerPacket : public IServerPacket<T>
{
public:
  AServerPacket(T, size_t);
  virtual ~AServerPacket();

protected:
  T				_command;
  size_t			_size;

public:
  T				getCommandType() const;
  size_t			getPacketSize() const;
  virtual char*			deserialize() = 0;
  virtual bool			checkHeader() = 0;
  virtual void			setRawData(char *) = 0;
};

# include "AServerPacket.tpp"

#endif /* !ASERVERPACKET_H_ */
