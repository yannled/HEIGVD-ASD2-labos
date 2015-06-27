/*============================================================================
 * Name        : ArbreHuffman.h
 * Date        : 18 juil. 2013
 * Author      : Fabien Dutoit
 * Version     : 1.0
 *
 * Description : Classe abstraite représentant un arbre de Huffman
 *============================================================================*/

#ifndef ARBREHUFFMAN_H
#define	ARBREHUFFMAN_H

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

//Exceptions
class OperationUniquementPossibleSurUneFeuille {};
class OperationUniquementPossibleSurUneBranche {};
class PositionDejaOccupee {};
class SousArbreVide{};
class ProblemeEncodage{};
class BitStreamTropCourt{};

class ArbreHuffman {
public:

    /*
     * But: Vérifie si le caractère appartient à l'arbre
     * Entrée: Le caractère dont la présence doit être vérifiée
     * Sortie: Booléen indiquant la présence
     */
    virtual bool contient(char caracter) = 0;
    
    /*
     * But: Obtenir la fréquence des éléments contenu dans cet arbre
     * Exception: SousArbreVide si au moins un des sous-arbres est non-défini
     */
    virtual long getFrequence() const = 0;
    
    /*
     * But: Setter une valeur de fréquence particulière
     * Entrée: valeur de la fréquence
     * Exception: OperationUniquementPossibleSurUneFeuille si appliqué sur une branche
     */
    virtual void setFrequence(long freq) = 0;
    
    /*
     * But: Opération permettant d'incrémenter la fréquence d'un élément
     * Exception: OperationUniquementPossibleSurUneFeuille si appliqué sur une branche
     */
    virtual void incrementeFrequence() = 0;
    
    /*
     * But: Opérations permettant d'accrocher un sous-arbre à gauche ou a droite de l'arbre courant
     * Exception: OperationUniquementPossibleSurUneBranche si appliqué sur une feuille
     *            PositionDejaOccupee si position déjà occupée
     */
    virtual void accrocheGauche(ArbreHuffman* sousArbre) = 0;
    virtual void accrocheDroite(ArbreHuffman* sousArbre) = 0;
    
    /*
     * But: Sérialisation de l'arbre
     * Exception: SousArbreVide si au moins un des sous-arbres est non-défini
     */
    virtual std::string toString() = 0;
    
    /*
     * But: Compresser un caractère
     * Entrée: Le caractère à encoder
     * Sortie: Une vecteur représentant les bits correspondant au caractère
     * Exceptions: SousArbreVide si au moins un des sous-arbres est non-défini
     *             ProblemeEncodage en cas d'erreur d'encodage (caractère manquant pas ex.)
     */
    virtual std::vector<bool> compresse(char caractere) = 0;
    
    /*
     * But: Décompresser un caractère
     * Entrée: Un pointeur sur le vecteur de bits à utiliser
     *         Les bits utilisés seront consommés, en cas de problème (par ex.: BitStreamTropCourt) le vecteur ne doit pas être modifié
     * Sortie: Le caractère décompressé
     * Exceptions: SousArbreVide si au moins un des sous-arbres est non-défini
     *             BitStreamTropCourt si le vecteur de bits est trop court pour déterminer un unique caractère             
     */
    virtual char decompresse(std::vector<bool>* bits) = 0;
};

#endif	/* ARBREHUFFMAN_H */

