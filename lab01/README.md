# Graph labs 01

Repository contains solution to tasks listed [here](http://home.agh.edu.pl/~ewach/grafy/Zestaw_1.pdf) (in Polish).
These are as follows:
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
Then run the script as follows:

```
python3 GraphPaint.py data.txt
```
You can save generated picture if you like, just press saving icon.


### Graph implementation




## Authors

* Mikołaj Skawiński
* Michalina Oleksy
* Mateusz Sacha
* Olga Sałagacka
