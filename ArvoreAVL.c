#include <stdio.h>
#include <stdlib.h>

typedef struct Arvore{
    int chave;
    int bal;
    struct Arvore *dir;
    struct Arvore *esq;
    int altEsq;
    int altDir;

}arvore;
void rotacaoesquerda(arvore **raiz);
void rotacaodireita(arvore **raiz);
void rotacao_esq_dir(arvore **raiz);
void rotacao_dir_esq(arvore **raiz);

int insereAVL(arvore **raiz,int valor,int cresceu)
{
    if(*raiz==NULL)
    {
        printf("\naqui");
        *raiz=(arvore *)malloc(sizeof(arvore));
        if(*raiz==NULL)
        {
            return 0;
         }
        (*raiz)->dir=NULL;
        (*raiz)->esq=NULL;
        (*raiz)->chave=valor;
        (*raiz)->bal=0;
        cresceu=1;
        return 1;
    }
    else if(valor < (*raiz)->chave)
    {
        cresceu=insereAVL(&(*raiz)->esq,valor,cresceu);
          if(cresceu)
            {
                switch ((*raiz)->bal)
                {
                    case -1:
                    if((*raiz)->esq->bal==-1)
                    {
                        printf("\nrotacionei a direita");
                        rotacaodireita(raiz);
                        (*raiz)->bal=(*raiz)->dir->bal=0;
                    }
                    else
                    {
                        rotacaoesquerda(&(*raiz)->esq);
                        rotacaodireita(raiz);
                        if((*raiz)->bal==-1)
                        {
                            (*raiz)->esq->bal=0;
                            (*raiz)->dir->bal=1;
                        }
                        else
                        {
                            (*raiz)->dir->bal=0;
                            (*raiz)->esq->bal=-(*raiz)->bal;
                        }
                        (*raiz)->bal=0;
                        
                    }
                    cresceu=0;
                    break;
                    case 0:
                    (*raiz)->bal=-1;
                    cresceu=1;
                    break;
                    case 1:
                    (*raiz)->bal=0;
                    cresceu=0;
                    break;
                }
            }
            return 1;

        
        else
        {
            return 0;
        }

    }
    else
    {
        if(insereAVL(&((*raiz)->dir),valor,cresceu))
        {
            if(cresceu){
                switch ((*raiz)->bal)
                {
                case -1:
                (*raiz)->bal=0;
                cresceu=0;
                break;
                case 0:
                (*raiz)->bal=1;
                cresceu=1;
                break;
                case 1:
                if((*raiz)->dir->bal==1)
                {
                    printf("\nrotacionei a esquerda");
                    rotacaoesquerda(&raiz);
                }
                else
                {
                    printf("\nrotacionei a direita e a esquerda");
                    rotacao_dir_esq(&raiz);
                }
                cresceu=0;
                break;
                
                }

            }
            return 1;
            

        }
        else
        {
            return 0;
        }

    }



}

void rotacaoesquerda(arvore **raiz)
    {
        arvore *no;
        no=(*raiz)->dir;
        (*raiz)->dir=no->esq;
        no->esq=*raiz;
        *raiz=no;
    }
void rotacaodireita(arvore *raiz)
{
    arvore *no;
    no=(*raiz)->esq;
    (*raiz)->esq=no->dir;
    no->dir=*raiz;
    *raiz=no;


}

void rotacao_esq_dir(arvore **raiz)
{
   arvore *no;
   no=(*raiz)->esq;
   arvore *no2;
   no2=no->dir;
   (*raiz)->esq=no2->dir;
   no->dir=no2->esq;
   no2->esq=no;
   no2->dir=*raiz;

    switch (no2->bal) {
    case -1:
    no->bal=0; (*raiz)->bal=1; break;
    case 0:
    no->bal=0; (*raiz)->bal=0; break;
    case 1:
    no->bal= -1; (*raiz)->bal=0; break;
    }
    
    no2->bal=0;
    *raiz=no2;

}

void rotacao_dir_esq(arvore **raiz)
{
    arvore *no;
    no=(*raiz)->dir;
    arvore *no2;
    no2=no->esq;
    no->esq=no2->dir;
    (*raiz)->dir=no2->esq;
    no2->esq=*raiz;
    no2->dir=no;
    *raiz=no2;
    switch (no2->bal) {
    case -1:
    (*raiz)->bal=0; no->bal=1; break;
    case 0:
    (*raiz)->bal=0; no->bal=0; break;
    case 1:
    (*raiz)->bal=-1; no->bal=0; break;
    }
    
    no2->bal=0;
    *raiz=no2;




}

void imprimearvore(arvore *r)
{
    if(r!=NULL)
    {
        printf("[%d]",r->chave);
        imprimearvore(r->dir);
        imprimearvore(r->esq);

    }

}


int main()
{
    arvore *raiz=NULL;
    int cresceu;
    insereAVL(&raiz,15,cresceu);
    insereAVL(&raiz,16,cresceu);
    insereAVL(&raiz,17,cresceu);
    insereAVL(&raiz,18,cresceu);
    imprimearvore(raiz);

}