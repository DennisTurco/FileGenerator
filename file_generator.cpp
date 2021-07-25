#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

void generatore (ostream&, char[]);
void ordinatore (const ostream&, int[], int, char[]);

int main (){	
	ofstream f1;	
	char string[32];
	cout<<"\tCreated By Dennis Turco\n";	
	
	cout<<"Inserire nome file: ";
	cin.getline(string, 32);
	f1.open(string);
	
	
	system("cls");
	generatore(f1, string);
	
	/*srand(time(NULL)); // Inizializza generatore di numeri pseudo-casuali
	int contatore = 0;
	int contatore2 = 0;
	int numero;
	int numeri_da_generare;
	int inizio, fine;	
	
	cout<<"Quantita' di numeri da generare: ";
	cin>>numeri_da_generare;
	cout<<"A partire da: ";
	cin>>inizio;
	cout<<"Fino a: ";
	cin>>fine;	
	f1<<"Numeri generati: "<<numeri_da_generare<<endl;
	while (contatore<numeri_da_generare){
		numero = rand();
		cout<<numero<<endl;
		if (numero>=inizio && numero<=fine){
			f1<<numero<<endl;
			contatore++;
		}
	}
	*/
			
	f1.close();
	system("pause");
	return 0;	
}

void ordinatore(const ostream& f1, int array[], int dim, char nome[]){
	ofstream f2;
	char nome2[32];
	for (int i=0; i<32; i++){
		if (nome[i] != '.')
			nome2[i] = nome[i];
		else break;
	}
	strcat (nome2, "_ordinato.txt");
	f2.open(nome2);
	
	//ORDINAMENTO DEI VALORI NEL FILE	
	int temp;
	for (int i=0; i<dim; i++){
		for (int j=i+1; j<dim; j++){
			if (array[i]>array[j]){
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
	
	//STAMPA DEL NUOVO FILE ORDINATO
	f2<<"Numeri generati: "<<dim<<endl;
	for (int i=0; i<dim; i++){
			f2<<array[i]<<endl;
	}
		
	cout<<"Ordinamento completato!";
	f2.close();
	return;
}

void generatore(ostream& f1, char nome[]){
	srand(time(NULL)); // Inizializza generatore di numeri pseudo-casuali
	int contatore = 0;
	int contatore2 = 0;
	int numero;
	int numeri_da_generare;
	int inizio, fine;	
	
	cout<<"Quantia' di numeri da generare: ";
	cin>>numeri_da_generare;
	cout<<"A partire da: ";
	cin>>inizio;
	cout<<"Fino a: ";
	cin>>fine;	
	f1<<"Numeri generati: "<<numeri_da_generare<<endl;
	
	int contenitore[numeri_da_generare];
	
	while (contatore < numeri_da_generare){
		numero = rand();
		if(numero>fine){	
			for (int i=0; i<10; i++){
				numero = numero/2;
				if(numero>=inizio && numero<=fine){
					f1<<numero<<endl;
					contenitore[contatore] = numero;
					contatore++;
					break;
				}
			}	
		}
		
		if (numero>=inizio && numero<=fine){
			f1<<numero<<endl;
			contenitore[contatore] = numero;
			contatore++;
		}
		
		if (numero<inizio){
			for (int i=0; i<10; i++){
				numero = numero*2;
				if(numero>=inizio && numero<=fine){
					f1<<numero<<endl;
					contenitore[contatore] = numero;
					contatore++;
					break;
				}
			}
		}
		contatore2++;
	}
	
	cout<<"Numero totale di numeri cercati: "<<contatore2; 
	cout<<"\nStampa terminata!\n";
	
	char scelta;
	cout<< ("Vuoi ordinare in modo crescente i valori del file? (s/n): ");
	cin>>scelta;
	if (scelta=='s')
		ordinatore(f1, contenitore, numeri_da_generare, nome);
	
	return;
}
