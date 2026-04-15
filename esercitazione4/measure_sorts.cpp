#include <iostream>
#include <vector>
#include <algorithm> // Per std::sort
#include <iomanip>   // Per formattare i numeri con la virgola
#include "sorts.hpp"
#include "timecounter.h"
#include "randfiller.h"

int main() {
    randfiller rf;
    timecounter tc;

    std::cout << "--- GARA DI VELOCITA' (Tempi in secondi) ---\n\n";

    // Ciclo che raddoppia la dimensione da 4 fino a 8192
    for (int size = 4; size <= 8192; size *= 2) {
        std::cout << "Dimensione vettore: " << size << "\n";

        std::vector<int> v_orig(size);
        rf.fill(v_orig, -10000, 10000);


        std::vector<int> v_bubble = v_orig;
        std::vector<int> v_insertion = v_orig;
        std::vector<int> v_selection = v_orig;
        std::vector<int> v_std = v_orig;

        // 1. Misuriamo Bubble Sort
        tc.tic();
        bubblesort(v_bubble);
        double t_bubble = tc.toc();

        // 2. Misuriamo Insertion Sort
        tc.tic();
        insertionsort(v_insertion);
        double t_insertion = tc.toc();

        // 3. Misuriamo Selection Sort
        tc.tic();
        selectionsort(v_selection);
        double t_selection = tc.toc();

        // 4. Misuriamo std::sort 
        tc.tic();
        std::sort(v_std.begin(), v_std.end());
        double t_std = tc.toc();

        // Stampiamo i risultati
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "  Bubble Sort:    " << t_bubble << " s\n";
        std::cout << "  Insertion Sort: " << t_insertion << " s\n";
        std::cout << "  Selection Sort: " << t_selection << " s\n";
        std::cout << "  std::sort:      " << t_std << " s\n\n";
    }

    return 0;
}