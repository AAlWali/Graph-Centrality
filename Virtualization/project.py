import matplotlib.pyplot as plt
import networkx as nx
import warnings
from matplotlib.cbook.deprecation import MatplotlibDeprecationWarning
warnings.filterwarnings("ignore", category=MatplotlibDeprecationWarning)

mylines = []
src=[]
des=[]
wt=[]
nums = []
node_sizes=[]
with open('input.txt', 'rt') as myfile:  # Open file input.txt for reading text
    for line in myfile:                   # For each line of text,
        mylines.append(line.rstrip('\n')) # add that line to the list.
    for i in range(len(mylines)):
        nums.append(mylines[i].split())

nums = [i for b in map(lambda x:[x] if not isinstance(x, list) else x, nums) for i in b]
for i in range(0, len(nums), 3):src.append(nums[i])
for i in range(0, len(nums), 3):des.append(nums[i+1])
for i in range(0, len(nums), 3):wt.append(nums[i+2])
wt = list(map(float, wt))
G = nx.Graph()
for i in range(len(mylines)):
    G.add_edge(src[i], des[i], weight=wt[i])
pos = nx.spring_layout(G)
nx.draw_networkx_edges(G, pos, width=3)
d= [val for (node, val) in G.degree()]
for n in d:node_sizes.append( 1000 * n )
nx.draw_networkx_nodes(G, pos, node_size=node_sizes)
# labels
nx.draw_networkx_labels(G, pos, font_size=15, font_family='sans-serif')
labels = nx.get_edge_attributes(G,'weight')
nx.draw_networkx_edge_labels(G,pos,edge_labels=labels)
plt.axis('off')
plt.show()
plt.save('out.png')
print(d)
