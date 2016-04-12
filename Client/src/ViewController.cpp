
#include "ViewController.hh"

ViewController::ViewController()
{
  _mainWindow = new sf::RenderWindow(sf::VideoMode(1920, 1080), "RType" ,sf::Style::Fullscreen);
  _mainWindow->setKeyRepeatEnabled(false);
  _soundTrack = ac->getSoundTrack();
  _focus = true;
}

ViewController::~ViewController()
{

}

void							ViewController::clear()
{
  _mainWindow->clear();
}

void ViewController::operator<<(GraphicalItem *item)
{
  draw(item->getDrawable());
}

void							ViewController::refresh()
{
  _mainWindow->display();
}

void							ViewController::draw(sf::Drawable* drawable)
{
  _mainWindow->draw(*drawable);
}

keyboardStatus					ViewController::getKeyboardStatus()
{
  keyboardStatus		state = {sf::Vector2i(0,0), -1, false, false, false, false, false, false, false};

  state.textEntered = getTextEntered();
  if (!_focus)
    return state;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    state.echap = true;

  state.mousePos = sf::Mouse::getPosition(*_mainWindow);

  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    state.leftClick = true;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    state.up = true;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    state.down = true;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    state.left = true;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    state.right = true;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
    state.ctrl = true;
  return state;
}

char ViewController::getTextEntered()
{
	sf::Event e;
	if (_mainWindow->pollEvent(e))
	  {
        if (e.type == sf::Event::LostFocus)
            _focus = false;
        if (e.type == sf::Event::GainedFocus)
            _focus = true;
	    if (e.type == sf::Event::TextEntered)
	      {
		if (e.text.unicode < 128)
		  return(static_cast<char>(e.text.unicode));
	      }
	  }
	return -1;
}

void ViewController::startSoundtrack()
{
	_soundTrack->play();
}
