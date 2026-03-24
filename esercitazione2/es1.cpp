#include <iostream>

int main()
{
    double ad[4] = {0.0, 1.1, 2.2, 3.3};
    float af[8] = {0.0, 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7};
    int ai[3] = {0, 1, 2};

    int x = 1;
    float y = 1.1;

    std::cout << "--- INDIRIZZI IN MEMORIA ---\n";
    std::cout << "Indirizzo di ad[0]: " << &ad[0] << "\n";
    std::cout << "Indirizzo di af[0]: " << &af[0] << "\n";
    std::cout << "Indirizzo di ai[0]: " << &ai[0] << "\n";
    std::cout << "Indirizzo di x:     " << &x << "\n";
    std::cout << "Indirizzo di y:     " << &y << "\n";
    std::cout << "----------------------------\n";


    (&y)[1] = 0;

    std::cout << "Valore finale di x: " << x << "\n";

    return 0;
}