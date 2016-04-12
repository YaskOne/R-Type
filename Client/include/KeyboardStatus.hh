#pragma once

#include <SFML/Graphics.hpp>

typedef struct s_keyboarStatus
{
  sf::Vector2i mousePos;
  char		textEntered;
  bool		leftClick;
  bool		up;
  bool		down;
  bool		left;
  bool		right;
  bool		ctrl;
  bool		echap;
}				keyboardStatus;
