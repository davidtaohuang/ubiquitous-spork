# Wolf3D
A raycasting maze-runner in the style of Wolfenstein 3D, built using C and libmlx (graphics library).

## Demo

![demo gif](demo/demo.gif?raw=true "wolf3d Demo")

You can also see a more in-depth demo [here on Youtube](https://youtu.be/n87m4rkzbOU).

## Installation

This project was build using the El Capitan version of libmlx, so it probably won't work (as in won't compile or just segfault) unless you're running El Capitan on a Mac.

1. Clone the repository or download and extract it.
2. `make`
3. `./wolf3d maps/example2.map`

You can replace `maps/example2.map` with any valid map file; see the two example maps for formatting.

### Controls:
```
W or UP ARROW to move forward
S or DOWN ARROW to move backwards
A or LEFT ARROW to turn to the left
D or RIGHT ARROW to turn to the right

Hold SHIFT to sprint (move faster)
Hold LEFT-CONTROL or SPACE to walk (move slower)
Hold Z and A/LEFT ARROW or D/RIGHT ARROW to strafe left/right>

Press TAB to display debug info
Press ESCAPE to exit the program
```
## Acknowledgements

[Lodev's Raycasting Tutorial](http://lodev.org/cgtutor/raycasting.html)

[Permadi's Raycasting Tutorial](http://www.permadi.com/tutorial/raycast/rayc2.html)

[Legend of Zelda: Phantom Hourglass Texture Pack](https://www.planetminecraft.com/texture_pack/zelda-phantom-hourglass/)
