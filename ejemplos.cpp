#include <iostream>
using namespace std;

class Item{
    private:
        string mes, restaurante, plato;
        int dia, hora, minuto, segundo;
        double price;
    public:
        Item(string name, double price){
            this -> mes = mes;
            this -> restaurante = restaurante;
            this -> plato = plato;
            this -> dia = dia;
            this -> hora = minuto;
            this -> segundo = segundo;
            this -> price = price;
        }
        string show(){ 
            return "Name: " + this -> restaurante + "\tPrice: " + to_string(this -> price); 
        }

        bool operator< (const Item& otro) const // & indica que no es copia, es referencia
        // los dos const son para que nunca se modifique cont ni el objeto que evoca la función
        { return this -> price < otro.price; } // this (izq) ItemA, otro (der) itemB 

        bool operator> (const Item& otro) const
        { return this -> price > otro.price; }

        bool operator== (const Item& otro) const
        { return this -> price == otro.price; }

        bool operator>= (const Item& otro) const
        { return this -> price == otro.price; }

        bool operator<= (const Item& otro) const
        { return this -> price <= otro.price; }
};

int main(){
    Item itemA("magic scroll", 85.00);
    Item itemB("broken sword", 5.00);
    //Jun 24 19:39:45 R:La Terraza del Mar O:Falafel con Hummus(284) 

    cout << itemA.show() << endl;
    cout << itemB.show() << endl;

    if(itemA < itemB){ cout << "Más barato: " << endl << itemA.show() << endl; }
    else if(itemA > itemB){cout << "Más barato: " << endl << itemB.show() << endl; }
    else if(itemA == itemB){ cout << "Son iguales :)" << endl; }
    else if(itemA <= itemB){ cout << endl;}
    else if(itemA >= itemB){ cout << endl; }

    return 0;
}