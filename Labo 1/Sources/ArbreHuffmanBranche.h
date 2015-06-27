/*============================================================================
 * Name        : ArbreHuffmanBranche.h
 * Date        : 18 juil. 2013
 * Author      : Fabien Dutoit
 * Version     : 1.0
 *
 * Description : Classe représentant un arbre de Huffman
 *               Implémentation d'une branche contenant deux sous arbres
 *============================================================================*/

#ifndef ARBREHUFFMANBRANCHE_H
#define	ARBREHUFFMANBRANCHE_H

#include <string>
#include <sstream>

#include "ArbreHuffman.h"

class ArbreHuffmanBranche : public ArbreHuffman  {
public:
    
    /*
     * Constructeur d'une branche vide
     */
    ArbreHuffmanBranche();
    
    /*
     * But: Vérifie si le caractère appartient à l'arbre
     * Entrée: Le caractère dont la présence doit être vérifiée
     * Sortie: Booléen indiquant la présence
     */
    virtual bool contient(char caracter);
    
    /*
     * But: Obtenir la fréquence des caractères contenu dans cet arbre
     * Exception: SousArbreVide si au moins un des sous-arbres est non-défini
     */
    virtual long getFrequence() const;
    
    /*
     * But: Setter une valeur de fréquence particulière
     * Entrée: valeur de la fréquence
     * Exception: OperationUniquementPossibleSurUneFeuille si appliqué sur une branche
     */
    virtual void setFrequence(long freq);
    
    /*
     * But: Opération permettant d'incrémenter la fréquence d'un caractère
     * Exception: OperationUniquementPossibleSurUneFeuille si appliqué sur une branche
     */
    virtual void incrementeFrequence();
    
    /*
     * But: Opérations permettant d'accrocher un sous-arbre à gauche ou a droite de l'arbre courant
     * Exception: OperationUniquementPossibleSurUneBranche si appliqué sur une feuille
     *            PositionDejaOccupee si position déjà occupée
     */
    virtual void accrocheGauche(ArbreHuffman* sousArbre);
    virtual void accrocheDroite(ArbreHuffman* sousArbre);
    
    /*
     * But: Sérialisation de l'arbre
     * Exception: SousArbreVide si au moins un des sous-arbres est non-défini
     */
    virtual std::string toString();
    
    /*
     * But: Compresser un caractère
     * Entrée: Le caractère à encoder
     * Sortie: Un vecteur représentant les bits correspondant au caractère
     * Exception: SousArbreVide si au moins un des sous-arbres est non-défini
     *            ProblemeEncodage en cas d'erreur d'encodage (caractère manquant pas ex.)
     */
    virtual std::vector<bool> compresse(char caractere);
    
    /*
     * But: Décompresser un caractère
     * Entrée: Un pointeur sur le vecteur de bits à utiliser
     *         Les bits utilisés seront consommés, en cas de problème (par ex.: BitStreamTropCourt) le vecteur ne doit pas être modifié
     * Sortie: Le caractère décompressé
     * Exceptions: SousArbreVide si au moins un des sous-arbres est non-défini
     *             BitStreamTropCourt si le vecteur de bits est trop court pour déterminer un unique caractère             
     */
    virtual char decompresse(std::vector<bool>* bits);
    
    /*
     * Destructeur
     * Détruit récursivement tout l'arbre
     */
    virtual ~ArbreHuffmanBranche();

private:
    ArbreHuffman* gauche;
    ArbreHuffman* droite;
};

#endif	/* ARBREHUFFMANBRANCHE_H */

