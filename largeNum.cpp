#include "largeNum.h"


bigInt getFrombinarFile(char* filename)
{
	// ����� �������, ��� � �������� ����� �������� ������� ����� �� ������ 256.
	// ����� �������, ����� ������� ����� �� ��������� ����� ���������� ������ ����
	// �������� �� 256 ^ i, ��� i - ������� ����� � ����� � �� ��� �������

	FILE* pfSource = fopen(filename, "r+b");
	if (!pfSource)
	{
		// ���� ���� �� ��������
		bigInt res;
		res.sizeNum = 0;
		res.sign = 0;
		res.digits = NULL;
		return res;
	}

	// ������ ������ �����
	fseek(pfSource, 0, SEEK_END);
	int filesizeNum = ftell(pfSource);
	fseek(pfSource, 0, SEEK_SET);

	// ��������� ���������� �����
	unsigned char* fileContent = (unsigned char*)malloc(filesizeNum);
	fread((char*) fileContent, sizeof(unsigned char), filesizeNum, pfSource);
	fclose(pfSource);

	bigInt pow256 = createFromInt(1); // ����� ����� 256 ^ i
	bigInt res = createFromInt(0); // ����� ���������� ���������
	bigInt b256 = createFromInt(256); // ����� 256

	// ���� ��� ���� ������ � �����
	int i;
	for (i = 0; i < filesizeNum; i++)
	{
		bigInt fi = createFromInt(fileContent[i]); // �������� ��������� ���� �����

		// res = res + pow256 * fi;

		// tmp = fi * 256 ^ i
		bigInt tmp = mul(fi, pow256);
		free(fi.digits);

		// tmp2 = res + tmp = res + fi * 256^i
		bigInt tmp2 = sumAndSub(res, tmp);
		free(tmp.digits);
		free(res.digits);
		res = tmp2; // res = res + pow256 * fi;

		// pow256 = pow256*256
		tmp = mul(pow256, b256);
		free(pow256.digits);
		pow256 = tmp;
	}

	free(fileContent);
	free(pow256.digits);
	free(b256.digits);

	return res;
}
int saveTobinarFile(char* filename, bigInt A)
{
	// ����� �������, ��� � �������� ���� ���������� �������� ����� �� ��������� 256
	// �� ���� ���������� ������� �� BASE � 256 (256 - ������ ��� ������������ �������� ����� - 255)
	// ��� ����� ���� �������� ������� �� ������� �� 256
	// ���� ����� �� ����������� �� 0
	// ���������� 0 � ������ �������� ������
	// �� 0 - � ������ ������

	FILE* pfDestination = fopen(filename, "w+b");
	if (!pfDestination)
		return 1;

	struct bigInt tmp = copy(A); // �����, ������� ����� ������ �� 256
	tmp.sign = 0; // �� ����� �������� �������� �� ����
	bigInt zero = createFromInt(0);
	bigInt b256 = createFromInt(256);

	// ���� ����� �� ������ ������ 0
	while (compare(tmp, zero) != 0)
	{
		bigInt ost; // ���� ����� ������� ������� �� ������� �� 256

		// tmp = tmp / 256
		bigInt tmp2 = dividing(tmp, b256, &ost);
		free(tmp.digits);
		tmp = tmp2;

		// ������ � ost ��������� ������� �� ������� �� 256
		// ������� ��� � ����

		fwrite((char*)&ost.digits[0], sizeof(unsigned char), 1, pfDestination);
		free(ost.digits);
	}

	free(tmp.digits);
	free(b256.digits);
	free(zero.digits);

	fclose(pfDestination);
	return 0;
}
bigInt ReadFromTextFile(char *fileName)
{
	FILE *fp = fopen(fileName, "r");
	if (!fp)
	{
		// ���� ���� �� ��������
		bigInt res;
		res.sizeNum = 0;
		res.sign = 0;
		res.digits = NULL;
		return res;
	}

	// ������ ������ �����
	fseek(fp, 0, SEEK_END);
	int filesizeNum = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	// ��������� ���������� �����
	char* fileContent = (char*)malloc(filesizeNum + 1);
	fscanf(fp, "%s", fileContent);
	fileContent[filesizeNum] = '\0';
	fclose(fp);
	bigInt res = createFromString(fileContent);
	free(fileContent);
	return res;
}
int WriteToTFile(char *fileName, bigInt A)
{
	FILE *fp = fopen(fileName, "w");
	if (!fp)
		return 1;

	char *res = getString(A);

	fprintf(fp, "%s", res);
	fclose(fp);
	free(res);

	return 0;
}
struct bigInt createFromString(char* string)
{
	int strsizeNum = strlen(string);
	int strSign = 0;
	if (string[0] == '-')
	{
		strsizeNum--;
		strSign = 1;
	}
	char* pStr = string + strsizeNum + strSign;
	// ������� ��������� ���������, � ������� ������� ��������� ��������
	struct bigInt res;
	res.sizeNum = ((strsizeNum + strSign + 8) / 9);
	res.sign = strSign;
	res.digits = (unsigned int*)malloc((res.sizeNum)*sizeof(unsigned int));
	// ��������� ������ �� ����� �� 9 ��������
	int i;
	for (i = 0; i < (strsizeNum + strSign) / 9; i++)
	{
		pStr -= 9;
		char splStr[10];
		memcpy(splStr, pStr, 9);
		splStr[9] = '\0'; // �������� ��������� ������ �� 9 ��������
		unsigned int digitI = atol(splStr);
		res.digits[i] = digitI;
	}
	// ������������ ���������� ������� (���� ����� ������ �� ������ 9)
	char ost[10];
	memset(ost, 0, 10);
	memcpy(ost, string + strSign, pStr - string - strSign); // �������� ������ - �������������� �����
	if (strlen(ost) > 0)
	{
		unsigned int lastDigit = atol(ost);
		res.digits[res.sizeNum - 1] = lastDigit;
	}
	res = DelZeros(res);
	return res;
}
bigInt createFromInt(long long int value)
{
	bigInt res;
	// �������� ������ ��� 3-� ���������
	res.digits = (unsigned int*)malloc((3)*sizeof(unsigned int));
	res.sizeNum = 0;
	res.sign = 0;
	if (value < 0)
	{
		res.sign = 1;
		value = -value;
	}
	do
	{
		res.sizeNum++;
		res.digits[res.sizeNum - 1] = value % BASE;
		value = value / BASE;
	} while (value);
	return res;
}

char* getString(bigInt a)
{
	char* strBuffer = (char*)malloc((a.sizeNum * 9 + 1 + a.sign) * sizeof(char));
	char* pString = strBuffer + a.sizeNum * 9 + a.sign;
	*pString = '\0';
	int i;
	for (i = 0; i < a.sizeNum; i++)
	{
		// �������� ��������� ������������� ���������� �������
		char splStr[10];
		sprintf(splStr, "%09u", a.digits[i]);
		pString -= 9;
		memcpy(pString, splStr, 9);
	}
	// �������� ������� �����
	while (*pString == '0' && *(pString + 1))
		pString++;
	if (a.sign)
	{
		pString--;
		*pString = '-';
	}
	char* string = (char*)malloc((strlen(pString) + 1) * sizeof(char));
	strcpy(string, pString);
	free(strBuffer);
	return string;
}

bigInt copy(bigInt from)
{
	bigInt cpy;
	cpy.sizeNum = from.sizeNum;
	cpy.digits = (unsigned int*)malloc((cpy.sizeNum)*sizeof(unsigned int));
	cpy.sign = from.sign;
	memcpy(cpy.digits, from.digits, cpy.sizeNum * sizeof(unsigned int));
	return cpy;
}

bigInt DelZeros(bigInt a)
{
	while ((a.sizeNum - 1) && a.digits && a.digits[a.sizeNum - 1] == 0)
		a.sizeNum--;
	if (a.sizeNum == 1 && a.digits[0] == 0)
		a.sign = 0;
	return a;
}

long long int compare(bigInt A, bigInt B)
{
	int aSign = 1;
	if (A.sign == 1)
		aSign = -1;
	if (A.sign != B.sign)
		return aSign;
	if (A.sizeNum > B.sizeNum)
		return aSign;
	if (A.sizeNum < B.sizeNum)
		return -aSign;
	int i = A.sizeNum - 1;
	while (A.digits[i] == B.digits[i] && i > 0)
	{
		i--;
	}
	return ((long long int) A.digits[i] - (long long int)B.digits[i]) * aSign;
}

bigInt sumAndSub(bigInt left, bigInt right)
{
	// ����� � � ����� �� ������ �� ������, ��� � B
	bigInt A = left, B = right;
	A.sign = 0;
	B.sign = 0;
	if (compare(A, B) > 0)
	{
		A.sign = left.sign;
		B.sign = right.sign;
	}
	else
	{
		A = right;
		B = left;
	}
	// ���� ����� ������ ����� - ���������� �� (� ������������ ������� �����)
	if (A.sign == B.sign)
		return sum(A, B);
	else // ����� ��������
		return sub(A, B);
}

bigInt sum(bigInt A, bigInt B)
	{// �������� ���� �����, ������ A - �� ������ B
	bigInt res;
	res.sign = 0;
	res.sizeNum = A.sizeNum + 1;
	res.digits = (unsigned int*)malloc((A.sizeNum + 1)*sizeof(unsigned int));

	unsigned int carry = 0;
	int i;
	for (i = 0; i < A.sizeNum; i++)
	{
		unsigned int tmp = A.digits[i] + carry;
		if (i < B.sizeNum)
			tmp += B.digits[i];

		res.digits[i] = tmp % BASE;
		carry = tmp / BASE;
	}
	res.digits[A.sizeNum] = carry;
	res.sign = A.sign;
	res = DelZeros(res);
	return res;
}

bigInt sub(bigInt A, bigInt B)
{// ��������� ���� �����, ������ A ������ B �� ������
	bigInt res;
	res.sign = 0;
	res.sizeNum = A.sizeNum;
	res.digits = (unsigned int*)malloc((A.sizeNum)*sizeof(unsigned int));
	unsigned int carry = 0;
	int i;
	for (i = 0; i < A.sizeNum; i++)
	{
		int tmp = A.digits[i] - carry;
		if (i < B.sizeNum)
		tmp -= B.digits[i];
		carry = 0;
		if (tmp < 0)
		{
			carry = 1;
			tmp += BASE;
		}
		res.digits[i] = tmp;
	}
	res.sign = A.sign;
	res = DelZeros(res);
	return res;
}

bigInt minus(bigInt a)
{// ������ ����� ����� a, �� � ��������������� ������
	bigInt res = copy(a);
	res.sign = !a.sign;
	return res;
}

bigInt mul(bigInt A, bigInt B)
{
	bigInt res;
	res.sizeNum = A.sizeNum + B.sizeNum;
	res.digits = (unsigned int*)malloc((res.sizeNum)*sizeof(unsigned int));
	memset(res.digits, 0, res.sizeNum * sizeof(unsigned int));
	unsigned int carry = 0;
	int i;
	for (i = 0; i < B.sizeNum; i++)
	{
		carry = 0;
		int j;
		for (j = 0; j < A.sizeNum; j++)
		{
			unsigned long long int tmp = (unsigned long long int) B.digits[i] * (unsigned long long int) A.digits[j]
				+ carry + (unsigned long long int) res.digits[i + j];
			carry = tmp / BASE;
			res.digits[i + j] = tmp % BASE;
		}
		res.digits[i + A.sizeNum] = carry;
	}
	res.sign = (A.sign != B.sign);
	res = DelZeros(res);
	return res;
}
bigInt dividing(bigInt A, bigInt B, bigInt* ost)
{
	*ost = copy(A);
	ost->sign = 0;
	bigInt divider = copy(B);
	divider.sign = 0;
	if (1 == divider.sizeNum)
	{
		if (divider.digits[0] == 0)
		{
			ost->sizeNum = 0;
			ost->sign = 0;
			ost->digits = NULL;
			bigInt a;
			a.sizeNum = 0;
			a.sign = 0;
			a.digits = NULL;
			free(divider.digits);
			return a;
		}
	}
	if (compare(*ost, divider) < 0)
	{
		ost->sign = A.sign;
		bigInt res;
		res.sign = 0;
		res.sizeNum = 1;
		res.digits = (unsigned int*)malloc((res.sizeNum)*sizeof(unsigned int));
		res.digits[0] = 0;
		free(divider.digits);
		return res;
	}
	if (divider.sizeNum == 1)
	{
		bigInt res;
		res.sizeNum = A.sizeNum;
		res.digits = (unsigned int*)malloc((res.sizeNum)*sizeof(unsigned int));
		unsigned long long int carry = 0;
		int i;
		for (i = A.sizeNum - 1; i >= 0; i--)
		{
			unsigned long long int temp = carry;
			temp *= BASE;
			temp += A.digits[i];
			res.digits[i] = temp / divider.digits[0];
			carry = (unsigned long long int)  temp - (unsigned long long int) res.digits[i] * (unsigned long long int) divider.digits[0];
		}
		ost->sign = (A.sign != B.sign);
		if (ost->sizeNum > 0)
		free(ost->digits);
		ost->sizeNum = 1;
		ost->digits = (unsigned int*)malloc((1)*sizeof(unsigned int));
		ost->digits[0] = carry;
		*ost = DelZeros(*ost);
		res.sign = (A.sign != B.sign);
		res = DelZeros(res);
		free(divider.digits);
		return res;
	}
	bigInt res;
	res.sign = 0;
	res.sizeNum = A.sizeNum - B.sizeNum + 1;
	res.digits = (unsigned int*)malloc((res.sizeNum)*sizeof(unsigned int));

	int i;
	for (i = A.sizeNum - B.sizeNum + 1; i != 0; i--)
	{
		long long int qGuessMax = BASE; // ��� ����, ����� qGuessMin ����� ���� ����� BASE - 1
		long long int qGuessMin = 0;
		long long int qGuess = qGuessMax;
		while (qGuessMax - qGuessMin > 1)
		{
			qGuess = (qGuessMax + qGuessMin) / 2;
			bigInt qGuesslargeNum = createFromInt(qGuess);
			bigInt tmp = mul(divider, qGuesslargeNum);
			free(qGuesslargeNum.digits);
			tmp = shiftLeft(tmp, i - 1);
			if (compare(tmp, *ost) > 0)
				qGuessMax = qGuess;
			else
				qGuessMin = qGuess;
			free(tmp.digits);
		}
		bigInt qGuessMinlargeNum = createFromInt(qGuessMin);
		bigInt tmp = mul(divider, qGuessMinlargeNum);
		free(qGuessMinlargeNum.digits);
		tmp = shiftLeft(tmp, i - 1);
		bigInt tmpRem = copy(*ost);
		bigInt minusTmp = minus(tmp);
		free(ost->digits);
		*ost = sumAndSub(tmpRem, minusTmp);
		free(tmpRem.digits);
		free(minusTmp.digits);
		free(tmp.digits);
		res.digits[i - 1] = qGuessMin;
	}
	res.sign = (A.sign != B.sign);
	ost->sign = (A.sign != B.sign);
	*ost = DelZeros(*ost);
	res = DelZeros(res);
	free(divider.digits);
	return res;
}

bigInt shiftLeft(bigInt a, int s)
{// �������� ����� a �� s �������� ������
	unsigned int* newDig = (unsigned int*)malloc((a.sizeNum + s)*sizeof(unsigned int));
	// ��������� ������� ������� ������
	memset(newDig, 0, s * sizeof(unsigned int));
	// �������� ������� �������
	memcpy(newDig + s, a.digits, a.sizeNum * sizeof(unsigned int));
	free(a.digits);
	a.digits = newDig;
	a.sizeNum += s;
	return a;
}

bigInt myPow(bigInt base, bigInt exp)
{
	// ���������� base � ������� exp
// ����� ��� ������, ��� ���� ����������� ������� � ����� �� ������,
// � � �� ��������� � ����������� �������
	bigInt res = createFromInt(1); // ���� ����� ������� ���������
	bigInt zero = createFromInt(0);
	bigInt i = copy(exp); // ������� ��� ��������� ���������� �������� �� exp
	bigInt minusOne = createFromInt(-1); // -1

	// ���� ���������� ����������� ��������� ������ ����
	while (compare(i, zero) > 0)
	{
		// res = res * base
		bigInt tmp = mul(res, base);
		free(res.digits);
		res = tmp;

		// ����� ��������� ��� �������: i = i -1
		tmp = sumAndSub(i, minusOne); // ���������� i � (-1), �.�. tmp = i - 1
		free(i.digits); // ������� ������
		i = tmp;
	}

	// ������� ������
	free(i.digits);
	free(zero.digits);
	free(minusOne.digits);

	return res;
}

bigInt powMod(bigInt base, bigInt exp, bigInt modul)
{
	// ���������� base � ������� exp �� ������ modul
	// ����� ������ �� ������� ���������� � �������,
	// ������ ����� ����� ������� ��������� ���������� ��� ����� ������� �� ������� �� modul
	bigInt res = createFromInt(1); // ���� ����� ������� ���������
	bigInt zero = createFromInt(0);
	bigInt i = copy(exp); // ������� ��� ��������� ���������� �������� �� exp
	bigInt minusOne = createFromInt(-1); // -1

	// ���� ���������� ����������� ��������� ������ ����
	while (compare(i, zero) > 0)
	{
		// tmp = res * base
		bigInt tmp = mul(res, base);

		// res = tmp % base
		bigInt modRem; // ���� ������� ������� �� �������
		bigInt tmp2 = dividing(tmp, modul, &modRem);
		free(tmp2.digits);
		free(tmp.digits);
		free(res.digits);
		res = modRem;

		// ����� ��������� ��� �������: i = i -1
		tmp = sumAndSub(i, minusOne); // ���������� i � (-1), �.�. tmp = i - 1
		free(i.digits); // ������� ������
		i = tmp;
	}
	// ������� ������
	free(i.digits);
	free(zero.digits);
	free(minusOne.digits);
	return res;
}