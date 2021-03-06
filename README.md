# Implementation of algorithms most used in Graphs Theory
This repository is dedicated to the implementation of the algorithms of Graphs Theory's subjects.<br>

Students : Paloma Lacerda and Rodrigo Ferreira

> Project Status: Concluded :heavy_check_mark:

## To run FordFullkerson code use
    g++ -o ford fordFullkerson.cpp
    ./ford

## To run Ford Fullkerson using a File
    g++ -o ford fordFullkerson.cpp
    ./ford < ford.input

#### Input example

```
    5 5
    0 3
    0 1 1000
    0 2 1000
    1 2 1
    1 3 1000
    2 3 1000
```
#### Output example
    Your max flow is: 2000

##

## To run Kruskall code use
    g++ -o kruskal kruskal.cpp
    ./kruskal

## To run Kruskall using a File
    g++ -o kruskal kruskal.cpp
    ./kruskal < kruskall.input

#### Input example

```
    7 11
    0 1 7
    0 3 5
    1 2 8
    1 3 9
    1 4 7
    2 4 5
    3 4 15
    3 5 6
    4 5 8
    4 6 9
    5 6 11
```
#### Output example
    (A, D) = 5
    (C, E) = 5
    (D, F) = 6
    (A, B) = 7
    (B, E) = 7
    (E, G) = 9
    Your Final Weight is: 39

## To run Prim code use
    g++ -o Prim Prim.cpp
    ./Prim

## To run Prim using a File
    g++ -o Prim Prim.cpp
    ./Prim < input.txt

#### Input example
<ul>
    <li>First line Vertices and Edges both integer.</li>
    <li>Last line will be the initial vertice of algorithm.</li>
</ul>

```
   6 8
   1 2 5
   1 3 4
   1 4 2
   1 6 6
   2 4 1
   2 5 7
   3 5 6
   4 6 1
   1
```
#### Output example
#### The initial vertice have father -1

    Father[1] = -1
    Father[2] = 4
    Father[3] = 1
    Father[4] = 1
    Father[5] = 3
    Father[6] = 4

    AGM/MST = 14

## To run Dijkstra code use
    g++ -o Dijkstra Dijkstra.cpp
    ./Dijkstra

## To run Dijkstra using a file
    g++ -o Dijkstra Dijkstra.cpp
    ./Dijkstra < input.txt

### Input example

<ul>
    <li>The last line is a specific vertice </li>
    <li> The penultimate is a decision to print all vertices or a specific vertex, (0) : print all vertices and (1) :  print a specific vertice</li>
    <li>The second to last  line is the initial vertice</li>
</ul>

```
    6 8
    1 2 5
    1 3 4
    1 4 2
    1 6 6
    2 4 1
    2 5 7
    3 5 6
    4 6 1
    1
    0
    5

```
#### Ouput example
```
    Distance(1, 1) = 0
    Distance(1, 2) = 3
    Distance(1, 3) = 4
    Distance(1, 4) = 2
    Distance(1, 5) = 10
    Distance(1, 6) = 3
```