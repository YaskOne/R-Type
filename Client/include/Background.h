#pragma once

#include "ViewController.hh"
#include "AssetsController.hh"

extern ViewController *vc;
extern AssetsController *ac;

class Backgroud
{
public:
	Backgroud();

public:
	void			update();
	sf::Drawable*	getDrawable();

private:
	sf::Sprite*		_background;
	sf::Vector2f	_scale;
	sf::Vector2f	_position;
	bool			_zoom;

};