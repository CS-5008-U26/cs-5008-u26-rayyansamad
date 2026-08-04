Final Project - Maze Generator and Solver
Rayyan Samad

This program generates a random 21 by 21 maze using recursive
backtracking. It then solves the same maze using Depth-First Search
and Breadth-First Search and prints comparison results.

Files:
FinalProject_RayyanSamad.c - source code
FinalProjectPresentation.pptx - presentation slides

How to compile:

gcc FinalProject_RayyanSamad.c -o FinalProject_RayyanSamad

How to run with a random seed based on the current time:

./FinalProject_RayyanSamad

How to run with a fixed seed:

./FinalProject_RayyanSamad 42

Using the same fixed seed will generate the same maze each time.

Program output:
- Original generated maze
- DFS solution
- BFS solution
- Path length
- Number of cells explored
- Runtime

Maze symbols:
# = wall
blank space = open hallway
S = start
E = end
* = final solution path
. = explored cell