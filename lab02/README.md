# Graph labs 02

Repository contains solution to tasks listed [here](http://home.agh.edu.pl/~ewach/grafy/Zestaw_2.pdf) (in Polish).
<p>
These are as follows:
<p>
1. Write a program to check if a given sequence is a degree sequence and build a simple graph from it
2. Write a program for randomising simple graphs with a given degree sequence
3. Find a biggest component in a graph
4. Write a program that generated a random Eulerian graph and find Eulerian path in it
5. Write a program for generating random k-regular graphs
6. Write a program that checks if a given graph is hamiltonian


## Running the tests

To run very simple tests type:

```
make run
```

### Description

#### Degree sequences

To generate a random sequence write:

```
unsigned int sequenceLen = 7;
std::vector<unsigned int> sequence = Graph::makeRandomDegreeSequence(sequenceLen);
```

To check if a given sequence can be a degree sequence use a function:
```
Graph::isDegreeSequence(sequence))
```

#### Eulerian graphs
To create an eulerian graph you can read matrix from file like always:

```
Graph eulerianGraph(Undirected);
eulerianGraph.readFile("sample_input_data/eulerianseq.txt");
```

You can also check if generated random degree sequence is eulerian like follows:
```
Graph::isEulerianSequence(sequence);
```

And also check if undirected graph contains Euler Cycle:
```
eulerianGraph.isEulerianCycle();
```

Then you can also convert it to adjacency list:

```
eulerianGraph.convertMatrix(AdjacencyList);
```

#### Random k-regular graphs
To create such a graph simply type:

```
Graph regularGraph(Undirected);

unsigned int minVertices = 6;
unsigned int maxVertices = 6;
unsigned int neighbours = 2;
regularGraph.generateRandomRegular(minVertices, maxVertices, neighbours);
```
It will be saves as an adjacency list.


#### Hamiltonian cycle

To check if a graph has a hamiltonian cycle first you need to create a graph as usual and for example use a `readFile()` function to get a graph matrix. Then, to check if hamitonian cycle is present use:

```
hamilton.checkHamiltonianCycle();
```
This will print the solution.

#### Separate Components

To find compoments simply do:
```
std::vector<unsigned int> components = randomGraph.findComponents();
```

And then to find biggest component:
```
std::vector<unsigned int> biggestComp = randomGraph.biggestComponent();
```

#### Randomization

To randomize graph, simply use
```
void yourGraph.randomize();
```
This may take several attempts to cause a change in edges. It's recommended to perform this multiple times

## Authors

* Mikołaj Skawiński
* Michalina Oleksy
* Mateusz Sacha
* Olga Sałagacka
