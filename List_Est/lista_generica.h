
namespace gli{

    template< typename T >
    struct u_Element{
        T var;
    };

    template< typename T , unsigned long MAX >
    struct Gen_List{
        u_Element<T> element[MAX];
        unsigned int size;
        
    };
    
    template< typename T , unsigned long MAX >
    void init( Gen_List< T , MAX > &list ){
        list.size = 0;
    }
    
    template< typename T , unsigned long MAX >
    bool insere_final( Gen_List<T,MAX> &list , T data ){

		if( list.size < MAX ){
                u_Element<T> temp;
                temp.var = data;
			list.element[ list.size ] = temp;
			list.size++;
			return 1;
		}else{
			return 0;
		}

	}

    template< typename T , unsigned long MAX >
    bool remove_final( Gen_List<T,MAX> &list ){
		if( list.size > 0 ){
			list.size--;
			return 1;
		}else{
			return 0;
		}
	}

    template< typename T , unsigned long MAX >
    unsigned long list_size( Gen_List<T,MAX> &list ){
		return list.size;
	}

    template< typename T , unsigned long MAX >
    bool insere_inicio( Gen_List<T,MAX> &list , T data ){
		if( list.size < MAX ){
			
			for( unsigned int I = list.size ; I > 0 ; I-- ){
				list.element[ I ] = list.element[ I-1 ];
			}

            u_Element<T> temp_data;
            temp_data.var = data;
            list.element[0] = temp_data;
            list.size++;

			return 1;
		}else{
			return 0;
		}
	}

    template< typename T , unsigned long MAX >
    bool remove_inicio( Gen_List<T,MAX> &list ){
		if( list.size > 0 ){

			for( unsigned int I = 0 ; I < list.size ; I++ ){
				list.element[I] = list.element[ I+1 ];
			}

			list.size--;
			return 1;
		}else{
			return 0;
		}
	}

    template< typename T , unsigned long MAX >
    bool remove_posicao( Gen_List<T,MAX> &list , const unsigned long posicao ){

		if( posicao > list.size || posicao > 0 ){

            for( short I = posicao-1 ; I < list.size ; I++ ){
                list.element[I] = list.element[ I+1 ];
			}
            list.size--;
			return 1;

		}else{
			return 0;
		}

	}

    template< typename T , unsigned long MAX >
    bool insere_posicao( Gen_List<T,MAX> &list , const T data , const unsigned long posicao ){

		if( posicao-1 <= list.size && posicao > 0 && list.size < MAX ){

            for( unsigned long I = posicao-1 ; I < list.size ; I++ ){
                list.element[ I+1 ] = list.element[I];
			}
            u_Element<T> temp_data;
            temp_data.var = data;
            list.element[ posicao-1 ].var = temp_data.var;
            list.size++;

			return 1;
		}else{
			return 0;
		}
	}

	unsigned int counter_test = 0;

    template< typename T , unsigned long MAX >
    bool ordenar_bubble( Gen_List<T,MAX> &list , unsigned int comeco , unsigned int fim ){

		counter_test = 0;
		if( list.size > 1 && comeco > 0 && fim <= list.size ){

			for( unsigned long I = comeco-1 ; I < fim ; I++ ){

				for( unsigned long J = 0 ; J < fim ; J++ ){
                    if( list.element[J].var > list.element[J+1].var ){

                        u_Element<T> swapo = list.element[J];
                        list.element[J] = list.element[ J+1 ];
                        list.element[ J+1 ] = swapo;
						counter_test++;
					}
				}

			}

			std::cout<<"Counter: " << counter_test << std::endl;
			return 1;
		}else{
			return 0;
		}

	}

    template< typename T>
    inline void swap(T* a, T* b){ 
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
				counter_test++;
			} 
		} 
		swap(&arr[i + 1], &arr[high]); 
		i++;
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

		counter_test = 0;
		fim+=1;
		if( list.size > 1 && comeco > 0 && fim > 0 ){

			T temp_data[ list.size+1 ];
            //temp_data[0];
			for( unsigned long I = 1 ; I < list.size+1 ; I++ ){
				temp_data[I] = list.element[I-1].var;
			}
			quickSort( temp_data , comeco-1 , fim );

			for( unsigned long I = 1 ; I < list.size+1 ; I++ ){
				list.element[I-1].var = temp_data[I];
			}
			std::cout<<"Counter: " << counter_test << std::endl;
			return 1;
		}else{
			return 0;
		}

	}
	
}


