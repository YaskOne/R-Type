#ifndef ACLIENTPACKET_H_
# define ACLIENTPACKET_H_

# include "IClientPacket.hh"

template <typename T>
class AClientPacket : public IClientPacket<T>
{
public:
  AClientPacket(T, size_t);
  virtual ~AClientPacket();

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

# include "AClientPacket.tpp"

#endif
