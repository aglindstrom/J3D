# Jgraph 3D
## Introduction
J3D generates jgraph code for a 3d mesh. Here is a fun [youtube](https://youtu.be/R08tyazQmP8) video animation of a rendered graph.

## Compilation
just use make.
`make`
make will compile the J3D binary and all generator binaries along side it.

## Contents
- [J3D](#usage): generates a jgraph file from a provided txt
- [makegrid](#makegrid): makes a grid of points with z heights specified by an input file
- [sine](#sine): generates a sinewave along the X axis of a mesh grid
- [rand](#rand): generates random z heights for a mesh grid

## Usage

The simplest usage is to simply pass a file
`./J3D < data.txt`
this is boring and will only give you a top down view of the mesh, still technically in 3d though.

This is a bit more interesting
`./J3D -x -0.615 -y 0.615 -z 0.785 < data.txt`
The result is a nice isometric projection. Using radians can be annoying though. To use degrees instead use this.
`./J3D -d -x -35.26 -y 35.26 -z 45 < data.txt`

Here's a list of the options

- d: use degree inputs instead of radian inputs
- x: the rotation on the x axis
- y: the rotation on the y axis
- z: the rotation on the z axis

One note is the the x and y axis rotations must be balanced or the projection will be tipped on it's side one way or the other.

## Generators
Generators can be used to generate meshes for J3D but are not necessary. As long as the correct file format is used the mesh will be rendered.

### Usage
generators all have the same usage
`./<generator> -x 10 -y 10`

### MakeGrid
makegrid: makes a grid of points with z heights specified by an input file
makegrid is unique because it is the only generator that takes input. The input comes from standard in and should be x*y in length

### Sine
sine: generates a sinewave along the X axis of a mesh grid

### Rand
rand: generates random z heights for a mesh grid

### Options
- x: width of the mesh
- y: length of the mesh
- t: sine: offset of the sine wave | rand: random seed 

## Future Additions

- Add standford ply support
- Add wavefront support
- Add colors as input options

