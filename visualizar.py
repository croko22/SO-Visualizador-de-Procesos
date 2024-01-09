import tkinter as tk
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

def display_chart(filename, title):
    df = pd.read_csv(filename)
    # Reduce to ten processes
    df = df[:100]

    # Convert timestamps to datetime objects
    df['start_time'] = pd.to_datetime(df['start_time'], unit='ms')
    df['end_time'] = pd.to_datetime(df['end_time'], unit='ms')

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

    ax.xaxis_date()

    plt.title('Diagrama de Gantt para ' + title)
    plt.show()

def fcfs():
    display_chart('fcfs.csv', 'First-Come-First-Serve (FCFS) Scheduling')

def sjf():
    display_chart('sjf.csv', 'Shortest Job First (SJF) Scheduling')

def rr():
    display_chart('rr.csv', 'Round Robin (RR) Scheduling')

root = tk.Tk()
root.geometry('+0+0')

button1 = tk.Button(root, text="FCFS", command=fcfs)
button1.pack()

button2 = tk.Button(root, text="SJF", command=sjf)
button2.pack()

button3 = tk.Button(root, text="RR", command=rr)
button3.pack()

root.mainloop()

