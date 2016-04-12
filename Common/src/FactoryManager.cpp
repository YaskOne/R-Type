#include <iostream>
#include "FactoryManager.hh"
#include "Exceptions.hpp"
#include "KayberosAlien.hh"
#include "GlamAlien.hh"
#include "YorkAlien.hh"
#include "Xelf16Alien.hh"
#include "ScantAlien.hh"
#include "RiosAlien.hh"
#include "BydoAlien.hh"
#include "DokanAlien.hh"
#include "Obstacle.hh"
#include "ShellAlien.hh"
#include "BonusSpeed.hh"
#include "MultiShoot.hh"

FactoryManager::FactoryManager(MapController *map) : _map(map)
{
  _factories.push_back(new AlienFactory<BydoAlien>(ObjectInfo::WaveType::BYDO));
  _factories.push_back(new AlienFactory<GlamAlien>(ObjectInfo::WaveType::GLAM));
  _factories.push_back(new AlienFactory<DokanAlien>(ObjectInfo::WaveType::DOKAN));
  _factories.push_back(new AlienFactory<KayberosAlien>(ObjectInfo::WaveType::KAYBEROS));
  _factories.push_back(new AlienFactory<RiosAlien>(ObjectInfo::WaveType::RIOS));
  _factories.push_back(new AlienFactory<ScantAlien>(ObjectInfo::WaveType::SCANT));
  _factories.push_back(new AlienFactory<ShellAlien>(ObjectInfo::WaveType::SHELL));
  _factories.push_back(new AlienFactory<YorkAlien>(ObjectInfo::WaveType::YORK));
  _factories.push_back(new AlienFactory<Xelf16Alien>(ObjectInfo::WaveType::XELF16));
  _factories.push_back(new AlienFactory<Obstacle>(ObjectInfo::WaveType::OBSTACLE));
  _factories.push_back(new AlienFactory<BonusSpeed>(ObjectInfo::SPEEDBONUS));
  _factories.push_back(new AlienFactory<MultiShoot>(ObjectInfo::MULTISHOOTBONUS));
  _nbFactory = _factories.size();
  _levelFiles.push_back("../../level/Level1.lvl");
  _levelFiles.push_back("../../level/Level2.lvl");
  _levelFiles.push_back("../../level/Level3.lvl");
  _levelFiles.push_back("../../level/Level4.lvl");
}

FactoryManager::~FactoryManager()
{}

void		FactoryManager::changeLevel(int level)
{
  try
    {
      _levelLoader.parseLevel(_levelFiles[level].c_str());
      this->initialiseLevel();
    }
  catch (Exceptions::FactoryExcept e)
    {
      std::cerr << e.what() << std::endl;
    }
}

void		FactoryManager::initialiseLevel()
{
  int j			= 0;
  int nb	        = _levelLoader.getWavesCount();
  std::vector<Waves*>	waves;

  waves.push_back(_levelLoader.getNextWave());
  for (int i = 0; j != nb; i = i + 1)
    {
      if (i >= static_cast<int>(_nbFactory))
	break;
      if (waves[j] != NULL)
	{
	  if (waves[j]->getType() == _factories[i]->getType())
	    {
	      _factories[i]->setWave(waves[j]);
	      j = j + 1;
	      i = -1;
	      if (j < nb)
		{
		  waves.push_back(_levelLoader.getNextWave());
		}
	    }
	}
      else
	waves.push_back(_levelLoader.getNextWave());
    }
}

bool				FactoryManager::remainingAliens()
{
  for (std::vector<IAlienFactory*>::iterator it = _factories.begin(); it != _factories.end(); it++)
    {
      if (!(*it)->isOver() && (*it)->getType() != ObjectInfo::WaveType::OBSTACLE)
	return false;
    }
  return true;
}

std::vector<IObject*>		*FactoryManager::update(const sf::Clock &clock)
{
  std::vector<IObject*>		*list = new std::vector<IObject*>;
  std::vector<IObject*>		*obj;

  for (std::vector<IAlienFactory*>::iterator it = _factories.begin(); it != _factories.end(); it++)
    {
      obj = (*it)->getNextEnemy(clock);
      for (auto it = obj->begin(); it != obj->end(); it++)
	{
	  if (*it != NULL)
	    {
	      list->push_back(*it);
	    }
	}
      delete obj;
    }
  return (list);
}
