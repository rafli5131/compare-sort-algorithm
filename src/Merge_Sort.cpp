#include <chrono>
#include <cstdlib>
#include <iostream>
using namespace std;
int *generate_random_int(int n) {
  int *data = new int[n];
  for (int i = 0; i < n; i++) {
    data[i] = rand();
  }
  return data;
}
bool is_sorted(int *data, int n) {
  for (int i = 1; i < n; i++) {
    if (data[i - 1] > data[i]) {
      return false;
    }
  }
  return true;
}
void merge(int *data, int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create R and L arrays
    int *L = new int[n1];
    int *R = new int[n2];

    // Copy data to R and L arrays
    for (i = 0; i < n1; i++)
        L[i] = data[left + i];
    for (j = 0; j < n2; j++)
        R[j] = data[mid + 1 + j];

    // Merge the R and L arrays back into data[left..right]
    i = 0;
    j = 0;
    k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            data[k] = L[i];
            i++;
        } else {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        data[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        data[k] = R[j];
        j++;
        k++;
    }

    // Free arrays
    delete[] L;
    delete[] R;
}

void mergeSort(int *data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort first and second halves
        mergeSort(data, left, mid);
        mergeSort(data, mid + 1, right);

        // Merge the sorted halves
        merge(data, left, mid, right);
    }
}

void sort(int *data, int n) {
    mergeSort(data, 0, n - 1);
}
int main() {
  int num_of_experiments = 100;
  int *data;
  int n;
  // DEBUG
  // The program will stop if the sorting is incorrect
  n = 100;
  data = generate_random_int(n);
  sort(data, n);
  if (!is_sorted(data, n)) {
    throw runtime_error("Sorting function ERROR.");
  }
  // EXPERIMENTS
  cout << "data, time (ms)\n";
  cout << " \n";
  for (int i = 1; i <= num_of_experiments; i++) {
    n = i * 1000;
    data = generate_random_int(n);
    auto start = chrono::high_resolution_clock::now();
    sort(data, n);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << n << ", " << duration.count() << "\n";
    delete data;
  }
  return 0;
}