#include <iostream>
#include <cmath>

int main() {

    double opp;
    double adj;
    double hyp;

    std::cout << "Opposite Side Length: ";
    std::cin >> opp;

    std::cout << "Adjacent Side Length: ";
    std::cin >> adj;

    hyp = sqrt(pow(opp, 2) + pow(adj, 2));

    std::cout << "Hypotenuse Calculated Length: " << hyp << "\n";

    return 0;
}