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

#### Weights

Weights are stored in the 'weights' member of the Graph class, including their source and destination vertices. <br />
To get weight of an edge between vertex A and B, use:
```
yourGraph.getWeight(A, B);
```
If such edge is not registered in 'weights' vector, -1 will be returned;

To set a new weight value for an edge between vertex A and B, use:

```
yourGraph.setWeight(A, B, weight);
```
If such edge is not registered in 'weights' vector, a new value will be added.

To generate random weight values from x to y for every edge, use:
```
yourGraph.generateRandomWeights(x, y);
```
When performing changes on the graph (such as adding or removing edges) the 'weights' might become desynchronized with the actual graph. To fix it, simply use:
```
yourGraph.updateWeights();
```
This will remove weights for edges that don't exist anymore, and add new weight values for newly added edges.

Finally, to print weight values along with their corresponding edges, type:
```
yourGraph.printWeights();
```


#### Shortest paths

To find and print shortest paths from vertex v to every other vertex, use:

```
std::vector<int> distances = yourGraph.Dijkstra(v+1, true);
```
The 'distances' vector will hold minimum distances to each vertex.

## Authors

* Mikołaj Skawiński
* Michalina Oleksy
* Mateusz Sacha
* Olga Sałagacka
