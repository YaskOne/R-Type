#pragma once

#include "GraphicalItem.h"
#include "ViewController.hh"
#include "AssetsController.hh"

class                   SplashMessage : public GraphicalItem
{
    public:
        SplashMessage(std::string);
        ~SplashMessage();
   
   public:
        bool                        update(sf::Clock const&);
        
   private:
        std::string                 _message;
        float                       _moveCoeff;
        sf::Time                    _referential;
        sf::Time                    _lastUpdate;

};