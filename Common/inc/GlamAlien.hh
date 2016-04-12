#ifndef _GLAM_ALIEN_HH_
# define _GLAM_ALIEN_HH_

# include "Alien.hh"

class GlamAlien : public Alien
{
public:
  GlamAlien(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff);
  ~GlamAlien();

public:
  bool		update(sf::Clock const&, std::vector<IObject*>&);
  bool		update(sf::Clock const&);
  IObject	*BasicShoot();
};

# endif
