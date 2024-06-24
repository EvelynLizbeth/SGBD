#include <iostream>
#include <vector>
#include <cstring>
#include <stdexcept>

const int PAGE_SIZE = 4096; // Tamaño de la página en bytes
const int RECORD_SIZE = 128; // Tamaño del registro en bytes

struct PageHeader {
    int recordCount; // Número de registros almacenados
    int freeSpaceOffset; // Offset al espacio libre
};

class Page {
private:
    PageHeader header;
    std::vector<int> slotArray; // Tabla de índices dinámicos
    char* data; // Área de datos

public:
    Page() {
        header.recordCount = 0;
        header.freeSpaceOffset = 0;
        data = new char[PAGE_SIZE - sizeof(PageHeader)];
        std::memset(data, 0, PAGE_SIZE - sizeof(PageHeader));
    }

    ~Page() {
        delete[] data;
    }

    bool insertRecord(const char* record) {
        if (header.freeSpaceOffset + RECORD_SIZE > PAGE_SIZE - sizeof(PageHeader)) {
            std::cerr << "Error: No more space for records" << std::endl;
            return false;
        }

        slotArray.push_back(header.freeSpaceOffset);
        std::memcpy(data + header.freeSpaceOffset, record, RECORD_SIZE);
        header.freeSpaceOffset += RECORD_SIZE;
        header.recordCount++;
        return true;
    }

    bool deleteRecord(int index) {
        if (index < 0 || index >= header.recordCount) {
            std::cerr << "Error: Invalid record index" << std::endl;
            return false;
        }

        slotArray.erase(slotArray.begin() + index);
        header.recordCount--;

        // Compactar el espacio si es necesario (opcional)
        if (index < header.recordCount) {
            int nextOffset = slotArray[index];
            int currentOffset = slotArray[index - 1];
            int shiftSize = nextOffset - currentOffset - RECORD_SIZE;
            std::memmove(data + currentOffset, data + nextOffset, shiftSize);
            header.freeSpaceOffset -= RECORD_SIZE;
        }

        return true;
    }

    void printRecords() const {
        for (int i = 0; i < header.recordCount; ++i) {
            const char* record = data + slotArray[i];
            std::cout << "Record " << i + 1 << ": " << std::string(record, RECORD_SIZE) << std::endl;
        }
    }
};

int main() {
    Page page;
    char record1[RECORD_SIZE] = "Record 1";
    char record2[RECORD_SIZE] = "Record 2";
    char record3[RECORD_SIZE] = "Record 3";

    page.insertRecord(record1);
    page.insertRecord(record2);
    page.insertRecord(record3);

    std::cout << "Records after insertion:" << std::endl;
    page.printRecords();

    page.deleteRecord(1);

    std::cout << "\nRecords after deletion of record 2:" << std::endl;
    page.printRecords();

    return 0;
}
