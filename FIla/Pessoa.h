#include "Fila.h"
#include <iostream> ////Damned intellisense

namespace pes{

    struct Pessoa{
        std::string nome;
        unsigned int data;
    };

    void DEBUG_SHOW_PESSOA( fila::Fila<Pessoa> &fila){
        if( fila.fila.inicio == nullptr ) return;
        unsigned long lenght = 1;
        L_Enc_elem<Pessoa> *interm = fila.fila.inicio;
        while( interm->prox != nullptr ){
            
            std::cout << "Nome: " << interm->data.nome << "\t\t|Data : " << interm->data.data << std::endl;

            interm = interm->prox;
            lenght++;
        }
        
        std::cout << "Nome: " << interm->data.nome << "\t\t|Data : " << interm->data.data << std::endl;
        std::cout << "\tSize of list : " << lenght << std::endl << std::endl;

        interm = nullptr;
        delete interm;
        
    }

    bool inserePessoa( fila::Fila<Pessoa> &fila , Pessoa pessoa ){

        if( pessoa.data != 0 && pessoa.nome != "" ){
            fila::queue( fila , pessoa );
            return 1;
        }else{
            return 0;
        }

    }

    Pessoa atendePessoa( fila::Fila<Pessoa> &fila ){
        if( fila.fila.inicio != nullptr ){
            return fila::dequeue( fila );
        }else{
            std::cerr << "Impossivel atender fila vazia" << std::endl;
        }
    }

    Pessoa consultaPessoa( fila::Fila<Pessoa> &fila ){
        return fila::consulta_inicio( fila );
    }

    inline void mostrarPessoa( Pessoa pessoa ){
        std::cout<<"-------------------------------------"<< std::endl;
        std::cout<< "Nome da Pessoa: " << pessoa.nome << std::endl;
        std::cout<< "Total de ciclos dessa pessoa: " << pessoa.data << std::endl;
    }

    bool atendeFilaInteira( fila::Fila<Pessoa> &atendimento ){

        if( atendimento.fila.inicio == nullptr ) return 0;

        while( atendimento.fila.inicio != nullptr ){

        pes::Pessoa pessoaAtual = pes::atendePessoa( atendimento );
        pes::mostrarPessoa( pessoaAtual );

        for( unsigned int I = pessoaAtual.data ; I > 0 ; I--){
            std::cout << "Ciclos restantes: " << I << std::endl;
        }

        }

        return 1;
    }

}