#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <cstdlib>

int cantidad = 0;
char byte[8];
int vec[1000];
int vec2[100];
int contador = 0;

// Prototipo de la funcion

void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);
void enmascarar_asm(unsigned char *a, unsigned char *b, unsigned char *mask, int cant);

//argc -> entero -> contiene el número de argumentos que se han introducido.
//argv -> array -> array de punteros a caracteres.

int main(int argc, char *argv[])
{

	int i = 0;
	for (i = 0; i < argc; i++)
	{
		printf("argv[%d] = %s\n", i, argv[i]);
	}
	//return 0;

	printf("Program name %s\n", argv[0]);

	if (argc == 5)
	{
		printf("Se ingresaron todos los argumentos \n");
	}
	else if (argc < 5)
	{
		printf("Faltaron argumentos.\n");
	}
	else
	{
		printf("Se ingresaron argumentos de mas.\n");
	}

	char *a = (char *)argv[1];
	char *b = (char *)argv[2];
	char *mask = (char *)argv[3];
	char *d = (char *)argv[4];
	int cant = atoi(d);
	//conversion a int con atoi
	//int cant = (int)argv[4];

	//llamada a metodo c
	enmascarar_c(a, b, mask, cant);

	system("PAUSE");

	return 0;
}

// Implementacion

void enmascarar_c(unsigned char *a, unsigned char *b, unsigned char *mask, int cant)
{

	cantidad = cant;

	//reservo espacio con malloc
	printf("\n\nCantidad de bytes a procesar: %d\n", cant);
	printf("Ruta a imagen 1:  %s\n", a);
	printf("Ruta a imagen 2:  %s\n", b);
	printf("Ruta a mascara :  %s\n", mask);
	printf("cantidad :  %d\n\n", cant);

	unsigned char *vectorA = malloc(cantidad);
	unsigned char *vectorB = malloc(cantidad);
	unsigned char *vectorMask = malloc(cantidad);
	unsigned char *resultado = malloc(cantidad);

	//abro los archivos rgb con FILE
	FILE *fpA = fopen(a, "rb");
	FILE *fpB = fopen(b, "rb");
	FILE *fpMask = fopen(mask, "rb");
	FILE *fpResultado = fopen("test.rgb", "wb");
	if (!fpResultado)
	{
		printf("No se pudo crear archivo de destino\n");
	}

	if (fpA == NULL)
	{
		printf("file A doesnt exist!");
		//return 1;
	}
	if (fpB == NULL)
	{
		printf("file B doesnt exist!");
		//return 1;
	}
	if (fpMask == NULL)
	{
		printf("file Mask doesnt exist!");
		//return 1;
	}

	fread(vectorA, sizeof *vectorA, cantidad, fpA);
	fread(vectorB, sizeof *vectorB, cantidad, fpB);
	fread(vectorMask, sizeof *vectorMask, cantidad, fpMask);

	// fgets(vectorA, cantidad, fpA);
	// fgets(vectorB, cantidad, fpB);
	// fgets(vectorMask, cantidad, fpMask);

	int i;
	for (i = 0; i < cantidad; i++)
	{
		resultado[i] = vectorMask[i] == 255 ? vectorA[i] : vectorB[i];
	}

	printf("iteraciones hechas :  %d\n\n", i);

	fwrite(resultado, 1, cantidad, fpResultado);

	fclose(fpA);
	fclose(fpB);
	fclose(fpMask);
	fclose(fpResultado);

	free(vectorA);
	free(vectorB);
	free(vectorMask);
	free(resultado);
}
