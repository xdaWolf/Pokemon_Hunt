# How to play:
- To start the game, open your cmd and type "make" (make sure you're in the path of this project, for Windows: `cd("path/to/Pokemon_Hunt")`).
- Execute `./main.exe`.
- Use `make clean` to delete .o files.

- Move your character (Pikachu) through keys WASD.
- Open the menu by pressing M, which allows changing game mode.
  
## Gamemode Normal:
- Collect all other Pokemon on the field while avoiding Pokeballs and Trainers. After you've collected all three Pokemon, head towards the Pokecenter to win.
- The fewer moves you make and the more HP you have left, the better your score.
- Getting hit three times results in Game Over.
- Pressing R at any point restarts the game. To get a new Pokemon/Trainer/Tree layout, restart the program.
- To end the game, press Escape or close the window.
  
## Gamemode Survival:
- Try not to get hit by Pokeballs.
- Once you get hit 3 times, the survived time is displayed.

# Customization:
- In `Field.h`, you can adjust the array sizes for `Collectable collectables[];`, `Trainer trainers[];`, `Pokeball pokeballs[];`, and `Obstacle trees[];`.
- IMPORTANT: Ensure that the number of elements in the `collectables` array matches the values of `positionCX` and `positionCY`.
- Modifying these values can make the game easier or harder. Change the `pokeballs`-Array for `Survival Gamemode`.
- After making changes, it's necessary to execute `make clean` and then `make` again to apply the modifications.

# How to test:
- To test the game, open your cmd and type "make test" (make sure you're in the path of this project, for Windows: `cd("path/to/Pokemon_Hunt")`).
- Execute `./test.exe`.
