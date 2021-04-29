#include <iostream>
#include "Fila.h"

#include <stdlib.h>
#include <time.h>

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

struct Estadio{};


namespace pes/*soa*/{
	enum TipoPessoa{
		NORMAL = 0, SOCIO_TORCEDOR
	};
	struct Pessoa{
		string nome;
		bool atendido;
		TipoPessoa tipo;
	};

	void init(Pessoa &pessoa, string nome, TipoPessoa tipo){
		pessoa.nome = nome;
		pessoa.tipo = tipo;
		pessoa.atendido = TipoPessoa::NORMAL;
	}

	void init_and_randomize(Pessoa &pessoa){
		unsigned char percent1 = rand() % 100;
		if(percent1 > 5){
			pessoa.tipo = TipoPessoa::NORMAL;
		}else{
			pessoa.tipo = TipoPessoa::SOCIO_TORCEDOR;
		}
		for(unsigned short I = 0 ; I < 10 ; I++){
			char rand_char = (rand() % 80) + 33;
			pessoa.nome += rand_char;
		}
		pessoa.atendido = false;
	}
}

int main(){

	srand(time(NULL));
	unsigned long qtd_socio_torcedor = 0;
	unsigned long qtd_normal = 0;
	unsigned long carga_inicial = 0 ;
	unsigned long carga_tempo = 0;
	unsigned long tempo = 0;

	cout << "Quantidade de guinces socio-torcedor: ";
	cin >> qtd_socio_torcedor;
	cout << "Quantidade de guinches normais: ";
	cin >> qtd_normal;
	cout << "Quantidade de pessoas esperando: ";
	cin >> carga_inicial;
	cout << "Qauntidade de pessoas que procuram guinches a cada unidade de tempo: ";
	cin >> carga_tempo;
	cout << "Quantidade de tempo simulado: ";
	cin >> tempo;

	Estadio* guiche_socio_torcedor = new Estadio[qtd_socio_torcedor];
	Estadio* guiche_normal = new Estadio[qtd_normal];
	pes::Pessoa* pessoas_total = new pes::Pessoa[carga_inicial];

	for(unsigned long I = 0 ; I < carga_inicial ; I++){
		pes::init_and_randomize(pessoas_total[I]);
		cout << "Created : " << pessoas_total[I].nome << endl;
	}


	delete[] guiche_socio_torcedor;
	delete[] guiche_normal;
	delete[] pessoas_total;

	return 0;
}
