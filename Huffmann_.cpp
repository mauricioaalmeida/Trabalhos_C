/******************************************************************************
Pedro Paes Siniscalchi - d2021101303@unifei.edu.br
Breno de Oliveira Renó - brenooliveirareno@unifei.edu.br
Maurício Andre de Almeida - d2021101420@unifei.edu.br

HUFFMAN


*******************************************************************************/


#include <iostream>
#include <cstring>
using namespace std;
#define MAX_TREE_HT 50

// CRIA A Huffman Tree
struct nohHT {
    int freq;
    char letra;
    nohHT* esq;
    nohHT* dir;
};

struct huffTree {
    nohHT* nohRaiz;
};

// CRIA UMA LISTA PARA ARMAZENAR OS CARACTERES E SUAS FREQUENCIAS
struct Celula {
    nohHT* noh;
    Celula *Proximo;
};
struct TipoLista {
    Celula *Primeiro;
    Celula *Ultimo;
};

// CRIA UMA LISTA PARA ARMAZENAR OS CARACTERES E SEUS BITS CODIFICADOS
struct CelCod {
    string code;
    char letra;
    CelCod *Proximo;
};

struct TipoListaCod {
    CelCod *Primeiro;
    CelCod *Ultimo;
};

nohHT* InsereNoh(int freq, char letra){
    nohHT *newnoh = new nohHT;
    newnoh->letra = letra;
    newnoh->freq = freq;
    newnoh->esq = NULL;
    newnoh->dir = NULL;
    return newnoh;
}


// CODIGO DE IMPRESSAO ASCII - copiado na internet

                /*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                !!!Code originally from /http://www.openasthra.com/c-tidbits/printing-binary-trees-in-ascii/
                !!! Just saved it, cause the website is down.
                !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
                //prints ascii tree for given Tree structure
                #define MAX_HEIGHT 1000
                int lprofile[MAX_HEIGHT];
                int rprofile[MAX_HEIGHT];
                #define INFINITY (1<<20)
                //adjust gap between left and right nodes
                int gap = 3;  
                
                //used for printing next node in the same level, 
                //this is the x coordinate of the next char printed
                int print_next;    
                
                int MIN (int X, int Y)  
                {
                  return ((X) < (Y)) ? (X) : (Y);
                }
                
                int MAX (int X, int Y)  
                {
                  return ((X) > (Y)) ? (X) : (Y);
                }
                
                
                typedef struct asciinode_struct asciinode;
                
                struct asciinode_struct
                {
                  asciinode * left, * right;
                
                  //length of the edge from this node to its children
                  int edge_length; 
                    
                  int height;      
                
                  int lablen;
                
                  //-1=I am left, 0=I am root, 1=right   
                  int parent_dir;   
                                         
                  //max supported unit32 in dec, 10 digits max
                  char label[11];  
                };
                
                asciinode * build_ascii_tree_recursive(nohHT * t) 
                {
                  asciinode * node;
                  
                  if (t == NULL) return NULL;
                
                  //node = malloc(sizeof(asciinode));
                  node = new asciinode;
                  node->left = build_ascii_tree_recursive(t->esq);
                  node->right = build_ascii_tree_recursive(t->dir);
                  
                  if (node->left != NULL) 
                  {
                    node->left->parent_dir = -1;
                  }
                
                  if (node->right != NULL) 
                  {
                    node->right->parent_dir = 1;
                  }
                
                  sprintf(node->label, "%d[%c]", t->freq,t->letra);
                  //node->label = t->info.Valor ;
                  node->lablen = strlen(node->label);
                
                  return node;
                }
                
                
                //Copy the tree into the ascii node structre
                asciinode * build_ascii_tree(nohHT * t) 
                {
                  asciinode *node;
                  if (t == NULL) return NULL;
                  node = build_ascii_tree_recursive(t);
                  node->parent_dir = 0;
                  return node;
                }
                
                //Free all the nodes of the given tree
                void free_ascii_tree(asciinode *node) 
                {
                  if (node == NULL) return;
                  free_ascii_tree(node->left);
                  free_ascii_tree(node->right);
                  free(node);
                }
                
                //The following function fills in the lprofile array for the given tree.
                //It assumes that the center of the label of the root of this tree
                //is located at a position (x,y).  It assumes that the edge_length
                //fields have been computed for this tree.
                void compute_lprofile(asciinode *node, int x, int y) 
                {
                  int i, isleft;
                  if (node == NULL) return;
                  isleft = (node->parent_dir == -1);
                  lprofile[y] = MIN(lprofile[y], x-((node->lablen-isleft)/2));
                  if (node->left != NULL) 
                  {
                	  for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++) 
                    {
                	    lprofile[y+i] = MIN(lprofile[y+i], x-i);
                    }
                  }
                  compute_lprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
                  compute_lprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
                }
                
                void compute_rprofile(asciinode *node, int x, int y) 
                {
                  int i, notleft;
                  if (node == NULL) return;
                  notleft = (node->parent_dir != -1);
                  rprofile[y] = MAX(rprofile[y], x+((node->lablen-notleft)/2));
                  if (node->right != NULL) 
                  {
                	  for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++) 
                    {
                	    rprofile[y+i] = MAX(rprofile[y+i], x+i);
                    }
                  }
                  compute_rprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
                  compute_rprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
                }
                
                //This function fills in the edge_length and 
                //height fields of the specified tree
                void compute_edge_lengths(asciinode *node) 
                {
                  int h, hmin, i, delta;
                  if (node == NULL) return;
                  compute_edge_lengths(node->left);
                  compute_edge_lengths(node->right);
                
                  /* first fill in the edge_length of node */
                  if (node->right == NULL && node->left == NULL) 
                  {
                	  node->edge_length = 0;
                  } 
                  else 
                  {
                    if (node->left != NULL) 
                    {
                	    for (i=0; i<node->left->height && i < MAX_HEIGHT; i++) 
                      {
                		    rprofile[i] = -INFINITY;
                	    }
                	    compute_rprofile(node->left, 0, 0);
                	    hmin = node->left->height;
                    } 
                    else 
                    {
                	    hmin = 0;
                    }
                	  if (node->right != NULL) 
                    {
                	    for (i=0; i<node->right->height && i < MAX_HEIGHT; i++) 
                      {
                		    lprofile[i] = INFINITY;
                	    }
                	    compute_lprofile(node->right, 0, 0);
                	    hmin = MIN(node->right->height, hmin);
                    } 
                    else 
                    {
                	    hmin = 0;
                    }
                	  delta = 4;
                	  for (i=0; i<hmin; i++) 
                    {
                	    delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
                    }
                	  
                    //If the node has two children of height 1, then we allow the
                    //two leaves to be within 1, instead of 2 
                	  if (((node->left != NULL && node->left->height == 1) ||
                	      (node->right != NULL && node->right->height == 1))&&delta>4) 
                    {
                      delta--;
                    }
                	    
                    node->edge_length = ((delta+1)/2) - 1;
                  }
                
                  //now fill in the height of node
                  h = 1;
                  if (node->left != NULL) 
                  {
                	  h = MAX(node->left->height + node->edge_length + 1, h);
                  }
                  if (node->right != NULL) 
                  {
                	  h = MAX(node->right->height + node->edge_length + 1, h);
                  }
                  node->height = h;
                }
                
                //This function prints the given level of the given tree, assuming
                //that the node has the given x cordinate.
                void print_level(asciinode *node, int x, int level) 
                {
                  int i, isleft;
                  if (node == NULL) return;
                  isleft = (node->parent_dir == -1);
                  if (level == 0) 
                  {
                	  for (i=0; i<(x-print_next-((node->lablen-isleft)/2)); i++) 
                    {
                	    cout << " ";
                	    // printf(" ");
                    }
                	  print_next += i;
                	  cout << node->label;
                	   //  printf("%s", node->label);
                	  print_next += node->lablen;
                  } 
                  else if (node->edge_length >= level) 
                  {
                	  if (node->left != NULL) 
                    {
                	    for (i=0; i<(x-print_next-(level)); i++) 
                      {
                		    cout << " ";
                	        // printf(" ");
                	    }
                	    print_next += i;
                	    cout << "/";
                	    //printf("/");
                	    print_next++;
                    }
                	  if (node->right != NULL) 
                    {
                	    for (i=0; i<(x-print_next+(level)); i++) 
                      {
                		    cout << " ";
                	        // printf(" ");
                	    }
                	    print_next += i;
                	    cout << "\\";
                	    // printf("\\");
                	    print_next++;
                    }
                  } 
                  else 
                  {
                	  print_level(node->left, 
                                x-node->edge_length-1, 
                                level-node->edge_length-1);
                	  print_level(node->right, 
                                x+node->edge_length+1, 
                                level-node->edge_length-1);
                  }
                }
                
                void print_ascii_tree(nohHT * t) 
                {
                  asciinode *proot;
                  int xmin, i;
                  if (t == NULL) return;
                  proot = build_ascii_tree(t);
                  compute_edge_lengths(proot);
                  for (i=0; i<proot->height && i < MAX_HEIGHT; i++) 
                  {
                	  lprofile[i] = INFINITY;
                  }
                  compute_lprofile(proot, 0, 0);
                  xmin = 0;
                  for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) 
                  {
                	  xmin = MIN(xmin, lprofile[i]);
                  }
                  for (i = 0; i < proot->height; i++) 
                  {
                	  print_next = 0;
                	  print_level(proot, -xmin, i);
                	  cout << endl;
                	  //printf("\n");
                  }
                  if (proot->height >= MAX_HEIGHT) 
                  {
                	  // printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
                	  cout << "(This tree is taller than " << MAX_HEIGHT << ", and may be drawn incorrectly.)" << endl;
                  }
                  free_ascii_tree(proot); 
                }

// FIM DO CODIGO DE IMPRESSAO ASCII


//Verificação de lista vazia
bool listaVazia( TipoLista* lista ) {

  // if (lista->Primeiro == lista->Ultimo)
   if (lista->Primeiro->Proximo == NULL)
   
      return true;
    else
      return false;
}

//Criação da lista vazia
void iniciaListaVazia( TipoLista* lista ) {

    Celula *prox;
    // Cria a cabeca vazia
    prox = new Celula;
    prox->noh = InsereNoh(0, '*');
    prox->Proximo = NULL;
    // Aponta a lista para a cabeca
    lista->Primeiro = prox;
    lista->Ultimo = prox;
}

//Criação da listaCod vazia
void iniciaListaCodVazia( TipoListaCod* lista ) {

    CelCod *prox;
    // Cria a cabeca vazia
    prox = new CelCod;
    prox->letra = '*';
    prox->code = "";
    
    prox->Proximo = NULL;
    // Aponta a lista para a cabeca
    lista->Primeiro = prox;
    lista->Ultimo = prox;
}


//Localizar o caracter na lista
Celula* ProcurarItem (TipoLista *lista, char letra) {
    Celula *cel, *aux = NULL;
    cel = lista->Primeiro;
    
    // verifica se a lista esta vazia
    if (cel->Proximo == NULL) {
        // cout << "---- LISTA VAZIA! ----" << endl;
        return NULL;
    } else 
        while (cel->Proximo != NULL) {
            cel = cel->Proximo;
            if (cel->noh->letra == letra) {
                aux = cel;
    
                break;
            }
        }
  return aux; 
    
 
}

//Verifica se existe e incrementa a frequencia ou insere na lista
void processaLetra( char letra, TipoLista *lista)
{
  // Procura na lista    
 Celula *celaux = ProcurarItem (lista, letra);    
 if (celaux != NULL) { // Encontrou, atualiza a frequencia
    celaux->noh->freq++;  
 } else {  // Cria nova entrada
    Celula *ult, *prox;
    // Cria a nova celula como a ultima da lista
    prox = new Celula;
    prox->noh = InsereNoh(1, letra);
    prox->Proximo = NULL;
    // Atualiza a ultima posicao da lista
    //cout << "---- ----" << lista->Ultimo << endl;
    ult = lista->Ultimo;
    ult->Proximo = prox;
    lista->Ultimo = prox;
 }
}

// insere noh na lista
void InsereNohHTLista( nohHT * noh, TipoLista *lista)
{
 
    Celula *ult, *prox;
    // Cria a nova celula como a ultima da lista
    prox = new Celula;
    prox->noh = noh;
    prox->Proximo = NULL;
    // Atualiza a ultima posicao da lista
    //cout << "---- ----" << lista->Ultimo << endl;
    ult = lista->Ultimo;
    ult->Proximo = prox;
    lista->Ultimo = prox;
    
}



// Ordena a lista pela Frequencia crescente
void OrdenarListaFreq (TipoLista *lista) {
  //cout << "---- Ordenando LISTA:";
  nohHT * nohAux;
  Celula *celI, *celJ, *antJ, *antI;
  antI = lista->Primeiro;
  antJ = lista->Primeiro;
  celI = antI->Proximo;
  celJ = antJ->Proximo;
  if (celI != NULL)
    while (celI->Proximo != NULL) {
        celI = antI->Proximo;
        antJ = lista->Primeiro;
        celJ = antJ->Proximo;
        while (celJ->Proximo != NULL) {
            //cout << "." ;
  
            celJ = antJ->Proximo;

            if ( celI->noh->freq < celJ->noh->freq ){
                nohAux = celI->noh;
                
                celI->noh = celJ->noh;
                
                celJ->noh = nohAux;
                
            } 
            antJ = celJ;
        }
        antI = celI;

    }
  //cout << " ---- LISTA ordenada ! ----" << endl;
  

}

// Processa a string caracter a caracter inserindo na lista e calculando a frequencia
void CriaListaCharFreq(string str, TipoLista *lista)
{
	// tamanho da string 'str'
	int n = str.size();

	// Cria a lista com cada caracter e sua frequencia 'str'
	for (int i = 0; i < n; i++)
    	processaLetra( str[i], lista);
   
    // Ordena a lista
    OrdenarListaFreq (lista);
}

// Listar os itens da lista
void ImprimeLista (TipoLista *lista) {
    int total = 0;
    Celula *cel;
    cel = lista->Primeiro;
    // verifica se a lista esta vazia
    if ( listaVazia(lista) ) {
        cout << "---- LISTA VAZIA! ----" << endl;
    } else {
        int i = 0;
        
        //cout << "LISTA: Primeiro: " << lista->Primeiro << "Ultimo: " << lista->Ultimo << endl;
        cout << "---- Inicio da Lista ----" << endl;
        while ( cel->Proximo != NULL) {
            i++;
            cel = cel->Proximo;
            cout << "Posicao: " << i << " = CARACTER: " << cel->noh->letra << " = Freq: " << cel->noh->freq << endl;
            total = total + cel->noh->freq;
        }
        cout << "---- Fim da Lista ---- TOTAL = " << total << endl;
    }

}

// Listar os itens da lista
void ImprimeListaCod (TipoListaCod *lista) {
    CelCod *cel;
    cel = lista->Primeiro;
    // verifica se a lista esta vazia
    if ( lista->Primeiro->Proximo == NULL ) {
        cout << "------- TABELA DE CODIFICACAO VAZIA! --------" << endl;
    } else {
        int i = 0;
        
        //cout << "LISTA: Primeiro: " << lista->Primeiro << "Ultimo: " << lista->Ultimo << endl;
        cout << "------------ TABELA DE CODIFICACAO  ----------" << endl;
        while ( cel->Proximo != NULL) {
            i++;
            cel = cel->Proximo;
            cout << "Posicao: " << i << " - CARACTER: " << cel->letra << " - Code: " << cel->code << endl;
            
        }
        cout << "------- FIM DA TABELA DE CODIFICACAO  --------" << endl;
        cout << endl;
    }

}


nohHT* retiraMenorFreq(TipoLista *lista){
    //cout << "=> Retirando item da lista." << endl;
    //ImprimeLista(lista);
    Celula *cel;
    Celula *cabeca;
    nohHT *noh;
    cabeca = lista->Primeiro;
    // Ignora a cabeca da lista
    cel = cabeca->Proximo;
    // verifica se a lista esta vazia
    if ( cel == NULL ) {
        //cout << "---- LISTA VAZIA! ----" << endl;
        return NULL;
    } else {
        
        
        if (cel->Proximo !=NULL){
           cabeca->Proximo = cel->Proximo; 
        } else {
           cabeca->Proximo = NULL;
           lista->Ultimo == cabeca;
           //cout << "Retirado ultimo da lista!!!!! "<< endl;
           //if (!listaVazia(lista))
           //   cout << " ===> Lista não Vazia "<< endl;
           //else
           //   cout << " ===> Lista Vazia "<< endl;
        }
        //cout << "Retirado CARACTER: " << cel->noh->letra << " = Freq: " << cel->noh->freq << endl;
        noh = cel->noh;
        delete cel;
        
        return noh;
    }

}



// Insere noh na arvore
nohHT* inserenoh( huffTree* tree, nohHT *folha1, nohHT *folha2 ){
    nohHT* aux = new nohHT;
    // cria o noh raiz
    aux->letra = '*';
    aux->freq = folha1->freq+folha2->freq;
    aux->dir = folha1;
    aux->esq = folha2;
    //cout << "criando noh de Folha1: " << folha1->letra << "[" << folha1->freq << "]" << endl;
    //cout << "             e Folha2: " << folha2->letra << "[" << folha2->freq << "]" << endl;
    cout << endl << " => Ramo parcial: " << endl;
    print_ascii_tree(aux); 
    cout  << endl;
    return aux;
}



//Criar a Huffman Tree 
void criarHuffmanTree (TipoLista *lista, huffTree* tree){
    nohHT * nohAux;
    nohHT * fol1;
    nohHT * fol2;
    while (!listaVazia(lista)){
        //int i = 0;
        fol1 = retiraMenorFreq(lista);
        fol2 = retiraMenorFreq(lista);
        
        if (fol2 == NULL){
           nohAux = fol1;
           break;
        } else {
        
            //cout << "Processando LISTA: Folha1: " << fol1->letra << "[" << fol1->freq << "]" << endl;
            //cout << "                   Folha2: " << fol2->letra << "[" << fol2->freq << "]" << endl;
            //cout << "---- Inicio da Lista ----" << endl;
            //while ( fol1 != NULL) {
            nohAux = inserenoh( tree, fol1, fol2 );
            // Insere noh na lista se nao forem os ultimos
            if (!listaVazia(lista)) {
               InsereNohHTLista ( nohAux, lista );
               // Reordena lista
               OrdenarListaFreq ( lista);
            } else {
                cout << "Processou ultimo da LISTA " << endl;
            }
            
        }
    }
    //cout << "Atualiza a raiz da arvore " << endl;
    tree->nohRaiz = nohAux;
    //}
    
}


// insere na listaCod
void InsereListaCod( TipoListaCod *lista, char letra, int arr[], int top)
{
    //cout << "=> Inserindo letra: " << letra << endl;
    CelCod *ult, *prox;
    // Cria a nova celula como a ultima da lista
    prox = new CelCod;
    string code;
    int i;
    for (i = 0; i < top; ++i)
      code += std::to_string(arr[i]);
    //cout << "           => code: " << code << endl;  
    prox->code = code;
    prox->letra = letra;
    prox->Proximo = NULL;
    // Atualiza a ultima posicao da lista
    //cout << "---- ----" << lista->Ultimo << endl;
    ult = lista->Ultimo;
    ult->Proximo = prox;
    lista->Ultimo = prox;
    
}

CelCod* EncontrarCodLetra (TipoListaCod *lista, char pesq) {
    
    CelCod *cel, *ant;
    cel = lista->Primeiro;
    // verifica se a lista esta vazia
    if (cel->Proximo == NULL) {
        cout << "---- LISTA VAZIA! ----" << endl;
        cel = NULL;
    } else {
        while (cel->Proximo != NULL) {
            
            ant = cel;
            cel = cel->Proximo;
            if (cel->letra == pesq)
                break;
        }
        // Verifica se eh o ultimo e nao encontrou
        if (cel->letra != pesq)
            cel = NULL; // maior do que o ultimo
    }
    return cel;
}

// Print the array
void printArray(int arr[], int n) {
  int i;
  string str;
  for (i = 0; i < n; ++i)
    str += std::to_string(arr[i]);

  //cout << str << "\n";
}


void printHCode(huffTree* tree, nohHT *noh, int arr[], int top) {
  if (noh->dir) {
    arr[top] = 0;
    printHCode(tree, noh->esq, arr, top + 1);
  }

  if (noh->esq) {
    arr[top] = 1;
    printHCode(tree, noh->dir, arr, top + 1);
  }
  if (noh->letra != '*') {
    //cout << endl << noh->letra << "  | ";// << codestr;
    printArray(arr, top);
   
  }
}

void criarCodes(TipoListaCod * lista, huffTree* tree, nohHT *noh, int arr[], int top) {
  //cout << "=> Criando Array de codes: " << endl;
  if (noh->dir) {
    arr[top] = 0;
    criarCodes(lista, tree, noh->esq, arr, top + 1);
  }

  if (noh->esq) {
    arr[top] = 1;
    criarCodes(lista, tree, noh->dir, arr, top + 1);
  }
  if (noh->letra != '*') {
    InsereListaCod( lista, noh->letra, arr, top); 
    
   
  }
}



void processaCodLetra( char letra, TipoListaCod *lista, string * codificado)
{
 //cout << "=> Processando letra: " << letra << endl;
  // Procura na lista    
 CelCod *celaux = EncontrarCodLetra (lista, letra);    
 if (celaux != NULL) { // Encontrou, atualiza a frequencia
    string code = celaux->code;
    *codificado += code;
    //cout << "- code: " << code << endl;
    //cout << "====> CODIFICADO: " << *codificado << endl;
    
 } else { 
    cout << "*** ERRO: NAO ENCONTROU NA TABELA O CARACTER:" << letra << endl;
 }
}

void processarString( TipoListaCod * lista, string str){
    // tamanho da string 'str'
    cout << "==> Processar String     :" << str << endl;
	int n = str.size();
	int tamorig = n* 8;
	cout << "====> Tamanho da string  : " << tamorig << " bits" << endl;
    string * codificado = new string;
	// Cria a lista com cada caracter e sua frequencia 'str'
	for (int i = 0; i < n; i++)
    	processaCodLetra( str[i], lista, codificado);
    cout << "====> CODIFICACAO OBTIDA : " << *codificado << endl;
    string temp = *codificado;
    int tamcod = temp.size();
    cout << "====> Tamanho codificacao: " << tamcod << " bits" << endl;
    double taxa = (double(tamcod) / double(tamorig)) * 100;
    cout << "====> Taxa de compressao : " << taxa << "%" << endl;
};

// Codifica a arvore
void codificarArvore(huffTree * tree, nohHT * raiz, TipoListaCod * lista){
    //cout << "=> Codificando Arvore " << endl;
    int arr[MAX_TREE_HT], top = 0;
    criarCodes (lista, tree, raiz, arr, 0);
    ImprimeListaCod (lista);
};

// Imprime a Codificacao da arvore
void ImprimecodificarArvore(huffTree * tree, nohHT * raiz){
    int arr[MAX_TREE_HT], top = 0;
    printHCode (tree, raiz, arr, 0);

};


int main()
{
    TipoLista *lista = new TipoLista;
    TipoListaCod *listaCod = new TipoListaCod;
    huffTree* tree = new huffTree;
    iniciaListaVazia ( lista );
    string str = "O tempo perguntou pro tempo quanto tempo o tempo tem. O tempo respondeu pro tempo que o tempo tem tanto tempo quanto tempo o tempo tem";
    //string str = "AAAAAABBBBBCCCCDDDEEF";
	CriaListaCharFreq(str, lista);
	//ImprimeLista (lista) ;
	
    criarHuffmanTree ( lista, tree);

    cout << "--------------------------------------------" << endl;
    cout << " ARVORE DE HUFFMAN " << endl;
	print_ascii_tree(tree->nohRaiz); 
	ImprimecodificarArvore(tree, tree->nohRaiz);
	cout << "--------------------------------------------" << endl;
	cout << endl;
	iniciaListaCodVazia( listaCod );
	codificarArvore(tree, tree->nohRaiz, listaCod);
	processarString(listaCod, str);
	return 0;
}
