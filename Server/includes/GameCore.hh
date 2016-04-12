#ifndef GAMECORE_H_
# define GAMECORE_H_

# include <vector>
# include "Player.hh"
# include "Alien.hh"
# include "GamerInfo.hh"
# include "FactoryManager.hh"
# include "MapController.hh"
# include "UMutex.h"
# include "ABonus.hh"

class GameCore
{
public :
  GameCore(std::string const&, std::string const&, CUMutex*, bool*);
  virtual ~GameCore();
  void				run();

private :
  GameCore(const GameCore &);
  GameCore &operator=(const GameCore &);
  void				receivePacket();
  void				processPacket(GamerInfo*, IClientPacket<ClientUDPCommand>*);
  void				authGamer(GamerInfo* client, IClientPacket<ClientUDPCommand>*);
  void				gamerTryShoot(GamerInfo* client, IClientPacket<ClientUDPCommand>* packet);
  void				sendMap(GamerInfo *client, std::vector<IServerPacket<ServerUDPResponse>*> *toSendMap);
  void				gamerMove(GamerInfo* client, IClientPacket<ClientUDPCommand>* packet);
  void				gamerDisconnect(GamerInfo* client, IClientPacket<ClientUDPCommand>* packet);
  sf::Time			getElapsedTimeSinceLoop();
  std::vector<IServerPacket<ServerUDPResponse>*>*	generatePackets(std::vector<IObject*>* aliens);
  void				updateMap();
  void				setAlive(GamerInfo*, IClientPacket<ClientUDPCommand>*);
  void				updateAliveClients(sf::Time const&);

private :
  std::vector<GamerInfo*>*	_clients;
  UDPNetworkHandler*		_network;
  MapController*		_map;
  FactoryManager*		_factory;
  sf::Clock			_clock;
  sf::Clock			_clockAlive;
  sf::Time			_referential;
  bool				_running;
  bool				_firstClient;
  int				_currentLevel;
  CUMutex*			_mutex;
  bool*				_end;
};

#endif /* !GAMECORE_H_ */
