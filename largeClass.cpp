#include "largeClass.h"

largeClass::largeClass()
{
	this->bigEx = createFromInt(0);
}

largeClass::largeClass(const largeClass& tmp)
{
	this->bigEx = copy(tmp.bigEx);
}

largeClass::largeClass(char *string)
{
	this->bigEx = createFromString(string);
}

largeClass::largeClass(long long int v)
{
	this->bigEx = createFromInt(v);
}
largeClass::~largeClass()
{
	if (this->bigEx.digits != NULL)
	{
		free(this->bigEx.digits);
	}
	
}

largeClass& largeClass::operator=(const largeClass& tmp)
{
	if (this->bigEx.digits != NULL)
	{
		free(this->bigEx.digits);
	}
	this->bigEx = copy(tmp.bigEx);
	return *this;
}

char * largeClass::str()
{
	return getString(this->bigEx);
}

largeClass largeClass::operator+(const largeClass &right) const
{
	largeClass res;
	res.bigEx = sumAndSub(this->bigEx, right.bigEx);
	return res;
}

largeClass largeClass::operator-() const
{
	largeClass res;
	res.bigEx = minus(this->bigEx);
	return res;
}

largeClass largeClass::operator-(const largeClass &right) const
{
	return *this + (-right);
}

largeClass largeClass::operator*(const largeClass &right) const
{
	largeClass res;
	res.bigEx = mul(this->bigEx, right.bigEx);
	return res;
}

largeClass largeClass::operator/(const largeClass &right) const
{
	largeClass ost;
	largeClass res;
	res.bigEx = dividing(this->bigEx, right.bigEx, &ost.bigEx);
	return res;
}

largeClass largeClass::operator%(const largeClass &right) const
{
	largeClass ost;
	largeClass res;
	res.bigEx = dividing(this->bigEx, right.bigEx, &ost.bigEx);
	return ost;
}

largeClass largeClass::operator^(const largeClass &right) const
{
	largeClass res;
	res.bigEx = myPow(this->bigEx, right.bigEx);
	return res;
}

	largeClass largeClass::operator+(int right)
	{
	return *this + (largeClass) right;
	}
	
	largeClass largeClass::operator-(int right)
	{
		return *this - (largeClass) right;
	}
	largeClass largeClass::operator*(int right)
	{
		return *this * (largeClass) right;
	}
	largeClass largeClass::operator/(int right)
	{
		return *this / (largeClass) right;
	}
	largeClass largeClass::operator%(int right)
	{
		return *this % (largeClass) right;
	}
	largeClass largeClass::operator^(int right)
	{
		return *this ^ (largeClass) right;
	}
	
	bool largeClass::operator>(const int right) const
	{
		*this > (largeClass) right;
	}
	
	bool largeClass::operator<(const int right) const
	{
		*this <(largeClass) right;
	}
	bool largeClass::operator!=(const int right) const
	{
		*this != (largeClass) right;
	}
	bool largeClass::operator<=(const int right) const
	{
		*this <= (largeClass) right;
	}
	bool largeClass::operator>=(const int right) const
	{
		*this >= (largeClass) right;
	}
	bool largeClass::operator==(const int right) const
	{
		*this == (largeClass) right;
	}
	
bool largeClass::readFromTextFile(char* filename)
{
	largeClass res;
	res.bigEx = ReadFromTextFile(filename);
	if (res.bigEx.digits == NULL)
	{
		return false;
	}
	else
	{
		*this = res;
		return true;
	}
}

bool largeClass::readFromBinFile(char* filename)
{
	largeClass res;
	res.bigEx = getFrombinarFile(filename);
	if (res.bigEx.digits == NULL)
	{
		return false;
	}
	else
	{
		*this = res;
		return true;
	}
}

bool largeClass::writeToTextFile(char* filename)
{
	int res;
	res = WriteToTFile(filename, this->bigEx);
	if (res != 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool largeClass::writeToBinFile(char* filename)
{
return saveTobinarFile(filename, this->bigEx) == 0;	
}

bool largeClass::operator>(const largeClass &tmp) const
{
	return compare(this->bigEx, tmp.bigEx) > 0;
}

bool largeClass::operator<(const largeClass &tmp) const
{
	return compare(this->bigEx, tmp.bigEx) < 0;
}

bool largeClass::operator!=(const largeClass &tmp) const
{
return compare(this->bigEx, tmp.bigEx) != 0;
}

bool largeClass::operator>=(const largeClass &tmp) const
{
return compare(this->bigEx, tmp.bigEx) >= 0;
}

bool largeClass::operator<=(const largeClass &tmp) const
{
return compare(this->bigEx, tmp.bigEx) <= 0;
}

bool largeClass::operator==(const largeClass &tmp) const
{
return compare(this->bigEx, tmp.bigEx) == 0;
}

largeClass powModClass(largeClass &base, largeClass &exp, largeClass &mod)
{
	largeClass res;
	res.bigEx = powMod(base.bigEx, exp.bigEx, mod.bigEx);
	return res;
}

char* largeClass::__str__()
{
	return str();
}
	
char* largeClass::__repr__()
{
	return str();
}
