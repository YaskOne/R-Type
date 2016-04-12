#pragma once
# include "DokanAlien.hh"
# include "GraphicalItem.h"

class DokanAlienGraphical : public DokanAlien, public GraphicalItem
{
public:
  DokanAlienGraphical(sf::Vector2f speed, sf::Vector2f pos, unsigned int, float coeff);

public:
	bool				update(sf::Clock const&);
  bool				update(std::vector<IObject*>&, sf::Clock const&);
};
