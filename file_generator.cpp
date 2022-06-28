/*
	Author	-> Dennis Turco 2022
	Email 	-> dennisturco@gmail.com
	WebSite	-> https://dennisturco.github.io/
	GitHub	-> https://github.com/DennisTurco
*/

#include <iostream>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <time.h>

void sort_on_file(int *array, const int &dim, const char *name, const std::string &delimiter){
	std::ofstream file;
	char *name2 = new char[32 + strlen("_sorted")]; // the new file will have the length of the first one plus the length of the string "_sorted"
	char *extension = new char[10];
	int index = 0;

	for (int i=0; i<32; i++){
		if (name[i] != '.'){
			name2[i] = name[i];
			name2[i+1] = '\0';
		}
		else {
			//i find the extension
			for (int j=i; j<10; j++){
				extension[index] = name[j];
				extension[index+1] = '\0';
				index++;
			}
		}	
	}

	strcat(name2, "_sorted");
	if (index != 0) strcat(name2, extension); // concatenate only if the name has an extension
	file.open(name2);
	
	//Sorting of values in the file (sorting not very efficient, but i'm not interested in doing a few reads of the array)
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
	
	//print of the new sorted file
	file<<"Numbers generated: "<<dim<<std::endl;
	for (int i=0; i<dim; i++){
		file<<array[i];
		if(i != dim-1) file<<delimiter; // i don't want to add the delimiter to the last element
	}
	
	// delete
	delete []name2;
	delete []extension;

	file.close();
}

int *generator_on_file(std::ostream& file, const int &number_to_generate, const int &start, const int &end, const std::string &delimiter){
	srand(time(NULL)); // Inizialize pseudo random number generator
	
	int count = 0;
	int random;
	int *container = new int[number_to_generate];
	
	// random generation
	while (count < number_to_generate){
		random = rand() % (end-start+1) + start; //int randNum = rand()%(max-min + 1) + min;
		file<<random;
		if(count != number_to_generate-1) file<<delimiter; // i don't want to add the delimiter to the last element
		container[count] = random;
		count++;
	}
	
	return container;
	
}

int main (void) {	
	std::ofstream f1;	
	char *file_name = new char[32];
	std::cout<<"\tCreated By Dennis Turco\n";	
	
	std::cout<<"Enter file name: ";
	std::cin.getline(file_name, 32);
	f1.open(file_name);


	// -------------------------------- Generating
	int number_to_generate;
	int start, end;
	char *delimiter = new char[5];

	std::cout<<"Amount of numbers to generate: ";
	std::cin>>number_to_generate;
	std::cout<<"From: ";
	std::cin>>start;
	std::cout<<"To: ";
	std::cin>>end;	
	std::cin.ignore(10000, '\n'); // clean the cin
	std::cout<<"Space character/s (max 5 characters): ";
	std::cin.getline(delimiter, 5);
	f1<<"Numbers generated: "<<number_to_generate<<std::endl;
	
	system("cls");
	int *container = generator_on_file(f1, number_to_generate, start, end, delimiter);
	std::cout<<"\nPrint finished!\n";

	char choose;
	std::cout<< ("Do you want to sort the file values in ascending order? (y/n): ");
	
	do {
		std::cin>>choose;
		if (choose == 'y') {
			//-------------------------------- Sorting
			sort_on_file(container, number_to_generate, file_name, delimiter);
			std::cout<<"Sorting completed!\n";
			break;
		}
		else if (choose == 'n') {
			break;
		}
		else {
			std::cin.ignore(10000, '\n'); // clean the cin
			std::cout<<"Error!! Repeat the entry: ";
		}
		
	} while (true);
	
	// delete
	delete []file_name;
	delete []delimiter;
	delete []container;

	f1.close();

	system("pause");

	return EXIT_SUCCESS;	
}