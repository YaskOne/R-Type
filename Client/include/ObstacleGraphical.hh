#pragma once
# include "Obstacle.hh"
# include "GraphicalItem.h"

class ObstacleGraphical : public Obstacle, public GraphicalItem
{
public:
  ObstacleGraphical(sf::Vector2f speed, sf::Vector2f pos, unsigned int, float coeff);

public:
	bool				update(sf::Clock const&);
  bool				update(std::vector<IObject*>&, sf::Clock const&);
};
