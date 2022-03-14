## CMSC858 Bioinformatics Assignment 1

All tasks have been implemented to the specs provided in the assignment. Sample main() functions exist within each of the individual structures CPP files (commented out).

The CSV files contain the unaveraged output per plot from the experiments class.

### To compile the experiments and create the CSV files, run: 
`g++ -std=c++20 -O3 -I ~/include -L ~/lib experiments.cpp -o experiments -lsdsl -ldivsufsort -ldivsufsort64`
Then
`./experiment`

### To see the generated graphs, run: 
`python3 charts.py` 

#### To independently compile the individual RankSupport, SelectSupport, and SparseVector classes:
run: `make` inside the corresponding directory of the structure. A sample main() function exists within each of the .cpp files and has been commented out.
