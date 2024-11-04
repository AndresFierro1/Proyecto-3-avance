#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct prod {
    string nom;
    float pre;
    int stk;
};

class tenda {
private:
    vector<string> catNames;
    map<string, vector<prod>> cats;
    float totC;
    float totCr;
    string adminPass = "admin123"; // Contra de administrador

public:
    tenda() : totC(0), totCr(0) {
        cats["lacteos"] = { {"queso", 50.0, 5}, {"crema", 30.0, 5} };
        cats["frutas"] = { {"manzana", 10.0, 5}, {"banana", 15.0, 5} };

        for (const auto& cat : cats) {
            catNames.push_back(cat.first);
        }
    }

    void vnta() {
        string usr;
        cout << "Ingrese el nombre del usuario: ";
        cin >> usr;

        cout << "Seleccione una categoria:\n";
        for (size_t i = 0; i < catNames.size(); i++) {
            cout << (i + 1) << ". " << catNames[i] << endl;
        }

        int catSel;
        cin >> catSel;
        string selectedCat = catNames[catSel - 1];

        cout << "Seleccione un producto:\n";
        auto& productos = cats[selectedCat];
        for (size_t i = 0; i < productos.size(); i++) {
            cout << (i + 1) << ". " << productos[i].nom << " - $" << productos[i].pre << " (Stock: " << productos[i].stk << ")" << endl;
        }

        int prodSel;
        cin >> prodSel;
        prod& p = productos[prodSel - 1];

        if (p.stk <= 0) {
            cout << "No hay stock disponible para " << p.nom << endl;
            return;
        }

        char formaP;
        cout << "¿Es a credito (c) o al contado (a)? ";
        cin >> formaP;

        if (formaP == 'c') {
            totCr += p.pre;
        }
        else {
            totC += p.pre;
        }

        p.stk--;
        cout << "Venta registrada: " << p.nom << " - $" << p.pre << endl;
    }

    void corte() {
        cout << "Total vendido a credito: $" << totCr << endl;
        cout << "Total vendido al contado: $" << totC << endl;
    }

    void verStk() {
        cout << "Stock actual:\n";
        for (const auto& cat : cats) {
            cout << cat.first << ":\n";
            for (const auto& p : cat.second) {
                cout << "  " << p.nom << ": " << p.stk << endl;
            }
        }
    }

    void agregarStk(int cant) {
        string pass;
        cout << "Ingrese la contraseña de administrador: ";
        cin >> pass;

        if (pass == adminPass) {
            for (auto& cat : cats) {
                for (auto& p : cat.second) {
                    p.stk += cant;
                }
            }
            cout << "Stock actualizado. Nuevo stock de cada producto: " << cant << " agregado.\n";
        }
        else {
            cout << "Contraseña incorrecta. No se pudo agregar stock.\n";
        }
    }
};

int main() {
    tenda t;
    int op;

    do {
        cout << "\n1. Realizar Venta\n2. Corte de Caja\n3. Ver Stock\n4. Agregar Stock\n5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> op;

        switch (op) {
        case 1:
            t.vnta();
            break;
        case 2:
            t.corte();
            break;
        case 3:
            t.verStk();
            break;
        case 4: {
            int cant;
            cout << "Ingrese la cantidad a agregar al stock: ";
            cin >> cant;
            t.agregarStk(cant);
            break;
        }
        case 5:
            cout << "Saliendo del programa.\n";
            break;
        default:
            cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (op != 5);

    return 0;
}
