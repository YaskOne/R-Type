#pragma once
# include "ShellAlien.hh"
# include "GraphicalItem.h"

class ShellAlienGraphical : public ShellAlien, public GraphicalItem
{
public:
  ShellAlienGraphical(sf::Vector2f speed, sf::Vector2f pos, unsigned int, float coeff);

public:
	bool				update(sf::Clock const&);
  bool				update(std::vector<IObject*>&, sf::Clock const&);
};
