#include <cstring> /// for memcpy
#include <ostream>
#include <time.h>
#include <stdlib.h>


namespace CRD{
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


}
////Structure above kept

namespace pkr{

const short max = 52;	//???
struct Baralho{
    CRD::Simples_Carta cartas[max];
	unsigned char tamanho_s; ///Although char, use as int
};

    void initialize( Baralho &baralho ){
		baralho.tamanho_s = 0;
	}

    bool insere_carta_final( Baralho &baralho , const unsigned char carta ){

		if( baralho.tamanho_s < max ){
			baralho.cartas[ baralho.tamanho_s ].carta_s = carta;
			baralho.tamanho_s++;
			return 1;
		}else{
			return 0;
		}

	}

    bool remove_cartas_final( Baralho &baralho ){
		if( baralho.tamanho_s > 0 ){
			baralho.tamanho_s--;
			return 1;
		}else{
			return 0;
		}
	}

    unsigned char qtd_cartas( Baralho &baralho ){
		return baralho.tamanho_s;
	}

    bool imprime_carta( Baralho &baralho , char ref[] , const unsigned char endereco ){
		if( endereco <= baralho.tamanho_s && endereco > 0){
			
			unsigned char temp_carta = '\0';
			unsigned char temp_naipe = '\0';
			unsigned char temp_cor = '\0';

			temp_carta	= ( baralho.cartas[endereco-1].carta_s & 0x0F );	///0000XXXX
			temp_naipe	= ( baralho.cartas[endereco-1].carta_s & 0x30 );	///00XX0000
			temp_cor	= ( baralho.cartas[endereco-1].carta_s & 0x40 );	///0X000000

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

    void imprime_baralho_console( Baralho &baralho ){

		char carta_i[3];

		std::cout<<"Tamanho do baralho: " << (int)baralho.tamanho_s << std::endl;

		for( unsigned char I = 1 ; I < max+1 ; I++ ){
			carta_i[0] = ' ';
			carta_i[1] = ' ';
			carta_i[2] = ' ';
			imprime_carta( baralho , carta_i , I);
			std::cout<<"Carta: " 	<< carta_i[0] <<
			" Naipe: " 				<< carta_i[1] <<
			" Cor: " 				<< carta_i[2];

			if( I <= baralho.tamanho_s ){
				std::cout<<"--"<<std::endl;
			}else{
				std::cout<<std::endl;
			}

		}

	}

    bool remove_inicio( Baralho &baralho ){
		if( baralho.tamanho_s > 0 ){
			for( short I = 0 ; I < baralho.tamanho_s ; I++ ){
				baralho.cartas[I].carta_s = baralho.cartas[I+1].carta_s;
			}
			baralho.tamanho_s--;
			return 1;
		}else{
			return 0;
		}
	}

    bool insere_inicio( Baralho &baralho , const unsigned char carta ){
		if( baralho.tamanho_s < max ){

			//unsigned char copyc [max];
			unsigned char s_copy[max];
			for(unsigned char I = 0 ; I < max ; I++){
				s_copy[I] = baralho.cartas[I].carta_s;
			}
			//memcpy( copyc , baralho.cartas_s, sizeof(copyc));

			for( short I = 0 ; I < baralho.tamanho_s ; I++ ){
				baralho.cartas[I+1].carta_s = s_copy[I];
			}
			baralho.cartas[0].carta_s = carta;
			baralho.tamanho_s++;
			return 1;
		}else{
			return 0;
		}
	}

    bool remove_posicao( Baralho &baralho , const unsigned char posicao ){

		if( posicao > baralho.tamanho_s || posicao > 0 ){

			//char copyc [max];
			unsigned char s_copy[max];
			for(unsigned char I = 0 ; I < max ; I++){
				s_copy[I] = baralho.cartas[I].carta_s;
			}
			//memcpy( copyc , baralho.cartas_s, sizeof(copyc));

			for( short I = posicao-1 ; I < baralho.tamanho_s+1 ; I++ ){
				baralho.cartas[I].carta_s = s_copy[I+1];
			}
			baralho.tamanho_s--;
			return 1;
		}else{
			return 0;
		}

	}

    bool insere_posicao( Baralho &baralho , const unsigned char carta , const unsigned char posicao ){

		if( posicao-1 <= baralho.tamanho_s && posicao > 0 && baralho.tamanho_s < max ){
			//char copyc [max];
			unsigned char s_copy[max];
			for(unsigned char I = 0 ; I < max ; I++){
				s_copy[I] = baralho.cartas[I].carta_s;
			}
			//memcpy( copyc , baralho.cartas_s, sizeof(copyc));
	
			for( short I = posicao-1 ; I < baralho.tamanho_s+1 ; I++ ){
				baralho.cartas[I+1].carta_s = s_copy[I];
			}
			baralho.cartas[posicao-1].carta_s = carta;
			baralho.tamanho_s++;
			return 1;
		}else{
			return 0;
		}
	}

    bool monta_baralho( Baralho &baralho ){
		
		unsigned char counter = 0;

		for( unsigned char I = 0 ; I < 127 ; I++ ){
			
			unsigned char temp_check = '\0';
			temp_check = ( I & 0x0F );
			if( temp_check <= 0x0C ){
				baralho.cartas[counter].carta_s = I;

				if( counter < 26 ){	///Vermelho if true
					baralho.cartas[counter].carta_s = ( baralho.cartas[counter].carta_s | 0x0040 );
				}

				counter++;
				//std::cout<<"Counter: " << (int)counter << std::endl;

			}

			if( counter == 52 ) break;
			
		}

		baralho.tamanho_s = 52;

		return 1;
		
	}

	
    bool embaralha( Baralho &baralho ){

		if( baralho.tamanho_s > 1 ){

			srand(time(NULL));
			
			for( unsigned char I = 0 ; I < baralho.tamanho_s ; I++ ){

				unsigned int temp_r = rand()%baralho.tamanho_s;
				unsigned char carta_r = baralho.cartas[I].carta_s;
				baralho.cartas[I].carta_s = baralho.cartas[temp_r].carta_s;
				baralho.cartas[temp_r].carta_s = carta_r;	//Swap

			}


			return 1;
		}else{
			return 0;
		}

	}
	

    void swap(unsigned char* a, unsigned char* b){ 
		unsigned char t = *a; 
		*a = *b; 
		*b = t; 
	} 

    bool ordenar_cartas_bubble( Baralho &baralho ){

		if( baralho.tamanho_s > 1 ){

			for( unsigned char I = 0 ; I < ( baralho.tamanho_s-1 ) - 1 ; I++ ){

				for( unsigned char J = 0 ; J < ( baralho.tamanho_s-1 ) - I ; J++ ){
					if ( baralho.cartas[ J ].carta_s > baralho.cartas[ J+1 ].carta_s ){ 

						//unsigned char swapo = baralho.cartas_s[ J ];
						//baralho.cartas_s[ J ] = baralho.cartas_s[ J+1 ];
						//baralho.cartas_s[ J+1 ] = swapo;

                        swap( &baralho.cartas[ J ].carta_s , &baralho.cartas[ J+1 ].carta_s );

					}
				}

			}

			return 1;
		}else{
			return 0;
		}


	}

	// partition the array using last element as pivot
	int partition (unsigned char arr[], unsigned char low, unsigned char high) 
	{ 
		///https://www.softwaretestinghelp.com/quick-sort/
		unsigned char pivot = arr[high];    // pivot 
		unsigned char i = (low - 1);   
	
		for (unsigned char j = low; j <= high- 1; j++) 
		{ 
			//if current element is smaller than pivot, increment the low element
			//swap elements at i and j
			if (arr[j] <= pivot) 
			{ 
				i++;    // increment index of smaller element 
				swap(&arr[i], &arr[j]); 
			} 
		} 
		swap(&arr[i + 1], &arr[high]); 
		return (i + 1); 
	} 
	
	//quicksort algorithm
	void quickSort( unsigned char arr[], unsigned char low, unsigned char high) 
	{ 
		///https://www.softwaretestinghelp.com/quick-sort/
		if (low < high) 
		{ 
			//partition the array 
			int pivot = partition(arr, low, high); 
	
			//sort the sub arrays independently 
			quickSort(arr, low, pivot - 1); 
			quickSort(arr, pivot + 1, high); 
		} 
	}  

	unsigned char ordenar_cartas_quick( Baralho &baralho , unsigned char comeco , unsigned char fim ){

		if( baralho.tamanho_s > 1 && comeco > 0 && fim > 0 ){

			unsigned char temp_card[baralho.tamanho_s];
			for( unsigned int I = 0 ; I < baralho.tamanho_s ; I++ ){
				temp_card[I] = baralho.cartas[I].carta_s;
			}
			quickSort( temp_card , comeco-1 , fim-1 );

			for( unsigned int I = 0 ; I < baralho.tamanho_s ; I++ ){
				baralho.cartas[I].carta_s = temp_card[I];
			}
			return 1;
		}else{
			return 0;
		}

	}

	unsigned char distribuir_cartas_fase_um( Baralho &baralho , Baralho &jog_mes , const unsigned char num_players ){

		/*	Return table:
		 *	1 - All good
		 *	2 - Too many players
		 *	3 - jog_mes array hs too many cards
		 *	4 - baralho has no cards to remove
		*/

		if( num_players < 47 ){

			for( unsigned char I = 0 ; I < num_players ; I++ ){

				for( unsigned char J = 0 ; J < 3 ; J++ ){	///Two cards for every player
					if( J < 2 ){
						if( insere_carta_final( jog_mes , baralho.cartas[0].carta_s ) == 0) return 3;
						if( remove_inicio( baralho ) == 0 ) return 4;
					}else{
						if( insere_carta_final( jog_mes , 0xFF ) == 0 ) return 3;	///Give U
					}
				}

			}

			for( unsigned char I = 0 ; I < 5 ; I++ ){	///Table recieves 3 cards
				if( I < 3 ){
					if( insere_carta_final( jog_mes , baralho.cartas[0].carta_s ) == 0) return 3;
					if( remove_inicio( baralho ) == 0 ) return 4;
				}
			}

			return 1;

		}else{
			return 2;
		}

	}

	unsigned char distribuir_cartas_fase_dois( Baralho &baralho , Baralho &jog_mes , const unsigned char num_players ){

		/*	Return table:
		 *	1 - All good
		 *	2 - Too many players
		 *	3 - removal index invalid
		 *	4 - insertion index invalid
		 *	5 - baralho has no cards to remove
		 *	6 - jog_mes array hs too many cards
		*/

		if( num_players < 47 ){

			for( unsigned char I = 0 ; I < num_players ; I++ ){

				if( remove_posicao( jog_mes , (I*3) + 3) == 0) return 3;
				if( insere_posicao( jog_mes , baralho.cartas[0].carta_s, (I*3) + 3 ) == 0 ) return 4;
				if( remove_inicio( baralho ) == 0 ) return 5;

			}

			if( insere_carta_final( jog_mes , baralho.cartas[0].carta_s ) == 0) return 6;
			if( remove_inicio( baralho ) == 0 ) return 5;
			if( insere_carta_final( jog_mes , baralho.cartas[0].carta_s ) == 0) return 6;
			if( remove_inicio( baralho ) == 0 ) return 5;

			return 1;

		}else{
			return 2;
		}

	}


}
