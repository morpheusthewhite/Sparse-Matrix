#include "mat_sparsa_lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

matrice_sparsa* read_mat_ff(const char* file_name);

int main() {
	matrice_sparsa* mat1 = read_mat_ff("mat.dat");

	printf("Original Matrix:\n");
	mat_print(mat1);
	printf("\n");
	printf("########################################");
	printf("########################################");
	printf("\n");
	printf("\n");
	printf("Added -> 0,0,5\n");
	mat_set(mat1, 0, 0, 5);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 10,10,45\n");
	mat_set(mat1, 10, 10, 45);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 10,10,7\n");
	mat_set(mat1, 10, 10, 7);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 24,29,1\n");
	mat_set(mat1, 24, 29, 1);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 24,29,5\n");
	mat_set(mat1, 24, 29, 5);
	mat_print(mat1);
	printf("\n");
	printf("Added -> 18,17,12\n");
	mat_set(mat1, 18, 17, 12);
	mat_print(mat1);
	printf("\n");

	matrice_sparsa* mat2 = read_mat_ff("mat2.dat");

//#########################################
	printf("test della add:\n");
	printf("\n");
	printf("\n");
	mat_print(mat1);
	printf("\n");
	mat_print(mat2);
	printf("\n");
	matrice_sparsa* mat_res;
//#########################################
	mat_res=mat_add(mat1, mat2);
	mat_print(mat_res);
	matrice_sparsa_delete(mat_res);
	printf("\n");
	printf("\n");
	printf("\n");
	printf("test della trasposta:\n");
	printf("\n");
	mat_print(mat1);
	printf("\n");
	mat_res=mat_tra(mat1);
	mat_print(mat_res);
	matrice_sparsa_delete(mat_res);
	printf("\n");
//##########################################
	printf("test della mul:\n");
	mat_res=mat_mul(mat1, mat2);
	mat_print(mat_res);
	matrice_sparsa_delete(mat_res);
	matrice_sparsa_delete(mat1);
	matrice_sparsa_delete(mat2);

}

matrice_sparsa* read_mat_ff(const char* file_name){
	FILE* file = fopen(file_name, "r");
	int val = 0;
	int m, n;
	fscanf(file, "%d", &val);
	m = val;
	fscanf(file, "%d", &val);
	n = val;
	matrice_sparsa* ret = matrice_sparsa_new(m, n);
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			//printf("%d ", i);
			fscanf(file, "%d", &val);
			mat_set(ret, i, j, val);
		}
	}
	fclose(file);
	return ret;
}
