# Running the Project

## Building and Running

1. **Build the Project**:
   - Use the `make` command to compile the source files and create the executable:

   - Alternatively, you can build the project manually using `gcc`:
     gcc -o main main.c  serial.c mutex.c read_write_lock.crandom_numbers.c linked_list.c -lpthread

2. **Run the Executable**:
   - After building, execute the program:
     ./main

## Cleaning Up

1. **Clean Build Artifacts**:
   - To remove object files and the executable, use:
     make clean
