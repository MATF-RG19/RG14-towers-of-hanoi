# RG077-towers-of-hanoi

# # Towers of Hanoi
author: Milisavljević Katarina

# Description:

The Tower of Hanoi is a mathematical game or puzzle. It consists of three towers and a number of disks of different sizes, which can slide onto any tower. The puzzle starts with the disks in a stack in ascending order (the smallest at the top). The objective of the puzzle is to move the entire stack to another tower, obeying the following rules:
*   Only one disk can be moved at a time.
*   Each move consists of taking the upper disk from one of the stacks and placing it on top of another stack or on an empty rod.
*   No disk may be placed on top of a smaller disk.

# Preview:

![](https://raw.githubusercontent.com/MATF-RG18/RG7-towers-of-hanoi/master/Screenshots/2019-01-16.gif)

# Installation:

* Prerequisites: OpenGL/GLUT libraries installes

* Run make from the project directory.
* run ./towers_of_hanoi
* _if you want to play with custom number of disks, run ./towers_of_hanoi n (where n is the number of disks that you want)_

# Instructions:

| **Key** | **Description** |
| :---  | :--- |
| `a` | Move disk from A to B |
| `A` | Move disk from B to A |
| `s` | Move disk from A to C |
| `S` | Move disk from C to A |
| `d` | Move disk from B to C |
| `d` | Move disk from C to B |
| `h` `H` | Solve the puzzle using algorithm |
| `u` `U` | Undo move |
| `q` `Q` | Stop automatic solving |
| `r` `R` | Restart game |
| `ESC` | Exit the simulation |
