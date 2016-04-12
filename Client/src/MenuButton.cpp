#include "MenuButton.h"

MenuButton::MenuButton(std::string const& text, sf::Vector2f const& pos, sf::Vector2f const& size, Font const& font) :
_text(text), _position(pos), _size(size)
{
	_font = ac->getFont(font);
	_background = new sf::RectangleShape(_size);
	_background->setPosition(_position);
	_background->setFillColor(sf::Color(76, 157, 172));

	_drawableText = new sf::Text;
	_drawableText->setFont(*_font);
	_drawableText->setPosition(
	_position.x + (_size.x / 2 - ((_drawableText->getCharacterSize() * (_text.size()-1) / 2)))
	, _position.y + 5);
	_drawableText->setString(_text);
	_isHigh = false;
}

sf::Drawable* MenuButton::getBackground()
{
	return _background;
}

sf::Drawable* MenuButton::getDrawableText()
{
	return _drawableText;
}

sf::Vector2f MenuButton::getPosition()
{
	return _position;
}

void MenuButton::update(sf::Vector2i const& mousepos)
{
	_isHigh = cursorOnIt(mousepos);
	if (_isHigh)
		_background->setFillColor(sf::Color(171, 76, 172));
	else
		_background->setFillColor(sf::Color(76, 157, 172));

}

bool MenuButton::cursorOnIt(sf::Vector2i const& mousepos)
{
	if (
		mousepos.x > _position.x &&
		mousepos.x < (_position.x + _size.x) &&
		mousepos.y > _position.y &&
		mousepos.y < (_position.y + _size.y)
		)
		return true;
	return false;
}

bool MenuButton::getIsHigh()
{
	return _isHigh;
}
