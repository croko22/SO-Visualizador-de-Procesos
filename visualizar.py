import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from datetime import datetime
import pandas as pd

# df = pd.DataFrame(data)
df = pd.read_csv('fcfs.csv')
df.describe()

# Reduce to ten processes
df = df[:10]

# Convert timestamps to datetime objects
df['start_time'] = pd.to_datetime(df['start_time'], unit='ms')
df['end_time'] = pd.to_datetime(df['end_time'], unit='ms')

# Creating Gantt Chart
fig, ax = plt.subplots(figsize=(10, 6))

for i, row in df.iterrows():
    ax.barh(y=row['pid'], width=(row['end_time'] - row['start_time']),
            left=row['start_time'], color='blue')

# Formatting the plot
ax.set_xlabel('Time')
ax.set_ylabel('Process ID')

# Use automatic date formatting
ax.xaxis_date()

plt.title('Gantt Chart')
plt.show()
