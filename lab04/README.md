# Graph labs 03

Repository contains solution to tasks listed [here](http://home.agh.edu.pl/~ewach/grafy/Zestaw_3.pdf) (in Polish).
<p>
These are as follows:
<p>
1. Generate a random connected graph. Assign a weight for every edge with a random value of 1 - 10 <br />
2. Implement Dijkstra's algorithm to find and print shortest paths from one vertex to every other <br />
3. Generate a matrix of shortest path distances for every vertex-to-vertex pair <br />
4. Find graph's center, where the sum of minimal distances to every other vertex is minimal <br />
5. Generate a minimum spanning tree using either Prim's of Kruskal's algorithm <br />


## Running the tests

To run very simple tests type:

```
make run
```

### Description

#### Randon directed graph G(n,p)

To create a directed graph simply type:

```
Graph directedRandomGraph(Directed);
```

Then you can make a random G(n,p) graph out of it. Create also variables for holding vertices number and probability as the function creating G(n,p) graph saves there random numbers it chose. You can also give it minumim and maximum number of vertices as well as probability.

```
int minVertices = 6;
int maxVertices = 10;
int minProbability = 5;
int maxProbability = 10;

int chosenVertices, chosenPprobability;
directedRandomGraph.generateRandomNP(minVertices, maxVertices, minProbability, maxProbability, chosenVertices, chosenProbability);
```

In order to display this graph first save it:

```
 directedRandomGraph.saveGraph("directedRandomGraph.txt");
```

And then check `GraphPaint.py` script to check if it has `arrows=True`. If this variable is set to `False` then change it. Then run this script as follows:

```
python3 GraphPaint.py directedRandomGraph.txt
```


## Authors

* Mikołaj Skawiński
* Michalina Oleksy
* Mateusz Sacha
* Olga Sałagacka
