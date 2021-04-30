
template< typename T >
struct L_Enc_elem{
	T data;
	L_Enc_elem<T> *prox;
};

namespace len{
    template< typename T >
    struct L_Enc{

        L_Enc_elem<T> *inicio;

    };

    template< typename T >
    L_Enc_elem<T>* operator << ( len::L_Enc<T> &list , unsigned long index ){
        L_Enc_elem<T> *interm = list.inicio;
        for( unsigned long I = 0 ; I < index ; I++ ){

            if( interm->prox != nullptr ) interm = interm->prox;
            else return nullptr;

        }
        return interm;
    }


    template< typename T >
    inline void init( L_Enc<T> &list ){
        list.inicio = nullptr;
    }

    template< typename T >
    inline void delete_copy_pointer( L_Enc_elem<T> *shell ){
        shell = nullptr;
        delete shell;
    }

    template< typename T >
    bool insere_final( L_Enc<T> &list , T data ){	///Talvez do while?

        if( list.inicio == nullptr ){	//lista vazia

            L_Enc_elem<T> *shell = new L_Enc_elem<T>;
            shell->data = data;
            shell->prox = nullptr;

            list.inicio = shell;

            delete_copy_pointer( shell );
            return 1;

        }else{

            L_Enc_elem<T> *interm = list.inicio;
            while( interm->prox != nullptr ){
                interm = interm->prox;
            }

            L_Enc_elem<T> *shell = new L_Enc_elem<T>;
            shell->data = data;
            shell->prox = nullptr;

            interm->prox = shell;

            delete_copy_pointer( interm );
            delete_copy_pointer( shell );
            return 1;

        }

    }

    template< typename T >
    bool remove_final( L_Enc<T> &list ){

        if( list.inicio != nullptr ){
            L_Enc_elem<T> *interm = list.inicio;

            if( interm->prox == nullptr ){
                delete interm;
                init( list );
            }

            L_Enc_elem<T> *interm_old;
            while( interm->prox != nullptr ){
                interm_old = interm;
                interm = interm->prox;
            }
            interm_old->prox = nullptr;

            delete_copy_pointer( interm );
            delete_copy_pointer( interm_old );
            return 1;
        }
        return 0;

    }

    template< typename T >
    bool insere_inicio( L_Enc<T> &list , T data ){

        if( list.inicio != nullptr ){

            L_Enc_elem<T> *shell = new L_Enc_elem<T>;
            shell->data = data;
            shell->prox = list.inicio;

            list.inicio = shell;
            delete_copy_pointer( shell );
            return 1;

        }else{

            L_Enc_elem<T> *shell = new L_Enc_elem<T>;
            shell->data = data;
            shell->prox = nullptr;

            list.inicio = shell;
            delete_copy_pointer( shell );
            return 1;

        }

    }

    template< typename T >
    bool remove_inicio( L_Enc<T> &list ){

        if( list.inicio != nullptr ){

            L_Enc_elem<T> *temp = list.inicio;
            list.inicio = list.inicio->prox;

            delete_copy_pointer( temp );
            return 1;

        }else{

            return 0;

        }

    }

    template< typename T >
    bool insere_posicao( L_Enc<T> &list , T data , unsigned long index ){

        if( index < 1 ) return 0;   ///No position 0

        if( list.inicio != nullptr ){

            unsigned long counter = 1;
            L_Enc_elem<T> *interm = list.inicio;
            L_Enc_elem<T> *interm_old;
            while( interm->prox != nullptr ){
                interm_old = interm;
                interm = interm->prox;
                if( counter == index -1 ) break;
                counter++;
            }

            if( counter != index - 1 ) return 0;    ///desired index too big
            
            L_Enc_elem<T> *shell = new L_Enc_elem<T>;
            shell->data = data;
            shell->prox = interm;
            
            interm_old->prox = shell;

            delete_copy_pointer( interm_old );
            delete_copy_pointer( shell );
            delete_copy_pointer( interm );
            return 1;

        }else if( list.inicio == nullptr && index == 1 ){
            L_Enc_elem<T> *shell = new L_Enc_elem<T>;
            shell->data = data;
            shell->prox = nullptr;

            list.inicio = shell;

            delete_copy_pointer( shell );
            return 1;
        }else{
            return 0;
        }
    }

    template< typename T >
    bool remove_posicao( L_Enc<T> &list , unsigned long index ){

        if( index < 1 ) return 0;   ///No index 0;

        if( list.inicio != nullptr && index != 1 ){

            unsigned long counter = 1;
            L_Enc_elem<T> *interm = list.inicio;
            L_Enc_elem<T> *interm_old;
            while( interm->prox != nullptr ){
                interm_old = interm;
                interm = interm->prox;
                if( counter == index -1 ) break;
                counter++;
            }

            if( interm->prox == nullptr ){  ///if last index, cant remove normally
                interm_old->prox = nullptr;
                return 1;
            }
            ///If not the last index
            if( counter != index - 1 ) return 0;    ///desired index too big

            interm_old->prox = interm->prox;

            delete interm;
            delete_copy_pointer( interm_old );
            return 1;
            
        }else if( list.inicio != nullptr && index == 1 ){

            L_Enc_elem<T> *temp = list.inicio;
            list.inicio = list.inicio->prox;

            delete temp;
            return 1;
        
        }else{
            return 0;
        }

    }

    template< typename T >
    unsigned long qtd_lista(  L_Enc<T> &list ){

        if( list.inicio != nullptr ){
            unsigned long lenght = 1;
            L_Enc_elem<T> *interm = list.inicio;
            while( interm->prox != nullptr ){
                interm = interm->prox;
                lenght++;
            }

            interm = nullptr;
            delete interm;
            return lenght;
        }else return 0;

	}

    template< typename T >
    inline void swap(L_Enc_elem<T> *a, L_Enc_elem<T> *b){ 
        L_Enc_elem<T> interm = *a;
        a->data = b->data;
        b->data = interm.data;
	} 

    unsigned int counter_test = 0;

    template< typename T >
    bool ordenar_bubble(  L_Enc<T> &list , unsigned long comeco , unsigned long fim ){

        counter_test = 0;
        unsigned long lenght = qtd_lista(list);
        fim -= 1;

		if( lenght > 1 && comeco > 0 && fim <= lenght ){

			for( unsigned long I = comeco-1 ; I < fim ; I++ ){

                for( unsigned long J = 0 ; J < fim ; J++ ){
                    if( (( list << J )->data) > (( list << J+1 )->data) ){
                        swap( (list << J) , (list << J+1) );
                        counter_test++;
					}
				}

            }
            std::cout<< "Counter: " << counter_test << std::endl;
			return 1;
		}else{
			return 0;
		}

	}

    //QUICKSORT
    /////////////////////////////////////////////////////////////////////////////////////////
    
    template< typename T >
    L_Enc_elem<T>* getTail( L_Enc_elem<T>* elem ){

        ///https://www.codespeedy.com/program-on-quicksort-on-linked-list-in-cpp/
        while( elem->prox != nullptr && elem != nullptr ){
            elem = elem->prox;
        }
        return elem;

    }

    template< typename T >
    L_Enc_elem<T>* partition(   L_Enc_elem<T>* head , L_Enc_elem<T>* end ,
                                L_Enc_elem<T>**newHead , L_Enc_elem<T>** newEnd ){

        ///https://www.codespeedy.com/program-on-quicksort-on-linked-list-in-cpp/
        L_Enc_elem<T>* pivot = end; 
        L_Enc_elem<T> *prev = NULL, *cur = head, *tail = pivot; 

        while (cur != pivot) 
        { 
            if (cur->data < pivot->data) 
            {  
                if ((*newHead) == NULL) 
                    (*newHead) = cur; 
    
                prev = cur;   
                cur = cur->prox; 
                counter_test++;
            } 
            else
            { 
                if (prev) prev->prox = cur->prox; 
                L_Enc_elem<T>* tmp = cur->prox; 
                cur->prox = NULL; 
                tail->prox = cur; 
                tail = cur; 
                cur = tmp; 
                counter_test++;
            } 
        } 
  
        if ((*newHead) == NULL) 
            (*newHead) = pivot; 
    
        (*newEnd) = tail; 
  
        return pivot; 

    }

    template< typename T >
    L_Enc_elem<T>* quickSortRecur( L_Enc_elem<T>* head , L_Enc_elem<T>* end ){

        ///https://www.codespeedy.com/program-on-quicksort-on-linked-list-in-cpp/
        if (!head || head == end) 
            return head; 

        L_Enc_elem<T> *newHead = NULL, *newEnd = NULL; 

        L_Enc_elem<T>* pivot = partition(head, end, &newHead, &newEnd);

        if (newHead != pivot) 
        { 
            L_Enc_elem<T>* tmp = newHead; 
            while (tmp->prox != pivot) 
                tmp = tmp->prox; 
            tmp->prox = NULL; 
    
            newHead = quickSortRecur(newHead, tmp); 
    
            tmp = getTail(newHead); 
            tmp->prox =  pivot; 
        } 

        pivot->prox = quickSortRecur(pivot->prox, newEnd); 
  
        return newHead; 

    }

    template< typename T >
    void quickSort ( L_Enc<T> &list ){
        ///https://www.codespeedy.com/program-on-quicksort-on-linked-list-in-cpp/
        counter_test = 0;
        list.inicio = quickSortRecur(list.inicio, getTail(list.inicio)); 
        std::cout<< "Counter: " << counter_test << std::endl;
        return; 
    }

    //QUICKSORT
    /////////////////////////////////////////////////////////////////////////////////////////
    

}

