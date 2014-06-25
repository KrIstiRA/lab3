%module largeClass
%{
/* Includes the header in the wrapper code */
#include "largeClass.h"
%}


/* Parse the header file to generate wrappers */
%include "largeClass.h"