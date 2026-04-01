#include <iostream>
#include "rational.hpp"

int main(void)
{
    // Test richiesto dalla consegna (deve stampare 1/2)
    rational<int> r(3, 6);
    std::cout << "Frazione r(3,6) semplificata: " << r << "\n\n";

    // --- TEST AGGIUNTIVI ---
    rational<int> a(1, 2);
    rational<int> b(1, 4);
    
    std::cout << "a = " << a << ", b = " << b << "\n";
    std::cout << "Somma (a + b) = " << a + b << "\n";
    std::cout << "Sottrazione (a - b) = " << a - b << "\n";
    std::cout << "Moltiplicazione (a * b) = " << a * b << "\n";
    std::cout << "Divisione (a / b) = " << a / b << "\n\n";

    // Test casi limite (Inf e NaN)
    rational<int> inf(5, 0);
    rational<int> nan(0, 0);
    std::cout << "Frazione (5/0): " << inf << "\n";
    std::cout << "Frazione (0/0): " << nan << "\n";

    return 0;
}