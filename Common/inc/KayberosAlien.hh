#ifndef _KAYBEROS_ALIEN_HH_
# define _KAYBEROS_ALIEN_HH_

# include "Alien.hh"

class KayberosAlien : public Alien
{
public:
  KayberosAlien(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff);
  ~KayberosAlien();

public:
  bool		update(sf::Clock const&, std::vector<IObject*>&);
  bool		update(sf::Clock const&);
  IObject	*BasicShoot();
};

# endif
