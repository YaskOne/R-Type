#include "Explosion.hh"

Explosion::Explosion(sf::Vector2f const& pos) : GraphicalItem(), _pos(pos)
{
    _sprite->setTexture(*(ac->getExplosion()));
    _sprite->setPosition(sf::Vector2f(_pos.x - (EXPLOSION_X / 2), _pos.y - (EXPLOSION_Y / 2)));
    _sprite->setTextureRect(sf::IntRect(0, 0, 120, 100));
    _referential = sf::milliseconds(100);
    _stage = 1;
    _lastUpdate = sf::seconds(0);
}

Explosion::~Explosion()
{

}

bool                Explosion::update(sf::Clock const& clock)
{
    if ((clock.getElapsedTime() - _lastUpdate) > _referential)
    {
    _lastUpdate = clock.getElapsedTime();
    _sprite->setTextureRect(sf::IntRect((120 * _stage) - 120,0 , 120, 100));
    _stage += 1;
    if (_stage == 5)
        return false;
    }
   return true;
}
