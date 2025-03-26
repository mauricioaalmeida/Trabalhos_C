/******************************************************************************
MAURICIO ANDRE DE ALMEIDA - UniFEI Matricula 2021101420
Arvore Binaria

Criação de uma nova
Busca se o item está ou não presente, qual o pai e quais os filhos do mesmo
Inserção
Remoção
Impressão da árvore

*******************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

struct Informacao {
    int Valor;
};
struct nohArv {
    Informacao info;
	nohArv *esq;
	nohArv *dir;
};

struct ArvoreBinaria {
  nohArv *raiz;  
};


// Verifica se o noh esta vazio 
bool ehVazia_noArv(nohArv* noh) {
	return noh==NULL;
}


//Criação de um noh
void Cria_noh( nohArv* noh, Informacao info, nohArv* nohesq, nohArv* nohdir ) {
   
    // Cria o noh vazio
    noh = new nohArv;
    noh->info = info;
    noh->esq =  nohesq;
    noh->dir =  nohdir;
}

//Criação da estrutura de dados vazia
ArvoreBinaria* Inicia_ArvVazia( void ) {
    //return NULL;
    // Cria o noh vazio
    //nohArv* noh = NULL;
    ArvoreBinaria* raiz = new ArvoreBinaria;
    raiz->raiz = NULL;
    return raiz;
    //Informacao info;
    //Cria_noh( raiz->raiz, info, NULL, NULL );
    //raiz->raiz->info.Valor = 0;
    //raiz->raiz->esq = NULL;
    //raiz->raiz->dir = NULL;
}

nohArv* inserirnohArv (nohArv* raiz, Informacao info) {
    if (ehVazia_noArv(raiz)){
		raiz = new nohArv;
		raiz->info = info;
		raiz->esq = NULL;
		raiz->dir = NULL;
		return raiz;
	} else {
		if (info.Valor < raiz->info.Valor)
			raiz->esq = inserirnohArv (raiz->esq, info);
		if (info.Valor > raiz->info.Valor)
			raiz->dir = inserirnohArv (raiz->dir, info);
		return raiz;
	}
}
// Inserir valor na Arvore
nohArv* inserirItemArv (ArvoreBinaria* arv, Informacao info) {
    if (arv->raiz == NULL) {
	//if (ehVazia_noArv(raiz)){
		arv->raiz = new nohArv;
		arv->raiz->info = info;
		arv->raiz->esq = NULL;
		arv->raiz->dir = NULL;
		return arv->raiz;
	} else 
		return inserirnohArv(arv->raiz, info);
	
}

// Descobrir pai
nohArv* Pai_noArv(nohArv * raiz, nohArv* pai, Informacao info) {
    Informacao *i;
    if (ehVazia_noArv(raiz)){
		return NULL;
	} else {
	    if (raiz->info.Valor == info.Valor) {
	       return pai;
	    } else {
	        pai = raiz;
    	    if (info.Valor < raiz->info.Valor) 
    	        return Pai_noArv(raiz->esq, pai, info);
    	    else
    	        return Pai_noArv(raiz->dir, pai, info);
	    }
	}
}

nohArv* Minimo_Arv (nohArv * noh) {
   while (noh->esq != NULL) {
       noh = noh->esq;
   } 
   return noh;
}

nohArv* Maximo_Arv (nohArv * noh) {
   while (noh->dir != NULL) {
       noh = noh->dir;
   } 
   return noh;
}


bool ehraizsemfilhos(nohArv * raiz, nohArv * noh) {
 if (raiz == noh && noh->esq == NULL && noh->dir == NULL) 
    return true;
 else
    return false;
}

// Remove um item da Arvore 
nohArv* RemoveItem_Arv (ArvoreBinaria* arv, nohArv* noh, Informacao info) {
    if (ehVazia_noArv(noh)) 
      return NULL;
    else if (noh->info.Valor > info.Valor) 
        noh->esq = RemoveItem_Arv (arv, noh->esq, info);
    else if (noh->info.Valor < info.Valor) 
        noh->dir = RemoveItem_Arv (arv, noh->dir, info);
    else { // achou o noh correto
      // verificar se nao tem filhos 
	  if (noh->esq == NULL && noh->dir == NULL) {
	      // Verificar se nao eh a raiz antes de deletar
	      if (arv->raiz == noh)
	         arv->raiz = NULL;
	      delete noh;
	      noh = NULL;
	         
	  } else // noh soh tem filho a direita
	    if (noh->esq == NULL) {
	        // Verificar se nao eh a raiz antes de deletar
	        if (arv->raiz == noh)
	           arv->raiz = noh->dir;
	        nohArv* temp = noh;
	        noh = noh->dir;
	        delete temp;
	  } else // noh soh tem filho a esquerda
	    if (noh->dir == NULL) {
	        // Verificar se nao eh a raiz antes de deletar
	        if (arv->raiz == noh)
	           arv->raiz = noh->esq;
	        nohArv* temp = noh;
	        noh = noh->esq;
	        delete temp;	    
      } else {// noh tem filho a direita e esquerda
	        nohArv* temp = noh->esq;
	        while (temp->dir != NULL){
	            temp = temp->dir;
	        }
	        noh->info = temp->info; // thread_local
	        temp->info = info;
	        noh->esq = RemoveItem_Arv(arv, noh->esq, info);
	  }
    } 
	return noh;
}


// Procurar valor na Arvore
nohArv* buscarItem_Arv (nohArv* raiz, Informacao info) {
	if (ehVazia_noArv(raiz)){
		return NULL;
	} else {
	    if (raiz->info.Valor == info.Valor) {
	        return raiz;
	    } else {
    	    if (info.Valor < raiz->info.Valor) 
    	        return buscarItem_Arv(raiz->esq, info);
    	    else
    	        return buscarItem_Arv(raiz->dir, info);
	    }
	}
}

// Imprime a arvore horizontalmente da esquerda para a direita
void Imprimir_arv (nohArv* noh){
   if(!ehVazia_noArv(noh)) {
	   Imprimir_arv(noh->esq);
	   //Imprime a raiz
	   cout << "[" << noh->info.Valor << "]";
	   Imprimir_arv(noh->dir);
   }
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
                
                asciinode * build_ascii_tree_recursive(nohArv * t) 
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
                
                  sprintf(node->label, "%d", t->info.Valor);
                  //node->label = t->info.Valor ;
                  node->lablen = strlen(node->label);
                
                  return node;
                }
                
                
                //Copy the tree into the ascii node structre
                asciinode * build_ascii_tree(nohArv * t) 
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
                
                void print_ascii_tree(nohArv * t) 
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

int main() {
    nohArv *noh = NULL;
    nohArv *pai = NULL;
    ArvoreBinaria *arvore;
    Informacao info;
    int opcao;
    int valor, posicao, tamanho, ocorr;
    do {
        cout << "  --------------------------------------------------------------------------------  " << endl;
        cout << "   1) Iniciar Arvore Binaria Vazia:       ";
        cout << "   2) Inserir um novo item na Arvore:     " << endl;
        cout << "   3) Impressao ordenada da Arvore:       ";
        cout << "   4) Encontrar elemento na Arvore:       " << endl;
        cout << "   5) Retirar um item da Arvore:          ";
        cout << "   6) Encontrar o menor elemento:         " << endl;
        cout << "   7) Encontrar o maior elemento:         ";
        cout << "   8) Criar Arvore e executar exemplos:   " << endl;
        cout << "   9) Mostrar Arvore Binaria Completa:    ";
        cout << "   0) Sair:                               " << endl;
        cout << "   Escolha uma Opcao:";
        cin >> opcao;

        switch(opcao)
        {
            case 1:
                
                arvore = Inicia_ArvVazia();
                
                cout << " --- Arvore Inicializada --- " << endl;
                break;
            case 2:
                cout << "Digite o valor do item a incluir: " << endl;
                cin >> valor;
                info.Valor = valor;
                //noh = *arvore->raiz;
                noh = inserirItemArv(arvore, info );
                break;
            case 3:
               
                cout << " --- Arvore --- " << endl;
                Imprimir_arv (arvore->raiz);
                cout << endl;
                cout << " -------------- " << endl;
                break;
            case 4:
                cout << "Digite o valor do item a buscar: " << endl;
                cin >> valor;
                info.Valor = valor;
                noh = buscarItem_Arv(arvore->raiz, info );
                if (noh != NULL) {
                    cout << "valor encontrado: " << noh->info.Valor << endl;
                    pai = Pai_noArv(arvore->raiz, arvore->raiz, info);
                    cout << " --- valor do Pai: " << pai->info.Valor << endl;
                    if (noh->esq != NULL)
                        cout << " --- valor do filho aa esquerda: " << noh->esq->info.Valor << endl;
                    if (noh->dir != NULL)
                        cout << " --- valor do filho aa direita : " << noh->dir->info.Valor << endl;
                    
                    //mostrar pai e filhos
                } else
                    cout << "valor não encontrado: " << endl;
                
                break;
            case 5:
                cout << "Digite o valor do item a retirar: " << endl;
                cin >> valor;
                info.Valor = valor;
                // Primeiro verifica se o valor existe
                noh = buscarItem_Arv(arvore->raiz, info );
                // Verifica se nao eh uma raiz sem filhos antes de retirar
                //if (ehraizsemfilhos(arvore->raiz,noh)) {
                //    noh = RemoveItem_Arv(arvore, arvore->raiz, info );
                //    cout << "valor encontrado e removido! " << endl;
                //    arvore->raiz = NULL;
                //} else 
                if (noh != NULL)  {
                    noh = RemoveItem_Arv(arvore, arvore->raiz, info );
                    cout << "valor encontrado e removido! " << endl;
                } else
                    cout << "valor não encontrado: " << endl;
                
                break;
                
            case 6: 
                noh = Minimo_Arv (arvore->raiz);
                if (noh != NULL) {
                    cout << "Menor valor encontrado: " << noh->info.Valor << endl;
                } else
                    cout << "valor não encontrado: " << endl;
                break;
            case 7:
                noh = Maximo_Arv (arvore->raiz);
                if (noh != NULL) {
                    cout << "Maior valor encontrado: " << noh->info.Valor << endl;
                } else
                    cout << "valor não encontrado: " << endl;
                break;
            case 8: 
                arvore = Inicia_ArvVazia();
                cout << " --- Arvore Inicializada --- " << endl;
                cout << " -> Inserindo valores: ";
                valor = 50; cout << valor << ", "; info.Valor = valor;
                noh = inserirItemArv(arvore, info );
                valor = 25; cout << valor << ", "; info.Valor = valor;
                noh = inserirItemArv(arvore, info );
                valor = 75; cout << valor << ", "; info.Valor = valor;
                noh = inserirItemArv(arvore, info );
                valor = 15; cout << valor << ", "; info.Valor = valor;
                noh = inserirItemArv(arvore, info );
                valor = 5; cout << valor << ", "; info.Valor = valor;
                noh = inserirItemArv(arvore, info );
                valor = 90; cout << valor << ", "; info.Valor = valor;
                noh = inserirItemArv(arvore, info );
                valor = 80; cout << valor << ", "; info.Valor = valor;
                noh = inserirItemArv(arvore, info );
                valor = 30; cout << valor << ", "; info.Valor = valor;
                noh = inserirItemArv(arvore, info );
                valor = 10; cout << valor << ", "; info.Valor = valor;
                noh = inserirItemArv(arvore, info );
                valor = 60; cout << valor << ", "; info.Valor = valor;
                noh = inserirItemArv(arvore, info );
                // Insere um item duplicado!
                valor = 10; cout << valor << ", "; info.Valor = valor;
                noh = inserirItemArv(arvore, info );
                cout << endl;
                cout << " --- Arvore Ordenada --- " << endl;
                Imprimir_arv (arvore->raiz);
                cout << endl;
                cout << " --- Arvore completa --- " << endl;
                print_ascii_tree(arvore->raiz);
                cout << " ----------------------- " << endl;    
                //cout << " -------------- " << endl;
                cout << "-> Retirando o valor: 20" << endl;
                // Tenta retirar um item que não existe
                valor = 20; info.Valor = valor;
                // Primeiro verifica se o valor existe
                noh = buscarItem_Arv(arvore->raiz, info );
                if (noh != NULL) {
                    noh = RemoveItem_Arv(arvore, arvore->raiz, info );
                    cout << "valor encontrado e removido! " << endl;
                } else
                    cout << "valor não encontrado: " << endl;
                // Tenta retirar um item que existe    
                cout << "-> Retirando o valor: 25" << endl;
                valor = 25; info.Valor = valor;
                noh = buscarItem_Arv(arvore->raiz, info );
                if (noh != NULL) {
                    noh = RemoveItem_Arv(arvore, arvore->raiz, info );
                    cout << "valor encontrado e removido! " << endl;
                } else
                    cout << "valor não encontrado: " << endl;
                cout << "-> Encontrar valor: 75 " << endl;    
                valor = 75;
                info.Valor = valor;
                noh = buscarItem_Arv(arvore->raiz, info );
                if (noh != NULL) {
                    cout << "valor encontrado: " << noh->info.Valor << endl;
                    pai = Pai_noArv(arvore->raiz, arvore->raiz, info);
                    cout << " --- valor do Pai: " << pai->info.Valor << endl;
                    if (noh->esq != NULL)
                        cout << " --- valor do filho aa esquerda: " << noh->esq->info.Valor << endl;
                    if (noh->dir != NULL)
                        cout << " --- valor do filho aa direita : " << noh->dir->info.Valor << endl;
                }        
                cout << " --- Arvore Ordenada --- " << endl;
                Imprimir_arv (arvore->raiz);
                cout << endl;
                cout << " -------------- " << endl;
               // Inicia_nohArvVazia ( noh );
                cout << " --- Arvore completa --- " << endl;
                print_ascii_tree(arvore->raiz);    
                break;
            case 9:
                cout << " --- Arvore completa --- " << endl;
                print_ascii_tree(arvore->raiz);
                cout << " ----------------------- " << endl;
                break;
        }
    } while (opcao != 0);
    return 0;
}
