# SkyRoads-Remastered
A modern, OpenGL take on the video game SkyRoads developed by BlueMoon Software(1993)

For this game to work:
- Download the Framework-EGC-master VS project from my Bow-And-Arrow repository
- Add the Skyroads directory (from Models) to .../Framework-EGC-master/Resources/Models/ (the 3d objects needed for the game)
- Add: #include <SkyroadsRemastered/Skyroads.h> to Main.cpp (from .../Framework-EGC-master/Source/)
- Change the line: World *world = new BowAndArrow(); to World *world = new Skyroads(); (in Main.cpp)
- Add the SkyroadsRemastered directory to .../Framework-EGC-master/Source/

How to play:

- W/S - adjust moving speed
- A/D - move left/right
- Space - jump
- C - toggle 3rd person/1st person camera

Rules:

Fuel bar in the upper right corner:
    - empties proportionally to the speed the UFO is travelling at
    - if it's depleted: -1HP

Landing:
    - Green platform: fuel++
    - Yellow platform: fuel--
    - Orange platform: game speeds up for a set amount of time
    - Red platform: game over
    - Falling: game over
    
Demo gameplay on YouTube:
https://youtu.be/YNz6FkyEvds

    
