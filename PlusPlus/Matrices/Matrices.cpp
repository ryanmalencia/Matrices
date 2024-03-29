// Matrices.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <Windows.h>

#define THREADS 6

using namespace std;

typedef struct Data {
	int r;
	int end;
	int cols;
	int ** arr1;
	int * arr2;
	int * res;
} DATA, *PDATA;

DWORD WINAPI DoMath(LPVOID lpParam)
{
	PDATA pDataArray;
	int total = 0;
	int i = 0;
	int j = 0;

	pDataArray = (PDATA)lpParam;
	for (i = pDataArray->r; i < pDataArray->end; i++)
	{
		total = 0;
		for (j = 0; j < pDataArray->cols; j++)
		{
			total += pDataArray->arr1[i][j] * pDataArray->arr2[j];
		}
		pDataArray->res[i] = total;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	char mode = argv[1][0];
	DWORD start;
	start = GetTickCount();
	int row = 14000;
	int col = 14000;
	int **array1;
	int *array2;
	int *result;
	int i = 0;
	int j = 0;
	int count = 0;
	int total = 0;
	DWORD end;
	unsigned int time = 0;
	HANDLE hThreadArray[THREADS];
	DWORD dwThreadIdArray[THREADS];
	PDATA pDataArray[THREADS];

	array1 = (int **)malloc(sizeof(int *) * row);
	array1[0] = (int *)malloc(sizeof(int) * col * row);
	array2 = (int *)malloc(sizeof(int) * row);
	result = (int *)malloc(sizeof(int) * row);

	for (i = 0; i < row; i++)
	{
		array1[i] = (*array1 + col * i);
	}

	for (i = 0; i < row; i++)
	{
		array2[i] = i;
		for (j = 0; j < col; j++)
		{
			array1[i][j] = count;
			count++;
		}
	}

	switch (mode)
	{
	case 't':
		for (i = 0; i < THREADS; i++)
		{
			pDataArray[i] = (PDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(DATA));
			pDataArray[i]->r = (row*i) / THREADS;
			pDataArray[i]->end = (row*(i + 1)) / THREADS;
			pDataArray[i]->cols = col;
			pDataArray[i]->arr1 = array1;
			pDataArray[i]->arr2 = array2;
			pDataArray[i]->res = result;
			hThreadArray[i] = CreateThread(NULL, 0, DoMath, pDataArray[i], 0, &dwThreadIdArray[i]);
		}
		WaitForMultipleObjects(THREADS, hThreadArray, TRUE, INFINITE);
		break;
	case 'n':
		for (i = 0; i < row; i++)
		{
			total = 0;
			for (j = 0; j < col; j++)
			{
				total += array1[i][j] * array2[j];
			}
			result[i] = total;
		}
		break;
	}

	end = GetTickCount();
	time = (unsigned int)(end - start);
	cout << "7888x788: " << array1[7888][788] << endl;
	cout << "Time: " << (end - start) << " ms" << endl;
	cin >> total;

	if (mode == 't')
	{
		for (i = 0; i < THREADS; i++)
		{
			CloseHandle(hThreadArray[i]);
			if (pDataArray[i] != NULL)
			{
				HeapFree(GetProcessHeap(), 0, pDataArray[i]);
				pDataArray[i] = NULL;
			}
		}
	}
    return 0;
}
