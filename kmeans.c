#include <math.h>
#include <stdlib.h>
#include <stdio.h>

int N;
int DIM;
int K;
struct Cluster
{
    double **data;
    int len;
};

double euclideanDistance(double *p, double *q);
double *strToFloatArray(char *str);
int findClosestCluster(double *point, double **centroids);
void assignClusters(struct Cluster *clusters, double **dataPoints, double **centroids);
double **updateCentroids(struct Cluster *clusters);
void copyArray(double *dest, double *src, int len);
int kMeansClustering(double **centroids, double **dataPoints, int K, int iter, double eps, int N, int DIM);
double updateDelta(double **centroids, double **updatedCentroids);

int main()
{
    return 0;
}

int kMeansClustering(double **centroids, double **dataPoints, int k, int iter, double eps, int n, int dim)
{
    int it, i, j, d;
    struct Cluster *clusters;
    double **updatedCentroids;
    double maxDeltaMeu;
    size_t size;

    maxDeltaMeu = 1;
    K = k;
    N = n;
    DIM = dim;
    size = (size_t)N / K;
    it = 0;
    while (maxDeltaMeu >= eps && it < iter)
    {
        clusters = (struct Cluster *)malloc(K * sizeof(struct Cluster));
        for (i = 0; i < K; i++)
        {
            clusters[i].data = (double **)calloc(size, sizeof(double *));
            clusters[i].len = 0;
        }
        assignClusters(clusters, dataPoints, centroids);
        updatedCentroids = updateCentroids(clusters);
        for (i = 0; i < K; i++)
        {
            for (j = 0; j < clusters[i].len; j++)
            {
                free(clusters[i].data[j]);
            }
            free(clusters[i].data);
        }
        free(clusters);
        maxDeltaMeu = updateDelta(centroids, updatedCentroids);
        it++;

        for (j = 0; j < K; j++)
        {
            for (d = 0; d < DIM; d++)
            {
                centroids[j][d] = updatedCentroids[j][d];
            }
        }

        for (j = 0; j < K; j++)
        {
            free(updatedCentroids[j]);
        }
        free(updatedCentroids);
    }

    return 0;
}

double updateDelta(double **centroids, double **updatedCentroids)
{
    int i;
    double maxMeu, meu;
    maxMeu = 0;
    i = 0;
    for (i = 0; i < K; i++)
    {
        meu = euclideanDistance(centroids[i], updatedCentroids[i]);
        if (meu > maxMeu)
        {
            maxMeu = meu;
        }
    }
    return maxMeu;
}

double euclideanDistance(double *p, double *q)
{
    int i = 0;
    double sum = 0.0;
    for (i = 0; i < DIM; i++)
    {
        sum += pow(p[i] - q[i], 2.0);
    }
    return sqrt(sum);
}

int findClosestCluster(double *point, double **centroids)
{
    int i;
    double minDist;
    int minIndex;
    double dist;
    i = 1;
    minDist = euclideanDistance(point, centroids[0]);
    minIndex = 0;
    for (i = 1; i < K; i++)
    {
        dist = euclideanDistance(point, centroids[i]);
        if (dist < minDist)
        {
            minDist = dist;
            minIndex = i;
        }
    }
    return minIndex;
}

void assignClusters(struct Cluster *clusters, double **dataPoints, double **centroids)
{
    int i, d;
    int closestIndex;
    for (i = 0; i < N; i++)
    {
        closestIndex = findClosestCluster(dataPoints[i], centroids);
        ;
        if (clusters[closestIndex].len >= (int)N / K)
        {
            clusters[closestIndex].data = (double **)realloc(clusters[closestIndex].data, (clusters[closestIndex].len + 1) * sizeof(double *));
        }
        clusters[closestIndex].data[clusters[closestIndex].len] = (double *)malloc(DIM * sizeof(double));

        for (d = 0; d < DIM; d++)
        {
            clusters[closestIndex].data[clusters[closestIndex].len][d] = dataPoints[i][d];
        }
        clusters[closestIndex].len++;
    }
    return;
}

double **updateCentroids(struct Cluster *clusters)
{
    int i, d, j;
    double **centroids;
    centroids = (double **)malloc(K * sizeof(double *));
    for (i = 0; i < K; i++)
    {
        centroids[i] = (double *)calloc(DIM, sizeof(double));
    }

    for (i = 0; i < K; i++)
    {
        for (j = 0; j < clusters[i].len; j++)
        {
            for (d = 0; d < DIM; d++)
            {
                centroids[i][d] += clusters[i].data[j][d];
            }
        }
        for (d = 0; d < DIM; d++)
        {
            centroids[i][d] /= clusters[i].len;
        }
    }

    return centroids;
}

void copyArray(double *dest, double *src, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        dest[i] = src[i];
    }
}

double *strToFloatArray(char *str)
{
    char numBuffer[64];
    double *numbers;
    int j, i, k, dim;
    j = 0;
    dim = 1;
    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ',')
        {
            dim += 1;
        }
        i++;
    }
    DIM = dim;

    numbers = (double *)calloc(dim, sizeof(double));

    k = 0;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == ',')
        {
            numBuffer[k] = '\0';
            numbers[j++] = atof(numBuffer);
            k = 0;
        }
        else
        {
            numBuffer[k++] = str[i];
        }
        i++;
    }
    numBuffer[k] = '\0';
    numbers[j] = atof(numBuffer);

    return numbers;
}