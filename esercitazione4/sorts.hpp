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

#endif // SORTS_HPP