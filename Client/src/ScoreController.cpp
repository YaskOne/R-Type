#include "ScoreController.hh"

ScoreController::ScoreController()
{
    for (int i = 0; i != 4; i++ )
    {
        _scoresDrawable.emplace_back(new sf::Text);
        _scoresDrawable[i]->setFont(*(ac->getFont(STAR)));
    }
    _scoresDrawable[0]->setPosition(sf::Vector2f(10, 10));
    _scoresDrawable[1]->setPosition(sf::Vector2f(210, 10));
    _scoresDrawable[2]->setPosition(sf::Vector2f(410, 10));
    _scoresDrawable[3]->setPosition(sf::Vector2f(610, 10));
    _increaseColor = true;
    for (int i = 0; i != 4; i++ )
    _scoreValue.emplace_back(0);
    _color = sf::Color(1,0,255);
}

ScoreController::~ScoreController()
{
}

void                ScoreController::update()
{
    if (_color.r == 255 || _color.r == 0)
        _increaseColor = !_increaseColor;
    if (_increaseColor)
    {
        _color.r += 1;
        _color.g += 1;
        _color.b -= 1;
    }
    else
    {
        _color.r -= 1;
        _color.g -= 1;
        _color.b += 1;
    }
    _scoresDrawable[0]->setColor(_color);
    _scoresDrawable[1]->setColor(_color);
    _scoresDrawable[2]->setColor(_color);
    _scoresDrawable[3]->setColor(_color);
    _scoresDrawable[0]->setString(sf::String("P1: " + std::to_string(_scoreValue[0])));
    _scoresDrawable[1]->setString(sf::String("P2: " + std::to_string(_scoreValue[1])));
    _scoresDrawable[2]->setString(sf::String("P3: " + std::to_string(_scoreValue[2])));
    _scoresDrawable[3]->setString(sf::String("P4: " + std::to_string(_scoreValue[3])));
}

void                ScoreController::setScore(int player, int score)
{
    _scoreValue[player] = score;
}

sf::Text*           ScoreController::getScoreDrawable(int player)
{
    return _scoresDrawable[player];
}
