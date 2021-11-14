/*Operaciones básicas con árboles
    Añadir o insertar elementos. L
    Buscar o localizar elementos. L
    Moverse a través del árbol (InOrden, PosOrden, PreOrden)
    Borrar elementos.
     */

#include<iostream>
#include<conio.h>
#include<stdlib.h>
using namespace std;

struct Nodo{ //Definimos la estructura del nodo
	int dato; //Dato entero
	Nodo *der; //Puntero derecho
	Nodo *izq; //Puntero izquiero
	Nodo *padre; //Puntero	
};

//Prototipos
void menu(); //Funcion muestra MENU
Nodo *crearNodo(int,Nodo *); //Funcion crea el Nodo
void insertarNodo(Nodo *&,int,Nodo *);
void mostrarArbol(Nodo *,int);
bool busqueda(Nodo *,int);
	void preOrden(Nodo *);
	void inOrden(Nodo *);
	void postOrden(Nodo *);
void eliminar(Nodo *,int);
void eliminarNodo(Nodo *);
Nodo *minimo(Nodo *);
void reemplazar(Nodo *,Nodo *);
void destruirNodo(Nodo *);

Nodo *arbol = NULL; //Iniciamos el arbol en NULL

int main(){
	menu();
	
	getch();
	return 0;
}

//Funcion de menu
void menu(){
	int dato,opcion,contador=0;
	
	do{
		cout<<"\t..:MENU:.."<<endl;
		cout<<"1. Insertar un nuevo nodo"<<endl;
		cout<<"2. Mostrar el arbol completo"<<endl;
		cout<<"3. Buscar un elemento en el arbol"<<endl;
		cout<<"4. Recorrer el arbol en PreOrden"<<endl;
		cout<<"5. Recorrer el arbol en InOrden"<<endl;
		cout<<"6. Recorrer el arbol en PostOrden"<<endl;
		cout<<"7. Eliminar un nodo del arbol"<<endl;
		cout<<"8. Salir"<<endl;
		cout<<"Opcion: "; 
		cin>>opcion;
		
		switch(opcion){
			case 1: cout<<"\nDigite un numero: ";
					cin>>dato;
					insertarNodo(arbol,dato,NULL); //Insertamos un nuevo nodo
					cout<<"\n";
					system("pause");
					break;
			case 2: cout<<"\nMostrando el arbol completo:\n\n";
					mostrarArbol(arbol,contador);//Llama función
					cout<<"\n";
					system("pause");
					break;
			case 3: cout<<"\nDigite el elemento a buscar: ";
					cin>>dato;
					if(busqueda(arbol,dato) == true){
						cout<<"\nElemento "<<dato<<" a sido encontrado en el arbol\n";
					}
					else{
						cout<<"\nElemento no encontrado\n";
					}
					cout<<"\n";
					system("pause"); 
					break;
			case 4: cout<<"\nRecorrido en PreOrden: ";
					preOrden(arbol);
					cout<<"\n\n";
					system("pause");
					break;
			case 5: cout<<"\nRecorrido en InOrden: ";
					inOrden(arbol);
					cout<<"\n\n";
					system("pause");
					break;
			case 6: cout<<"\nRecorrido en PostOrden: ";
					postOrden(arbol);
					cout<<"\n\n";
					system("pause");
					break;
			case 7: cout<<"\nDigite el numero a eliminar: ";
					cin>>dato;
					eliminar(arbol,dato);
					cout<<"\n";
					system("pause");
					break;
		}
		system("cls");
	}while(opcion != 8);
}

//Funcion para crear un nuevo nodo
Nodo *crearNodo(int n,Nodo *padre){
	Nodo *nuevo_nodo = new Nodo(); //Instanciamos
	
	nuevo_nodo->dato = n; //Asignamos el valor del nodo
	nuevo_nodo->der = NULL; //Asignamos NULL
	nuevo_nodo->izq = NULL; //Asignamos NULL
	nuevo_nodo->padre = padre;
	
	return nuevo_nodo;
} //Fin Funcion Crear Nuevo Nodo

//Funcion para insertar nodos en el arbol
void insertarNodo(Nodo *&arbol,int n,Nodo *padre){
	if(arbol == NULL){ //Si el arbol esta vacio
		Nodo *nuevo_nodo = crearNodo(n,padre); //Creamos el nuevo nodo
		arbol = nuevo_nodo; //Asignamos el nuevo nodo
	}
	else{ //Si el arbol tiene un nodo o mas
		int valorRaiz = arbol->dato; //Obtenemos el valor de la raiz
		if(n < valorRaiz){ //Si el elemento es menor a la raiz, insertamos en izq
			insertarNodo(arbol->izq,n,arbol);
		}
		else{//Si el elemento es mayor a la raiz, insertamos en derecha
			insertarNodo(arbol->der,n,arbol);
		}	
	}
}

//Funcion para mostrar el arbol completo
void mostrarArbol(Nodo *arbol,int cont){
	if(arbol == NULL){ //Si el arbol esta vacio
		return;
	}
	else{
		mostrarArbol(arbol->der,cont+1); //Mostramos el lado derecho
		for(int i=0;i<cont;i++){
			cout<<"   ";	
		}
		cout<<arbol->dato<<endl;
		mostrarArbol(arbol->izq,cont+1);//Mostramos lado izquierdo
	}
}

//Funcion para buscar un elemento en el arbol
// Si el valor agregado es Menor al padre va a la iz, de lo contrario va a la derecha
// Los nodos siguientes siguen la misma regla a lo interno de cada raiz

bool busqueda(Nodo *arbol,int n){
	if(arbol == NULL){ //si el arbol esta vacio
		return false;
	}
	else if(arbol->dato == n){ //Si el nodo es igual al elemento
		return true;			
	}
	else if(n < arbol->dato){ //Si el elemento es menor al nodo busca a la izq
		return busqueda(arbol->izq,n);
	}
	else{
		return busqueda(arbol->der,n); //Si el elemento es menor al nodo busca a la der
	}
} //FIN Funcion para buscar un elemento en el arbol

//Funcion para recorrido en profundidad - PreOrden
//Se debe mostrar todo el bloque izquierdo y luego todo el derecho
void preOrden(Nodo *arbol){
	if(arbol == NULL){ //Si el arbol esta vacio
		return;
	}
	else{
		cout<<arbol->dato<<" - ";
		preOrden(arbol->izq); //Imprime todo el bloque izq
		preOrden(arbol->der); //Imprime todo el bloque der	
	}	
}

//Funcion para recorrido en profundidad  - InOrden
//Se debe mostrar todo el bloque izquierdo, luego la Raiz y luego todo el derecho
void inOrden(Nodo *arbol){
	if(arbol == NULL){
		return;
	}
	else{
		inOrden(arbol->izq); //Imprime bloque izq
		cout<<arbol->dato<<" - "; // Imprime Raiz
		inOrden(arbol->der); //Imprime bloque der
	}
}

//Funcion para recorrido en profundidad - PostOrden
//Se debe mostrar todo el bloque izquierdo, luego todo el derecho y  la Raiz
void postOrden(Nodo *arbol){
	if(arbol == NULL){ //Si el arbol esta vacio
		return;
	}
	else{
		postOrden(arbol->izq); //Imprime el bloque izq
		postOrden(arbol->der); //Imprime el bloque izq
		cout<<arbol->dato<<" - "; //Imprime la raiz
	}
}

//Eliminar un nodo del arbol
void eliminar(Nodo *arbol,int n){
	if(arbol == NULL){ //Si el arbol esta vacio
		return; //No haces nada
	}
	else if(n < arbol->dato){ //Si el valor es menor
		eliminar(arbol->izq,n); //Busca por la izq
	}
	else if(n > arbol->dato){ //Si el valor es mayor
		eliminar(arbol->der,n); //Buscar por la der
	}
	else{ //Si ya encontraste el valor
		eliminarNodo(arbol);
	}
}

//Funcion para eliminar el nodo encontrado
void eliminarNodo(Nodo *nodoEliminar){
	if(nodoEliminar->izq && nodoEliminar->der){ //Si el nodo tiene hijos izq y der
		Nodo *menor = minimo(nodoEliminar->der); //Busca el mas retirado moviendose primero a la Derecha luego a Izquierda
		nodoEliminar->dato = menor->dato; //Intercambia el valor a eliminar por el menor
		eliminarNodo(menor);
	}
	else if(nodoEliminar->izq){ //Si tiene hijo izq
		reemplazar(nodoEliminar,nodoEliminar->izq);
		destruirNodo(nodoEliminar);
	}
	else if(nodoEliminar->der){ //Si tiene un hijo der
		reemplazar(nodoEliminar,nodoEliminar->der);
		destruirNodo(nodoEliminar);
	}
	else{ //No tiene hijos
		reemplazar(nodoEliminar,NULL);
		destruirNodo(nodoEliminar);
	}
}
//Funcion para determinar el nodo mas izq posible
Nodo *minimo(Nodo *arbol){
	if(arbol == NULL){ //Si el arbol esta vacio
		return NULL; //retornas nulo
	}
	if(arbol->izq){ //Si tiene hijo izq
		return minimo(arbol->izq); //buscamos la parte mas izq posible
	}
	else{ //Si no tiene hijo izq
		return arbol; //retornamos el mismo nodo
	}
}

//Funcion para reemplazar dos nodos
void reemplazar(Nodo *arbol,Nodo *nuevoNodo){
	if(arbol->padre){
		//arbol->padre hay que asignarle su nuevo hijo
		if(arbol->dato == arbol->padre->izq->dato){
			arbol->padre->izq = nuevoNodo;
		}
		else if(arbol->dato == arbol->padre->der->dato){
			arbol->padre->der = nuevoNodo;
		}
	}
	if(nuevoNodo){
		//Procedemos a asignarle su nuevo padre
		nuevoNodo->padre = arbol->padre;
	}
}

//Funcion para destruir un nodo
void destruirNodo(Nodo *nodo){
	nodo->izq = NULL;
	nodo->der = NULL;
	
	delete nodo;
}


