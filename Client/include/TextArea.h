#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "ViewController.hh"
#include "AssetsController.hh"

extern ViewController *vc;

class TextArea
{
public:
	TextArea(Font const& font, sf::Vector2f const& pos, sf::Vector2f const& size, std::string const& defaultText);
	void			update(keyboardStatus status);
	sf::Drawable*	getTextArea();
	std::string	getText();
	sf::Text*		getDrawableText();
	bool			cursorOnIt(sf::Vector2i const&);

private:
	sf::Font		*_font;
	std::string		_text;
	std::string		_defaultText;
	sf::RectangleShape		*_textArea;
	sf::Text		*_drawableText;
	sf::Vector2f	_pos;
	sf::Vector2f	_size;
};
