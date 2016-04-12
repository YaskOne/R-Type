#pragma once
#include "ViewController.hh"
#include "AssetsController.hh"
#include "IObject.hh"

//extern ViewController *vc;
extern AssetsController *ac;

class GraphicalItem
{
public:
	GraphicalItem();
	sf::Drawable*		getDrawable();
	virtual bool	        update(sf::Clock const&) = 0;

protected:
    bool                _msg;
	sf::Sprite			*_sprite;
    sf::Text            *_messageDrawable;
};
