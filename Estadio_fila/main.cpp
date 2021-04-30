#include <iostream>
#include "Fila.h"

#include <stdlib.h>
#include <time.h>

using namespace std;

namespace pes/*soa*/{
	enum TipoPessoa{
		NORMAL = 0, SOCIO_TORCEDOR
	};
	struct Pessoa{
		string nome;
		bool atendido;
		TipoPessoa tipo;
                unsigned int turnos;
	};

        bool RandomChanceGen(unsigned int chance){  ///Not very efficient
            return (((rand() % 100)+1) < chance);
        }

        Pessoa init_and_randomize(){
                Pessoa pessoa;
                pessoa.atendido = false;
                if(RandomChanceGen(95)){    ///Normal 95% of the time
			pessoa.tipo = TipoPessoa::NORMAL;
		}else{
			pessoa.tipo = TipoPessoa::SOCIO_TORCEDOR;
		}

                if(pessoa.tipo == TipoPessoa::NORMAL){
                    if(RandomChanceGen(25)){
                        pessoa.turnos = 1;
                    }else if(RandomChanceGen(30)){
                        pessoa.turnos = 2;
                    }else{
                        pessoa.turnos = 3;
                    }
                }else{  ///SocioTorcedor
                    if(RandomChanceGen(85)){
                        pessoa.turnos = 1;
                    }else{
                        pessoa.turnos = 2;
                    }
                }

		for(unsigned short I = 0 ; I < 10 ; I++){
			char rand_char = (rand() % 80) + 33;
			pessoa.nome += rand_char;
		}
                return pessoa;
	}

        void display(Pessoa pessoa, string indentation = ""){
            cout << indentation << "////////////////////////////////" << endl;
            cout << indentation << "Nome:\t\t" << pessoa.nome << endl;
            cout << indentation << "Atendido:\t" << ((pessoa.atendido)? "true" : "false") << endl;
            cout << indentation << "Tipo:\t\t" << ((pessoa.tipo == TipoPessoa::NORMAL)? "Normal" : "Socio Torcedor") << endl;
            cout << indentation << "Turnos:\t\t" << pessoa.turnos << endl;
            cout << indentation << "\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\" << endl;
        }
}

namespace est/*adio*/ {
    struct Estadio{

        ///Contem arrays de filas normais e socio torcedores
        fila::Fila<pes::Pessoa>* guinche_normal;
        fila::Fila<pes::Pessoa>* guinche_socio_torcedor;

        ///Total de pessoas
        fila::Fila<pes::Pessoa> total_pessoas;

        ///Variables
        unsigned long qtd_socio_torcedor;
        unsigned long qtd_normal;
        unsigned long carga_inicial;
        unsigned long carga_tempo;
    };

    /* Example:
        fila::queue(estadio.guinche_normal[0], fila::dequeue(pessoas_total) );
        pes::display(fila::dequeue(estadio.guinche_normal[0]));
    */

    void init(Estadio& estadio, unsigned int qtd_normal, unsigned int qtd_socio_torcedor, unsigned int carga_inicial, unsigned int carga_tempo){
        ///Make sure to have everything assigned before initing
        for(unsigned int I = 0 ; I < qtd_normal ; I++){
            fila::init(estadio.guinche_normal[I]);
        }

        for(unsigned int I = 0 ; I < qtd_socio_torcedor ; I++){
            fila::init(estadio.guinche_socio_torcedor[I]);
        }

        estadio.qtd_normal = qtd_normal;
        estadio.qtd_socio_torcedor = qtd_socio_torcedor;
        estadio.carga_inicial = carga_inicial;
        estadio.carga_tempo = carga_tempo;
    }

    void display_fila(fila::Fila<pes::Pessoa>& fila, string indentation = ""){
        len::L_Enc<pes::Pessoa> list = fila.fila;
        unsigned long lenght = 1;
        L_Enc_elem<pes::Pessoa> *interm = list.inicio;
        while( interm->prox != nullptr ){
            pes::display(interm->data, indentation);
            interm = interm->prox;
            lenght++;
        }
            pes::display(interm->data, indentation);
            cout << indentation << "\tTamanho da fila : " << lenght << endl << endl;

            interm = nullptr;
    }
}


int main(){

	srand(time(NULL));
	unsigned long qtd_socio_torcedor = 0;
	unsigned long qtd_normal = 0;
	unsigned long carga_inicial = 0 ;
	unsigned long carga_tempo = 0;
	unsigned long tempo = 0;

        est::Estadio estadio;

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

        fila::Fila<pes::Pessoa> pessoas_total;
        fila::init(pessoas_total);

        for(unsigned long I = 0 ; I < carga_inicial ; I++){
                fila::queue(pessoas_total, pes::init_and_randomize());
        }

        estadio.guinche_normal = new fila::Fila<pes::Pessoa>[qtd_normal];   ///Allocate Heap
        estadio.guinche_socio_torcedor = new fila::Fila<pes::Pessoa>[qtd_socio_torcedor];   ///Allocate Heap
        estadio.total_pessoas = pessoas_total;
        est::init(estadio, qtd_normal, qtd_socio_torcedor, carga_inicial, carga_tempo);

        est::display_fila(pessoas_total, "\t");

        delete[] estadio.guinche_normal;
        delete[] estadio.guinche_socio_torcedor;
	return 0;
}
