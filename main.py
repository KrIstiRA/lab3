#!/usr/bin/python
import largeClass
import sys


def Menu():
	print "Usage: "
	print "<file_1> <oper> <file_2> <file_result> [-b] [<file_with_modul>]"
	print "Parameters:"
	print "  opers:"
	print "    \"+\" - sum"
	print "    \"-\" - subtract"
	print "    \"*\" - multiply"
	print "    \"/\" - divide"
	print "    \"%\" - take the remainder"
	print "    \"^\" - pow"
	print "  -b for binary files"


def proc(A, B, mod, oper):
	zero = largeClass.largeClass("0")
	res = zero

	if (mod < zero):
		print "Negative mod!"
		return False, res

	if oper == '^':
		res = largeClass.Pow(A, B, mod)
		return True, res

	if (mod > zero):
		A = A % mod
		B = B % mod

	if oper == '+':
		res = A + B

	elif oper == '-':
		res = A - B

	elif oper == '*':
		res = A * B

	elif oper == '/':
		if B == zero:
			print "Division by zero"
			return False, res
		res = A / B

	elif oper == '%':
		if (B == zero):
			print "Division by zero"
			return False, res
		res = A % B

	if (mod > zero):
			res = res % mod
			while (res < zero):
				res = res + mod

	return True, res


def main():
	if len(sys.argv) < 5:
		print "Too few arguments passed."
		Menu()
		return -1

	if len(sys.argv) > 7:
		print "Too many arguments passed."
		Menu()
		return -1
	
	fileA = sys.argv[1]
	oper = sys.argv[2]
	fileB = sys.argv[3]
	fileRes = sys.argv[4]
	binary = False
	fileMod = None

	if len(sys.argv) == 6:
		if sys.argv[5] == "-b":
			binary = True
		else:
			fileMod = sys.argv[5]

	if len(sys.argv) == 7:
		binary = True;
		fileMod = sys.argv[6]
	
	A = largeClass.largeClass(0)
	B = largeClass.largeClass(0)
	mod = largeClass.largeClass(0)
	
	if binary == True:
		A.readFromBinFile(fileA)
		B.readFromBinFile(fileB)
		if fileMod != None:
			mod.readFromBinFile(fileMod)
	else:
		A.readFromTextFile(fileA)
		B.readFromTextFile(fileB)
		if fileMod != None:
			mod.readFromTextFile(fileMod)
	
	isproc, res = proc(A, B, mod, oper)
	if not isproc:
		sys.exit(-1)
		
	if binary == True:
		res.writeToBinFile(fileRes)
	else:
		res.writeToTextFile(fileRes)
			

if __name__ == "__main__":
	main()