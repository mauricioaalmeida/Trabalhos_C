/******************************************************************************
MAURICIO ANDRE DE ALMEIDA - UniFEI Matricula 2021101420
Lista implementada por meio de estruturas auto-referenciadas

*******************************************************************************/

#include <iostream>
using namespace std;

struct Celula {
    int Valor;
    Celula *Proximo;
};
struct TipoLista {
    Celula *Primeiro;
    Celula *Ultimo;
};

//Criação da estrutura de dados vazia
void iniciaListaVazia( TipoLista* lista ) {

    Celula *prox;
    // Cria a cabeca vazia
    prox = new Celula;
    prox->Valor = 0;
    prox->Proximo = NULL;
    // Aponta a lista para a cabeca
    lista->Primeiro = prox;
    lista->Ultimo = prox;
}

//Inserir um novo item imediatamente após o i-ésimo item
void insereItem( int item, TipoLista *lista)
{
    Celula *ult, *prox;
    // Cria a nova celula como a ultima da lista
    prox = new Celula;
    prox->Valor = item;
    prox->Proximo = NULL;
    // Atualiza a ultima posicao da lista
    //cout << "---- ----" << lista->Ultimo << endl;
    ult = lista->Ultimo;
    ult->Proximo = prox;
    lista->Ultimo = prox;

}


//Retirar o primeiro item
void RetiraPrimeiroItem(TipoLista *lista)
{
    Celula *prox, *cabeca, *prim;
    cabeca = lista->Primeiro;
    if (cabeca->Proximo != NULL) {
        prim = cabeca->Proximo;
        prox = prim->Proximo;
        cabeca->Proximo = prox;
        // Verifica se e o ultimo e atualiza a lista
        if (prox == NULL) {
            lista->Ultimo = cabeca;
        }
        delete prim;
    }
}

//Retirar o i-ésimo item
int RetiraItem (TipoLista *lista, int posicao) {
    Celula *cel, *ant;
    cel = lista->Primeiro;
    int i = 0;
    // verifica se a lista esta vazia
    if (cel->Proximo == NULL) {
        cout << "---- LISTA VAZIA! ----" << endl;
        posicao = -1;
    } else {
        while (cel->Proximo != NULL) {
            i++;
            ant = cel;
            cel = cel->Proximo;
            if (i == posicao)
                break;
        }
        // Verifica se eh o ultimo e se eh pra apagar
        if (cel->Proximo == NULL && posicao == 0)
            posicao = i;

        // Verifica se eh o Ultimo
        if (posicao <= i) {
            if (cel->Proximo == NULL) {
                ant->Proximo = NULL;
                lista->Ultimo = ant;
                delete cel;
            } else {
                ant->Proximo = cel->Proximo;
                delete cel;
            }
        } else {
            posicao = -1; // maior do que o ultimo
        }

    }
    return posicao;
}

//Localizar o i-ésimo item para examinar e/ou alterar o conteúdo de seus componentes
int ProcurarItem (TipoLista *lista, int posicao) {
    Celula *cel, *ant;
    cel = lista->Primeiro;
    int i = 0;
    // verifica se a lista esta vazia
    if (cel->Proximo == NULL) {
        cout << "---- LISTA VAZIA! ----" << endl;
        posicao = -1;
    } else {
        while (cel->Proximo != NULL) {
            i++;
            ant = cel;
            cel = cel->Proximo;
            if (i == posicao)
                break;
        }
        // Verifica se eh o ultimo
        if (cel->Proximo == NULL && posicao == 0)
            posicao = i;

        // Verifica se eh maior que o Ultimo
        if (posicao > i) {
            posicao = -1; // maior do que o ultimo
        }

    }
    return posicao;
}

// Listar conteudo do item em determinada posicao
int ConteudoItem(TipoLista *lista, int posicao) {
    Celula *cel, *ant;
    cel = lista->Primeiro;
    int valor = -1;
    int i = 0;
    // verifica se a lista esta vazia
    if (cel->Proximo == NULL) {
        cout << "---- LISTA VAZIA! ----" << endl;
        posicao = -1;
    } else {
        while (cel->Proximo != NULL) {
            i++;
            ant = cel;
            cel = cel->Proximo;
            if (i == posicao)
                break;
        }
        // Verifica se eh o ultimo
        if (cel->Proximo == NULL && posicao == 0)
            posicao = i;

        // Verifica se eh maior que o Ultimo
        if (posicao > i) {
            valor = -1; // maior do que o ultimo
        } else
            valor = cel->Valor;

    }
    return valor;
}

//Combinar duas ou mais da estrutura em questão (lista, fila, pilha, árvore) em uma única estrutura
int CombinarLista (TipoLista *lista1, TipoLista *lista2) {
    int itens = 1;
    Celula *cel, *ant, *prox;
    cel = lista2->Primeiro;
    // verifica se a lista2 esta vazia
    prox = lista1->Ultimo;
    // verifica se a lista2 esta vazia
    if (cel->Proximo == NULL) {
        cout << "---- LISTA VAZIA! ----" << endl;
        itens = -1;
    } else {
        // ignora a cabeca
        cel = cel->Proximo;
        ant = cel;
        prox->Proximo = cel;
        // percorre a lista2 pra descobrir o ultimo
        while (cel->Proximo != NULL) {
            itens++;
            ant = cel;
            cel = cel->Proximo;
        }
        // Atualiza o ultimo
        lista1->Ultimo = ant;
        // limpa a lista2
        cel = lista2->Primeiro;
        cel->Proximo = NULL;
        lista2->Ultimo = cel;

    }
    return itens;
}

//Partir uma estrutura em duas
int DividirLista (TipoLista *lista1, TipoLista *lista2, int posicao) {
    int itens = 0;
    Celula *cel, *ant, *prox;
    cel = lista1->Primeiro;
    prox = lista2->Ultimo;
    // verifica se a lista1 esta vazia
    if (cel->Proximo == NULL) {
        cout << "---- LISTA VAZIA! ----" << endl;
    } else {
        // percorre a lista pra chegar no ponto
        while (cel->Proximo != NULL) {
            itens++;
            ant = cel;
            cel = cel->Proximo;
            if (itens == posicao) {
                // Encerra aqui a lista1
                ant->Proximo = NULL;
                lista1->Ultimo = ant;
                // Transfere o próximos para a lista2
                prox->Proximo = cel;
                // encontra o Ultimo
                itens = 1;
                while (cel->Proximo != NULL) {
                    itens++;
                    ant = cel;
                    cel = cel->Proximo;
                }
                // Atualiza o ultimo na lista 2
                lista2->Ultimo = ant;
                break;
            }
        }


    }
    return itens;
}

//Fazer uma cópia
int CopiarLista (TipoLista *lista1, TipoLista *lista2) {
    int itens = 0;
    // Copia os itens para a segunda lista
    Celula *prox, *cel, *aux;
    cel = lista1->Primeiro;
    prox = lista2->Ultimo;
    // verifica se a lista1 esta vazia
    if (cel->Proximo == NULL) {
        cout << "---- LISTA VAZIA! ----" << endl;
        itens = -1;
    } else {
        // percorre a lista duplicando o
        while (cel->Proximo != NULL) {
            itens++;
            cel = cel->Proximo;
            aux = new Celula;
            aux->Valor = cel->Valor;
            aux->Proximo = NULL;
            prox->Proximo = aux;
            prox = aux;
            lista2->Ultimo = aux;

        }
    }
    return itens;
}
//Ordenar os itens da estrutura em ordem ascendente ou descendente, de acordo com alguns de seus componentes

void OrdenarLista (TipoLista *lista) {
    int aux;
    Celula *celI, *celJ, *antJ, *antI;
    antI = lista->Primeiro;
    antJ = lista->Primeiro;
    celI = antI->Proximo;
    celJ = antJ->Proximo;
    while (celI->Proximo != NULL) {
        celI = antI->Proximo;
        antJ = lista->Primeiro;
        celJ = antJ->Proximo;
        while (celJ->Proximo != NULL) {

            celJ = antJ->Proximo;

            if (celI->Valor < celJ->Valor) {
                aux = celI->Valor;
                
                
                celI->Valor = celJ->Valor;
                
                celJ->Valor = aux;
            }
            antJ = celJ;
        }
        antI = celI;

    }

    /*
    for (int i = lista->Primeiro; i <= lista->Ultimo; i++) {
        for (int j = lista->Primeiro; j <= lista->Ultimo; j++) {
            if (lista->Item[i] < lista->Item[j]) {
                aux = lista->Item[i];
                lista->Item[i] = lista->Item[j];
                lista->Item[j] = aux;
            }
        }
    }*/
}

//Pesquisar a primeira ocorrência de um item com um valor particular
int PesquisarItem (TipoLista *lista, int pesq) {
    /*
    for (int i = lista->Primeiro; i <= lista->Ultimo; i++) {
        if (lista->Item[i] == pesq) {
            pos = i;
            break;
        }
    }
    */
    Celula *cel, *ant;
    cel = lista->Primeiro;
    int valor = -1;
    int i = 0;
    // verifica se a lista esta vazia
    if (cel->Proximo == NULL) {
        cout << "---- LISTA VAZIA! ----" << endl;
        i = -1;
    } else {
        while (cel->Proximo != NULL) {
            i++;
            ant = cel;
            cel = cel->Proximo;
            if (cel->Valor == pesq)
                break;
        }
        // Verifica se eh o ultimo e nao encontrou
        if (cel->Valor != pesq)
            i = -1; // maior do que o ultimo
    }
    return i;
}

//Pesquisar a quantidade de ocorrências de um valor particular
int OcorrenciasItem (TipoLista *lista, int pesq) {
    int ocorr = 0;
    /*  for (int i = lista->Primeiro; i <= lista->Ultimo; i++) {
          10        if (lista->Item[i] == pesq) {
              ocorr++;
          }
      }
   */
    Celula *cel, *ant;
    cel = lista->Primeiro;
    int valor = -1;
    int i = 0;
    // verifica se a lista esta vazia
    if (cel->Proximo == NULL) {
        cout << "---- LISTA VAZIA! ----" << endl;
        i = -1;
    } else {
        while (cel->Proximo != NULL) {
            i++;
            ant = cel;
            cel = cel->Proximo;
            if (cel->Valor == pesq)
                ocorr++;
        }

    }
    return ocorr;

}

// Listar os itens da lista
void ImprimeLista (TipoLista *lista) {

    Celula *cel;
    cel = lista->Primeiro;
    // verifica se a lista esta vazia
    if ( cel->Proximo == NULL ) {
        cout << "---- LISTA VAZIA! ----" << endl;
    } else {
        int i = 0;
        //cout << "LISTA: Primeiro: " << lista->Primeiro << "Ultimo: " << lista->Ultimo << endl;
        cout << "---- Inicio da Lista ----" << endl;
        while ( cel->Proximo != NULL) {
            i++;
            cel = cel->Proximo;
            cout << "Posicao: " << i << " = Valor: " << cel->Valor << endl;
        }
        cout << "---- Fim da Lista ----" << endl;
    }

}


int main() {
    TipoLista *lista1, *lista2;
    int opcao;
    int valor, posicao, tamanho, ocorr;
    do {
        cout << "  --------------------------------------------------------------------------------  " << endl;
        cout << "   1) Criar uma lista vazia:             ";
        cout << "   2) Inserir um novo item na lista:     " << endl;
        cout << "   3) Retirar o primeiro item:           ";
        cout << "   4) Retirar o i-esimo item:            " << endl;
        cout << "   5) Localizar o i-esimo item:          ";
        cout << "   6) Combinar duas listas:              " << endl;
        cout << "   7) Partir uma lista em duas:          ";
        cout << "   8) Fazer uma copia:                   " << endl;
        cout << "   9) Ordenar os itens da lista:         ";
        cout << "  10) Pesquisar a ocorrencia de um item: " << endl;
        cout << "  11) Qtd de ocorrencias de um item:     ";
        cout << "  12) Imprimir a lista:                  " << endl;
        cout << "  13) Sair:                              " << endl;
        cout << "Escolha uma Opcao:" << endl;
        cin >> opcao;

        switch(opcao)
        {
            case 1:
                lista1 = new TipoLista;
                lista2 = new TipoLista;
                iniciaListaVazia ( lista1 );
                iniciaListaVazia ( lista2 );
                cout << " --- Listas Inicializadas --- " << endl;
                break;
            case 2:
                cout << "Digite o valor do item a incluir: " << endl;
                cin >> valor;
                insereItem( valor, lista1 );
                break;
            case 3:
                RetiraPrimeiroItem (lista1);
                cout << " --- Primeiro Item retirado --- " << endl;
                break;
            case 4:  //Retirar o i-ésimo item
                do {
                    cout << "Digite a posição, ou ZERO para retirar do fim: " << endl;
                    cin >> posicao;

                } while (posicao < 0);
                posicao = RetiraItem (lista1, posicao);
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
                posicao = ProcurarItem (lista1, posicao);
                if (posicao > 0)
                    cout << " --- Item: " << posicao << " Valor: " << ConteudoItem(lista1, posicao) << " --- " << endl;
                else
                    cout << " --- Item não encontrado! --- " << endl;
                break;
            case 6:  //Combinar duas ou mais da estrutura em questão (lista, fila, pilha, árvore) em uma única estrutura
                tamanho = CombinarLista (lista1, lista2);
                if (tamanho > 0)
                    cout << " --- Itens adicionados na Lista: " << tamanho << " --- " << endl;
                else
                    cout << " --- Erro na combinacao! --- "<< endl;
                break;
            case 7:  //Partir uma estrutura em duas ou mais
                //lista2 = new
                do {
                    cout<<"Digite a posição para dividir a lista: "<< endl;
                    cin >> posicao;

                } while (posicao < 0);
                tamanho = DividirLista (lista1, lista2, posicao);
                if (tamanho > 0)
                    cout << " --- Lista nova criada com : " << tamanho << " itens --- " << endl;
                else
                    cout << " --- Erro ao dividir! --- " << endl;
                break;
            case 8:  //Fazer uma cópia
                tamanho = CopiarLista (lista1, lista2);
                if (tamanho > 0)
                    cout << " --- Lista nova copiada com : " << tamanho << " itens --- " << endl;
                else
                    cout << " --- Erro ao dividir! --- "<< endl;
                break;
            case 9:  //Ordenar os itens da estrutura em ordem ascendente ou descendente, de acordo com alguns de seus componentes
                OrdenarLista(lista1);
                cout << " --- Lista ordenada --- " << endl;
                break;
            case 10:  //Pesquisar a primeira ocorrência de um item com um valor particular
                cout << "Digite o valor a ser pesquisado: " << endl;
                cin >> valor;
                posicao = PesquisarItem (lista1, valor);
                if (posicao > 0)
                    cout << " --- Item encontrado na posicao: " << posicao << " Valor: " << ConteudoItem(lista1, posicao)  << " --- " << endl;
                else
                    cout << " --- Item não encontrado! --- " << endl;
                break;
            case 11:  //Pesquisar a quantidade de ocorrências de um valor particular
                cout << "Digite o valor a ser pesquisado: " << endl;
                cin >> valor;
                ocorr = OcorrenciasItem (lista1, valor);
                if (ocorr > 0)
                    cout << " --- Encontrado na lista, ocorrencias: " << ocorr << " --- " << endl;
                else
                    cout << " --- Item não encontrado! --- "<< endl;
                break;
            case 12:  // Listar os itens da lista
                cout << " ===== Lista1 ===== " << endl;
                ImprimeLista (lista1);
                cout << " ===== Lista2 ===== " << endl;
                ImprimeLista (lista2);
                break;
        }
    } while (opcao != 13);
    return 0;
}
