#include <chrono>
#include <cmath>
#include <iostream>
#include <vector>

void compute() {
  std::vector<double> v(1000000);
  for (size_t i = 0; i < v.size(); ++i) {
    v[i] = std::sin(i) * std::cos(i);
  }
}

int main() {
  auto start = std::chrono::high_resolution_clock::now();
  compute();
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Elapsed time: " << elapsed.count() << " seconds\n";

  return 0;
}
