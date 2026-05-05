#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "sorts.hpp"
#include "randfiller.h"

int main() {
    randfiller rf;
    
    // TEST 1: 100 vettori di dimensioni casuali
    for (int i = 0; i < 100; ++i) {
        int size = std::rand() % 500 + 1;
        std::vector<int> v(size);
        rf.fill(v, -1000, 1000);
        quicksort(v);
        
        // Verifichiamo se è ordinato
        if (!is_sorted(v)) {
            std::cerr << "ERRORE: Quick Sort ha fallito con i numeri!\n";
            return EXIT_FAILURE; // Segnala al sistema che il test è fallito
        }
    }

    // TEST 2: Vettore di stringhe
    std::vector<std::string> vs = {
        "zebra", "albero", "mela", "zaino", "banana",
        "chitarra", "dado", "elefante", "fragola", "gatto"
    };
    
    quicksort(vs);
    
    if (!is_sorted(vs)) {
        std::cerr << "ERRORE: Quick Sort ha fallito con le stringhe!\n";
        return EXIT_FAILURE;
    }

    std::cout << "Test Quick Sort: SUPERATO CON SUCCESSO!\n";
    return EXIT_SUCCESS;
}