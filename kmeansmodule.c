#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>

int kMeansClustering(double **centroids, double **dataPoints, int K, int iter, double eps, int N, int DIM);

static PyObject *fit(PyObject *self, PyObject *args)
{
    PyObject *dataPointsFromPython, *dataPoint;
    PyObject *centroidsFromPython;
    PyObject *item;
    PyObject *finalCentroids;
    double **centroidsForC;
    double **dataPointsForC;
    int i;
    int j;
    int DIM;
    int K;
    int iter;
    double eps;
    int N;
    double point;

    if (!PyArg_ParseTuple(args, "OOiidii", &centroidsFromPython, &dataPointsFromPython, &K, &iter, &eps, &N, &DIM))
        return NULL;
    dataPointsForC = (double **)calloc(N, sizeof(double *));
    for (i = 0; i < N; i++)
    {
        dataPointsForC[i] = (double *)calloc(DIM, sizeof(double));
        dataPoint = PyList_GetItem(dataPointsFromPython, i);
        if (!PyList_Check(dataPoint))
        {
            PyErr_SetString(PyExc_TypeError, "Expected a list of lists\n");
            return NULL;
        }

        for (j = 0; j < DIM; j++)
        {
            item = PyList_GetItem(dataPoint, j);

            if (!PyFloat_Check(item))
            {
                PyErr_SetString(PyExc_TypeError, "Expected a float\n");
                return NULL;
            }
            point = (double)PyFloat_AsDouble(item);
            dataPointsForC[i][j] = point;
        }
    }
    centroidsForC = (double **)calloc(K, sizeof(double *));
    for (i = 0; i < K; i++)
    {
        centroidsForC[i] = (double *)calloc(DIM, sizeof(double));
        dataPoint = PyList_GetItem(centroidsFromPython, i);
        if (!PyList_Check(dataPoint))
        {
            PyErr_SetString(PyExc_TypeError, "Expected a list of lists");
            return NULL;
        }
        for (j = 0; j < DIM; j++)
        {
            item = PyList_GetItem(dataPoint, j);
            if (!PyFloat_Check(item))
            {
                PyErr_SetString(PyExc_TypeError, "Expected a float");
                return NULL;
            }
            point = PyFloat_AsDouble(item);
            centroidsForC[i][j] = point;
        }
    }

    kMeansClustering(centroidsForC, dataPointsForC, K, iter, eps, N, DIM);

    finalCentroids = PyList_New(K);
    for (i = 0; i < K; i++)
    {
        dataPoint = PyList_New(DIM);
        for (j = 0; j < DIM; j++)
        {
            PyList_SetItem(dataPoint, j, Py_BuildValue("d", centroidsForC[i][j]));
        }

        PyList_SetItem(finalCentroids, i, dataPoint);
    }

    for (i = 0; i < K; i++)
    {
        free(centroidsForC[i]);
    }
    free(centroidsForC);

    for (i = 0; i < N; i++)
    {
        free(dataPointsForC[i]);
    }
    free(dataPointsForC);

    return finalCentroids;
}

static PyMethodDef fit_FunctionTable[] = {
    {"fit", fit, METH_VARARGS, "NO DOCUMENTATION NEEDED"},
    {NULL, NULL, 0, NULL}};

static struct PyModuleDef fit_Module = {
    PyModuleDef_HEAD_INIT, "mykmeanssp",
    "fit Python wrapper for custom C extension library.",
    -1,
    fit_FunctionTable};

PyMODINIT_FUNC PyInit_mykmeanssp(void)
{

    return PyModule_Create(&fit_Module);
}
        