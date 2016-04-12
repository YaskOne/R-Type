#ifndef ABONUS_H_
# define ABONUS_H_

# include "ObjectInfo.hpp"
# include "Object.hh"

class ABonus : public Object
{
public:
  ABonus(sf::Vector2f const&, sf::Vector2f const&, sf::Vector2i const& , unsigned int);
  virtual ~ABonus();
  virtual bool	update(sf::Clock const&) = 0;
  virtual bool	update(sf::Clock const&, std::vector<IObject*>&) = 0;
  virtual void	actionBonus(Object*) = 0;
  virtual ObjectInfo::WaveType	getBonusType() const = 0;

private:
  ABonus(const ABonus&);
  ABonus &operator=(const ABonus&);
};

#endif /* !ABONUS_H_ */
