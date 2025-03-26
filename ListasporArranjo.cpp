/******************************************************************************
MAURICIO ANDRE DE ALMEIDA - UniFEI Matricula 2021101420
Listas por Arranjo

*******************************************************************************/

#include <iostream>
using namespace std;

const int InicioArranjo = 0;
const int TamMax = 1000;

struct TipoLista {
    int Item[TamMax];
    int Primeiro;
    int Ultimo;
};

//Criação da estrutura de dados vazia
void iniciaListaVazia( TipoLista *lista ) {
    lista->Item[InicioArranjo] = 0;
    lista->Primeiro = InicioArranjo+1;
    lista->Ultimo = InicioArranjo;
}

//Inserir um novo item imediatamente após o i-ésimo item
int insereItem( int item, TipoLista *lista)
{

    lista->Item[++lista->Ultimo] = item;
    return lista->Ultimo;
}

//Retirar o primeiro item
int RetiraPrimeiroItem(TipoLista *lista)
{
    for (int i = lista->Primeiro; i < lista->Ultimo; i++) {
        lista->Item[i] = lista->Item[i+1];
    }
    lista->Ultimo = lista->Ultimo -1;
    return lista->Ultimo;
}

//Retirar o i-ésimo item
int RetiraItem (TipoLista *lista, int pos) {
    if (pos <= lista->Ultimo) {
        for (int i = pos; i < lista->Ultimo; i++) {
            lista->Item[i] = lista->Item[i+1];
        }
        lista->Ultimo = lista->Ultimo -1;
    } else pos = -1;
    return pos;
}

//Localizar o i-ésimo item para examinar e/ou alterar o conteúdo de seus componentes
int ProcurarItem (TipoLista *lista, int pesq) {
    return lista->Item[pesq];
}

//Combinar duas ou mais da estrutura em questão (lista, fila, pilha, árvore) em uma única estrutura
int CombinarLista (TipoLista *lista1, TipoLista *lista2) {
    int itens = -1;
    int ult = lista1->Ultimo;
    for (int i = lista2->Primeiro; i <= lista2->Ultimo; i++) {
        if (ult < TamMax) {
            ult++;
            lista1->Ultimo = ult;
            lista1->Item[ult] = lista2->Item[i];
        } else {
            // Estouro do tamanho maximo
            itens = -1;
            break;
        }
    }
    return itens;
}

//Partir uma estrutura em duas
int DividirLista (TipoLista *lista1, TipoLista *lista2, int posicao) {
    int ult = InicioArranjo;
    // Copia os itens para a segunda lista
    for (int i = posicao; i <= lista1->Ultimo; i++) {
        ult++;
        lista2->Ultimo = ult;
        lista2->Item[ult] = lista1->Item[i];
        lista1->Item[i] = 0;
    }
    lista1->Ultimo = posicao-1;
    return ult;
}

//Fazer uma cópia
int CopiarLista (TipoLista *lista1, TipoLista *lista2) {
    int ult = InicioArranjo;
    // Copia os itens para a segunda lista
    for (int i = lista1->Primeiro; i <= lista1->Ultimo; i++) {
        ult++;
        lista2->Ultimo = ult;
        lista2->Item[ult] = lista1->Item[i];
    }
    return ult;
}
//Ordenar os itens da estrutura em ordem ascendente ou descendente, de acordo com alguns de seus componentes

void OrdenarLista (TipoLista *lista) {
    int aux = 0;
    for (int i = lista->Primeiro; i <= lista->Ultimo; i++) {
        for (int j = lista->Primeiro; j <= lista->Ultimo; j++) {
            if (lista->Item[i] < lista->Item[j]) {
                aux = lista->Item[i];
                lista->Item[i] = lista->Item[j];
                lista->Item[j] = aux;
            }
        }
    }
}

//Pesquisar a primeira ocorrência de um item com um valor particular
int PesquisarItem (TipoLista *lista, int pesq) {
    int pos = 0;
    for (int i = lista->Primeiro; i <= lista->Ultimo; i++) {
        if (lista->Item[i] == pesq) {
            pos = i;
            break;
        }
    }
    return pos;
}

//Pesquisar a quantidade de ocorrências de um valor particular
int OcorrenciasItem (TipoLista *lista, int pesq) {
    int ocorr = 0;
    for (int i = lista->Primeiro; i <= lista->Ultimo; i++) {
10        if (lista->Item[i] == pesq) {
            ocorr++;
        }
    }
    return ocorr;
}

// Listar os itens da lista
void ImprimeLista (TipoLista *lista) {

    if ( lista->Ultimo == 0 ) {
        cout << "---- LISTA VAZIA! ----" << endl;
    } else {
        cout << "LISTA: Primeiro: " << lista->Primeiro << "Ultimo: " << lista->Ultimo << endl;
        cout << "---- Inicio da Lista ----" << endl;
        for (int i = lista->Primeiro; i <= lista->Ultimo; i++) {
            cout << "Posicao: " << i << " = Valor: " << lista->Item[i] << endl;
        }
        cout << "---- Fim da Lista ----" << endl;
    }

}

int main() {
    TipoLista *lista, *lista2;
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
                lista = new TipoLista;
                lista2 = new TipoLista;
                iniciaListaVazia ( lista );
                iniciaListaVazia ( lista2 );
                cout << " --- Listas Inicializadas --- " << endl;
                break;
            case 2:

                cout << "Digite o valor do item a incluir: " << endl;
                cin >> valor;
                /*
                do {
                    cout<<"Digite a posição, ou ZERO para inserir no fim: "<< endl;
                    cin >> posicao;
                    if (posicao == 0) {
                        posicao = lista->Ultimo+1;
                        break;
                    }
                } while ( posicao < lista->Primeiro || posicao > lista->Ultimo+1);
                */
                posicao = insereItem( valor, lista);
                if (posicao > 0)
                    cout << "--- Item inserido: " << posicao << endl;
                else
                    cout << " --- Erro na inclusao do item! --- " << endl;
                break;
            case 3:
                RetiraPrimeiroItem (lista);
                cout << " --- Primeiro Item retirado --- " << endl;
                break;
            case 4:  //Retirar o i-ésimo item
                do {
                    cout << "Digite a posição, ou ZERO para retirar do fim: " << endl;
                    cin >> posicao;
                    if (posicao == 0) {
                        posicao = lista->Ultimo;
                        break;
                    }
                } while (posicao < lista->Primeiro || posicao > lista->Ultimo);
                posicao = RetiraItem (lista, posicao);
                if (posicao > 0)
                    cout << " --- Item: " << posicao << " retirado --- " << endl;
                else
                    cout << " --- Item não encontrado! --- " << endl;
                break;
            case 5:  //Localizar o i-ésimo item para examinar e/ou alterar o conteúdo de seus componentes
                do {
                    cout << "Digite a posição: " << endl;
                    cin >> posicao;
                    if (posicao == 0) {
                        posicao = lista->Ultimo;
                        break;
                    }
                } while ( posicao < lista->Primeiro || posicao > lista->Ultimo);
                posicao = ProcurarItem (lista, posicao);
                if (posicao > 0)
                    cout << " --- Item: " << posicao << " Valor: " << lista->Item[posicao] << " --- " << endl;
                else
                    cout << " --- Item não encontrado! --- " << endl;
                break;
            case 6:  //Combinar duas ou mais da estrutura em questão (lista, fila, pilha, árvore) em uma única estrutura
                tamanho = CombinarLista (lista, lista2);
                if (tamanho > 0)
                    cout << " --- Tamanho final da Lista: " << tamanho << " --- " << endl;
                else
                    cout << " --- Erro na combinacao! --- "<< endl;
                break;
            case 7:  //Partir uma estrutura em duas ou mais
                //lista2 = new
                do {
                    cout<<"Digite a posição para dividir a lista: "<< endl;
                    cin >> posicao;
                    if (posicao == 0) {
                        posicao = lista->Ultimo;
                        break;
                    }
                } while ( posicao < lista->Primeiro || posicao > lista->Ultimo+1);
                tamanho = DividirLista (lista, lista2, posicao);
                if (tamanho > 0)
                    cout << " --- Lista nova criada com : " << tamanho << " valores --- " << endl;
                else
                    cout << " --- Erro ao dividir! --- " << endl;
                break;
            case 8:  //Fazer uma cópia
                //lista2 = new
                tamanho = CopiarLista (lista, lista2);
                if (tamanho > 0)
                    cout << " --- Lista nova copiada com : " << tamanho << " valores --- " << endl;
                else
                    cout << " --- Erro ao dividir! --- "<< endl;
                break;
            case 9:  //Ordenar os itens da estrutura em ordem ascendente ou descendente, de acordo com alguns de seus componentes
                OrdenarLista(lista);
                cout << " --- Lista ordenada --- " << endl;
                break;
            case 10:  //Pesquisar a primeira ocorrência de um item com um valor particular
                cout << "Digite o valor a ser pesquisado: " << endl;
                cin >> valor;
                posicao = PesquisarItem (lista, valor);
                if (posicao > 0)
                    cout << " --- Item encontrado na posicao: " << posicao << " Valor: " << lista->Item[posicao] << " --- " << endl;
                else
                    cout << " --- Item não encontrado! --- " << endl;
                break;
            case 11:  //Pesquisar a quantidade de ocorrências de um valor particular
                cout << "Digite o valor a ser pesquisado: " << endl;
                cin >> valor;
                ocorr = OcorrenciasItem (lista, valor);
                if (ocorr > 0)
                    cout << " --- Encontrado na lista, ocorrencias: " << ocorr << " --- " << endl;
                else
                    cout << " --- Item não encontrado! --- "<< endl;
                break;
            case 12:  // Listar os itens da lista
                ImprimeLista (lista);
                break;
        }
    } while (opcao != 13);
    return 0;
}
