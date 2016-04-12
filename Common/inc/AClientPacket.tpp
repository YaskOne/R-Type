template <typename T>
AClientPacket<T>::AClientPacket(T cmd, size_t size)
  : _command(cmd), _size(size)
{
}

template <typename T>
AClientPacket<T>::~AClientPacket()
{
}

template <typename T>
T		AClientPacket<T>::getCommandType() const
{
  return _command;
}

template <typename T>
size_t	AClientPacket<T>::getPacketSize() const
{
  return _size;
}

template class	AClientPacket<ClientTCPCommand>;
template class	AClientPacket<ClientUDPCommand>;
