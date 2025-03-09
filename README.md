
#K-Means Clustering Implementation
This repository contains an implementation of the K-Means clustering algorithm using a combination of Python and C. The Python script handles data preprocessing and initialization, while the C code performs the core clustering operations for efficiency.

Files Overview

1. kmeans_pp.py

This is the main Python script that:

Reads input data from two CSV files.
Merges and sorts the data based on an index column.
Initializes centroids using the K-Means++ algorithm.
Calls the C extension to perform the K-Means clustering.
Outputs the final centroids.
2. kmeans.c

This C file contains the core implementation of the K-Means algorithm:

Computes Euclidean distances.
Assigns data points to the nearest cluster.
Updates centroids based on the mean of the assigned points.
Iterates until convergence or the maximum number of iterations is reached.
3. kmeansmodule.c

This file acts as a bridge between Python and C:

Defines a Python module mykmeanssp that can be imported in Python.
Converts Python data structures (lists) to C arrays.
Calls the K-Means clustering function from kmeans.c.
Returns the final centroids to Python.
4. setup.py

This script is used to compile the C code into a Python extension:

Compiles kmeansmodule.c and kmeans.c into a shared library.
Creates a Python module named mykmeanssp.
5. tester.py

This script is used for testing the implementation:

Reads input data from two CSV files.
Merges and sorts the data.
Converts the data into a list of points for clustering.
Installation and Usage

Prerequisites

Python 3.x
C compiler (e.g., GCC)
setuptools and numpy Python packages
Steps to Run the Code

Compile the C Extension:
Run the following command to compile the C code into a Python extension:
bash
Copy
python setup.py build_ext --inplace
Run the K-Means Clustering:
Use the kmeans_pp.py script to perform clustering. The script takes the following arguments:
K: Number of clusters.
iter: Maximum number of iterations (optional, default is 300).
eps: Convergence threshold (optional, default is 0).
file_name_1: Path to the first input CSV file.
file_name_2: Path to the second input CSV file.
Example command:
bash
Copy
python kmeans_pp.py 3 100 0.01 input1.csv input2.csv
Testing:
Use the tester.py script to test the data preprocessing steps. It reads input files and prepares the data for clustering.
Input Data Format

The input CSV files should have the following format:

The first column should be an index column.
The remaining columns should contain the data points.
Example:

Copy
index,feature1,feature2
1,0.5,1.2
2,1.3,2.4
3,2.1,3.6
