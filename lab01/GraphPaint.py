import networkx as nx
import numpy as np
import matplotlib.pyplot as plt

plt.figure(figsize=(6,6))

G = nx.DiGraph(directed=True)

with open("out.txt") as f:
    lines = f.readlines()
    
G.add_edges_from(
    [('1', '5'), ('1', '2'), ('5', '2'), ('5', '4'), ('2', '4'),
     ('2', '3'), ('3', '4')])

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
