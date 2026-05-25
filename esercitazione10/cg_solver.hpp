#ifndef CG_SOLVER_HPP
#define CG_SOLVER_HPP

#include <Eigen/Dense>
#include <iostream>

/**
 * Risolve il sistema lineare Ax = b usando il metodo del Gradiente Coniugato.
 * @param A Matrice simmetrica definita positiva
 * @param b Vettore dei termini noti
 * @param x Vettore di partenza (inizializzato a zero, conterrà la soluzione)
 * @param tol Tolleranza sul residuo relativo per l'arresto
 * @param max_iters Massimo numero di iterazioni consentite
 * @return Numero di iterazioni impiegate per convergere
 */
inline unsigned int conjugate_gradient(const Eigen::MatrixXd& A, 
                                      const Eigen::VectorXd& b, 
                                      Eigen::VectorXd& x, 
                                      double tol = 1e-12, 
                                      unsigned int max_iters = 10000) 
{
    unsigned int n = b.size();
    x = Eigen::VectorXd::Zero(n); // Vettore iniziale x0 = 0

    Eigen::VectorXd r = b - A * x; // Residuo iniziale r0
    Eigen::VectorXd p = r;         // Direzione iniziale p0 = r0

    double r_old_norm_sq = r.squaredNorm(); // Corrisponde a r^T * r
    double b_norm = b.norm();

    // Se il termine noto è praticamente zero, la soluzione è zero
    if (b_norm < 1e-16) {
        return 0;
    }

    unsigned int k = 0;
    // Eseguiamo il ciclo finché il residuo non scende sotto la tolleranza richiesta
    while (k < max_iters && (r.norm() / b_norm) > tol) {
        Eigen::VectorXd Ap = A * p;
        
        // Calcolo della lunghezza del passo alpha_k
        double alpha = r_old_norm_sq / p.dot(Ap);
        
        // Aggiornamento della soluzione e del residuo
        x += alpha * p;
        r -= alpha * Ap;
        
        // Calcolo del nuovo coefficiente beta_k per la direzione coniugata
        double r_new_norm_sq = r.squaredNorm();
        double beta = r_new_norm_sq / r_old_norm_sq;
        
        // Aggiornamento della direzione di discesa
        p = r + beta * p;
        
        r_old_norm_sq = r_new_norm_sq;
        k++;
    }

    return k;
}

#endif