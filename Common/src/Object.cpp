#include "Object.hh"
#include "Projectile.hh"
#include "BasicPlayerProjectile.hh"
#include "ABonus.hh"
#include "Player.hh"

Object::Object(sf::Vector2f const& speed, sf::Vector2f const& pos, sf::Vector2i const& size, ObjectInfo::Type type, unsigned int id)
  : _damage(false), _speed(speed), _pos(pos), _size(size), _objType(type), _id(id)
{
  _life = 1;
  _isAlive = true;
  _isShoot = false;
}

Object::~Object() {}

const ObjectInfo::Type		&Object::getObjType() const
{
  return _objType;
}

const sf::Vector2i		&Object::getSize() const
{
  return _size;
}

const sf::Vector2f		&Object::getSpeed() const
{
  return _speed;
}

const sf::Vector2f		&Object::getPos() const
{
  return _pos;
}

const unsigned int		&Object::getId() const
{
  return _id;
}

void			Object::setPos(const sf::Vector2f &pos)
{
  this->_pos = pos;
}

void                    Object::setSpeed(const sf::Vector2f &speed)
{
  this->_speed = speed;
}

void			Object::damage()
{
  _damage = true;
}
bool			Object::isAlive() const
{
  return _isAlive;
}

bool			Object::isShooting()
{
  return _isShoot;
}

void			Object::setShooting(bool shoot)
{
  _isShoot = shoot;
}

bool			Object::isCaseToCheck(IObject* obj)
{
  return ((this->getObjType() == ObjectInfo::PLAYER && ((obj->getObjType() == ObjectInfo::SHOT
							 && static_cast<Projectile*>(obj)->getRealType() == ObjectInfo::ALIENREGULAR) || obj->getObjType() == ObjectInfo::ALIEN))
	  || (this->getObjType() == ObjectInfo::PLAYER && obj->getObjType() == ObjectInfo::BONUS)
	  || (this->getObjType() == ObjectInfo::BONUS && obj->getObjType() == ObjectInfo::PLAYER)
	  || (this->getObjType() == ObjectInfo::ALIEN && ((obj->getObjType() == ObjectInfo::SHOT
							   && static_cast<Projectile*>(obj)->getRealType() == ObjectInfo::PLAYERREGULAR) || obj->getObjType() == ObjectInfo::PLAYER))
	  || (this->getObjType() == ObjectInfo::SHOT && static_cast<Projectile*>(this)->getRealType() == ObjectInfo::PLAYERREGULAR && obj->getObjType() == ObjectInfo::ALIEN)
	  || (this->getObjType() == ObjectInfo::SHOT && static_cast<Projectile*>(this)->getRealType() == ObjectInfo::ALIENREGULAR && obj->getObjType() == ObjectInfo::PLAYER));
}

void			Object::changeScores(IObject* obj)
{
  if (this->getObjType() == ObjectInfo::SHOT && static_cast<Projectile*>(this)->getRealType() == ObjectInfo::PLAYERREGULAR && obj->getObjType() == ObjectInfo::ALIEN)
    static_cast<BasicPlayerProjectile*>(this)->increaseScore();
  if (this->getObjType() == ObjectInfo::ALIEN && obj->getObjType() == ObjectInfo::SHOT && static_cast<Projectile*>(obj)->getRealType() == ObjectInfo::PLAYERREGULAR)
    static_cast<BasicPlayerProjectile*>(obj)->increaseScore();
}

void			Object::handleBonuses(IObject *obj)
{
  if (this->getObjType() == ObjectInfo::PLAYER && obj->getObjType() == ObjectInfo::BONUS)
    {
      static_cast<ABonus*>(obj)->actionBonus(this);
    }
  if (this->getObjType() == ObjectInfo::BONUS && obj->getObjType() == ObjectInfo::PLAYER)
    {
      static_cast<ABonus*>(this)->actionBonus(static_cast<Object*>(obj));
    }
}

bool			Object::collision(std::vector<IObject*>& map)
{
  if (_damage)
    {
      _life -= 1;
      _damage = false;
    }
  else
    for (std::vector<IObject*>::iterator it = map.begin(); it != map.end(); it++)
      {
	if (this->isCaseToCheck(*it))
	  {
	    if ((this != *it)
		&& ((this->getPos().x <= (*it)->getPos().x + (*it)->getSize().x)
		    && (this->getPos().x + this->getSize().x >= (*it)->getPos().x)
		    && (this->getPos().y <= (*it)->getPos().y + (*it)->getSize().y)
		    && (this->getPos().y + this->getSize().y >= (*it)->getPos().y)))

	      {
		if (this->getObjType() != ObjectInfo::PLAYER || (*it)->getObjType() != ObjectInfo::BONUS)
		  {
		    _life = _life - 1;
		  }
		if (this->getObjType() != ObjectInfo::BONUS)
		  {
		    static_cast<Object*>(*it)->damage();
		  }
		changeScores(*it);
		handleBonuses(*it);
	      }
	  }
      }
  if (_life <= 0)
    _isAlive = false;
  return (_isAlive);
}
