#ifndef _OBJECT_INFO_HPP_
# define _OBJECT_INFO_HPP_

namespace ObjectInfo
{
enum Type
  {
    PLAYER = 0,
    ALIEN,
    BONUS,
    SHOT
  };

enum PlayerType
  {
    PLAYER1 = 0,
    PLAYER2,
    PLAYER3,
    PLAYER4,
    NUMBERPLAYER
  };

enum BonusType
  {
    SPEED = 1,
    MULTISHOOT
  };

enum ShotType
{
  PLAYERREGULAR = 1,
  ALIENREGULAR,
  NUMBEROFSHOT
};

enum WaveType
  {
    BYDO = 0,
    GLAM,
    DOKAN,
    KAYBEROS,
    RIOS,
    SCANT,
    SHELL,
    YORK,
    XELF16,
    OBSTACLE,
    SPEEDBONUS,
    MULTISHOOTBONUS,
    NUMBEROFWAVE
  };
};

#endif
