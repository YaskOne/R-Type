template <typename T>
AServerPacket<T>::AServerPacket(T cmd, size_t size) : _command(cmd), _size(size)
{

}

template <typename T>
AServerPacket<T>::~AServerPacket()
{

}

template <typename T>
T		AServerPacket<T>::getCommandType() const
{
  return _command;
}

template <typename T>
size_t		AServerPacket<T>::getPacketSize() const
{
  return _size;
}

template class AServerPacket<ServerTCPResponse>;
template class AServerPacket<ServerUDPResponse>;
