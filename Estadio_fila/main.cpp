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

        inline bool RandomChanceGen(unsigned int chance){  ///Not very efficient
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

            for(unsigned short I = 0 ; I < 10 ; I++){
                char rand_char = (rand() % 80) + 33;
                pessoa.nome += rand_char;
            }

            if(pessoa.tipo == TipoPessoa::NORMAL){

                if(RandomChanceGen(25)){pessoa.turnos = 1; return pessoa;}
                if(RandomChanceGen(30)){pessoa.turnos = 2; return pessoa;}
                if(RandomChanceGen(45)){pessoa.turnos = 3; return pessoa;}
                pessoa.turnos = 3;
                return pessoa;

            }else{  ///SocioTorcedor
                if(RandomChanceGen(85)){
                    pessoa.turnos = 1;
                }else{
                    pessoa.turnos = 2;
                }
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
        if(fila.fila.inicio == nullptr){
            cout << "Fila Vazia" << endl;
            return;
        }
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

    void display_todas_filas_normais(Estadio& estadio, string indentation = ""){
        cout << "================================================================================================" << endl;
        cout << "Filas Normais:" << endl;
        for(unsigned int I = 0 ; I < estadio.qtd_normal ; I++){
            cout << "Fila[" << I << "]: " << endl;
            display_fila(estadio.guinche_normal[I], indentation);
        }
        cout << "================================================================================================" << endl;
    }

    void display_inicio_filas_normais(Estadio& estadio, string indentation = ""){
        cout << "=================================================" << endl;
        cout << "Filas Normais:" << endl;
        for(unsigned int I = 0 ; I < estadio.qtd_normal ; I++){
            cout << "Fila[" << I << "]: " << endl;
            if(estadio.guinche_normal[I].fila.inicio != nullptr)
                pes::display(estadio.guinche_normal[I].fila.inicio->data, indentation);
        }
        cout << "=================================================" << endl;
    }

    void display_todas_filas_socio(Estadio& estadio, string indentation = ""){
        cout << "================================================================================================" << endl;
        cout << "Filas Socio Torcedoras:" << endl;
        for(unsigned int I = 0 ; I < estadio.qtd_socio_torcedor ; I++){
            cout << "Fila Socio Torcedora[" << I << "]: " << endl;
            display_fila(estadio.guinche_socio_torcedor[I], indentation);
        }
        cout << "================================================================================================" << endl;
    }

    void display_inicio_filas_socio(Estadio& estadio, string indentation = ""){
        cout << "=================================================" << endl;
        cout << "Filas Socio Torcedoras:" << endl;
        for(unsigned int I = 0 ; I < estadio.qtd_socio_torcedor ; I++){
            cout << "Fila[" << I << "]: " << endl;
            if(estadio.guinche_socio_torcedor[I].fila.inicio != nullptr)
                pes::display(estadio.guinche_socio_torcedor[I].fila.inicio->data, indentation);
        }
        cout << "=================================================" << endl;
    }
}

namespace taxa{
    struct DadosRelevantes{ /*Dados Relevantes por fila*/
        unsigned int num_pessoas_total;
        unsigned int num_pessoas_normal;
        unsigned int num_pessoas_socio;

        unsigned int num_pessoas_3_turnos_normal;
        unsigned int num_pessoas_2_turnos_normal;
        unsigned int num_pessoas_1_turnos_normal;

        unsigned int num_pessoas_2_turnos_socio;
        unsigned int num_pessoas_1_turnos_socio;
    };

    inline void init(DadosRelevantes& dados){
        dados.num_pessoas_total = 0;
        dados.num_pessoas_normal = 0;
        dados.num_pessoas_socio = 0;

        dados.num_pessoas_3_turnos_normal = 0;
        dados.num_pessoas_2_turnos_normal = 0;
        dados.num_pessoas_1_turnos_normal = 0;

        dados.num_pessoas_2_turnos_socio = 0;
        dados.num_pessoas_1_turnos_socio = 0;
    }

    inline double taxa_media(double total, double variavel){
        return ((variavel / total)*100);
    }

    void extrair_dados_relevantes(fila::Fila<pes::Pessoa>& fila, DadosRelevantes& dados){
        len::L_Enc<pes::Pessoa> list = fila.fila;
        L_Enc_elem<pes::Pessoa> *interm = list.inicio;
        while( interm->prox != nullptr ){
            dados.num_pessoas_total++;

            if(interm->data.tipo == pes::TipoPessoa::NORMAL){
                dados.num_pessoas_normal++;
                if(interm->data.turnos == 3) dados.num_pessoas_3_turnos_normal++;
                else if(interm->data.turnos == 2) dados.num_pessoas_2_turnos_normal++;
                else dados.num_pessoas_1_turnos_normal++;
            }else{
                dados.num_pessoas_socio++;
                if(interm->data.turnos == 2) dados.num_pessoas_2_turnos_socio++;
                else dados.num_pessoas_1_turnos_socio++;
            }
            interm = interm->prox;
        }
        ///Ultima pessoa na lista fica fora do loop
        dados.num_pessoas_total++;
        if(interm->data.tipo == pes::TipoPessoa::NORMAL){
            dados.num_pessoas_normal++;
            if(interm->data.turnos == 3) dados.num_pessoas_3_turnos_normal++;
            else if(interm->data.turnos == 2) dados.num_pessoas_2_turnos_normal++;
            else dados.num_pessoas_1_turnos_normal++;
        }else{
            dados.num_pessoas_socio++;
            if(interm->data.turnos == 2) dados.num_pessoas_2_turnos_socio++;
            else dados.num_pessoas_1_turnos_socio++;
        }


        interm = nullptr;
    }

    void display(DadosRelevantes dados, pes::TipoPessoa tipo){
        cout << "Numero de Pessoas na fila:\t\t" << dados.num_pessoas_total << endl;
        if(tipo == pes::TipoPessoa::NORMAL){
            cout << "Numero de Pessoas Normais:\t\t" << dados.num_pessoas_normal << "(" << taxa_media(dados.num_pessoas_total, dados.num_pessoas_normal) << "%)" << endl;
            cout << "Numero de pessoas que precisam de 3 turnos:\t" << dados.num_pessoas_3_turnos_normal << "(" << taxa_media(dados.num_pessoas_normal, dados.num_pessoas_3_turnos_normal) << "%)" << endl;
            cout << "Numero de pessoas que precisam de 2 turnos:\t" << dados.num_pessoas_2_turnos_normal << "(" << taxa_media(dados.num_pessoas_normal, dados.num_pessoas_2_turnos_normal) << "%)" << endl;
            cout << "Numero de pessoas que precisam de 1 turnos:\t" << dados.num_pessoas_1_turnos_normal << "(" << taxa_media(dados.num_pessoas_normal, dados.num_pessoas_1_turnos_normal) << "%)" << endl;

        }else{
            cout << "Numero de Pessoas Socio Torcedoras:\t\t" << dados.num_pessoas_socio << "(" << taxa_media(dados.num_pessoas_total, dados.num_pessoas_socio) << "%)" << endl;
            cout << "Numero de pessoas que precisam de 2 turnos:\t" << dados.num_pessoas_2_turnos_socio << "(" << taxa_media(dados.num_pessoas_socio, dados.num_pessoas_2_turnos_socio) << "%)" << endl;
            cout << "Numero de pessoas que precisam de 1 turnos:\t" << dados.num_pessoas_1_turnos_socio << "(" << taxa_media(dados.num_pessoas_socio, dados.num_pessoas_1_turnos_socio) << "%)" << endl;
        }
        cout << "\n";
    }

    void display_tudo(DadosRelevantes dados){
        cout << "Numero de Pessoas na fila:\t\t" << dados.num_pessoas_total << endl;
        cout << "Numero de Pessoas Normais:\t\t" << dados.num_pessoas_normal << "(" << taxa_media(dados.num_pessoas_total, dados.num_pessoas_normal) << "%)" << endl;
        cout << "Numero de pessoas que precisam de 3 turnos:\t" << dados.num_pessoas_3_turnos_normal << "(" << taxa_media(dados.num_pessoas_normal, dados.num_pessoas_3_turnos_normal) << "%)" << endl;
        cout << "Numero de pessoas que precisam de 2 turnos:\t" << dados.num_pessoas_2_turnos_normal << "(" << taxa_media(dados.num_pessoas_normal, dados.num_pessoas_2_turnos_normal) << "%)" << endl;
        cout << "Numero de pessoas que precisam de 1 turnos:\t" << dados.num_pessoas_1_turnos_normal << "(" << taxa_media(dados.num_pessoas_normal, dados.num_pessoas_1_turnos_normal) << "%)" << endl;
        cout << "\n";
        cout << "Numero de Pessoas Socio Torcedoras:\t\t" << dados.num_pessoas_socio << "(" << taxa_media(dados.num_pessoas_total, dados.num_pessoas_socio) << "%)" << endl;
        cout << "Numero de pessoas que precisam de 2 turnos:\t" << dados.num_pessoas_2_turnos_socio << "(" << taxa_media(dados.num_pessoas_socio, dados.num_pessoas_2_turnos_socio) << "%)" << endl;
        cout << "Numero de pessoas que precisam de 1 turnos:\t" << dados.num_pessoas_1_turnos_socio << "(" << taxa_media(dados.num_pessoas_socio, dados.num_pessoas_1_turnos_socio) << "%)" << endl;

        cout << "\n";
    }
}


void mainTimeLoop(est::Estadio& estadio, unsigned long tempo){

    unsigned int pessoasAtendidas = 0;
    unsigned int numTotalDePessoas = fila::qtd_fila(estadio.total_pessoas);

    for(unsigned long tempoRestante = tempo ; tempoRestante > 0 ; tempoRestante--){

        cout << "\n\n" << "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\" << endl;
        cout << "" << "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\" << endl;
        cout << "" << "/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\/\\" << endl;

        ///Lidar com a carga de pessoas e dividi-la nas filas...
        for(unsigned int I = 0 ; I < estadio.carga_tempo ; I++){

            if(pessoasAtendidas == numTotalDePessoas){
                cout << "[ALERTA]Numero de pessoas esperando esgotado, Simul????o encerrando." << endl;
                break;
            }
            pessoasAtendidas++;

            bool goodReturn = 0;
            fila::consulta_inicio(estadio.total_pessoas, goodReturn);
            if(!goodReturn){
                cerr << "Corrompimento de Fila 'total_pessoas', Simula????o encerrada." << endl;
                return;
            }

            pes::Pessoa pessoa = fila::dequeue(estadio.total_pessoas);
            cout << "\tMexendo com pessoa: " << endl;
            pes::display(pessoa, "\t");

            if(pessoa.tipo == pes::TipoPessoa::NORMAL){
                ///Procurar guiches normais
                unsigned int menorFila = 0;
                for(unsigned int J = 0 ; J < estadio.qtd_normal ; J++){
                    if(fila::qtd_fila(estadio.guinche_normal[J]) < fila::qtd_fila(estadio.guinche_normal[menorFila])){
                        menorFila = J;
                    }
                }
                cout << "Pessoa Normal incluida na fila '" << menorFila << "'." << endl;
                fila::queue(estadio.guinche_normal[menorFila], pessoa);
            }else{
                ///Procurar guiches socio torcedores
                unsigned int menorFila = 0;
                for(unsigned int J = 0 ; J < estadio.qtd_socio_torcedor ; J++){
                    if(fila::qtd_fila(estadio.guinche_socio_torcedor[J]) < fila::qtd_fila(estadio.guinche_socio_torcedor[menorFila])){
                        menorFila = J;
                    }
                }
                cout << "Pessoa Socio Torcedora incluida na fila '" << menorFila << "'." << endl;
                fila::queue(estadio.guinche_socio_torcedor[menorFila], pessoa);
            }

            //est::display_todas_filas_normais(estadio);
            //est::display_todas_filas_socio(estadio);
            est::display_inicio_filas_socio(estadio, "\t\t");
            est::display_inicio_filas_normais(estadio, "\t\t");
        }


        ///Atender clientes ...
        cout << "Atendendo clientes..." << endl;
        for(unsigned int I = 0 ; I < estadio.qtd_normal; I++){
            if(estadio.guinche_normal[I].fila.inicio != nullptr){
                estadio.guinche_normal[I].fila.inicio->data.turnos--; ///Conex??o direta

                if(estadio.guinche_normal[I].fila.inicio->data.turnos < 1){
                    cout << "Pessoa Normal ' " << estadio.guinche_normal[I].fila.inicio->data.nome << " 'atendida na fila[" << I << "]." << endl;
                    fila::dequeue(estadio.guinche_normal[I]);
                }
            }
        }

        for(unsigned int I = 0 ; I < estadio.qtd_socio_torcedor; I++){
            if(estadio.guinche_socio_torcedor[I].fila.inicio != nullptr){
                estadio.guinche_socio_torcedor[I].fila.inicio->data.turnos--; ///Conex??o direta

                if(estadio.guinche_socio_torcedor[I].fila.inicio->data.turnos < 1){
                    cout << "Pessoa Socio Torcedora ' " << estadio.guinche_socio_torcedor[I].fila.inicio->data.nome << " 'atendida na fila[" << I << "]." << endl;
                    fila::dequeue(estadio.guinche_socio_torcedor[I]);
                }
            }
        }

        cout << "Situa????o final das filas: " << endl;
        est::display_todas_filas_socio(estadio, "\t\t\t");
        est::display_todas_filas_normais(estadio, "\t\t\t");

        ///Ver se as filas est??o vazias, se sim, encerrar a simula????o.

        bool guinche_socio_vazio = true;
        for(unsigned int I = 0 ; I < estadio.qtd_socio_torcedor; I++){
            if(estadio.guinche_socio_torcedor[I].fila.inicio != nullptr) guinche_socio_vazio = false;
        }
        bool guinche_normal_vazio = true;
        for(unsigned int I = 0 ; I < estadio.qtd_normal; I++){
            if(estadio.guinche_normal[I].fila.inicio != nullptr) guinche_normal_vazio = false;
        }

        if(guinche_socio_vazio){
            cout << "Todas as filas nos guinches socio tor??edoras est??o vazias." << endl;
        }
        if(guinche_normal_vazio){
            cout << "Todas as filas nos guinches normais est??o vazias." << endl;
        }

        if(guinche_normal_vazio && guinche_socio_vazio){
            cout << "Todos as filas est??o vazias, Simul????o encerrada." << endl;
            return;
        }

        ///Mostrar Dados relevantes sobre as filas...
        cout << "\n\nDados Importantes sobre Guiches Socio Toredores: " << endl;
        for(unsigned int I = 0 ; I < estadio.qtd_socio_torcedor; I++){
            if(estadio.guinche_socio_torcedor[I].fila.inicio != nullptr){
                taxa::DadosRelevantes dados;
                taxa::init(dados);
                taxa::extrair_dados_relevantes(estadio.guinche_socio_torcedor[I], dados);
                cout << "Dados sobre Guiche Socio Torcedor[" << I << "]: " << endl;
                taxa::display(dados, pes::TipoPessoa::SOCIO_TORCEDOR);
                cout << "\n";
            }
        }

        cout << "\n\nDados Importantes sobre Guiches Normais: " << endl;
        for(unsigned int I = 0 ; I < estadio.qtd_normal; I++){
            if(estadio.guinche_normal[I].fila.inicio != nullptr){
                taxa::DadosRelevantes dados;
                taxa::init(dados);
                taxa::extrair_dados_relevantes(estadio.guinche_normal[I], dados);
                cout << "Dados sobre Guiche Normal[" << I << "]: " << endl;
                taxa::display(dados, pes::TipoPessoa::NORMAL);
                cout << "\n";
            }
        }

        cin.get();
    }

    ///Se codigo chega aqui, tempo acabou
    cout << "Fim de Tempo, Simul????o encerrada." << endl;

}

///////////////////////////////


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

    taxa::DadosRelevantes dados_pessoas;
    taxa::init(dados_pessoas);
    taxa::extrair_dados_relevantes(pessoas_total, dados_pessoas);
    cout << "\n\nDados relevantes sobre 'pessoas_total': " << endl;
    taxa::display_tudo(dados_pessoas);


    estadio.guinche_normal = new fila::Fila<pes::Pessoa>[qtd_normal];   ///Allocate Heap
    estadio.guinche_socio_torcedor = new fila::Fila<pes::Pessoa>[qtd_socio_torcedor];   ///Allocate Heap
    estadio.total_pessoas = pessoas_total;
    est::init(estadio, qtd_normal, qtd_socio_torcedor, carga_inicial, carga_tempo);

    //est::display_fila(pessoas_total, "\t");

    mainTimeLoop(estadio, tempo);

    //est::display_todas_filas_normais(estadio);

    delete[] estadio.guinche_normal;
    delete[] estadio.guinche_socio_torcedor;
    return 0;
}
