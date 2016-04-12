#ifndef MAP_CONTROLLER_HH_
# define MAP_CONTROLLER_HH_

# include <vector>
# include "IObject.hh"
# include "ObjectInfo.hpp"
# include "UDPNetworkHandler.hh"
# include "GamerInfo.hh"
# include "IServerPacket.hh"
# include <SFML/System/Clock.hpp>

# define MAP_SIZE_X 1920
# define MAP_SIZE_Y 1080

class	MapController
{
public:
  MapController();
  ~MapController();


  void		addObject(IObject*);
  void		addAlien(IObject*);
  void		updateMap(sf::Clock const&);
  std::vector<IServerPacket<ServerUDPResponse>*>*     getMap() const;
  void		updatePlayer(IObject*, sf::Clock const&);
  IObject*	getPlayer(int id);
  void		resetClockPlayer();
  void		deletePlayer(int id);
  void		generatePacketsMap(IObject *);
  void		checkNewObj(std::vector<IObject*>::iterator& it, IObject* obj);
  int       getAlienCount() const;

private:
  std::vector<IObject*>					_map;
  std::vector<IServerPacket<ServerUDPResponse>*>	*_deserializedMap;
  std::vector<IObject*>					_toAppend;
  int                          _alienCount;
  int				_fact;
};

#endif
