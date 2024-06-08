#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

void merge(std::vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    std::vector<int> L(n1), R(n2);

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temporary arrays back into arr[l..r]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = l; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(std::vector<int>& arr, int l, int r) {
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for large l and r
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        // Merge the sorted halves
        merge(arr, l, m, r);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <ARRAY_SIZE>\n";
        return 1;
    }

    std::chrono::time_point<std::chrono::system_clock> start, end;

    int array_size = std::atoi(argv[1]);
    std::vector<int> arr(array_size);

    // Seed for random number generation
    std::srand(std::time(0));

    // Fill the array with random elements
    for (int i = 0; i < array_size; i++) {
        arr[i] = std::rand() % array_size; // Adjust the range as needed
    }
    
    start = std::chrono::system_clock::now();
    // Perform merge sort
    mergeSort(arr, 0, arr.size() - 1);

    std::cout << "Sorted array:\n";
   // for (const auto& elem : arr) {

     //   std::cout << elem << " ";
    //}
    
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Time taken for sorting: " << elapsed_seconds.count() << " seconds\n\n";
	
    std::cout << "\n";

    return 0;
}

