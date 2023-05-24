#include <iostream>

template<typename T>
struct Nodo {
    T dato;
    Nodo<T>* izquierdo;
    Nodo<T>* derecho;
};

template<typename T>
class ArbolBusqueda {
public:
    Nodo<T>* raiz;
    ArbolBusqueda() {
        raiz = nullptr;
    }


    void inicializa() {
        raiz = nullptr;
    }

    bool vacio() {
        return (raiz == nullptr);
    }

    /*Nodo<T>* recupera(pos, Nodo<T>*& nodo)
    {
        return (raiz == nullptr || pos == nullptr);
    }*/

    bool es_hoja(Nodo<T>* nodo) {
        return (nodo != nullptr && nodo->izquierdo == nullptr && nodo->derecho == nullptr);
    }

    int fact_eq(Nodo<T>* nodo) {
        if (nodo == nullptr) {
            return 0;
        }
        return altura(nodo->derecho) - altura(nodo->izquierdo);
    }

    T recupera(Nodo<T>* pos) {
        if (pos == nullptr || raiz == nullptr) {
            throw std::runtime_error("Insuficiencia de datos");
        }
        return pos->dato;
    }

    void balanceo(Nodo<T>*& nodo) {
        if (fact_eq(nodo) < -1) {
            if (fact_eq(nodo->izquierdo) == -1) {
                rot_sim_der(nodo);
            } else {
                rot_dob_der(nodo);
            }
        } else if (fact_eq(nodo) > 1) {
            if (fact_eq(nodo->derecho) == 1) {
                rot_sim_izq(nodo);
            } else {
                rot_dob_izq(nodo);
            }
        }
    }

    void rot_sim_der(Nodo<T>*& nodo) {
        Nodo<T>* aux1 = nodo->izquierdo;
        Nodo<T>* aux2 = aux1->derecho;
        nodo->izquierdo = aux2;
        aux1->derecho = nodo;
        nodo = aux1;
    }

    void rot_sim_izq(Nodo<T>*& nodo) {
        Nodo<T>* aux1 = nodo->derecho;
        Nodo<T>* aux2 = aux1->izquierdo;
        nodo->derecho = aux2;
        aux1->izquierdo = nodo;
        nodo = aux1;
    }

    void rot_dob_der(Nodo<T>*& nodo) {
        Nodo<T>* aux1 = nodo->izquierdo;
        Nodo<T>* aux2 = aux1->derecho;
        Nodo<T>* aux3 = aux2->izquierdo;
        Nodo<T>* aux4 = aux2->derecho;
        nodo->izquierdo = aux4;
        aux1->derecho = aux3;
        aux2->izquierdo = aux1;
        nodo = aux2;
    }

    void rot_dob_izq(Nodo<T>*& nodo) {
        Nodo<T>* aux1 = nodo->derecho;
        Nodo<T>* aux2 = aux1->izquierdo;
        Nodo<T>* aux3 = aux2->derecho;
        Nodo<T>* aux4 = aux2->izquierdo;
        nodo->derecho = aux4;
        aux1->izquierdo = aux3;
        aux2->derecho = aux1;
        nodo = aux2;
    }

    void inserta(const T& valor) {
        if (raiz == nullptr) {
            raiz = new Nodo<T>;
            raiz->dato = valor;
            raiz->izquierdo = nullptr;
            raiz->derecho = nullptr;
        } else {
            insertaRec(raiz, valor);
        }
    }

    void insertaRec(Nodo<T>*& nodo, const T& valor) {
        if (nodo == nullptr) {
            nodo = new Nodo<T>;
            nodo->dato = valor;
            nodo->izquierdo = nullptr;
            nodo->derecho = nullptr;
        } else if (valor < nodo->dato) {
            insertaRec(nodo->izquierdo, valor);
        } else {
            insertaRec(nodo->derecho, valor);
        }
        balanceo(nodo);
    }

    Nodo<T>* localiza(const T& valor, Nodo<T>* nodo) {
        if (nodo == nullptr) {
            return nullptr;
        }
        if (valor == nodo->dato) {
            return nodo;
        } else if (valor < nodo->dato) {
            return localiza(valor, nodo->izquierdo);
        } else {
            return localiza(valor, nodo->derecho);
        }
    }

    void local(int pos){
        localiza(pos,raiz);
    }

    Nodo<T>* menor(Nodo<T>* nodo) {
        if (nodo == nullptr) {
            return nullptr;
        }
        if (nodo->izquierdo == nullptr) {
            return nodo;
        }
        return menor(nodo->izquierdo);
    }

    Nodo<T>* mayor(Nodo<T>* nodo) {
        if (nodo == nullptr) {
            return nullptr;
        }
        if (nodo->derecho == nullptr) {
            return nodo;
        }
        return mayor(nodo->derecho);
    }

    void elimina(const T& valor) {
        eliminaRec(raiz, valor);
    }

    void eliminaRec(Nodo<T>*& nodo, const T& valor) {
        if (nodo == nullptr) {
            return;
        }
        if (valor == nodo->dato) {
            if (es_hoja(nodo)) {
                delete nodo;
                nodo = nullptr;
            } else if (nodo->izquierdo != nullptr) {
                Nodo<T>* pos_reemplazo = mayor(nodo->izquierdo);
                nodo->dato = pos_reemplazo->dato;
                eliminaRec(nodo->izquierdo, pos_reemplazo->dato);
            } else {
                Nodo<T>* pos_reemplazo = menor(nodo->derecho);
                nodo->dato = pos_reemplazo->dato;
                eliminaRec(nodo->derecho, pos_reemplazo->dato);
            }
        } else if (valor < nodo->dato) {
            eliminaRec(nodo->izquierdo, valor);
        } else {
            eliminaRec(nodo->derecho, valor);
        }
        balanceo(nodo);
    }

    void recorrido_preorder() {
        recorrido_preorderRec(raiz);
        std::cout << std::endl;
    }

    void recorrido_preorderRec(Nodo<T>* nodo) {
        if (nodo != nullptr) {
            std::cout << nodo->dato << " ";
            recorrido_preorderRec(nodo->izquierdo);
            recorrido_preorderRec(nodo->derecho);
        }
    }

    void recorrido_inorder() {
        recorrido_inorderRec(raiz);
        std::cout << std::endl;
    }

    void recorrido_inorderRec(Nodo<T>* nodo) {
        if (nodo != nullptr) {
            recorrido_inorderRec(nodo->izquierdo);
            std::cout << nodo->dato << " ";
            recorrido_inorderRec(nodo->derecho);
        }
    }

    void recorrido_postorder() {
        recorrido_postorderRec(raiz);
        std::cout << std::endl;
    }

    void recorrido_postorderRec(Nodo<T>* nodo) {
        if (nodo != nullptr) {
            recorrido_postorderRec(nodo->izquierdo);
            recorrido_postorderRec(nodo->derecho);
            std::cout << nodo->dato << " ";
        }
    }

    int altura(Nodo<T>* nodo) {
        if (nodo == nullptr) {
            return 0;
        }
        int altura_izq = altura(nodo->izquierdo);
        int altura_der = altura(nodo->derecho);
        return 1 + std::max(altura_izq, altura_der);
    }



};

int main()
{
    ArbolBusqueda<int>hoja;
    int pos = 3;
    hoja.inserta(1);
    hoja.inserta(4);
    hoja.inserta(6);
    hoja.inserta(3);
    hoja.inserta(9);
    hoja.recorrido_preorder();
    hoja.elimina(pos);
    std::cout<<""<<std::endl;
    std::cout<<"imprimiendo despues de eliminar el numero: "<<pos<<std::endl;
    hoja.recorrido_preorder();
}
