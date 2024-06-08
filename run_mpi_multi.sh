#!/bin/bash
## Example SLURM helper for running MIMD MPI programs 
## 
## usage: 
##   sbatch run_mpi.sh my_mpi_program <ARRAY SIZE>

#SBATCH -o std.out
#SBATCH -e std.err
#SBATCH -n 8	

MPI_PROGRAM=$1
ARRAY_SIZE=$2

if [ -z "$ARRAY_SIZE" ]; then
  echo "Array size not specified."
  exit -1
fi

if [ -z "$MPI_PROGRAM" ];then
   echo "MPI Program not specified"
   exit -1
fi
echo "Array size: $ARRAY_SIZE"
echo "Program name:  $MPI_PROGRAM"

# Run the MPI program with specified number of processes and array size
time mpirun  ./$MPI_PROGRAM $ARRAY_SIZE

