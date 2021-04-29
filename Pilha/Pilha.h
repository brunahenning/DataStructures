#include "Lista_Encadeada.h"

namespace pil{
	
	template<typename T>
	struct Pilha{
		len::L_Enc<T> pilha;
	};

	template<typename T>
	bool push(Pilha<T> &pilha, T dado){
		return len::insere_inicio(pilha.pilha, dado);
	}

	template<typename T>
	T pop(Pilha<T> &pilha){
		T ret = pilha.pilha.inicio->data;
		len::remove_inicio(pilha.pilha);
		return ret;
	}

	template<typename T>
	T peek(Pilha<T> &pilha){
		return pilha.pilha.inicio->data;
	}

}
