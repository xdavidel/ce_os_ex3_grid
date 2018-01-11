# Introduction
We’re not trying to be greedy, but we’re going to ask you to code quite a big thing. This, will
probably take your Windows API skills to the next level. We are going to create a grid!

## Grid
As basic as it sounds, and a bit like the image shows - you’re asked to create a program that
displays an active grid, the grid could be either a red, green, or blue grid.
By active - it means that items on the grid will change their color intensity randomly, in 3 different
modes:
* Fade in - Item intensity grows from darkest to brightest in animation
* Fade out - Opposite of fade in, until black (off)
* On/Off - directly from off (black) to on (full intensity)
[Modes should be activated in turns, randomly, per-item.]

The grid items can be drawn as rectangles, circles, or whatever you choose, make sure they are all
in the same size, positioned symmetrically and with proper margins between each.
The color mode is changed with the user hitting the spacebar. For instance, if the current color is
red and user hits spacebar, color changes to green, another hit - changes to blue, then back to red,
and so on..
The size of the window created should be fixed, while the dimensions of the grid should be
dynamic (received as parameters from the user - items count as width, items count as height).
Therefore scrollbars will be necessary.

## Remarks
- Only WinAPI is allowed, no external UI libraries accepted.
- As mentioned above, the user supplies the grid dimensions.
- Write your program in steps, divide your work so you see progress.
## Your Submission

Please submit the necessary code files