#include "Background.h"

Backgroud::Backgroud()
{
  _background = new sf::Sprite;
  _background->setTexture(*(ac->getBackground(MENU_BACKGROUND)));
  _scale = sf::Vector2f(1.0, 1.0);
  _position = sf::Vector2f(0, 0);
  _zoom = true;
}

void Backgroud::update()
{
  if (_scale.x > 1.500 || _scale.x < 0.999)
    _zoom = !_zoom;
  if (_zoom)
    {
      _scale.x += 0.001;
      _scale.y += 0.001;
      _position.x -= 1;
      _position.y -= 1;
    }
  else
    {
      _scale.x -= 0.001;
      _scale.y += 0.001;
      _position.x += 1;
      _position.y += 1;
    }
  _background->setScale(_scale);
  _background->setPosition(_position);
}

sf::Drawable * Backgroud::getDrawable()
{
  return _background;
}
