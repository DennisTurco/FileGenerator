#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <time.h>

void ordinatore_su_file(int *array, const int &dim, const char *nome, const std::string &delimitatore){
	std::ofstream file;
	char *nome2 = new char[32 + strlen("_ordinato")]; // il nuovo file avra' la lunghezza del primo piu' la lunghezza della stringa "_ordinato".
	char *estensione = new char[10];
	int index = 0;

	for (int i=0; i<32; i++){
		if (nome[i] != '.'){
			nome2[i] = nome[i];
			nome2[i+1] = '\0';
		}
		else {
			//trovo l'estensione
			for (int j=i; j<10; j++){
				estensione[index] = nome[j];
				estensione[index+1] = '\0';
				index++;
			}
		}	
	}

	strcat(nome2, "_ordinato");
	if (index != 0) strcat(nome2, estensione); // concateno solo se il nome ha un estensione
	file.open(nome2);
	
	//ORDINAMENTO DEI VALORI NEL FILE (ordinamento poco efficiente ma non mi interessa fare poche letture dell'array)
	int temp;
	for (int i=0; i<dim; i++){
		for (int j=i+1; j<dim; j++){
			if (array[i] > array[j]){
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
	
	//STAMPA DEL NUOVO FILE ORDINATO
	file<<"Numeri generati: "<<dim<<std::endl;
	for (int i=0; i<dim; i++){
		file<<array[i];
		if(i != dim-1) file<<delimitatore; // non voglio che mi aggiunga il delimitatore all'ultimo elemento
	}
		
	file.close();
}

int *generatore_su_file(std::ostream& file, const int &numeri_da_generare, const int &start, const int &end, const std::string &delimitatore){
	srand(time(NULL)); // Inizializza generatore di numeri pseudo-casuali
	
	int contatore = 0;
	int random;
	int *contenitore = new int[numeri_da_generare];
	
	// generazione randomica
	while (contatore < numeri_da_generare){
		random = rand() % (end-start+1) + start; //int randNum = rand()%(max-min + 1) + min;
		file<<random;
		if(contatore != numeri_da_generare-1) file<<delimitatore; // non voglio che mi aggiunga il delimitatore all'ultimo elemento
		contenitore[contatore] = random;
		contatore++;
	}
	
	return contenitore;
	
}

int main (void) {	
	std::ofstream f1;	
	char *nome_file = new char[32];
	std::cout<<"\tCreated By Dennis Turco\n";	
	
	std::cout<<"Inserire nome file: ";
	std::cin.getline(nome_file, 32);
	f1.open(nome_file);


	// -------------------------------- GENERAZIONE
	int numeri_da_generare;
	int inizio, fine;
	char *delimitatore = new char[5];

	std::cout<<"Quantita' di numeri da generare: ";
	std::cin>>numeri_da_generare;
	std::cout<<"A partire da: ";
	std::cin>>inizio;
	std::cout<<"Fino a: ";
	std::cin>>fine;	
	std::cin.ignore(10000, '\n'); // pulisco il cin
	std::cout<<"Carattere/i di spaziatura (max 5 caratteri): ";
	std::cin.getline(delimitatore, 5);
	f1<<"Numeri generati: "<<numeri_da_generare<<std::endl;
	
	system("cls");
	int *contenitore = generatore_su_file(f1, numeri_da_generare, inizio, fine, delimitatore);
	std::cout<<"\nStampa terminata!\n";

	char scelta;
	std::cout<< ("Vuoi ordinare in modo crescente i valori del file? (s/n): ");
	
	do {
		std::cin>>scelta;
		if (scelta == 's') {
			//-------------------------------- ORDINAMENTO
			ordinatore_su_file(contenitore, numeri_da_generare, nome_file, delimitatore);
			std::cout<<"Ordinamento completato!\n";
			break;
		}
		else if (scelta == 'n') {
			break;
		}
		else {
			std::cin.ignore(10000, '\n'); // pulisco il cin
			std::cout<<"Errore!! Ripetere l'immissione: ";
		}
		
	} while (true);
			
	f1.close();

	system("pause");

	return EXIT_SUCCESS;	
}