#include <iostream>
#include "Pessoa.h"

using namespace std;

template< typename T >
void DEBUG_SHOW_LIST( len::L_Enc<T> &list , bool indexing = 0 ){

    unsigned long lenght = 1;
    L_Enc_elem<T> *interm = list.inicio;
    while( interm->prox != nullptr ){
                if( indexing ) cout<<"Index Hex  : " << hex << interm << endl;
                cout<<"Index Data : " << dec << interm->data << endl;
        interm = interm->prox;
                lenght++;
    }
        if( indexing ) cout << "Index Hex  : " << hex << interm->prox << endl;
        cout << "Index Data : " << dec << interm->data << endl;
        cout << "\tSize of list : " << lenght << endl << endl;

        interm = nullptr;
        delete interm;

}


int main(){
    /*
    fila::Fila<int> fila1;
    fila::init(fila1);
    
    fila::queue( fila1 , 123 );
    fila::queue( fila1 , 312 );
    fila::queue( fila1 , 345 );

    DEBUG_SHOW_LIST( fila1.fila );

    int test = fila::dequeue( fila1 );

    DEBUG_SHOW_LIST( fila1.fila );

    cout<<"return: " << test << endl;

    cout<<"///////////////////////////////////////////////////"<<endl;
    */

    pes::Pessoa pessoa1;
    fila::Fila< pes::Pessoa > atendimento;
    fila::init( atendimento );

    pessoa1.nome = "Lucas";
    pessoa1.data = 10;

    pes::inserePessoa( atendimento , pessoa1 );

    pessoa1.nome = "Mateus";
    pessoa1.data = 20;

    pes::inserePessoa( atendimento , pessoa1 );

    //pes::DEBUG_SHOW_PESSOA( atendimento );

    //pes::Pessoa pessoaTeste = pes::atendePessoa( atendimento );
    //cout<<"Pessoateste: " << pessoaTeste.nome <<endl;
    //cout<<"Pessoateste: " << pessoaTeste.data <<endl;

    //pes::DEBUG_SHOW_PESSOA( atendimento );

    pes::atendeFilaInteira( atendimento );
    

    return 0;
}