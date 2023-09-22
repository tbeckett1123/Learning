/* Name: 	Timothy Beckett
 * Lab:		3
 * Set:		5
 * Number:	4
 * Description: Write a program to read two matrices of numbers and find their product. Use 2D-
 * array to represent matrices and use a function to multiply them.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void GetMatrixSize(char* label, int *columns, int *rows);
int* GetMatrixWithValues(char* label, int columns, int rows);
int* NewArray(int size);
void Print(char *message, int *matrix, int columns, int rows);
int* Product(int *matrix1, int *matrix2, int m1Columns, int m1Rows, int m2Columns, int m2Rows, int *m3Columns, int *m3Rows);

int main(int argc, char** argv)
{
    int *matrix1, m1Rows, m1Columns, *matrix2, m2Rows, m2Columns, *matrix3, m3Rows, m3Columns;
    
    GetMatrixSize("A", &m1Columns, &m1Rows);
    GetMatrixSize("B", &m2Columns, &m2Rows);
    
    if (m1Rows != m2Columns) // check if the matrices can be multiplied.
    {
        printf("Invalid matrix dimensions\n");
        return 0;
    }
    
    matrix1 = GetMatrixWithValues("A", m1Columns, m1Rows);
    matrix2 = GetMatrixWithValues("B", m2Columns, m2Rows);    
    matrix3 = Product(matrix1, matrix2, m1Columns, m1Rows, m2Columns, m2Rows, &m3Columns, &m3Rows);
    
    Print("A", matrix1, m1Rows, m1Columns);
    Print("B", matrix2, m2Rows, m2Columns);
    Print("The product of matrices A and B is", matrix3, m3Columns, m3Rows);
    
    free(matrix1);
    free(matrix2);
    free(matrix3);
    
    return 0;
}

// get matrix order from the user
void GetMatrixSize(char* label, int *columns, int *rows)
{   
    printf("Enter the order of the matrix %s:", label);
    scanf("%d %d", columns, rows); 
}

int* GetMatrixWithValues(char* label, int columns, int rows)
{
    // create dynamically sized int array;
    int *array = NewArray(rows * columns);     
    
    printf("Enter the elements of the matrix %s:", label);
    for (int i = 0; i < columns; i++)        
        for (int j = 0; j < rows; j++)
            scanf("%d", &(*(array + (rows * i) + j)));
    
    return array;
}

// allows me to create the matrices the size that I need.
int* NewArray(int size)
{
    return (int*)malloc(sizeof(int) * size);
}

// dumps the matrix to the console.
void Print(char *message, int *matrix, int columns, int rows)
{
    printf("%s:\n", message);
    for (int i = 0; i < columns; i++)        
    {
        for (int j = 0; j < rows; j++)
            printf("%d ", *(matrix + (rows * i) + j));
        
        printf("\n");
    }       
}

int* Product(int *matrix1, int *matrix2, int m1Columns, int m1Rows, int m2Columns, int m2Rows, int *m3Columns, int *m3Rows)
{
    (*m3Columns) = m1Columns;
    (*m3Rows) = m2Rows;
    
    int *matrix3 = NewArray((*m3Columns) * (*m3Rows));
    
    // computers n x p matrix one * two for n x m matrix one, m x p matrix twoand stores the results in matrix3
    for(int i = 0; i < m1Columns; i++)
    {
        for(int j = 0; j < m2Rows; j++)
        {
            *(matrix3 + ((*m3Rows) * i) + j) = 0; init the matrices
            for(int k = 0; k < m2Columns; k++)
                *(matrix3 + ((*m3Rows) * i) + j) = *(matrix3 + ((*m3Rows) * i) + j) + (*(matrix1 + (m1Rows * i) + k) * *(matrix2 + (m2Rows * k) + j)); // sum the products as you go through the matrices
        }
    }
    
    return matrix3;
}