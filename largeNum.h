#ifndef _LARGENUM_H_
#define _LARGENUM_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define BASE 1000000000

struct bigInt
{
	int sizeNum;//размер
	int sign;//знак
	unsigned int* digits;//цифры
};

typedef struct bigInt bigInt;//определение типа, чтобы не писать каждый раз struct bigInt
bigInt getFrombinarFile(char* filename);
int saveTobinarFile(char* filename, bigInt A);
bigInt ReadFromTextFile(char *fileName);
int WriteToTFile(char *fileName, bigInt A);
struct bigInt createFromString(char* string);
bigInt createFromInt(long long int value);
char* getString(bigInt a);
bigInt copy(bigInt from);
bigInt DelZeros(bigInt a);
long long int compare(bigInt A, bigInt B);
bigInt sumAndSub(bigInt left, bigInt right);
bigInt sum(bigInt A, bigInt B);
bigInt sub(bigInt A, bigInt B);
bigInt minus(bigInt a);
bigInt mul(bigInt A, bigInt B);
bigInt dividing(bigInt A, bigInt B, bigInt* ost);
bigInt shiftLeft(bigInt a, int s);
bigInt myPow(bigInt base, bigInt exp);
bigInt powMod(bigInt base, bigInt exp, bigInt modul);
#endif