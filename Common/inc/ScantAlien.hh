#ifndef _SCANT_ALIEN_HH_
# define _SCANT_ALIEN_HH_

# include "Alien.hh"

class ScantAlien : public Alien
{
public:
  ScantAlien(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff);
  ~ScantAlien();

public:
  bool		update(sf::Clock const&, std::vector<IObject*>&);
  bool		update(sf::Clock const&);
  IObject	*BasicShoot();
};

# endif
