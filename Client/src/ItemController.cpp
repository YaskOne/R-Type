#include "ItemController.hh"

ItemController::ItemController()
{
  _background = new sf::Sprite;
  _playerCount = 1;
  for (unsigned int i = 0; i < 4; ++i)
    {
      _availableNbPlayer.push_back(true);
    }
}

ItemController::~ItemController()
{
}

void		ItemController::draw()
{
  if (_background->getTexture() != NULL)
    vc->draw(_background);
  for (GraphicalItem *i : _items)
    vc->draw(i->getDrawable());
  for (GraphicalItem *i : _unlogicalItems)
    vc->draw(i->getDrawable());
  for (int i = 0; i != 4; i++)
    vc->draw(_scoreCtrl.getScoreDrawable(i));
}

void		ItemController::update()
{
    _scoreCtrl.update();
  for (GraphicalItem* i : _items)
    i->update(_clock);
  for (std::vector<GraphicalItem*>::iterator it = _unlogicalItems.begin(); it != _unlogicalItems.end();)
    {
      if (!((*it)->update(_clock)))
	{
	  it = _unlogicalItems.erase(it);
	}
      else
	++it;
    }
}

void		ItemController::levelUp(unsigned int lvl)
{
  this->setBackground(static_cast<BackgroundType>(lvl));
  this->addSplash("NEXT LEVEL !!!");
  _buffer.setBuffer(*(ac->getSound(NEXTLEVEL)));
  _buffer.play();
}

void		ItemController::setBackground(BackgroundType id)
{
  _background->setTexture(*(ac->getBackground(id)));
}

void ItemController::addShip(CrePlayPacket *packet)
{
  CrePlayData *data = packet->getData();

  for (size_t i = 0; i < 4; ++i)
    {
      if (_availableNbPlayer[i])
	{
	  _availableNbPlayer[i] = false;
	  _items.emplace_back(new PlayerGraphical(sf::Vector2f(0,0), sf::Vector2f(data->x - (1 / 4) * data->x, data->y - (1 / 4) * data->y), data->id, i));
	  break ;
	}
    }
}

void ItemController::addObj(CreObjPacket *packet)
{
  int id = packet->getData()->id;
  sf::Vector2f pos(packet->getData()->x, packet->getData()->y);
  float speedX = packet->getData()->speedX;
  float speedY = packet->getData()->speedY;

  if (packet->getData()->type == ObjectInfo::PLAYERREGULAR)
    _items.emplace_back(new BasicPlayerProjectileGrapical(sf::Vector2f(speedX, speedY), pos, (unsigned int)id, NULL));
  if (packet->getData()->type == ObjectInfo::ALIENREGULAR)
    _items.emplace_back(new BasicAlienProjectileGrapical(sf::Vector2f(speedX, speedY), pos, (unsigned int)id));
}

void ItemController::addObj(BonusPacket *packet)
{
  int id = packet->getData()->id;
  sf::Vector2f pos(packet->getData()->x, packet->getData()->y);
  ObjectInfo::WaveType type = packet->getData()->type;
  sf::Vector2f speed(packet->getData()->speed, packet->getData()->speed);

  switch (type)
    {
    case ObjectInfo::SPEEDBONUS :
      _items.emplace_back(new BonusSpeedGraphical(speed, pos, id, 0));
      break;
    case ObjectInfo::MULTISHOOTBONUS :
      _items.emplace_back(new MultiShootGraphical(speed, pos, id, 0));
      break;
    default :
      break;
    }
}

void ItemController::moveShip(MovePacket *packet)
{
  int id = packet->getData()->id;
  sf::Vector2f newPos(packet->getData()->x ,packet->getData()->y);
  uint32_t	score = packet->getData()->score;

  for (unsigned int i = 0; i != _items.size(); ++i)
    {
      if (dynamic_cast<IObject*>(_items[i])->getId() == id)
	{
	  static_cast<PlayerGraphical*>(_items[i])->setScore(score);
	  _scoreCtrl.setScore(static_cast<PlayerGraphical*>(_items[i])->getNbPlayer(), score);
	  static_cast<PlayerGraphical*>(_items[i])->setPos(newPos);
	  break;
	}
    }
}

void ItemController::addExplosion(sf::Vector2f pos)
{
  Explosion *expl = new Explosion(pos);
  
  _unlogicalItems.push_back(expl);
}

void ItemController::addSplash(std::string msg)
{
  _unlogicalItems.push_back(new SplashMessage(msg));
}

void ItemController::deleteObject(DelItemPacket *packet)
{
  int  id = packet->getData()->data;
  size_t i;
  
  for (i = 0; i != _items.size(); ++i)
    {
      if ((dynamic_cast<IObject*>(_items[i])->getId()) == id)
	break;
    }
  if (i == _items.size())
    return;
  if (dynamic_cast<IObject*>(_items[i])->getObjType() == ObjectInfo::PLAYER)
    {
      _availableNbPlayer[static_cast<PlayerGraphical*>(_items[i])->getNbPlayer()] = true;
    }
  addExplosion(static_cast<sf::Sprite*>(_items[i]->getDrawable())->getPosition());
  _items.erase(_items.begin() + i);
}

void ItemController::addAlien(CreIAPacket *packet)
{
  ObjectInfo::WaveType type = packet->getData()->iatype;
  sf::Vector2f speed(packet->getData()->speed, packet->getData()->speed);
  sf::Vector2f pos(packet->getData()->x, packet->getData()->y);
  unsigned int id = packet->getData()->id;
  float coeff = packet->getData()->coeff;

  switch (type)
    {
    case ObjectInfo::WaveType::BYDO :
      _items.emplace_back(new BydoAlienGraphical(speed, pos, id, coeff));
      break;
    case ObjectInfo::WaveType::GLAM :
      _items.emplace_back(new GlamAlienGraphical(speed, pos, id, coeff));
      break;
    case ObjectInfo::WaveType::DOKAN :
      _items.emplace_back(new DokanAlienGraphical(speed, pos, id, coeff));
      break;
    case ObjectInfo::WaveType::KAYBEROS :
      _items.emplace_back(new KayberosAlienGraphical(speed, pos, id, coeff));
      break;
    case ObjectInfo::WaveType::RIOS :
      _items.emplace_back(new RiosAlienGraphical(speed, pos, id, coeff));
      break;
    case ObjectInfo::WaveType::SCANT :
      _items.emplace_back(new ScantAlienGraphical(speed, pos, id, coeff));
      break;
    case ObjectInfo::WaveType::SHELL :
      _items.emplace_back(new ShellAlienGraphical(speed, pos, id, coeff));
      break;
    case ObjectInfo::WaveType::YORK :
      _items.emplace_back(new YorkAlienGraphical(speed, pos, id, coeff));
      break;
    case ObjectInfo::WaveType::XELF16 :
      _items.emplace_back(new Xelf16AlienGraphical(speed, pos, id, coeff));
      break;
    case ObjectInfo::WaveType::OBSTACLE :
      _items.emplace_back(new WallGraphical(speed, pos, id, coeff));
      break;
    default:
      break;
    }
}
