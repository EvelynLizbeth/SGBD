#include<iostream>
#include <filesystem>
#include <fstream>
#include <iterator>
using namespace std;
#include <vector>

#include "bloques.h"
#include "longitudfija.h"
#include "heapfile.h"
namespace fs = std::filesystem;
class Disco{
    public:
        int num_platos, num_pistas, num_sectores, num_bytes_en_sector, num_superficies=2,num_sectores_x_bloque;
        string datos_de_sector;
        vector<string> sectores;
        //Disco();
        Disco(int,int,int,int,int);
        void get_data();
        void capacidad_del_disco();

        void set_num_platos(int);
        void set_num_pistas(int);
        void set_num_sectores(int);
        void set_num_bytes_en_sector(int);
        void set_num_sectores_x_bloque(int);

        int contar_bytes(string);
        int contar_bytes_archivo(string);

        void agregar_registro(string, string);
        void crear_file(string);
        void crear_disco();
        void capacidad_para_llenar_sector();
        void llenar_sector();
        void vector_sectores();

        void info_sectores();
        bool archivo_tiene_contenido(string);

        void mostrarMenu();

        int sumaMetadata();
        //Para BLOQUE-DICCIONARIO
        map<int, diccionario> mapa;
        //int num_sectores_x_bloque=4;
        vector<string> direcciones_de_sectores_para_Bloque;
        
        void mostrar_diccio();

        //HEAP FILE
        header header;
        void crear_header();
        
        
        //////////////////////////////

        bool archivoExiste(string);
        
};

//Disco::Disco() {}


Disco::Disco(int platos, int pistas, int sectores, int bytes ,int secXbloque)
    : num_platos(platos),
      num_pistas(pistas),
      num_sectores(sectores),
      num_bytes_en_sector(bytes),
      num_sectores_x_bloque(secXbloque) {
}


void Disco::get_data(){
    cout << "----------------------------------" << endl;
    cout << "Datos del disco\t" << endl;
    cout << "Numero de platos:\t" << num_platos << endl;
    cout << "Numero de pistas:\t" << num_pistas << endl;
    cout << "Numero de sectores:\t" << num_sectores << endl;
    cout << "Numero de bytes:\t" << num_bytes_en_sector << endl;
    cout << "Numero de sectores en bloque:\t" << num_sectores_x_bloque << endl;
    cout << "----------------------------------" << endl;
    
}

void Disco::capacidad_del_disco(){
    int total, GB;
    GB = 1024 * 1024 * 1024;
    total = this->num_platos * this->num_superficies * this->num_pistas * this->num_sectores * this->num_bytes_en_sector;
    
    cout << "CAPACIDAD DEL DISCO" << endl;
    cout << "Capacidad en bytes:\t" << total << endl;
    cout << "Capacidad en GB:\t" << total/GB << endl;
}


void Disco::set_num_platos(int nplatos){
    this->num_platos = nplatos;
    return;
}

void Disco::set_num_pistas(int npistas){
    this->num_pistas = npistas;
    return;
}

void Disco::set_num_sectores(int nsectores){
    this->num_sectores = nsectores;
    return;
}

void Disco::set_num_bytes_en_sector(int nbytes){
    this->num_bytes_en_sector = nbytes;
    return;
}

void Disco::set_num_sectores_x_bloque(int nsec_xbloques){
    this->num_sectores_x_bloque = nsec_xbloques;
    return;
}



int Disco::contar_bytes(string str) {
    // Obtener el tamaño del string
    int size = str.size();
    // Devolver el tamaño
    return size;
} 


int Disco::contar_bytes_archivo(string filename){
        

        // Abrir el archivo en modo binario
        ifstream file(filename, ios::binary);

        // Verificar si el archivo se abrió correctamente
        if (!file) {
            //cerr << "No se pudo abrir el archivo." << endl;
            return 1;
        }

        // Contador de bytes
        int byteCount = 0;
        char byte;

        // Leer el archivo byte por byte y contar
        while (file.get(byte)) {
            byteCount++;
        }

        // Cerrar el archivo
        file.close();

        // Mostrar el resultado
        //cout << "El archivo tiene " << byteCount << " bytes." << endl;
        return byteCount;
}

void Disco::agregar_registro(string file, string registro){
    ofstream writer (file, ios::app);

    if(! writer){
        cout << "Error opening file: " << endl;
    }
    writer << registro << endl;
    //writer << "\n" << endl;//OPCIONAL
    //std::cout<<"Registro adicionado!"<<std::endl;
    writer.close();
 
}

void Disco::crear_file(string nombre_file){

    // se crea el objeto de la clase ofstream
    ofstream mifichero;

    // se abre el fichero
    mifichero.open ( nombre_file ) ;

    // se escribe en el fichero
    //mifichero<< "Escribo 2 " << endl ;


    // se cierra el fichero
    mifichero.close() ;
}
void Disco::crear_disco(){
    string CARPETA= "Disco";
    fs::create_directories(CARPETA);

    string subcarpeta_platos,  subcarpeta_superficie, subcarpeta_pistas, subcarpeta_sector;

    for(int platos_= 0 ; platos_ < num_platos ;platos_++){
        subcarpeta_platos = CARPETA+ "/" + "__plato"+ to_string(platos_);
        fs::create_directories(subcarpeta_platos);

        for (int superficies_ = 0; superficies_ < num_superficies ; superficies_++){
            subcarpeta_superficie = subcarpeta_platos + "/" +"__superficie"+to_string(superficies_);
            fs::create_directories(subcarpeta_superficie);

            for (int pistas_  = 0; pistas_ < num_pistas; pistas_++){
                subcarpeta_pistas = subcarpeta_superficie + "/" +"__pista"+to_string(pistas_);
                fs::create_directories(subcarpeta_pistas);

                for (int sector_ = 0; sector_ < num_sectores; sector_++){
                    subcarpeta_sector = subcarpeta_pistas + "/" +"__sector"+to_string(sector_);
                    fs::create_directories(subcarpeta_sector);
                }
                
            }
            
        }
        
        
    }
    cout << "Disco creado..." <<endl;

}


void Disco::capacidad_para_llenar_sector(){
    std::string filename = "titanic.csv";
    int capacidad_permitida, capacidad_registro;
    // Abrir el archivo
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
        //return "";
    }
    //datos ="";
    // Leer el archivo línea por línea
    string line;
    capacidad_permitida = 0;
    while (getline(file, line)) {
        // Imprimir la línea leída
        datos_de_sector = datos_de_sector + line + "#";
        //cout << line << endl;
        //cout << contar_bytes(line) << endl;

        /*capacidad_registro = contar_bytes(line);
        capacidad_permitida = capacidad_permitida + capacidad_registro;
        
        if((capacidad_permitida <= num_bytes_en_sector)  ){
            //capacidad_permitida = capacidad_permitida + contar_bytes(line);
            datos_de_sector = line;
            cout<< line << "#" <<endl;
        }else{
            capacidad_permitida = 0;
            
        }*/
    }
    //cout<<datos_de_sector<<endl;
    // Cerrar el archivo
    file.close();
    //return "";

}

void Disco::info_sectores(){
    int a;
}


bool Disco::archivo_tiene_contenido(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    return archivo.peek() != ifstream::traits_type::eof();
}


bool Disco::archivoExiste(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    return archivo.good();
}



int Disco::sumaMetadata(){
    ifstream file("metadata.txt"); // Nombre del archivo con los datos
    string line;
    int tamTotal1Registro = 0;

    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        
        // Vamos a leer hasta llegar a la tercera columna 
        for (int i = 0; i < 2; ++i) {
            getline(ss, field, '#'); // Descartamos las primeras dos columnas
        }
        
        // Ahora leemos la tercera columna 
        getline(ss, field, '#'); 
        getline(ss, field, '#'); 
        getline(ss, field, '#'); 

        // Convertimos el valor de Pclass a entero y lo sumamos a tamTotal1Registro
        int tamAtributo = stoi(field);
        tamTotal1Registro += tamAtributo;
    }

    // Mostramos la suma de la tercera columna 
    //cout << "Suma de los números en la tercera columna : " << tamTotal1Registro << endl;
    return tamTotal1Registro;
}

void Disco::vector_sectores(){
    int cant_max_sectores = num_platos  * num_pistas * num_superficies * num_sectores;
    int cant_max_bytes_en_sector = num_bytes_en_sector;
    int pos_sec=0;
    
    

    string filename = "Titanic.csv"; //titanictotal.csv
    string line;
    string datos;
    // Abrir el archivo
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo " << filename << endl;
    }

    while (getline(file, line)) {
        /*if(datos.empty()){
            datos += "#";
            //cout << "ENTRANDO?" << endl;
            //cout << "------------> " << datos <<endl;
        }*/
        //sectores.push_back(line + "#");
        sectores.push_back(line);
        /*datos += line;
        
        if(datos.length() > cant_max_bytes_en_sector){
            sectores.push_back(datos);
            id_sector.push_back(datos);
            datos = "";
        }*/
    }
    


    file.close();

    /*int cant_sectores = 3;

    int canti_max_sectores, cant_usada_sectores, cant_disponibles_sectores;
    canti_max_sectores = num_platos  * num_pistas * num_superficies * num_sectores;
    cant_usada_sectores = 4;
    cout << "INFORMACIÓN DE SECTORES" << endl;
    cout << "Cantidad maxima de sectores en el DISCO : \t" <<canti_max_sectores  << endl;
    cout << "Cantidad usada de sectores : \t" << endl;
    cout << "Cantidad disponibles : \t" << endl;*/
    
    /*cout<<"************************************************************************"<<endl;
    for (int i = 0; i < sectores.size(); i++) {
        // Printing the element at
        // index 'i' of vector
        cout << sectores[i] << "/////////" << endl;
    }
    cout<<"************************************************************************"<<endl;*/
    


}   

void Disco::crear_header(){
    header.numero_paginas = 0;
    header.numero_registros_totales = 0;
    inicializarLista(header.PaginasLlenas);
    inicializarLista(header.PaginasConEspacio);
}

void Disco::llenar_sector(){

    
    /*int canti_max_sectores = num_platos  * num_pistas * num_superficies * num_sectores;
    int canti_max_bytes =  num_platos  * num_pistas * num_superficies * num_sectores * num_bytes_en_sector;
    int cant_permitida_en_un_sector = cant_permitida_en_un_sector/canti_max_sectores ;
    cout << " AQUI LA CANTIDAD MAX DE BYTES EN UN SECTOR :" << cant_permitida_en_un_sector<< endl;*/
    string CARPETA= "CarpetaBloques";
    int longRegistroFijo=sumaMetadata();
    int cantRegistroEnSector = num_bytes_en_sector/longRegistroFijo;
    int contRegistro=0;
    int tamBloqueBytes = num_bytes_en_sector*num_sectores_x_bloque;



    fs::create_directories(CARPETA);
    string  datos_en_sector;
    int pos=0;
    int cont=0;
    int id_bloque=0;
    string nombre_file, direccion_y_nombre_file;
    for(int platos_= 0 ; platos_ < num_platos ;platos_++){
        for (int superficies_ = 0; superficies_ < num_superficies ; superficies_++){
            for (int pistas_  = 0; pistas_ < num_pistas; pistas_++){
                for (int sector_ = 0; sector_ < num_sectores; sector_++){
                    nombre_file = "plato" + to_string(platos_) + "__superficie" + to_string(superficies_) + "__pista"+ to_string(pistas_) + "__sector"+ to_string(sector_);
                    direccion_y_nombre_file ="Disco/__plato" + to_string(platos_) + "/__superficie" + to_string(superficies_) + "/__pista"+ to_string(pistas_) + "/__sector"+ to_string(sector_)+ "/" + nombre_file + ".txt";
                    //cout<<nombre_file<<endl;
                    //cout <<  "***********" << sectores[pos].size()  << sectores[pos] <<endl;
                    
                    
                    
                    
                    //int limite = contar_bytes_archivo(direccion_y_nombre_file ) + sectores[pos].size();
                    /*cout <<" limite " << limite <<endl;
                    cout << " bytes en archivo : "<<contar_bytes_archivo(direccion_y_nombre_file )<<endl;
                    cout << "sectores en pos: " <<pos << "--"<< sectores[pos].size()<< "\t"<< sectores[pos]<<endl;

                    cout << "bytes por sector: " <<num_bytes_en_sector<<endl;*/
                    
                    
                    while((         ( contar_bytes_archivo(direccion_y_nombre_file ) + sectores[pos].size()   )    <= num_bytes_en_sector  )    ){
                    //while((          longRegistroFijo      <= num_bytes_en_sector  )    ){
                    
                    //while((          cantRegistroEnSector>0 )    ){
                        //cout << " ---> " << contar_bytes_archivo(direccion_y_nombre_file) <<  " -- " << num_bytes_en_sector + sectores[pos].size() <<endl ;
                        agregar_registro(direccion_y_nombre_file,sectores[pos]);
                        //cout << "agragar registro: " <<direccion_y_nombre_file << "\tpos:"<<pos << "\t"<< "--tam:"<< sectores[pos].size()<< "\tregistro"<< sectores[pos]<<endl;
                        //longRegistroFijo=longRegistroFijo+sumaMetadata();
                        //cout<<"============"<<longRegistroFijo<<endl;
                        contRegistro++;
                        pos ++;
                        if(contRegistro==cantRegistroEnSector){
                            contRegistro=0;
                            break;
                        }
                        //agregar_registro(direccion_y_nombre_file,"\n");
                    }
                    //cout<<"BINGOOO: "<<sectores[49];


                    if (cont<num_sectores_x_bloque){
                        cont++;
                        
                        direcciones_de_sectores_para_Bloque.push_back(direccion_y_nombre_file);
                        cout << "Entrada1: "<<direccion_y_nombre_file<<endl;
                    }
                    //PAGINAS LLENAS
                    if(cont==num_sectores_x_bloque){
                        cout<< cont<<"->"<<num_sectores_x_bloque<<endl;
                        cout << "Entrada2"<<endl;
                        
                        //cout << "Entrada3"<<endl;
                        id_bloque++;
                        añadirSector_aBloque(mapa, id_bloque , direcciones_de_sectores_para_Bloque);
                        //UBICACION Y NOMBRE DE BLOQUE
                        string nombre_del_bloque= CARPETA+ "/"+"BLOQUE_"+to_string(id_bloque)+".txt";
                        
                        
                        //cout<<"*******************************************************************************************"<<endl;
                        for (const auto& fileName : direcciones_de_sectores_para_Bloque) {
                            convertir_registros_long_fija("metadata.txt",  fileName);
                            //std::cout << fileName << std::endl;
                        }
                        //cout<<"*******************************************************************************************"<<endl;
                        combineFiles(nombre_del_bloque, direcciones_de_sectores_para_Bloque);

                        if(archivo_tiene_contenido(nombre_del_bloque) && archivo_tiene_contenido(direcciones_de_sectores_para_Bloque[num_sectores_x_bloque-1]) ){
                            int cantRegistrosEn1Bloque = cantRegistroEnSector*num_sectores_x_bloque;
                            insertarNodo(header.PaginasLlenas, id_bloque, nombre_del_bloque, cantRegistrosEn1Bloque ,  tamBloqueBytes ,0 );//tamBloqueBytes - contar_bytes_archivo(nombre_del_bloque)
                            
                        }else{
                            int cantRegistrosEn1Bloque =contar_bytes_archivo(nombre_del_bloque)/sumaMetadata();
                            int espacioocupado= cantRegistrosEn1Bloque*num_bytes_en_sector;
                            insertarNodo(header.PaginasConEspacio, id_bloque, nombre_del_bloque,cantRegistrosEn1Bloque, espacioocupado ,tamBloqueBytes - espacioocupado );
                        }

                        // Limpiar la lista de direcciones de sectores para el bloque
                        direcciones_de_sectores_para_Bloque.clear();
                        cont = 0;
                        
                    }
                    
                    //pos++;
                    
                    /*if ((         ( contar_bytes_archivo(direccion_y_nombre_file ) + sectores[pos].size()   )    <= num_bytes_en_sector  )      ){
                        //cout << " ---> " << contar_bytes_archivo(direccion_y_nombre_file) <<  " -- " << num_bytes_en_sector + sectores[pos].size() <<endl ;
                        agregar_registro(direccion_y_nombre_file,sectores[pos]);
                        //agregar_registro(direccion_y_nombre_file,"\n");
                    }
                    else if (archivo_tiene_contenido(direccion_y_nombre_file) && ((  (contar_bytes_archivo(direccion_y_nombre_file ) + sectores[pos].size()) <= num_bytes_en_sector )  ))
                    {
                       cout <<" ";
                       // NO cout << "El sector tiene contenido" <<endl;
                        //agregar_registro(direccion_y_nombre_file,sectores[pos]);
                        //agregar_registro(direccion_y_nombre_file,"\n");
                    }else{
                        break;
                    }
               
                    pos ++;*/


                    
                    /*num_bytes_en_sector = std::min(num_bytes_en_sector, static_cast<int>(datos_de_sector.size()) - inicio);
                    string info_por_sector= datos_de_sector.substr(inicio, num_bytes_en_sector);
                    inicio =inicio +num_bytes_en_sector;
                    agregar_registro(direccion_y_nombre_file, info_por_sector);*/

                }
                
            }
            
        }
       
    }    

if (!direcciones_de_sectores_para_Bloque.empty()) {
        cout << "Procesando bloque parcial" << endl;
        id_bloque++;
        añadirSector_aBloque(mapa, id_bloque, direcciones_de_sectores_para_Bloque);
        string nombre_del_bloque = CARPETA + "/BLOQUE_" + to_string(id_bloque) + ".txt";
        
        for (const auto& fileName : direcciones_de_sectores_para_Bloque) {
            convertir_registros_long_fija("metadata.txt", fileName);
        }
        combineFiles(nombre_del_bloque, direcciones_de_sectores_para_Bloque);

        int cantRegistrosEn1Bloque =contar_bytes_archivo(nombre_del_bloque)/sumaMetadata();
        int espacioocupado= cantRegistrosEn1Bloque*num_bytes_en_sector;
        insertarNodo(header.PaginasConEspacio, id_bloque, nombre_del_bloque,cantRegistrosEn1Bloque, espacioocupado ,tamBloqueBytes - espacioocupado );
        direcciones_de_sectores_para_Bloque.clear();
    }
    cout<<"\nPaginas con llenas\n";
    desplegarListaPU(header.PaginasLlenas);
    cout<<"\nPaginas con espacio\n";
    desplegarListaPU(header.PaginasConEspacio);
}




void Disco::mostrar_diccio(){
    mostrar_diccionario(mapa);

}







void Disco::mostrarMenu() {
    cout << "--------------------MEGATRON--------------------" << endl;
    cout << "Bienvenido al Sistema Gestor de Base de Datos!!!" << endl;
    
    cout << "------------------------------------------------" << endl;
    cout << "1. Crear Disco" << endl;
    cout << "2. Llenar disco con registros de Longitud Variable" << endl;
    cout << "3. Capacidad del disco" << endl;
    cout << "4. Imprimir Bloques(sectores)" << endl;
    cout << "5. Salir" << endl;
    cout << "Ingrese el numero de la opcion deseada: ";
    cout << endl;
}


int main(){
    int nplatos, npistas, nsectores, nbytes, nsecxbloq;
    /*cout<<"----------------------------------"<<endl;
    cout<<"Ingrese numero de platos:\t"; cin>> nplatos;
    cout<<"Ingrese numero de pistas:\t"; cin>> npistas;
    cout<<"Ingrese numero de sectores:\t"; cin>> nsectores;
    cout<<"Ingrese numero de bytes:\t"; cin>> nbytes;
    cout<<"----------------------------------"<<endl;

    Disco Megatron(nplatos,npistas,nsectores,nbytes);
    Megatron.get_data();
    Megatron.capacidad_del_disco();
    Megatron.crear_disco();


    Megatron.capacidad_para_llenar_sector();
    Megatron.vector_sectores();
    Megatron.llenar_sector();*/

    //int nplatos, npistas, nsectores, nbytes;
    cout << "Creando Disco ..." << endl;
    cout<<"----------------------------------"<<endl;
    cout<<"Ingrese numero de platos:\t"; cin>> nplatos;
    cout<<"Ingrese numero de pistas:\t"; cin>> npistas;
    cout<<"Ingrese numero de sectores:\t"; cin>> nsectores;
    cout<<"Ingrese numero de bytes:\t"; cin>> nbytes;
    cout<<"Ingrese numero de sectores por bloque:\t"; cin>> nsecxbloq;
    cout<<"----------------------------------"<<endl;

    Disco Megatron(nplatos,npistas,nsectores,nbytes,nsecxbloq);
    Megatron.get_data();
    int opcion;

    do {
        
        Megatron.mostrarMenu();
        cin >> opcion;

        switch(opcion) {
            case 1:
                
                //cout << "Has seleccionado la opcion 1." << endl;
                cout << "Creando disco..."  << endl;
                Megatron.crear_disco();
                //cout << "Disco creado..." << endl;
                // Aquí puedes colocar el código correspondiente a la opción 1
                break;
            case 2:
                //cout << "Has seleccionado la opcion 2." << endl;
                cout << "Llenando disco"  << endl;
                Megatron.crear_header();
                Megatron.capacidad_para_llenar_sector();
                Megatron.vector_sectores();
                Megatron.llenar_sector();
                break;
            case 3:
                //cout << "Has seleccionado la opcion 3." << endl;
                cout << "Mostrando capacidad del disco"  << endl;
                Megatron.capacidad_del_disco();
                //cout << "Capacidad del disco..." << endl;
                break;
            case 4:
                //cout << "Has seleccionado la opcion 4." << endl;
                cout << "Mostrando diccionario"  << endl;
                Megatron.mostrar_diccio();
                break;
            case 5:
                
                cout << "Saliendo del gestor. Hasta luego!" << endl;
                break;
            default:
                cout << "Opcion no valida. Por favor, selecciona una opcion valida." << endl;
        }
    } while (opcion != 5);


    
    return 0;
}