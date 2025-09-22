#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class Item{
    private:
        string mes, r, o;
        int dia, hora, minuto, segundo, price;
    public:
        Item(): mes(""), dia(0), hora(0), minuto(0), segundo(0), r(""), o(""), price(0) {} //constructor por defecto para evitar inicializar siempre

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
            return this -> mes + " " + to_string(this -> dia) + " " + to_string(this -> hora) + ":" + to_string(this -> minuto) + ":" 
            + to_string(this -> segundo) + " R:" + this -> r + + " O:" + this -> o + "(" + to_string(this -> price) + ")"; 
        }  

        int num_mes() const{
            if(this -> mes == "ene") return 1;
            if(this -> mes == "Feb") return 2;
            if(this -> mes == "Mar") return 3;
            if(this -> mes == "Abr") return 4;
            if(this -> mes == "May") return 5;
            if(this -> mes == "Jun") return 6;
            if(this -> mes == "Jul") return 7;
            if(this -> mes == "Ago") return 8;
            if(this -> mes == "Sep") return 9;
            if(this -> mes == "Oct") return 10;
            if(this -> mes == "Nov") return 11;
            if(this -> mes == "Dic") return 12;
            return 0;
        }

        long long fecha() const{
            return (num_mes()*100000000) + (this -> dia) * 1000000 + (this -> hora) * 10000 + (this -> minuto)*100 + this -> segundo;
        }

        bool operator< (const Item& otro) const // & indica que no es copia, es referencia
        // los dos const son para que nunca se modifique cont ni el objeto que evoca la función
        { return this -> fecha() < otro.fecha(); } // this (izq) ItemA, otro (der) itemB 

        bool operator> (const Item& otro) const
        { return this -> fecha() > otro.fecha(); }

        bool operator>= (const Item& otro) const
        { return this -> fecha() >= otro.fecha(); }

        bool operator<= (const Item& otro) const
        { return this -> fecha() <= otro.fecha(); }
};


// Merge function
template <class T>
void merge(T *A, int l, int m, int r){
    int s1, s2; // Tamaño de cada partición
    s1 = m - l + 1;
    s2 = r - m;
    //T L[s1], R[s2];
    T *L = new T[s1]; //inicializar mejor con new
    T *R = new T[s2];
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


// Algoritmo de búsqueda binaria
template <class T>
int binaria(T *A, Item s, int n, bool clo){
    int l = 0, r = n-1, i, cercano; // left y right para orientaarnos
    while(l <= r){
        i = l + (r-l) / 2; // definir i como la mitad
        if(A[i].fecha() == s.fecha()) return i; 
        else if(A[i].fecha() < s.fecha()){ 
            l = i+1;
            if(clo) cercano = i+1; 
        }
        else{ // delimitar de lado derecho
            r = i-1;
            if(!clo) cercano = i-1;
        }
    }
    return cercano;
}


// declarar componentes de array según el txt
template <class T>
void declare(T *A, string archivo){
	string sline;
	int index;

	ifstream inFile(archivo);
    //ofstream outFile("salida2.txt");
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
			//string r = line.substr(0, index);
            string r;
            if (index == string::npos) { r = ""; } else { r = line.substr(0, index); }

            // Se obtiene orden
            string o;
            if(index != string::npos){
                line = line.substr(index+3); // sin r
			    index = line.find("("); // aparición de (
                if(index == string::npos){ o = ""; } else{ o = line.substr(0, index); }
            }
            
            // Se obtiene price
            int price = 0; // valor por defecto
            if(index != string::npos){
                line = line.substr(index+1); // sin o
			    index = line.find(")"); // aparición de )
                if(index != string::npos){
                    string price_str = line.substr(0, index);
                    if(price_str != ""){ price = stoi(price_str); }
                }
            }

            // meter al arreglo
            A[i] = Item(mes, dia, hora, minuto, segundo, r, o, price); i++;
		}
	}
    inFile.close();
    //outFile.close();
}

template <class T>
void rango(T *A, int n){
    string inicio, final;
    cout << "--- Rango de fechas a buscar ---" << endl;
    cout << "Ingrese la fecha de inicio: "; getline(cin, inicio);
    cout << "Ingrese la fecha de final: "; getline(cin, final);

    //guardar ambas fechas en un archivo auxiliar para reusar declare()
    ofstream auxiliar("auxiliar.txt");
    Item aux[2];
    auxiliar << inicio << endl;
    auxiliar << final << endl;

    declare(aux, "auxiliar.txt"); //convertir los datos a su tipo en el array
    auxiliar.close(); //cerrar archivo

    //for(int i = 0; i < 2; i++){ //comprobar que se guardaron bien
    //    cout << aux[i].show() << endl;
    //}

    // buscar índice del primer elemento
    int indice1 = binaria(A, aux[0], n, true);
    int indice2 = binaria(A, aux[1], n, false);
    
    // imprimir los que estén dentro del rango! :D
    cout << "--- Órdenes en el rango seleccionado --- " << endl;
    for(int i = indice1; i <= indice2; i++){
        cout << A[i].show() << endl;
    }

    // ¿añadir a archivo :D?
    cout << "--- Desea guardar lo anterior en un registro .txt? (s/n) ---" << endl;
    string answer; cin >> answer;
    if(answer == "s"){
        ofstream output_fecha("ordenesPorFecha.txt");
        for(int i = indice1; i <= indice2; i++){ output_fecha << A[i].show() << endl; }
        cout << "El archivo ordenesPorFecha.txt ha guardado el registro" << endl;
        cout << "Gracias por usar el programa! Que tenga un maravilloso día! :D" << endl;
    } else cout << "Tenga un buen día :D" << endl;
}


int main(){
    ifstream inFile("orders.txt"); ofstream outFile("salida.txt"); string line; int counter;
    while (getline(inFile, line)) {
        counter++; // Incrementar el contador por cada línea leída
    }
    const int n = counter;
    Item arr[n];
    declare(arr, "orders.txt");

    // ordenar
    int l = 0, r = n-1;
    mergeSort(arr, l, r);

    // guardar en salida.txt ordenados
    for(int i = 0; i < n; i++){
        outFile << arr[i].show() << endl;
    }

    cout << "--- Primeros 10 registros por fecha ---" << endl;
    for(int i = 0; i < 10; i++){
        cout << arr[i].show() << endl;
    }

    rango(arr, n);

    return 0;
}
