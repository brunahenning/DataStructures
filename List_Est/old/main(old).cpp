#include<iostream>
#include <ostream>
#include"poker.h"


using namespace std;

int main(){

	/*	TODO
	 *	--------------
	 *	--------------
	 *	--------------
	 *	--------------
	 *	--------------
	 *	--------------
	 *
	*/

	pkr::Baralho baralho;
	initialize( baralho );

	CRD::Simples_Carta carta_s;
	unsigned char carta;

	cout<<"\n\tTestando (insere carta final): "<<endl;
	
	carta = CRD::criar_carta_simples( carta_s , 'A' , 'C', 'V');
	cout<<pkr::insere_carta_final( baralho , carta )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;
	carta = CRD::criar_carta_simples( carta_s , '3' , 'C', 'V');
	cout<<pkr::insere_carta_final( baralho , carta )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;
	carta = CRD::criar_carta_simples( carta_s , 'J' , 'E', 'P');
	cout<<pkr::insere_carta_final( baralho , carta )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;

	cout<<"\n\n\tTestando (imprime_carta): " << endl;
	char carta_i[3];

	cout<< pkr::imprime_carta( baralho , carta_i , 3 ) << endl;
	cout<<"Carta: " << carta_i[0] << " Naipe: " << carta_i[1] << " Cor: " << carta_i[2]<<endl<<endl<<endl;

	cout<<"\n\n";
	pkr::imprime_baralho_console( baralho );

	cout<<"\n\n\tTestando (remove_carta_final): "<<endl;
	cout<<pkr::remove_cartas_final( baralho )<<endl;
	cout<<"Tamanho do baralho: " << (int)pkr::qtd_cartas( baralho ) << endl;
	cout<<pkr::remove_cartas_final( baralho )<<endl;
	cout<<"Tamanho do baralho: " << (int)pkr::qtd_cartas( baralho ) << endl;

	cout<<"\n\n";
	pkr::imprime_baralho_console( baralho );

	cout<<"\n\n\tRe-preenchendo decke..."<<endl;
	carta = CRD::criar_carta_simples( carta_s , 'J' , 'E', 'P');
	cout<<pkr::insere_carta_final( baralho , carta )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;
	carta = CRD::criar_carta_simples( carta_s , '7' , 'O', 'P');
	cout<<pkr::insere_carta_final( baralho , carta )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;
	carta = CRD::criar_carta_simples( carta_s , '9' , 'P', 'V');
	cout<<pkr::insere_carta_final( baralho , carta )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;

	cout<<"\n\n";
	pkr::imprime_baralho_console( baralho );

	cout<<"\n\n\tTestando (remove_inicio): "<<endl;
	cout<<pkr::remove_inicio( baralho )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;
	cout<<pkr::remove_inicio( baralho )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;

	cout<<"\n\n";
	pkr::imprime_baralho_console( baralho );


	cout<<"\n\n\tTestando (insere_inicio): "<<endl;

	carta = CRD::criar_carta_simples( carta_s , '4' , 'C', 'P');
	cout<<pkr::insere_inicio( baralho , carta )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;
	carta = CRD::criar_carta_simples( carta_s , 'Q' , 'O', 'V');
	cout<<pkr::insere_inicio( baralho , carta )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;
	carta = CRD::criar_carta_simples( carta_s , 'K' , 'E', 'P');
	cout<<pkr::insere_inicio( baralho , carta )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;

	cout<<"\n\n";
	pkr::imprime_baralho_console( baralho );


	cout<<"\n\n\tTestando (remove_posicao): "<<endl;

	cout<<pkr::remove_posicao( baralho , 3 )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;
	cout<<pkr::remove_posicao( baralho , 3 )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;

	cout<<"\n\n";
	pkr::imprime_baralho_console( baralho );


	cout<<"\n\n\tTestando (insere_posicao): "<<endl;
	carta = CRD::criar_carta_simples( carta_s , '4' , 'P', 'V');
	cout<<pkr::insere_posicao( baralho , carta , 2 )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;
	carta = CRD::criar_carta_simples( carta_s , '8' , 'E', 'P');
	cout<<pkr::insere_posicao( baralho , carta , 5 )<<endl;
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;

	cout<<"\n\n";
	pkr::imprime_baralho_console( baralho );

	cout<<"\n\n\tTestando (monta_baralho): "<<endl;
	pkr::monta_baralho( baralho );
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;

	cout<<"\n\n";
	pkr::imprime_baralho_console( baralho );

	cout<<"\n\n\tTestando (embaralhar): "<<endl;
	pkr::embaralha( baralho );
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;

	cout<<"\n\n";
	pkr::imprime_baralho_console( baralho );
	
	/*
	cout<<"\n\n\tTestando (ordenar_cartas_bubble): "<<endl;
	pkr::ordenar_cartas_bubble( baralho );
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;

	cout<<"\n\n";
	pkr::imprime_baralho_console( baralho );
	*/

	
	cout<<"\n\n\tTestando (ordenar_cartas_quick): "<<endl;
	pkr::ordenar_cartas_quick( baralho , 1 , pkr::qtd_cartas( baralho ) );
	cout<<"Tamanho do baralho: " << (int)qtd_cartas(baralho) << endl;
	

	cout<<"\n\n";
	pkr::imprime_baralho_console( baralho );


	//-----
	
	cout<<"\n\n\tTestando (Jogador): "<<endl;

	pkr::Baralho jog_mes;	///4 players with 3 cards each (12 cards) and 5 cards for table
							///Number of players can be upto 47 but in this case is 4, as is most common
	
	pkr::distribuir_cartas_fase_um( baralho , jog_mes , 4);

	cout<<"\n\tBaralho: "<<endl;
	pkr::imprime_baralho_console( baralho );

	cout<<"\n\n\t Jogadores e Mesa: " << endl;
	pkr::imprime_baralho_console( jog_mes );

	cout<<"\n\tTestando fase 2: "<<endl;

	pkr::distribuir_cartas_fase_dois( baralho , jog_mes , 4);

	cout<<"\n\tBaralho: "<<endl;
	pkr::imprime_baralho_console( baralho );

	cout<<"\n\n\t Jogadores e Mesa: " << endl;
	pkr::imprime_baralho_console( jog_mes );

	return 0;
}
