#ifndef _LEVEL_LOADER_HH_
# define _LEVEL_LOADER_HH_

# include <fstream>
# include <sstream>
# include <deque>
# include <cstddef>
# include <vector>
# include "ObjectInfo.hpp"
# include "Waves.hh"

class	LevelLoader
{
public:
  LevelLoader();
  ~LevelLoader();

  void			parseLevel(const char *);
  static bool	        verifLine(const std::string &);
  static bool		verifFirst(const std::string &);
  static bool		verifOther(const std::string &);
  Waves			*getNextWave();
  const int		getWavesCount() const;

private:
  std::string			 _name;
  std::string			 _oldName;
  std::ifstream			 _levelFile;
  std::deque<std::string>	 _lines;
  std::string			 _compare[ObjectInfo::NUMBEROFWAVE];
  unsigned int		        _wavesCount;
};

#endif
