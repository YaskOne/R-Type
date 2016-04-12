#pragma once

#include <ViewController.hh>


class    MenuButton
{
public:
	MenuButton(std::string const&, sf::Vector2f const&, sf::Vector2f const&, Font const&);
	sf::Drawable*		getBackground();
	sf::Drawable*		getDrawableText();
	sf::Vector2f		getPosition();
	void				update(sf::Vector2i const&);
	bool				cursorOnIt(sf::Vector2i const&);

public:
	bool				getIsHigh();

protected:
	std::string			_text;
	sf::Text*			_drawableText;
	sf::RectangleShape*	_background;
	bool				_isHigh;
	sf::Vector2f		_position;
	sf::Vector2f		_size;
	sf::Font*			_font;
};
