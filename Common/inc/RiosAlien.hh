#ifndef _RIOS_ALIEN_HH_
# define _RIOS_ALIEN_HH_

# include "Alien.hh"

class RiosAlien : public Alien
{
public:
  RiosAlien(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff);
  ~RiosAlien();

public:
  bool		update(sf::Clock const&, std::vector<IObject*>&);
  bool		update(sf::Clock const&);
  IObject	*BasicShoot();
};

# endif
