# include "MenuController.hh"

MenuController::MenuController(CNetworkHandler **tcpHand) : _tcpHandAddr(tcpHand)
{
  _join = false;
  _ipArea =
  new TextArea(STAR, sf::Vector2f((RES_X / 2) - (LOGO_SIZE_X / 2), RES_Y * 0.3),
			 sf::Vector2f(500,50), "Enter ip");

  _portArea =
  new TextArea(STAR, sf::Vector2f((RES_X / 2) - (LOGO_SIZE_X / 2), RES_Y * 0.4),
			 sf::Vector2f(500, 50), "Enter port");

  _nicknameArea =
  new TextArea(STAR, sf::Vector2f((RES_X / 2) - (LOGO_SIZE_X / 2), RES_Y * 0.5),
			 sf::Vector2f(500, 50), "Enter nickname");

  _buttons.resize(NUMBEROFBUTTON);
  _buttons[JOIN] = new MenuButton
  ("Join", sf::Vector2f((RES_X / 2) - (LOGO_SIZE_X / 2), RES_Y * 0.6), sf::Vector2f(500 , 50), STAR);;
  _buttons[EXIT] = new MenuButton
  ("Exit", sf::Vector2f((RES_X / 2) - (LOGO_SIZE_X / 2), RES_Y * 0.7), sf::Vector2f(500 , 50),  STAR);

  _background = new Backgroud();
  _logo.setTexture(*(ac->getLogo()));
  _logo.setPosition(sf::Vector2f((RES_X / 2) - (LOGO_SIZE_X / 2), RES_Y * 0.05));
}

MenuController::~MenuController()
{
}

void MenuController::loop()
{
  while (true)
    {
      _clock.restart();
      vc->clear();

      _keyboardStatus = vc->getKeyboardStatus();
      treatEvents();

      if (_join)
	return;

      update();
      drawMenuItems();

      vc->refresh();
      _loopTime = _clock.getElapsedTime();
      sf::sleep(sf::Time(sf::microseconds(16666)) - _loopTime);
    }
}

void MenuController::treatEvents()
{
  if (_keyboardStatus.leftClick == true)
    for (int i = 0; i != _buttons.size(); i++)
      {
	if (_buttons[i]->getIsHigh())
	  onClick((ButtonType)i);
      }
}

void MenuController::update()
{
  for (int i = 0; i != _buttons.size(); i++)
    {
      _buttons[i]->update(_keyboardStatus.mousePos);
    }
  _ipArea->update(_keyboardStatus);
  _portArea->update(_keyboardStatus);
  _nicknameArea->update(_keyboardStatus);
  _background->update();
}

void MenuController::drawMenuItems()
{
  vc->draw(_background->getDrawable());
  vc->draw(&_logo);
  vc->draw(_ipArea->getTextArea());
  vc->draw(_ipArea->getDrawableText());
  vc->draw(_portArea->getTextArea());
  vc->draw(_portArea->getDrawableText());
  vc->draw(_nicknameArea->getTextArea());
  vc->draw(_nicknameArea->getDrawableText());
  for (int i = 0; i != _buttons.size(); i++)
    {
      vc->draw(_buttons[i]->getBackground());
      vc->draw(_buttons[i]->getDrawableText());
    }
}

void MenuController::onClick(ButtonType type)
{
  switch (type)
    {
    case JOIN:
      joinGame();
      break;
    case EXIT:
      exit(0);
      break;
    }
}

void MenuController::joinGame()
{
  std::string ip = _ipArea->getText();
  std::string port = _portArea->getText();
  IServerPacket<ServerTCPResponse>* response;

  *_tcpHandAddr = new CNetworkHandler(ip, port);
  CNetworkHandler* _tcpHand = *_tcpHandAddr;
  if (_tcpHand->initSocket())
    {
      _tcpHand->sendToServer(new NickPacket(AUTH_TCP, _nicknameArea->getText()));
      response = _tcpHand->receiveFromServer();
      if (response->getCommandType() == AUTH)
      {
	_join = true;
      }
      else
	;
    }
  else
    std::cerr << "FAILED TO JOIN GAME" << std::endl;
}
