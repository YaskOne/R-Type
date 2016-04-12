#pragma once
# include "KayberosAlien.hh"
# include "GraphicalItem.h"

class KayberosAlienGraphical : public KayberosAlien, public GraphicalItem
{
public:
  KayberosAlienGraphical(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int, float coeff);

public:
	bool				update(sf::Clock const&);
  bool				update(std::vector<IObject*>&, sf::Clock const&);
};
