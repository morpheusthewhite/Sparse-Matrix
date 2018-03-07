#include "mat_sparsa_lista.h"
#include "mat_op.h"
#include <stdlib.h>
#include <stdio.h>


//allocate a new matrix
matrice_sparsa* matrice_sparsa_new(int m, int n) {
	matrice_sparsa* res=malloc(sizeof(matrice_sparsa));
	res->m=m;
	res->n=n;
	res->head=NULL;
	return res;
}

//free matrix
void matrice_sparsa_delete(matrice_sparsa* mat) {
	if(mat==NULL)	return;
	elem* aux=mat->head, *temp;
	while(aux!=NULL)
	{
		temp=aux->next;
		free(aux);
		aux=temp;
	}
	free(mat);
	return;
}

//get number of rows
int get_num_row(matrice_sparsa* mat) {
	return mat->m;
}

//get number of columns
int get_num_col(matrice_sparsa* mat) {
	return mat->n;
}


//allocate a node
elem* node_alloc(int i, int j, int x)
{
	elem* res=malloc(sizeof(elem));
	res->i=i;
	res->j=j;
	res->x=x;
	res->next=NULL;
}

//change an element value in matrix mat
void mat_set(matrice_sparsa* mat, int i, int j, int x) {
	if(mat==NULL)	return;
	elem* aux=mat->head;
	if(i>=mat->m || j>=mat->n)	return;	//elemento fuori dalla matrice
	else if(aux==NULL)									//la matrice non contiene alcun elemento
	{
		if(!x)return;
		elem* temp= node_alloc(i,j,x);
		mat->head=temp;
		return;
	}
	elem* prev=NULL;
	while(aux!=NULL)												//la matrice contiene elementi
	{
		if(aux->i == i && aux->j == j)				//nodo già esistente,appena trovato
		{
			if(!x)
			{
				//free del nodo poiché 0
				if(prev!=NULL)
				{
					prev->next=aux->next;
				}
				else
				{
					mat->head=aux->next;
				}
				free(aux);
				return;
			}
			aux->x=x;
			return;
		}
		else if((aux->i == i && aux->j > j) || (aux->i > i))	//nodo non presente nella matrice
		{
			if(!x)return;
			elem* temp=node_alloc(i, j, x);
			if(prev==NULL)
			{
				mat->head=temp;
			}
			else
			{
				prev->next=temp;
			}
			temp->next=aux;
			return;
		}
		prev=aux;
		aux=aux->next;
	}
	if (!x)return;
	elem* temp= node_alloc(i, j, x);
	prev->next=temp;
	return;
}


//get a certain value in matrix mat
int mat_get(matrice_sparsa* mat, int i, int j) {
	elem* aux=mat->head;
	while(aux!=NULL)
	{
		if(aux->i == i && aux->j == j)
		{
			return aux->x;
		}
		else if ((aux->i == i && aux->j < j) || (aux->i <= i))	break;
	}
	return 0;
}

//print a matrix
void mat_print(matrice_sparsa* mat) {
	int r, s;
	elem* aux=mat->head;
	for (r=0; r<mat->m; r++)
	{
		for (s=0; s<mat->n; s++)
		{
			if(aux!=NULL && aux->i == r && aux->j== s)
			{
				printf("%d ", aux->x);
				aux=aux->next;
				continue;
			}
			printf("0 ");
		}
		printf("\n");
	}
	return;
}
