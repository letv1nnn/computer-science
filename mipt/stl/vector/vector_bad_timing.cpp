#include <iostream>
#include <vector>
#include <cstdlib>
#include <chrono>
#include <string>

int main(int argc, char **argv) {
    int n, repeats;
    if (argc == 3) n = std::stoi(argv[1]), repeats = std::stoi(argv[2]);
    else std::cin >> n >> repeats;

    std::vector<int> time_of_push_back(n, 0), time_of_push_back_reserve(n, 0);

    for (int i = 0; i < repeats; ++i) {
        std::vector<int> vec;
        for (int j = 0; j < n; ++j) {
            auto start = std::chrono::high_resolution_clock::now();
            vec.push_back(j);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            time_of_push_back[i] += elapsed.count();
        }
    }

    for (int i = 0; i < repeats; ++i) {
        std::vector<int> vec;
        vec.reserve(n);
        for (int j = 0; j < n; ++j) {
            auto start = std::chrono::high_resolution_clock::now();
            vec.push_back(j);
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            time_of_push_back_reserve[i] += elapsed.count();
        }
    }
   
    double no = 0, yes = 0; 
    std::cout << "Iteration | NO Reserve | Reserve\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "     " << i << "\t\t" << time_of_push_back[i] << "\t  " << time_of_push_back_reserve[i] << '\n';
        no += time_of_push_back[i]; yes += time_of_push_back_reserve[i];
    }
    
    std::cout << "NO reserve avarage: " << no / n << ", YES reserve avarage: " << yes / n << '\n';

    return 0;
}
