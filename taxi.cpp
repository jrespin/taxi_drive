#include <iostream>
#include <string>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <sstream>
#include <cctype>
#include <limits>

using namespace std;

const int MAX = 100;

struct Vehiculo {
    string placa;
    string numero_motor;
    string modelo;
    string capacidad_pasajos;
    string anio;
    string categoria;
    bool disponible;
};

struct Conductor {
    string nombre;
    string apellido;
    string dui;
    string NUP;
    string isss;
    string licencia;
    string telefono;
    string placaVehiculo;
};

Conductor conductores[MAX];
int totalConductores = 0;
Vehiculo vehiculos[MAX];
int totalVehiculos = 0;

void limpiarPantalla() {
    system("cls");
}

void pausar() {
    cout << "\nPresiona cualquier tecla para continuar...";
    getch();
}

bool soloDigitos(const string& s) {
    for (size_t i = 0; i < s.length(); i++) {
        if (!isdigit(s[i])) return false;
    }
    return true;
}

bool soloLetras(const string& s) {
    for (size_t i = 0; i < s.length(); i++) {
        if (!isalpha(s[i]) && s[i] != ' ') return false;
    }
    return true;
}

bool stringAInt(const string& s, int& resultado) {
    stringstream ss(s);
    ss >> resultado;
    if (ss.fail() || !ss.eof()) {
        return false;
    }
    return true;
}

bool existeDUI(const string& dui) {
    for (int i = 0; i < totalConductores; i++) {
        if (conductores[i].dui == dui) {
            return true;
        }
    }
    return false;
}

bool existeNUP(const string& nup) {
    for (int i = 0; i < totalConductores; i++) {
        if (conductores[i].NUP == nup) {
            return true;
        }
    }
    return false;
}

bool existeISSS(const string& isss) {
    for (int i = 0; i < totalConductores; i++) {
        if (conductores[i].isss == isss) {
            return true;
        }
    }
    return false;
}

bool existePlaca(const string& placa) {
    for (int i = 0; i < totalVehiculos; i++) {
        if (vehiculos[i].placa == placa) {
            return true;
        }
    }
    return false;
}

int leerOpcionMenu() {
    string entrada;
    int opcion;
    while (true) {
        cout << "Seleccione una opción: ";
        getline(cin, entrada);
        stringstream ss(entrada);
        if (ss >> opcion && (opcion == 1 || opcion == 2 || opcion == 3 || opcion == 4)) {
            break;
        } else {
            cout << "Opción inválida. Por favor ingrese 1, 2 , 3 o 4.\n";
        }
    }
    return opcion;
}

bool placaExiste(const string& placa) {
    for (int i = 0; i < totalVehiculos; i++) {
        if (vehiculos[i].placa == placa) {
            return true;
        }
    }
    return false;
}

string leerInputConLimite(int maxLongitud) {
    string input;
    while (true) {
        input.clear();
        cin.clear();
        cin.sync();

        getline(cin, input);

        if ((int)input.length() > maxLongitud) {
            cout << "Error: Solo se permiten " << maxLongitud << " caracteres. Intenta de nuevo: ";
            continue;
        }
        if ((int)input.length() < maxLongitud) {
            cout << "Error: Debe ingresar exactamente " << maxLongitud << " caracteres. Intenta de nuevo: ";
            continue;
        }
        break;
    }
    return input;
}

void registrarConductor(const string& placaVehiculo) {
    limpiarPantalla();
    cout << "===== Registro de Conductor =====\n";
    cout << "Vehículo asociado (placa): " << placaVehiculo << endl;

    if (totalConductores >= MAX) {
        cout << "No se pueden registrar más conductores.\n";
        pausar();
        return;
    }

    Conductor c;

    cout << "Nombre: ";
    getline(cin, c.nombre);

    cout << "Apellido: ";
    getline(cin, c.apellido);

    cout << "DUI: ";
    getline(cin, c.dui);

    cout << "NUP: ";
    getline(cin, c.NUP);

    cout << "ISSS: ";
    getline(cin, c.isss);

    cout << "Licencia: ";
    getline(cin, c.licencia);

    cout << "Teléfono: ";
    getline(cin, c.telefono);

    c.placaVehiculo = placaVehiculo;

    conductores[totalConductores++] = c;

    cout << "Conductor registrado y vinculado correctamente al vehículo.\n";
    pausar();
}

void registrarVehiculo() {
    limpiarPantalla();
    cout << "===== Registro de Vehículo =====\n";

    if (totalVehiculos >= MAX) {
        cout << "No se pueden registrar más vehículos.\n";
        pausar();
        return;
    }

    string placaInput;
    while (true) {
        cout << "Placa (6 números): ";
        placaInput = leerInputConLimite(6);
        if (!soloDigitos(placaInput)) {
            cout << "Error: La placa debe contener solo números.\n";
            continue;
        }
        if (placaExiste(placaInput)) {
            cout << "Error: ya existe un vehículo con esa placa.\n";
            continue;
        }
        break;
    }
    vehiculos[totalVehiculos].placa = placaInput;

    string numeroMotorInput;
    while (true) {
        cout << "Número de motor (7 números): ";
        numeroMotorInput = leerInputConLimite(7);
        if (!soloDigitos(numeroMotorInput)) {
            cout << "Error: El número de motor debe contener solo números.\n";
            continue;
        }
        break;
    }
    vehiculos[totalVehiculos].numero_motor = numeroMotorInput;

    string modeloInput;
    while (true) {
        cout << "Modelo (solo letras): ";
        getline(cin, modeloInput);
        if (!soloLetras(modeloInput) || modeloInput.empty()) {
            cout << "Error: El modelo debe contener solo letras y no puede estar vacío.\n";
            continue;
        }
        break;
    }
    vehiculos[totalVehiculos].modelo = modeloInput;

    string capacidadPasajerosInput;
    while (true) {
        cout << "Capacidad de pasajeros (máximo 4): ";
        getline(cin, capacidadPasajerosInput);
        if (!soloDigitos(capacidadPasajerosInput) || capacidadPasajerosInput.empty()) {
            cout << "Error: Debe ingresar un número válido.\n";
            continue;
        }
        int capacidad;
        if (!stringAInt(capacidadPasajerosInput, capacidad) || capacidad > 4 || capacidad < 1) {
            cout << "Error: La capacidad debe ser un número entre 1 y 4.\n";
            continue;
        }
        break;
    }
    vehiculos[totalVehiculos].capacidad_pasajos = capacidadPasajerosInput;

    string anioInput;
    while (true) {
        cout << "Año del vehículo (4 dígitos): ";
        anioInput = leerInputConLimite(4);
        if (!soloDigitos(anioInput)) {
            cout << "Error: El año debe contener solo números.\n";
            continue;
        }
        break;
    }
    vehiculos[totalVehiculos].anio = anioInput;

    int anioNumerico;
    if (!stringAInt(anioInput, anioNumerico)) {
        cout << "Error: el año debe ser un número válido.\n";
        pausar();
        return;
    }

    if (anioNumerico <= 2010) {
        vehiculos[totalVehiculos].categoria = "Tradicional";
    } else if (anioNumerico >= 2015) {
        vehiculos[totalVehiculos].categoria = "Ejecutiva";
    } else {
        cout << "El vehículo no cumple con los criterios de categoría.\n";
        pausar();
        return;
    }

    vehiculos[totalVehiculos].disponible = true;
    cout << "Vehículo registrado como '" << vehiculos[totalVehiculos].categoria << "'.\n";

    string placa = vehiculos[totalVehiculos].placa;
    totalVehiculos++;
    pausar();

    registrarConductor(placa);
}

void mostrarVehiculos() {
    limpiarPantalla();
    cout << "===== Lista de Vehículos Registrados =====\n";

    if (totalVehiculos == 0) {
        cout << "No hay vehículos registrados.\n";
    } else {
        cout << left << setw(10) << "Placa"
             << setw(15) << "Motor"
             << setw(10) << "Modelo"
             << setw(10) << "Pasajeros"
             << setw(6)  << "Año"
             << setw(12) << "Categoría"
             << setw(12) << "Disponible" << endl;

        for (int i = 0; i < totalVehiculos; i++) {
            cout << left << setw(10) << vehiculos[i].placa
                 << setw(15) << vehiculos[i].numero_motor
                 << setw(10) << vehiculos[i].modelo
                 << setw(10) << vehiculos[i].capacidad_pasajos
                 << setw(6)  << vehiculos[i].anio
                 << setw(12) << vehiculos[i].categoria
                 << setw(12) << (vehiculos[i].disponible ? "Si" : "No") << endl;
        }
    }

    pausar();
}

void mostrarConductores() {
    limpiarPantalla();
    cout << "===== Lista de Conductores Registrados =====\n";

    if (totalConductores == 0) {
        cout << "No hay conductores registrados.\n";
    } else {
        cout << left << setw(15) << "Nombre"
             << setw(15) << "Apellido"
             << setw(12) << "DUI"
             << setw(12) << "NUP"
             << setw(12) << "ISSS"
             << setw(12) << "Licencia"
             << setw(12) << "Teléfono"
             << setw(10) << "Placa" << endl;

        for (int i = 0; i < totalConductores; i++) {
            cout << left << setw(15) << conductores[i].nombre
                 << setw(15) << conductores[i].apellido
                 << setw(12) << conductores[i].dui
                 << setw(12) << conductores[i].NUP
                 << setw(12) << conductores[i].isss
                 << setw(12) << conductores[i].licencia
                 << setw(12) << conductores[i].telefono
                 << setw(10) << conductores[i].placaVehiculo << endl;
        }
    }

    pausar();
}


void menu() {
    SetConsoleOutputCP(65001); // Soporte para UTF-8
    int opcion;
    do {
        limpiarPantalla();
        cout << "===== Sistema de Registro de Vehículos de Taxi =====\n";
        cout << "1. Registrar vehículo\n";
        cout << "2. Mostrar vehículos\n";
        cout << "3. Mostrar Conductores\n";
        cout << "4. Salir\n";
        opcion = leerOpcionMenu();

        switch (opcion) {
            case 1:
                registrarVehiculo();
                break;
            case 2:
                mostrarVehiculos();
                break;
            case 3:
                mostrarConductores();
            break;
            case 4:
                cout << "Saliendo del sistema...\n";
                break;
        }

    } while (opcion != 4);
}

int main() {
    menu();
    return 0;
}
