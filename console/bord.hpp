// bord.hpp

struct zet {
	// datastructuur om een zet te beschrijven
	int speler;		// speler die de zet doet
	int xbron;		// x coordinaat van het virus waarmee gespeeld wordt
	int ybron;		// y coordinaat van het virus waarmee gespeeld wordt
	int xdoel;		// x coordinaat van het voelvakje
	int ydoel;		// y coordinaat van het voelvakje
	int aantal;		// hulpvariabele: getelde aantal mogelijke zetten
					// (om te kunnen communiceren tussen functies)
};

class ataxxbord {
	// klasse die het ataxx speelbord en acties daarop omschrijft
public:
	struct zet randomzet (int speler);		// bedenk een willekeurige zet
	struct zet strategiezet (int speler);	// bedenk een slimme zet
	struct zet allezetten (int speler, int maxzet);	// doorloopt alle zetten
	bool toegestanezet (zet test);	// controleer of een zet toegestaan is
	void doezet (zet doen);			// voert een zet uit
	void drukaf();					// toont het speelveld op het scherm
	void drukaf_stats();			// toont spelersinfo op het scherm
	void beginstand();				// initialiseer de beginstand
	int telvirussen (int speler);	// telt aantal virussen van een speler
	bool bestaanmogelijkezetten (int speler);	// kan speler nog zetten?
	ataxxbord (int aantalkolommen, int aantalrijen);	// constructor
	~ataxxbord();		// destructor
	int ** veld;		// pointer naar twee-dimensionale dynamische array
						// die het speelveld bevat: 0 = leeg veld,
						// 1 = bezet door speler 1, 2 = bezet door speler 2
	int maxkolom;		// breedte
	int maxrij;			// hoogte
};
