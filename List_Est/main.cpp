#include<iostream>
#include "poker.h"  ///new poker

using namespace std;

    template< typename T , unsigned long MAX >
    void DEBUG_DISPLAY_ARRAY(gli::Gen_List<T,MAX> &list){
        cout<<"Lista Tamanho: " << gli::list_size(list) << endl;
        for( unsigned long I = 0 ; I < list.size ; I++ ){
            cout<< "Index["<<I<<"], " <<"Pos["<<I+1<<"]: " << list.element[I].var << endl;
        }
    }

int main(){

    /*
    gli::Gen_List< int , 52 > baralho;
    gli::init( baralho );
    gli::insere_final( baralho , 123 );
    gli::insere_inicio( baralho , 456 );
    gli::insere_inicio( baralho , 789 );
    gli::insere_inicio( baralho , 345 );
    gli::insere_inicio( baralho , 678 );

    DEBUG_DISPLAY_ARRAY( baralho );
    cout<<"--------------"<<endl;

    gli::remove_inicio(baralho);
    DEBUG_DISPLAY_ARRAY( baralho );
    cout<<"--------------"<<endl;

    gli::remove_posicao( baralho , 2 );
    DEBUG_DISPLAY_ARRAY( baralho );
    cout<<"--------------"<<endl;

    gli::insere_posicao( baralho , 987 , 3 );
    DEBUG_DISPLAY_ARRAY( baralho );
    cout<<"--------------"<<endl;

    cout<<"BEFORE: " << endl;
    gli::insere_inicio( baralho , 432 );
    gli::insere_inicio( baralho , 321 );
    DEBUG_DISPLAY_ARRAY( baralho );
    cout<<"--------------"<<endl;

    cout<<"Bubble e Quick: " << endl;
    //gli::ordenar_quick( baralho , 1 , gli::list_size(baralho) );
    gli::ordenar_bubble( baralho , 1 , gli::list_size( baralho ) );
    DEBUG_DISPLAY_ARRAY( baralho );
    cout<<"--------------"<<endl;
    */

    cout<<"Testando novo baralho..."<<endl<<endl;

    cout << "Criando e populando novo baralho: " << endl;
    gli::Gen_List< crd::Simples_Carta , 52 > baralho_n;
    gli::init( baralho_n );
    crd::Simples_Carta carta_s;
    crd::criar_carta_simples( carta_s , 'A' , 'C' , 'V' );
    gli::insere_inicio( baralho_n , carta_s );
    crd::criar_carta_simples( carta_s , '2' , 'P' , 'P' );
    gli::insere_inicio( baralho_n , carta_s );
    crd::criar_carta_simples( carta_s , '3' , 'E' , 'V' );
    gli::insere_inicio( baralho_n , carta_s );

    pkr::imprime_baralho_console( baralho_n , 1 );

    cout<<"Montando baralho: " << endl;
    pkr::monta_baralho( baralho_n );
    pkr::imprime_baralho_console( baralho_n , 1 );

    cout<<"Embaralhando: " << endl;
    pkr::embaralha( baralho_n );
    pkr::imprime_baralho_console( baralho_n , 1 );

    cout<<"Criando jogadores e mesa" << endl;
    gli::Gen_List< crd::Simples_Carta , 3 > jogador1;
    gli::init( jogador1 );
    gli::Gen_List< crd::Simples_Carta , 3 > jogador2;
    gli::init( jogador1 );
    gli::Gen_List< crd::Simples_Carta , 3 > jogador3;
    gli::init( jogador1 );
    gli::Gen_List< gli::Gen_List<crd::Simples_Carta , 3> , 3 > jogadores;
    gli::init( jogadores );
    gli::Gen_List< crd::Simples_Carta , 5 > mesa;
    gli::init( mesa );

    gli::insere_final( jogadores , jogador1 );
    gli::insere_final( jogadores , jogador2 );
    gli::insere_final( jogadores , jogador3 );

    pkr::distribuir_cartas_fase_um( baralho_n , mesa , jogadores );

    //jogadores.    element[0]. var.        element[0]. var.    carta_s
    //  grupo,      index,      jogador,    index,      carta,  valor da carta

    cout<<"\n\nJogadores: " << endl;
    pkr::imprime_baralho_console( jogadores.element[0].var , 1 ); cout<<"\n";
    pkr::imprime_baralho_console( jogadores.element[1].var , 1 ); cout<<"\n";
    pkr::imprime_baralho_console( jogadores.element[2].var , 1 ); cout<<"\n";

    cout<<"\nMesa: " << endl;
    pkr::imprime_baralho_console( mesa , 1 ); cout<<"\n";

    cout<<"\nBaralho: " << endl;
    pkr::imprime_baralho_console( baralho_n , 1 );

    cout<<"Fase 2: " << endl<<endl;

    pkr::distribuir_cartas_fase_dois( baralho_n , mesa , jogadores );

    cout<<"\n\nJogadores: " << endl;
    pkr::imprime_baralho_console( jogadores.element[0].var , 1 ); cout<<"\n";
    pkr::imprime_baralho_console( jogadores.element[1].var , 1 ); cout<<"\n";
    pkr::imprime_baralho_console( jogadores.element[2].var , 1 ); cout<<"\n";

    cout<<"\nMesa: " << endl;
    pkr::imprime_baralho_console( mesa , 1 ); cout<<"\n";

    cout<<"\nBaralho: " << endl;
    pkr::imprime_baralho_console( baralho_n , 1 );

    //-----------------------------------------
    cout<<"\n\nTestando ordenações\n\n";

    cout<<"Montando baralho: " << endl;
    pkr::monta_baralho( baralho_n );
    pkr::imprime_baralho_console( baralho_n , 1 );

    cout<<"Embaralhando: " << endl;
    pkr::embaralha( baralho_n );
    pkr::imprime_baralho_console( baralho_n , 1 );

    cout<<"Bubble: " << endl;
    cout<<pkr::ordenar_bubble( baralho_n , 1 , gli::list_size( baralho_n )-1 , 'V' )<<endl;

    cout<<"\nBaralho: " << endl;
    pkr::imprime_baralho_console( baralho_n , 1 );

    
    cout<<"-----------------------------------------------"<<endl;

    cout<<"Montando baralho: " << endl;
    pkr::monta_baralho( baralho_n );
    pkr::imprime_baralho_console( baralho_n , 1 );

    cout<<"Embaralhando: " << endl;
    pkr::embaralha( baralho_n );
    pkr::imprime_baralho_console( baralho_n , 1 );
    
    cout<<"Quick: " << endl;
    cout<<pkr::ordenar_quick( baralho_n , 1 , gli::list_size( baralho_n ) )<<endl;

    cout<<"\nBaralho: " << endl;
    pkr::imprime_baralho_console( baralho_n , 1 );
    
    

    return 0;
}