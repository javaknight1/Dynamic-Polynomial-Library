/******************************************
** File:    polynomials.h
** Author:  Rob Avery
** Date:    4/3/2012
** Section: 02
** Email:   pw97976@gmail.com
**
**   This program will read in a text file that includes
** a bunch of commands and will process them accordingly.
** From the commands given, the program will store multiple
** polynomials and display the results.
**
** Other files:
**      1.project3.c -- main
**      2.polynomials.c -- includes the function
**                         defintions of this header
**
******************************************/

//#include <stdio.h>
#define TERMLEN 20

typedef struct term {
   int coeff;
   int exp;
} TERM;

typedef struct poly {
   TERM *term;
} POLY;

/**************************************
** freePoly --
**   Frees all the polynomials and it's
** terms that were allocated.
**   Input: Polynomial that was allocated
**   Output: Void. No output.
**************************************/
void freePoly(POLY*);

/**************************************
** addTerm -- 
**   Adds a new term to the current 
** polynomial.
**   Input: Polynomial  to the
** polynomial that is getting the
** new term, coefficient, and exponent
**   Output: New POLY with new TERM
**************************************/
void addTerm(POLY*, int, int);


/**************************************
** add --
**   Adds two polynomials.
**   Input: Two polynomials to add, and
** the new sum polynomial
**   Output: the new polynomial after
**         adding the two polynomials
**************************************/
void add(POLY, POLY, POLY*);


/**************************************
** subtract --
**   Subtracts one polynomial from
** another.
**   Input: two polynomials that need
** to be subtracted, and the new 
** difference polynomial.
**   Output: No output. Void function.
**************************************/
void subtract(POLY, POLY, POLY*);

/**************************************
** multiply --
**   Mulitplies a polynomial by a certain
** number
**   Input: polynomial and number to 
** multiply them by.
**   Output: the new polynomial
**************************************/
void multiply(POLY*, int);

/**************************************
** displayPoly --
**   Simply displays the POLY passed in
**   Input: POLY that is being
** displayed
**   Output: VOID function. Prints
** polynomial.
**************************************/
void displayPoly(POLY*);

/**************************************
** getTermLength --
**   Returns the number of terms in a 
** POLY
**   Input: POLY
**   Output: number of valid terms
**************************************/
int getTermLength(POLY);

/**************************************
** sortExp --
**   Sorts the exponents of the POLY
** passed and returns the new sorted
** POLY
**   Input: POLY needing sorted
**   Output: new sorted POLY
**************************************/
int sortExp(POLY);

/**************************************
** emptyPoly --
**   Completely empties the POLY by
** making the exponent = -1 and the 
** coefficient = 0
**   Input: POLY needing to empty
**   Output: New empty POLY
**************************************/
void emptyPoly(POLY*);

/*************************************
** clearTerm --
**   Clears all terms in one Poly
**   Input: one POLY
**   Output: No output. Void function.
*************************************/
void clearTerm(POLY*);
