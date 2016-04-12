#ifndef BONUSSPEED_H_
# define BONUSSPEED_H_

# include "ObjectInfo.hpp"
# include "ABonus.hh"
# include "Player.hh"

class BonusSpeed : public ABonus
{
public:
  BonusSpeed(sf::Vector2f const&, sf::Vector2f const&, unsigned int, float);
  virtual ~BonusSpeed();
  bool	update(sf::Clock const&, std::vector<IObject*>&);
  bool	update(sf::Clock const&);
  void	actionBonus(Object*);
  ObjectInfo::WaveType	getBonusType() const;

private:
  BonusSpeed(const BonusSpeed &);
  BonusSpeed &operator=(const BonusSpeed &);
  bool		_stay;
  int		_fact;
};

#endif /* !BONUSSPEED_H_ */
