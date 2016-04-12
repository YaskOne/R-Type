#include "Waves.hh"
#include <iostream>

Waves::Waves(int count, sf::Time const& time, sf::Time const& freq, sf::Vector2f const& pos, sf::Vector2f const& speed, float coeff, ObjectInfo::WaveType type)
  : _count(count), _time(time), _frequency(freq), _pos(pos), _speed(speed), _coeff(coeff), _type(type)
{
}

Waves::~Waves() {}

Waves::Waves() {}

Waves		&Waves::operator=(const Waves& wave)
{
  if (this != &wave)
    {
      _count = wave._count;
      _time = wave._time;
      _pos = wave._pos;
      _frequency = wave._frequency;
      _speed = wave._speed;
      _coeff = wave._coeff;
      _type = wave._type;
    }
  return (*this);
}

void		Waves::pop()
{
  _time = _time + _frequency;
  _count = _count - 1;
}

const int			&Waves::getCount() const
{
  return _count;
}

const sf::Time			&Waves::getFreq() const
{
  return _frequency;
}

const sf::Time			&Waves::getTime() const
{
  return _time;
}

const sf::Vector2f		&Waves::getPos() const
{
  return _pos;
}

const float			&Waves::getCoeff() const
{
  return _coeff;
}

const sf::Vector2f		&Waves::getSpeed() const
{
  return _speed;
}

const ObjectInfo::WaveType	&Waves::getType() const
{
  return _type;
}
