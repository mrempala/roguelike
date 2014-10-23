Assumptions Made:
The player is explicitly given in the map.txt file as an @.
Goblins can somehow jump on top of one another since they don't check for collision of each other. I may or may not fix this issue in the future.

I copied some linux specific code to get input to work without pressing enter. Will not work on windows. You will need to delete #include <termios.h> and related code from the game constructor to get regular input on windows.

