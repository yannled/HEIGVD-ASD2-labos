/*============================================================================
 * Name        : Labo1_tools.cpp
 * Date        : 12 juil. 2013
 * Author      : Fabien Dutoit
 * Version     : 1.0
 *
 * Description : Corrigé - Outils utiles pour le labo
 *============================================================================*/

#ifndef LABO1_TOOLS_CPP
#define	LABO1_TOOLS_CPP

#include "Labo1_tools.h"

/*
 * But: Méthode permettant de lire (et d'enlever) une partie d'un string
 */
std::string getInfo(std::string& ligne, char separateur)
{
	size_t index = ligne.find(separateur);
	std::string temp = ligne.substr(0,index);

	ligne = ligne.substr(index+1, ligne.length());

	return temp;
}

/*
 * But: Méthode permettant de spliter un string selon un séparateur
 */
std::string* splitInfo(std::string ligne, char separateur, int nbInfo)
{
	std::string* tab = new std::string[nbInfo];

	for(int i = 0; i < nbInfo; i++)
        {
                tab[i] = getInfo(ligne, separateur);
        }

	return tab;
}

/*
 * But: Créer la table de codage à partir d'un fichier texte
 * Entrée: nom du fichier .txt
 */
ArbreHuffman* creerTableDeCodageDeTexte(std::string filename)
{
    
    //la classe ArbreHuffman ne peut pas être instanciée
    //on fait donc un vecteur de pointeurs sur des arbres de Huffman
    std::vector<ArbreHuffman*> symboles;
    
    //ouverture du fichier
    std::ifstream fichier(filename.c_str(), std::ios::in | std::ios::binary);

    //buffer pour une ligne
    char c;
    
    bool symboleTrouve;
    
    //lire char par char
    if(fichier)
    {
        while ( fichier.get(c) )
        {
            symboleTrouve = false;
            for(int s = 0; s < symboles.size(); ++s) {
                ArbreHuffman* tmp = symboles[s];
                if(tmp->contient(c)) {
                    symboleTrouve = true;
                    tmp->incrementeFrequence();
                    break;
                }
            }

            if(!symboleTrouve) {
                //on doit créer une feuille pour ce symbole
                ArbreHuffmanFeuille* tmp = new ArbreHuffmanFeuille(c);
                symboles.push_back(tmp);
            }
        }

        //on ferme le fichier
        fichier.close();
    }
    
    //formation de l'arbre de huffman
    //la table de codage
    while(symboles.size() > 1) {
        //on trie les feuilles, le vecteur contenant des pointeurs:
        //- on ne peut pas utiliser les opérateurs standard pour le tri > et <
        //- on doit donc fournir à la méthode sort une fonction de comparaison
        //- on utilise une lambda (fonction anonyme)
        std::sort(symboles.begin(), symboles.end(), [](ArbreHuffman* a, ArbreHuffman* b) {
            return b->getFrequence() > a->getFrequence();   
        });
        
        //on crée une nouvelle branche qui accueillera les 2 sous-arbres de plus petite fréquences
        ArbreHuffman* tmpBranche = new ArbreHuffmanBranche();
        
        //on y accroche les deux arbres de moindre fréquences
        //placés au début du vecteur après le tri
        tmpBranche->accrocheGauche(symboles[0]);
        tmpBranche->accrocheDroite(symboles[1]);
        
        //on les supprime du vecteur
        symboles.erase(symboles.begin());
        symboles.erase(symboles.begin());
        
        //on ajoute la nouvelle branche au vecteur
        symboles.push_back(tmpBranche);
    }

    //il ne reste plus qu'un arbre dans le vecteur
    //il s'agit de notre table de codage
    return symboles[0];
}

/*
 * But: Créer la table de codage à partir d'un string
 * Entrée: string (typiquement la première ligne du fichier compressé)
 */
ArbreHuffman* creerTableDeCodageDeString(std::string serialisation) {
    ArbreHuffman* racine = nullptr;
   
    //cas problématiques
    if(serialisation.empty()) return racine;
    
    //cas d'une branche
    if(serialisation[0] == '(' && serialisation[serialisation.length() -1] == ')') {
        //on enlève les parenthèse utilisées
        serialisation = serialisation.substr(1, serialisation.length() -2);
        
        //on récupère les 2 sous-arbres
        //on doit trouver le séparateur séparant les 2 arbres
        //c'est le caractère ; situé entre 2 groupe de parenthèses "équilibrées"
        int nbrParentheseOuvertes = 0;
        int posSeparateur = -1;
        for(int i = 0; i < serialisation.length(); ++i) {
            char courant = serialisation[i];
            
            switch(courant) {
                case '(':
                case '[':
                    ++nbrParentheseOuvertes;
                    break;
                case ')':
                case ']':
                    --nbrParentheseOuvertes;
                    break;
                case ';':
                    if(nbrParentheseOuvertes  == 0 ) {
                        //on a trouvé le séparateur
                        posSeparateur = i;
                    }
                    break;
            }
            
        }
        
        std::string sousarbregauche = serialisation.substr(0, posSeparateur);
        std::string sousarbredroite = serialisation.substr(posSeparateur + 1);
      
        //on crée les 2 sous-arbres
        ArbreHuffman* gauche = creerTableDeCodageDeString(sousarbregauche);
        ArbreHuffman* droite = creerTableDeCodageDeString(sousarbredroite);
        
        //on crée la branche
        racine = new ArbreHuffmanBranche();
        
        //on y accroche les 2 sous-arbres
        racine->accrocheGauche(gauche);
        racine->accrocheDroite(droite);
        
    }
    else if(serialisation[0] == '[' && serialisation[serialisation.length() -1] == ']') {
        //on enlève les parenthèse utilisées
        serialisation = serialisation.substr(1, serialisation.length() -2);
        //on récupère les 2 paramètres
        std::string* params = splitInfo(serialisation, ';', 2);
 
        //caractère
        char c;
        if(params[0].length() > 1) {
            //cas spéciaux
            if(params[0] == "\\n")
                c = '\n';
            else if(params[0] == "\\r")
                c = '\r';
            else if(params[0] == "\\po")
                c = '(';
            else if(params[0] == "\\pf")
                c = ')';
            else if(params[0] == "\\co")
                c = '[';
            else if(params[0] == "\\cf")
                c = ']';
            else if(params[0] == "\\pv")
                c = ';';
        } else {
            c = params[0][0];
        }
        
        //fréquence
        long freq = atol(params[1].c_str());
        
        racine = new ArbreHuffmanFeuille(c);
        racine->setFrequence(freq);
        
        delete params;
    } else {
        //problème
        std::cout << "Probleme de deserialisation de l'arbre: " << serialisation << std::endl;
        std::cout << "Premier: '" << serialisation[0] << "'" << std::endl;
        std::cout << "Longueur: '" << serialisation.length() << "'" << std::endl;
        std::cout << "Dernier: '" << serialisation[serialisation.length()-2] << "'" << std::endl;
    }
    
    return racine;
}


/*
 * But: Compresser un fichier texte
 * Entrées: nom du fichier à compresser
 *          nom du fichier ou écrire le résultat de la compression
 */
void compresser(std::string aCompresser, std::string sortie) {
    
    //la première étape consiste à générer la table de codage
    ArbreHuffman* table = creerTableDeCodageDeTexte(aCompresser);
    
    //ouverture du fichier
    std::ifstream fichierIn(aCompresser.c_str(), std::ios::in | std::ios::binary);
    //on ouvre le fichier en sortie
    std::ofstream fichierOut(sortie.c_str(), std::ios::out | std::ios::binary);
    
    if(fichierIn.is_open() && fichierOut.is_open()) {
        
        //on écrit la table de codage sur la première ligne
        fichierOut << table->toString() << std::endl;
        
        //on écrit le nombre de caractères sur la seconde
        fichierOut << table->getFrequence() << std::endl;
        
        //compression
        char c;
        std::vector<bool> buffer;
        
        //on lit le fichier à compresser
        //caractère par caractère
        while ( fichierIn.get(c) ) {
            
            std::vector<bool> bitsC = table->compresse(c);
            
            //on place les bits à la fin du buffer
            buffer.insert(buffer.end(), bitsC.begin(), bitsC.end());
            
            //on va écrire les bits 8 par 8
            while(buffer.size() >= 8) {
                
                char byte = 0;
                
                for(int i = 0; i < 8; ++i) {
                    bool b = buffer[0];
                    buffer.erase(buffer.begin());
                    byte |= (char) b << (7-i);
                }
                fichierOut << byte;
            }
        }
        
        //s'il reste des bits, on va les écrire (+ éventuellement padding avec des 0)
        if(buffer.size() > 0) {
                char byte = 0;
                for(int i = 0; i < 8; ++i) {
                    bool b = 0;
                    if(buffer.size() > 0) {
                        b = buffer[0];
                        buffer.erase(buffer.begin());
                    }
                    byte |= (char) b << (7-i);
                }
                fichierOut << byte;
        }
        
        //on ferme les fichiers
        fichierIn.close();
        fichierOut.close();
    }
    
    delete table;
}

/*
 * But: Déompresser un fichier texte
 * Entrées: nom du fichier à décompresser
 *          nom du fichier ou écrire le résultat de la décompression
 */
void decompresser(std::string aDeCompresser, std::string sortie) {
    
    long nbrCaracteres = 0, nbrCaracteresEcrits = 0;
    
    //ouverture du fichier
    std::ifstream fichierIn(aDeCompresser.c_str(), std::ios::in | std::ios::binary);
    if(!fichierIn.is_open()) return;
    
    std::string ligne;
    
    // première étape: consiste à récupérer la table de codage sur la première ligne du fichier
    if(!std::getline( fichierIn, ligne )){
       //problème lors de la lecture de la 1ere ligne
       return;
    }
    
    //on enlève les éventuels caractères de fin de ligne
    while(ligne[ligne.length()-1] == '\n' || ligne[ligne.length()-1] == '\r') {
        ligne = ligne.substr(0, ligne.length() -1);
    }
    
    //on récupère la table de décompression
    ArbreHuffman* table = creerTableDeCodageDeString(ligne);
    
    // seconde étape: consiste à récupérer le nombre de caractères sur la seconde ligne
    if(!std::getline( fichierIn, ligne )){
       //problème lors de la lecture de la 1ere ligne
       return;
    }

    nbrCaracteresEcrits = atol(ligne.c_str());
    
    //on ouvre le fichier en sortie
    std::ofstream fichierOut(sortie.c_str(), std::ios::out | std::ios::binary);
    
    if(!fichierOut.is_open()) return;
    
    //décompression
    char c[1];
    std::vector<bool> buffer;
    bool dernierPassage = false;
    
    while(fichierIn.good()) {
        
        while(!dernierPassage) {
            try {
                //on décompresse un caractére
                char caracterDecompresse = table->decompresse(&buffer);
                //on l'ecrit uniquement s'il doit l'etre
                if(nbrCaracteresEcrits > nbrCaracteres) {
                    fichierOut << caracterDecompresse;
                    ++nbrCaracteres;               
                }
            } 
            catch(BitStreamTropCourt) {

                if(!fichierIn.good()) {
                    dernierPassage = true;
                    continue;
                }
                
                //on doit remplir le buffer, on va lire
                fichierIn.read(c, 1);

                std::vector<bool> tmpbuffer;

                for(int i = 0; i < 8; ++i) {

                    bool b = c[0] & 1;
                    c[0] = c[0] >> 1;

                    tmpbuffer.insert(tmpbuffer.begin(), b);
                }

                //on place les bits du buffer temporaire à la fin du buffer
                buffer.insert(buffer.end(), tmpbuffer.begin(), tmpbuffer.end());
            }
        }
    }
    
    fichierIn.close();
    fichierOut.close();
    
    delete table;    
}

#endif	/* LABO1_TOOLS_CPP */
