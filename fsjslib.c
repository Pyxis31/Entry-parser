#include <stdio.h>
#include <stdlib.h>	// atoi, atof
#include <string.h>	// strlen, strcmp
#include <ctype.h>	// isdigit
#include "fsjslib.h"


// Vérifie si la chaîne de caractères saisie n'est pas vide et si elle représente un nombre entier ou un flottant
void fEntryIsIntOrFloat(sfEisIntFloat* psfEisIntFloat)
{
	// *********** Déclarations locales *************
	// *********** Fin de déclarations **************

	if (!strcmp(psfEisIntFloat->pcharEntry,""))
	{
		// L'entrée est vide
		psfEisIntFloat->errNumber=-1;
		psfEisIntFloat->pcharErrMessage="Entry is empty";
		psfEisIntFloat->intResult=0;
		psfEisIntFloat->doubleResult=0.0;
	}
	else if (!fIsIntOrFloat(psfEisIntFloat->pcharEntry,psfEisIntFloat->type))
	{
		// L'entrée est invalide
		psfEisIntFloat->errNumber=-2;
		psfEisIntFloat->intResult=0;
		psfEisIntFloat->doubleResult=0.0; 
		psfEisIntFloat->pcharErrMessage="Entry is invalid";
	}
	else if (atof(psfEisIntFloat->pcharEntry)<psfEisIntFloat->min || atof(psfEisIntFloat->pcharEntry)>psfEisIntFloat->max)
	{
		// L'entrée est hors limites
		psfEisIntFloat->errNumber=-3;
		psfEisIntFloat->pcharErrMessage="Entry is out of range";
		psfEisIntFloat->intResult=0;
		psfEisIntFloat->doubleResult=0.0;
	}
	else
	{
		// l'entrée est valide
		psfEisIntFloat->errNumber=0;
		psfEisIntFloat->pcharErrMessage="";
		
		if (psfEisIntFloat->type==typeInteger)
		{
			// La chaîne est convertie en Integer
			psfEisIntFloat->intResult=atoi(psfEisIntFloat->pcharEntry);
			psfEisIntFloat->doubleResult=0.0;
		}
		else
		{
			// La chaîne est convertie en double
			psfEisIntFloat->doubleResult=atof(psfEisIntFloat->pcharEntry);
			psfEisIntFloat->intResult=0;
		}
	}
}


// Vérifie que la chaîne de caractères ne contienne que des chiffres, un signe, un point
char fIsIntOrFloat(const char* pString,eType type)
{
	// *********** Déclarations locales *************	
	int loop ;
	int result=1;
	int sign=0;
	int dot=0;
	// *********** Fin de déclarations **************

	// Parcourt de la chaîne 
	for (loop=0 ; loop<strlen(pString) && result ; loop++)
	{
		// Analyse le nombre de signes et de points
		// Maxi. pour un entier : 1 signe, 0 point -- Maxi. pour un flottant : 1 signe, 1 point
		if (pString[loop]=='-')
		{
			sign++;
		}
		if (pString[loop]=='.')
		{
			dot++;
		}
		if ((type==typeInteger && (sign>1 || dot>0))||(type==typeFloat && (sign>1 || dot>1)))
		{
			result=0;
		}
		// Vérifie la position du signe : toujours en tête
		if ((pString[loop]=='-')&&loop>0)
		{
			result=0;
		}
		// Analyse chaque caractère : ni un chiffre, ni un signe, ni un point ?
		if (!isdigit(pString[loop]) && pString[loop]!='-' && pString[loop]!='.')
		{
			result=0;
		}
		// Analyse le 1er caractère
		if (loop==0)
		{

			// C'est un signe ou un point seul
			if ((pString[loop]=='-' || pString[loop]=='.') && strlen(pString)==1)
			{
				result=0;
			}
		}
		// Analyse le 2eme caractère
		else if (loop==1)
		{
			// C'est un point suivi d'aucun autre caractère
			if (pString[loop]=='.' && strlen(pString)==2)
			{
				result=0;
			}
		}
	}
	// Retourne 1 si la chaîne de caractères est conforme	
	return result;
}
