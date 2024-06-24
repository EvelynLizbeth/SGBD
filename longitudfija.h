#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdexcept>

struct Campo {
    std::string nombre;
    std::string tipo;
    int longitud;
};

// Función para leer el esquema desde un archivo
std::vector<Campo> leerArchivoMetadata(const std::string& archivoEsquema) {
    std::vector<Campo> esquema;
    std::ifstream inFile(archivoEsquema);
    if (!inFile) {
        throw std::runtime_error("No se pudo abrir el archivo de esquema.");
    }
    std::string linea;
    
    while (std::getline(inFile, linea)) {
        std::istringstream ss(linea);
        Campo campo;
        std::getline(ss, campo.nombre, '#');
        std::getline(ss, campo.tipo, '#');
        ss >> campo.longitud;
        esquema.push_back(campo);
    }
    
    return esquema;
}

// Función para limpiar una cadena de caracteres no imprimibles o desconocidos
std::string limpiarCadena(const std::string& cadena) {
    std::string limpia;
    for (char c : cadena) {
        if (isprint(c) || c == '\n' || c == '\r' || c == '\t') {
            limpia += c;
        }
    }
    return limpia;
}

// Función para formatear un registro de acuerdo con el esquema
std::string formatearRegistro(const std::vector<std::string>& registro, const std::vector<Campo>& esquema) {
    std::ostringstream registroFormateado;
    
    for (size_t i = 0; i < registro.size(); ++i) {
        const auto& campo = esquema[i];
        if (campo.tipo == "int") {
            registroFormateado << std::setw(campo.longitud) << std::right << registro[i];
        } else if (campo.tipo == "char") {
            registroFormateado << std::setw(campo.longitud) << std::left << registro[i];
        } else if (campo.tipo == "float") {
            float valor = std::stof(registro[i]);
            registroFormateado   << std::setw(campo.longitud) << std::left << valor;//<< std::fixed <<std::setprecision(2)
        }
        if (i < registro.size() - 1) {
            //registroFormateado <<'#';  // Usar '#' como delimitador entre campos
        }
    }
    
    return registroFormateado.str();
}

// Función para dividir una línea en campos usando una coma como delimitador
std::vector<std::string> dividir(const std::string& linea, char delimitador) {
    std::vector<std::string> campos;
    std::string campo;
    std::istringstream ss(linea);
    bool dentroDeComillas = false;
    
    while (ss.good()) {
        char c = ss.get();
        if (c == '\"') {
            dentroDeComillas = !dentroDeComillas;
        } else if (c == delimitador && !dentroDeComillas) {
            campos.push_back(campo);
            campo.clear();
        } else {
            campo += c;
        }
    }
    campos.push_back(campo);  // Añadir el último campo
    
    return campos;
}

void convertir_registros_long_fija(std::string archivoEsquema,std::string archivoRegistros){
    try {
        // Leer el esquema
        auto esquema = leerArchivoMetadata(archivoEsquema);
        
        // Leer los registros y convertirlos a formato de longitud fija, sobrescribiendo el mismo archivo
        std::ifstream inFile(archivoRegistros);
        if (!inFile) {
            throw std::runtime_error("Bloque vacio");
        }
        std::vector<std::string> registros; // Almacenar registros en un vector
        std::string linea;
        
        while (std::getline(inFile, linea)) {
            registros.push_back(linea);
        }
        
        inFile.close(); // Cerrar el archivo de entrada
        
        std::ofstream outFile(archivoRegistros); // Abrir el archivo para escribir (sobrescribiendo)
        if (!outFile) {
            throw std::runtime_error("No se pudo abrir el archivo de registros para escribir.");
        }
        
        for (const auto& registro : registros) {
            auto campos = dividir(registro, ',');
            if (campos.size() != esquema.size()) {
                throw std::runtime_error("Discrepancia entre el número de campos en el archivo metadata.txt y en el registro.");
            }
            std::string registroFormateado = formatearRegistro(campos, esquema);
            outFile << limpiarCadena(registroFormateado) << std::endl; // Escribir el registro formateado en el archivo
        }
        
        //std::cout << "Conversión completada en el mismo archivo " << archivoRegistros << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Nota: " << e.what() << std::endl;
        return ;
    }
}

/*
int main() {
    std::string archivoEsquema = "metadata.txt";
    std::string archivoRegistros = "registros.txt";
    convertir_registros_long_fija(archivoEsquema,  archivoRegistros);
    
    
    
    return 0;
}
*/