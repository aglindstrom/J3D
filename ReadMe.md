# Jgraph 3D
![](out/preview.png)
## Introduction
j3D generates jgraph code for a 3d mesh. Here is a fun [youtube](https://youtu.be/R08tyazQmP8) video animation of a rendered graph.

## Compilation
just use make. Running
`make`
in the repository root directory will compile the j3D binary, the makegrid binary, and all the generator binaries. They will be in `./bin/`. It will run all necessary commands to generate images of each generator graph. Images of the graph will be written to `./out/`.

## Contents
- [j3D](#usage): generates a Jgraph file from a provided txt
- [makegrid](#makegrid): makes a grid of points with z heights specified by an input file
- [sine](#sine): generates a sine wave along the x-axis of a mesh grid
- [rsine](#rsine): generates a sine wave along the radius of a mesh grid
- [rand](#rand): generates random z heights for a mesh grid
- [log](#log): generates a log graph along the radius of a mesh
- [quadratic](#quadratic): generates a quadratic graph along the x-axis of a mesh

## Usage

The simplest usage is to pass a file on stdin
```
./j3D < data.txt
```
this is boring and will only give you a top-down view of the mesh, still technically in 3d.

This is a bit more interesting
```
./j3D -x -0.615 -y 0.955 -z 0.785 < data.txt
```
The result is a nice isometric projection. Using radians can be annoying though. To use degrees instead use this.
```
./j3D -d -x -35.26 -y 54.74 -z 45 < data.txt
```

### Options
- d: use degree inputs instead of radian inputs
- x: the rotation on the x axis
- y: the rotation on the y axis
- z: the rotation on the z axis
  
One note is the the x and y axis rotations must be balanced or the projection will be tipped on it's side one way or the other.

### MakeGrid
makegrid: makes a grid of points with z heights specified by an input file

## Generators
Generators can be used to generate meshes for j3D but are not necessary. As long as the correct file format is used the mesh will be rendered.

### Usage
generators all have the same usage
```
./<generator> -x 10 -y 10 -t 2
```

### Options
- x: width of the mesh
- y: length of the mesh

### Sine
generates a sinewave along the X axis of a mesh grid
#### Options
- t: offset of the sine wave
- s: scale of the sine wave

### Rsine
generates a sinewave along the radius of a mesh grid
#### Options
- t: offset of the sine wave
- s: scale of the sine wave

### Rand
generates random z heights for a mesh grid
#### Options
- t: random seed

### Log
generates a log graph along the radius of a mesh
 
### Quadratic
generates a quadratic graph along the x-axis of a mesh
  
## j3D File Format
The file format is a simple ascii format. The format header is two values the number of indices followed by the number of vertices. A list of indices follows the header. The indices are grouped by faces, and separated by newlines. The vertices are listed after the indices. Vertices are listed as x,y,z coordinates and are separated by spaces. New line characters separate the vertices. The format looks like this.
```
 6 4
 1 2 3
 2 3 4
 0.0 0.0 1.0
 1.0 0.0 1.0
 0.0 1.0 1.0
 1.0 1.0 1.0
```


## Future Additions

- Add standford ply support
- Add wavefront support
- Add colors as input options

