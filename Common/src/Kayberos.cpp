#include "KayberosAlien.hh"
#include "BasicAlienProjectile.hh"
#include <stdlib.h>

extern unsigned int _maxId;

KayberosAlien::KayberosAlien(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff)
  : Alien(speed, pos, sf::Vector2i(100, 100), id, coeff)
{
  _realType = ObjectInfo::KAYBEROS;
  _f = 2;
  _life = 3;
  _rad = 4;
  _a = 6;
}

KayberosAlien::~KayberosAlien()
{}

bool		KayberosAlien::update(sf::Clock const& clock)
{
  upPattern();
  if (_pos.x + _size.x < 0 || _pos.x > MAP_SIZE_X
      || _pos.y + _size.y < 0 || _pos.y > MAP_SIZE_Y)
    _isAlive = false;

  int pPos = _patternPos % 300;
  if (pPos < 50)
    _pos.x -= _speed.x;
  else if (pPos < 150)
    _pos.y -= _speed.x;
  else if (pPos < 200)
    _pos.x -= _speed.x;
  else
    _pos.y += _speed.x;
  // this->_pos.y = _pos.y - (_a * cos((0.23 * _f * (this->_pos.x / 150) * M_PI) + _rad * _coeff));
  if (((pPos >= 50 && pPos < 150) || (pPos >= 200)) && static_cast<int>(_patternPos + _pauseShoot) % 50 == 0)
    _isShoot = true;
  return true;
}


bool		KayberosAlien::update(sf::Clock const& clock, std::vector<IObject*>& map)
{
  this->update(clock);
  this->collision(map);
  return (_isAlive);
}

IObject		*KayberosAlien::BasicShoot()
{
  sf::Vector2f pos;

  pos.x = _pos.x + _speed.x;
  pos.y = _pos.y;
  _isShoot = false;
  return new BasicAlienProjectile(_speed, pos, _maxId++);
}
