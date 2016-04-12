#ifndef _BYDO_ALIEN_HH_
# define _BYDO_ALIEN_HH_

# include "Alien.hh"

class BydoAlien : public Alien
{
public:
  BydoAlien(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff);
  ~BydoAlien();

public:
  bool				update(sf::Clock const&, std::vector<IObject*>&);
  bool				update(sf::Clock const&);
  IObject			*BasicShoot();
};

# endif
