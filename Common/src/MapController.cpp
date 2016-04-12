#include <iostream>
#include <algorithm>
#include "MapController.hh"
#include "ObjectInfo.hpp"
#include "Alien.hh"
#include "Player.hh"

unsigned int _maxId;

MapController::MapController()
  : _deserializedMap(new std::vector<IServerPacket<ServerUDPResponse>*>)
{
    _alienCount = 0;
}

MapController::~MapController()
{
  delete _deserializedMap;
}

void			MapController::generatePacketsMap(IObject* player)
{
  for (std::vector<IObject*>::iterator it = _map.begin(); it != _map.end(); ++it)
    {
      if (*it == player)
	continue ;
      switch ((*it)->getObjType())
	{
	case ObjectInfo::PLAYER :
	  _deserializedMap->push_back(new CrePlayPacket(CRE_PLAY, 0, (*it)->getId(), (*it)->getPos().x + (*it)->getSize().x, (*it)->getPos().y));
	  break ;
	case ObjectInfo::SHOT :
	  if (static_cast<Projectile*>(*it)->getRealType() == ObjectInfo::PLAYERREGULAR)
	    {
	      _deserializedMap->push_back(new CreObjPacket(CRE_OBJ, 0, (*it)->getId(), (*it)->getPos().x, (*it)->getPos().y, (*it)->getSpeed().x, (*it)->getSpeed().y, ObjectInfo::PLAYERREGULAR));
	    }
	  else
	    {
	      _deserializedMap->push_back(new CreObjPacket(CRE_OBJ, 0, (*it)->getId(), (*it)->getPos().x, (*it)->getPos().y, (*it)->getSpeed().x, (*it)->getSpeed().y, ObjectInfo::ALIENREGULAR));
	    }
	  break ;
	case ObjectInfo::BYDO || ObjectInfo::GLAM || ObjectInfo::DOKAN || ObjectInfo::KAYBEROS || ObjectInfo::RIOS || ObjectInfo::SCANT || ObjectInfo::SHELL || ObjectInfo::YORK || ObjectInfo::XELF16 :
	  _deserializedMap->push_back(new CreIAPacket(CRE_IA, 0, (*it)->getId(), (*it)->getPos().x, (*it)->getPos().y, (*it)->getSpeed().x, static_cast<Alien*>((*it))->getCoeff(), static_cast<Alien*>((*it))->getRealType()));
	  break ;
	default :
	  break ;
	}
    }
}

std::vector<IServerPacket<ServerUDPResponse>*>*	MapController::getMap() const
{
  return _deserializedMap;
}

void		MapController::addObject(IObject* obj)
{
  _map.push_back(obj);
}

void		MapController::addAlien(IObject* obj)
{
    if (static_cast<Alien*>(obj)->getRealType() != ObjectInfo::OBSTACLE)
    {
        if (_alienCount == -1)
            _alienCount = 1;
        else
            _alienCount += 1;
    }
  _map.push_back(obj);
}

void		MapController::resetClockPlayer()
{
  for (auto it = _map.begin(); it != _map.end(); ++it)
    if ((*it)->getObjType() == ObjectInfo::PLAYER)
      static_cast<Player*>(*it)->resetLoopTime();
}

void		MapController::updateMap(sf::Clock const& clock)
{
  auto it = _map.begin();

  _toAppend.clear();
  _deserializedMap->clear();
  while (it != _map.end())
    {
      (*it)->update(clock, _map);
      ++it;
    }
  it = _map.begin();
  while (it != _map.end())
    {
      checkNewObj(it, (*it));
      if (it == _map.end())
	break;
      ++it;
    }
  _map.insert(std::end(_map), std::begin(_toAppend), std::end(_toAppend));
}

void		MapController::checkNewObj(std::vector<IObject*>::iterator& it, IObject* obj)
{
  if (obj->isShooting())
    {
      obj->setShooting(false);
      if (obj->getObjType() == ObjectInfo::PLAYER)
  	{
	  std::vector<IObject*> *shots = static_cast<Player*>(obj)->MultiShoot();
	  IObject* shot;
	  while (!shots->empty())
	    {
	      shot = shots->back();
	      shots->pop_back();
	      _toAppend.push_back(shot);
	      _deserializedMap->push_back(new CreObjPacket(CRE_OBJ, 0, _maxId - 1, shot->getPos().x, shot->getPos().y, shot->getSpeed().x, shot->getSpeed().y, ObjectInfo::PLAYERREGULAR));
	    }
	  delete shots;
  	}
      if (obj->getObjType() == ObjectInfo::ALIEN)
  	{
	  IObject* shot = static_cast<Alien*>(obj)->BasicShoot();
  	  _toAppend.push_back(shot);
  	  _deserializedMap->push_back(new CreObjPacket(CRE_OBJ, 0, _maxId - 1, shot->getPos().x, shot->getPos().y, shot->getSpeed().x, shot->getSpeed().y, ObjectInfo::ALIENREGULAR));
  	}
    }
  if (!obj->isAlive())
    {
        if (obj->getObjType() == ObjectInfo::ALIEN
            && static_cast<Alien*>(obj)->getRealType() != ObjectInfo::OBSTACLE)
                _alienCount -= 1;
      _deserializedMap->push_back(new DelItemPacket(DEL_ITEM, 0, obj->getId()));
      this->deletePlayer(obj->getId());
    }
}

void		MapController::updatePlayer(IObject* player, sf::Clock const& clock)
{
  player->update(clock, _map);
}

IObject*	MapController::getPlayer(int id)
{
  if (id == -1)
    return NULL;
  for (std::vector<IObject*>::iterator it = _map.begin(); it != _map.end(); ++it)
    {
      if ((*it)->getId() == id)
	return (*it);
    }
  return NULL;
}

void		MapController::deletePlayer(int id)
{
  IObject*	player = this->getPlayer(id);

  if (player == NULL)
    return ;
  _map.erase(std::find(_map.begin(), _map.end(), player));
  delete (player);
}

int       MapController::getAlienCount() const
{
    return _alienCount;
}
