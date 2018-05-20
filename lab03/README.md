# Graph labs 03

Repository contains solution to tasks listed [here](http://home.agh.edu.pl/~ewach/grafy/Zestaw_3.pdf) (in Polish).
<p>
These are as follows:
<p>
1. Generate a random connected graph. Assign a weight for every edge with a random value of 1 - 10
2. Implement Dijkstra's algorithm to find and print shortest paths from one vertex to every other
3. Generate a matrix of shortest path distances for every vertex-to-vertex pair
4. Find graph's center, where the sum of minimal distances to every other vertex is minimal
5. Generate a minimum spanning tree using either Prim's of Kruskal's algorithm


## Running the tests

To run very simple tests type:

```
make run
```

### Description

#### Shortest paths

To find and print shortest paths from vertex v to every other vertex, use:

```
std::vector<int> distances = graph.Dijkstra(v+1, true);
```
The 'distances' vector will hold minimum distances to each vertex.

## Authors

* Mikołaj Skawiński
* Michalina Oleksy
* Mateusz Sacha
* Olga Sałagacka
