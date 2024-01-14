# groups .csv files called 'id_*.csv' (* from 1 to 9)
# into a single .csv file with headers corresponding to the filename 

import os
import pandas as pd

directory_path = os.getcwd()
combined_data = pd.DataFrame()

for i in range(1, 10):
    filename = str(directory_path) + "/id_" + str(i) + ".csv"
    if filename.endswith(".csv"):
        
        file_path = os.path.join(directory_path, filename)
        df = pd.read_csv(file_path, header=None, names=["id_" + str(i)])
        
        combined_data = pd.concat([combined_data, df], axis=1)

fname = directory_path + "/combined.csv"
combined_data.to_csv(fname, index=False)
