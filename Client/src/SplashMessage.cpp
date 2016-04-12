#include "SplashMessage.hh"

SplashMessage::SplashMessage(std::string message) : GraphicalItem()
{
    _message = message;
    _messageDrawable->setFont(*(ac->getFont(SPLASH)));
    _messageDrawable->setString(_message);
    _messageDrawable->setCharacterSize(100);
    _messageDrawable->setPosition(sf::Vector2f(0, 0));
    _moveCoeff = 0.005;
    _msg  = true;
    _referential = sf::microseconds(1);
    _lastUpdate = sf::seconds(0);


}

SplashMessage::~SplashMessage()
{
    
}

bool                        SplashMessage::update(sf::Clock const& clock)
{
    if (_moveCoeff >= 1)
        return false;
   if ((clock.getElapsedTime() - _lastUpdate) > _referential)
    {
     _lastUpdate = clock.getElapsedTime();
   _moveCoeff += 0.005;
   _messageDrawable->setPosition(RES_X * _moveCoeff, RES_Y * _moveCoeff);
    }
    return true;
}



