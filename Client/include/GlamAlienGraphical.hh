#pragma once
# include "GlamAlien.hh"
# include "GraphicalItem.h"

class GlamAlienGraphical : public GlamAlien, public GraphicalItem
{
public:
  GlamAlienGraphical(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int, float coeff);

public:
	bool				update(sf::Clock const&);
  bool				update(std::vector<IObject*>&, sf::Clock const&);
};
