#include <iostream>
#include <iomanip>
#include <Eigen/Dense>
#include <Eigen/SVD>
#include "cg_solver.hpp"

// Funzione per calcolare il numero di condizionamento di A (dal codice del professore)
double condA(const Eigen::MatrixXd& A) {
    Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
    Eigen::VectorXd singularValuesA = svd.singularValues();
    return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}

int main() {
    std::cout << "--- TEST METODO DEL GRADIENTE CONIUGATO ---" << std::endl;

    const double tol = 1.0e-15;
    unsigned int n = 5; // Testiamo su una dimensione n = 5

    // Generazione di una matrice casuale non singolare
    Eigen::MatrixXd B = Eigen::MatrixXd::Random(n, n);
    if (std::abs(B.determinant()) < tol) {
        std::cerr << "Errore: Matrice B singolare." << std::endl;
        return -1;
    }

    // Costruzione di una matrice simmetrica definita positiva A = B^T * B
    Eigen::MatrixXd A = B.transpose() * B;
    
    // Soluzione esatta nota (vettore di tutti 1)
    Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(n);
    
    // Calcolo del termine noto b = A * x_ex
    Eigen::VectorXd b = A * x_ex;

    // Vettore soluzione iniziale (inizializzato a zero dentro la funzione)
    Eigen::VectorXd x;
    
    const unsigned int it_max = 1000;
    const double res_tol = 1.0e-12;

    std::cout << std::scientific << std::setprecision(4);
    std::cout << "Condizionamento della matrice A: " << condA(A) << std::endl;

    // Esecuzione del Gradiente Coniugato
    unsigned int it = conjugate_gradient(A, b, x, res_tol, it_max);

    // Calcolo dell'errore relativo finale rispetto alla soluzione esatta
    double err_rel = (x_ex.norm() == 0.0) ? (x - x_ex).norm() : (x - x_ex).norm() / x_ex.norm();

    // Stampa dei risultati
    std::cout << "\nIterazioni effettuate / Max consentite: " << it << " / " << it_max << std::endl;
    std::cout << "Errore relativo finale: " << err_rel << std::endl;
    std::cout << "Tolleranza richiesta: " << res_tol << std::endl;
    
    std::cout << "\nSoluzione calcolata x:\n" << x << std::endl;
    std::cout << "\nSoluzione esatta x_ex:\n" << x_ex << std::endl;

    // Verifica di correttezza (il test fallisce se l'errore è grossolano)
    if (err_rel < 1e-10) {
        std::cout << "\n--- TEST SUPERATO CON SUCCESSO ---" << std::endl;
    } else {
        std::cout << "\n--- TEST FALLITO (Errore troppo elevato) ---" << std::endl;
        return -1;
    }

    return 0;
}