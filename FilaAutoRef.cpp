/******************************************************************************
MAURICIO ANDRE DE ALMEIDA - UniFEI Matricula 2021101420
Fila implementada por meio de estruturas auto-referenciadas

*******************************************************************************/

#include <iostream>
using namespace std;

const int TamMax = 1000;

struct Celula {
    int Valor;
    Celula *Proximo;
};
struct TipoFila {
    Celula *Inicio;
    Celula *Fim;
    int Tamanho;
};

// ----------- Funções basicas de Filas ---------------
// isEmpty - Fila esta vazia?
bool FilaIsEmpty ( TipoFila *Fila ) {
    if ( Fila->Inicio != NULL) 
       return false;
    else
       return true;
}

// isFull - Fila esta cheia?
bool FilaIsFull ( TipoFila *Fila ) {
    if (false) // Verificar estouro de memória????
       return true;
    else // Sempre falso!
       return false;
}
// PUSH - Enfileirar
bool FilaPush ( int item, TipoFila *fila ) {
    if (FilaIsFull(fila)) {
        return false;
    } else {
        Celula *ult, *prox;
        // Cria a nova celula como o fim da fila
        prox = new Celula;
        prox->Valor = item;
		prox->Proximo = NULL;
		// Consulta o fim Atual
        ult = fila->Fim;
		// Se nao for o primeiro da Fila, atualiza o ultimo
		if (ult != NULL)
           ult->Proximo = prox;
        else // Se for o primeiro, atualiza o apontador Inicio da fila
           fila->Inicio = prox;
        // Atualiza o fim anterior da fila
        fila->Fim = prox;
        fila->Tamanho++;
        return true;
    }
}
// POP - Desenfileirar
int FilaPop ( TipoFila *fila ) {
    Celula *inicio, *prox;
    int item;
    // Consulta o topo Atual
    inicio = fila->Inicio;
    // Copia o item
    item = inicio->Valor;
    prox = inicio->Proximo;
    // verifica se eh o fim da fila
    if (prox == NULL)
       fila->Fim = NULL;
    // Retira o topo da fila
    delete inicio;
    // Atualiza o topo da fila
    fila->Inicio = prox; 
    fila->Tamanho--;
    return item;
}
// TOP - consultar item do inicio
int FilaTop ( TipoFila *fila ) {
    Celula *inicio;
    int item;
    // Consulta o inicio Atual
    inicio = fila->Inicio;
    // Copia o item
    item = inicio->Valor;
    return item;
}
// Esvazia fila
void FilaEmpty ( TipoFila *fila ) {
    if (!FilaIsEmpty( fila )) {
        while (fila->Inicio != NULL) {
            FilaPop (fila);
        }
    }
    
}
// ----------- demais Funcoes 
//Criação da estrutura de dados vazia
void iniciaFilaVazia( TipoFila *fila ) {

    fila = new TipoFila;
    fila->Inicio = NULL;
    fila->Fim = NULL;
    fila->Tamanho= 0;
}

//Inserir um novo item na fila
bool insereItem( int item, TipoFila *fila)
{
  return FilaPush ( item, fila );
}


//Retirar o primeiro item
bool RetiraPrimeiroItem(TipoFila *fila, TipoFila *filaAux)
{
    if (FilaIsEmpty(fila))
      return false;
    else 
	{
	  FilaPop(fila);
      return true;
	}
}

//Retirar o i-ésimo item
int RetiraItem (TipoFila *fila, TipoFila *filaAux, int posicao) {
    if (FilaIsEmpty(fila))
      return -1;
    else {
        int cont = 0;
        // esvazia a auxiliar
        int aux;
        FilaEmpty (filaAux);
        while ( !FilaIsEmpty(fila) ) {
            // Move os itens para a fila auxiliar
            cont++;
            aux = FilaPop(fila);
            // Pula a posicao
            if (posicao != cont) 
               FilaPush( aux, filaAux);
        }
        // retorna os itens para a fila original
        while ( !FilaIsEmpty(filaAux) ) {
            aux = FilaPop(filaAux);
            FilaPush( aux, fila);
        } 
    }
    return posicao;
}

//Localizar o i-ésimo item para examinar e/ou alterar o conteúdo de seus componentes
int ProcurarItem (TipoFila *fila, TipoFila *filaAux, int posicao, int &item) {
    int res = -1;   
    if (FilaIsEmpty(fila))
      return -1;
    else {
        int cont = 0;
        int aux;
        // esvazia a auxiliar
        FilaEmpty (filaAux);
        while ( !FilaIsEmpty(fila) ) {
            // Move os itens para a fila auxiliar 
            cont++;
            aux = FilaPop(fila);
            FilaPush( aux, filaAux);
            // Grava a posicao
            if (posicao == cont) {
                res = cont;
                item = aux;
            }
        }
        // retorna os itens para a fila original
        while ( !FilaIsEmpty(filaAux) ) {
            aux = FilaPop(filaAux);
            FilaPush( aux, fila);
        } 
    }
    return res;
}

//Altera o i-ésimo item 
int AlterarItem (TipoFila *fila, TipoFila *filaAux, int posicao, int item) {
    int res = -1;
    if (FilaIsEmpty(fila))
      return res;
    else {
        int cont = 0;
        int aux;        
        // esvazia a auxiliar
        FilaEmpty (filaAux);
        while ( !FilaIsEmpty(fila) ) {
            // Move os itens para a fila auxiliar 
            cont++;
            aux = FilaPop(fila);
            // Altera o item da posicao escolhida
            if (posicao == cont) {
                FilaPush( item, filaAux);
                res = cont;
            } else
              FilaPush( aux, filaAux); 
        }
        // retorna os itens para a fila original
        while ( !FilaIsEmpty(filaAux) ) {
            aux = FilaPop(filaAux);
            FilaPush( aux, fila);
        } 
    }
    return res;
}

//Combinar duas filas em uma única estrutura
int CombinarFila (TipoFila *fila1, TipoFila *fila2, TipoFila *filaAux) {
    int cont = 0;
    if (FilaIsEmpty(fila1) || FilaIsEmpty(fila2))
      return -1;
    else {
        int aux;
        // esvazia a auxiliar
        FilaEmpty (filaAux);
        // Move os itens da fila1 para a auxiliar
        while ( !FilaIsEmpty(fila1) ) {
            // Move os itens para a fila auxiliar 
            cont++;
            aux = FilaPop(fila1);
            FilaPush( aux, filaAux); 
        }
        while ( !FilaIsEmpty(fila2) ) {
            // Move os itens para a fila auxiliar 
            cont++;
            aux = FilaPop(fila2);
            FilaPush( aux, filaAux); 
        }
        // retorna os itens para a fila original
        while ( !FilaIsEmpty(filaAux) ) {
            aux = FilaPop(filaAux);
            FilaPush( aux, fila1);
        } 
    }
    return cont;
}

//Partir uma estrutura em duas
int DividirFila (TipoFila *fila1, TipoFila *fila2, int posicao) {
    int cont = 0;
    if (FilaIsEmpty(fila1))
      return -1;
    else {
        // esvazia a auxiliar e a fila2
        FilaEmpty (fila2);
        int aux;
        // Move os itens da fila1 para a fila2 até chegar na posicao
        while ( !FilaIsEmpty(fila1) ) {
            // Move os itens para a fila2 
            cont++;
            aux = FilaPop(fila1);
            FilaPush( aux, fila2); 
            if (cont == posicao) {
                break;
            }
        }
    }
    return cont;
}

//Fazer uma cópia
int CopiarFila (TipoFila *fila1, TipoFila *fila2, TipoFila *filaAux) {
    int cont = 0;
    if (FilaIsEmpty(fila1))
      return -1;
    else {
        // esvazia a auxiliar e a fila2
        FilaEmpty (filaAux);
        FilaEmpty (fila2);
        int aux;
        // Move os itens para a fila auxiliar 
        while ( !FilaIsEmpty(fila1) ) {
            // Move os itens para a fila auxiliar 
            cont++;
            aux = FilaPop(fila1);
            FilaPush( aux, filaAux); 
        }
        while ( !FilaIsEmpty(filaAux) ) {
            // Move os itens da fila auxiliar para a fila1 e fila2 
            cont++;
            aux = FilaPop(filaAux);
            FilaPush( aux, fila1); 
            FilaPush( aux, fila2); 
        }
    }
    return cont;
}

//Ordenar os itens da estrutura em ordem ascendente ou descendente, de acordo com alguns de seus componentes
void OrdenarFila (TipoFila *fila1, TipoFila *fila2, TipoFila *filaAux) {
    int menor;
    // Move todos os itens para a fila auxiliar, encontrando o menor e retirando-o para a fila2 ao retornar
    if (!FilaIsEmpty(fila1)) {
        // esvazia a auxiliar e a fila2
        FilaEmpty (filaAux);
        FilaEmpty (fila2);
        int aux;
        // loop de ordenacao (soh termina qdo a fila1 e aux estiverem vazias)
        do {
            // pega o primeiro item para iniciar
            aux = FilaTop(fila1);
            menor = aux;
            // Move os itens da fila1 para a auxiliar encontrando o menor deles
            while ( !FilaIsEmpty(fila1) ) {
                aux = FilaPop(fila1);
                if (aux < menor) 
                    menor = aux;
                FilaPush( aux, filaAux); 
            }    
            // Move de volta para a fila1 retirando o(s) menor(es) para a fila2
            while ( !FilaIsEmpty(filaAux) ) {
                aux = FilaPop(filaAux);
                if (aux == menor)
                    FilaPush( aux, fila2);
                else
                    FilaPush( aux, fila1); 
            }    
        } while (!(FilaIsEmpty(fila1) && FilaIsEmpty(filaAux)));
        // Retorna os itens para a fila1, para manter a ordem crescente
        while ( !FilaIsEmpty(fila2) ) {
            aux = FilaPop(fila2);
            FilaPush( aux, fila1); 
        }
    }
}

//Pesquisar a primeira ocorrência de um item com um valor particular
int PesquisarItem (TipoFila *fila, TipoFila *filaAux, int pesq) {
    int res = -1;   
    if (FilaIsEmpty(fila))
      return -1;
    else {
        int cont = 0;
        int aux;
        // esvazia a auxiliar
        FilaEmpty (filaAux);
        while ( !FilaIsEmpty(fila) ) {
            // Move os itens para a fila auxiliar pesquisando
            cont++;
            aux = FilaPop(fila);
            FilaPush( aux, filaAux);
            // Grava a posicao
            if (aux == pesq && res < 0) {
                res = cont;
            }
        }
        // retorna os itens para a fila original
        while ( !FilaIsEmpty(filaAux) ) {
            aux = FilaPop(filaAux);
            FilaPush( aux, fila);
        } 
    }
    return res;
}

//Pesquisar a quantidade de ocorrências de um valor particular
int OcorrenciasItem (TipoFila *fila, TipoFila *filaAux, int pesq) {
    int ocorr = -1;   
    if (FilaIsEmpty(fila))
      return -1;
    else {
        int cont = 0;
        ocorr = 0;
        int aux;
        // esvazia a auxiliar
        FilaEmpty (filaAux);
        while ( !FilaIsEmpty(fila) ) {
            // Move os itens para a fila auxiliar pesquisando
            cont++;
            aux = FilaPop(fila);
            FilaPush( aux, filaAux);
            // incrementa a ocorrencia
            if (aux == pesq) {
                ocorr++;
            }
        }
        // retorna os itens para a fila original
        while ( !FilaIsEmpty(filaAux) ) {
            aux = FilaPop(filaAux);
            FilaPush( aux, fila);
        } 
    }
    return ocorr;
}

// Listar os itens da fila
void ImprimeFila (TipoFila *fila, TipoFila *filaAux) {
    int aux;
    if (FilaIsEmpty(fila)) {
       cout << "---- LISTA VAZIA! ----" << endl;
    } else {
        int cont = 0;
        cout << "---- Inicio da Lista ----" << endl;
        // esvazia a auxiliar
        FilaEmpty (filaAux);
        while ( !FilaIsEmpty(fila) ) {
            // Move os itens para a fila auxiliar e imprimindo
            cont++;
            aux = FilaPop(fila);
            cout << "Posicao: " << cont << " = Valor: " << aux << endl;
            FilaPush( aux, filaAux);
            
            }
        cout << "---- Fim da Lista ----" << endl;
        // retorna os itens para a fila original
        while ( !FilaIsEmpty(filaAux) ) {
            aux = FilaPop(filaAux);
            FilaPush( aux, fila);
        } 
    }
}

int main() {
    TipoFila *fila1, *fila2, *filaAux;
    int opcao;
    int valor, posicao, tamanho, ocorr;
    do {
        cout << "  --------------------------------------------------------------------------------  " << endl;
        cout << "   1) Criar uma Fila vazia:             ";
        cout << "   2) Inserir um novo item na Fila:     " << endl;
        cout << "   3) Retirar o primeiro item:           ";
        cout << "   4) Retirar o i-esimo item:            " << endl;
        cout << "   5) Localizar o i-esimo item:          ";
        cout << "   6) Combinar duas Filas:              " << endl;
        cout << "   7) Partir uma Fila em duas:          ";
        cout << "   8) Fazer uma copia da Fila:          " << endl;
        cout << "   9) Ordenar os itens da Fila:         ";
        cout << "  10) Pesquisar a ocorrencia de um item: " << endl;
        cout << "  11) Qtd de ocorrencias de um item:     ";
        cout << "  12) Imprimir a Fila:                  " << endl;
        cout << "  13) Alterar um item da fila:          ";
        cout << "  14) Sair:                              " << endl;
        cout << "Escolha uma Opcao:" << endl;
        cin >> opcao;

        switch(opcao)
        {
            case 1:
                fila1 = new TipoFila;
                fila2 = new TipoFila;
                filaAux = new TipoFila;
                iniciaFilaVazia ( fila1 );
                iniciaFilaVazia ( fila2 );
                iniciaFilaVazia ( filaAux );
                cout << " --- Filas Inicializadas --- " << endl;
                break;
            case 2:
                cout << "Digite o valor do item a incluir: " << endl;
                cin >> valor;
                insereItem( valor, fila1 );
                break;
            case 3:
                RetiraPrimeiroItem (fila1, filaAux);
                cout << " --- Primeiro Item retirado --- " << endl;
                break;
            case 4:  //Retirar o i-ésimo item
                do {
                    cout << "Digite a posição, ou ZERO para retirar do fim: " << endl;
                    cin >> posicao;

                } while (posicao < 0);
                posicao = RetiraItem (fila1, filaAux, posicao);
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
                posicao = ProcurarItem (fila1, filaAux, posicao, valor);
                if (posicao > 0)
                    cout << " --- Item: " << posicao << " Valor: " << valor << " --- " << endl;
                else
                    cout << " --- Item não encontrado! --- " << endl;
                break;
            case 6:  //Combinar duas ou mais da estrutura em questão (lista, fila, fila, árvore) em uma única estrutura
                tamanho = CombinarFila (fila1, fila2, filaAux);
                if (tamanho > 0)
                    cout << " --- Itens adicionados na Fila: " << tamanho << " --- " << endl;
                else
                    cout << " --- Erro na combinacao! --- "<< endl;
                break;
            case 7:  //Partir uma estrutura em duas ou mais
                //lista2 = new
                do {
                    cout<<"Digite a posição para dividir a lista: "<< endl;
                    cin >> posicao;

                } while (posicao < 0);
                tamanho = DividirFila (fila1, fila2, posicao);
                if (tamanho > 0)
                    cout << " --- Fila nova criada com : " << tamanho << " itens --- " << endl;
                else
                    cout << " --- Erro ao dividir! --- " << endl;
                break;
            case 8:  //Fazer uma cópia
                tamanho = CopiarFila (fila1, fila2, filaAux);
                if (tamanho > 0)
                    cout << " --- Fila nova copiada com : " << tamanho << " itens --- " << endl;
                else
                    cout << " --- Erro ao dividir! --- "<< endl;
                break;
            case 9:  //Ordenar os itens da estrutura em ordem ascendente ou descendente, de acordo com alguns de seus componentes
                OrdenarFila(fila1, fila2, filaAux);
                cout << " --- Fila ordenada --- " << endl;
                break;
            case 10:  //Pesquisar a primeira ocorrência de um item com um valor particular
                cout << "Digite o valor a ser pesquisado: " << endl;
                cin >> valor;
                posicao = PesquisarItem (fila1, filaAux, valor);
                if (posicao > 0)
                    cout << " --- Item encontrado na posicao: " << posicao << " Valor: " << valor << " --- " << endl;
                else
                    cout << " --- Item não encontrado! --- " << endl;
                break;
            case 11:  //Pesquisar a quantidade de ocorrências de um valor particular
                cout << "Digite o valor a ser pesquisado: " << endl;
                cin >> valor;
                ocorr = OcorrenciasItem (fila1, filaAux, valor);
                if (ocorr > 0)
                    cout << " --- Encontrado na Fila, ocorrencias: " << ocorr << " --- " << endl;
                else
                    cout << " --- Item não encontrado! --- "<< endl;
                break;
            case 12:  // Listar os itens da lista
                cout << " ===== Fila1 ===== " << endl;
                ImprimeFila (fila1, filaAux);
                cout << " ===== Fila2 ===== " << endl;
                ImprimeFila (fila2, filaAux);
                break;
            case 13:  //Alterar o conteudo de um item em particular
                cout << "Digite a posicao do item a ser alterado: " << endl;
                cin >> posicao;
                cout << "Digite o novo valor: " << endl;
                cin >> valor;
                posicao = AlterarItem (fila1, filaAux, posicao, valor);
                if (posicao > 0)
                    cout << " --- Item alterado na Fila na posicao: " << posicao << " --- " << endl;
                else
                    cout << " --- ERRO: Item não alterado! --- "<< endl;
                break;
        }
    } while (opcao != 14);
    return 0;
}