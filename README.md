# cub3D
## Summary
This project is inspired by the world-famous 90’s game Wolfenstein 3D, which
was the first FPS ever. It uses the technique of ray-casting. The goal of this project is to
make a dynamic view inside a maze, using colors, textures and sprites.
## Compilation
Use the ```make``` command to compile using the Makefile.
## Execution
```./cub3D [map_path]```: play the game.

```./cub3D [map_path] --save```: save the first rendered image in a bmp format.
## Recommendations
The map file must be in *.cub format.

The textures must be in *.xpm format.

The colors must be in R,G,B format (each byte from 0 to 255).

All the following information must be present in the *.cub file:

* R resolutionX resolutionY : window resolution
* NO/SO/EA/WE R,G,B : color on either North, South, East or West wall
* NO/SO/EA/WE texture_path : texture on either North, South, East or West wall
* S texture_path : sprite texture
* C/F R,G,B : color on ceiling and floor
* C/F texture_path : texture on ceiling and floor (note that if the ceiling texture is named sky#.xpm, a skybox effect will replace the ceiling effect).
* The map must be present and last in the file

The map must be in the following format:

* 1s are walls
* 0s are paths
* 2s are sprites
* N/S/W/E is the player start position and direction; must be present one and only once on the map
* The map must be surrounded by 1s
## Usage
* W/A/S/D to move
* Left/right arrows to turn
* Shift to sprint
* H to hide/unhide help menu
* ESC to quit
