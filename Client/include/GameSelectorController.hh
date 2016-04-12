#pragma once

#include <utility>
#include "ViewController.hh"
#include "AssetsController.hh"
#include "MenuButton.h"
#include "TextArea.h"
#include "Background.h"
#include "CNetworkHandler.hh"
#include "CUDPNetworkHandler.hh"
#include "ReqGamePacket.h"

class			GameSelectorController
{

public:
  GameSelectorController(CUDPNetworkHandler **handler, CNetworkHandler *tcpHand);
  void						loop();
  void						treatEvents();
  void						update();
  void						drawMenuItems();
  void						joinGame(int i);
  void                        initList();
  void                        createGame();

private:
  sf::Clock					    _clock;
  keyboardStatus				_keyboardStatus;
  Backgroud*					_background;
  sf::Time					    _loopTime;
  bool						    _join;
  sf::Text*					    _disclaimer;
  std::vector<std::pair<MenuButton*, int>>	_games;
  MenuButton					*_createGameButton;
  TextArea					*_gameName;
  MenuButton                *_refresh;

private:
  CNetworkHandler				*_tcpHand;
  CUDPNetworkHandler				**_udpHand;
};
