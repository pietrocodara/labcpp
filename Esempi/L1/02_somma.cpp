// L1 - Esempio 2: variabili, input e operatori aritmetici
// Input di esempio: 17 5
#include <iostream>
using namespace std;

int main() {
    int a, b;
    cout << "Inserisci due numeri interi: ";
    cin >> a >> b;

    cout << a << " + " << b << " = " << a + b << "\n";
    cout << a << " - " << b << " = " << a - b << "\n";
    cout << a << " * " << b << " = " << a * b << "\n";
    cout << a << " / " << b << " = " << a / b << "   (divisione intera!)\n";
    cout << a << " % " << b << " = " << a % b << "   (resto)\n";
    cout << a << " / " << b << " = " << (double)a / b << "   (divisione reale)\n";
    return 0;
}
