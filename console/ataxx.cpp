/*
	Evert Mouw
	emouw@liacs.nl
	S 0332291
	Programmeermethoden
	4e programmeeropdracht, ATAXX
	2006-12-02
*/

// main

#include <iostream>
#include <cmath>		// om pseudorandom getallen te krijgen dmv cosinus
#include "bord.hpp"
#include "stapel.hpp"
using namespace std;
#include "hulpfuncties.cpp"
#include "bord.cpp"
#include "stapel.cpp"

//prototypes
void toon_computerzet (zet invoer);
void toon_infonieuwezet (int speler);

int main() {
	int kolommen, rijen;		// invoer grootte speelbord
	int x,y;					// hulpvariabelen voor bewerkingen op bord
	int speler = 1;				// aan de beurt; speler 1 begint altijd
	bool slim;					// random zetten of slimme zetten?
	int hulp;					// hulpvariabele
	zet invoer;					// ingevoerde zet (struct)
	ataxxbord * bord;			// class ataxxbord
	bool geldigeinvoer;			// was de invoer geldig?
	stapel geheugen;			// om zetten te onthouden
	bool herinner = true;		// wel of geen zetten onthouden?

	infoblok();					// toon algemene info over het programma

	// invoer grootte bord
	cout << "Hoeveel kolommen (x) (oneven, max=99) ? ";
	kolommen = leesgetal(2);
	cout << "Hoeveel rijen (y) (oneven, max=99) ? ";
	rijen = leesgetal(1);
	if ( kolommen==-1 || rijen==-1 || ! oneven(kolommen) || ! oneven(rijen) ) {
		cout << "Onjuiste invoer voor kolommen en/of rijen." << endl;
		return -1;
	}

	// invoer speler
	cout << "Speelt u speler 1 of speler 2 (speler 1 begint) ? ";
	invoer.speler = leesgetal(2);
	cout << "U bent speler " << invoer.speler << endl;

	// invoer wel/niet willekeur
	cout << "Moet computer willekeurige (0) of " <<
		"slimme (1) zetten doen (0|>=1) ? ";
	slim = (bool) leesgetal(1);
	if (slim) cout << "De computer speelt een beetje slim." << endl;
	else cout << "De computer speelt willekeurig." << endl;

	// maak een nieuw ataxxbord object en toon 'm
	bord = new ataxxbord (kolommen,rijen);
	bord->drukaf();

	// speel door zolang beide partijen nog virussen hebben en
	// minstens een van de partijen nog een zet kan doen
	while ( bord->telvirussen(speler) > 0 && ( bord->bestaanmogelijkezetten(1)
		|| bord->bestaanmogelijkezetten(2) ) ) {
		if ( bord->bestaanmogelijkezetten(speler) ) {
			// invoer van zet
			if ( speler==invoer.speler ) {
				do {
					if (herinner) geheugen.zetopstapel (bord);
					cout << endl;
					toon_infonieuwezet (speler);
					cout << "bron x ? ";
					invoer.xbron = leesgetal(kolommen) - 1;
					// invoer voor terugzetten ondervangen en afhandelen
					if ( invoer.xbron==-2 ) {
						herinner = false;
						geheugen.haallaatstevanstapel();
						// stelling terughalen vanuit het geheugen
						if ( geheugen.lijst->stelling != NULL ) {
							cout << "We doen een zet terug!" << endl;
							for (x=0;x<kolommen;x++) {
								for (y=0;y<rijen;y++) {
									bord->veld[x][y] =
										geheugen.lijst->stelling->veld[x][y];
								}
							}
							spelerwissel (speler);
						}
						else cout << "Kan niet verder terug." << endl;
						bord->drukaf();
					}
					// invoer voor stoppen ondervangen en afhandelen
					if ( invoer.xbron==-1 ) {
						cout << "Bedankt voor het spelen." << endl;
						return 0;
					}
					// normale invoer voor een zet vervolgen
					if ( invoer.xbron>=0 ) {
						herinner = true;
						cout << "bron y ? ";
						invoer.ybron = leesgetal(rijen) - 1;
						cout << "doel x ? ";
						invoer.xdoel = leesgetal(kolommen) - 1;
						cout << "doel y ? ";
						invoer.ydoel = leesgetal(rijen) - 1;
						// als het een toegestane zet is
						if ( bord->toegestanezet(invoer) ) {
							bord->doezet (invoer);
							bord->drukaf();
							geldigeinvoer = true;
						}
						// als het geen toegestane zet is
						else {
							cout << "De ingevoerde zet is niet toegestaan." << endl;
							cout << "Probeer het nog eens!" << endl;
							bord->drukaf();
							geldigeinvoer = false;
						}
					}
				} while ( ! geldigeinvoer );
			}
			else {
				// laat de computer spelen als die aan de beurt is
				hulp = invoer.speler;
				if (slim) invoer = bord->strategiezet(speler);
				else invoer = bord->randomzet(speler);
				toon_computerzet (invoer);
 				bord->doezet (invoer);
				bord->drukaf();
				invoer.speler = hulp; // invoer.speler herstellen
			}
		}
		// acties voor als een speler niets kan doen
		else cout << "Geen zet mogelijk voor speler " << speler << "." <<endl;
		spelerwissel (speler);
	}
	// als geen enkele speler iets kan doen, is het spel ten einde
	cout << "Einde spel: ";
	if ( bord->telvirussen(speler)==0 ) cout << "Speler " << speler
		<< " heeft geen virussen meer." << endl;
	else cout << "Beide spelers kunnen geen zet meer doen." << endl;
	bord->drukaf_stats();	// toon de stats voor de spelers

	delete bord;
	return 0;
}

void toon_computerzet(zet invoer) {
	// toont de zet van de computer op het scherm (console)
	cout << endl << "De computer speelt: (" << invoer.xbron+1 << "," <<
		invoer.ybron+1 << ") --> (" << invoer.xdoel+1 << "," <<
		invoer.ydoel+1 << ")" << endl << endl;
}

void toon_infonieuwezet (int speler) {
	// toont instructies bij de zetinvoer (console)
	cout << " ---- invoer nieuwe zet" << endl;
	cout << " ---- geef bij 'bron x' een 0 om te stoppen," << endl;
	cout << " ---- of een -1 om een zet terug te doen." << endl;
	cout << " ---- speler " << speler << endl;
}
