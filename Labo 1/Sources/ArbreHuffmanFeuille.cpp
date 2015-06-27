/*============================================================================
 * Name        : ArbreHuffmanFeuille.cpp
 * Date        : 18 juil. 2013
 * Author      : Fabien Dutoit
 * Version     : 1.0
 *
 * Description : Classe représentant un arbre de Huffman
 *               Implémentation d'une feuille contenant un élément
 *============================================================================*/

#ifndef ARBREHUFFMANFEUILLE_CPP
#define	ARBREHUFFMANFEUILLE_CPP

#include <sstream>

#include "ArbreHuffmanFeuille.h"

/*
 * Constructeur d'une feuille avec un caractère
 * Entrée: Le caractère qui sera contenu sur la feuille
 */
ArbreHuffmanFeuille::ArbreHuffmanFeuille(char caracter) {
    /*A IMPLEMENTER*/
  this->caracter = caracter;
  this->frequence = 1;
}
    
/*
 * But: Vérifie si le caractère appartient à l'arbre
 * Entrée: Le caractère dont la présence doit être vérifiée
 * Sortie: Booléen indiquant la présence
 */
bool ArbreHuffmanFeuille::contient(char caracter) {
    /*A IMPLEMENTER*/
   return this->caracter == caracter;
}

/*
 * But: Obtenir la fréquence des éléments contenu dans cet arbre
 * Exception: SousArbreVide si au moins un des sous-arbres est non-défini
 */
long ArbreHuffmanFeuille::getFrequence() const {
    /*A IMPLEMENTER*/
   return this->frequence;
}

/*
 * But: Setter une valeur de fréquence particulière
 * Entrée: valeur de la fréquence
 * Exception: OperationUniquementPossibleSurUneFeuille si appliqué sur une branche
 */
void ArbreHuffmanFeuille::setFrequence(long freq){
    /*A IMPLEMENTER*/
   this->frequence = freq;
}

/*
 * But: Opération permettant d'incrémenter la fréquence d'un élément
 * Exception: OperationUniquementPossibleSurUneFeuille si appliqué sur une branche
 */
void ArbreHuffmanFeuille::incrementeFrequence() {
    /*A IMPLEMENTER*/
   this->frequence++;
}

/*
 * But: Opérations permettant d'accrocher un sous-arbre à gauche ou a droite de l'arbre courant
 * Exception: OperationUniquementPossibleSurUneBranche si appliqué sur une feuille
 */
void ArbreHuffmanFeuille::accrocheGauche(ArbreHuffman* sousArbre) {
    /*A IMPLEMENTER*/
   throw OperationUniquementPossibleSurUneBranche();
   
}

void ArbreHuffmanFeuille::accrocheDroite(ArbreHuffman* sousArbre) {
    /*A IMPLEMENTER*/
   throw OperationUniquementPossibleSurUneBranche();
}

/*
 * But: Sérialisation de l'arbre
 * Exception: SousArbreVide si au moins un des sous-arbres est non-défini
 */
std::string ArbreHuffmanFeuille::toString() {
    
    std::string sortie(1, caracter);
    
    //pour ne pas casser la structure de la sortie, on va devoir 
    //redéfinir les caractères spéciaux
    switch(caracter) {
        case '\r':
            sortie = "\\r";
            break;
        case '\n':
            sortie = "\\n";
            break;
        case '[':
            sortie = "\\co";
            break;
        case '(':
            sortie = "\\po";
            break;
        case ']':
            sortie = "\\cf";
            break;
        case ')':
            sortie = "\\pf";
            break;
        case ';':
            sortie = "\\pv";
            break;
    }
    
    std::stringstream sstrings;
    sstrings << "[" << sortie << ";" << frequence << "]";
    return sstrings.str();
}

/*
 * But: Compresser un caractère
 * Entrée: Le caractère à encoder
 * Sortie: Un vecteur représentant les bits correspondant au caractère
 * Exception: SousArbreVide si au moins un des sous-arbres est non-défini
 *            ProblemeEncodage en cas d'erreur d'encodage (caractère manquant pas ex.)
 */
std::vector<bool> ArbreHuffmanFeuille::compresse(char caractere)
{
    /*A IMPLEMENTER*/
   if(caractere != this->caracter){
       throw ProblemeEncodage();
   }
   std::vector<bool> encodage;
   return encodage;
}

/*
 * But: Décompresser un caractère
 * Entrée: Un pointeur sur le vecteur de bits à utiliser
 *         Les bits utilisés seront consommés, en cas de problème (par ex.: BitStreamTropCourt) le vecteur ne doit pas être modifié
 * Sortie: Le caractère décompressé
 * Exceptions: SousArbreVide si au moins un des sous-arbres est non-défini
 *             BitStreamTropCourt si le vecteur de bits est trop court pour déterminer un unique caractère             
 */
char ArbreHuffmanFeuille::decompresse(std::vector<bool>* bits) {
    /*A IMPLEMENTER*/
   
   
   return this->caracter;
}

/*
 * Destructeur
 * Détruit la feuille
 */
ArbreHuffmanFeuille::~ArbreHuffmanFeuille() {}

#endif	/* ARBREHUFFMANFEUILLE_CPP */
