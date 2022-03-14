import pandas as pd
import numpy as np
from icecream import ic
import matplotlib.pyplot as plt

p1_create_pd = pd.read_csv("p1_create.csv")
p1_query_pd = pd.read_csv("p1_query.csv")
p1_overhead_pd = pd.read_csv("p1_overhead.csv")
p1_plots = [p1_create_pd, p1_query_pd, p1_overhead_pd]

p1_create_final_pd = pd.DataFrame(columns=['Size', 'Time'])
p1_query_final_pd = pd.DataFrame(columns=['Size', 'Time'])
p1_overhead_final_pd = pd.DataFrame(columns=['Size', 'Overhead'])
p1_final_plots = [p1_create_final_pd, p1_query_final_pd, p1_overhead_final_pd]

sizes = [1000, 10000, 100000, 1000000]


for size in sizes:
    time_avg = p1_create_pd.loc[p1_create_pd['Size'] == size]["Time"].mean()
    p1_create_final_pd.loc[len(p1_create_final_pd.index)] = [size, time_avg]
ic(p1_create_final_pd)
p1_create_final_pd.plot(x='Size', y='Time', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="Creation of Rank Support (Time x Size)", logx=True)
plt.show()

for size in sizes:
    time_avg = p1_query_pd.loc[p1_query_pd['Size'] == size]["Time"].mean()
    p1_query_final_pd.loc[len(p1_query_final_pd.index)] = [size, time_avg]
ic(p1_query_final_pd)
p1_query_final_pd.plot(x='Size', y='Time', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="Avg of 10 Random Rank Queries (Time x Size)", logx=True)
plt.show()

for size in sizes:
    time_avg = p1_overhead_pd.loc[p1_overhead_pd['Size'] == size]["Overhead"].mean()
    p1_overhead_final_pd.loc[len(p1_overhead_final_pd.index)] = [size, time_avg]
ic(p1_overhead_final_pd)
p1_overhead_final_pd.plot(x='Size', y='Overhead', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="Overhead of Rank Support (Overhead x Size)", logx=True)
plt.show()

p2_create_pd = pd.read_csv("p2_create.csv")
p2_query_pd = pd.read_csv("p2_query.csv")
p2_overhead_pd = pd.read_csv("p2_overhead.csv")
p2_plots = [p2_create_pd, p2_query_pd, p2_overhead_pd]

p2_create_final_pd = pd.DataFrame(columns=['Size', 'Time'])
p2_query_final_pd = pd.DataFrame(columns=['Size', 'Time'])
p2_overhead_final_pd = pd.DataFrame(columns=['Size', 'Overhead'])
p2_final_plots = [p2_create_final_pd, p2_query_final_pd, p2_overhead_final_pd]

sizes = [1000, 10000, 100000, 1000000]


for size in sizes:
    time_avg = p2_create_pd.loc[p2_create_pd['Size'] == size]["Time"].mean()
    p2_create_final_pd.loc[len(p2_create_final_pd.index)] = [size, time_avg]
ic(p2_create_final_pd)
p2_create_final_pd.plot(x='Size', y='Time', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="Creation of Select Support (Time x Size)", logx=True)
plt.show()

for size in sizes:
    time_avg = p2_query_pd.loc[p2_query_pd['Size'] == size]["Time"].mean()
    p2_query_final_pd.loc[len(p2_query_final_pd.index)] = [size, time_avg]
ic(p2_query_final_pd)
p2_query_final_pd.plot(x='Size', y='Time', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="Avg of 10 Random Select Queries (Time x Size)", logx=True)
plt.show()

for size in sizes:
    time_avg = p2_overhead_pd.loc[p2_overhead_pd['Size'] == size]["Overhead"].mean()
    p2_overhead_final_pd.loc[len(p2_overhead_final_pd.index)] = [size, time_avg]
ic(p2_overhead_final_pd)
p2_overhead_final_pd.plot( x='Size', y='Overhead', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="Overhead of Select Support (Overhead x Size)", logx=True)
plt.show()

p3_getAtRank_pd = pd.read_csv("p3_getAtRank.csv")
p3_getAtIndex_pd = pd.read_csv("p3_getAtIndex.csv")
p3_numElAt_pd = pd.read_csv("p3_numElAt.csv")
p3_plots = [p3_getAtRank_pd, p3_getAtIndex_pd, p3_numElAt_pd]

p3_getAtRank_final_pd = pd.DataFrame(columns=['Size', 'Time', 'Sparsity'])
p3_getAtIndex_final_pd = pd.DataFrame(columns=['Size', 'Time', 'Sparsity'])
p3_numElAt_final_pd = pd.DataFrame(columns=['Size', 'Time', 'Sparsity'])
p3_final_plots = [p3_getAtRank_final_pd, p3_getAtIndex_final_pd, p3_numElAt_final_pd]

sizes = [1000, 10000, 100000, 1000000]
sparsity = [0.01, 0.05, 0.1]

for sparse in sparsity:
    for size in sizes:
        time_avg = p3_getAtRank_pd.loc[(p3_getAtRank_pd['Size'] == size) & (p3_getAtRank_pd['Sparsity'] == sparse)]["Time"].mean()
        p3_getAtRank_final_pd.loc[len(p3_getAtRank_final_pd.index)] = [size, time_avg, sparse]
        #p3_getAtRank_final_pd.subplot(x='Size', y='Time', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="getAtRank")
#p3_getAtRank_final_pd = p3_getAtRank_final_pd.pivot(columns=['Time', 'Size'], values='Sparsity')
#df.plot(color=df.columns, figsize=(5, 3))
ic(p3_getAtRank_final_pd)

fig, ax = plt.subplots()

for key, grp in p3_getAtRank_final_pd.groupby(['Sparsity']):
    ax = grp.plot(ax=ax, kind='line', x='Size', y='Time', label=key, title="Avg Random getAtRank Calls, Time vs Size, by Sparsity (Color)", marker='o', logx=True)

plt.legend(loc='best')
plt.show()



for sparse in sparsity:
    for size in sizes:
        time_avg = p3_getAtIndex_pd.loc[(p3_getAtIndex_pd['Size'] == size) & (p3_getAtIndex_pd['Sparsity'] == sparse)]["Time"].mean()
        p3_getAtIndex_final_pd.loc[len(p3_getAtIndex_final_pd.index)] = [size, time_avg, sparse]
        #p3_getAtRank_final_pd.subplot(x='Size', y='Time', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="getAtRank")
#p3_getAtRank_final_pd = p3_getAtRank_final_pd.pivot(columns=['Time', 'Size'], values='Sparsity')
#df.plot(color=df.columns, figsize=(5, 3))
ic(p3_getAtIndex_final_pd)

fig, ax = plt.subplots()

for key, grp in p3_getAtIndex_final_pd.groupby(['Sparsity']):
    ax = grp.plot(ax=ax, kind='line', x='Size', y='Time', label=key, title="Avg Random getAtIndex Calls, Time vs Size, by Sparsity (Color)", marker='o', logx=True)

plt.legend(loc='best')
plt.show()


for sparse in sparsity:
    for size in sizes:
        time_avg = p3_numElAt_pd.loc[(p3_numElAt_pd['Size'] == size) & (p3_numElAt_pd['Sparsity'] == sparse)]["Overhead"].mean()
        p3_numElAt_final_pd.loc[len(p3_numElAt_final_pd.index)] = [size, time_avg, sparse]
        #p3_getAtRank_final_pd.subplot(x='Size', y='Time', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="getAtRank")
#p3_getAtRank_final_pd = p3_getAtRank_final_pd.pivot(columns=['Time', 'Size'], values='Sparsity')
#df.plot(color=df.columns, figsize=(5, 3))
ic(p3_numElAt_final_pd)

fig, ax = plt.subplots()

for key, grp in p3_numElAt_final_pd.groupby(['Sparsity']):
    ax = grp.plot(ax=ax, kind='line', x='Size', y='Time', label=key, title="Avg Random numElAt Calls, Time vs Size, by Sparsity (Color)", marker='o', logx=True)

plt.legend(loc='best')
plt.show()

#df.plot(color=df.columns, figsize=(5, 3))
#p3_getAtRank_final_pd.plot(x='Size', y='Time', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="getAtRank")

#fig, ax = plt.subplots()
#for key, grp in p3_getAtRank_final_pd.groupby(['Sparsity']):
#    ax = grp.plot(ax=ax, kind='line', x='Size', y='Time', c=key, label=key)
#p3_getAtRank_final_pd.plot(color='Sparsity', x='Size', y='Time', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="getAtRank")
#plt.show()
#
#for size in sizes:
#    time_avg = p3_getAtIndex_pd.loc[p3_getAtIndex_pd['Size'] == size]["Time"].mean()
#    p3_getAtIndex_final_pd.loc[len(p3_getAtIndex_final_pd.index)] = [size, time_avg, sparse]
#ic(p3_getAtIndex_final_pd)
#p3_getAtIndex_final_pd.plot(x='Size', y='Time', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="Avg of 10 Random Select Queries (Time x Size)")
#plt.show()
#
#for size in sizes:
#    time_avg = p3_numElAt_pd.loc[p3_numElAt_pd['Size'] == size]["Overhead"].mean()
#    p3_numElAt_final_pd.loc[len(p3_numElAt_final_pd.index)] = [size, time_avg, sparse]
#ic(p3_numElAt_final_pd)
#p3_numElAt_final_pd.plot( x='Size', y='Overhead', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="Overhead of Select Support (Overhead x Size)")
#plt.show()
##ctr = 0
##for plot, final_plot in zip(p1_plots, p1_final_plots):
#    for size in sizes:
#        if (ctr == 2):
#            time_avg = plot.loc[plot['Size'] == size]["Overhead"].mean()
#        else:
#            time_avg = plot.loc[plot['Size'] == size]["Time"].mean()
#        final_plot.loc[len(final_plot.index)] = [size, time_avg]
#        #time_avg = p1_create_pd.loc[p1_create_pd['Size'] == size]["Time"].mean()
#        #p1_create_final_pd.loc[len(p1_create_final_pd.index)] = [size, time_avg]
#    ctr += 1
#    #p1_create_pd.loc[p1_create_pd['Size'] == size]["Time"].mean()
#
#ic(p1_create_final_pd)
#p1_create_final_pd.plot(x='Size', y='Time', kind = 'line', marker='o', ylabel = 'Time (milliseconds)', title="Creation of Rank Support (Time x Size)")
##plt.xticks(sizes, sizes_string)
#plt.show()
