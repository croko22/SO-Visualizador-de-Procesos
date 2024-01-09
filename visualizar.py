import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from datetime import datetime
import pandas as pd


# Get user input
print("Seleccione el algoritmo que desea utilizar:")
print("1. FCFS")
print("2. SJF")
print("3. RR")
choice = input("Ingrese el número del algoritmo: ")

# Execute the chosen algorithm
if choice == '1':
    df = pd.read_csv('fcfs.csv')
    title = 'First-Come-First-Serve (FCFS) Scheduling'
elif choice == '2':
    df = pd.read_csv('sjf.csv')
    title = 'Shortest Job First (SJF) Scheduling'
elif choice == '3':
    df = pd.read_csv('rr.csv')
    title = 'Round Robin (RR) Scheduling'
else:
    print("Opción no válida. Por favor, ingrese un número del 1 al 3.")

# Reduce to ten processes
df = df[:20]

# Convert timestamps to datetime objects
df['start_time'] = pd.to_datetime(df['start_time'], unit='ms')
df['end_time'] = pd.to_datetime(df['end_time'], unit='ms')

# Creating Gantt Chart
# fig, ax = plt.subplots(figsize=(10, 6))

# for i, row in df.iterrows():
#     ax.barh(y=row['pid'], width=(row['end_time'] - row['start_time']),
#             left=row['start_time'], color='blue')

# Creating Gantt Chart
fig, ax = plt.subplots(figsize=(10, 30))  # Increase the height of the figure

bar_height = 0.5  # Adjust the bar height to fit more processes
y_ticks = []  # List to store the y-tick labels

for i, row in df.iterrows():
    ax.barh(y=i, width=(row['end_time'] - row['start_time']),
            left=row['start_time'], height=bar_height, color='blue')
    y_ticks.append(row['pid'])

ax.set_ylim(-0.5, len(df) - 0.5)  # Set the y-axis limits
ax.set_yticks(range(len(df)))  # Set the y-tick positions
ax.set_yticklabels(y_ticks)  

# Formateando el gráfico
ax.set_xlabel('Tiempo')
ax.set_ylabel('ID del Proceso')

# Usar formato de fecha automático
ax.xaxis_date()

plt.title('Diagrama de Gantt para ' + title)
plt.show()
