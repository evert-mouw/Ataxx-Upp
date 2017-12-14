// hulpfuncties.cpp

// prototypes
char invoer();
void infoblok();
void wachten();
int leesgetal (int max);
long willekeur (int max);
bool oneven (int getal);
void spelerwissel (int & speler);

char invoer() {
	// vraagt invoer van een keuze
	// alleen het eerste ingevoerde karakter wordt werkelijk benut
	char keuze;	// voor invoer van een menukeuze
	cout << endl;
	cout << "Geef uw keuze d.m.v. een enkele letter of cijfer ";
	cout << "gevolgd door enter." << endl;
	cin.get (keuze);
	if ( keuze != '\n' ) cin.ignore(256, '\n'); // invoerbuffer legen
	// kleine letters omzetten in hoofdletters
	if (keuze > 96 && keuze < 123) keuze -= 32;
	return keuze;
}

void infoblok() {
// toont de inforegels
	cout << "/-----------------------------------------------------\\" << endl;
	cout << "| 2006-12-02                                          |" << endl;
	cout << "| Evert Mouw, S0332291, emouw@liacs.nl (keuzevakker)  |" << endl;
	cout << "| vierde programmeeropgave                            |" << endl;
	cout << "|                                                     |" << endl;
	cout << "|                    ATAXX                            |" << endl;
	cout << "|                                                     |" << endl;
	cout << "| Speel een spelletje ataxx!                          |" << endl;
	cout << "|                                                     |" << endl;
	cout << "\\-----------------------------------------------------/" << endl;
	cout << endl;
}

void wachten() {
	// wacht op een enter (soort pause)
	char k;		// voor invoer van een willekeurig karakter
	cout << "Druk op enter om verder te gaan." << endl;
	cin.get(k);
	if ( k != '\n' ) cin.ignore(256, '\n'); // invoerbuffer legen
}

int leesgetal (int max) {
	// verkrijgt invoer van stdin, zet het om in een positief getal
	// en retourneer dit getal
	// max = maximaal aantal in te lezen posities (cijfers)
	// indien verkeerde invoer, retourneer dan -1
	int i;				// hulpvariabele voor iteratie
	bool stop = false;		// hulpvariabele ivm stop invoer
	int getal = 0;			// de te berekenen retourneerwaarde
	char regel[256];		// om de invoerbuffer uit te lezen
	cin.get (regel,256);
	cin.ignore(256, '\n');		// invoerbuffer legen
	for (i=0; i<max; i++) {
		if ( regel[i] > 47 && regel[i] < 58 ) {
			// getal = regel[i] - 48;
			getal = getal * 10 + ( regel[i] - 48 );
		}
		else {
			if ( regel[i] == '\0' || regel[i] == '\r'
				|| regel[i] == '\n' || stop ) {
				stop = true;
			}
			else {
				return -1;
			}
		}
	}
	return getal;
}

long willekeur (int max) {
	// pseudoramdom getal genereren mbv cosinus en teller
	// (cmath bibliotheek nodig)
	static long int getal = max/2;	// te bepalen willekeuig getal
	static int teller = 0;		// elke nieuwe aanroep onthouden
	teller++;
	getal = (long int) ( ( cos( (double)getal ) * cos( (double)teller ) )
		* (max+1) );
	if (getal<0) getal *= -1;
	return getal;
}

bool oneven (int getal) {
	if ( getal % 2 > 0 ) return true;
	else return false;
}

void spelerwissel (int & speler) {
	// wisselen van speler 1 en 2
	if (speler==1) speler=2;
	else speler=1;
}
