#pragma once
#ifndef _LARGECLASS_H_
#define _LARGECLASS_H_
#include "largeNum.h"


class largeClass
{
	bigInt bigEx;

public:
	//������������
	largeClass(); // ����������� �� ���������, ���������� ��� ����������
	~largeClass();// ����������, ������� ������
	largeClass(const largeClass& tmp);// ������-� �����������
	largeClass(char *string); //����������� �� ������
	largeClass(long long int v);

	// ������
	char *str(); 
	bool readFromTextFile(char* filename);
	bool writeToTextFile(char* filename);
	bool readFromBinFile(char* filename);
	bool writeToBinFile(char* filename);

	// ���������
	largeClass& operator=(const largeClass& rhv); // �������� ���������
	largeClass operator+(const largeClass &right) const;
	largeClass operator-() const; // ������� ��������
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
	
	// ��� Python
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
	
	// ������������� �������
	friend largeClass powModClass(largeClass &base, largeClass &exp, largeClass &mod);
};
#endif