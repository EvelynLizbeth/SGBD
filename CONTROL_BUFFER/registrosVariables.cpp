#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;


// Registro de longitud variable
struct VariableLengthRecord {
    int id;
    vector<string> fields;
};

// Función para escribir un registro en un archivo de texto
void writeRecordToFile(const string& filename, const VariableLengthRecord& variableRecord) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Error al abrir el archivo." << endl;
        return;
    }


    // Escribir el registro de longitud variable
    file << "Variable Record:" << endl;
    file << "ID: " << variableRecord.id << endl;
    file << "Campos:" << endl;
    int offset = 0;
    for (const string& field : variableRecord.fields) {
        // Calcular longitud y escribir offset
        file << "Offset: " << offset << endl;
        file << "Longitud: " << field.length() << endl;
        // Calcular el bitmap de valores nulos
        bitset<8> nullBitmap(0);
        if (field.empty()) {
            nullBitmap.set(0); // Establecer el primer bit si el campo está vacío
        }
        file << "Bitmap null: " << nullBitmap << endl;
        file << "- " << field << endl;
        offset += field.length();
        file <<  endl;
    }

    file.close();
}

int main() {
    // Crear registros de ejemplo

    VariableLengthRecord variableRecord = {2, {"Jane Smith", "DDDDDD", "60000.0"}};

    // Escribir registros en el archivo
    writeRecordToFile("records.txt",variableRecord);

    cout << "Registros escritos en el archivo 'records.txt'." << endl;

    return 0;
}
