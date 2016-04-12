#ifndef GAMEHANDLER_H_
# define GAMEHANDLER_H_

# include "GameInfo.h"
# include "ClientInfo.h"
# include <vector>

class GameHandler
{
 public:
  GameHandler(std::string const& ip);
  ~GameHandler();
  GameInfo*				addClientInGame(ClientInfo* client, int id);
  int					startNewGame(std::string const& name);
  std::vector<GameInfo*>&		getGameList();
  void					closeGame(std::vector<GameInfo*>::iterator& it, GameInfo* game);
  void					checkEndGames();

 private:
  std::vector<GameInfo*>		_gameList;
  int					_maxID;
  std::string				_ip;
  uint32_t				_maxPort;
};

#endif
