#include <stdio.h>
#include <stdlib.h>

typedef struct Nakup {
	int pocetParku;
	int pocetChlebu;
}Nakup;

Nakup* nacist(char *nazevSouboru, int* pocetNakupu) {
	char line[50];

	FILE* input = fopen(nazevSouboru, "r");
	fgets(line, sizeof(line), input);
	*pocetNakupu = atoi(line);

	Nakup* poleNakupu = (Nakup*)malloc((int)pocetNakupu * sizeof(Nakup*));

	int counter = 0;
	while (fgets(line, sizeof(line), input) != NULL) {
		Nakup temp;
		temp.pocetParku = atoi(line);
		fgets(line, sizeof(line), input);
		temp.pocetChlebu = atoi(line);
		poleNakupu[counter] = temp;
		counter++;
	}

	fclose(input);
	return poleNakupu;
}

Nakup* vypisNakupu(Nakup* vypisovanePole, int velikostPole) {
	for (int i = 0; i < velikostPole; i++){
		printf("Nakup cislo %d ... parky: %d, chleba: %d\n", 
			i+1, 
			vypisovanePole[i].pocetParku, 
			vypisovanePole[i].pocetChlebu);
	}
}

double prumernaCenaNakupu(Nakup* poleNakupu, int velikostPole) {
	double suma = 0;
	int cenaParku = 12;
	int cenaChleba = 2;
	for (int i = 0; i < velikostPole; i++) {
		suma += poleNakupu[i].pocetParku * cenaParku + poleNakupu[i].pocetChlebu * cenaChleba;
	}
	return (suma / velikostPole);
}

int cenaNakupu(Nakup nakup) {
	int cenaParku = 12;
	int cenaChleba = 2;
	return (nakup.pocetParku * cenaParku + nakup.pocetChlebu * cenaChleba);
}

Nakup nejdrazsiNakupUlozitDoSouboru(Nakup* poleNakupu, int velikostPole) {
	Nakup nejdrazsiNakup = poleNakupu[0];	
	int cenaParku = 12;
	int cenaChleba = 2;
	for (int i = 0; i < velikostPole; i++) {
		if (cenaNakupu(poleNakupu[i]) > cenaNakupu(nejdrazsiNakup)) {
			nejdrazsiNakup = poleNakupu[i];
		}
	}
	char pocetParku[10];
	char pocetChlebu[10];
	sprintf(pocetParku, "%d", nejdrazsiNakup.pocetParku);
	sprintf(pocetChlebu, "%d", nejdrazsiNakup.pocetChlebu);
	char vystup[500] = "Nejdrazsi nakup ... pocet parku: ";
	strcat(vystup, pocetParku);
	strcat(vystup, " a pocet chlebu: ");
	strcat(vystup, pocetChlebu);

	FILE* output = fopen("nejdrazsiNakup.txt", "w");

	fputs(vystup, output);
	fputs(vystup, stdout);
	
	return nejdrazsiNakup;
}

void freeNakupy(Nakup* nakupy) {
	free(nakupy);
}

int main() {
	int pocetNakupu = 0;
	
	Nakup* poleNakupu = nacist("nakupy.txt", &pocetNakupu);
	printf("Pocet nakupu v souboru: %d\n\n", pocetNakupu);
	
	vypisNakupu(poleNakupu, pocetNakupu);

	printf("\nPrumerna cena jednoho nakupu je: %fKc.\n", prumernaCenaNakupu(poleNakupu, pocetNakupu));

	nejdrazsiNakupUlozitDoSouboru(poleNakupu, pocetNakupu);

	freeNakupy(poleNakupu);
	return 0;
}