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
    T consulta_inicio( Fila<T> &fila ){
        
        return fila.fila.inicio->data;

    }

}