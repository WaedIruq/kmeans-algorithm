import numpy as np
import sys
import pandas as pd 
import mykmeanssp as kmeans 

def main():
    K = int(sys.argv[1])
    if len(sys.argv) == 6:
        iter = int(sys.argv[2])
        eps = float(sys.argv[3])
        file_name_1 = sys.argv[4]
        file_name_2 = sys.argv[5]
        
    else:
        iter = 300
        eps = float(sys.argv[2])
        file_name_1 = sys.argv[3]
        file_name_2 = sys.argv[4]

    if iter <= 1 or iter >= 1000:
        print("Invalid maximum iteration!")
        return 1
    
    if eps < 0: 
        print("Invalid epsilon!")
        return 1
    df1 = pd.read_csv(file_name_1, sep=',', header=None)
    df2 = pd.read_csv(file_name_2, sep=',', header=None)
    if K <= 1 or (int(K) - K != 0) or len(df1) <= K:
        print("Invalid number of clusters!")
        return 1

    df1.rename(columns={0: 'index'}, inplace=True)
    df2.rename(columns={0: 'index'}, inplace=True)
    result = pd.merge(df1, df2, on='index', how='inner')
    df = result.sort_values(by='index')
    df.drop('index', axis = 1,inplace = True)
    data_points = df.values.tolist()
    centroids = k_centroids_init(data_points, K)
    centroids = kmeans.fit(centroids, data_points, K, iter, eps, len(data_points), len(data_points[0]))
    for centroid in centroids:
            print(",".join(['%.4f' % quard for quard in centroid]))
    return 0


def k_centroids_init(data_points, K):
    np.random.seed(1234)
    centers = []
    distances = []
    centers_indicies = set()
    indecies = [i for i in range(len(data_points))]
    r = np.random.choice(indecies)
    set.add(centers_indicies,r)
    centers.append(data_points[r])
    for i in range(K-1):
        print(str(r), end = ',')
        distances = [min(euclidean_distance(data_points[h],data_points[j]) for h in centers_indicies) for j in range(len(data_points))]
        distances_sum = sum(distances)
        r = np.random.choice(indecies, p=[distances[j]/distances_sum for j in indecies])
        set.add(centers_indicies,r)
        centers.append(data_points[r])    
    print(str(r))
        
    return centers


euclidean_distance = lambda p,q: sum((p[i]-q[i])**2 for i in range(len(p)))**0.5




if __name__ == "__main__":
    main()
        