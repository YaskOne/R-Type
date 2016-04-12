#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

typedef enum e_ButtonType
{
	JOIN = 0,
	EXIT,
	NUMBEROFBUTTON,
}			ButtonType;

typedef enum e_BackgroundType
{
	MENU_BACKGROUND = 0,
	BACKGROUND_ONE,
	BACKGROUND_TWO,
	BACKGROUND_THREE,
	BACKGROUND_FOUR,
	NUMBEROFBACKGROUND
}				BackgroundType;

typedef enum    e_Ship
{
    PONE = 0,
    PTWO,
    PTHREE,
    PFOUR,
    PONEFIRE,
    PTWOFIRE,
    PTHREEFIRE,
    PFOURFIRE,
    NUMBEROFSHIP
}               Ship;

typedef enum    e_Sound
{
    BASICSHOT = 0,
    NEXTLEVEL,
    NUMBEROFSOUND
}               Sound;

typedef enum   e_Bonus
{
    SPEED = 0,
    MULTISHOOT,
    NUMBEROFBONUS
}               Bonus;

typedef enum e_Fonts
{
	STAR = 0,
    SPLASH,
	NUMBEROFFONTS
}			Font;

typedef enum e_Shot
{
	BASICALIENSHOT = 0,
	BASICPLAYERSHOT,
	NUMBEROFSHOT
}			 Shot;

typedef enum e_AlienType
{
	BYDO = 0,
	GLAM,
	DOKAN,
	KAYBEROS,
	RIOS,
	SCANT,
	SHELL,
	YORK,
	XELF16,
    WALL1,
	NUMBEROFALIEN
}			AlienType;

class							AssetsController
{
public:
	AssetsController(const char *);
	~AssetsController();

public:
	bool						loadAssets();
	bool						loadSoundAssets();
	bool						loadShipsAssets();
	bool						loadBackground();
	bool						loadShots();
	bool						loadButtons();
	bool						loadFonts();
	bool						loadAliens();
    bool                        loadBonus();

public:
	sf::Music					*getSoundTrack();
    sf::SoundBuffer             *getSound(Sound);
	sf::Texture					*getShipTexture(Ship);
	sf::Texture					*getBackground(BackgroundType);
	sf::Texture					*getShot(Shot);
	sf::Texture					*getButton(ButtonType, bool);
	sf::Texture					*getLogo();
	sf::Font					*getFont(Font);
	sf::Texture					*getAlien(AlienType);
	sf::Texture					*getExplosion();
    sf::Texture                 *getBonus(Bonus);

private:
	std::string					_assetsPath;

private:
	sf::Music					*_soundTrack;

private:
	std::vector<sf::Texture*>	_ships;
	std::vector<sf::Texture*>	_aliens;
	std::vector<sf::Texture*>	_backgrounds;
	std::vector<sf::Texture*>	_buttons;
	std::vector<sf::Texture*>	_buttonsHigh;
	std::vector<sf::Texture*>	_shots;
    std::vector<sf::Texture*>   _bonus;
	std::vector<sf::Font*>		_fonts;
    std::vector<sf::SoundBuffer*> _sounds;
	sf::Texture*				_rtypeLogo;
    sf::Texture*                _explosion;

};
