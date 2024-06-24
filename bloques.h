#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

// Estructura para almacenar la información de cada sector
struct diccionario {
    vector<pair< int,string>> lista_direcciones; // Almacenar las direcciones y un ID adicional
};

// Contador global para los IDs adicionales
int contador_global_id = 1;

// Función para añadir un sector al mapa
void añadirSector_aBloque(map<int, diccionario>& mapa, int id_sector, const vector<string>& direcciones) {
    diccionario info;

    for (const auto& direccion : direcciones) {
        info.lista_direcciones.push_back(make_pair( contador_global_id++ , direccion));
    }

    mapa[id_sector] = info;
}

void mostrar_diccionario(const map<int, diccionario>& mapa) {
    // Mostrar el contenido del mapa
    for (const auto& [id, info] : mapa) {
        cout << "BLOQUE: " << id << "\n";
        cout << "Lista de direcciones:\n";
        for (const auto& [ id_adicional,direccion] : info.lista_direcciones) {
            cout << "  " <<  " -num sector: " << id_adicional << "\t--> \t"<< direccion <<"\n";
        }
        cout << "---------------------------------------------------------------------------------------\n";
        
    }
}
void combineFiles(const std::string& mainFileName, const std::vector<std::string>& filesToAdd) {
    std::ofstream mainFile(mainFileName, std::ios::app);  // Open main file in append mode
    if (!mainFile.is_open()) {
        std::cerr << "Error al abrir bloque: " << mainFileName << std::endl;
        return;
    }

    for (const auto& fileName : filesToAdd) {
        std::ifstream fileToAdd(fileName);
        if (!fileToAdd.is_open()) {
            //std::cerr << "Error opening file to add: " << fileName << std::endl;
            if (!std::filesystem::exists(fileName)) {
                std::cerr << "El Bloque(archivo) esta vacio: " << fileName << std::endl;
            } 
            continue;
        }

        //mainFile << "\n--- Contenido de " << fileName << " ---\n";  // Optional: Add a separator for clarity

        std::string line;
        while (std::getline(fileToAdd, line)) {
            mainFile << line << '\n';
        }

        fileToAdd.close();
    }

    mainFile.close();
}

/*
int main() {
    map<string, diccionario> mapa;

    // Inicializar vectores vacíos
    //vector<string> direcciones1;
    vector<string> direcciones2;

    // Llenar los vectores con un bucle for
    //for (int i = 1; i <= 2; ++i) {
        //direcciones1.push_back("Calle " + to_string(i) + " del Sector A");
    //}

    for (int i = 1; i <= 4; ++i) {
        direcciones2.push_back("Avenida " + to_string(i) + " del Sector D");
    }

    // Añadir los sectores al mapa
    añadirSector(mapa, "ID123", direcciones2);
    añadirSector(mapa, "ID124", direcciones2); 

    return 0;
}
*/