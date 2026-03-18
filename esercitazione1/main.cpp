#include <iostream>
#include <fstream>
#include <string>

int main(int argc, const char *argv[]) {
    // 1. Controllo che l'utente abbia inserito il parametro (il nome del file)
    if (argc < 2) {
        std::cerr << "Errore: parametro mancante. Devi specificare il nome del file da linea di comando.\n";
        return 1;
    }

    // 2. Apertura dello stream di lettura file usando il parametro passato
    std::ifstream fileInput(argv[1]);

    // 3. Controllo se c'è stato un problema ad aprire il file
    if (!fileInput.is_open()) {
        std::cerr << "Errore: impossibile aprire il file " << argv[1] << ".\n";
        return 1; 
    }

    // Variabili per memorizzare i dati letti dal file
    std::string citta;
    double t1, t2, t3, t4;

    // 4. Ciclo di lettura: finché riesci a leggere una città e 4 temperature...
    while (fileInput >> citta >> t1 >> t2 >> t3 >> t4) {
        // Calcolo della media
        double media = (t1 + t2 + t3 + t4) / 4.0;
        
        // Stampa a schermo della città e della media
        std::cout << citta << " " << media << "\n";
    }

    fileInput.close();

    return 0;
}