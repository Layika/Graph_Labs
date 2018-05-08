# Graph labs 01

Repository contains solution to tasks listed [here](http://home.agh.edu.pl/~ewach/grafy/Zestaw_1.pdf) (in Polish).
<p>
These are as follows:
<p>
1. Implement a graph, use adjacency matrix, adjacency list and incidence matrix. Implement translating from one type to another
2. Write a program to visualize a graph
3. Implement generating random graphs

## Getting Started

These instructions will tell you how to get and use the code here.


### Setting up

First clone the repository:

```
$ git clone https://github.com/Layika/Graph_Labs.gi
```

and then simply run make:

``` 
make
```

### Dependencies

In order to use python script to visualize graphs you need to install a few packages. Try this:

```
pip3 install networkx
pip3 install numpy
pip3 install matplotlib.pyplot
```

## Running the tests

To run very simple tests type:

``` 
make run
```

## Project description

### Visualisation script

Script used for showing graphs is written in Python. In order to get a graph chart prepare a file `data.txt` with adjacency list inside.
<p>
Then run the script as follows:

```
python3 GraphPaint.py data.txt
```
You can save generated picture if you like, just press saving icon.


### Graph implementation

Below you can find more detailed description how it all works and how to navigate.

#### Class Graph

This is the default class for handling graphs. Below you can find a few useful methods. 
<p><p>
To create a graph write:
```
Graph g;
```
Graph's constructor creates a new matrix, but doesn't fill it. It's empty by default so in order to use it you either need to generate a random graph or read a file with base data.
<p><p>
This is how you create a random graph:

```
TODO
```

And this is what you can do to read a file (this project comes with three example files):

```
g.readFile("adjlist.txt");
```

This method can read three types of files: adjacency matrices, adjacency lists and incidence matrices. Then it saves read matrix. For detailed description how it does it look in `Graph.cpp` file. 


#### Class Matrix

Unless you want to add something new don't use this class.


## Authors

* Mikołaj Skawiński
* Michalina Oleksy
* Mateusz Sacha
* Olga Sałagacka
