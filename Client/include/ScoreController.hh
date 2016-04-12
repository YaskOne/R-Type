#pragma once

#include <string>
#include "ViewController.hh"
#include "AssetsController.hh"

class               ScoreController
{
public:
  ScoreController();
  ~ScoreController();

public:
  void                update();
  void                setScore(int player, int score);
  sf::Text*           getScoreDrawable(int);

private:
  std::vector<sf::Text*>       _scoresDrawable;
  std::vector<int>             _scoreValue;
  sf::Color                   _color;
  bool                        _increaseColor;
};
