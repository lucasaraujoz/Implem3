#include <stdio.h>
#include <stdlib.h>
#include "dll.h"
#include <stdbool.h>
#include <string.h>

typedef struct _aluno
{
    char name[30];
    int matr;
    float nota;
} Aluno;

void menu()
{
    printf("1 - Criar colection\n");
    printf("2 - Inserir na colection\n");
    printf("3 - Listar colection\n");
    printf("4 - Buscar na colection\n");
    printf("5 - Remover da colection\n");
    printf("6 - Limpar a colection\n");
}

int cmpmatr(void *a, void *b) // (spec->data, key)
{
    int *matr = (int *)b;
    Aluno *al = (Aluno *)a; //{'mackele', 1004, 9}  blushing

    if (al->matr == *matr) //e20302403 == 1004
    {
        return true;
    }
    return false;
}

int cmpname(void *a, void *b)
{
    char *name = (char *)b;
    Aluno *al = (Aluno *)a;

    if (strcmp(al->name, name) == 0) // ==0 quer dizer que as string sao iguais, n confundir com true ou false
    {
        return true;
    }
    return false;
}

int cmpfloat(void *a, void *b)
{
    float *nota = (float *)b;
    Aluno *al = (Aluno *)a;

    if (al->nota == *nota)
    {
        return true;
    }
    return false;
}

int main(void)
{
    DLList *l = NULL;
    Aluno *a;
    int i, opc = 0;
    char op;

    int key;
    char nome[30];
    float nota;

    while (1)
    {
        system("CLS");
        printf("1 - Criar Colecao\n");
        printf("2 - Insira um aluno\n");
        printf("3 - Remover um aluno\n");
        printf("4 - Consultar um aluno\n");
        printf("5 - Liste todos os alunos\n");
        printf("6 - Destruir a colection\n");
        printf("7 - Limpe a colection\n");
        printf("8 - Sair\n");
        scanf("%c", &op);
        switch (op)
        {
        case '1':
            //todo criar 2 vezes
            if (l == NULL)
            {
                l = dllCreate();
                printf("Colecao criada com sucesso\n");
                system("PAUSE");
            }
            break;
        case '2':
            if (l != NULL)
            {
                for (i = 0; i < 3; i++)
                {
                    a = (Aluno *)malloc(sizeof(Aluno));
                    printf("Digite o nome do aluno: ");
                    scanf("%s", a->name);
                    printf("Digite a matricula do aluno: ");
                    scanf("%d", &a->matr);
                    printf("Digite a nota do aluno: ");
                    scanf("%f", &a->nota);
                    dllInsertAsFirst(l, (void *)a);
                    printf("Alunos inseridos com sucesso!\n");
                }
            }
            else
            {

                printf("Colecao nao existente\n");
            }
            system("PAUSE");
            break;
        case '5':
            a = (Aluno *)getFirst(l);
            while (a != NULL)
            {
                printf("Nome: %s\n", a->name);
                printf("Matricula: %d\n", a->matr);
                printf("Nota: %.2f\n", a->nota);
                printf("---------------------------------\n");
                a = (Aluno *)getNext(l);
            }
            system("PAUSE");
            break;
        case '4':
            if (l != NULL)
            {
                printf("Como voce quer buscar?\n1 - Matricula\n2 - Nome\n3 - Nota\n");
                scanf("%d", &opc);
                switch (opc)
                {
                case 1:
                    printf("Digite a matricula: ");
                    scanf("%d", &key);
                    a = (Aluno *)dllGetSpecData(l, (void *)&key, cmpmatr);
                    break;
                case 2:
                    printf("Digite o nome: ");
                    scanf("%s", &nome);
                    a = (Aluno *)dllGetSpecData(l, (void *)nome, cmpname);
                    break;
                case 3:
                    printf("Digite a nota: ");
                    scanf("%f", &nota);
                    a = (Aluno *)dllGetSpecData(l, (void *)&nota, cmpfloat);
                    break;
                default:
                    break;
                }

                if (a != NULL)
                {
                    printf("Matricula %d Encontrada:\n", a->matr);
                    printf("Nome.....: %s\n", a->name);
                    printf("Nota.....: %.2f\n", a->nota);
                }
                else
                {
                    printf("\nMatricula nao encontrada\n");
                }
                system("PAUSE");
            }
            break;
        case '3':
            if (l != NULL)
            {
                printf("Entre com a matricula a ser removida: ");
                scanf("%d", &key);
                a = (Aluno *)dllRemoveSpec(l, (void *)&key, cmpmatr);
                if (a != NULL)
                {
                    printf("Matricula %d Removida:\n", a->matr);
                }
                else
                {
                    printf("\nMatricula nao encontrada\n");
                }
                system("PAUSE");
            }
            break;
        case '6':
            if (l != NULL)
            {
                dllDestroy(l);
                l = NULL;
                printf("Colecao destruida com sucesso\n");
                system("PAUSE");
            }
            break;
        case '7':
            dllClearList(l);
            break;
        case '8':
            dllDestroy(l);
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}