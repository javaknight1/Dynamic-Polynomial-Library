/******************************************
** File:    polynomials.c
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
**      2.polynomials.h -- includes the prototypes
**                         of these defintions
**
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "polynomials.h"

#define TRUE 1
#define FALSE 0
#define TERMLEN 20



void freePoly(POLY* poly){

   //printf("...freePoly: poly       = |%p|\n", poly);
   //printf("...freePoly: poly->term = |%p|\n", poly->term);
   free( poly->term );
   free( poly );

}

void emptyPoly(POLY* poly) {

   poly->term = (TERM*)malloc( TERMLEN * sizeof(TERM) );
   //printf("...emptyPoly: poly       = |%p|\n", poly);
   //printf("...emptyPoly: poly->term = |%p|\n", poly->term);

   clearTerm( poly );
  
}

void clearTerm(POLY* p){
  
   int i;

   for( i = 0; i < TERMLEN; i++ ) {
         p->term[i].coeff = 0;
         p->term[i].exp = -1;
   }
  
}

int getTermLength(POLY poly) {

   int count = 0;
   //int length = ( sizeof(poly.term)/sizeof(TERM) );
   int i;

   for( i = 0; i < TERMLEN; i++ ) {
      if(poly.term[i].coeff != 0 ) {
         count++;
      }
   }
   return count;
}

POLY bsortExp(POLY poly) {

   POLY newPoly = poly;
   TERM tempTerm;
   int length = getTermLength(poly);
   int i, j;

   for( i = length; i > 0; i-- ) {
      for( j = 1; j < i; j++ ) {
         if( newPoly.term[j-1].exp < newPoly.term[j].exp ) {
            tempTerm = newPoly.term[j-1];
            newPoly.term[j-1] = newPoly.term[j];
            newPoly.term[j] = tempTerm;
         }
      }
   }

   return newPoly;
}


void addTerm(POLY* oldPoly, int coeff, int exp) {

   int i = 0;
   int length = getTermLength(*oldPoly);
   POLY newPoly = *oldPoly;

   while( i < length ) {
      if( exp == oldPoly->term[i].exp ) {
         break;
      }
      i++;
   }

   newPoly.term[i].coeff += coeff;
   newPoly.term[i].exp = exp;

   newPoly = bsortExp(newPoly);
   *oldPoly = newPoly;
}

void add(POLY poly1, POLY poly2, POLY* pSum) {

   int i, j;
   //POLY newPoly = *poly1;
   int poly1Len = getTermLength(poly1);
   int poly2Len = getTermLength(poly2);
   int pSumLen;
 
   clearTerm( pSum );
  
   for( i = 0; i < poly1Len; i++ ){
      pSum->term[i].coeff = poly1.term[i].coeff;    
      pSum->term[i].exp   = poly1.term[i].exp;
   }

   pSumLen = getTermLength(*pSum);

   for( i = 0; i < poly2Len; i++ ){
      for( j = 0; j < poly1Len; j++ ){

         if( poly1.term[j].exp == poly2.term[i].exp ) {
            pSum->term[j].coeff += poly2.term[i].coeff;
            break;

         }else if( j == (poly1Len-1) ){
           pSum->term[pSumLen].coeff = poly2.term[i].coeff;
           pSum->term[pSumLen].exp = poly2.term[i].exp;
           pSumLen++;
         }
      }
   }

   *pSum = bsortExp(*pSum);

}

void subtract(POLY poly1, POLY poly2, POLY* pDiff) {

   int i, j;
   //POLY newPoly = *poly1;
   int poly1Len = getTermLength(poly1);
   int poly2Len = getTermLength(poly2);
   int pDiffLen;
  
   clearTerm( pDiff );
  
   for( i = 0; i < poly1Len; i++ ){
      pDiff->term[i].coeff = poly1.term[i].coeff;    
      pDiff->term[i].exp   = poly1.term[i].exp;
   }

   pDiffLen = getTermLength(*pDiff);

   for( i = 0; i < poly2Len; i++ ){
      for( j = 0; j < poly1Len; j++ ){

         if( poly1.term[j].exp == poly2.term[i].exp ) {
            pDiff->term[j].coeff -= poly2.term[i].coeff;
            
            if( pDiff->term[j].coeff == 0 ) {
               pDiff->term[j].exp = -1;
            }
            break;

         }else if( j == (poly1Len-1) ){
           pDiff->term[pDiffLen].coeff = poly2.term[i].coeff * -1;
           pDiff->term[pDiffLen].exp = poly2.term[i].exp;
           pDiffLen++;
         }
      }
   }

   *pDiff = bsortExp(*pDiff);
 
}

void multiply(POLY* oldPoly, int multiplier) {

   int i = 0;
   int length = getTermLength(*oldPoly);
   POLY newPoly = *oldPoly;

   for( i = 0; i < length; i++ ) {
      newPoly.term[i].coeff *= multiplier;
   }

   *oldPoly = newPoly;
}

void displayPoly(POLY* poly) {
   int i = 0;
   int length = getTermLength(*poly);
   int coeff = poly->term[0].coeff;
   int exp = poly->term[0].exp;

   //Prints the first term
   if ( exp == -1 ) {
      printf("0");
   }else if ( exp == 0 ) {
      printf("%d", coeff);
   }else if ( exp == 1 ) {
      printf("%dx", coeff);
   }else {
      printf("%dx^%d", coeff, exp);
   }


   //Prints the preceding terms
   for(i = 1; i < length; i++ ) {
      coeff = poly->term[i].coeff;
      exp = poly->term[i].exp;

      if( exp == 0 && coeff != 0 ) {
         if( coeff < 0 ) {
            coeff *= -1;
            printf(" - %d", coeff);
         }else {
            printf(" + %d", coeff);
         }
      }else if ( exp == 1 && coeff != 0 ) {
         if( coeff < 0 ) {
            coeff *= -1;
            printf(" - %dx", coeff);
         }else {
            printf(" + %dx", coeff);
         }
      }else if ( coeff != 0 ) {
         if( coeff < 0 ) {
            coeff *= -1;
            printf(" - %dx^%d", coeff, exp);
         }else {
            printf(" + %dx^%d", coeff, exp);
         }
      }
   }
   printf("\n");
}
