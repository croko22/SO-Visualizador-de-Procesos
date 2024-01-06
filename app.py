import tkinter as tk
from tkinter import ttk
from multiprocessing import Process, Queue
import subprocess
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from matplotlib.animation import FuncAnimation

def run_rr_algorithm(queue):
    process = subprocess.Popen(["./rr_algorithm"], stdout=subprocess.PIPE, text=True)
    for line in process.stdout:
        queue.put(line)
    process.wait()

def update_interface(queue, tree, fig, ax):
    while True:
        try:
            line = queue.get_nowait()
            process_info = line.strip().split("|")
            if len(process_info) == 7:
                tree.insert("", "end", values=process_info[1:-1])
                # Actualizar el gráfico en tiempo real
                update_bar_chart(ax, tree)
        except queue.Empty:
            pass

def update_bar_chart(ax, tree):
    # Obtener datos de la tabla y actualizar el gráfico
    process_names = [item[0] for item in tree.get_children("")]
    burst_times = [int(tree.item(process, "values")[1]) for process in process_names]
    ax.clear()
    ax.bar(process_names, burst_times, color='blue')
    ax.set_ylabel('Tiempo de Ráfaga')
    ax.set_title('Progreso de Ejecución de Procesos')

def main():
    root = tk.Tk()
    root.title("Round Robin Visualization")

    # Crear un Treeview para mostrar la tabla de procesos
    columns = ("Proceso", "Ráfaga", "Tiempo de llegada", "Prioridad", "Tiempo ejecución", "Tiempo espera")
    tree = ttk.Treeview(root, columns=columns, show="headings")
    for col in columns:
        tree.heading(col, text=col)
    tree.pack(expand=True, fill="both")

    # Crear una figura y un eje para el gráfico
    fig, ax = plt.subplots()
    canvas = FigureCanvasTkAgg(fig, master=root)
    widget = canvas.get_tk_widget()
    widget.pack(side=tk.TOP, fill=tk.BOTH, expand=1)

    # Crear una cola para la comunicación entre procesos
    queue = Queue()

    # Iniciar el proceso que ejecuta el algoritmo Round Robin
    rr_process = Process(target=run_rr_algorithm, args=(queue,))
    rr_process.start()

    # Iniciar el proceso que actualiza la interfaz gráfica
    update_process = Process(target=update_interface, args=(queue, tree, fig, ax))
    update_process.start()

    # Configurar el evento para cerrar la aplicación
    root.protocol("WM_DELETE_WINDOW", lambda: root.quit())

    # Ejecutar la aplicación
    root.mainloop()

    # Esperar a que los procesos terminen
    rr_process.join()
    update_process.join()

if __name__ == "__main__":
    main()