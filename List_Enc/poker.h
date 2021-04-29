#include "Lista_Encadeada.h"
using namespace len;

namespace crd{
	struct Simples_Carta{
		
		unsigned char carta_s;

		///carta_s will be composed of 'Ucnnvvvv' where
		//U is undefined
		//c is the color, where 1 is red and 0 is black
		//n is naipe, where 00 is Ouro, 01 is Copas, 10 is Paus and 11 is Espadas
		//v is carta, wich starts at 0000 to A and 0001 to 2 and 0010 to 3 ... 1000 to 9 and 1001 to 'D' and 1010 to 'J'...
		//EXAMPLE:
		//	'3''C''V', 3 de copas vermelho -> 01 01 0010
		//	'A''E''P', As de Espadas Preto -> 00 11 0000
		//NOTE: 'D' = 10, using one char only

	};

	short testar_entrada( char carta , char naipe , char cor ){

		//If return is: 
		//0, naipe is undefined
		//1, cor is undefined
		//2, carta is undefined
		//3, good combination

		if( naipe == 'O' || naipe == 'C' || naipe == 'P' || naipe == 'E' ){
			
			if( cor == 'V' || cor == 'P' ){
				
				if( 	carta == 'A' ||
					carta == 'J' ||
					carta == 'Q' ||
					carta == 'K' ||
					carta == 'D' ||
					( carta > 0x30 && carta < 0x3A )
				){
					return 3;
				}else{
					return 2;
				}

			}else{
				return 1;
			}

		}else{
			return 0;
		}
	}

	unsigned char criar_carta_simples( Simples_Carta &carta_o, char carta , char naipe , char cor ){
		
		short test = testar_entrada( carta , naipe , cor );
		//std::cout<<"Entrada e: " << test << std::endl;

		if( test == 3 ){
			carta_o.carta_s = '\0';
			///first four bits for carta
			if( carta == 'A' ){
				carta_o.carta_s = ( carta_o.carta_s | 0x00 );	
			}else if( carta == 'J' ){
				carta_o.carta_s = ( carta_o.carta_s | 0x0A );
			}else if( carta == 'Q' ){
				carta_o.carta_s = ( carta_o.carta_s | 0x0B );
			}else if( carta == 'K' ){
				carta_o.carta_s = ( carta_o.carta_s | 0x0C );
			}else if( carta == 'D' ){
				carta_o.carta_s = ( carta_o.carta_s | 0x09 );
			}
			else{
				carta_o.carta_s = ( carta_o.carta_s | carta - '0' - 1 );
			}
			///Next two bits for naipe
			switch( naipe ){	
				case 'O': carta_o.carta_s = ( carta_o.carta_s | 0x0000 ); break;
				case 'C': carta_o.carta_s = ( carta_o.carta_s | 0x0010 ); break;
				case 'P': carta_o.carta_s = ( carta_o.carta_s | 0x0020 ); break;
				case 'E': carta_o.carta_s = ( carta_o.carta_s | 0x0030 ); break;
			}
			///second to last bit for color
			if( cor == 'V' ){
				carta_o.carta_s = ( carta_o.carta_s | 0x0040 );
			}
			///last bit is unused
			//std::cout<< "Final card is: " << carta_s << std::endl; 
			return carta_o.carta_s;

		}

	}

};


bool operator >( crd::Simples_Carta a , crd::Simples_Carta b ){
    if( a.carta_s > b.carta_s ) return 1;
    return 0;
}
bool operator <( crd::Simples_Carta a , crd::Simples_Carta b ){
    if( a.carta_s < b.carta_s ) return 1;
    return 0;
}

namespace pkr{

    template< typename T >
    bool imprime_carta( L_Enc<T> &list, char ref[] , const unsigned long endereco ){
		if( endereco <= qtd_lista( list ) && endereco > 0){
			
			unsigned char temp_carta = '\0';
			unsigned char temp_naipe = '\0';
			unsigned char temp_cor = '\0';

			//temp_carta	= ( baralho.cartas[endereco-1].carta_s & 0x0F );	///0000XXXX
			//temp_naipe	= ( baralho.cartas[endereco-1].carta_s & 0x30 );	///00XX0000
			//temp_cor	= ( baralho.cartas[endereco-1].carta_s & 0x40 );	///0X000000

			temp_carta	= ( (list << endereco-1)->data.carta_s & 0x0F );	///0000XXXX
			temp_naipe	= ( (list << endereco-1)->data.carta_s & 0x30 );	///00XX0000
			temp_cor	= ( (list << endereco-1)->data.carta_s & 0x40 );	///0X000000

			temp_naipe = ( temp_naipe >> 4 );	/// 00XX0000 -> 000000XX

			switch (temp_carta) {
				case 0x00:	ref[0] = 'A'; break;
				case 0x01:	ref[0] = '2'; break;
				case 0x02:	ref[0] = '3'; break;
				case 0x03:	ref[0] = '4'; break;
				case 0x04:	ref[0] = '5'; break;
				case 0x05:	ref[0] = '6'; break;
				case 0x06:	ref[0] = '7'; break;
				case 0x07:	ref[0] = '8'; break;
				case 0x08:	ref[0] = '9'; break;
				case 0x09:	ref[0] = 'D'; break;
				case 0x0A:	ref[0] = 'J'; break;
				case 0x0B:	ref[0] = 'Q'; break;
				case 0x0C:	ref[0] = 'K'; break;

				default: ref[0] = 'U';
			}

			switch( temp_naipe ){
				case 0x00:	ref[1] = 'O'; break;
				case 0x01:	ref[1] = 'C'; break;
				case 0x02:	ref[1] = 'P'; break;
				case 0x03:	ref[1] = 'E'; break;
				
				default:	ref[1] = 'U';
			}

			if( temp_cor == 0x0040 ){
				ref[2] = 'V';
			}else{
				ref[2] = 'P';
			}

			return 1;
		}else{
			return 0;
		}
	}

    template< typename T >
	void imprime_baralho_console( L_Enc<T> &list ){

		char carta_i[3];

        unsigned long max = qtd_lista( list );
		std::cout<<"Tamanho do baralho: " << max << std::endl;
		
		for( unsigned char I = 1 ; I < max+1 ; I++ ){
			carta_i[0] = ' ';
			carta_i[1] = ' ';
			carta_i[2] = ' ';
			imprime_carta( list , carta_i , I);
			std::cout<<"Carta: " 	<< carta_i[0] <<
			" Naipe: " 				<< carta_i[1] <<
			" Cor: " 				<< carta_i[2];

			if( I <= max ){
				std::cout<<"--"<<std::endl;
			}else{
				std::cout<<std::endl;
			}

		}

	}

    template< typename T >
	bool monta_baralho( L_Enc<T> &list ){
		
		unsigned char counter = 0;
        init(list); ///Começa do inicio

		for( unsigned char I = 0 ; I < 127 ; I++ ){
			
			unsigned char temp_check = '\0';
			temp_check = ( I & 0x0F );
			if( temp_check <= 0x0C ){

                crd::Simples_Carta carta;
                carta.carta_s = I;
                insere_final( list , carta );

				if( counter < 26 ){	///Vermelho if true
					( list << counter )->data.carta_s = ( ( list << counter )->data.carta_s | 0x0040 );
				}

				counter++;

			}

			if( counter == 52 ) break;
			
		}

		return 1;
		
	}

    template< typename T >
	bool embaralha( L_Enc<T> &list ){

        unsigned long size = qtd_lista(list);
		if( size > 1 ){

			srand(time(NULL));
			
			for( unsigned char I = 0 ; I < size ; I++ ){
				unsigned int temp_r = rand()%size;
                swap( ( list << I ) , ( list << temp_r ) );
			}

			return 1;
		}else{
			return 0;
		}

	}

    
	unsigned char distribuir_cartas_fase_um( 	L_Enc<crd::Simples_Carta> &baralho , 
												L_Enc<crd::Simples_Carta> &mesa , 
												L_Enc<L_Enc< crd::Simples_Carta >> &jogadores,
                                                unsigned int num_players ){

	    ///3 cards to mesa, 2 cards to each jogadores
		crd::Simples_Carta temp_carta;

		for( unsigned long I = 0 ; I < num_players ; I++ ){	///For each player
			
            init( ( jogadores << I )->data );
			for( unsigned long J = 0 ; J < 2 ; J++ ){

				//temp_carta = baralho.element[0].var;
                temp_carta = baralho.inicio->data;
				//gli::remove_inicio( baralho );
                len::remove_inicio( baralho );

				//gli::insere_inicio( jogadores.element[I].var , temp_carta );
                len::insere_inicio( ( jogadores << I )->data , temp_carta );

			}
			
		}

        init( mesa );
		for( unsigned long I = 0 ; I < 3 ; I++ ){

			//temp_carta = baralho.element[0].var;
            temp_carta = baralho.inicio->data;

			//gli::remove_inicio( baralho );
            len::remove_inicio( baralho );

			//gli:insere_inicio( mesa , temp_carta );
            len::insere_inicio( mesa , temp_carta );

		}

	}

    unsigned char distribuir_cartas_fase_dois( 	L_Enc<crd::Simples_Carta> &baralho , 
												L_Enc<crd::Simples_Carta> &mesa , 
												L_Enc<L_Enc< crd::Simples_Carta >> &jogadores,
                                                unsigned int num_players ){

	    ///3 cards to mesa, 2 cards to each jogadores
		crd::Simples_Carta temp_carta;

		for( unsigned long I = 0 ; I < num_players ; I++ ){	///For each player
			
            //temp_carta = baralho.element[0].var;
            temp_carta = baralho.inicio->data;

			//gli::remove_inicio( baralho );
            len::remove_inicio( baralho );

			//gli::insere_inicio( jogadores.element[I].var , temp_carta );
			len::insere_inicio( ( jogadores << I )->data , temp_carta );
			
		}

        for( unsigned long I = 0 ; I < 2 ; I++ ){

			//temp_carta = baralho.element[0].var;
            temp_carta = baralho.inicio->data;

			//gli::remove_inicio( baralho );
            len::remove_inicio( baralho );

			//gli:insere_inicio( mesa , temp_carta );
            len::insere_inicio( mesa , temp_carta );
		}

	}

}