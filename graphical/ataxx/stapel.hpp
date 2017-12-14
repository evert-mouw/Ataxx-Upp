// stapel.hpp

class linkedlist {
	// beschrijft een linked list voor ataxx speelborden
public:
	class ataxxbord * stelling;				// het ataxx bord
	struct linkedlist * vorige;				// eerder bord
	struct linkedlist * volgende;			// volgend bord
	linkedlist();							// standaard constructor
	linkedlist (int kolommen, int rijen);	// constructor (overloaded)
	~linkedlist();							// destructor
};

class stapel {
	// de stapel bestaat uit een linked list van ataxx bordobjecten
	// en een aantal functies om borden toe te voegen of weg te halen
public:
	void zetopstapel (const ataxxbord * bord);	// voeg een bord toe
	void haallaatstevanstapel();				// verwijder het laatste bord
	bool isstapelleeg();						// test of de stapel leeg is
	linkedlist * lijst;							// de lijst met borden
	stapel();									// constructor
	~stapel();									// destructor
};
