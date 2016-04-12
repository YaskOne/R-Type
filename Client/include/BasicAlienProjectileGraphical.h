#pragma once

#include "BasicAlienProjectile.hh"
#include "GraphicalItem.h"

class BasicAlienProjectileGrapical : public BasicAlienProjectile, public GraphicalItem
{
public:
	BasicAlienProjectileGrapical(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int);
	bool			update(sf::Clock const&);
	bool			update(std::vector<IObject*>&, sf::Clock const&) {};
};
