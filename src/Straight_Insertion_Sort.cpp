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
  int i, j, x;
  for (i = 1; i < n; i++) {
    x = data[i];
    j = i - 1;
    while (j >= 0 && x < data[j]) {  
      data[j + 1] = data[j];
      j--;
    }
    data[j + 1] = x;
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
    delete[] data;
    throw runtime_error("Sorting function ERROR.");
  }
  delete[] data;

  // EXPERIMENTS
  cout << "data, time (ms)\n";
  for (int i = 1; i <= num_of_experiments; i++) {
    n = i * 1000;
    data = generate_random_int(n);
    auto start = chrono::high_resolution_clock::now();
    sort(data, n);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << n << ", " << duration.count() << "\n";
    delete[] data;
  return 0;
}
