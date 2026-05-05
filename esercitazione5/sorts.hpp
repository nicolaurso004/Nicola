#ifndef SORTS_HPP
#define SORTS_HPP

#include <vector>
#include <utility>

// Funzione is_sorted
template<typename T>
bool is_sorted(const std::vector<T>& vec) {
    if (vec.empty()) {
        return true;
    }
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i] < vec[i - 1]) {
            return false;
        }
    }
    return true;
}

// 1. BUBBLE SORT
template<typename T>
void bubblesort(std::vector<T>& A) {
    int n = A.size();
    if (n <= 1) return;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = n - 1; j > i; --j) {
            if (A[j] < A[j - 1]) {
                std::swap(A[j], A[j - 1]);
            }
        }
    }
}

// 2. INSERTION SORT
template<typename T>
void insertionsort(std::vector<T>& A) {
    int n = A.size();
    if (n <= 1) return;

    for (int j = 1; j < n; ++j) {
        T key = A[j];
        int i = j - 1;
        while (i >= 0 && A[i] > key) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
}

// 3. SELECTION SORT
template<typename T>
void selectionsort(std::vector<T>& A) {
    int n = A.size();
    if (n <= 1) return;

    for (int i = 0; i < n - 1; ++i) {
        int min_idx = i;
        for (int j = i + 1; j < n; ++j) {
            if (A[j] < A[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            std::swap(A[i], A[min_idx]);
        }
    }
}

/* --- 4. MERGE SORT --- */

template<typename T>
void merge(std::vector<T>& A, int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    
    // Creiamo gli array temporanei di appoggio
    std::vector<T> L(n1);
    std::vector<T> R(n2);
    
    // Copiamo i dati
    for (int i = 0; i < n1; ++i) L[i] = A[p + i];
    for (int j = 0; j < n2; ++j) R[j] = A[q + 1 + j];
    
    // Fonde L e R di nuovo in A[p..r]
    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copia gli elementi rimanenti di L (se ce ne sono)
    while (i < n1) {
        A[k] = L[i];
        i++; k++;
    }
    // Copia gli elementi rimanenti di R (se ce ne sono)
    while (j < n2) {
        A[k] = R[j];
        j++; k++;
    }
}

template<typename T>
void merge_sort_helper(std::vector<T>& A, int p, int r) {
    if (p < r) {
        int q = p + (r - p) / 2; // Calcola il punto medio in modo sicuro
        merge_sort_helper(A, p, q);
        merge_sort_helper(A, q + 1, r);
        merge(A, p, q, r);
    }
}

// Funzione principale che l'utente chiama
template<typename T>
void mergesort(std::vector<T>& A) {
    if (!A.empty()) {
        merge_sort_helper(A, 0, A.size() - 1);
    }
}


/* --- 5. QUICK SORT --- */

template<typename T>
int partition(std::vector<T>& A, int p, int r) {
    T x = A[r]; // Il pivot è l'ultimo elemento
    int i = p - 1;
    
    for (int j = p; j < r; ++j) {
        if (A[j] <= x) {
            i++;
            std::swap(A[i], A[j]);
        }
    }
    std::swap(A[i + 1], A[r]);
    return i + 1;
}

template<typename T>
void quick_sort_helper(std::vector<T>& A, int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quick_sort_helper(A, p, q - 1);
        quick_sort_helper(A, q + 1, r);
    }
}

// Funzione principale che l'utente chiama
template<typename T>
void quicksort(std::vector<T>& A) {
    if (!A.empty()) {
        quick_sort_helper(A, 0, A.size() - 1);
    }
}

/* --- 6. QUICKSORT IBRIDO --- */

// Versione dell'Insertion Sort che lavora solo su un intervallo specifico [p, r]
template<typename T>
void insertion_sort_range(std::vector<T>& A, int p, int r) {
    if (p >= r) return;
    for (int j = p + 1; j <= r; ++j) {
        T key = A[j];
        int i = j - 1;
        while (i >= p && A[i] > key) {
            A[i + 1] = A[i];
            i = i - 1;
        }
        A[i + 1] = key;
    }
}

// Helper per il Quicksort Ibrido
template<typename T>
void hybrid_quick_sort_helper(std::vector<T>& A, int p, int r) {
    const int THRESHOLD = 50; // La nostra soglia magica dai test!

    if (r - p + 1 <= THRESHOLD) {
        // Se il pezzo è piccolo, usiamo l'algoritmo quadratico più veloce
        insertion_sort_range(A, p, r);
    } else if (p < r) {
        // Altrimenti continuiamo con il classico Quicksort
        int q = partition(A, p, r);
        hybrid_quick_sort_helper(A, p, q - 1);
        hybrid_quick_sort_helper(A, q + 1, r);
    }
}

// Funzione principale del Quicksort Ibrido
template<typename T>
void hybrid_quicksort(std::vector<T>& A) {
    if (!A.empty()) {
        hybrid_quick_sort_helper(A, 0, A.size() - 1);
    }
}

#endif // SORTS_HPP