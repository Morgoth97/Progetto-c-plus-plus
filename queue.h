#ifndef QUEUE_H
#define QUEUE_H

#include <algorithm>
#include <iostream>
#include <ostream>

#include <iterator>  	// std::forward_iterator_tag
#include <cstddef>	// std::ptrdiff_t

/**
	Classe che implementa una coda di tipo FIFO (una queue) di dati generici T.
	
	@brief Coda di tipo FIFO (queue)

	@param T tipo di dato
	@param E funtore di uguaglianza
*/


template <typename T, typename E>
class queue {

	/**
	
		Struttura di supporto interna che implementa un elemento della queue

		@brief Elemento della queue
	*/
	
	struct element {
		T value;		///< Dato inserito nella queue
		element *next;		///< Puntatore all'elemento successivo della queue

		/**
			Costruttore di default
		*/
		element() : next(nullptr) {}

		/**
			Costruttore secondario che inizializza l'elemento

			@param v valore del dato
		*/
		element(const T &v) : value(v), next(nullptr) {}

		/**
			Costruttore secondario che inizializza l'elemento

			@param v valore del dato
			@param n puntatore al nodo successivo
		*/
		element(const T &v, element *n) : value(v), next(n) {}

		/**
			Distruttore
		*/
		~element() {
			next = nullptr;
		}
	}; //struct element


	element *_first;	///< puntatore al primo elemento inserito nella queue
	element *_last;		///< puntatore all'ultimo elemento inserito nella queue
	unsigned int _size;	///< numero di elementi nella queue

	E _eql;			///< oggetto funtore per l'uguaglianza

	/**
		Funzione helper per la rimozione ricorsiva degli elementi

		@param e elemento da rimuovere
	*/
	void clear_helper(element *e) {
		if (e != nullptr) {
			clear_helper(e->next);
			delete e;
			_size--;
			e = nullptr;
		}		
	}

	public:

	/**
		Costruttore di default
	*/
	queue() : _first(nullptr), _last(nullptr), _size(0) {}

	/**
		Costruttore di copia

		@param other queue da copiare

		@throw eccezione di allocazione di memoria
	*/
	queue(const queue &other) : _first(nullptr), _last(nullptr), _size(0) {
		element *curr = other._first;

		try {
			while (curr != nullptr) {
				enqueue(curr->value);
				curr = curr->next;
			}
		}
		catch (...) {
			clear();
			throw;
		}
	}

	/**
		Operatore di assegnamento

		@param other queue da copiare

		@return reference a this

		@throw eccezione di allocamento di memoria
	*/
	queue &operator=(const queue &other) {
		if (this != &other) {
			queue tmp(other);
			std::swap(_first, tmp._first);
			std::swap(_last, tmp._last);
			std::swap(_size, tmp._size);
		}
		return *this;
	}

	/**
		Distruttore
	*/
	~queue() {
		clear();
	}

	/**
		Cancella il contenuto della queue
	*/
	void clear() {
		clear_helper(_first);
		_first = nullptr;
		_last = nullptr;
	}

	/**
		Ritorna il numero di elementi della queue

		@return numero degli elementi inseriti
	*/
	unsigned int size () const {
		return _size;
	}

	/**
		Determina se esiste un elemento nella queue.
		L'uguaglianza è definita dal funtore di confronto

		@param value valore da cercare

		@return true se esiste l'elemento, false altrimenti
	*/
	bool find (const T &value) const {
		element *curr = _first;
		while (curr != nullptr) {
			if (_eql(curr->value, value)) {
				return true;
			}
			curr = curr->next;
		}
		return false;
	}

	/**
		Inserisce un elemento nella queue in fondo ad essa

		@param value valore da inserire

		@throw eccezione di allocamento di memoria
	*/
	void enqueue (const T &value) {
		element *tmp = new element(value);

		if (_first == nullptr) {
			_first = tmp;
			_last = tmp;
			_size++;
			return;
		}

		_last->next = tmp;
		_last = tmp;
		_size++;
	}

	/**
		Elimina il primo elemento inserito nella queue
	*/
	void dequeue () {
		if (_first == nullptr) {
			std::cout << "ERROR: operazione impossibile su coda vuota" << std::endl;
			return;
		}
		element *tmp = _first->next;
		delete _first;
		_first = tmp;
		_size--;
	} 

	/**
		Costruttore secondario che costruisce una queue a partire
		da una sequenza generica di dati identificata da due iteratori

		@param begin iteratore di inizio della sequenza
		@param end iteratore di fine della sequenza

		@throw eccezione di allocazione di memoria
	*/
	template <typename IterT>
	queue (IterT begin, IterT end) : _first(nullptr), _last(nullptr), _size(0) {
		try {
			while (begin != end) {
				enqueue(static_cast<T>(*begin));
				++begin;
			}
		}
		catch (...) {
			clear();
			throw;
		}
	}

	/**
		Ritorna il primo elemento inserito nella queue

		@return valore del primo elemento inserito
	*/
	T getFirst () const {
		return _first->value;
	}

	/**
		Modifica il valore del primo elemento inserito

		@param value valore con cui modificare l'elemento

	*/
	void setFirst (const T &value) {
		if (_first == nullptr) {
			std::cout << "ERROR: operazione impossibile su coda vuota" << std::endl;
			return;
		}
		else {
			_first->value = value;
		}
	}

	/**
		Ritorna l'ultimo elemento inserito nella queue

		@return valore dell'ultimo inserito
	*/
	T getLast () const {
		return _last->value;
	}

	/**
		Modifica il valore dell'ultimo elemento inserito

		@param value valore con cui modificare l'elemento

	*/
	void setLast (const T &value) {
		if (_last == nullptr) {
			std::cout << "ERROR: operazione impossibile su coda vuota" << std::endl;
			return;
		}
		else {
			_last->value = value;
		}
	}

	/**
		Iteratore della queue
	*/
	class const_iterator; // forward declaration

	class iterator {
		element *_e;
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef T*                        pointer;
		typedef T&                        reference;

	
		iterator() : _e(nullptr) {}
		
		iterator(const iterator &other) : _e(other._e) {}

		iterator& operator=(const iterator &other) {
			_e = other._e;
			return *this;
		}

		~iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return _e->value;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return &(_e->value);
		}

		// Operatore di iterazione post-incremento
		iterator operator++(int) {
			iterator tmp(*this);
			_e = _e->next;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		iterator& operator++() {
			_e = _e->next;
			return *this;
		}

		// Uguaglianza
		bool operator==(const iterator &other) const {
			return (_e == other._e);
		}

		// Diversita'
		bool operator!=(const iterator &other) const {
			return (_e != other._e);
		}
		
		// Solo se serve anche const_iterator aggiungere le seguenti definizioni
		friend class const_iterator;

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return (_e == other._e);
		}

		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return (_e != other._e);
		}

	private:
		friend class queue; 

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		iterator(element *e) : _e(e) {}
		
	}; // classe iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	iterator begin() {
		return iterator(_first);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	iterator end() {
		return iterator(nullptr);
	}
	
	/**
		Iteratore costante della queue
	*/
	
	class const_iterator {
		const element *_e;
		
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;

	
		const_iterator() : _e(nullptr) {}
		
		const_iterator(const const_iterator &other) : _e(other._e) {}

		const_iterator& operator=(const const_iterator &other) {
			_e = other._e;
			return *this;
		}

		~const_iterator() {}

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return _e->value;
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return &(_e->value);
		}
		
		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			_e = _e->next;
			return tmp;
		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() {
			_e = _e->next;
			return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return (_e == other._e);
		}
		
		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return (_e != other._e);
		}

		// Solo se serve anche iterator aggiungere le seguenti definizioni
		
		friend class iterator;

		// Uguaglianza
		bool operator==(const iterator &other) const {
			return (_e == other._e);
		}

		// Diversita'
		bool operator!=(const iterator &other) const {
			return (_e != other._e);
		}

		// Costruttore di conversione iterator -> const_iterator
		const_iterator(const iterator &other) : _e(other._e) {}

		// Assegnamento di un iterator ad un const_iterator
		const_iterator &operator=(const iterator &other) {
			_e = other._e;
			return *this;
		}

	private:
		friend class queue; 

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const element *e) : _e(e) {}
		
	}; // classe const_iterator
	
	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(_first);
	}
	
	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return const_iterator(nullptr);
	}
	

};  // class queue

/**
	Funzione che modifica i valori della queue che rispettano
	un predicato P attraverso una operazione F

	@param q queue da modificare
	@param pred predicato da confrontare
	@param op operazione da utilizzare per la modifica
*/
template <typename T, typename E, typename P, typename F>
void transformif (queue<T,E> &q, P pred, F op) {
	typename queue<T,E>::iterator i, ie;
	i = q.begin();
	ie = q.end();
	while (i != ie) {
		if (pred(*i)) {
			op(*i);
		}
		++i;
	}
}


template <typename T, typename E>
std::ostream &operator<<(std::ostream &os, const queue<T,E> &q) {
	typename queue<T,E>::const_iterator i, ie;
	i = q.begin();
	ie = q.end();
	while(i!=ie) {
		os << *i << " ";
		++i;
	}
	return os;
}

#endif
