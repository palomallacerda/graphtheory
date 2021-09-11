# Implementation of algorithms most used in Graphs Theory
This repository is dedicated to the implementation of the algorithms of Graphs Theory's subjects.

> Status do Projeto: Em desenvolvimento :warning: 

## To run FordFullkerson code use
    g++ -o grafo fordFullkerson.cpp

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
