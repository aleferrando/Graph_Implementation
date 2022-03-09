//
//  Graph.hpp
//
//
//  Created by Alessandro Ferrando on 17/03/21.
//

#ifndef Graph_h
#define Graph_h

#include <iostream>  // std::cout
#include <algorithm> // std::swap
#include <stdexcept>
#include <string>
#include <iterator>  // std::forward_iterator_tag
#include <cstddef>   // std::ptrdiff_t

/**
    Classe eccezione custom che deriva da std::logic_error
 
    @brief Classe eccezione custom derivata da std::logic_error
 */
class customException : public std::logic_error {
    int _value;
    std::string error_string = "";
public:
    customException(const std::string &message, int value): std::logic_error(message), _value(value), error_string(message) { };
    
    int get_value(void) const {
        return _value;
    }
    
    std::string get_error() const {
        return error_string;
    }
};

/**
    Classe che implementa un grafo diretto di dati generici di tipo T.
    L'uguaglianza tra due dati di tipo T è fatta usando un funtore di
    uguaglianza E.
 
    @brief Grafo diretto di elementi di tipo T
 
    @param T tipo del dato
    @param E funtore di comparazione (uguaglianza) tra due dati
 */
template <typename T, typename E>
class Graph {
    
    T *array;          // Puntatore all'array dinamico di T
    bool **adjMatrix;  // Puntatore array bidimensionale dinamico
    int n_node;        // Numero di nodi
    E _eql;            // Istanza del funtore di uguaglianza
    
    
public:
    /**
        @brief Costruttore di default
     
        Costruttore di default per istanziare un grafo vuoto.
     
        @post adjMatrix == nullptr
        @post n_node == 0
     */
    Graph() : array(nullptr), adjMatrix(nullptr), n_node(0){}
    
    /**
        @brief Copy constructor
     
        Costruttore di copia tra un grafo e un altro grafo.
     
        @param other grafo da copiare
        @throw eccezione allocazione di memoria
     */
    Graph(const Graph &other) : array(nullptr), adjMatrix(nullptr), n_node(0) {
        try {
        adjMatrix = new bool*[other.n_node]();
        array = new T [other.n_node]();
        n_node = other.n_node;
        
            for (unsigned int i = 0; i < other.n_node; i++) {
                adjMatrix[i] = new bool[n_node]();
                array[i] = other.array[i];
                for (unsigned int j = 0; j < other.n_node; j++)
                    adjMatrix[i][j] = other.adjMatrix[i][j];
            }
        }
        catch(...) {
            clear();
            throw;
        }
        
    }
    
    /**
        @brief Distruttore della classe
     
        Distruttore della classe. Rimuove dallo heap gli array dinamici
        allocati in precedenza.
     
     */
    ~Graph() {
        clear();
        n_node = 0;
    }
    
    /**
        Metodo per la rimozione di tutti i nodi negli array e lasciare la memoria in uno stato consistente.
     
        @brief Metodo per lasciare la memoria in uno stato consistente.
     
     */
    void clear() {
        for (unsigned int c = 0; c < n_node; c++) {
            delete[] adjMatrix[c];
        }
        delete[] adjMatrix;
        delete[] array;
        array = nullptr;
        adjMatrix = nullptr;
        n_node = 0;
    }
    
    /**
        @brief Operatore di assegnamento
     
        Operatore di assegnamento che serve per copiare il contenuto di
        other in *this.
     
        @param other Graph da copiare
        @return reference a Graph
     */
    Graph& operator=(const Graph &other) {
        if (&other != this) {
            Graph tmp(other);
            tmp.swap(*this);
        }
        return *this;
    }
    
    /**
     
        Funzione che scambia gli stati interni tra due grafi
     
        @brief Funzione di swap dei dati interni tra due grafi
     
        @param other grafo sorgente
     */
    void swap(Graph &other) {
        std::swap(this->array, other.array);
        std::swap(this->n_node, other.n_node);
        std::swap(this->adjMatrix, other.adjMatrix); 
    }

    /**
        Metodo per l'inserimento di nuovi nodi nel grafo utilizzando array di appoggio.
     
        @brief Metodo per l'inserimento di nuovi nodi nel grafo.
     
        @param node nodo che si vuole aggiungere al grafo.
     
        @throw eccezione custom che gestisce il caso in cui il nodo già esista
        @throw eccezione copia dei valori
     
    */
    void addNode(const T &node){
        if (exists(node) == true) {
            throw customException("Valore non valido!", 999);
        }
        int _n_node = n_node + 1;
        // 1. Creo (alloco) una nuova matrice e un nuovo array con n_node aumentati di +1
        bool **_adjMatrix = new bool*[_n_node](); // matrice  di appoggio temporaneo
        T *_array = new T [_n_node]();            //array di appoggio temporaneo
        for (unsigned int a = 0; a < _n_node; a++) {
            _adjMatrix[a] = new bool[_n_node]();
        }
        try {
            // 2. Copio i vecchi array in quelli nuovi e aggiungo il nodo nuovo
            for (unsigned int i = 0; i < n_node; i++) {
                _array[i] = array[i];
                for (unsigned int j = 0; j < n_node; j++) {
                    _adjMatrix[i][j] = adjMatrix[i][j];
                }
            }
            _array[n_node] = node;
            _adjMatrix[n_node][n_node] = false;
            
        } catch (...) {
            clear();
            throw;
        }
        // 3. Dealloco quelli vecchi
        clear();
        n_node = _n_node;
        array = _array;
        adjMatrix = _adjMatrix;
    }
    
    /**
     Metodo per la rimozione di nodi nel grafo utilizzando array di appoggio.
     
     @brief Metodo per lla rimozione di nodi nel grafo.
     
     @param node nodo che si vuole rimuovere dal grafo.
     
     @throw eccezione custom che gestisce il caso in cui il nodo già non esista
     @throw eccezione copia dei valori
     
     */
    void removeNode(const T &node) {
        if (exists(node) != true) {
            throw customException("Valore non valido!", 998);
        }
        // Gestire il caso in cui si tenti di rimuovere un nodo dal quale entra/esce un arco!
        for (unsigned int h = 0; h < n_node; h++) {
            if(hasEdge(node, array[h]) == true) {
                removeEdge(node, array[h]);
            }
            if(hasEdge(array[h], node) == true) {
                removeEdge(array[h], node);
            }
        }
        int _n_node = n_node - 1;
        // 1. Creo (alloco) una nuova matrice e un nuovo array con n_node diminuiti di -1
        bool **_adjMatrix = new bool*[_n_node](); // matrice  di appoggio temporaneo
        T *_array = new T [_n_node]();            // array di appoggio temporaneo
        for (unsigned int a = 0; a < _n_node; a++) {
            _adjMatrix[a] = new bool[_n_node]();
        }
        bool* temp_linear = new bool[_n_node * _n_node](); //array temporaneo di appoggio per la copia dei valori nella adjMatrix
        // 2. Tolgo il nodo da togliere e copio i vecchi array in quelli nuovi
        int cont = 0;
        for (unsigned int c = 0; c < n_node; c++) {
            if (_eql(array[c], node) == true) {
                cont = c;
            }
        }
        try {
            int k = 0;
            for ( int q = 0; q < n_node; q++ ) {
                for ( int u = 0; u < n_node; u++ ) {
                    if (q != cont && u != cont) {
                        temp_linear[k] = adjMatrix[q][u];
                        k++;
                    }
                }
            }
            int shift = 0;
            k = 0;
            for (unsigned int i = 0; i < _n_node; i++) {
                if (i == cont) {
                    shift = 1;
                    _array[i] = array[i+shift];
                }
                else _array[i] = array[i+shift];
                for (unsigned int j = 0; j < _n_node; j++) {
                    _adjMatrix[i][j] = temp_linear[k];
                    k++;
                }
            }
        } catch (...) {
            clear();
            throw;
        }
        // 3. Dealloco quelli vecchi ( con una delete[] )
        clear();
        delete[] temp_linear;
        temp_linear = nullptr;
        array = _array;
        adjMatrix = _adjMatrix;
        n_node = _n_node;
    }
    
    /**
     Metodo per l'inserimento di nuovi archi nel grafo ( matrice di adiacenza ).
     
     @brief Metodo per l'inserimento di nuovi archi nel grafo.
     
     @param node1 nodo di partenza dell'arco.
     @param node2 nodo di destinazione dell'arco.
     
     @throw eccezione costum si tenta di aggiungere un arco su nodi non esistenti
     @throw eccezione costum l'arco già esiste
     
     */
    // metodo per aggiungere archi
    void addEdge(const T &node1, const T &node2) {
        int count1 = 0;
        int count2 = 0;
        if (exists(node1) == false || exists(node2) == false) {  // gestisce il caso in cui si tenta di aggiungere un arco su nodi non esistenti
            throw customException("Valore non valido!", 997);
        }
        for (unsigned int i = 0; i < n_node; ++i) {
            if (_eql(array[i], node1))
                count1 = i;
        }
        for (unsigned int j = 0; j < n_node; ++j) {
            if (_eql(array[j], node2))
                count2 = j;
        }
        if (adjMatrix[count1][count2] == true){  // gestisce il caso in cui l'arco già esiste
            throw customException("Valore non valido!", 996);
        }
        adjMatrix[count1][count2] = true;
    }
    
    /**
     Metodo per la rimozione di archi dal grafo ( matrice di adiacenza ).
     
     @brief Metodo per la rimozione di archi dal grafo.
     
     @param node1 nodo di partenza dell'arco.
     @param node2 nodo di destinazione dell'arco.
     
     @throw eccezione costum si tenta di rimuovere un arco su nodi non esistenti
     @throw eccezione costum l'arco già non esiste
     
     */
    void removeEdge(const T &node1, const T &node2) {
        int count1 = 0;
        int count2 = 0;
        if (exists(node1) == false || exists(node2) == false) {  // gestisce il caso in cui si tenta di rimuovere un arco su nodi non esistenti
            throw customException("Valore non valido!", 995);
        }
        for (unsigned int i = 0; i < n_node; ++i) {
            if (_eql(array[i], node1))
                count1 = i;
        }
        for (unsigned int j = 0; j < n_node; ++j) {
            if (_eql(array[j], node2))
                count2 = j;
        }
        if (adjMatrix[count1][count2] != true){  // gestisce il caso in cui l'arco già non esiste
            throw customException("Valore non valido!", 994);
        }
        adjMatrix[count1][count2] = false;
    }
    
    /**
     Metodo per sapere se esiste un certo nodo nel grafo tramite funtore E _eql.
     
     @brief Metodo per sapere se esiste un certo nodo nel grafo.
     
     @param node nodo che vogliamo sapere se esiste.
     
     @return true se esiste, false altrimenti.
     
     */
    bool exists(const T &node) {
        for (int i = 0; i < n_node; ++i) {
            if (_eql(array[i], node))
                return true;
        }
        return false;
    }
    /**
     Metodo per sapere se una coppia di nodi è connessa da un arco
     
     @brief Metodo per sapere se esiste un certo arco tra due nodi.
     
     @param node1 nodo di partenza.
     @param node2 nodo di destinazione.
     
     @throw eccezione custom che gestisce il caso in cui uno o entrambi i nodi non esistano.

     @return true se esiste, false altrimenti.
     
     */
    bool hasEdge(const T &node1, const T &node2) {
        int count1 = 0;
        int count2 = 0;
        if (exists(node1) == false || exists(node2) == false) {
            throw customException("Valore non valido!", 993);
        }
        for (unsigned int i = 0; i < n_node; ++i) {
            if (_eql(array[i], node1))
                count1 = i;
        }
        for (unsigned int j = 0; j < n_node; ++j) {
            if (_eql(array[j], node2)) 
                count2 = j;
        }
        if (adjMatrix[count1][count2] == true)
            return true;
        return false;
    }
    
    /**
        Metodo per conoscere il numero di nodi della classe.
     
        @brief metodo per conoscere il numero di nodi della classe
     
        @return numero di nodi.
    */
    int num_nodes() const {
        return n_node;
    }
    
    /**
     Metodo per conoscere il numero di archi della classe.
     
     @brief metodo per conoscere il numero di archi della classe
     
     @return numero di archi.
     */
    int num_edges() const {
        int cont = 0;
        for (int i = 0; i < n_node; i++) {
            for (int j = 0; j < n_node; j++) {
                if (adjMatrix[i][j] == true)
                    cont++;
            }
        }
        return cont;
    }
    
    /**
     Metodo per stampare la matrice di adiacenza (grafo).
     
     @brief metodo per per stampare la matrice di adiacenza (grafo).
     
     */
    void toString() {
        for (unsigned int i = 0; i < n_node; i++) {
            std::cout << i << " : ";
            for (unsigned int j = 0; j < n_node; j++)
                std::cout << adjMatrix[i][j] << " ";
            std::cout << "\n";
        }
    }
    
    // forward const iterator
    class const_iterator; // forward declaration
    class const_iterator {
        const T* ptr;
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T                         value_type;
        typedef ptrdiff_t                 difference_type;
        typedef const T*                  pointer;
        typedef const T&                  reference;
        
        
        const_iterator() : ptr(nullptr) {}
        
        const_iterator(const const_iterator &other) : ptr(other.ptr) {
        }
        
        const_iterator& operator=(const const_iterator &other) {
            ptr = other.ptr;
            return *this;
        }
        
        ~const_iterator() {
            
        }
        
        // Ritorna il dato riferito dall'iteratore (dereferenziamento)
        reference operator*() const {
            return *ptr;
        }
        
        // Ritorna il puntatore al dato riferito dall'iteratore
        pointer operator->() const {
            return ptr;
        }
        
        // Operatore di iterazione post-incremento
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++ptr;
            return tmp;
        }
        
        // Operatore di iterazione pre-incremento
        const_iterator& operator++() {
            ++ptr;
            return *this;
        }
        
        // Uguaglianza
        bool operator==(const const_iterator &other) const {
            return (ptr == other.ptr);
        }
        
        // Diversita'
        bool operator!=(const const_iterator &other) const {
            return (ptr != other.ptr);
        }
        
    private:
        //Dati membro
        
        // La classe container deve essere messa friend dell'iteratore per poter
        // usare il costruttore di inizializzazione.
        friend class Graph;
        
        // Costruttore privato di inizializzazione usato dalla classe container
        // tipicamente nei metodi begin e end
        const_iterator(const T* p) : ptr(p) { }
        
    }; // classe const_iterator
    
    // Ritorna l'iteratore all'inizio della sequenza dati
    const_iterator begin() const {
        return const_iterator(array);
    }
    
    // Ritorna l'iteratore alla fine della sequenza dati
    const_iterator end() const {
        return const_iterator(array+n_node);
    }
};

#endif /* graph_hpp */
