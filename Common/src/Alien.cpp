#include "Alien.hh"
#include <iostream>
#include <ctime>

extern unsigned int _maxId;

Alien::Alien(sf::Vector2f const& speed, sf::Vector2f const& pos, sf::Vector2i const& size, unsigned int id, float coeff)
  : Object(speed, pos, size, ObjectInfo::Type::ALIEN, id), _coeff(coeff), _patternPos(0)
{
  _pauseShoot = std::rand() % 320;
  _pauseShoot -= _pauseShoot % static_cast<int>(_speed.x);
}

Alien::~Alien() {}

Alien::Alien(const Alien &obj)
  : Object(obj._speed, obj._pos, obj._size, obj._objType, obj._id)
{
  if (this != &obj)
    {
      this->_life = obj._life;
      this->_isAlive = obj._isAlive;
      this->_isShoot = obj._isShoot;
      this->_objType = obj._objType;
      this->_coeff = obj._coeff;
      this->_f = obj._f;
      this->_a = obj._a;
      this->_rad = obj._rad;
      this->_realType = obj._realType;
    }
}

const float		&Alien::getCoeff() const
{
  return _coeff;
}

const ObjectInfo::WaveType	&Alien::getRealType() const
{
  return _realType;
}

void			Alien::upPattern()
{
  ++_patternPos;
}
