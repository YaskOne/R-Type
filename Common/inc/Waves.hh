#ifndef _WAVES_HH_
# define _WAVES_HH_

# include <SFML/System/Vector2.hpp>
# include <SFML/System/Time.hpp>
# include "ObjectInfo.hpp"

class	Waves
{
public:
  Waves(int, sf::Time const&, sf::Time const&, sf::Vector2f const&, sf::Vector2f const&, float, ObjectInfo::WaveType);
  Waves();
  ~Waves();

public:
  Waves				      &operator=(const Waves&);
  const int			      &getCount() const;
  const sf::Time		      &getTime() const;
  const sf::Time		      &getFreq() const;
  const sf::Vector2f		      &getPos() const;
  const sf::Vector2f		      &getSpeed() const;
  const float			      &getCoeff() const;
  const ObjectInfo::WaveType	      &getType() const;
  void				      setCount(int);
  void				      pop();

private:
  int			_count;
  sf::Time		_time;
  sf::Time		_frequency;
  sf::Vector2f		_pos;
  sf::Vector2f		_speed;
  float			_coeff;
  ObjectInfo::WaveType	_type;
};

#endif
