#ifndef BONUSMULTISHOOT_H_
# define BONUSMULTISHOOT_H_

# include "ObjectInfo.hpp"
# include "ABonus.hh"
# include "Player.hh"

class MultiShoot : public ABonus
{
public:
  MultiShoot(sf::Vector2f const&, sf::Vector2f const&, unsigned int, float);
  virtual ~MultiShoot();
  bool	update(sf::Clock const&, std::vector<IObject*>&);
  bool	update(sf::Clock const&);
  void	actionBonus(Object*);
  ObjectInfo::WaveType	getBonusType() const;

private:
  MultiShoot(const MultiShoot &);
  MultiShoot &operator=(const MultiShoot &);
  bool		_stay;
  int		_fact;
};

#endif /* !BONUSMULTISHOOT_H_ */
