# include "BasicAlienProjectile.hh"

BasicAlienProjectile::BasicAlienProjectile(sf::Vector2f const& speed, sf::Vector2f const& pos, unsigned int id)
  : Projectile(speed, pos, sf::Vector2i(50,20), id, ObjectInfo::ALIENREGULAR)
{}

BasicAlienProjectile::~BasicAlienProjectile()
{}

bool		BasicAlienProjectile::update(sf::Clock const& clock, std::vector<IObject*>& map)
{
  this->update(clock);
  this->collision(map);
  return true;
}

bool		BasicAlienProjectile::update(sf::Clock const& clock)
{
  if (_pos.x + _size.x < 0 || _pos.x > MAP_SIZE_X
      || _pos.y + _size.y < 0 || _pos.y > MAP_SIZE_Y)
    _isAlive = false;
  this->_pos.x = this->_pos.x - this->_speed.x;
  return true;
}
