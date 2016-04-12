#ifndef _BASIC_ALIEN_PROJECTILE_HH_
# define _BASIC_ALIEN_PROJECTILE_HH_

# include "Projectile.hh"

class BasicAlienProjectile : public Projectile
{
public:
  BasicAlienProjectile(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id);
  ~BasicAlienProjectile();

public:
  bool				update(sf::Clock const&, std::vector<IObject*>&);
  bool				update(sf::Clock const&);
};

# endif
