Assumptions Made:
The player is explicitly given in the map.txt file as an @.
Goblins can somehow jump (and also spawn) on top of one another since they don't check for collision of each other. I may or may not fix this issue in the future.

Todo:
Dependency injection. Create another class to act as a delagate between game and other classes. Currently using const *game as a stop gap.

Misc Notes:
Goblins are spawned randomly on the map and are allowed to only spawn on floor "." tiles. NumGoblins specifies the number of goblins to spawn.
I copied some linux specific code to get input to work without pressing enter. Will not work on windows. You will need to delete #include <termios.h> and related code from the game constructor to get regular input on windows.

