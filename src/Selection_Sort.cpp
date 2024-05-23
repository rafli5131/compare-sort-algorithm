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
void sort(int *data, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (data[j] < data[min_idx]) {
                min_idx = j;
            }
        }
        swap(data[i], data[min_idx]);
    }
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