/*============================================================================
 * Name        : Labo1_tools.h
 * Date        : 12 juil. 2013
 * Author      : Fabien Dutoit
 * Version     : 1.0
 *
 * Description : Corrigé - Outils utiles pour le labo
 *============================================================================*/

#ifndef LABO1_TOOLS_H
#define	LABO1_TOOLS_H

#include <iostream>
#include <stdlib.h>
#include <fstream> //lecture/ecriture fichiers

//utilisé pour trimer les strings
//et le mettre en minuscule
#include <algorithm>
#include <string>

#include <ctime>

#include "ArbreHuffmanFeuille.h"
#include "ArbreHuffmanBranche.h"

/*
 * But: Créer la table de codage à partir d'un fichier texte
 * Entrée: nom du fichier .txt
 */
ArbreHuffman* creerTableDeCodageDeTexte(std::string filename);

/*
 * But: Créer la table de codage à partir d'un string
 * Entrée: string (typiquement la première ligne du fichier compressé)
 */
ArbreHuffman* creerTableDeCodageDeString(std::string serialisation);


/*
 * But: Compresser un fichier texte
 * Entrées: nom du fichier à compresser
 *          nom du fichier ou écrire le résultat de la compression
 */
void compresser(std::string aCompresser, std::string sortie);

/*
 * But: Déompresser un fichier texte
 * Entrées: nom du fichier à décompresser
 *          nom du fichier ou écrire le résultat de la décompression
 */
void decompresser(std::string aDeCompresser, std::string sortie);

#endif	/* LABO1_TOOLS_H */

