Goal of the code

- Implement an efficient parallel sorting algorithm usign MPI
- Measure the performance scaling with 1m to 100m integer data elements.


Code Structure
- MergSort.cpp this is merge sort that support parallelization using MPI.
- Serial.cpp this merge sort for serial execution.
- run_mpi_multi.sh I am running the parallelization using slurm bash for resource and load management.

Requirements
- MPI
- C++

How to run parallel code
- Run mpic++ -o mergesort MergeSort.cpp to compile the cpp code.
- sbatch -o <OutPutFile> run_mpi_multi.sh ./mergesort <ARRAY SIZE>

To run the serial code
- Run mpic++ -o serialMergeSort serial.cpp to compile the cpp code.
- srun -n 1 -o <OutPutFile> ./serialMergeSort <ARRAY SIZE>

