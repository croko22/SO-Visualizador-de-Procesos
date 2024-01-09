option=$1

case $option in
    all)
        gcc main.c  src/procesos.h src/procesos.c  && ./a.out && python visualizar.py
        ;;
    c) 
        gcc main.c  src/procesos.h src/procesos.c  && ./a.out
        ;;
    py)
        python visualizar.py
        ;;
    *)
        echo "Invalid option. Use 'all' to compile and run all, or 'py' to run just the Python script."
        ;;
esac 