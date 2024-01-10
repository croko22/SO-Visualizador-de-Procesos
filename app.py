import pandas as pd
import tkinter as tk
from tkinter import ttk
from tkinter import PhotoImage
from tkinter import Label
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

# Función común para cargar el archivo CSV
def load_csv(file_path):
    try:
        df = pd.read_csv(file_path)
        return df
    except Exception as e:
        print(f"Error al cargar el archivo CSV: {e}")
        return None

# Función para mostrar la ventana con opciones específicas para cada algoritmo
def show_algorithm_options(algorithm):
    # Lowercase
    file_path = f'data/{algorithm.lower()}.csv'
    df = load_csv(file_path)

    if df is not None:
        # Crear ventana con opciones específicas para el algoritmo
        window_algorithm = tk.Toplevel()
        window_algorithm.title(f'{algorithm} - Opciones')

        # Agregar botones para la tabla, gráfica y diagrama de Gantt
        button_table = tk.Button(window_algorithm, text='Tabla', command=lambda: show_table(df))
        button_table.pack(side=tk.LEFT, padx=10)

        button_plot = tk.Button(window_algorithm, text='Gráfica', command=lambda: show_plot(df))
        button_plot.pack(side=tk.LEFT, padx=10)

        button_gantt = tk.Button(window_algorithm, text='Diagrama de Gantt', command=lambda: show_gantt(algorithm))
        button_gantt.pack(side=tk.LEFT, padx=10)

# Funciones específicas para cada algoritmo
def show_round_robin():
    show_algorithm_options('RR')

def show_fcfs():
    show_algorithm_options('FCFS')

def show_sjf():
    show_algorithm_options('SJF')

# Funciones comunes para mostrar la tabla, gráfica y diagrama de Gantt
def show_table(df):
    window_table = tk.Toplevel()
    window_table.title('Tabla de Procesos')
    window_table.geometry("800x600")  # Set the window size to 800x600 pixels

    tree = ttk.Treeview(window_table)
    tree["columns"] = tuple(df.columns)
    tree.column("#0", width=0)


    for col in df.columns:
        tree.column(col, anchor="center", width=100)
        tree.heading(col, text=col, anchor="center")

    for index, row in df.iterrows():
        tree.insert("", index, values=tuple(row))

    tree.pack(expand=tk.YES, fill=tk.BOTH)

def show_plot(df):
    fig, ax = plt.subplots()
    ax.plot(df['turnaround_time'], label='Tiempo de ejecución')
    ax.plot(df['waiting_time'], label='Tiempo de espera')
    ax.set_xlabel('Índice del Proceso')
    ax.set_ylabel('Tiempo (segundos)')
    ax.set_title('Tiempo de Ejecución y Tiempo de Espera')
    ax.legend()

    window_plot = tk.Toplevel()
    window_plot.title('Gráfico de Tiempos')

    canvas = FigureCanvasTkAgg(fig, master=window_plot)
    canvas.draw()
    canvas.get_tk_widget().pack(expand=tk.YES, fill=tk.BOTH)

def show_gantt(algorithm):
    window_gantt = tk.Toplevel()
    window_gantt.title('Gantt Chart')

    # Load the image
    img = PhotoImage(file=f'data/{algorithm.lower()}.png')

    # Create a label with the image
    img_label = Label(window_gantt, image=img)
    img_label.image = img  # Keep a reference to the image to prevent it from being garbage collected

    # Add the label to the window
    img_label.pack()

    window_gantt.mainloop()

if __name__ == "__main__":
    root = tk.Tk()
    root.title('Visualizador de Procesos')

    # Agregar botones para seleccionar el algoritmo
    button_round_robin = tk.Button(root, text='Round Robin', command=show_round_robin)
    button_round_robin.pack(side=tk.LEFT, padx=10)

    button_fcfs = tk.Button(root, text='FCFS', command=show_fcfs)
    button_fcfs.pack(side=tk.LEFT, padx=10)

    button_sjf = tk.Button(root, text='SJF', command=show_sjf)
    button_sjf.pack(side=tk.LEFT, padx=10)

    root.mainloop()

