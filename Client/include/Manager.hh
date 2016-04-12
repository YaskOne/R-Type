#pragma once

#include "ViewController.hh"
#include "AssetsController.hh"
#include "ItemController.hh"
#include "ObjectInfo.hpp"
#include "CUDPNetworkHandler.hh"
#include "IServerPacket.hh"
#include "CrePlayPacket.h"
#include "CreObjPacket.h"
#include "CreIAPacket.h"
#include "MovePacket.h"
#include "AlivePacket.hh"
#include "BonusPacket.hh"

extern ViewController *vc;
extern AssetsController *ac;

class					Manager
{
public:
  Manager(CUDPNetworkHandler*);
  ~Manager();

public:
  void				loop();
  sf::Time 			getElapsedTimeSinceLoop();
  int				treatEventsFromKeyboard();
  void				treatEventsFromNetwork();
  void				sendAlive(sf::Time const&);
  void				treatPacket(IServerPacket<ServerUDPResponse>* res);

private:
  sf::Clock			_clock;
  sf::Time			_referential;
  sf::Time			_lastAliveSent;
  sf::Time			_refAlive;
  unsigned int			_lvl;

private:
  keyboardStatus		_keyboardStatus;
  ItemController		*_itemCtrl;
  CUDPNetworkHandler		*_udpHand;
};
