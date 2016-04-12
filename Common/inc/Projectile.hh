#ifndef _PROJECTILE_HH_
# define _PROJECTILE_HH_

# include "Object.hh"

class Projectile : public Object
{
public:
  Projectile(sf::Vector2f const&, sf::Vector2f const&, sf::Vector2i const&, unsigned int, ObjectInfo::ShotType);
  ~Projectile();

  ObjectInfo::ShotType	getRealType() const;

public:
  virtual bool		update(sf::Clock const&, std::vector<IObject*>&) = 0;
  virtual bool		update(sf::Clock const&) = 0;
  ObjectInfo::ShotType	_realType;
};

# endif
