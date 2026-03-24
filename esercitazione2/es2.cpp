#include <iostream>
#include <cmath>
#include <algorithm>

int main() {
    static const int N = 10;
    
    double arr[N] = {12.5, 7.2, 15.8, 3.4, 9.1, 5.5, 7.9, 9.2, 3.4, 2.1};

    double somma = 0.0;
    
    double minimo = arr[0];
    double massimo = arr[0];

    // Calcoliamo la somma, il minimo e il massimo
    for (int i = 0; i < N; ++i) {
        somma += arr[i];
        minimo = std::min(minimo, arr[i]);
        massimo = std::max(massimo, arr[i]);
    }

    // Calcoliamo la media
    double media = somma / N;

    // Calcoliamo la deviazione standard
    double somma_scarti_quadrati = 0.0;
    for (int i = 0; i < N; ++i) {
        double scarto = arr[i] - media;
        somma_scarti_quadrati += (scarto * scarto);
    }
    double dev_standard = std::sqrt(somma_scarti_quadrati / N);

    // Stampiamo i risultati a schermo
    std::cout << "--- STATISTICHE DELL'ARRAY ---\n";
    std::cout << "Minimo: " << minimo << "\n";
    std::cout << "Massimo: " << massimo << "\n";
    std::cout << "Media: " << media << "\n";
    std::cout << "Deviazione Standard: " << dev_standard << "\n";
    
    // 2. ALGORITMO BUBBLESORT
    std::cout << "--- BUBBLESORT ---\n";
    std::cout << "Array originale: ";
    for (int i = 0; i < N; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    bool scambiato;
    do {
        scambiato = false; // All'inizio del giro, supponiamo di non dover fare scambi
        for (int i = 0; i < N - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                double temp = arr[i];
                arr[i] = arr[i + 1];
                arr[i + 1] = temp;
                
                scambiato = true; // Abbiamo fatto almeno uno scambio, dovremo fare un altro giro
            }
        }
    } while (scambiato); // Se 'scambiato' è true, ripete il ciclo do-while

    std::cout << "Array ordinato:  ";
    for (int i = 0; i < N; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";

    return 0;
}