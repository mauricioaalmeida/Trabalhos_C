/******************************************************************************
MAURICIO ANDRE DE ALMEIDA - UniFEI Matricula 2021101420
Pilha implementada por meio de estruturas auto-referenciadas

*******************************************************************************/

#include <iostream>
using namespace std;

const int TamMax = 1000;

struct Celula {
    int Valor;
    Celula *Proximo;
};
struct TipoPilha {
    Celula *Fundo;
    Celula *Topo;
    int Tamanho;
};

// ----------- Funções basicas de Pilhas ---------------
// isEmpty - pilha esta vazia?
bool PilhaIsEmpty ( TipoPilha *pilha ) {
    if ( pilha->Topo != NULL) 
       return false;
    else
       return true;
}

// isFull - pilha esta cheia?
bool PilhaIsFull ( TipoPilha *pilha ) {
    if (pilha->Tamanho >= TamMax)
       return true;
    else
       return false;
}
// PUSH - Empilhar
bool PilhaPush ( int item, TipoPilha *pilha ) {
    if (PilhaIsFull(pilha)) {
        return false;
    } else {
        Celula *ult, *prox;
        // Consulta o topo Atual
        ult = pilha->Topo;
        // Cria a nova celula como o topo da pilha
        prox = new Celula;
        prox->Valor = item;
        prox->Proximo = ult;
        // Atualiza o topo da pilha
        pilha->Topo = prox;
        pilha->Tamanho++;
        return true;
    }
}
// POP - Desempilhar
int PilhaPop ( TipoPilha *pilha ) {
    Celula *topo, *prox;
    int item;
    // Consulta o topo Atual
    topo = pilha->Topo;
    // Copia o item
    item = topo->Valor;
    prox = topo->Proximo;
    // Retira o topo da pilha
    delete topo;
    // Atualiza o topo da pilha
    pilha->Topo = prox; 
    pilha->Tamanho--;
    return item;
}
// TOP - consultar item do topo
int PilhaTop ( TipoPilha *pilha ) {
    Celula *topo;
    int item;
    // Consulta o topo Atual
    topo = pilha->Topo;
    // Copia o item
    item = topo->Valor;
    return item;
}
// Esvazia pilha
void PilhaEmpty ( TipoPilha *pilha ) {
    if (!PilhaIsEmpty( pilha )) {
        while (pilha->Topo != NULL) {
            PilhaPop (pilha);
        }
    }
    
}
// ----------- demais Funcoes 
//Criação da estrutura de dados vazia
void iniciaPilhaVazia( TipoPilha *pilha ) {

    pilha = new TipoPilha;
    pilha->Fundo = NULL;
    pilha->Topo = NULL;
    pilha->Tamanho= 0;
}

//Inserir um novo item no topo
bool insereItem( int item, TipoPilha *pilha)
{
  return PilhaPush ( item, pilha );
}


//Retirar o primeiro item
bool RetiraPrimeiroItem(TipoPilha *pilha, TipoPilha *pilhaAux)
{
    if (PilhaIsEmpty(pilha))
      return false;
    else {
        // esvazia a auxiliar
        int aux;
        PilhaEmpty (pilhaAux);
        while ( !PilhaIsEmpty(pilha) ) {
            // Move os itens para a pilha auxiliar invertendo a ordem
            aux = PilhaPop(pilha);
            PilhaPush( aux, pilhaAux);
        }
        // retira o topo da pilha auxiliar
        PilhaPop(pilhaAux);
        // retorna os itens para a pilha original
        while ( !PilhaIsEmpty(pilhaAux) ) {
            aux = PilhaPop(pilhaAux);
            PilhaPush( aux, pilha);
        } 
        return true;
    }
    
}

//Retirar o i-ésimo item
int RetiraItem (TipoPilha *pilha, TipoPilha *pilhaAux, int posicao) {
    if (PilhaIsEmpty(pilha))
      return -1;
    else {
        int cont = 0;
        // esvazia a auxiliar
        int aux;
        PilhaEmpty (pilhaAux);
        while ( !PilhaIsEmpty(pilha) ) {
            // Move os itens para a pilha auxiliar invertendo a ordem e contando
            cont++;
            aux = PilhaPop(pilha);
            // Pula a posicao
            if (posicao != cont) 
               PilhaPush( aux, pilhaAux);
        }
        // retorna os itens para a pilha original
        while ( !PilhaIsEmpty(pilhaAux) ) {
            aux = PilhaPop(pilhaAux);
            PilhaPush( aux, pilha);
        } 
    }
    return posicao;
}

//Localizar o i-ésimo item para examinar e/ou alterar o conteúdo de seus componentes
int ProcurarItem (TipoPilha *pilha, TipoPilha *pilhaAux, int posicao, int &item) {
    int res = -1;   
    if (PilhaIsEmpty(pilha))
      return -1;
    else {
        int cont = 0;
        int aux;
        // esvazia a auxiliar
        PilhaEmpty (pilhaAux);
        while ( !PilhaIsEmpty(pilha) ) {
            // Move os itens para a pilha auxiliar invertendo a ordem e contando
            cont++;
            aux = PilhaPop(pilha);
            PilhaPush( aux, pilhaAux);
            // Grava a posicao
            if (posicao == cont) {
                res = cont;
                item = aux;
            }
        }
        // retorna os itens para a pilha original
        while ( !PilhaIsEmpty(pilhaAux) ) {
            aux = PilhaPop(pilhaAux);
            PilhaPush( aux, pilha);
        } 
    }
    return res;
}

//Altera o i-ésimo item 
int AlterarItem (TipoPilha *pilha, TipoPilha *pilhaAux, int posicao, int item) {
    int res = -1;
    if (PilhaIsEmpty(pilha))
      return res;
    else {
        int cont = 0;
        int aux;        
        // esvazia a auxiliar
        PilhaEmpty (pilhaAux);
        while ( !PilhaIsEmpty(pilha) ) {
            // Move os itens para a pilha auxiliar invertendo a ordem e contando
            cont++;
            aux = PilhaPop(pilha);
            // Altera o item da posicao escolhida
            if (posicao == cont) {
                PilhaPush( item, pilhaAux);
                res = cont;
            } else
              PilhaPush( aux, pilhaAux); 
        }
        // retorna os itens para a pilha original
        while ( !PilhaIsEmpty(pilhaAux) ) {
            aux = PilhaPop(pilhaAux);
            PilhaPush( aux, pilha);
        } 
    }
    return res;
}

//Combinar duas ou mais da estrutura em questão (lista, fila, pilha, árvore) em uma única estrutura
int CombinarPilha (TipoPilha *pilha1, TipoPilha *pilha2, TipoPilha *pilhaAux) {
    int cont = 0;
    if (PilhaIsEmpty(pilha1) || PilhaIsEmpty(pilha2))
      return -1;
    else {
        int aux;
        // esvazia a auxiliar
        PilhaEmpty (pilhaAux);
        // Move os itens da pilha1 para a auxiliar
        while ( !PilhaIsEmpty(pilha1) ) {
            // Move os itens para a pilha auxiliar invertendo a ordem e contando
            cont++;
            aux = PilhaPop(pilha1);
            PilhaPush( aux, pilhaAux); 
        }
        while ( !PilhaIsEmpty(pilha2) ) {
            // Move os itens para a pilha auxiliar invertendo a ordem e contando
            cont++;
            aux = PilhaPop(pilha2);
            PilhaPush( aux, pilhaAux); 
        }
        // retorna os itens para a pilha original
        while ( !PilhaIsEmpty(pilhaAux) ) {
            aux = PilhaPop(pilhaAux);
            PilhaPush( aux, pilha1);
        } 
    }
    return cont;
}

//Partir uma estrutura em duas
int DividirPilha (TipoPilha *pilha1, TipoPilha *pilha2, TipoPilha *pilhaAux, int posicao) {
    int cont = 0;
    if (PilhaIsEmpty(pilha1))
      return -1;
    else {
        // esvazia a auxiliar e a pilha2
        PilhaEmpty (pilhaAux);
        PilhaEmpty (pilha2);
        int aux;
        // Move os itens da pilha1 para a auxiliar até chegar na posicao
        while ( !PilhaIsEmpty(pilha1) ) {
            // Move os itens para a pilha auxiliar invertendo a ordem e contando
            cont++;
            aux = PilhaPop(pilha1);
            PilhaPush( aux, pilhaAux); 
            if (cont == posicao) {
                break;
            }
        }
        while ( !PilhaIsEmpty(pilhaAux) ) {
            // Move os itens da pilha auxiliar para a pilha2 invertendo a ordem
            cont++;
            aux = PilhaPop(pilhaAux);
            PilhaPush( aux, pilha2); 
        }
    }
    return cont;
}

//Fazer uma cópia
int CopiarPilha (TipoPilha *pilha1, TipoPilha *pilha2, TipoPilha *pilhaAux) {
    int cont = 0;
    if (PilhaIsEmpty(pilha1))
      return -1;
    else {
        // esvazia a auxiliar e a pilha2
        PilhaEmpty (pilhaAux);
        PilhaEmpty (pilha2);
        int aux;
        // Move os itens da pilha1 para a auxiliar 
        while ( !PilhaIsEmpty(pilha1) ) {
            // Move os itens para a pilha auxiliar invertendo a ordem e contando
            cont++;
            aux = PilhaPop(pilha1);
            PilhaPush( aux, pilhaAux); 
        }
        while ( !PilhaIsEmpty(pilhaAux) ) {
            // Move os itens da pilha auxiliar para a pilha1 e pilha2 invertendo a ordem
            cont++;
            aux = PilhaPop(pilhaAux);
            PilhaPush( aux, pilha1); 
            PilhaPush( aux, pilha2); 
        }
    }
    return cont;
}

//Ordenar os itens da estrutura em ordem ascendente ou descendente, de acordo com alguns de seus componentes
void OrdenarPilha (TipoPilha *pilha1, TipoPilha *pilha2, TipoPilha *pilhaAux) {
    int menor;
    // Move todos os itens para a pilha auxiliar, encontrando o menor e retirando-o para a pilha2 ao retornar
    if (!PilhaIsEmpty(pilha1)) {
        // esvazia a auxiliar e a pilha2
        PilhaEmpty (pilhaAux);
        PilhaEmpty (pilha2);
        int aux;
        // loop de ordenacao (soh termina qdo a pilha1 e aux estiverem vazias)
        do {
            // pega o primeiro item para iniciar
            aux = PilhaTop(pilha1);
            menor = aux;
            // Move os itens da pilha1 para a auxiliar encontrando o menor deles
            while ( !PilhaIsEmpty(pilha1) ) {
                aux = PilhaPop(pilha1);
                if (aux < menor) 
                    menor = aux;
                PilhaPush( aux, pilhaAux); 
            }    
            // Move de volta para a pilha1 retirando o(s) menor(es) para a pilha2
            while ( !PilhaIsEmpty(pilhaAux) ) {
                aux = PilhaPop(pilhaAux);
                if (aux == menor)
                    PilhaPush( aux, pilha2);
                else
                    PilhaPush( aux, pilha1); 
            }    
        } while (!(PilhaIsEmpty(pilha1) && PilhaIsEmpty(pilhaAux)));
        // Retorna os itens para a pilha1, para manter a ordem crescente
        while ( !PilhaIsEmpty(pilha2) ) {
            aux = PilhaPop(pilha2);
            PilhaPush( aux, pilha1); 
        }
    }
}

//Pesquisar a primeira ocorrência de um item com um valor particular
int PesquisarItem (TipoPilha *pilha, TipoPilha *pilhaAux, int pesq) {
    int res = -1;   
    if (PilhaIsEmpty(pilha))
      return -1;
    else {
        int cont = 0;
        int aux;
        // esvazia a auxiliar
        PilhaEmpty (pilhaAux);
        while ( !PilhaIsEmpty(pilha) ) {
            // Move os itens para a pilha auxiliar invertendo a ordem e pesquisando
            cont++;
            aux = PilhaPop(pilha);
            PilhaPush( aux, pilhaAux);
            // Grava a posicao
            if (aux == pesq) {
                res = cont;
            }
        }
        // retorna os itens para a pilha original
        while ( !PilhaIsEmpty(pilhaAux) ) {
            aux = PilhaPop(pilhaAux);
            PilhaPush( aux, pilha);
        } 
    }
    return res;
}

//Pesquisar a quantidade de ocorrências de um valor particular
int OcorrenciasItem (TipoPilha *pilha, TipoPilha *pilhaAux, int pesq) {
    int ocorr = -1;   
    if (PilhaIsEmpty(pilha))
      return -1;
    else {
        int cont = 0;
        ocorr = 0;
        int aux;
        // esvazia a auxiliar
        PilhaEmpty (pilhaAux);
        while ( !PilhaIsEmpty(pilha) ) {
            // Move os itens para a pilha auxiliar invertendo a ordem e pesquisando
            cont++;
            aux = PilhaPop(pilha);
            PilhaPush( aux, pilhaAux);
            // incrementa a ocorrencia
            if (aux == pesq) {
                ocorr++;
            }
        }
        // retorna os itens para a pilha original
        while ( !PilhaIsEmpty(pilhaAux) ) {
            aux = PilhaPop(pilhaAux);
            PilhaPush( aux, pilha);
        } 
    }
    return ocorr;
}

// Listar os itens da pilha
void ImprimePilha (TipoPilha *pilha, TipoPilha *pilhaAux) {
    int aux;
    if (PilhaIsEmpty(pilha)) {
       cout << "---- LISTA VAZIA! ----" << endl;
    } else {
        int cont = 0;
        cout << "---- Inicio da Lista ----" << endl;
        // esvazia a auxiliar
        PilhaEmpty (pilhaAux);
        while ( !PilhaIsEmpty(pilha) ) {
            // Move os itens para a pilha auxiliar invertendo a ordem e imprimindo
            cont++;
            aux = PilhaPop(pilha);
            cout << "Posicao: " << cont << " = Valor: " << aux << endl;
            PilhaPush( aux, pilhaAux);
            
            }
        cout << "---- Fim da Lista ----" << endl;
        // retorna os itens para a pilha original
        while ( !PilhaIsEmpty(pilhaAux) ) {
            aux = PilhaPop(pilhaAux);
            PilhaPush( aux, pilha);
        } 
    }
}

int main() {
    TipoPilha *pilha1, *pilha2, *pilhaAux;
    int opcao;
    int valor, posicao, tamanho, ocorr;
    do {
        cout << "  --------------------------------------------------------------------------------  " << endl;
        cout << "   1) Criar uma Pilha vazia:             ";
        cout << "   2) Inserir um novo item na Pilha:     " << endl;
        cout << "   3) Retirar o primeiro item:           ";
        cout << "   4) Retirar o i-esimo item:            " << endl;
        cout << "   5) Localizar o i-esimo item:          ";
        cout << "   6) Combinar duas Pilhas:              " << endl;
        cout << "   7) Partir uma Pilha em duas:          ";
        cout << "   8) Fazer uma copia da Pilha:          " << endl;
        cout << "   9) Ordenar os itens da Pilha:         ";
        cout << "  10) Pesquisar a ocorrencia de um item: " << endl;
        cout << "  11) Qtd de ocorrencias de um item:     ";
        cout << "  12) Imprimir a Pilha:                  " << endl;
        cout << "  13) Alterar um item da pilha:          ";
        cout << "  14) Sair:                              " << endl;
        cout << "Escolha uma Opcao:" << endl;
        cin >> opcao;

        switch(opcao)
        {
            case 1:
                pilha1 = new TipoPilha;
                pilha2 = new TipoPilha;
                pilhaAux = new TipoPilha;
                iniciaPilhaVazia ( pilha1 );
                iniciaPilhaVazia ( pilha2 );
                iniciaPilhaVazia ( pilhaAux );
                cout << " --- Pilhas Inicializadas --- " << endl;
                break;
            case 2:
                cout << "Digite o valor do item a incluir: " << endl;
                cin >> valor;
                insereItem( valor, pilha1 );
                break;
            case 3:
                RetiraPrimeiroItem (pilha1, pilhaAux);
                cout << " --- Primeiro Item retirado --- " << endl;
                break;
            case 4:  //Retirar o i-ésimo item
                do {
                    cout << "Digite a posição, ou ZERO para retirar do fim: " << endl;
                    cin >> posicao;

                } while (posicao < 0);
                posicao = RetiraItem (pilha1, pilhaAux, posicao);
                if (posicao > 0)
                    cout << " --- Item: " << posicao << " retirado --- " << endl;
                else
                    cout << " --- Item não encontrado! --- " << endl;
                break;
            case 5:  //Localizar o i-ésimo item para examinar e/ou alterar o conteúdo de seus componentes
                do {
                    cout << "Digite a posição, ou ZERO para mostrar o ultimo: " << endl;
                    cin >> posicao;

                } while ( posicao < 0);
                posicao = ProcurarItem (pilha1, pilhaAux, posicao, valor);
                if (posicao > 0)
                    cout << " --- Item: " << posicao << " Valor: " << valor << " --- " << endl;
                else
                    cout << " --- Item não encontrado! --- " << endl;
                break;
            case 6:  //Combinar duas ou mais da estrutura em questão (lista, fila, pilha, árvore) em uma única estrutura
                tamanho = CombinarPilha (pilha1, pilha2, pilhaAux);
                if (tamanho > 0)
                    cout << " --- Itens adicionados na Pilha: " << tamanho << " --- " << endl;
                else
                    cout << " --- Erro na combinacao! --- "<< endl;
                break;
            case 7:  //Partir uma estrutura em duas ou mais
                //lista2 = new
                do {
                    cout<<"Digite a posição para dividir a lista: "<< endl;
                    cin >> posicao;

                } while (posicao < 0);
                tamanho = DividirPilha (pilha1, pilha2, pilhaAux, posicao);
                if (tamanho > 0)
                    cout << " --- Pilha nova criada com : " << tamanho << " itens --- " << endl;
                else
                    cout << " --- Erro ao dividir! --- " << endl;
                break;
            case 8:  //Fazer uma cópia
                tamanho = CopiarPilha (pilha1, pilha2, pilhaAux);
                if (tamanho > 0)
                    cout << " --- Pilha nova copiada com : " << tamanho << " itens --- " << endl;
                else
                    cout << " --- Erro ao dividir! --- "<< endl;
                break;
            case 9:  //Ordenar os itens da estrutura em ordem ascendente ou descendente, de acordo com alguns de seus componentes
                OrdenarPilha(pilha1, pilha2, pilhaAux);
                cout << " --- Pilha ordenada --- " << endl;
                break;
            case 10:  //Pesquisar a primeira ocorrência de um item com um valor particular
                cout << "Digite o valor a ser pesquisado: " << endl;
                cin >> valor;
                posicao = PesquisarItem (pilha1, pilhaAux, valor);
                if (posicao > 0)
                    cout << " --- Item encontrado na posicao: " << posicao << " Valor: " << valor << " --- " << endl;
                else
                    cout << " --- Item não encontrado! --- " << endl;
                break;
            case 11:  //Pesquisar a quantidade de ocorrências de um valor particular
                cout << "Digite o valor a ser pesquisado: " << endl;
                cin >> valor;
                ocorr = OcorrenciasItem (pilha1, pilhaAux, valor);
                if (ocorr > 0)
                    cout << " --- Encontrado na Pilha, ocorrencias: " << ocorr << " --- " << endl;
                else
                    cout << " --- Item não encontrado! --- "<< endl;
                break;
            case 12:  // Listar os itens da lista
                cout << " ===== Pilha1 ===== " << endl;
                ImprimePilha (pilha1, pilhaAux);
                cout << " ===== Pilha2 ===== " << endl;
                ImprimePilha (pilha2, pilhaAux);
                break;
            case 13:  //Alterar o conteudo de um item em particular
                cout << "Digite a posicao do item a ser alterado: " << endl;
                cin >> posicao;
                cout << "Digite o novo valor: " << endl;
                cin >> valor;
                posicao = AlterarItem (pilha1, pilhaAux, posicao, valor);
                if (posicao > 0)
                    cout << " --- Item alterado na Pilha na posicao: " << posicao << " --- " << endl;
                else
                    cout << " --- ERRO: Item não alterado! --- "<< endl;
                break;
        }
    } while (opcao != 14);
    return 0;
}