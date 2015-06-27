/*============================================================================
 * Name        : ArbreHuffmanBranche.cpp
 * Date        : 18 juil. 2013
 * Author      : Fabien Dutoit
 * Version     : 1.0
 *
 * Description : Classe représentant un arbre de Huffman
 *               Implémentation d'une branche contenant deux sous arbres
 *============================================================================*/

#ifndef ARBREHUFFMANBRANCHE_CPP
#define	ARBREHUFFMANBRANCHE_CPP

#include <vector>

#include "ArbreHuffmanBranche.h"

/*
 * Constructeur d'un arbre vide
 */
ArbreHuffmanBranche::ArbreHuffmanBranche() {
    /*A IMPLEMENTER*/
   
   this->droite = nullptr;
   this->gauche = nullptr;
   
   
}
/*
 * But: Vérifie si le caractère appartient à l'arbre
 * Entrée: Le caractère dont la présence doit être vérifiée
 * Sortie: Booléen indiquant la présence
 */
bool ArbreHuffmanBranche::contient(char caracter) {
    /*A IMPLEMENTER*/
   
   if((this->droite != nullptr) && (this->gauche !=nullptr)){
      
       return(this->gauche->contient(caracter) || this->droite->contient(caracter));           
   }
   else{
      return false;
   }
   
}

/*
 * But: Obtenir la fréquence des caractères contenu dans cet arbre
 * Exception: SousArbreVide si au moins un des sous-arbres est non-défini
 */
long ArbreHuffmanBranche::getFrequence() const {
    /*A IMPLEMENTER*/
   
   if((this->droite != nullptr) && (this->gauche !=nullptr)){
      
      return this->droite->getFrequence()+ this->gauche->getFrequence();

   }
   else{
      throw SousArbreVide();
   }
}

/*
 * But: Setter une valeur de fréquence particulière
 * Entrée: valeur de la fréquence
 * Exception: OperationUniquementPossibleSurUneFeuille si appliqué sur une branche
 */
void ArbreHuffmanBranche::setFrequence(long freq){
    /*A IMPLEMENTER*/
   
   throw OperationUniquementPossibleSurUneFeuille();
}

/*
 * But: Opération permettant d'incrémenter la fréquence d'un élément
 * Exception: OperationUniquementPossibleSurUneFeuille si appliqué sur une branche
 */
void ArbreHuffmanBranche::incrementeFrequence() {
    /*A IMPLEMENTER*/
   
   throw OperationUniquementPossibleSurUneFeuille();
}

/*
 * But: Opérations permettant d'accrocher un sous-arbre à gauche ou a droite de l'arbre courant
 * Exception: OperationUniquementPossibleSurUneBranche si appliqué sur une feuille
 */
void ArbreHuffmanBranche::accrocheGauche(ArbreHuffman* sousArbre) {
    /*A IMPLEMENTER*/
   
   this->gauche = sousArbre;
   
   
}

void ArbreHuffmanBranche::accrocheDroite(ArbreHuffman* sousArbre) {
    /*A IMPLEMENTER*/
   this->droite = sousArbre;
}

/*
 * But: Sérialisation de l'arbre
 * Exception: SousArbreVide si au moins un des sous-arbres est non-défini
 */
std::string ArbreHuffmanBranche::toString() {
    if(gauche == nullptr || droite == nullptr){
        throw SousArbreVide();
    }
    
    std::stringstream sstrings;
    sstrings << "(" << gauche->toString() << ";" << droite->toString() << ")";
    return sstrings.str();
}

/*
 * But: Compresser un caractère
 * Entrée: Le caractère à encoder
 * Sortie: Un vecteur représentant les bits correspondant au caractère
 * Exception: SousArbreVide si au moins un des sous-arbres est non-défini
 *            ProblemeEncodage en cas d'erreur d'encodage (caractère manquant pas ex.)
 */
std::vector<bool> ArbreHuffmanBranche::compresse(char caractere)
{
    /*A IMPLEMENTER*/
   std::vector<bool> encodage;
   std::vector<bool> buffer;
   
   //std::cout << "char: " << caractere << " ";
   
   if((this->droite != nullptr) && (this->gauche !=nullptr)){
      
      if(this->gauche->contient(caractere)){ //0
         encodage.push_back(false);
         //std::cout << "false \n";
         buffer = this->gauche->compresse(caractere);
         
         for(int i=0; i< buffer.size(); i++)
            encodage.push_back(buffer.at(i));
         
         
         
      }
      else if(this->droite->contient(caractere)){ //1
         encodage.push_back(true);
         //std::cout << "true \n";
         buffer = this->droite->compresse(caractere);
        
        for(int i=0; i< buffer.size(); i++)
            encodage.push_back(buffer.at(i));
      }
      else{
         throw ProblemeEncodage();
      }
      
   }
   else{
      throw SousArbreVide();
   }
   
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
char ArbreHuffmanBranche::decompresse(std::vector<bool>* bits) {
    /*A IMPLEMENTER*/
   
   if((this->droite != nullptr) && (this->gauche !=nullptr)){
      
      if(bits->empty()){
         throw BitStreamTropCourt();
      }
                  
      bool flag = bits->front();
      //std::cout << "flag: " << flag << " bitstream: " << std::endl;
      
      /*for(size_t i =0; i< bits->size(); i++)
         std::cout << bits->at(i);*/
      //std::cout << std::endl;
      
      bits->erase(bits->begin());
      
      try{
         if(!flag){ // gauche

            return this->gauche->decompresse(bits);
         }
         else{ // droite

            return this->droite->decompresse(bits);
         }
      }
      catch(BitStreamTropCourt e){
         
         bits->insert(bits->begin(), flag);
         throw BitStreamTropCourt();
         
      }
      
      
   }
   else{
      throw SousArbreVide();
   }
      
   
}

/*
 * Destructeur
 * Détruit récursivement tout l'arbre
 */
ArbreHuffmanBranche::~ArbreHuffmanBranche() {
    /*A IMPLEMENTER*/
}

#endif	/* ARBREHUFFMANBRANCHE_CPP */
