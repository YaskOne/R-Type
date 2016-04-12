#include "GraphicalItem.h"

GraphicalItem::GraphicalItem()
{
	_sprite = new sf::Sprite;
    _messageDrawable = new sf::Text;
    _msg = false;
}

sf::Drawable * GraphicalItem::getDrawable()
{
    if (!_msg)
	   return _sprite;
   return _messageDrawable;
}
