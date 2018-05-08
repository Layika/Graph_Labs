import networkx as nx
import numpy as np
import matplotlib.pyplot as plt

# Set size for plt window, same dimensions because we want to get a cricle in it
plt.figure(figsize=(6,6))

# Create a graph
G = nx.MultiDiGraph(directed=True)

# Read adjacency list from file and make a list of paired edges from it
# Then add it to the graph
# TODO: not the prettiest way, but works... also find a way to
# draw to arrows instead of one
with open("graph.txt") as f:
    lines = f.readlines()
    for i in range(len(lines)):
        line = lines[i].split()
        for j in range(len(line)):
            G.add_edge(str(i+1), line[j])

# Choose some options for the chart
options = {
    'node_color': 'green',
    'node_size': 2000,
    'width': 1,
    'arrowstyle': '-|>',
    'arrowsize': 15,
}

# Draw a graph in a circular layout with arrows
nx.draw(G, pos=nx.circular_layout(G), arrows=True, with_labels=True, **options)

# Display chart with the graph
plt.show()
