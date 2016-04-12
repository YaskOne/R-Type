#pragma once

#include "GraphicalItem.h"
#include "ViewController.hh"
#include "AssetsController.hh"

class           Explosion : public GraphicalItem
{
    public:
    Explosion(sf::Vector2f const& pos);
    ~Explosion();
    public:
    bool            update(sf::Clock const&);

    private:
    sf::Vector2f    _pos;
    sf::Time        _referential;
    sf::Time        _lastUpdate;
    int             _stage;
};
