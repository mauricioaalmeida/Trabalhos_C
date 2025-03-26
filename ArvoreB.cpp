/******************************************************************************
MAURICIO ANDRE DE ALMEIDA - UniFEI Matricula 2021101420
Arvore B

Criação de uma nova
Busca se o item está ou não presente, qual o pai e quais os filhos do mesmo
Inserção
Remoção
Impressão da árvore

*******************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

#define m 2 
#define mm (m * 2)


typedef long TipoChave;

typedef struct Registro {
    TipoChave Chave;
    // Outros componentes
    
} Registro;

typedef struct Pagina* Apontador;

typedef struct Pagina{
    short n; //0..mm
    Registro r[mm]; //1..mm
    Apontador p[mm + 1]; // 0..mm
} Pagina;

void Inicializa (Apontador* Dicionario){
    *Dicionario = NULL;
}
 
void Pesquisa(Registro *x, Apontador Ap){ 
  long i = 1;
  if (Ap == NULL) 
  { printf("Registro nao esta presente na arvore\n");
    return;
  }
  while (i < Ap->n && x->Chave > Ap->r[i-1].Chave) i++;
  if (x->Chave == Ap->r[i-1].Chave) 
    { *x = Ap->r[i-1];
      return;
    }
  if (x->Chave < Ap->r[i-1].Chave)
    Pesquisa(x, Ap->p[i-1]);
  else
    Pesquisa(x, Ap->p[i]);
} 

void PesquisaCompleta(Registro *x, Apontador Ap, Registro Pai){ 
  long i = 1;
  if (Ap == NULL) 
  { printf(" => Registro nao esta presente na arvore\n");
    return;
  }
  while (i < Ap->n && x->Chave > Ap->r[i-1].Chave) i++;
  if (x->Chave == Ap->r[i-1].Chave) 
    { *x = Ap->r[i-1];
    // Achou
      printf(" => Registro encontrado na arvore\n");
      printf("    Nivel: %ld \n",i);
      if (Pai.Chave != Ap->r[i-1].Chave)
          printf("    Pai: %ld \n",Pai.Chave);
      else
          printf("    Pai = Raiz!\n");
      if (Ap->p[i-1] != NULL){
          printf("    Filhos: ");
          int nnn = Ap->p[i-1]->n;
          //printf("N-filhos %d \n",nnn);
          for (int j = 0; j < nnn ; j++) 
             printf("%ld ", Ap->p[i-1]->r[j].Chave);
          printf("\n");
      } else
        printf("    Nao tem filhos!\n");
      return;
    }
  if (x->Chave < Ap->r[i-1].Chave){
    Pai = Ap->r[i-1];
    PesquisaCompleta(x, Ap->p[i-1], Pai);
  } else {
    Pai = Ap->r[i-1]; 
    PesquisaCompleta(x, Ap->p[i], Pai);
  }
} 

 
void ImprimeI(Apontador p, int nivel)

{ long i;

  if (p == NULL)
  return;
  printf("Nivel %d : ", nivel);
  for (i = 0; i < p->n; i++)
    printf("%ld ",(long)p->r[i].Chave);
  putchar('\n');
  nivel++;
  for (i = 0; i <= p->n; i++)
    ImprimeI(p->p[i], nivel);
} 

void Imprime(Apontador p)

{ int  n = 0;
  ImprimeI(p, n);
} 

void InsereNaPagina(Apontador Ap, Registro Reg, Apontador ApDir)
{ short NaoAchouPosicao;
  int k;
  k = Ap->n;
  NaoAchouPosicao = (k > 0);
  while (NaoAchouPosicao) 
    { if (Reg.Chave >= Ap->r[k-1].Chave) 
      { NaoAchouPosicao = false;
        break;
      }
      Ap->r[k] = Ap->r[k-1];
      Ap->p[k+1] = Ap->p[k];
      k--;
      if (k < 1)  NaoAchouPosicao = false;
    }
  Ap->r[k] = Reg;
  Ap->p[k+1] = ApDir;
  Ap->n++;
} 

void Ins(Registro Reg, Apontador Ap, short *Cresceu, 
	 Registro *RegRetorno,  Apontador *ApRetorno)
{ long i = 1;
  long j;
  Apontador ApTemp;
  if (Ap == NULL) 
  { *Cresceu = true; (*RegRetorno) = Reg; (*ApRetorno) = NULL;
    return;
  }
  while (i < Ap->n && Reg.Chave > Ap->r[i-1].Chave)  i++;
  if (Reg.Chave == Ap->r[i-1].Chave) 
  { printf(" Erro: Registro ja esta presente\n"); *Cresceu = false;
    return;
  }
  if (Reg.Chave < Ap->r[i-1].Chave)
  i--;
  Ins(Reg, Ap->p[i], Cresceu, RegRetorno, ApRetorno);
  if (!*Cresceu)
  return;
  if (Ap->n < mm)   /* Pagina tem espaco */
    { InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
      *Cresceu = false;
      return;
    }
  /* Overflow: Pagina tem que ser dividida */
  ApTemp = (Apontador)malloc(sizeof(Pagina));
  ApTemp->n = 0;  ApTemp->p[0] = NULL;
  if (i < m+1) 
    { InsereNaPagina(ApTemp, Ap->r[mm-1], Ap->p[mm]);
      Ap->n--;
      InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    } 
  else
    InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
  for (j = m + 2; j <= mm; j++)
    InsereNaPagina(ApTemp, Ap->r[j-1], Ap->p[j]);
  Ap->n = m;  ApTemp->p[0] = Ap->p[m+1];
  *RegRetorno = Ap->r[m];
  *ApRetorno = ApTemp;
}

void Insere(Registro Reg, Apontador *Ap)

{ short Cresceu;
  Registro RegRetorno;
  Pagina *ApRetorno, *ApTemp;

  Ins(Reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);
  if (Cresceu)  /* Arvore cresce na altura pela raiz */
  { ApTemp = (Pagina *)malloc(sizeof(Pagina));
    ApTemp->n = 1;
    ApTemp->r[0] = RegRetorno;
    ApTemp->p[1] = ApRetorno;
    ApTemp->p[0] = *Ap;
    *Ap = ApTemp;
  }
}


void Reconstitui(Apontador ApPag, Apontador ApPai, int PosPai, short *Diminuiu)

{ Pagina *Aux;
  long DispAux, j;
  if (PosPai < ApPai->n)   /* Aux = Pagina a direita de ApPag */
  { Aux = ApPai->p[PosPai+1];
    DispAux = (Aux->n - m + 1) / 2;
    ApPag->r[ApPag->n] = ApPai->r[PosPai];
    ApPag->p[ApPag->n + 1] = Aux->p[0];
    ApPag->n++;
    if (DispAux > 0)  /* Existe folga: transfere de Aux para ApPag */
    { for (j = 1; j < DispAux; j++)
        InsereNaPagina(ApPag, Aux->r[j-1], Aux->p[j]);
      ApPai->r[PosPai] = Aux->r[DispAux-1];
      Aux->n -= DispAux;
      for (j = 0; j < Aux->n; j++)  Aux->r[j]   = Aux->r[j + DispAux];
      for (j = 0; j <= Aux->n; j++)	Aux->p[j] = Aux->p[j + DispAux];
      *Diminuiu = false;
    }
    else
      { /* Fusao: intercala Aux em ApPag e libera Aux */
        for (j = 1; j <= m; j++)
	  InsereNaPagina(ApPag, Aux->r[j-1], Aux->p[j]);
	free(Aux);
        for (j = PosPai + 1; j < ApPai->n; j++) 
	  { ApPai->r[j-1] = ApPai->r[j]; ApPai->p[j] = ApPai->p[j+1]; }
	ApPai->n--;
	if (ApPai->n >= m)
	*Diminuiu = false;
      }
  }
  else
    { /* Aux = Pagina a esquerda de ApPag */
      Aux = ApPai->p[PosPai-1];
      DispAux = (Aux->n - m + 1) / 2;
      for (j = ApPag->n; j >= 1; j--) ApPag->r[j] = ApPag->r[j-1];
      ApPag->r[0] = ApPai->r[PosPai-1];
      for (j = ApPag->n; j >= 0; j--) ApPag->p[j+1] = ApPag->p[j];
      ApPag->n++;
      if (DispAux > 0)   /* Existe folga: transfere de Aux para ApPag */
	{ for (j = 1; j < DispAux; j++)
	    InsereNaPagina(ApPag, Aux->r[Aux->n - j], Aux->p[Aux->n - j + 1]);
	  ApPag->p[0] = Aux->p[Aux->n - DispAux + 1];
	  ApPai->r[PosPai-1] = Aux->r[Aux->n - DispAux];
	  Aux->n -= DispAux;
	  *Diminuiu = false;
	}
      else
	{ /* Fusao: intercala ApPag em Aux e libera ApPag */
	  for (j = 1; j <= m; j++)
	    InsereNaPagina(Aux, ApPag->r[j-1], ApPag->p[j]);
          free(ApPag);
	  ApPai->n--;
	  if (ApPai->n >= m)  *Diminuiu = false;
    
	}
    }
}

void Antecessor(Apontador Ap, int Ind, Apontador ApPai, short *Diminuiu)
{ if (ApPai->p[ApPai->n] != NULL) 
  { Antecessor(Ap, Ind, ApPai->p[ApPai->n], Diminuiu);
    if (*Diminuiu)
      Reconstitui(ApPai->p[ApPai->n], ApPai, (long)ApPai->n, Diminuiu);
    return;
  }
  Ap->r[Ind-1] = ApPai->r[ApPai->n - 1]; ApPai->n--; *Diminuiu = (ApPai->n < m);
} 

void Ret(TipoChave Ch, Apontador *Ap, short *Diminuiu)

{ long j, Ind = 1;
  Apontador Pag;
  if (*Ap == NULL) 
    { printf("Erro: registro nao esta na arvore\n"); *Diminuiu = false;
      return;
    }
  Pag = *Ap;
  while (Ind < Pag->n && Ch > Pag->r[Ind-1].Chave) Ind++;
  if (Ch == Pag->r[Ind-1].Chave) 
  { if (Pag->p[Ind-1] == NULL)   /* Pagina folha */
    { Pag->n--;
      *Diminuiu = (Pag->n < m);
      for (j = Ind; j <= Pag->n; j++) 
        { Pag->r[j-1] = Pag->r[j];	Pag->p[j] = Pag->p[j+1]; }
      return;
    }
    /* Pagina nao e folha: trocar com antecessor */
    Antecessor(*Ap, Ind, Pag->p[Ind-1], Diminuiu);
    if (*Diminuiu)
      Reconstitui(Pag->p[Ind-1], *Ap, Ind - 1, Diminuiu);
    return;
  }
  if (Ch > Pag->r[Ind-1].Chave) Ind++;
  Ret(Ch, &Pag->p[Ind-1], Diminuiu);
  if (*Diminuiu)
  Reconstitui(Pag->p[Ind-1], *Ap, Ind - 1, Diminuiu);
}  

void Retira(TipoChave Ch, Apontador *Ap)

{ short Diminuiu;
  Apontador Aux;
  Ret(Ch, Ap, &Diminuiu);
  if (Diminuiu && (*Ap)->n == 0)  /* Arvore diminui na altura */
  { Aux = *Ap;   *Ap = Aux->p[0]; free(Aux);}
}  
 


int main() {
    
    Pagina *Dic;
    Registro R;                
    
    int opcao;
    int valor, posicao, tamanho, ocorr;
    do {
        cout << "  --------------------------------------------------------------------------------  " << endl;
        cout << "   1) Iniciar Arvore B Vazia:             ";
        cout << "   2) Inserir um novo item na Arvore:     " << endl;
        cout << "   3) Encontrar elemento na Arvore:       ";
        cout << "   4) Retirar um item da Arvore:          " << endl;

        cout << "   8) Criar Arvore e executar exemplos:   ";
        cout << "   9) Impressao ordenada da Arvore:       " << endl; 
        cout << "   0) Sair:                               " << endl;
        cout << "   Escolha uma Opcao:  (Para Executar exemplos use opcao 8)";
        cin >> opcao;

        switch(opcao)
        {
            case 1:

                Inicializa(&Dic);

                cout << " --- Arvore Inicializada --- " << endl;
                break;
            case 2:
                cout << "Digite o valor do item a incluir: " << endl;
                cin >> valor;

                R.Chave = valor;
                Insere(R, &Dic);
                break;
            case 3:
                cout << "Digite o valor do item a buscar: " << endl;
                cin >> valor;
                R.Chave = valor; 
                PesquisaCompleta(&R, Dic, R);
                if (R.Chave == valor)
                   cout << "-> Registro Encontrado! " << endl;
                break;
                
            case 4:
                cout << "Digite o valor do item a retirar: " << endl;
                cin >> valor;
                R.Chave = valor; 
                Retira(valor, &Dic);
                break;
          
            case 8:
                Inicializa(&Dic);
                cout << " --- Arvore Inicializada --- " << endl;

                cout << " -> Inserindo valores: ";
                valor = 50; cout << valor << ", "; R.Chave = valor; Insere(R, &Dic);
                valor = 25; cout << valor << ", "; R.Chave = valor; Insere(R, &Dic);
                valor = 75; cout << valor << ", "; R.Chave = valor; Insere(R, &Dic);
                valor = 15; cout << valor << ", "; R.Chave = valor; Insere(R, &Dic);
                valor =  5; cout << valor << ", "; R.Chave = valor; Insere(R, &Dic);
                valor = 90; cout << valor << ", "; R.Chave = valor; Insere(R, &Dic);
                valor = 80; cout << valor << ", "; R.Chave = valor; Insere(R, &Dic);
                valor = 30; cout << valor << ", "; R.Chave = valor; Insere(R, &Dic);
                valor = 10; cout << valor << ", "; R.Chave = valor; Insere(R, &Dic);
                valor = 60; cout << valor << ", "; R.Chave = valor; Insere(R, &Dic);
                cout << endl;
                cout << " -> Tentando Inserir um valor duplicado: ";
                // Insere um item duplicado!
                valor = 10; cout << valor << ", "; R.Chave = valor; Insere(R, &Dic);
                cout << endl;
                // Imprime
                cout << " --- Arvore --- " << endl;
                Imprime (Dic);
                cout << endl;
                cout << " -------------- " << endl;
                
                // Tenta retirar um item que não existe
                cout << "-> Tenta retirar um item que não existe" << endl;
                cout << "   -> Retirando o valor: 20" << endl;
                valor = 20; 
                R.Chave = valor; 
                Retira(R.Chave, &Dic);
                
                // Tenta retirar um item que existe    
                cout << "-> Retirando o valor: 25" << endl;
                valor = 25; 
                R.Chave = valor; 
                Retira(valor, &Dic);
                
                // Imprime
                cout << " --- Arvore --- " << endl;
                Imprime (Dic);
                cout << endl;
                cout << " -------------- " << endl;
                
                // Tenta encontrar um item que não existe
                cout << "-> Tenta encontrar um item que não existe" << endl;
                cout << "   -> Encontrar o valor: 20" << endl;
                valor = 20; 
                R.Chave = valor; 
                PesquisaCompleta(&R, Dic, R);
                
                cout << "-> Encontrar valor: 75 " << endl;    
                valor = 75;
                R.Chave = valor; 
                PesquisaCompleta(&R, Dic, R);
                
                cout << "-> Encontrar valor: 30 " << endl;    
                valor = 30;
                R.Chave = valor; 
                PesquisaCompleta(&R, Dic, R);
                
                cout << " --- Arvore --- " << endl;
                Imprime (Dic);
                cout << endl;
                cout << " -------------- " << endl;
                break;
            case 9:
       
                    
                cout << " --- Arvore --- " << endl;
                Imprime (Dic);
                cout << endl;
                cout << " -------------- " << endl;
                break;
        }
    } while (opcao != 0);
    
    

    return 0;
}

