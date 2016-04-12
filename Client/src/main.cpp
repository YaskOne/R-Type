# include <iostream>
# include <ctime>
# include "ViewController.hh"
# include "Manager.hh"
# include "MenuController.hh"
# include "AssetsController.hh"
# include "CNetworkHandler.hh"
# include "CUDPNetworkHandler.hh"
# include "GameSelectorController.hh"

ViewController *vc;
AssetsController *ac;

int main(int argc, char **av)
{
  ac = new AssetsController("../../assets/");
  if (ac->loadAssets() == false)
    {
      std::cerr << "assets could not be loaded, aborting . . ." << std::endl;
      return -1;
    }

  vc = new ViewController;

  Manager *m;
  MenuController *menu;
  CNetworkHandler *tcpHand;
  CUDPNetworkHandler *udpHand;
  GameSelectorController *menu2;

  std::srand(std::time(0));
  while (true)
    {
      menu = new MenuController(&tcpHand);
      menu->loop();
      menu2 = new GameSelectorController(&udpHand, tcpHand);
      menu2->loop();
      m = new Manager(udpHand);
      m->loop();
      delete m;
    }
}
