#ifndef LISTA_DUP_ENC_H

#define LISTA_DUP_ENC_H


template< typename T >

struct L_D_Enc_elem{

    T data;

    L_D_Enc_elem<T> *prox;

    L_D_Enc_elem<T> *prev;

};


namespace lde{

    template< typename T >

    struct L_D_Enc{
        L_D_Enc_elem<T> *inicio;
        L_D_Enc_elem<T> *fim;
    };


    template< typename T >
    inline void init( L_D_Enc<T> &lista ){
        lista.fim = nullptr;
        lista.inicio = nullptr;
    }

    template< typename T >
    inline void delete_copy_pointer( L_D_Enc_elem<T> *shell ){
        shell = nullptr;
        delete shell;
    }

    template< typename T >
    L_D_Enc_elem<T>* operator << ( L_D_Enc<T> &list , unsigned long index ){
        L_D_Enc_elem<T> *interm = list.inicio;
        for( unsigned long I = 0 ; I < index ; I++ ){

            if( interm->prox != nullptr ) interm = interm->prox;
            else return nullptr;

        }
        return interm;
    }

    template< typename T >
    inline void swap(L_D_Enc_elem<T> *a, L_D_Enc_elem<T> *b){ 
        L_D_Enc_elem<T> interm = *a;
        a->data = b->data;
        b->data = interm.data;
	} 

    template< typename T >
    bool insere_fim( L_D_Enc<T> &lista , T data ){

        L_D_Enc_elem<T>* new_elem = new L_D_Enc_elem<T> ;
        new_elem->data = data;

        if( lista.fim == nullptr ){ //lista vazia
            new_elem->prev = nullptr;
            new_elem->prox = nullptr;

            lista.fim = new_elem;
            lista.inicio = new_elem;

            delete_copy_pointer( new_elem );
            return 1;

        }else{  //lista preenchida

            lista.fim->prox = new_elem;
            new_elem->prev = lista.fim;
            new_elem->prox = nullptr;

            lista.fim = new_elem;

            delete_copy_pointer( new_elem );
            return 1;

        }

    }


    template< typename T >
    bool remove_fim( L_D_Enc<T> &lista ){

        if( lista.fim == nullptr || lista.inicio == nullptr ){ //lista vazia

            return 0;

        }else{

            lista.fim = lista.fim->prev;
            delete lista.fim->prox;

            lista.fim->prox = nullptr;

            return 1;

        }

    }

    template< typename T >
    bool insere_inicio( L_D_Enc<T> &lista , T data ){

        L_D_Enc_elem<T>* new_elem = new L_D_Enc_elem<T> ;
        new_elem->data = data;

        if( lista.fim == nullptr ){ //lista vazia
            new_elem->prev = nullptr;
            new_elem->prox = nullptr;

            lista.fim = new_elem;
            lista.inicio = new_elem;

            return 1;

        }else{

            new_elem->prox = lista.inicio;
            lista.inicio->prev = new_elem;
            new_elem->prev = nullptr;

            lista.inicio = new_elem;
            delete_copy_pointer( new_elem );
            return 1;

        }

    }

    template< typename T >
    bool remove_inicio( L_D_Enc<T> &list ){

        if( list.inicio != nullptr ){

            L_D_Enc_elem<T> *temp = list.inicio;
            list.inicio = list.inicio->prox;
            list.inicio->prev = nullptr;

            delete_copy_pointer( temp );
            return 1;

        }else{

            return 0;

        }

    }

    template< typename T >
    unsigned long qtd_lista( L_D_Enc<T> &list ){

        if( list.inicio == nullptr ) return 0;
        unsigned long counter = 1;
        L_D_Enc_elem<T>* interm = list.inicio;

        while( interm->prox != nullptr ){
            interm = interm->prox;
            counter++;
        }

        return counter;

    }

    template< typename T >
    bool insere_posicao( L_D_Enc<T> &list , T data , unsigned long index ){

        if( index == 0 ) return 0;   ///No position 0
        if( index == 1 && list.inicio != nullptr ){ ///insere_inicio
            L_D_Enc_elem<T>* new_elem = new L_D_Enc_elem<T> ;
            new_elem->data = data;
            new_elem->prox = list.inicio;
            list.inicio->prev = new_elem;
            new_elem->prev = nullptr;

            list.inicio = new_elem;
            delete_copy_pointer( new_elem );
            return 1;
        }

        if( list.inicio != nullptr ){

            unsigned long counter = 1;
            L_D_Enc_elem<T> *interm = list.inicio;
            L_D_Enc_elem<T> *interm_old;
            while( interm->prox != nullptr ){
                interm_old = interm;
                interm = interm->prox;
                if( counter == index -1 ) break;
                counter++;
            }
            if( interm->prox == nullptr && counter != index - 1 ){  ///Insere_fim
                L_D_Enc_elem<T>* new_elem = new L_D_Enc_elem<T> ;
                new_elem->data = data;
                list.fim->prox = new_elem;
                new_elem->prev = list.fim;
                new_elem->prox = nullptr;

                list.fim = new_elem;

                delete_copy_pointer( interm_old );
                delete_copy_pointer( new_elem );
                delete_copy_pointer( interm );
                return 1;
            }
            if( counter != index - 1 ) return 0;    ///desired index too big
            
            L_D_Enc_elem<T>* new_elem = new L_D_Enc_elem<T> ;
            new_elem->data = data;
            new_elem->prox = interm;
            new_elem->prev = interm_old;
            
            interm_old->prox = new_elem;
            interm->prev = new_elem;

            delete_copy_pointer( interm_old );
            delete_copy_pointer( new_elem );
            delete_copy_pointer( interm );
            return 1;

        }else if( list.inicio == nullptr && index == 1 ){
            L_D_Enc_elem<T>* new_elem = new L_D_Enc_elem<T> ;
            new_elem->data = data;
            new_elem->prox = list.inicio;
            list.inicio->prev = new_elem;
            new_elem->prev = nullptr;

            list.inicio = new_elem;
            delete_copy_pointer( new_elem );
            return 1;
        }else{
            return 0;
        }
    }

    template< typename T >
    bool remove_posicao( L_D_Enc<T> &list , unsigned long index ){

        if( index == 0 ) return 0;

        if( index == 1 ){   ///Remove_inicio
            L_D_Enc_elem<T> *temp = list.inicio;
            list.inicio = list.inicio->prox;
            list.inicio->prev = nullptr;

            delete_copy_pointer( temp );
            return 1;
        }

        L_D_Enc_elem<T> *interm = list.inicio;
        unsigned long counter = 0;
        while( interm->prox != nullptr && counter < index-1 ){
            interm = interm->prox;
            counter++;
        }
        
        if( interm->prox == nullptr && interm->prev != nullptr ){  ///Remove_fim
            list.fim = list.fim->prev;
            delete list.fim->prox;

            list.fim->prox = nullptr;

            return 1;
        }

        ///NOTE, if the index goes too far, it removes the last index aways, seems

        interm->prev->prox = interm->prox;
        interm->prox->prev = interm->prev;

        return 1;

    }

    template< typename T >
    bool ordenar_bubble(  L_D_Enc<T> &list , unsigned long comeco , unsigned long fim ){

        unsigned long lenght = qtd_lista(list);
        fim -= 1;

		if( lenght > 1 && comeco > 0 && fim <= lenght ){

			for( unsigned long I = comeco-1 ; I < fim ; I++ ){

                for( unsigned long J = 0 ; J < fim ; J++ ){
                    if( (( list << J )->data) > (( list << J+1 )->data) ){
                        swap( (list << J) , (list << J+1) );
					}
				}

            }

			return 1;
		}else{
			return 0;
		}

	}

    //QUICKSORT
    /////////////////////////////////////////////////////////////////////////////////////////
    
    template< typename T >
    L_D_Enc_elem<T> *lastNode(L_D_Enc_elem<T> *root) 
    { 
        while (root && root->prox) 
            root = root->prox; 
        return root; 
    } 
    
    template< typename T >
    L_D_Enc_elem<T>* partition(L_D_Enc_elem<T> *l, L_D_Enc_elem<T> *h) 
    { 
        // set pivot as h element 
        int x = h->data; 
    
        // similar to i = l-1 for array implementation 
        L_D_Enc_elem<T> *i = l->prev; 
    
        // Similar to "for (int j = l; j <= h- 1; j++)" 
        for (L_D_Enc_elem<T> *j = l; j != h; j = j->prox) 
        { 
            if (j->data <= x) 
            { 
                // Similar to i++ for array 
                i = (i == NULL)? l : i->prox; 
    
                swap( i , j ); 
            } 
        } 
        i = (i == NULL)? l : i->prox; // Similar to i++ 
        swap( i , h );
        return i; 
    } 
    
    template< typename T >
    void _quickSort(L_D_Enc_elem<T>* l, L_D_Enc_elem<T> *h) 
    { 
        if (h != NULL && l != h && l != h->prox) 
        { 
            L_D_Enc_elem<T> *p = partition(l, h); 
            _quickSort(l, p->prev); 
            _quickSort(p->prox, h); 
        } 
    } 
    
    template< typename T >
    void quickSort(L_D_Enc_elem<T> *head) 
    { 
        //https://www.geeksforgeeks.org/quicksort-for-linked-list/     
        L_D_Enc_elem<T> *h = lastNode(head); 
    
        _quickSort(head, h); 
    } 

    //QUICKSORT
    /////////////////////////////////////////////////////////////////////////////////////////
    
}


#endif // LISTA_DUP_ENC_H
