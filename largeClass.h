#pragma once
#ifndef _LARGECLASS_H_
#define _LARGECLASS_H_
#include "largeNum.h"


class largeClass
{
	bigInt bigEx;

public:
	//конструкторы
	largeClass(); // конструктор по умолчанию, вызывается без аргументов
	~largeClass();// деструктор, очистка памяти
	largeClass(const largeClass& tmp);// констр-р копирования
	largeClass(char *string); //конструктор из строки
	largeClass(long long int v);

	// методы
	char *str(); 
	bool readFromTextFile(char* filename);
	bool writeToTextFile(char* filename);
	bool readFromBinFile(char* filename);
	bool writeToBinFile(char* filename);

	// операторы
	largeClass& operator=(const largeClass& rhv); // оператор присвания
	largeClass operator+(const largeClass &right) const;
	largeClass operator-() const; // унарный оператор
	largeClass operator-(const largeClass &right) const;
	largeClass operator*(const largeClass &right) const;
	largeClass operator/(const largeClass &right) const;
	largeClass operator%(const largeClass &right) const;
	largeClass operator^(const largeClass &right) const;

	bool operator>(const largeClass &tmp) const;
	bool operator<(const largeClass &tmp) const;
	bool operator!=(const largeClass &tmp) const;
	bool operator<=(const largeClass &tmp) const;
	bool operator>=(const largeClass &tmp) const;
	bool operator==(const largeClass &tmp) const;
	
	// для Python
	largeClass operator+(int right);
	largeClass operator-(int right);
	largeClass operator*(int right);
	largeClass operator/(int right);
	largeClass operator%(int right);
	largeClass operator^(int right);
	
	bool operator>(const int right) const;
	bool operator<(const int right) const;
	bool operator!=(const int right) const;
	bool operator<=(const int right) const;
	bool operator>=(const int right) const;
	bool operator==(const int right) const;
	
	char* __str__();
	
	char* __repr__();
	
	// дружественная функция
	friend largeClass powModClass(largeClass &base, largeClass &exp, largeClass &mod);
};
#endif