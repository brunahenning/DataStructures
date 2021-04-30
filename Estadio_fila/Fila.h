#include "Lista_Encadeada.h"

namespace fila{

    template< typename T >
    struct Fila{
        len::L_Enc<T> fila;
    };

    template< typename T >
    void init( Fila<T> &fila ){
        len::init( fila.fila );
    }

    template< typename T >
    bool queue( Fila<T> &fila , T dado ){
        return len::insere_final( fila.fila , dado );
    }

    template< typename T >
    T dequeue( Fila<T> &fila ){

        T ret = fila.fila.inicio->data;
        len::remove_inicio( fila.fila );

        return ret;

    }

    template< typename T >
    T consulta_inicio( Fila<T> &fila, bool& goodReturn = nullptr){
        
        if(fila.fila.inicio == nullptr){
            goodReturn = 0;
        }else{
            goodReturn = 1;
        }

        return fila.fila.inicio->data;

    }

    template< typename T >
    unsigned long qtd_fila(fila::Fila<T>& fila){
        if(fila.fila.inicio == nullptr) return 0;
        len::L_Enc<T> list = fila.fila;
        unsigned long lenght = 1;
        L_Enc_elem<T> *interm = list.inicio;
        while( interm->prox != nullptr ){
            interm = interm->prox;
            lenght++;
        }
        interm = nullptr;
        return lenght;
    }

}
