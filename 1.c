#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#pragma warning(disable : 4996)

int main()
{
	system("chcp 1251");
	system("cls");
	char cc; //cc - current cymbol
	int k = 1;
	int n;
	int length = 0;	//length - number of rs
	int ones_in_column; //for visualisation
	FILE* file; //for visualisation

	//--------------------------//
	//			Input           //
	//--------------------------//
	printf("Enter number of dots: "); //num of dots
	scanf_s("%d", &n);

	int* stepen = (int*)calloc(n, sizeof(int));//value of dots of the graph
	int* name = (int*)malloc(n * sizeof(int));
	int** a = (int**)malloc(n * sizeof(int*));//matrix

	for (int i = 0; i < n; i++)
	{
		stepen[i] = 0;
	}

	for (int arr = 0; arr < n; arr++)
	{
		a[arr] = (int*)malloc(sizeof(int));
	}

	cc = getchar();
	for (int i = 0; i < n; i++)
	{
		printf("%d  : ", i);
		cc = getchar();
		for (int j = 0; cc != '\n'; j++)
		{
			if ((cc == '1') || (cc == '0'))
			{
				a[i] = (int*)realloc(a[i], sizeof(int) * k);
				a[i][k - 1] = (int)cc - '0';
				k++;
			}
			cc = getchar();
		}
		cc = '\0';
		length = k - 1; //string length 
		k = 1;
	}
	printf("\n\n");

	//Output the table
	printf("\n\n   ");
	printf(" ");
	for (int lit = 'a'; lit < length + 'a'; lit++)
	{

		printf("  %c", lit);
	}
	printf("\n");
	for (int j = 1; j <= ((3 * length) + 8); j++)
	{
		printf("-");
	}
	printf("\n");

	for (int i = 0; i < n; i++)
	{
		printf("%i| ", (i + 1));
		for (int j = 0; j < length; j++)
		{
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}

	// Dot file

	if ((file = fopen("Dot_file.txt", "w")) == NULL) {
		printf("Cannot open file.\n");
		exit(1);
	}
	fprintf(file, "graph G{\n");


	int t = -1;
	ones_in_column = 0;
	int zero = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < length; j++) {
			if (a[i][j] == 1)
				zero = 1;
		}
		if (zero == 0)
			fprintf(file, "%d;\n", (i + 1));
		zero = 0;
	}


	for (int j = 0; j < length; j++) //columns
	{
		for (int i = 0; i < n; i++)  //rows
		{
			if ((a[i][j] == 1) && (ones_in_column > 1))
            
			{
				printf("One edge cannot connect more than 2 graphs");
				exit(-1);
			}
			else
			{
				if ((a[i][j] == 1) && (ones_in_column == 0))
				{
					fprintf(file, "%d", (i + 1));
					fprintf(file, " -- ");
					ones_in_column++;
					t = i;
					stepen[i]++;
				}
				else
				{
					if ((a[i][j] == 1) && (ones_in_column == 1))
					{
						fprintf(file, "%d", (i + 1));
						fprintf(file, " [label=%c];\n", (('a' - 1) + j + 1));
						ones_in_column++;
						stepen[i]++;
					}
				}
			}
		}
		if (ones_in_column == 1)
		{
			fprintf(file, "%d", (t + 1));
			fprintf(file, " [label=%c];\n", (('a' - 1) + t + 1));
		}
		

		//final ones in column
		if (ones_in_column == 1)
			stepen[t] ++;
        
		ones_in_column = 0;
		t = -1;
	}
	
	//--------------//
	//insertion sort//
	//--------------//
	for (int i = 0; i < n; i++)
	{
		name[i] = i + 1;
	}
	int temp,ntemp;
	for (int i = 1; i < n; i++){
		ntemp = name[i];
		temp = stepen[i];
		for (int j = i - 1; j >= 0; j--)
		{
			if (stepen[j] < temp)
				break;
			name[j + 1] = name[j];
			name[j] = ntemp;
			stepen[j + 1] = stepen[j];
			stepen[j] = temp;
		}
	}
	//output//
	//------//
	printf("Name of dot -- stepen \n");

	for (int i = 0; i < n; i++)
	{
		if (stepen[i] % 2 == 0) {
			
			printf("%d -- %d \n", name[i], stepen[i]);
		}
	}
	fprintf(file, "}");
	fclose(file);
	system("dot C:\\Projects\\DZ2\\Dot_file.txt -Tbmp -o Dot_file.bmp");
	system("rundll32  \"%ProgramFiles%\\Windows Photo Viewer\\PhotoViewer.dll\", ImageView_Fullscreen C:\\Projects\\DZ2\\Dot_file.bmp");

	for (int i = 0; i < n; i++)
	{
		free(a[i]);
		free(stepen[i]);
		free(name[i]);
	}
	free(a);
	getchar();
	return 0;
}
