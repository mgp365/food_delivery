#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class Item{
    private:
        string mes, r, o;
        int dia, hora, minuto, segundo;
        double price;
    public:
        Item(string mes, int dia, int hora, int minuto, int segundo, string r, string o, double price){
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
            return "Name: " + this -> r + "\tPrice: " + to_string(this -> price); 
        }

        bool operator< (const Item& otro) const // & indica que no es copia, es referencia
        // los dos const son para que nunca se modifique cont ni el objeto que evoca la función
        { return this -> price < otro.price; } // this (izq) ItemA, otro (der) itemB 

        bool operator> (const Item& otro) const
        { return this -> price > otro.price; }
};

int main(){

    //	C++
	string sline;
	int index;

	ifstream inFile("orders.txt"); 	    //  input file stream
	ofstream outFile("salida2.txt");		//	output file stream	
	
	//	Verifica que los archivos se hayan abierto correctamente
	if (inFile.is_open() && outFile.is_open() )		
	{	//	Lee linea a linea
        int counter = 0; // quitar al rato
		while ( getline(inFile, sline) && counter < 1 )		
		{	counter++;
            cout << "Read:\t"<< sline << endl;			
			outFile << sline << endl;

			// Se obtiene el mes: 
			string line = sline; //pasar string auxiliar
			index = line.find(" "); // primera aparición de espacio (índice 3)
			string mes = line.substr(0, index); //guarda mes aquí
			
			//	Obtine dia
			line = sline.substr(index+1); // sin mes
			index = line.find(" "); // aparición de espacio
			int dia = stoi(line.substr(0, index));

            // Se obtiene hora
			line = sline.substr(index+1); // sin día
			index = line.find(":"); // aparición de :
		    int hora = stoi(line.substr(0, index));

            // Se obtiene minuto
			line = sline.substr(index+1); // sin hora
			index = line.find(":"); // aparición de :
			int minuto = stoi(line.substr(0, index));

            // Se obtiene segundo
			line = sline.substr(index+1); // sin minuto
			index = line.find(":"); // aparición de :
			int segundo = stoi(line.substr(0, index));

            // Se obtiene restaurante
			line = sline.substr(index+1); // sin minuto
			index = line.find(":"); // aparición de :
			string r = line.substr(0, index);

            // Se obtiene orden
			line = sline.substr(index+1); // sin minuto
			index = line.find(":"); // aparición de :
			string o = line.substr(0, index);

            // Se obtiene orden
			line = sline.substr(index+1); // sin minuto
			index = line.find("("); // aparición de :
			int price = stoi(line.substr(0, index));
            
            // string mes, int dia, int hora, int minuto, int segundo, string restaurante, string orden, double price
            Item itemA(mes, dia, hora, minuto, segundo, r, o, price);
            cout << itemA.show() << endl;
		}
    }

    //Item itemB("broken sword", 5.00);
    //Jun 24 19:39:45 R:La Terraza del Mar O:Falafel con Hummus(284) 

    //cout << itemA.show() << endl;
    //cout << itemB.show() << endl;

    //if(itemA < itemB){ cout << "Más barato: " << endl << itemA.show() << endl; }
    //else if(itemA > itemB){cout << "Más barato: " << endl << itemB.show() << endl; }
    //else{ cout << "Son iguales :)" << endl; }

    return 0;
}