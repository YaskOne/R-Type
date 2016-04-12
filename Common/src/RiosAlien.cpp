#include "RiosAlien.hh"
#include "BasicAlienProjectile.hh"
#include <stdlib.h>

extern unsigned int _maxId;

RiosAlien::RiosAlien(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff)
  : Alien(speed, pos, sf::Vector2i(100, 100), id, coeff)
{
  _realType = ObjectInfo::RIOS;
  _f = 0.04;
  _rad = 6;
  _a = 1;
}

RiosAlien::~RiosAlien()
{}

bool	        RiosAlien::update(sf::Clock const& clock)
{
  if (_pos.x + _size.x < 0 || _pos.x > MAP_SIZE_X
      || _pos.y + _size.y < 0 || _pos.y > MAP_SIZE_Y)
    _isAlive = false;
  if ((static_cast<int>(_pos.x) % 200) == 0)
    {
      _pos.y = _pos.y - _speed.y;
      if ((static_cast<int>(_pos.y) % 200) == 0)
	_isShoot = true;
    }
  if ((static_cast<int>(_pos.y) % 200) == 0)
    _pos.x = _pos.x - _speed.x;
  return true;
}


bool	        RiosAlien::update(sf::Clock const& clock, std::vector<IObject*>& map)
{
  this->update(clock);
  this->collision(map);
  return (_isAlive);
}

IObject		*RiosAlien::BasicShoot()
{
  sf::Vector2f pos;
  sf::Vector2f speed;

  pos.x = _pos.x;
  pos.y = _pos.y + (_size.y / 2);
  _isShoot = false;
  speed.x = _speed.y + (_speed.y / 3);
  speed.y = speed.x;
  return new BasicAlienProjectile(speed, pos, _maxId++);
}
