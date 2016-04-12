#include "ScantAlien.hh"
#include "BasicAlienProjectile.hh"
#include <stdlib.h>

extern unsigned int _maxId;

ScantAlien::ScantAlien(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff)
  : Alien(speed, pos, sf::Vector2i(100, 100), id, coeff)
{
  _life = 3;
  _realType = ObjectInfo::SCANT;
  _f = 0.04;
  _rad = 3;
  _a = 3;
}

ScantAlien::~ScantAlien()
{
}

bool		ScantAlien::update(sf::Clock const& clock)
{
  if (_pos.x + _size.x < 0 || _pos.x > MAP_SIZE_X
      || _pos.y + _size.y < 0 || _pos.y > MAP_SIZE_Y)
    _isAlive = false;
  // if (this->_pos.x > 1700)
  //   {
      // this->_pos.x = this->_pos.x - this->_speed.x;
      // this->_pos.y = _pos.y - (_a * cos(_f * this->_pos.x * M_PI + M_PI));
    // }
  // else
  //   {
  upPattern();
  _pos.x -= cos(_patternPos * _f * _speed.x);
  _pos.y +=  sin(_patternPos * _f * _speed.x);
    // }
  if (static_cast<int>(_pos.x + _pauseShoot) % 320 == 0)
    _isShoot = true;
  return true;
}

bool		ScantAlien::update(sf::Clock const& clock, std::vector<IObject*> &map)
{
  this->update(clock);
  this->collision(map);
  return (_isAlive);
}

IObject		*ScantAlien::BasicShoot()
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
