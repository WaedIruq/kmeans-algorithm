import pandas as pd

file_name_1 = "tests/input_1_db_1.txt"
file_name_2 = "tests/input_1_db_2.txt"

df1 = pd.read_csv(file_name_1, sep=',', header=None)
df2 = pd.read_csv(file_name_2, sep=',', header=None)
df1.rename(columns={0: 'index'}, inplace=True)
df2.rename(columns={0: 'index'}, inplace=True)
result = pd.merge(df1, df2, on='index', how='inner')
df = result.sort_values(by='index')
df.drop('index', axis = 1, inplace=True)
dataPoints = df.values.tolist()