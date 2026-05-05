#include <iostream>
#include <vector>
#include <iomanip>
#include "sorts.hpp"
#include "timecounter.h"
#include "randfiller.h"

const int NUM_VECTORS = 100;

// Funzione di supporto per automatizzare la misurazione su 100 vettori
template<typename Func>
double measure_time(Func sort_func, const std::vector<std::vector<int>>& original_data) {
    timecounter tc;
    std::vector<std::vector<int>> data_to_sort = original_data;
    
    tc.tic();
    for (int i = 0; i < NUM_VECTORS; ++i) {
        sort_func(data_to_sort[i]);
    }
    double total_time = tc.toc();
    
    return total_time / NUM_VECTORS; // Calcolo della media
}

int main() {
    randfiller rf;
    std::cout << "--- RICERCA DELLA SOGLIA (Tempi medi su 100 array in secondi) ---\n";
    std::cout << std::left << std::setw(6) << "Size" 
              << std::setw(15) << "Bubble" 
              << std::setw(15) << "Insertion" 
              << std::setw(15) << "Selection" 
              << std::setw(15) << "Merge" 
              << std::setw(15) << "Quick" << "\n";

    for (int size = 5; size <= 100; size += 5) {
        std::vector<std::vector<int>> vectors(NUM_VECTORS, std::vector<int>(size));
        for (int i = 0; i < NUM_VECTORS; ++i) {
            rf.fill(vectors[i], -1000, 1000);
        }

        double t_bub = measure_time(bubblesort<int>, vectors);
        double t_ins = measure_time(insertionsort<int>, vectors);
        double t_sel = measure_time(selectionsort<int>, vectors);
        double t_mer = measure_time(mergesort<int>, vectors);
        double t_qui = measure_time(quicksort<int>, vectors);

        std::cout << std::left << std::setw(6) << size 
                  << std::fixed << std::setprecision(8)
                  << std::setw(15) << t_bub 
                  << std::setw(15) << t_ins 
                  << std::setw(15) << t_sel 
                  << std::setw(15) << t_mer 
                  << std::setw(15) << t_qui << "\n";
    }
    return 0;
}