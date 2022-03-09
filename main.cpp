//
//  main.cpp
//  
//
//  Created by Alessandro Ferrando on 25/03/21.
//

#include <iostream>
#include "Graph.hpp"
#include <cassert>

/**
 Funtore per valutare l'uguaglianza tra interi. La valutazione e'
 fatta usando l'operatore == tra interi.
 
 @brief Funtore per valutare l'uguaglianza tra interi.
 */
struct equal_int {
    bool operator()(int a, int b) const {
        return a==b;
    }
};

// Typedef della classe grafo su interi di comodo
typedef Graph<int, equal_int> graphtest;

void test_metodi_fondamentali_interi() {
    std::cout<<"******** Test metodi fondamental del grafo di interi ********"<<std::endl;
    
    graphtest graph1; // costruttore di  default
    
    assert(graph1.num_nodes() == 0);
    
    try {
        graph1.addNode(4); // add
        graph1.addNode(6);
        graph1.addNode(7);
    } catch (customException  &m) {
        std::cout << m.get_value() << " " << m.get_error() << std::endl;
        return;
    }
    
    assert(graph1.num_nodes() == 3);
     
    graphtest graph2(graph1);  // copy constructor
    
    assert(graph2.num_nodes() == graph1.num_nodes());
    
    graphtest graph3;
    
    graph3 = graph1; // operatore di assegnamento =
    
    assert(graph3.num_nodes() == graph1.num_nodes());
    
    std::cout << "Stampa di graph3 dopo assegnamento :" << std::endl;
    
    graph3.toString(); //toString per la stampa della matrice di adiacenza che rappresenta il grafo
    
    std::cout << "Stampa id nodi di graph3 dopo assegnamento :" << std::endl;
    
    graphtest::const_iterator it, ite;
    for(it=graph3.begin(),ite=graph3.end(); it!=ite; ++it) {  //stampa degli identificatori dei nodi, usando const iterator
        std::cout << *it << std::endl;
    }
}

/**
 Test d'uso del grafo interi
 
 @brief Test d'uso del grafo
 */
void test_uso_interi() {
    std::cout<<"******** Test d'uso del grafo di interi ********"<<std::endl;
    
    graphtest graph4;
    
    assert(graph4.num_nodes() == 0);

    try {
        graph4.addNode(7); // metodo per aggiungere un nodo
        graph4.addNode(6);
        graph4.addNode(3);
        graph4.addNode(5);
    } catch (customException  &m) {
        std::cout << m.get_value() << " " << m.get_error() << std::endl;
        return;
    }
    
    try {
        graph4.addEdge(5, 7);
        graph4.addEdge(6, 6);
    } catch (customException  &m1) {
        std::cout << m1.get_value() << " " << m1.get_error() << std::endl;
        return;
    }
    
    std::cout << "Stampa di graph4 dopo aggiunta di nodi e archi:" << std::endl;
    
    graph4.toString();
    std::cout << std::endl;
    graphtest::const_iterator it, ite;
    for(it=graph4.begin(),ite=graph4.end(); it!=ite; ++it) {
        std::cout << *it << std::endl;
    }
    
    try {
        std::cout << "Esiste un arco da 5 a 7 in graph4? "<< graph4.hasEdge(5, 7) << std::endl;
    } catch (customException &m2) {
        std::cout << m2.get_value() << " " << m2.get_error() << std::endl;
        return;
    }
    bool ok1 = graph4.hasEdge(5, 7);
    assert(ok1 == true);
    
    std::cout << "Numero di archi di graph4: "<< graph4.num_edges() << std::endl;
    assert(graph4.num_edges() == 2);
    
    std::cout << "Numero di nodi di graph4: "<< graph4.num_nodes() << std::endl;
    assert(graph4.num_nodes() == 4);
    
    std::cout << "Rimozione di un nodo"<< std::endl;
    try {
        graph4.removeNode(5);
    } catch (customException &m3) {
        std::cout << m3.get_value() << " " << m3.get_error() << std::endl;
        return;
    }

    std::cout << "Numero di nodi di graph4: "<< graph4.num_nodes() << std::endl;
    assert(graph4.num_nodes() == 3);
    
    std::cout << "Numero di archi di graph4: "<< graph4.num_edges() << std::endl;
    assert(graph4.num_edges() == 1);
    
    std::cout << "Rimozione di un arco" << std::endl;
    try {
        graph4.removeEdge(6,6);
    } catch (customException &m4) {
        std::cout << m4.get_value() << " " << m4.get_error() << std::endl;
        return;
    }
    
    std::cout << "Numero di archi di graph4: "<< graph4.num_edges() << std::endl;
    assert(graph4.num_edges() == 0);
    
    graph4.toString();
    std::cout << std::endl;
    for(it=graph4.begin(),ite=graph4.end(); it!=ite; ++it) {
        std::cout << *it << std::endl;
    }
    
    graphtest graph5;
    
    graph4.swap(graph5);
    assert(graph5.num_nodes() == 3);
    
    graph4.clear();
    assert(graph4.num_nodes() == 0);
}

void test_eccezioni_interi(){
    std::cout<<"******** Test eccezioni del grafo di interi ********"<<std::endl;
    
    graphtest graph6;
    try {
        graph6.addNode(7); // metodo per aggiungere un nodo
        graph6.addNode(6);
        graph6.addNode(3);
        graph6.addNode(3);
    } catch (customException  &m) {
        std::cout << m.get_value() << " " << m.get_error() << std::endl;
        return;
    }
    
}

//--------------------------------------------------------------------

/**
 Funtore per l'uguaglianza tra stringhe.
 
 @brief Funtore per il confronto tra stringhe.
 */
struct equal_string {
    bool operator()(const std::string &a, const std::string &b) const {
        return (a==b);
    }
};

// Typedef della classe grafo su stringhe di comodo
typedef Graph<std::string,equal_string> graphString;

/**
 Test della lista ordinata istanziata su stringhe
 
 @brief Test della lista ordinata istanziata su stringhe
 */
void test_metodi_fondamentali_stringhe() {
    std::cout<<"******** Test metodi fondamentali grafo di stringhe ********"<<std::endl;
    
    graphString graphSt1; // costruttore di  default
    
    assert(graphSt1.num_nodes() == 0);
    
    try {
        graphSt1.addNode("pippo"); // add
        graphSt1.addNode("pluto");
        graphSt1.addNode("paperino");
        graphSt1.addNode("cip");
    } catch (customException  &m) {
        std::cout << m.get_value() << " " << m.get_error() << std::endl;
        return;
    }

    assert(graphSt1.num_nodes() == 4);
    
    graphString graphSt2(graphSt1);  // copy constructor
    
    assert(graphSt2.num_nodes() == graphSt1.num_nodes());

    graphString graphSt3;
    
    graphSt3 = graphSt1; // operatore di assegnamento =
    
    assert(graphSt3.num_nodes() == graphSt1.num_nodes());
    
    std::cout << "Stampa di graphSt3 dopo assegnamento:" << std::endl;
    
    graphSt3.toString();
    
    std::cout << "Stampa id nodi di graphSt3 dopo assegnamento:" << std::endl;
    
    graphString::const_iterator it, ite;
    for(it=graphSt3.begin(),ite=graphSt3.end(); it!=ite; ++it) {
        std::cout << *it << std::endl;
    }
}

/**
 Test d'uso del grafo di stringhe
 
 @brief Test d'uso del grafo di stringhe
 */
void test_uso_stringhe() {
    std::cout<<"******** Test d'uso del grafo di stringhe ********"<<std::endl;
    
    graphString graphSt4;
    
    assert(graphSt4.num_nodes() == 0);
    
    try {
        graphSt4.addNode("pippo"); // add
        graphSt4.addNode("pluto");
        graphSt4.addNode("paperino");
        graphSt4.addNode("cip");
    } catch (customException  &m) {
        std::cout << m.get_value() << " " << m.get_error() << std::endl;
        return;
    }
    
    try {
        graphSt4.addEdge("pippo", "pluto");
        graphSt4.addEdge("cip", "paperino");
    } catch (customException  &m1) {
        std::cout << m1.get_value() << " " << m1.get_error() << std::endl;
        return;
    }
    
    std::cout << "Stampa di graphSt4 dopo aggiunta di nodi e archi:" << std::endl;
    
    graphSt4.toString();
    graphString::const_iterator it, ite;
    for(it=graphSt4.begin(),ite=graphSt4.end(); it!=ite; ++it) {
        std::cout << *it << std::endl;
    }
    
    try {
        std::cout << "Esiste un arco da pippo a pluto in graphSt4? "<< graphSt4.hasEdge("pippo", "pluto") << std::endl;
    } catch (customException  &m2) {
        std::cout << m2.get_value() << " " << m2.get_error() << std::endl;
        return;
    }
    bool ok1 = graphSt4.hasEdge("pippo", "pluto");
    assert(ok1 == true);
    
    std::cout << "Numero di archi di graphSt4: "<< graphSt4.num_edges() << std::endl;
    assert(graphSt4.num_edges() == 2);
    
    std::cout << "Numero di nodi di graphSt4: "<< graphSt4.num_nodes() << std::endl;
    assert(graphSt4.num_nodes() == 4);
    
    std::cout << "Rimozione di un nodo"<< std::endl;
    try {
        graphSt4.removeNode("pippo");
    } catch (customException  &m3) {
        std::cout << m3.get_value() << " " << m3.get_error() << std::endl;
        return;
    }
    
    std::cout << "Numero di nodi di graphSt4: "<< graphSt4.num_nodes() << std::endl;
    assert(graphSt4.num_nodes() == 3);
    
    std::cout << "Numero di archi di graphSt4: "<< graphSt4.num_edges() << std::endl;
    assert(graphSt4.num_edges() == 1);
    
    std::cout << "Rimozione di un arco" << std::endl;
    try {
        graphSt4.removeEdge("cip", "paperino");
    } catch (customException &m4) {
        std::cout << m4.get_value() << " " << m4.get_error() << std::endl;
        return;
    }
    
    std::cout << "Numero di archi di graphSt4: "<< graphSt4.num_edges() << std::endl;
    assert(graphSt4.num_edges() == 0);
    
    graphSt4.toString();
    std::cout << std::endl;
    for(it=graphSt4.begin(),ite=graphSt4.end(); it!=ite; ++it) {
        std::cout << *it << std::endl;
    }
    
    graphString graphSt5;
    
    graphSt4.swap(graphSt5);
    assert(graphSt5.num_nodes() == 3);
    
    graphSt4.clear();
    assert(graphSt4.num_nodes() == 0);
}

void test_eccezioni_stringhe(){
    std::cout<<"******** Test eccezioni del grafo di stringhe ********"<<std::endl;
    
    graphString graphSt6;
    try {
        graphSt6.removeNode("pippo");
    } catch (customException  &m3) {
        std::cout << m3.get_value() << " " << m3.get_error() << std::endl;
        return;
    }
}
//--------------------------------------------------------------------

/**
 Struct point che implementa un punto 2D.
 
 @brief Struct point che implementa un punto 2D.
 */
struct point {
    int x; ///< coordinata x del punto
    int y; ///< coordinata y del punto
    
    point() : x(0), y(0) {}
    point(int xx, int yy) : x(xx), y(yy) {}
};

/**
 Ridefinizione dell'operatore di stream << per un point.
 Necessario per l'operatore di stream della classe ordered_list.
 */
std::ostream &operator<<(std::ostream &os, const point &p) {
    std::cout<<"("<<p.x<<","<<p.y<<")";
    return os;
}

/**
 Funtore per il confronto di uguaglianza tra due punti.
 Ritorna true se p1.x != p2.x.
 
 @brief Funtore per il confronto di due punti.
 */
struct equal_point {
    bool operator()(const point &p1, const point &p2) const {
        return (p1.x==p2.x) && (p1.y==p2.y);
    }
};

// Typedef della classe grafo su punti di comodo
typedef Graph<point,equal_point> graphPoint;

/**
 Test del grafo istanziato su oggetti point
 
 @brief Test del grafo istanziato su oggetti point
 */
void test_metodi_fondamentali_point() {

    std::cout<<"******** Test metodi fondamentali grafo di stringhe ********"<<std::endl;
    
    graphPoint graphPt1; // costruttore di  default
    
    assert(graphPt1.num_nodes() == 0);

    try {
        graphPt1.addNode(point(1,1));
        graphPt1.addNode(point(1,2));
        graphPt1.addNode(point(2,7));
        graphPt1.addNode(point(0,0));
        graphPt1.addNode(point(5,4));
    } catch (customException &m) {
        std::cout << m.get_value() << " " << m.get_error() << std::endl;
        return;
    }

    assert(graphPt1.num_nodes() == 5);

    graphPoint graphPt2(graphPt1);  // copy constructor
    
    assert(graphPt2.num_nodes() == graphPt1.num_nodes());
    
    graphPoint graphPt3;
    
    graphPt3 = graphPt1; // operatore di assegnamento =
    
    assert(graphPt3.num_nodes() == graphPt1.num_nodes());
    
    std::cout << "Stampa di graphPt3 dopo assegnamento:" << std::endl;
    
    graphPt3.toString();
    
    std::cout << "Stampa id nodi di graphPt3 dopo assegnamento:" << std::endl;
    
    Graph<point,equal_point>::const_iterator i,ie;
    for(i=graphPt3.begin(),ie=graphPt3.end(); i!=ie; ++i) {
        std::cout << *i << std::endl;
    }
}

/**
 Test d'uso del grafo di punti
 
 @brief Test d'uso del grafo di punti
 */
void test_uso_punti() {
    std::cout<<"******** Test d'uso del grafo di punti ********"<<std::endl;
    
    graphPoint graphPt4;
    
    assert(graphPt4.num_nodes() == 0);
    
    try {
        graphPt4.addNode(point(1,1));
        graphPt4.addNode(point(1,2));
        graphPt4.addNode(point(2,7));
        graphPt4.addNode(point(0,0));
        graphPt4.addNode(point(5,4));
    } catch (customException &m) {
        std::cout << m.get_value() << " " << m.get_error() << std::endl;
        return;
    }

    try {
        graphPt4.addEdge(point(1,1), point(1,2));
        graphPt4.addEdge(point(1,2), point(1,2));
        graphPt4.addEdge(point(2,7), point(0,0));
    } catch (customException &m1) {
        std::cout << m1.get_value() << " " << m1.get_error() << std::endl;
        return;
    }
    
    std::cout << "Stampa di graphPt4 dopo aggiunta di nodi e archi:" << std::endl;
    
    graphPt4.toString();
    std::cout << std::endl;
    graphPoint::const_iterator it, ite;
    for(it=graphPt4.begin(),ite=graphPt4.end(); it!=ite; ++it) {
        std::cout << *it << std::endl;
    }
    
    try {
        std::cout << "Esiste un arco da (1,1) a (1,2) in graphPt4? "<< graphPt4.hasEdge(point(1,1), point(1,2)) << std::endl;
    } catch (customException &m2) {
        std::cout << m2.get_value() << " " << m2.get_error() << std::endl;
        return;
    }
    bool ok1 = graphPt4.hasEdge(point(1,1), point(1,2));
    assert(ok1 == true);
    
    std::cout << "Numero di archi di graphPt4: "<< graphPt4.num_edges() << std::endl;
    assert(graphPt4.num_edges() == 3);
    
    std::cout << "Numero di nodi di graphPt4: "<< graphPt4.num_nodes() << std::endl;
    assert(graphPt4.num_nodes() == 5);
    
    std::cout << "Rimozione di un nodo"<< std::endl;
    try {
        graphPt4.removeNode(point(1,2));
    } catch (customException &m3) {
        std::cout << m3.get_value() << " " << m3.get_error() << std::endl;
        return;
    }
    
    std::cout << "Numero di nodi di graphPt4: "<< graphPt4.num_nodes() << std::endl;
    assert(graphPt4.num_nodes() == 4);
    
    std::cout << "Numero di archi di graphPt4: "<< graphPt4.num_edges() << std::endl;
    assert(graphPt4.num_edges() == 1);
    
    std::cout << "Rimozione di un arco" << std::endl;
    try {
        graphPt4.removeEdge(point(2,7), point(0,0));
    } catch (customException &m4) {
        std::cout << m4.get_value() << " " << m4.get_error() << std::endl;
        return;
    }
    
    std::cout << "Numero di archi di graphPt4: "<< graphPt4.num_edges() << std::endl;
    assert(graphPt4.num_edges() == 0);
    
    graphPt4.toString();
    std::cout << std::endl;
    for(it=graphPt4.begin(),ite=graphPt4.end(); it!=ite; ++it) {
        std::cout << *it << std::endl;
    }
    
    graphPoint graphPt5;
    
    graphPt4.swap(graphPt5);
    assert(graphPt5.num_nodes() == 4);
    
    graphPt4.clear();
    assert(graphPt4.num_nodes() == 0);
}

void test_eccezioni_point(){
    std::cout<<"******** Test eccezioni del grafo di punti ********"<<std::endl;
    
    graphPoint graphPt6;
    try {
        graphPt6.addEdge(point(1,1), point(1,2));
    } catch (customException &m1) {
        std::cout << m1.get_value() << " " << m1.get_error() << std::endl;
        return;
    }
}

//--------------------------------------------------------------------

int main() {
    
    test_metodi_fondamentali_interi();
    
    test_uso_interi();
    
    test_eccezioni_interi();
    
    test_metodi_fondamentali_stringhe();
    
    test_uso_stringhe();
    
    test_eccezioni_stringhe();
   
    test_metodi_fondamentali_point();
    
    test_uso_punti();
    
    test_eccezioni_point();
    
    return 0;
}

