#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class Item{
    private:
        string mes, r, o;
        int dia, hora, minuto, segundo, price;
    public:
        Item() : mes(""), dia(0), hora(0), minuto(), segundo(), r(""), o(""), price(0) {} // constructor por defecto para evitar inicializar siempre

        Item(string mes, int dia, int hora, int minuto, int segundo, string r, string o, int price){
            this -> mes = mes;
            this -> dia = dia;
            this -> hora = hora;
            this -> minuto = minuto;
            this -> segundo = segundo;
            this -> r = r;
            this -> o = o;
            this -> price = price;
        }
        string show(){ 
            return this -> mes + " " + to_string(this -> dia) + " " + to_string(this -> hora) + ":" + to_string(this -> minuto) + ":" + to_string(this -> segundo) + "(" + to_string(this -> price) + ")"; 
        }

        bool operator< (const Item& otro) const // & indica que no es copia, es referencia
        // los dos const son para que nunca se modifique cont ni el objeto que evoca la función
        { return this -> price < otro.price; } // this (izq) ItemA, otro (der) itemB 

        bool operator> (const Item& otro) const
        { return this -> price > otro.price; }
};


// Merge function
template <class T>
void merge(T *A, int l, int m, int r){
    int s1, s2; // Tamaño de cada partición
    s1 = m - l + 1;
    s2 = r - m;
    int L[s1], R[s2];
    for(int i = 0; i < s1; i++) L[i] = A[l+i];
    for(int j = 0; j < s2; j++) R[j] = A[m+1+j];

    int i = 0, j = 0, k = l;
    
    //comparar mitades y juntarlas
    while(i < s1 && j < s2){
        if(L[i] <= R[j]){ A[k] = L[i]; i++; } 
        else{ A[k] = R[j]; j++; }
        k++;
    }

    while(i < s1){ A[k] = L[i]; i++; k++; }
    while(j < s2){ A[k] = R[j]; j++; k++; }
}

template<class T>
void mergeSort(T *A, int l, int r){
    int m;
    if(l < r){
        m = l +(r-l)/2;
        mergeSort(A, l, m); mergeSort(A, m+1, r); // repetir para cada mitad
        merge(A, l, m , r);
    } 
} // fin de ordenamiento por merge


// declarar componentes de array según el txt
template <class T>
void declare(T *A){
	string sline;
	int index;

	ifstream inFile("orders.txt");
    ofstream outFile("salida2.txt");
	int i = 0;

	if (inFile.is_open()){	//	Lee linea a linea
		while (getline(inFile, sline)){
            //cout << "Read:\t"<< sline << endl;
            //outFile << sline << endl;

            // Se obtiene el mes: 
			string line = sline; //pasar string auxiliar
			index = line.find(" "); // primera aparición de espacio (índice 3)
			string mes = line.substr(0, index); //guarda mes aquí
			
			//	Obtine dia
			line = sline.substr(index+1); // sin mes
			index = line.find(" "); // aparición de espacio
			int dia = stoi(line.substr(0, index));

            // Se obtiene hora
			line = line.substr(index+1); // sin día
			index = line.find(":"); // aparición de :
		    int hora = stoi(line.substr(0, index));

            // Se obtiene minuto
			line = line.substr(index+1); // sin hora
			index = line.find(":"); // aparición de :
			int minuto = stoi(line.substr(0, index));

            // Se obtiene segundo
			line = line.substr(index+1); // sin minuto
			index = line.find(":"); // aparición de :
			int segundo = stoi(line.substr(0, index));

            // Se obtiene restaurante
			line = line.substr(index+1); // sin seg
			index = line.find(" O:"); // aparición de :
			string r = line.substr(0, index);

            // Se obtiene orden
			line = line.substr(index+3); // sin r
			index = line.find("("); // aparición de (
			string o = line.substr(0, index);
            
            // Se obtiene price
			line = line.substr(index+1); // sin o
            index = line.find(")");
			int price = stoi(line.substr(0, index)); // (tomar el resto)

            // meter al arreglo
            A[i] = Item(mes, dia, hora, minuto, segundo, r, o, price); i++;
		}
	}
    inFile.close();
    outFile.close();
}


int main(){
    ifstream inFile("orders.txt"); string line; int counter;
    while (getline(inFile, line)) {
        counter++; // Incrementar el contador por cada línea leída
    }
    const int n = counter;
    Item arr[n];
    declare(arr);

    cout << arr[0].show() << endl;

    return 0;
}