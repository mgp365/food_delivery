	//rm ./ejemploLeeArchivo.exe; g++ ejemploLeeEscribe.cpp -o ejemploLeeEscribe; ./ejemploLeeEscribe.exe
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <fstream>
#include <string.h>
using namespace std;

// using std::cin;
// using std::cout;
// using std::endl;


//	Ejemplos para leer lineas y luego escribirlas en otros archivos, con C/C++

int main(int argc, char* argv[]) 
{	// C/C++
	char line[1000];

	FILE *inputFile;           // punteros a archivos
	FILE *outputFile;
	
	// fopen: abre archivos para leer (r) y escribir (w)
	if ( (inputFile = fopen("orders.txt","r") ) == NULL)
	{	cout << "error "<< endl; 	}
	
	if ( (outputFile = fopen("salida.txt","w") ) == NULL)
	{	cout << "error "<< endl; 	}

	// Lee cada linea del archivo de entrada y la escribe en el archivo de salida, solo copia
    while (  fscanf(inputFile,"%[^\n]\n", line) != EOF )
	{	printf("Read:\t%s\n", line);

		fprintf(outputFile, "%s\n", line );
	}

	fclose(inputFile);
	fclose(outputFile);



	//	C++
	string sline;
	int index;

	ifstream inFile("orders.txt"); 	    //  input file stream
	ofstream outFile("salida2.txt");		//	output file stream	
	
	//	Verifica que los archivos se hayan abierto correctamente
	if (inFile.is_open() && outFile.is_open() )		
	{	//	Lee linea a linea
		while ( getline(inFile, sline) )		
		{	cout << "Read:\t"<< sline << endl;			
			outFile << sline << endl;

			// Se obtiene el mes: 
			string line = sline; //pasar string auxiliar
			index = line.find(" "); // primera aparición de espacio (índice 3)
			string mes = line.substr(0, index); //guarda mes aquí
			
			//	Obtine dia
			line = sline.substr(index+1); // sin mes
			index = line.find(" "); // aparición de espacio
			string dia = line.substr(0, index);

            // Se obtiene hora
			line = sline.substr(index+1); // sin día
			index = line.find(":"); // aparición de :
			string hora = line.substr(0, index);

            // Se obtiene minuto
			line = sline.substr(index+1); // sin hora
			index = line.find(":"); // aparición de :
			string minuto = line.substr(0, index);

            // Se obtiene segundo
			line = sline.substr(index+1); // sin minuto
			index = line.find(":"); // aparición de :
			string segundo = line.substr(0, index);
		}
	} 

	inFile.close();
	outFile.close();

	//	atoi, convesiones de string a entero

	// Mas info
	// C++ 	https://cplusplus.com/doc/tutorial/files/
	// C 	https://www.programiz.com/c-programming/c-file-input-output
	

}