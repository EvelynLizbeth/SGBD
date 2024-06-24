#include <iostream>

using namespace::std;
struct nodo{
	int idPagina;
    int num_registros;
    string direccionPagina;
    int espacioOcupado;
    int espacioVacio;

    

	nodo* siguiente;
	nodo* atras;
} ;//*primero, *ultimo;

struct ListaDoble{
    nodo* primero;
    nodo* ultimo;
};

struct header
{
    int numero_paginas;
    int numero_registros_totales;
    ListaDoble PaginasLlenas;
    ListaDoble PaginasConEspacio;
};





void inicializarLista(ListaDoble &lista) {
    lista.primero = nullptr;
    lista.ultimo = nullptr;
}

void insertarNodo(ListaDoble &lista, int valor, string direccion, int cant_registros, int espaOcupado, int espaVacio){
    nodo* nuevo = new nodo();
    nuevo -> idPagina = valor;
    nuevo -> direccionPagina = direccion;
    nuevo -> num_registros = cant_registros;
    nuevo -> espacioOcupado = espaOcupado;
    nuevo ->espacioVacio = espaVacio;
    if(lista.primero==NULL){
        lista.primero = nuevo;
        lista.primero -> siguiente = NULL;
        lista.primero -> atras = NULL;
        lista.ultimo = lista.primero;

    }else{
        lista.ultimo -> siguiente = nuevo;
        nuevo->siguiente = NULL;
        nuevo->atras = lista.ultimo;
        lista.ultimo = nuevo;
    }
    cout<<"\nNodo ingresado\n";
}


void buscarNodo(ListaDoble &lista, int nodoBuscado){
    nodo* actual = new nodo();
	actual = lista.primero;
	bool encontrado = false;
	//int nodoBuscado = 0;
    if(lista.primero!=NULL){
        while(actual != NULL && encontrado != true ){
            if(actual -> idPagina == nodoBuscado){
                cout<<"Nodo con ID ("<<nodoBuscado<<") ENCONTRADO!!!\n \n";
                encontrado = true;
            }
            actual = actual -> siguiente;
        }
        if(!encontrado){
            cout << "\n Nodo no Encontrado\n\n";
        }

    }else{
        cout << "\n La lista "<<&lista <<"se encuentra Vacia\n\n";
    }
}



void modificarNodo(ListaDoble &lista, int nodoBuscado){
    nodo* actual = new nodo();
	actual = lista.primero;
	bool encontrado = false;
	//int nodoBuscado = 0;

    if(lista.primero!=NULL){
		
		while(actual!=NULL && encontrado!=true){
			
			if(actual->idPagina == nodoBuscado){
				cout << "\n Nodo con el idPagina ( " << nodoBuscado << " ) Encontrado";
				cout << "\n Ingrese el nuevo idPagina para este Nodo: ";
				cin >> actual->idPagina;
                cout << "\n Ingrese el nuevo direccion para este Nodo: ";
                cin >> actual->direccionPagina;
				cout << " Nodo Modificado\n\n";
				encontrado = true;
			}
			
			actual = actual->siguiente;
		}
		
		if(!encontrado){
			cout << "\n Nodo no Encontrado\n\n";
		}
		
	}else{
		cout << "\n La lista se encuentra Vacia\n\n";
	}
}


void eliminarNodo(ListaDoble &lista, int nodoBuscado){
    nodo* actual = new nodo();
	actual = lista.primero;
	nodo* anterior = new nodo();
	anterior = NULL;
	bool encontrado = false;
	//int nodoBuscado = 0;

    if(lista.primero!=NULL){
		
		while(actual!=NULL && encontrado!=true){
			
			if(actual->idPagina == nodoBuscado){
				cout << "\n Nodo con el idPagina ( " << nodoBuscado << " ) Encontrado";
				
				if(actual==lista.primero){
					lista.primero = lista.primero->siguiente;
					lista.primero->atras = NULL;
				}else if(actual==lista.ultimo){
					anterior->siguiente = NULL;
					lista.ultimo = anterior;
				}else{
					anterior->siguiente = actual->siguiente;
					actual->siguiente->atras = anterior;
				}
				
				cout << "\n Nodo Eliminado";
				encontrado = true;
			}
			anterior = actual;
			actual = actual->siguiente;
		}
		
		if(!encontrado){
			cout << "\n Nodo no Encontrado\n\n";
		}
		
	}else{
		cout << "\n La listas se encuentra Vacia\n\n";
	}
}

void desplegarListaPU(ListaDoble &lista){
	nodo* actual = new nodo();
	actual = lista.primero;
	if(lista.primero!=NULL){
		
		while(actual!=NULL){
            cout << "\n---------------------------------------------\n";
			cout << "\n " << actual->idPagina; 
            cout << "\n " << actual->direccionPagina; 
            cout << "\n " << actual->num_registros; 
            cout << "\n " << actual->espacioOcupado; 
            cout << "\n " << actual->espacioVacio; 
            
			actual = actual->siguiente;
		}
		
	}else{
		cout << "\n La listas se encuentra Vacia\n\n";
	}
}

/*
void insertarNodoInicio(ListaDoble &lista, int valor, string direccion) {
    nodo* nuevo = new nodo();  // Crear un nuevo nodo
    nuevo->idPagina = valor;   // Asignar el valor al nodo
    nuevo->direccionPagina = direccion; // Asignar la dirección al nodo

    // Si la lista está vacía
    if (lista.primero == NULL) {
        lista.primero = nuevo; // El nuevo nodo es el primero
        lista.primero->siguiente = NULL; // No hay nodo siguiente
        lista.primero->atras = NULL; // No hay nodo anterior
        lista.ultimo = lista.primero; // El nuevo nodo es también el último
    } else {
        // Si la lista no está vacía
        nuevo->siguiente = lista.primero; // El nuevo nodo apunta al antiguo primer nodo
        lista.primero->atras = nuevo; // El antiguo primer nodo apunta al nuevo nodo como el anterior
        nuevo->atras = NULL; // El nuevo nodo no tiene nodo anterior
        lista.primero = nuevo; // El nuevo nodo se convierte en el primer nodo
    }

    cout << "\nNodo ingresado al inicio\n"; // Imprime un mensaje indicando que el nodo ha sido ingresado
}


void haciaPaginaLLena(ListaDoble &lista1, ListaDoble &lista2) {
    if (lista2.primero == NULL) {
        cout << "La lista 2 está vacía, no hay nodos para mover.\n";
        return;
    }

    nodo* nodoMover = lista2.primero; // Extraer el primer nodo de la lista2

    if (lista2.primero == lista2.ultimo) {
        // Si hay solo un nodo en la lista2
        lista2.primero = NULL;
        lista2.ultimo = NULL;
    } else {
        // Si hay más de un nodo en la lista2
        lista2.primero = lista2.primero->siguiente;
        lista2.primero->atras = NULL;
    }

    // Insertar el nodo extraído al inicio de la lista1
    nodoMover->siguiente = lista1.primero;
    nodoMover->atras = NULL;

    if (lista1.primero != NULL) {
        lista1.primero->atras = nodoMover;
    } else {
        // Si lista1 estaba vacía, el nodo movido es ahora el último nodo también
        lista1.ultimo = nodoMover;
    }

    lista1.primero = nodoMover;

    cout << "Nodo movido de lista2 a lista1 al inicio\n";
}
*/


nodo* _buscarNodo(ListaDoble &lista, int nodoBuscado) {
    nodo* actual = lista.primero;
    while (actual != NULL) {
        if (actual->idPagina == nodoBuscado) {
            cout << "Nodo con ID (" << nodoBuscado << ") ENCONTRADO!!!\n \n";
            return actual;
        }
        actual = actual->siguiente;
    }
    cout << "\n Nodo no Encontrado\n\n";
    return NULL;
}


void moverNodo(ListaDoble &lista1, ListaDoble &lista2, nodo* nodoMover) {
    if (nodoMover == NULL) {
        cout << "El nodo a mover es NULL.\n";
        return;
    }

    // Eliminar el nodo de lista2
    if (nodoMover->atras != NULL) {
        nodoMover->atras->siguiente = nodoMover->siguiente;
    } else {
        lista2.primero = nodoMover->siguiente;
    }

    if (nodoMover->siguiente != NULL) {
        nodoMover->siguiente->atras = nodoMover->atras;
    } else {
        lista2.ultimo = nodoMover->atras;
    }

    // Insertar el nodo al inicio de lista1
    nodoMover->siguiente = lista1.primero;
    nodoMover->atras = NULL;

    if (lista1.primero != NULL) {
        lista1.primero->atras = nodoMover;
    } else {
        lista1.ultimo = nodoMover;
    }

    lista1.primero = nodoMover;

    cout << "Nodo movido de lista2 a lista1 al inicio\n";
}


void haciaPaginaLLena(ListaDoble &lista1, ListaDoble &lista2, int idNodo) {
    nodo* nodoMover = _buscarNodo(lista2, idNodo);
    if (nodoMover != NULL) {
        moverNodo(lista1, lista2, nodoMover);
    } else {
        cout << "No se pudo mover el nodo porque no se encontró en lista2.\n";
    }
}



/*
int main() {
    // Crear e inicializar el header
    header h;
    h.numero_paginas = 0;
    h.numero_registros_totales = 0;
    inicializarLista(h.PaginasLlenas);
    inicializarLista(h.PaginasConEspacio);

    // Agregar algunos nodos a PaginasLlenas
    insertarNodo(h.PaginasLlenas, 1, "arrocito1");
    insertarNodo(h.PaginasLlenas, 2, "arrocito2");
    insertarNodo(h.PaginasLlenas, 3, "arrocito3");

    // Imprimir PaginasLlenas
    desplegarListaPU(h.PaginasLlenas); // Salida: 1 2 3
    cout<<"\n---------------------------\n";
    cout<<h.numero_paginas<<endl;
    cout<<h.numero_registros_totales;
    cout<<"\n---------------------------\n";

    modificarNodo(h.PaginasLlenas, 2);
    desplegarListaPU(h.PaginasLlenas);
    
    cout<<"\n---------------------------\n";
    eliminarNodo(h.PaginasLlenas, 2);
    desplegarListaPU(h.PaginasLlenas);
    eliminarNodo(h.PaginasLlenas, 1);
    desplegarListaPU(h.PaginasLlenas);
    cout<<"\n---------------------------\n";
    // Agregar algunos nodos a PaginasConEspacio
    insertarNodo(h.PaginasConEspacio, 10, "DiscoP/a.txt");
    insertarNodo(h.PaginasConEspacio, 20, "arrocito20");
    insertarNodo(h.PaginasConEspacio, 30, "arrocito30");
    insertarNodo(h.PaginasConEspacio, 40, "arrocito40");

    // Imprimir PaginasConEspacio
    
    desplegarListaPU(h.PaginasConEspacio); // Salida: 10 20

    cout<<"\n---------------------------\n";
    haciaPaginaLLena(h.PaginasLlenas,h.PaginasConEspacio, 30);
    desplegarListaPU(h.PaginasLlenas);
    cout<<"\n---------------------------\n";
    haciaPaginaLLena(h.PaginasLlenas,h.PaginasConEspacio, 40);
    desplegarListaPU(h.PaginasLlenas);
    cout<<"\n---------------------------\n";
    //haciaPaginaLLena(h.PaginasLlenas,h.PaginasConEspacio,10);
    //desplegarListaPU(h.PaginasLlenas);
    //cout<<"\n---------------------------\n";
    desplegarListaPU(h.PaginasConEspacio);
    return 0;
}
*/






