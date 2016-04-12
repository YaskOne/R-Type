#ifndef BASICPLAYERPROJECTILEGRAPHICAL_H_
# define BASICPLAYERPROJECTILEGRAPHICAL_H_

# include "BasicPlayerProjectile.hh"
# include "GraphicalItem.h"

class BasicPlayerProjectileGrapical : public BasicPlayerProjectile, public GraphicalItem
{
public:
  BasicPlayerProjectileGrapical(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id, uint32_t* score);
	bool			update(sf::Clock const&);
	bool			update(std::vector<IObject*>&, sf::Clock const&) {};

private:
	sf::Sound    _sound;
};

#endif /* !BASICPLAYERPROJECTILEGRAPHICAL_H_ */
