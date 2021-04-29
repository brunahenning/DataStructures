#include<iostream>
#include<memory>
#include "poker.h"

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
	len::L_Enc<int> lista;
	len::init( lista );

	len::insere_final( lista , 321 );
	len::insere_final( lista , 123 );
	len::insere_final( lista , 456 );
	len::insere_final( lista , 654 );

	DEBUG_SHOW_LIST( lista );

	len::remove_final( lista );

	DEBUG_SHOW_LIST( lista );

	len::insere_inicio( lista , 987 );
	len::insere_inicio( lista , 765 );
	len::insere_inicio( lista , 567 );

	DEBUG_SHOW_LIST( lista );

	len::remove_inicio( lista );

	DEBUG_SHOW_LIST( lista );

	len::insere_posicao( lista , 678 , 2 );

	DEBUG_SHOW_LIST( lista );

	len::insere_posicao( lista , 678 , 3 );

	DEBUG_SHOW_LIST( lista );

	len::remove_posicao( lista , 4 );
	
	DEBUG_SHOW_LIST( lista );

	//len::ordenar_bubble( lista , 1 , len::qtd_lista(lista) );
	len::quickSort( lista );

	DEBUG_SHOW_LIST( lista );

	///FIM DA LISTA GENERICA
	/////////////////////////////////////////////////////
	*/
	len::L_Enc< crd::Simples_Carta > baralho;
	len::init( baralho );

	crd::Simples_Carta carta_s;

	crd::criar_carta_simples( carta_s , 'A' , 'C' , 'V' );
	len::insere_inicio( baralho , carta_s );
	crd::criar_carta_simples( carta_s , '2' , 'P' , 'P' );
	len::insere_inicio( baralho , carta_s );
	crd::criar_carta_simples( carta_s , '3' , 'E' , 'V' );
	len::insere_inicio( baralho , carta_s );

	pkr::imprime_baralho_console( baralho );

	pkr::monta_baralho( baralho );
	pkr::imprime_baralho_console( baralho );

	pkr::embaralha( baralho );
	pkr::imprime_baralho_console( baralho );

	len::quickSort( baralho );
	pkr::imprime_baralho_console( baralho );

	/////////////////////////////////////////////////////////
	///FASE UM
	cout<<"\n\n\n";
	len::L_Enc< crd::Simples_Carta > baralho_n;
	len::init(baralho_n);
	len::L_Enc< crd::Simples_Carta > mesa;
	len::init(mesa);
	len::L_Enc< len::L_Enc< crd::Simples_Carta > > jogadores;
	len::init(jogadores);

	len::L_Enc< crd::Simples_Carta > jogador1;	len::init(jogador1);
	len::L_Enc< crd::Simples_Carta > jogador2;	len::init(jogador2);
	len::L_Enc< crd::Simples_Carta > jogador3;	len::init(jogador3);

	pkr::monta_baralho( baralho_n );

	len::insere_final( jogadores , jogador1 );
	len::insere_final( jogadores , jogador2 );
	len::insere_final( jogadores , jogador3 );

	//pkr::imprime_baralho_console( jogadores.inicio->prox->data );

	///	jogadores. inicio-> data
	///	list	 | start |  jogador1

	///	jogadores. inicio->prox -> data
	///	list	 | start | point|  jogador2

	pkr::embaralha( baralho_n );
	pkr::distribuir_cartas_fase_um( baralho_n , mesa , jogadores , 3 );

	cout<<"Baralho_n:\n"<<endl;
	pkr::imprime_baralho_console( baralho_n );

	cout<<"\n\nMesa:\n"<<endl;
	pkr::imprime_baralho_console( mesa );

	cout<<"\n\nJogador1:\n"<<endl;
	pkr::imprime_baralho_console( jogadores.inicio->data );

	cout<<"\n\nJogador2:\n"<<endl;
	pkr::imprime_baralho_console( jogadores.inicio->prox->data );

	cout<<"\n\nJogador3:\n"<<endl;
	pkr::imprime_baralho_console( jogadores.inicio->prox->prox->data );

	cout<<"\n\nDOIS\n\n";

	pkr::distribuir_cartas_fase_dois( baralho_n , mesa , jogadores , 3 );

	cout<<"Baralho_n:\n"<<endl;
	pkr::imprime_baralho_console( baralho_n );

	cout<<"\n\nMesa:\n"<<endl;
	pkr::imprime_baralho_console( mesa );

	cout<<"\n\nJogador1:\n"<<endl;
	pkr::imprime_baralho_console( jogadores.inicio->data );

	cout<<"\n\nJogador2:\n"<<endl;
	pkr::imprime_baralho_console( jogadores.inicio->prox->data );

	cout<<"\n\nJogador3:\n"<<endl;
	pkr::imprime_baralho_console( jogadores.inicio->prox->prox->data );

	cout<<"\n\nTestando ordenações: \n" << endl; 
	cout<<"Antes: "<<endl;
	pkr::imprime_baralho_console( mesa );
	len::ordenar_bubble( mesa , 1 , len::qtd_lista(mesa) );
	cout<<"Depois: "<<endl;
	pkr::imprime_baralho_console( mesa );

	
	/*
	cout<<"NOVO TESTE--------------------------------------------------"<<endl;

    len::L_Enc<unsigned int> melhor_caso;   ///Bubble = 0 , Quick = 1176
    len::init( melhor_caso );
    len::L_Enc<unsigned int> pior_caso;     ///Bubble = 647 , Quick = 233
    len::init( pior_caso );
    len::L_Enc<unsigned int> medio_caso;    ///Bubble = 131 , Quick = 933
    len::init( medio_caso );

    for( unsigned int I = 0 ; I < 49 ; I++ ){
        len::insere_final( melhor_caso , I );
    }
    for( unsigned int I = 0 ; I < 49 ; I++ ){
        len::insere_final( pior_caso , ((unsigned int)rand()%50) );
        
    }
    for( unsigned int I = 0 ; I < 24 ; I++ ){
        len::insere_final( medio_caso , (unsigned int)rand()%25 );
    }
    for( unsigned int I = 25 ; I < 49 ; I++ ){
        len::insere_final( medio_caso , I );
    }
    
    cout<<"\t\t\nMelhor caso:\n"<<endl;
    DEBUG_SHOW_LIST( melhor_caso );
    cout<<"\t\t\nPior caso:\n"<<endl;
    DEBUG_SHOW_LIST( pior_caso );
    cout<<"\t\t\nMedio caso:\n"<<endl;
    DEBUG_SHOW_LIST( medio_caso );

    cout<<"Ordenando" << endl;
    len::quickSort( medio_caso );

    DEBUG_SHOW_LIST( medio_caso );
	*/

	return 0;
}
