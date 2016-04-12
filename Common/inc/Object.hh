#ifndef _OBJECT_HH_
# define _OBJECT_HH_

# include "IObject.hh"
# include "MapController.hh"

class Object : public IObject
{
public:
  Object(sf::Vector2f const&,
	 sf::Vector2f const&,
	 sf::Vector2i const&,
	 ObjectInfo::Type,
	 unsigned int);
  ~Object();

public:
  const ObjectInfo::Type		&getObjType() const;
  const sf::Vector2i			&getSize() const;
  const sf::Vector2f			&getSpeed() const;
  const sf::Vector2f			&getPos() const;
  const unsigned int			&getId() const;
  bool					isAlive() const;
  bool					isShooting();
  void					setShooting(bool);
  void					damage();
  void					setPos(const sf::Vector2f &pos);
  void					setSpeed(const sf::Vector2f &speed);
  virtual bool				update(sf::Clock const&, std::vector<IObject*>&) = 0;
  virtual bool				update(sf::Clock const&) = 0;

private :
  bool					isCaseToCheck(IObject*);
  void					changeScores(IObject*);
  void					handleBonuses(IObject*);

protected:
  bool					collision(std::vector<IObject*>&);

protected:
  bool				_damage;
  unsigned int			_id;
  int				_life;
  bool				_isAlive;
  bool				_isShoot;
  sf::Vector2f			_speed;
  sf::Vector2i			_size;
  sf::Vector2f			_pos;
  ObjectInfo::Type		_objType;
};

#endif
