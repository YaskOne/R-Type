#ifndef _DOKAN_ALIEN_HH_
# define _DOKAN_ALIEN_HH_

# include "Alien.hh"

class DokanAlien : public Alien
{
public:
  DokanAlien(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff);
  ~DokanAlien();

public:
  bool				update(sf::Clock const&, std::vector<IObject*>&);
  bool				update(sf::Clock const&);
  IObject			*BasicShoot();
};

# endif
