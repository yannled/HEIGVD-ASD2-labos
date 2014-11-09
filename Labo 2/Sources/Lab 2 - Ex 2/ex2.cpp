/*
 * File:   ex2.cpp
 * Author: Olivier Cuisenaire
 *
 * Created on 2 oct. 2014, 11:19:03
 */

#include <stdlib.h>
#include <iostream>

#include "GraphFromImage.h"
#include "ParcoursEnProfondeur.h"

int main(int argc, char** argv) {

    std::string filename("input.bmp");
    bitmap_image image(filename);

    if (!image) {
        std::cout << "test1 : Failed to open " << filename << ") \n";
        return (EXIT_FAILURE);
    }

    std::cout << "image size: " << image.width() << " x " << image.height() << "\n";

    ASD2::GraphFromImage G(image);
    ASD2::DFS<ASD2::GraphFromImage> dfs(G);

    //Question BONUS: Pourquoi n'utilisons-nous pas la methode visite pour parcourir l'image ?
    /*
     * Réponse:
     * la méthode visite ne fonctionne pas, car nous devons:
     * - redéfinir nous-mêmes ce qu'est un voisin (sommet UP/DOWN/LEFT/RIGHT de MEME couleur)
     * - appliquer le traitement désiré (application de la nouvelle couleur)
     */

    //on colore la carotte
    int x = 250, y = 400;
    dfs.iterativeVisit(G.idx(x, y), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 224, 128, 64);
    });

    //on ajoute une couleur de fond
    dfs.iterativeVisit(G.idx(0, 0), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 0, 255, 64);
    });

    /* toutes sortes d'ameliorations pour le output-custom.bmp
     * Coloration oreilles, feuille, coussinnets, yeux
     * 
    //on colore les oreilles et la langue en rose
    x = 240, y = 130;
    dfs.iterativeVisit(G.idx(x, y), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 255, 102, 204);
    });
    x = 130, y = 150;
    dfs.iterativeVisit(G.idx(x, y), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 255, 102, 204);
    });
    x = 225, y = 372;
    dfs.iterativeVisit(G.idx(x, y), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 255, 102, 204);
    });

    // on colorie la feuille en vert tres fonce
    x = 390, y = 280;
    dfs.iterativeVisit(G.idx(x, y), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 0, 102, 51);
    });

    // on colorie les coussinets des pattes en rose
    x = 94, y = 519;
    dfs.iterativeVisit(G.idx(x, y), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 255, 102, 204);
    });
    x = 130, y = 498;
    dfs.iterativeVisit(G.idx(x, y), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 255, 102, 204);
    });
    x = 127, y = 536;
    dfs.iterativeVisit(G.idx(x, y), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 255, 102, 204);
    });
    x = 317, y = 505;
    dfs.iterativeVisit(G.idx(x, y), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 255, 102, 204);
    });
    x = 94, y = 519;
    dfs.iterativeVisit(G.idx(x, y), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 255, 102, 204);
    });
    x = 309, y = 537;
    dfs.iterativeVisit(G.idx(x, y), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 255, 102, 204);
    });
    x = 343, y = 526;
    dfs.iterativeVisit(G.idx(x, y), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 255, 102, 204);
    });

    // on colorie les yeux en bleu
    x = 167, y = 301;
    dfs.iterativeVisit(G.idx(x, y), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 0, 204, 255);
    });
    x = 233, y = 280;
    dfs.iterativeVisit(G.idx(x, y), [&G, &image] (int v) {
        image.set_pixel(G.x(v), G.y(v), 0, 204, 255);
    });
     */

    //on sauve l'image modifiee
    image.save_image("output.bmp");


    //on charge l'image temoin pour verifier notre code
    bitmap_image image_gold("goal.bmp");

    
    /* Procedure de test: on constate tout d'abord que le psnr est extrèmement faible
     * ce qui signifie qu'elle sont très proches.
     * 
     * par ailleurs, la commande "diff output.png goal.png" 
     * renvoie "same files, no differences found" ce qui signifie que les deux fichiers
     * sont strictement identiques au bit près. 
     * Le changement d'un seul bit d'un des deux fichiers implique le retour de diff
     * "Binary files differ." ce qui renforce cette affirmation.
     * */
    if (image.psnr(image_gold) < 1000000)
        std::cout << "test failed - psnr = " << image.psnr(image_gold) << ") \n";
    else
        std::cout << "test succeeded - image is identical to goal.bmp\n";

    return (EXIT_SUCCESS);

}

