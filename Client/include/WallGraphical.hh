#include "AssetsController.hh"
#include "ViewController.hh"
#include "GraphicalItem.h"
#include "Obstacle.hh"

class                   WallGraphical : public Obstacle, public GraphicalItem
{
    public:
    
    WallGraphical(sf::Vector2f speed, sf::Vector2f pos, unsigned int id, float coeff);
    ~WallGraphical();
    
    public:
	bool				update(sf::Clock const&);
    bool				update(std::vector<IObject*>&, sf::Clock const&);

};