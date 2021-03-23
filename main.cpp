#include <iostream>
#include "queue.h"
#include <cassert>	// assert

/**
	Funtore per l'uguaglianza tra interi

	@brief funtore per l'uguaglianza tra interi
*/
struct equal_int {
	bool operator()(int a, int b) const {
		return a==b;
	}
};

/**
	Predicato di confronto del valore con 10
	La valutazione è fatta sul numero intero
	Ritorna true se il valore è minore, false altrimenti

	@brief predicato per il confronto tra operatori
*/
struct predicate_int {
	bool operator()(int val) const {
		return val==6;	
	}
};

/**
	Operatore sul valore che aggiunge 10
	Restituisce il valore modificato

	@brief operatore sul valore
*/
struct generic_operator_int {
	int operator()(int val) {
		return val+10;
	}
};

typedef queue<int, equal_int> qint;

void test_metodi_fondamentali() {
	
	qint q;

	q.enqueue(4);
	q.enqueue(8);
	q.enqueue(2);
	std::cout << "Stampa di queue dopo inserimento" << std::endl << q << std::endl;

	qint q2(q);
	std::cout << "Stampa di q2 riempita attraverso q2(q)" << std::endl << q2 << std::endl;

	qint q3;
	q3 = q;
	std::cout << "Stampa di q3 riempita attraverso q3=q" << std::endl << q3 << std::endl;

	q.clear();
	std::cout << "Dimensione q dopo clear: " << q.size() << std::endl;
}

void test_uso() {

	int a[8] = {2, 50, 47, 4, 6, 8, 9, 75};

	qint q(a, a+8);
	std::cout << "Stampa di queue costruita mediante iteratori" << std::endl << q << std::endl;

	std::cout << "Grandezza di queue: " << q.size() << std::endl;
	assert(q.size()==8);

	bool check1 = q.find(8);
	assert(check1 == true);

	bool check2 = q.find(12);
	assert(check2 == false);

	q.dequeue();
	std::cout << "Queue dopo l'eliminazione dell'elemento più vecchio" << std::endl << q << std::endl;

	int first = q.getFirst();
	std::cout << "Primo elemento inserito" << std::endl << first << std::endl;
	int last = q.getLast();
	std::cout << "Ultimo elemento inserito" << std::endl << last << std::endl;

	q.setFirst(30);
	std::cout << "Primo elemento modificato" << std::endl << q << std::endl;
	q.setLast(61);
	std::cout << "Ultimo elemento modificato" << std::endl << q << std::endl;

	transformif(q, predicate_int(), generic_operator_int());
	std::cout << "Queue modificata se verificato il predicato" << std::endl << q << std::endl;
}

/**
	Funtore per l'uguaglianza tra stringhe

	@brief funtore per il confronto tra stringhe
*/

struct equal_string {
	bool operator() (const std::string &a, const std::string &b) const {
		return a==b;
	}	
};

/**
	Struct point che implementa un punto 2D

	@brief struct point che implementa un punto 2D
*/
struct point {
	int x;		///< coordinata x del punto
	int y;		///< coordinata y del punto
	point(int xx, int yy) : x(xx), y(yy) {}
};

/**
	Funtore per il confronto di uguaglianza tra due punti
	Ritorna true se le coordinate del due punti coincidono

	@brief funtore per il confronto tra due punti
*/
struct equal_point {
	bool operator()(const point &p1, const point &p2) const {
		return (p1.x==p2.x) && (p1.y==p2.y);
	}
};


std::ostream &operator<<(std::ostream &os, const point &p) {
	std::cout<<"("<<p.x<<","<<p.y<<")";
	return os;
}

void test_list_int(qint &other) {
	std::cout << "TEST SU LISTA DI INTERI" << std::endl;
	
	other.enqueue(84);
	other.enqueue(2);
	other.enqueue(66);
	other.enqueue(35);

	std::cout << "Stampa con operator<<" << std::endl;
	std::cout << other << std::endl;

	std::cout<< "Dimensione della lista: " << other.size() << std::endl;

	std::cout << "Stampa con iteratori" << std::endl;
	qint::const_iterator i,ie;
	for (i=other.begin(), ie=other.end(); i!=ie; ++i)
		std::cout << *i << std::endl;

	bool check1 = other.find(66);
	assert(check1 == true);

	bool check2 = other.find(12);
	assert(check2 == false);

	other.setFirst(30);
	std::cout << "Primo elemento modificato" << std::endl << other << std::endl;
	other.setLast(61);
	std::cout << "Ultimo elemento modificato" << std::endl << other << std::endl;

	other.clear();
	std::cout << "Dimensione della lista dopo il clear(): " << other.size() << std::endl;
}

void test_funtore_stringhe(void) {
	std::cout << "TEST SU LISTA DI STRINGHE" << std::endl;

	queue<std::string, equal_string> qs;

	qs.enqueue("tizio");
	qs.enqueue("caio");
	qs.enqueue("sempronio");

	std::cout << "Stampa con operator<<" << std::endl;
	std::cout << qs << std::endl;

	std::cout << "Dimensione della queue: " << qs.size() << std::endl;

	bool check1 = qs.find("caio");
	assert(check1 == true);

	bool check2 = qs.find("calippo");
	assert(check2 == false);

	qs.setFirst("ciao");
	std::cout << "Primo elemento modificato" << std::endl << qs << std::endl;
	qs.setLast("mamma");
	std::cout << "Ultimo elemento modificato" << std::endl << qs << std::endl;
}

void test_list_point(void) {
	queue<point, equal_point> qp;

	std::cout << "TEST SU LISTA DI POINT" << std::endl;

	qp.enqueue(point(1,1));
	qp.enqueue(point(1,2));
	qp.enqueue(point(7,1));
	qp.enqueue(point(5,3));
	qp.enqueue(point(8,0));

	std::cout << "Stampa con operator<<" << std::endl;
	std::cout << qp << std::endl;

	std::cout << "Dimensione della queue: " << qp.size() << std::endl;

	std::cout << "Stampa con iteratori" << std::endl;
	queue<point, equal_point>::const_iterator i,ie;
	for(i=qp.begin(), ie=qp.end(); i!=ie; ++i)
		std::cout << *i << std::endl;
	
	bool check1 = qp.find(point(7,1));
	assert(check1 == true);

	bool check2 = qp.find(point(0,0));
	assert(check2 == false);

	qp.setFirst(point(4,4));
	std::cout << "Primo elemento modificato" << std::endl << qp << std::endl;
	qp.setLast(point(10,10));
	std::cout << "Ultimo elemento modificato" << std::endl << qp << std::endl;
}

int main (int argc, char const *argv[]) {
	
	test_metodi_fondamentali();

	test_uso();

	qint qint;

	test_list_int(qint);

	test_funtore_stringhe(); 

	test_list_point();

	return 0;
}
