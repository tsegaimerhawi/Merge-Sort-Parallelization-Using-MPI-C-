
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <vector>
#include <mpi.h>

void merge(std::vector<int>&, std::vector<int>&, int, int, int);
void mergeSort(std::vector<int>&, std::vector<int>&, int, int);

int main(int argc, char** argv) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Create and populate the array in the root process
    int n = std::atoi(argv[1]);
    std::vector<int> original_array(n);
    if (world_rank == 0) {
        srand(time(NULL));
        std::cout << "Generating random elements for the array\n";
        for (int i = 0; i < n; i++) {
            original_array[i] = rand() % n;
        }
    }

    // Divide the array into equal-sized chunks
    int size = n / world_size;

    // Scatter the array data from the root process to other processes
    std::vector<int> sub_array(size);
    MPI_Scatter(original_array.data(), size, MPI_INT, sub_array.data(), size, MPI_INT, 0, MPI_COMM_WORLD);

    // Start the timer
    std::chrono::time_point<std::chrono::system_clock> start, end;
    if (world_rank == 0)
        start = std::chrono::system_clock::now();

    // Perform the mergesort on each process
    std::vector<int> tmp_array(size);
    mergeSort(sub_array, tmp_array, 0, size - 1);

    // Gather the sorted subarrays into one on the root process
    std::vector<int> sorted;
    if (world_rank == 0) {
        sorted.resize(n);
    }

    MPI_Gather(sub_array.data(), size, MPI_INT, sorted.data(), size, MPI_INT, 0, MPI_COMM_WORLD);

    // Make the final mergeSort call on the root process
    if (world_rank == 0) {
        std::vector<int> other_array(n);
        mergeSort(sorted, other_array, 0, n - 1);

        // End the timer
end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "Time taken for sorting: " << elapsed_seconds.count() << " seconds\n\n";

        // Display the sorted array
        //std::cout << "This is the sorted array: ";
        //for (int i = 0; i < n; i++) {
          //  std::cout << sorted[i] << " ";
        //}
        //std::cout << "\n\n";

        // Clean up root
        sorted.clear();
        other_array.clear();
    }

    // Finalize MPI
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}

// Merge Function
void merge(std::vector<int>& a, std::vector<int>& b, int l, int m, int r) {
    int h = l;
    int i = l;
    int j = m + 1;

    while ((h <= m) && (j <= r)) {
        if (a[h] <= a[j]) {
            b[i] = a[h];
            h++;
        } else {
            b[i] = a[j];
            j++;
        }
        i++;
    }

    if (m < h) {
        for (int k = j; k <= r; k++) {
            b[i] = a[k];
            i++;
        }
    } else {
        for (int k = h; k <= m; k++) {
            b[i] = a[k];
            i++;
        }
    }

    for (int k = l; k <= r; k++) {
        a[k] = b[k];
    }
}

// Recursive Merge Function
void mergeSort(std::vector<int>& a, std::vector<int>& b, int l, int r) {
    int m;

    if (l < r) {
        m = (l + r) / 2;

        mergeSort(a, b, l, m);
        mergeSort(a, b, m + 1, r);
        merge(a, b, l, m, r);
    }
}

