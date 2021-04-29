#include "lista_generica.h"

using namespace gli;

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


namespace pkr{

	template< typename T , unsigned long MAX >
    bool imprime_carta( Gen_List<T,MAX> &list , char ref[] , const unsigned long endereco ){
		if( endereco <= list.size && endereco > 0){
			
			unsigned char temp_carta = '\0';
			unsigned char temp_naipe = '\0';
			unsigned char temp_cor = '\0';

			//temp_carta	= ( baralho.cartas[endereco-1].carta_s & 0x0F );	///0000XXXX
			//temp_naipe	= ( baralho.cartas[endereco-1].carta_s & 0x30 );	///00XX0000
			//temp_cor	= ( baralho.cartas[endereco-1].carta_s & 0x40 );	///0X000000

			temp_carta	= ( list.element[endereco-1].var.carta_s & 0x0F );	///0000XXXX
			temp_naipe	= ( list.element[endereco-1].var.carta_s & 0x30 );	///00XX0000
			temp_cor	= ( list.element[endereco-1].var.carta_s & 0x40 );	///0X000000

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

	template< typename T , unsigned long MAX >
	void imprime_baralho_console( Gen_List<T,MAX> &list , bool full_range = 0 ){

		char carta_i[3];

		std::cout<<"Tamanho do baralho: " << list.size << std::endl;
		unsigned long max = 0;

		if( full_range ) max = MAX;
		else max = list.size;

		for( unsigned char I = 1 ; I < max+1 ; I++ ){
			carta_i[0] = ' ';
			carta_i[1] = ' ';
			carta_i[2] = ' ';
			imprime_carta( list , carta_i , I);
			std::cout<<"Carta: " 	<< carta_i[0] <<
			" Naipe: " 				<< carta_i[1] <<
			" Cor: " 				<< carta_i[2];

			if( I <= list.size ){
				std::cout<<"--"<<std::endl;
			}else{
				std::cout<<std::endl;
			}

		}

	}

	template< typename T , unsigned long MAX >
	bool monta_baralho( Gen_List<T,MAX> &list ){
		
		unsigned char counter = 0;

		for( unsigned char I = 0 ; I < 127 ; I++ ){
			
			unsigned char temp_check = '\0';
			temp_check = ( I & 0x0F );
			if( temp_check <= 0x0C ){
				list.element[counter].var.carta_s = I;

				if( counter < 26 ){	///Vermelho if true
					list.element[counter].var.carta_s = ( list.element[counter].var.carta_s | 0x0040 );
				}

				counter++;
				//std::cout<<"Counter: " << (int)counter << std::endl;

			}

			if( counter == 52 ) break;
			
		}

		list.size = 52;

		return 1;
		
	}

	template< typename T , unsigned long MAX >
	bool embaralha( Gen_List<T,MAX> &list ){

		if( list.size > 1 ){

			srand(time(NULL));
			
			for( unsigned char I = 0 ; I < list.size ; I++ ){

				unsigned int temp_r = rand()%list.size;
				
				//unsigned char carta_r = baralho.cartas[I].carta_s;
				//baralho.cartas[I].carta_s = baralho.cartas[temp_r].carta_s;
				//baralho.cartas[temp_r].carta_s = carta_r;	//Swap

				crd::Simples_Carta carta_r;
				carta_r = list.element[I].var;
				list.element[I].var = list.element[temp_r].var;
				list.element[temp_r].var = carta_r;

			}


			return 1;
		}else{
			return 0;
		}

	}

	template< 	typename T , typename P , 
				unsigned long MAXB , unsigned long MAXM , unsigned long MAXP >
	unsigned char distribuir_cartas_fase_um( 	Gen_List<T,MAXB> &baralho , 
												Gen_List<T,MAXM> &mesa , 
												Gen_List<P,MAXP> &jogadores  ){

	    ///3 cards to mesa, 2 cards to each jogadores
		crd::Simples_Carta temp_carta;

		for( unsigned long I = 0 ; I < MAXP ; I++ ){	///For each player
			
			for( unsigned long J = 0 ; J < 2 ; J++ ){

				temp_carta = baralho.element[0].var;
				gli::remove_inicio( baralho );

				gli::insere_inicio( jogadores.element[I].var , temp_carta );

			}
			jogadores.element[I].var.size = 3;

		}

		for( unsigned long I = 0 ; I < 3 ; I++ ){

			temp_carta = baralho.element[0].var;
			gli::remove_inicio( baralho );

			gli:insere_inicio( mesa , temp_carta );

		}

	}

	template< 	typename T , typename P , 
				unsigned long MAXB , unsigned long MAXM , unsigned long MAXP >
	unsigned char distribuir_cartas_fase_dois( 	Gen_List<T,MAXB> &baralho , 
												Gen_List<T,MAXM> &mesa , 
												Gen_List<P,MAXP> &jogadores  ){

		///2 cards to mesa, 1 cards to each jogadores
		crd::Simples_Carta temp_carta;

		for( unsigned long I = 0 ; I < MAXP ; I++ ){	///For each player

			temp_carta = baralho.element[0].var;
			gli::remove_inicio( baralho );

			gli::insere_inicio( jogadores.element[I].var , temp_carta );
			jogadores.element[I].var.size = 3;

		}

		for( unsigned long I = 0 ; I < 2 ; I++ ){

			temp_carta = baralho.element[0].var;
			gli::remove_inicio( baralho );

			gli:insere_inicio( mesa , temp_carta );

		}

	}

	template< typename T , unsigned long MAX >
    bool ordenar_bubble( Gen_List<T,MAX> &list , unsigned int comeco , unsigned int fim , unsigned char p_cor ){

		///p_cor, indica que cor primeiro
		if( p_cor != 'P' && p_cor != 'V' ) return 0;

		if( list.size > 1 && comeco > 0 && fim <= list.size ){

			for( unsigned long I = comeco-1 ; I < fim ; I++ ){

				for( unsigned long J = 0 ; J < fim ; J++ ){
					if( p_cor == 'P' ){
						if( list.element[J].var.carta_s > list.element[J+1].var.carta_s ){

							u_Element<T> swapo = list.element[J];
							list.element[J] = list.element[ J+1 ];
							list.element[ J+1 ] = swapo;

						}
					}else{
						if( list.element[J].var.carta_s < list.element[J+1].var.carta_s ){

							u_Element<T> swapo = list.element[J];
							list.element[J] = list.element[ J+1 ];
							list.element[ J+1 ] = swapo;

						}
					}
				}

			}

			return 1;
		}else{
			return 0;
		}

	}


	template< typename T>
    void swap(T* a, T* b){ 
		T t = *a; 
		*a = *b; 
		*b = t; 
	} 

    // partition the array using last element as pivot
    template< typename T >
	int partition (T arr[], unsigned long low, unsigned long high) 
	{ 
		///https://www.softwaretestinghelp.com/quick-sort/
		T pivot = arr[high];    // pivot 
		unsigned long i = (low - 1);   
	
		for (unsigned long j = low; j <= high- 1; j++) 
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
    template< typename T >
	void quickSort( T arr[], unsigned long low, unsigned long high) 
	{ 
		///https://www.softwaretestinghelp.com/quick-sort/
		if (low < high) 
		{ 
			//partition the array 
			T pivot = partition(arr, low, high); 
	
			//sort the sub arrays independently 
			quickSort(arr, low, pivot - 1); 
			quickSort(arr, pivot + 1, high); 
		} 
	}  

    template< typename T , unsigned long MAX >
    bool ordenar_quick( Gen_List<T,MAX> &list , unsigned long comeco , unsigned long fim ){

		if( list.size > 1 && comeco > 0 && fim > 0 ){

			unsigned char temp_data[ list.size+1 ];
            //temp_data[0];
			for( unsigned long I = 1 ; I < list.size+1 ; I++ ){
				temp_data[I] = list.element[I-1].var.carta_s;
			}
			quickSort( temp_data , comeco-1 , fim );

			for( unsigned long I = 1 ; I < list.size+1 ; I++ ){
				list.element[I-1].var.carta_s = temp_data[I];
			}
			return 1;
		}else{
			return 0;
		}

	}

}