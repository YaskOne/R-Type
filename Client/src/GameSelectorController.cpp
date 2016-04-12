#include "GameSelectorController.hh"

GameSelectorController::GameSelectorController(CUDPNetworkHandler **handler, CNetworkHandler *tcpHand) :
  _tcpHand(tcpHand), _udpHand(handler)
{
  _background = new Backgroud;
  std::string txt("or choose an existing game, May the force be with you");
  _disclaimer = new sf::Text(txt, *(ac->getFont(STAR)));

  _disclaimer->setPosition(
			   (1920 ) - 1590//((_disclaimer->getCharacterSize() * txt.size()) / 2)
			   , RES_Y * 0.4
			   );

  _join = false;

  _createGameButton = new MenuButton("Create a game", sf::Vector2f((RES_X / 2) - (LOGO_SIZE_X / 2), RES_Y * 0.3), sf::Vector2f(500 , 50), STAR);
  _refresh = new MenuButton("Refresh game list", sf::Vector2f(RES_X - (LOGO_SIZE_X + 100), RES_Y * 0.5), sf::Vector2f(500 , 50), STAR);

  _gameName =   new TextArea(STAR, sf::Vector2f((RES_X / 2) - (LOGO_SIZE_X / 2), RES_Y * 0.2),
			     sf::Vector2f(500, 50), "Enter new game name");
}

void                        GameSelectorController::initList()
{
  IServerPacket<ServerTCPResponse> *response;
  ServerTCPResponse type;
  std::string name;
  unsigned int         id;
  float                posy = 0.45;

    _games.clear();
  _tcpHand->sendToServer(new ReqGamePacket(REQ_GAME));
  while (true)
    {
      response = _tcpHand->receiveFromServer();
      type = response->getCommandType();
      if (type == DES_GAME)
	{
	  name = static_cast<DesGamePacket*>(response)->getData()->gameName;
	  id = static_cast<DesGamePacket*>(response)->getData()->id;
	  _games.emplace_back(
	  std::pair<MenuButton*, int>(
	  new MenuButton(name , sf::Vector2f((RES_X / 2) - (LOGO_SIZE_X / 2), RES_Y * posy), sf::Vector2f(500 , 50), STAR)
      , id
		)
			      );
       posy += 0.05;
	}
      if (type == END_GAME_LIST) {
	return; }
      delete response;
    }

}

void						GameSelectorController::loop()
{

  initList();
  while (true)
    {
      _clock.restart();
      vc->clear();

      if (_join)
	return;

      _keyboardStatus = vc->getKeyboardStatus();
      treatEvents();

      update();
      drawMenuItems();

      vc->refresh();
      _loopTime = _clock.getElapsedTime();
      sf::sleep(sf::Time(sf::microseconds(16666)) - _loopTime);
    }
}

void						GameSelectorController::treatEvents()
{
  if (_keyboardStatus.leftClick)
    {
      for (auto i : _games)
        {
	  if (i.first->getIsHigh())
            {
	      joinGame(i.second);
	      return;
            }
        }
      if (_createGameButton->getIsHigh())
	createGame();
      if (_refresh->getIsHigh())
    initList();
    }
}

void						GameSelectorController::update()
{
  _background->update();
  _createGameButton->update(_keyboardStatus.mousePos);
  _refresh->update(_keyboardStatus.mousePos);
  for (auto i : _games)
    {
      i.first->update(_keyboardStatus.mousePos);
    }
  _gameName->update(_keyboardStatus);
}

void						GameSelectorController::drawMenuItems()
{
  vc->draw(_background->getDrawable());
  vc->draw(_disclaimer);
  vc->draw(_createGameButton->getBackground());
  vc->draw(_createGameButton->getDrawableText());
  vc->draw(_refresh->getBackground());
  vc->draw(_refresh->getDrawableText());
  vc->draw(_gameName->getTextArea());
  vc->draw(_gameName->getDrawableText());
  for (auto i : _games)
    {
      vc->draw(i.first->getBackground());
      vc->draw(i.first->getDrawableText());
    }
}

void                        GameSelectorController::createGame()
{
  IServerPacket<ServerTCPResponse> *response;

  _tcpHand->sendToServer(new NewGamePacket(ADD_GAME, _gameName->getText()));
  response = _tcpHand->receiveFromServer();
  *_udpHand = new CUDPNetworkHandler((
				      (GameInfoPacket*)response)->getData()->ip,
				     std::to_string(((GameInfoPacket*)response)->getData()->port));
  sf::sleep(sf::milliseconds(500));
  (*_udpHand)->initSocket();
  (*_udpHand)->send(new CAuthUDPPacket(CAUTH_UDP, 0, "bite"));
  IServerPacket<ServerUDPResponse>	*packet;
  while (true)
    {
      if ((*_udpHand)->selectServer(NULL)
	  && (packet = (*_udpHand)->receive())
	  && packet->getCommandType() == AUTH_UDP
	  && static_cast<AuthUDPPacket*>(packet)->getData()->success == SUCCESS)
	break;
    }
  _join = true;
}

void						GameSelectorController::joinGame(int i)
{
  IServerPacket<ServerTCPResponse> *response;

  _tcpHand->sendToServer(new JoinPacket(JOIN_GAME, i));
  response = _tcpHand->receiveFromServer();
  if (response->getCommandType() != GAME_INFO)
  {
    initList();
    return;
  }
  *_udpHand = new CUDPNetworkHandler(((GameInfoPacket*)response)->getData()->ip, std::to_string(((GameInfoPacket*)response)->getData()->port));
  (*_udpHand)->initSocket();
  (*_udpHand)->send(new CAuthUDPPacket(CAUTH_UDP, 0, "bite"));
  IServerPacket<ServerUDPResponse>	*packet;
  while (true)
    {
      if ((*_udpHand)->selectServer(NULL)
	  && (packet = (*_udpHand)->receive())
	  && packet->getCommandType() == AUTH_UDP
	  && static_cast<AuthUDPPacket*>(packet)->getData()->success == SUCCESS)
	break;
    }
  _join = true;
}
