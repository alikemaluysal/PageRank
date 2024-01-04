import numpy as np
import matplotlib.pyplot as plt
import networkx as nx

NUM_PAGES = 4
DAMPING_FACTOR = 0.85
NUM_ITERATIONS = 10

link_matrix = np.array([
    [0, 1, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 0, 0],
    [1, 1, 1, 0]
])

G = nx.DiGraph(link_matrix)

layout = nx.spring_layout(G)
plt.figure(figsize=(16, 12))
node_size = 12500
node_color = 'lightblue'

nx.draw(G, with_labels=True, node_color=node_color, node_size = node_size)
plt.title("Initial Network")
plt.savefig(f"pagerank_images/{0}.png")

plt.show()


def compute_pagerank(link_matrix, num_iterations, damping_factor):
    N = link_matrix.shape[0]
    pageRank = np.ones(N) / N
    for _ in range(num_iterations):
        newPageRank = np.zeros(N)
        for i in range(N):
            for j in range(N):
                if link_matrix[j, i] > 0:
                    newPageRank[i] += damping_factor * pageRank[j] / np.sum(link_matrix[j, :])
            newPageRank[i] += (1.0 - damping_factor) / N
        pageRank = newPageRank
    return pageRank

def visualize_pagerank(link_matrix, pageRank, iteration):
    G = nx.DiGraph(link_matrix)
    layout = nx.spring_layout(G)
    plt.figure(figsize=(16, 12))
    node_size = [v * 50000 for v in pageRank]
    node_color = [(1.0 - v) * 20000 for v in pageRank]

    nx.draw(G, layout, with_labels=True, node_size=node_size, 
            node_color= node_color, alpha=0.7, edge_color='.4')
    plt.title(f"Iteration {iteration}: PageRank")

    plt.savefig(f"pagerank_images/{iteration}.png")
    
    plt.show()

for iteration in range(1, NUM_ITERATIONS + 1):
    pageRank = compute_pagerank(link_matrix, iteration, DAMPING_FACTOR)
    visualize_pagerank(link_matrix, pageRank, iteration)
