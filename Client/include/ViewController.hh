#pragma once

# include <iostream>
# include <SFML/Graphics.hpp>
# include <SFML/Audio.hpp>
# include "KeyboardStatus.hh"
# include "AssetsController.hh"
# include "GraphicalItem.h"

extern AssetsController *ac;

#define SCREENRATIO 1

#define RES_X 1920
#define RES_Y 1080

#define SHIP_ASSET_SIZE_Y 270
#define SHIP_ASSET_SIZE_X 100

#define ALIEN_ASSET_SIZE_Y 100
#define ALIEN_ASSET_SIZE_X 100

#define BOSS_SIZE_X 500
#define BOSS_SIZE_Y 500

#define EXPLOSION_X 120
#define EXPLOSION_Y 100 

#define SHOT_ASSET_SIZE_Y 20
#define SHOT_ASSET_SIZE_X 50

#define LOGO_SIZE_X 500
#define LOGO_SIZE_Y 100

#define BUTTON_X 100
#define BUTTON_Y 50

class GraphicalItem;

class				ViewController
{
public:
	ViewController();
	~ViewController();

//GRAPHICAL STUFF
public:
	void			refresh();
	void			draw(sf::Drawable*);
	void			clear();
	void			operator<<(GraphicalItem*);

//INPUT STUFF
	keyboardStatus	getKeyboardStatus();
	char			getTextEntered();

//AUDIO STUFF
public:
	void			startSoundtrack();

private:
	sf::RenderWindow	*_mainWindow;
	sf::Music			*_soundTrack;
    bool                _focus;
};
