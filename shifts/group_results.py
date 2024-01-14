import os
import pandas as pd

# Set the path to the directory containing your CSV files
directory_path = os.getcwd()

# Create an empty DataFrame to store the combined data
combined_data = pd.DataFrame()

# Loop through each CSV file in the directory
for i in range(1, 10):
    filename = str(directory_path) + "/id_" + str(i) + ".csv"
    if filename.endswith(".csv"):
        # Read the CSV file into a DataFrame
        file_path = os.path.join(directory_path, filename)
        df = pd.read_csv(file_path, header=None, names=["id_" + str(i)])
        # Concatenate the data to the combined DataFrame
        combined_data = pd.concat([combined_data, df], axis=1)

# Write the combined DataFrame to a new CSV file
fname = directory_path + "combined.csv"
combined_data.to_csv(fname, index=False)
