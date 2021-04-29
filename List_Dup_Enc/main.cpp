#include <iostream>

#include "lista_dup_enc.h"


#include <vector>

#include <algorithm>


using namespace std;


template< typename T >

void DEBUG_SHOW_COMP_LIST( lde::L_D_Enc<T>& list){


    vector< T > comp_list1;
    vector< T > comp_list2;

    unsigned long counter = 1;
    L_D_Enc_elem<T>* interm = list.inicio;

    while( interm->prox != nullptr ){

        cout<< "\tlist["<<counter-1<<"] data = " << interm->data << endl;
        comp_list1.push_back( interm->data );
        interm = interm->prox;

        counter++;

    }

    cout<< "\tlist["<<counter-1<<"] data = " << interm->data << endl;
    cout<< "\tList size = " << counter << endl;
    comp_list1.push_back( interm->data );

    unsigned long counter2 = 1;
    L_D_Enc_elem<T>* interm2 = list.fim;

    while( interm2->prev != nullptr ){

        comp_list2.insert(comp_list2.begin(), interm2->data);
        interm2 = interm2->prev;

        counter2++;

    }

    comp_list2.insert(comp_list2.begin(), interm2->data);
    if( comp_list1.size() != comp_list2.size() ){ 
        cout<<"\n\t\t[PRIORITY ALERT]\tSize difference in vectors."; 
        cout<<"Backwards Size = " << comp_list2.size() << endl << endl;
    }

    if( comp_list1 != comp_list2 ) {

        cout<<"\n\t\t[PRIORITY ALERT]\tContent difference in vectors.\n"<<endl;

    }

    interm = nullptr;
    interm2 = nullptr;

    delete interm;
    delete interm2;

    cout<<"\n\n"<<endl;

}


int main()

{


    lde::L_D_Enc<int> lista;

    lde::init(lista);


    lde::insere_fim( lista , 123 );

    lde::insere_fim( lista , 321 );

    lde::insere_fim( lista , 456 );

    lde::insere_fim( lista , 654 );


    DEBUG_SHOW_COMP_LIST(lista);


    lde::remove_fim( lista );


    DEBUG_SHOW_COMP_LIST( lista );


    lde::remove_fim( lista );


    DEBUG_SHOW_COMP_LIST( lista );

    lde::insere_inicio( lista , 765 );
    lde::insere_inicio( lista , 567 );
    lde::insere_inicio( lista , 908 );

    DEBUG_SHOW_COMP_LIST( lista );

    lde::remove_inicio( lista );
    lde::remove_inicio( lista );

    DEBUG_SHOW_COMP_LIST( lista );

    cout<<lde::insere_posicao( lista , 980 , 3  )<<endl;

    DEBUG_SHOW_COMP_LIST( lista );

    lde::remove_posicao( lista , 5 );

    DEBUG_SHOW_COMP_LIST( lista );

    //cout << ( lista << 2 )->data << endl;
    lde::swap( ( lista << 0 ) , ( lista << 1 ) );

    DEBUG_SHOW_COMP_LIST( lista );

    lde::insere_inicio( lista , 354 );
    lde::insere_inicio( lista , 587 );
    lde::insere_inicio( lista , 907 );

    //lde::ordenar_bubble( lista , 1 , lde::qtd_lista(lista) );
    lde::quickSort( lista.inicio );

    DEBUG_SHOW_COMP_LIST( lista );
    
    return 0;

}
