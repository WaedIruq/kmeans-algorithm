
# K-Means Clustering Implementation

This repository contains an implementation of the K-Means clustering algorithm using a combination of Python and C. The Python script handles data preprocessing and initialization, while the C code performs the core clustering operations for efficiency.

---

## Files Overview

| File Name        | Description                                      |
|------------------|--------------------------------------------------|
| `kmeans_pp.py`   | Main Python script for K-Means clustering.       |
| `kmeans.c`       | Core K-Means implementation in C.                |
| `kmeansmodule.c` | Python-C bridge for the K-Means implementation.  |
| `setup.py`       | Script to compile the C code into a Python module.|
| `tester.py`      | Script for testing data preprocessing.           |

---

## Installation and Usage

### Prerequisites
- Python 3.x
- C compiler (e.g., GCC)
- `setuptools` and `numpy` Python packages

### Steps to Run the Code

1. **Compile the C Extension**:
   Run the following command to compile the C code into a Python extension:
   ```bash
   python setup.py build_ext --inplace
