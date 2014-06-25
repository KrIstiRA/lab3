all:
	swig -c++ -python largeClass.i
	g++ -fPIC -c largeClass.cpp
	g++ -fPIC -c largeNum.cpp
	g++ -fPIC -c largeClass_wrap.cxx -I/usr/include/python2.7
	g++ -shared largeClass.o largeNum.o largeClass_wrap.o -o _largeClass.so
	
windows32:
	swig -c++ -python largeClass.i
	g++ -c largeClass.cpp
	g++ -c largeNum.cpp
	g++ -c largeClass_wrap.cxx -IC:\Python27\include
	g++ largeClass.o largeNum.o largeClass_wrap.o -Ic:\python27\include -Lc:\python27\libs -lpython27 -shared -o _largeClass.pyd
	del *.o *.cxx
