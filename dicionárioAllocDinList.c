#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<windows.h>

// Anderson Silva 

struct Dicionario {
    char palavra[50];
    char significado [500];
};
typedef struct Dicionario  Dicionario;

struct No {
    Dicionario dic;
    struct No *prox;
};
typedef struct No *pontno;

pontno alocar() {
    return (malloc(sizeof(struct No)));
}

int menu () {
    int op;

        printf("\n====Dicionário de Palavras====\n\n");
        printf("1- Cadastrar uma palavra.\n");
        printf("2- Listar palavras cadastradas.\n");
        printf("3- Pesquisar uma palavra.\n");
        printf("4- Remover uma palavra.\n5-Sair\n\n");
        printf("Digite uma opção: ");
        scanf("%d", &op);
        
        return op;
}

int vazia(pontno inicio) {
    if (inicio == NULL)
        return 1;

    return 0;
}

void inicializar(pontno *i, pontno *f) {
    *i = NULL;
    *f = NULL;
}

void cadastrar (pontno *i, pontno *f) {
    pontno aux;

    aux = alocar();
    
    printf("Palavra: ");
    fflush(stdin);
    gets(aux->dic.palavra);
    printf("Significado: ");
    fflush(stdin);
    gets(aux->dic.significado);
    printf("\nPalavra cadastrada com sucesso.\n");
    if(vazia(*i)) {
        *i = aux;
        *f = aux;
        (*f)->prox = NULL;
    } else {
       (*f)->prox = aux;
       *f = aux;
       (*f)->prox = NULL;
    }

}

void listar(pontno aux) {
    if(vazia(aux)) {
        printf("\nA lista está vazia.\n");
    } else {
        printf("\nLista de todas as palavras cadastradas.\n");
        while(aux != NULL) {
            printf("%s\n%s\n\n", (aux)->dic.palavra, (aux)->dic.significado);
            aux = aux->prox;
        }
    }
}

void pesquisar(pontno aux, char palavra[50]) {
    int naotem = 0;

    while(aux != NULL) {
        if (strcmp(aux->dic.palavra, palavra) == 0) {
            printf("%s\n%s\n\n", aux->dic.palavra, aux->dic.significado);
            naotem = 1;
        }
        aux = aux->prox;
    }

    if (naotem == 0) {
        printf("\nPalavra não encontrada.\n");
    }
}

void excluir(pontno *i, pontno *f, char palavra[50]) {
    pontno aux, ant;

    ant = NULL;
    aux = *i;

    while(aux != NULL) {
        if (strcmp(aux->dic.palavra, palavra) == 0) {
            aux = aux->prox;
            if (ant == NULL) {
                free(*i);
                *i = aux;
            } else {
                free(ant->prox);
                ant->prox = aux;
            }
        } else {
            ant = aux;
            aux = aux->prox;  
        }
    }
    printf("\nPalavra excluída.\n");  
}

int main () {

    UINT CPAGE_UTF8 = 65001;
    UINT CPAGE_DEFAULT = GetConsoleOutputCP();
    SetConsoleOutputCP(CPAGE_UTF8);

    int opc;
    pontno inicio, fim;
    char pesq[50];
    

    inicializar(&inicio, &fim);


    do {
 
        opc = menu();

        switch(opc) {
            case 1:
                cadastrar (&inicio, &fim);
            break;

            case 2:
                listar(inicio);
            break;

            case 3:
            if(vazia(inicio)) {
                printf("\nA lista está vazia.\n");
            } else {
                printf("Palavra a pesquisar: ");
                fflush(stdin);
                gets(pesq);

                pesquisar(inicio, pesq);
            }
        
            break;

            case 4:
            if(vazia(inicio)) {
                printf("\nA lista está vazia.\n");
            } else {
                printf("Palavra a ser excluída: ");
                fflush(stdin);
                gets(pesq);

                if(vazia(inicio)) {
                    printf("\nA lista está vazia\n");
                } else {
                    excluir(&inicio, &fim, pesq);
                }
            }
            break;

            case 5:
                printf("Saindo...\n\n");
            break;

            default:
                printf("Opção inválida.");
        }

    } while(opc!=5);
}