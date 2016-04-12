# R-Type

Lancer le CMakeLists.txt à la racine via la gui de CMake ou l'invite de commande avec la commande "cmake CMakeLists.txt"
pour génerer 
* une solution Visual 2k15 (v14.0) sous Windows
* un Makefile sous Unix

_Pour éviter les bétises, n'oublier pas dans Visual de faire : Projet->Afficher tout les fichiers_

La SFML est directement embarquée dans le dossier du client, pour rendre le projet completment portable.

La SFML est compilée satiquement sous windows

Les executables sont générés dans $ROOT/bin ( $ROOT/bin/client $ROOT/bin/server)

Les projets doivents etres générés en debug mode dans les IDE

L'architecture de dossier est la suivante :

* root
  * Client
    * SFML
    * src
        * ALL CLIENT SOURCES
    * includes
        * ALL CLIENT HEADERS
  
  * Server
    * src
        * ALL SERVER SOURCES
    * includes
        * ALL SERVER HEADERS
  
  * Common
    * ALL COMMONS FILES BETWEEN CLIENT AND SERVER
