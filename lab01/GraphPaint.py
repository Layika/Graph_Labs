import networkx as nx
import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(6,6))

G = nx.MultiDiGraph(directed=True)

# TODO: not the prettiest way, but works... also find a way to
# draw to arrows instead of one
with open("out.txt") as f:
    lines = f.readlines()
    for i in range(len(lines)):
        line = lines[i].split()
        for j in range(len(line)):
            G.add_edge(str(i+1), line[j])


options = {
    'node_color': 'green',
    'node_size': 2000,
    'width': 1,
    'arrowstyle': '-|>',
    'arrowsize': 15,
}

pos = nx.circular_layout(G)
nx.draw(G, pos=nx.circular_layout(G), arrows=True, with_labels=True, **options)


plt.show()
