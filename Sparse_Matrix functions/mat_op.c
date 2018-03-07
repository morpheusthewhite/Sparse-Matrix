#include "mat_sparsa_lista.h"
#include <stdlib.h>
#include <stdio.h>


//clone a node
elem* node_clone(elem* one)
{
  elem* res=malloc(sizeof(elem));
  res->i=one->i;
  res->j=one->j;
  res->x=one->x;
  res->next=NULL;
  return res;
}

// Ritorna mat1 + mat2 come una nuova matrice
matrice_sparsa * mat_add ( matrice_sparsa * mat1 , matrice_sparsa * mat2 )
{
  if(mat1==NULL || mat2==NULL)return NULL;
  if(mat1->m!= mat2->m || mat1->n!= mat2->n)
  {
	  printf("Wrong dimensions\n");
	  return NULL; //dimensioni devono essere uguali
  }
  matrice_sparsa* res=matrice_sparsa_new(mat1->m, mat1->n);
  elem* aux1=mat1->head, *aux2=mat2->head, *aux_res=NULL;

  int i1, i2, j1, j2;
  while(aux1!=NULL || aux2!=NULL)
  {
    if(aux1!=NULL && aux2!=NULL) //matrici entrambe con elementi
    {
		i1=aux1->i;
		i2=aux2->i;
		j1=aux1->j;
		j2=aux2->j;
		if(i1==i2 && j1==j2) //nodo presente in entrambe le matrici
		{
			if(aux_res==NULL)
			{
				res->head=node_alloc(i1, j1, aux1->x + aux2->x);
				aux_res=res->head;
			}
			else
			{
				aux_res->next=node_alloc(i1, j1, aux1->x + aux2->x);
				aux_res=aux_res->next;
			}
			aux1=aux1->next;
			aux2=aux2->next;
		}
		else if((i1==i2 && j1<j2) || i1<i2 )  //nodo presente solo in una, la prima
		{
			if(aux_res==NULL)
			{
				res->head=node_alloc(i1, j1, aux1->x);
				aux_res=res->head;
			}
			else
			{
				aux_res->next=node_alloc(i1, j1, aux1->x);
				aux_res=aux_res->next;
			}
			aux1=aux1->next;
		}
		else if((i1==i2 && j2<j1) || i2<i1)	 //nodo presente solo in una, la seconda
		{
			if(aux_res==NULL)
			{
				res->head=node_alloc(i2, j2, aux2->x);
				aux_res=res->head;
			}
			else
			{
				aux_res->next=node_alloc(i2, j2, aux2->x);
				aux_res=aux_res->next;
			}
			aux2=aux2->next;
		}
    }
    else if (aux1==NULL)//una delle due matrici è finita, la prima
    {
      while(aux2!=NULL)
      {
		i2=aux2->i, j2=aux2->j;
		if(aux_res==NULL)
  		{
  			res->head=node_alloc(i2, j2, aux2->x);
  			aux_res=res->head;
  		}
  		else
  		{
  			aux_res->next=node_alloc(i2, j2, aux2->x);
  			aux_res=aux_res->next;
  		}
        aux2=aux2->next;
      }
    }
    else
    {
      while(aux1!=NULL)
      {
        i1=aux1->i, j1=aux1->j;
		if(aux_res==NULL)
		{
			res->head=node_alloc(i1, j1, aux1->x);
			aux_res=res->head;
		}
		else
		{
			aux_res->next=node_alloc(i1, j1, aux1->x);
			aux_res=aux_res->next;
		}
        aux1=aux1->next;
      }
    }
  }
  return res;
}


// Ritorna mat ^t come una nuova matrice
matrice_sparsa * mat_tra ( matrice_sparsa * mat )
{
  if(mat==NULL)return NULL;
  elem* aux=mat->head;
  matrice_sparsa* res=matrice_sparsa_new(mat->n, mat->m);
  while(aux!=NULL)
  {
    mat_set(res, aux->j, aux->i, aux->x);
    aux=aux->next;
  }
  return res;
}


// Ritorna mat1 * mat2 come una nuova matrice
matrice_sparsa * mat_mul ( matrice_sparsa * mat1 , matrice_sparsa * mat2 )
{
  if(mat1==NULL || mat2==NULL)	return NULL;
  else if(mat1->n!= mat2->m)
  {
	  printf("Wrong dimensions!\n");
	  return NULL;
  }
  matrice_sparsa* res=matrice_sparsa_new(mat1->m, mat2->n);
  mat2=mat_tra(mat2);
  elem* aux1=mat1->head, *aux2=mat2->head, *this_line, *aux_res=NULL;

  int r, s, count;
  for (r=0; r<res->m; r++)
  {
	this_line=aux1;
    for (s=0; s<res->n; s++)
    {
	  //iterazione per ogni elemento della nuova matrice
	  aux1=this_line;
	  count=0;

      while(aux1!=NULL && aux2!=NULL && (aux1->i == r) && (aux2->i==s))
      {
        if(aux1->j == aux2->j)
		{
			count+=(aux1->x)*(aux2->x);
			aux1=aux1->next;
			aux2=aux2->next;
		}
        else if ((aux1->j) < (aux2->j)){
          aux1=aux1->next;
        }
        else if (aux1->j > aux2->j){
          aux2=aux2->next;
        }
      }
	  while(aux2!=NULL && aux2->i==s)	aux2=aux2->next;

	  if(count==0)	continue;
	  else if(aux_res==NULL)	//inserimento del nodo nella matrice res
	  {
		  res->head=node_alloc(r, s, count);
		  aux_res=res->head;
	  }
	  else
	  {
		  aux_res->next=node_alloc(r, s, count);
		  aux_res=aux_res->next;
	  }

    }
	while(aux1!=NULL && aux1->i==r)	aux1=aux1->next;
	aux2=mat2->head;
  }
  matrice_sparsa_delete(mat2);
  return res;
}
