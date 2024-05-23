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
void quickSort(int *data, int left, int right) {
    if (left < right) {
        int pivot = data[right];
        int i = left - 1;
        for (int j = left; j <= right - 1; j++) {
            if (data[j] < pivot) {
                i++;
                swap(data[i], data[j]);
            }
        }
        swap(data[i + 1], data[right]);
        int partitionIndex = i + 1;
        quickSort(data, left, partitionIndex - 1);
        quickSort(data, partitionIndex + 1, right);
    }
}
void sort(int *data, int n) {
    quickSort(data, 0, n - 1);
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