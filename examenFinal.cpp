#include<iostream>
#include<stdlib.h>

using namespace std;

//colas y pilas

struct nodo{
	int data;
	nodo *next;
	int priority;	
};

struct nodoC{
	int dato;
	nodoC *siguiente;
}*ultimo;

struct Nodo{
	int dato;
	Nodo *der;
	Nodo *izq;
};

void insert_pila(nodo *&list,int data,int priority);
void insert_cola(nodo *&list,int data,int priority);
void insertarListaCircular(int n,nodoC *&lista);
void mostrarListaCircular(nodoC *&lista);
void showList(nodo *&list);
void detele(nodo *&list);
void insertarNodo(Nodo *&arbol,int n);
void mostrarArbol(Nodo *arbol,int contador);
bool repite(Nodo *arbol,int dato);
Nodo *crearNodo(int n);
int main(){
	
	int option;
	bool  continues=true;
	int priority;
	int data;
	nodo *list=NULL;
	nodoC *listC=NULL;
	Nodo *arbol=NULL;
	bool warning=false;
	bool isPilas=true;
	string opti;
	
	cout<<"\tCONFIGURACION"<<endl;
	cout<<"1. Usar colas"<<endl;
	cout<<"2. Usar pilas"<<endl;
	cout<<"*. default(pila)"<<endl;
	cout<<"-->";cin>>opti;
	
	if(opti=="1"){
		isPilas=false;
	}
	system("cls");
	do{
		if(isPilas){
			cout<<"\t MENU PRINCIPAL PILAS\n"<<endl;
		}
		else{
			cout<<"\t MENU PRINCIPAL COLAS\n"<<endl;
		}
		
		cout<<"1. Agregar Proceso"<<endl;
		cout<<"2. Despachar proceso"<<endl;
		cout<<"3. Mostrar procesos"<<endl;
		cout<<"4. salir"<<endl;
		cout<<"--> ";cin>>option;
		
		switch(option){
			case 1:{
				cout<<"\tAGREGAR PROCESO"<<endl<<endl;
				cout<<"Valor del proceso: ";cin>>data;
				do{
					if(warning){
						cout<<"*la prioridad no puede ser menor que 0*"<<endl;
					}
					cout<<"Prioridad del proceso: ";cin>>priority;
					warning=true;
				}while(priority<0);
				warning=false;
				if(isPilas){
					insert_pila(list,data,priority);	
				}
				else{
					insert_cola(list,data,priority);
				}
				
				break;
			}
			case 2:{
				
				detele(list);
					
				system("pause");
				break;
			}
			case 3:{
				showList(list);
				
				system("pause");
				break;
			}
			case 4:{
				
				//convertir a lista circular
				nodo *aux=list;
				while(aux!=NULL){
					insertarListaCircular(aux->data,listC);
					if(!repite(arbol,aux->data)){
						insertarNodo(arbol,aux->data);
					}
					
					aux=aux->next;
				}
				cout<<"\tLISTA CIRCULAR"<<endl<<endl;
			    mostrarListaCircular(*&listC);
			    
			    cout<<"\t\n\nARBOL"<<endl<<endl;
			    mostrarArbol(arbol,0);
				
				system("pause");
				continues=false;
				break;
			}
			
		}
		system("cls");
	}while(continues);
	
	system("pause");
	return 0;
}

void insert_pila(nodo *&list,int data,int priority){
	
	nodo *newNodo= new nodo();
	newNodo->data=data;
	newNodo->priority=priority;
	nodo *aux1=list;
	nodo *aux2;
	
	while(aux1!=NULL && aux1->priority<priority){
		aux2=aux1;
		aux1=aux1->next;
	}
	
	if(aux1==list){
		list=newNodo;
		
	}
	else{
		aux2->next=newNodo;
	}
	newNodo->next=aux1;
}

void insert_cola(nodo *&list,int data,int priority){
	nodo *newNodo= new nodo();
	newNodo->data=data;
	newNodo->priority=priority;
	nodo *aux1=list;
	nodo *aux2;
	
	while(aux1!=NULL && aux1->priority<=priority){
		aux2=aux1;
		aux1=aux1->next;
	}
	
	if(aux1==list){
		list=newNodo;
		
	}
	else{
		aux2->next=newNodo;
	}
	newNodo->next=aux1;
	
	
}

//true=pila
//false=cola
void showList(nodo *&list){
	
	nodo *aux=list;
	
	while(aux!=NULL){
		cout<<"[ DATA="<<aux->data<<", Priority="<<aux->priority<<"] -> ";
		aux=aux->next;
	}
	cout<<"NULL"<<endl;		
	


}

void detele(nodo *&list){
	nodo *aux=list;
	if(list!=NULL){
		list=list->next;
		cout<<"PROCESO DESPACHADO:"<<endl;
		cout<<"[ DATA="<<aux->data<<", Priority="<<aux->priority<<"]"<<endl;
		delete aux;		
	}
	else{
		cout<<"NO HAY PROCESOS"<<endl;
	}

}

void insertarListaCircular(int n,nodoC *&lista){
	
	nodoC *nuevoNodo=new nodoC();
	nuevoNodo->dato=n;
	nodoC *aux1=lista;
	nodoC *aux2;
	
	if(lista==NULL){
		ultimo=nuevoNodo;
		ultimo->siguiente=nuevoNodo;
	}
	else{
		nuevoNodo->siguiente=aux1;
		ultimo->siguiente=nuevoNodo;
		
	}
	
	lista=nuevoNodo;
	
	
	
}

void mostrarListaCircular(nodoC *&lista){
	bool entro=false;
	nodoC *buscar = lista;
	bool inicio;
	if(buscar->siguiente!=buscar){
		entro=true;
	}
	cout<<buscar->dato<<" -> ";
	buscar=buscar->siguiente;

	while(buscar!=ultimo){
		
		cout<<buscar->dato<<" -> ";		
		buscar=buscar->siguiente;	
			
	}
	if(entro){
		cout<<buscar->dato<<endl;//mostrando el ultimo
	}
	

}

void insertarNodo(Nodo *&arbol,int n){
	
	if(arbol==NULL){
		Nodo *nuevoNodo=crearNodo(n);
		arbol=nuevoNodo;
	}
	else{
		int valorRaiz=arbol->dato;
		if(n<valorRaiz){
			insertarNodo(arbol->izq,n);
		}
		else{
			insertarNodo(arbol->der,n);
		}
	}
	
}

void mostrarArbol(Nodo *arbol,int contador){
	
	if(arbol==NULL){
		return;
	}
	else{
		mostrarArbol(arbol->der,contador+1);
		for(int i=0;i<contador;i++){
			cout<<"   ";
		}
		cout<<arbol->dato<<endl;
		mostrarArbol(arbol->izq,contador+1);
	}
	
}

Nodo *crearNodo(int n){
	Nodo *nuevo_nodo = new Nodo();
	
	nuevo_nodo->dato=n;
	nuevo_nodo->der=NULL;
	nuevo_nodo->izq=NULL;
	
	return nuevo_nodo;
}

bool repite(Nodo *arbol,int dato){
	
	
	if(arbol==NULL){
		return false;
	}
	else{
		repite(arbol->izq,dato);
		if(arbol->dato==dato){
			return true;
		}
		repite(arbol->der,dato);
	}
}
