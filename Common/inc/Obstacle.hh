#ifndef _OBSTACLE_HH_
# define _OBSTACLE_HH_

# include "Alien.hh"

class Obstacle : public Alien
{
public:
  Obstacle(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, float coeff);
  ~Obstacle();

public:
  bool				update(sf::Clock const&, std::vector<IObject*>&);
  bool				update(sf::Clock const&);
  IObject			*BasicShoot();
};

# endif
