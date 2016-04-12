#ifndef _SHELL_ALIEN_HH_
# define _SHELL_ALIEN_HH_

# include "Alien.hh"

class ShellAlien : public Alien
{
public:
  ShellAlien(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff);
  ~ShellAlien();

public:
  bool		update(sf::Clock const&, std::vector<IObject*>&);
  bool		update(sf::Clock const&);
  IObject	*BasicShoot();
};

# endif
