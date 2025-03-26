/******************************************************************************
MAURICIO ANDRE DE ALMEIDA - UniFEI Matricula 2021101420
Arvore RubroNegra

Criação de uma nova
Busca se o item está ou não presente, qual o pai e quais os filhos do mesmo
Inserção
Remoção
Impressão da árvore

USE A OPCAO 8 PARA TESTAR!

*******************************************************************************/

#include <iostream>
#include <cstring>
using namespace std;

struct Informacao {
    int Valor;
};
struct nohArv {
    Informacao info;
    char cor; // Cor do Noh - Vermelho ou Preto
    nohArv *pai;
	nohArv *esq;
	nohArv *dir;
};

struct ArvoreVP {
  nohArv *raiz; 
  nohArv *nilVP;
};


// Verifica se o noh esta vazio 
bool ehVazia_noArv(nohArv* noh) {
	return noh==NULL;
}

nohArv* NilVP (ArvoreVP* arv){
   return arv->nilVP;
}


//Criação da estrutura de dados vazia
ArvoreVP* Inicia_ArvVazia( void ) {

    ArvoreVP* arv = new ArvoreVP;
    arv->raiz = NULL;
    //Cria NIL
    nohArv* nilVP = new nohArv;
    Informacao info;
    info.Valor = 0;
    nilVP->info = info;
    nilVP->cor = 'P';
    nilVP->esq = NULL;
    nilVP->dir = NULL;
    return arv;
}

bool rotacao_esq(ArvoreVP* arv, nohArv* nohX) {
 if (nohX==NULL || nohX == NilVP(arv))
    return false;
 else {
     nohArv* temp;
     nohArv* nohY = nohX->dir;
     nohX->dir = nohY->esq;
     if (nohY->esq != NilVP(arv)){
        temp = nohY->esq; 
        temp->pai = nohX;
     }
     nohY->pai = nohX->pai;
     temp = nohX->pai;
     if (nohX->pai == NilVP(arv))
        arv->raiz = nohY;
     else 
         if (nohX == temp->esq){
           //temp = nohX->pai; 
           temp->esq = nohY;
           
         } else {
           //temp = nohX->pai; 
           temp->dir = nohY;
         } 
     nohY->esq = nohX;
     nohX->pai = nohY;
     return true;
 }
}

bool rotacao_dir(ArvoreVP* arv, nohArv* nohX) {
 if (nohX==NULL || nohX == NilVP(arv))
    return false;
 else {
     nohArv* temp;
     nohArv* nohY = nohX->esq;
     nohX->esq = nohY->dir;
     if (nohY->dir != NilVP(arv)){
         temp = nohY->dir; 
         temp->pai = nohX;
     }
     nohY->pai = nohX->pai;
     temp = nohX->pai;
     if (nohX->pai == NilVP(arv))
        arv->raiz = nohY;
     else 
         if (nohX == temp->dir){
             //temp = nohX->pai; 
             temp->dir = nohY;
         }else {
           //temp = nohX->pai; 
           temp->esq = nohY;
         }
     nohY->dir = nohX;
     nohX->pai = nohY;
     return true;
 }
}

// Inserir cor e balancear
void inserirCorArvVP (ArvoreVP* arv, nohArv* nohX) {
 if (nohX==NULL || nohX == NilVP(arv))
    return; // return false
 else {
     nohArv* nohY;
     nohArv* pai = nohX->pai;
     while (pai->cor == 'V') {
         nohArv* avo = pai->pai;
         if (nohX->pai == avo->dir){
             nohY= avo->dir;
             
             if (nohY->cor == 'V'){
                 pai->cor = 'P';
                 nohY->cor = 'P';
                 avo->cor='V';
                 nohX = avo;
             } else {
                 if (nohX == pai->dir){
                     nohX = pai;
                     rotacao_esq(arv, nohX);
                 }
                 pai->cor = 'P';
                 avo->cor = 'V';
                 rotacao_dir(arv, avo);
             }
         } else if (nohX->pai == avo->esq){
             nohY = avo->esq;
             if (nohY->cor == 'V'){
                pai->cor = 'P';
                nohY->cor = 'P';
                avo->cor = 'V';
                nohX = avo;
             } else {
                if (nohX == pai->esq){
                    nohX = nohX->pai;
                    rotacao_dir(arv, nohX);
                }
                pai->cor = 'P';
                avo->cor = 'V';
                rotacao_esq(arv, avo);
             }
         }
        
     }
     nohArv* raiz = arv->raiz;
     raiz->cor='P';
 }
}
     


nohArv* inserirnohArv (ArvoreVP* arv, nohArv* raiz, Informacao info) {
    if (raiz==NULL){
		raiz = new nohArv;
		raiz->info = info;
		raiz->cor = 'V'; // Todo novo noh eh vermelho
        raiz->pai = NilVP(arv);
		raiz->esq = NilVP(arv);
		raiz->dir = NilVP(arv);
    }
    
    nohArv* nohY = new nohArv;
    nohArv* nohX = arv->raiz;
   // if (raiz->info.Valor == info.Valor)// duplicado
   //    return NULL;
    while( nohX != NilVP(arv)){
        nohY = nohX;
    	if (raiz->info.Valor < nohX->info.Valor) 
		    nohX = nohX->esq;
		else
		    nohX = nohX->dir;
    }
	raiz->pai = nohY;
	if (nohY == NilVP(arv))
	   arv->raiz = raiz;
	else
	
    	if (raiz->info.Valor < nohY->info.Valor) 
    		    nohY->esq = raiz;
    	else if (raiz->info.Valor > nohY->info.Valor) 
    		    nohY->dir = raiz;
    		 else return NULL; // Repetido
    raiz->pai = nohY;
	raiz->esq = NilVP(arv);
	raiz->dir = NilVP(arv);
	raiz->cor = 'V';
	inserirCorArvVP(arv,raiz);
	return raiz;

}

nohArv* Minimo_Arv (ArvoreVP* arv, nohArv * noh) {
   while (noh->esq != NilVP(arv)) {
       noh = noh->esq;
   } 
   return noh;
}

nohArv* Maximo_Arv (ArvoreVP* arv, nohArv * noh) {
   while (noh->dir != NilVP(arv)) {
       noh = noh->dir;
   } 
   return noh;
}

nohArv* sucessorVP (ArvoreVP* arv, nohArv* noh) {
   if (noh->dir!= NilVP(arv))
       return Minimo_Arv( arv, noh->dir);
   nohArv* nohY = noh->pai;
   while (nohY != NilVP(arv) && noh == nohY->dir){
       noh = nohY;
       nohY = nohY->pai;
    
   }
   return nohY;      
    
}

// Remover cor e balancear
void removercorVP(ArvoreVP* arv, nohArv* nohX){
 if (nohX==NULL || nohX == NilVP(arv))
    return; // return false
 else {
     while (nohX != arv->raiz && nohX->cor == 'P') {
         if (nohX == nohX->pai->esq){
             nohArv* nohW = nohX->pai->dir;
             if (nohW->cor == 'V') {
               nohW->cor = 'P';
               nohX->pai->cor = 'V';
               rotacao_esq(arv, nohX->pai);
               nohW = nohX->pai->dir;
             }
             if (nohW->esq->cor == 'P' && nohW->dir->cor == 'P'){
                 nohW->cor = 'V';
                 nohX = nohX->pai;
             } else if (nohW->dir->cor == 'P') {
                         nohW->esq->cor = 'P';
                         nohW->cor = 'V';
                         rotacao_dir(arv, nohW);
                         nohW = nohX->pai->dir;
                         nohW->cor = nohX->pai->cor;
                         nohX->pai->cor = 'P';
                         nohW->dir->cor = 'P';
                         rotacao_esq(arv, nohX->pai);
                         nohX = arv->raiz;
                     }
         } else {
             nohArv* nohW = nohX->pai->esq;
             if (nohW->cor == 'V') {
               nohW->cor = 'P';
               nohX->pai->cor = 'V';
               rotacao_dir(arv, nohX->pai);
               nohW = nohX->pai->esq;
             }
             if (nohW->dir->cor == 'P' && nohW->esq->cor == 'P'){
                 nohW->cor = 'V';
                 nohX = nohX->pai;
             } else if (nohW->esq->cor == 'P') {
                         nohW->dir->cor = 'P';
                         nohW->cor = 'V';
                         rotacao_esq(arv, nohW);
                         nohW = nohX->pai->esq;
                         nohW->cor = nohX->pai->cor;
                         nohX->pai->cor = 'P';
                         nohW->dir->cor = 'P';
                         rotacao_dir(arv, nohX->pai);
                         nohX = arv->raiz;
                     }  
         }
        
            
              
         }
     nohX->cor = 'P';    
     }
}
 

nohArv* removernohArv (ArvoreVP* arv, nohArv* noh) {
    if(noh == NULL || noh == NilVP(arv)){ 
    	return NULL; 
	} else {
	    nohArv* nohY;
	    nohArv* nohX;
	    if (noh->esq == NilVP(arv) || noh->dir == NilVP(arv))
	      nohY = noh;
	    else
	      nohY = sucessorVP(arv, noh);
	    if (nohY->esq != NilVP(arv))
	       nohX = nohY->esq;
	    else
	       nohX = nohY->dir;
	    nohX->pai = nohY->pai;
	    if (nohY->pai == NilVP(arv))
	       arv->raiz = nohX;
	    else
	      if (nohY==nohY->pai->esq)
	         nohY->pai->esq = nohX;
	      else
	         nohY->pai->dir = nohX;
	    if (nohY != noh) 
	       noh->info = nohY->info;
	    if (nohY->cor == 'P')  
	      removercorVP(arv, nohX);
	    return nohY;
	        
/*	    
	    
	       nohX = noh->pai;
	    
	    if (nohY->pai == NULL)
	       arv->raiz = nohX;
	    else
	      if (nohY==nohY->pai->esq)
	         nohY->pai->esq = nohX;
	   
	    if (nohY != noh)
	      noh->info = nohY->info;
	    
	    if (nohY->cor == 'P')
	      if (arv->raiz->dir == NULL && arv->raiz->esq->dir != NULL){
	         rotacao_esq(arv, arv->raiz->esq);
	         removercorVP(arv, arv->raiz->esq);
	         rotacao_dir(arv, arv->raiz);
	      } else {
	         if (arv->raiz->esq == NULL && arv->raiz->dir->esq != NULL){
	            rotacao_dir(arv, arv->raiz->dir);
	            removercorVP(arv, arv->raiz->dir);
	            rotacao_esq(arv, arv->raiz); 
	         }
	             
	      }
	    delete (nohY);
	    delete (nohX);
 
*/
	}
}


// Inserir valor na Arvore
nohArv* inserirItemArv (ArvoreVP* arv,  nohArv* raiz, Informacao info) {
    if (arv->raiz == NULL) {
	//if (ehVazia_noArv(raiz)){
		arv->raiz = new nohArv;
		arv->raiz->info = info;
		arv->raiz->cor = 'P'; // Todo novo noh eh vermelho, mas a raiz é preto
		arv->raiz->pai = NilVP(arv);
		arv->raiz->esq = NilVP(arv);
		arv->raiz->dir = NilVP(arv);
		return arv->raiz;
	} else 
		return inserirnohArv(arv, raiz, info);
	
}


// Procurar valor na Arvore
nohArv* buscarItem_Arv (nohArv* raiz, Informacao info) {
	if (raiz==NULL){
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
void Imprimir_arv (nohArv* noh,int nivel){
   if(!ehVazia_noArv(noh)) {
       nivel++;
	   Imprimir_arv(noh->esq, nivel);
	   //Imprime a raiz
	   cout << "[" << noh->info.Valor << "]=" << nivel << noh->cor << " ";
	   Imprimir_arv(noh->dir,nivel);
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
                
                  sprintf(node->label, "%d%c", t->info.Valor,t->cor);
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
    ArvoreVP *arvore;
    Informacao info;
    int opcao;
    int valor, posicao, tamanho, ocorr;
    do {
        cout << "  --------------------------------------------------------------------------------  " << endl;
        cout << "   1) Iniciar Arvore Binaria Vazia:       ";
        cout << "   2) Inserir um novo item na Arvore:     " << endl;
        cout << "   3) Sucessor de um item na Arvore:      ";
        cout << "   4) Encontrar elemento na Arvore:       " << endl;
        cout << "   5) Retirar um item da Arvore:          ";
        cout << "   6) Encontrar o menor elemento:         " << endl;
        cout << "   7) Encontrar o maior elemento:         ";
        cout << "   8) Criar Arvore e executar exemplos:   " << endl;
        cout << "   9) Mostrar Arvore Binaria Completa:    ";
        cout << "  10) Impressao ordenada da Arvore:       " << endl; 
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
                pai = arvore->raiz;
                noh = NULL;
                noh = inserirItemArv(arvore, noh, info );
                break;
            case 3:
                cout << "Digite o valor do item a buscar: " << endl;
                cin >> valor;
                info.Valor = valor;
                noh = buscarItem_Arv(arvore->raiz, info );
                if (noh != NULL) {
                    cout << "    valor encontrado: " << noh->info.Valor << endl;
                    pai = sucessorVP(arvore, noh);
                    cout << " --- valor do Sucessor: " << pai->info.Valor << endl;
                    
                } else
                    cout << "  valor nao encontrado: " << endl;
                
                break;
            case 4:
                cout << "Digite o valor do item a buscar: " << endl;
                cin >> valor;
                info.Valor = valor;
                noh = buscarItem_Arv(arvore->raiz, info );
                if (noh != NULL) {
                    cout << "     valor encontrado: " << noh->info.Valor << endl;
                    pai = noh->pai; 
                    cout << " --- valor do Pai: " << pai->info.Valor << endl;
                    if (noh->esq != NULL)
                        cout << " --- valor do filho aa esquerda: " << noh->esq->info.Valor << endl;
                    if (noh->dir != NULL)
                        cout << " --- valor do filho aa direita : " << noh->dir->info.Valor << endl;
                    
                    //mostrar pai e filhos
                } else
                    cout << "  valor nao encontrado: " << endl;
                
                break;
            case 5:
                cout << "Digite o valor do item a retirar: " << endl;
                cin >> valor;
                info.Valor = valor;
                // Primeiro verifica se o valor existe
                noh = buscarItem_Arv(arvore->raiz, info );

                if (noh != NULL)  {
                    removernohArv(arvore, noh );
                    cout << "  valor encontrado e removido! " << endl;
                } else
                    cout << "  valor nao encontrado: " << endl;
                
                break;
                
            case 6: 
                noh = Minimo_Arv (arvore, arvore->raiz);
                if (noh != NULL) {
                    cout << "  Menor valor encontrado: " << noh->info.Valor << endl;
                } else
                    cout << "  valor nao encontrado: " << endl;
                break;
            case 7:
                noh = Maximo_Arv (arvore, arvore->raiz);
                if (noh != NULL) {
                    cout << "  Maior valor encontrado: " << noh->info.Valor << endl;
                } else
                    cout << "  valor nao encontrado: " << endl;
                break;
            case 8: 
                arvore = Inicia_ArvVazia();
                cout << " --- Arvore Inicializada --- " << endl;
                cout << " -> Inserindo valores: ";
                valor = 50; cout << valor << ", "; info.Valor = valor; noh = NULL;
                noh = inserirItemArv(arvore,noh, info );
                valor = 25; cout << valor << ", "; info.Valor = valor; noh = NULL;
                noh = inserirItemArv(arvore,noh, info );
                valor = 75; cout << valor << ", "; info.Valor = valor; noh = NULL;
                noh = inserirItemArv(arvore,noh, info );
                valor = 15; cout << valor << ", "; info.Valor = valor; noh = NULL;
                noh = inserirItemArv(arvore,noh, info );
                valor = 5; cout << valor << ", "; info.Valor = valor; noh = NULL;
                noh = inserirItemArv(arvore,noh, info );
                valor = 90; cout << valor << ", "; info.Valor = valor; noh = NULL;
                noh = inserirItemArv(arvore,noh, info );
                valor = 60; cout << valor << ", "; info.Valor = valor; noh = NULL;
                noh = inserirItemArv(arvore,noh, info );
                valor = 30; cout << valor << ", "; info.Valor = valor; noh = NULL;
                noh = inserirItemArv(arvore,noh, info );
                valor = 10; cout << valor << ", "; info.Valor = valor; noh = NULL;
                noh = inserirItemArv(arvore,noh, info );
                valor = 3; cout << valor << ", "; info.Valor = valor; noh = NULL;
                noh = inserirItemArv(arvore,noh, info );
                cout << endl;
                cout << " -> Tenta inserir um valor duplicado: " << endl;
                // Insere um item duplicado!
                valor = 10; cout << valor << ", "; info.Valor = valor;noh = NULL;
                noh = inserirItemArv(arvore,noh, info );
                cout << endl;
                cout << " --- Arvore Ordenada --- " << endl;
                Imprimir_arv (arvore->raiz,0);
                cout << endl;
                cout << " --- Arvore completa --- " << endl;
                print_ascii_tree(arvore->raiz);
                cout << " ----------------------- " << endl;    
                //cout << " -------------- " << endl;
                cout << " -> Retirando o valor inexistente: 20" << endl;
                // Tenta retirar um item que não existe
                valor = 20; info.Valor = valor;
                // Primeiro verifica se o valor existe
                noh = buscarItem_Arv(arvore->raiz, info );
                if (noh != NULL) {
                    removernohArv(arvore, noh );
                    cout << "  valor encontrado e removido! " << endl;
                } else
                    cout << "  valor nao encontrado: " << endl;
                // Tenta retirar um item que existe    
                cout << " -> Retirando o valor: 15" << endl;
                valor = 15; info.Valor = valor;
                noh = buscarItem_Arv(arvore->raiz, info );
                if (noh != NULL) {
                    removernohArv(arvore, noh );
                    cout << "  valor encontrado e removido! " << endl;
                } else
                    cout << "  valor nao encontrado: " << endl;
                cout << " -> Encontrar valor: 75 " << endl;    
                valor = 75;
                info.Valor = valor;
                noh = buscarItem_Arv(arvore->raiz, info );
                if (noh != NULL) {
                    cout << "     valor encontrado: " << noh->info.Valor << endl;
                    pai = noh->pai; //Pai_noArv(arvore->raiz, arvore->raiz, info);
                    cout << " --- valor do Pai: " << pai->info.Valor << endl;
                    if (noh->esq != NULL)
                        cout << " --- valor do filho aa esquerda: " << noh->esq->info.Valor << endl;
                    if (noh->dir != NULL)
                        cout << " --- valor do filho aa direita : " << noh->dir->info.Valor << endl;
                    pai = sucessorVP(arvore, noh);
                    cout << " --- valor do Sucessor: " << pai->info.Valor << endl;
                }    
                // Encontrar valor inexistente
                cout << " -> Encontrar valor inexistente: 115 " << endl;    
                valor = 115;
                info.Valor = valor;
                noh = buscarItem_Arv(arvore->raiz, info );
                if (noh != NULL) {
                    cout << "     valor encontrado: " << noh->info.Valor << endl;
                    pai = noh->pai; //Pai_noArv(arvore->raiz, arvore->raiz, info);
                    cout << " --- valor do Pai: " << pai->info.Valor << endl;
                    if (noh->esq != NULL)
                        cout << " --- valor do filho aa esquerda: " << noh->esq->info.Valor << endl;
                    if (noh->dir != NULL)
                        cout << " --- valor do filho aa direita : " << noh->dir->info.Valor << endl;
                    pai = sucessorVP(arvore, noh);
                    cout << " --- valor do Sucessor: " << pai->info.Valor << endl;    
                } else
                    cout << "   valor nao encontrado: " << endl;    
                cout << " -> Encontrar Minimo e Maximo: " << endl; 
                // Encontrar o minimo
                noh = Minimo_Arv (arvore, arvore->raiz);
                if (noh != NULL) {
                    cout << " Menor valor encontrado: " << noh->info.Valor << endl;
                } else
                    cout << "   valor não encontrado: " << endl;
                
                // Encontrar o maximo
                noh = Maximo_Arv (arvore, arvore->raiz);
                if (noh != NULL) {
                    cout << " Maior valor encontrado: " << noh->info.Valor << endl;
                } else
                    cout << "   valor nao encontrado: " << endl;
                
                cout << " --- Arvore Ordenada --- " << endl;
                Imprimir_arv (arvore->raiz, 0);
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
            case 10:
                    
                cout << " --- Arvore --- " << endl;
                Imprimir_arv (arvore->raiz,0);
                cout << endl;
                cout << " -------------- " << endl;
                break;
        }
    } while (opcao != 0);
    return 0;
}


