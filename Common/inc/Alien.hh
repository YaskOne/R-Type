#ifndef _ALIEN_HH_
# define _ALIEN_HH_

# define _USE_MATH_DEFINES
# include <cmath>
# include "BasicAlienProjectile.hh"
# include "Object.hh"

class Alien : public Object
{
public:
  Alien(sf::Vector2f const&, sf::Vector2f const&, sf::Vector2i const&, unsigned int, float);
  Alien(const Alien &);
  ~Alien();

public:
  virtual bool		        update(sf::Clock const&, std::vector<IObject*>&) = 0;
  virtual bool		        update(sf::Clock const&) = 0;
  const float&			getCoeff() const;
  virtual IObject		*BasicShoot() = 0;
  const ObjectInfo::WaveType	&getRealType() const;
  void				upPattern();

protected:
  float			_coeff;
  int			_f;
  int			_a;
  float			_rad;
  ObjectInfo::WaveType	_realType;
  unsigned int		_patternPos;
  unsigned int		_pauseShoot;
};

# endif
