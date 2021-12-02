#ifndef ECHIQUIER_H
#define ECHIQUIER_H
#include "piece.h"
#include "coup.h"
#include <iostream>
#include <vector>

using namespace std;


class echiquier
{
    private:
        vector<vector<piece*>>  plateau; //Plateau avec les différentes pièces restantes
    public:
        echiquier(); //Permet d'initialiser un plateau de début de jeu
        echiquier(vector<coup> liste);  //Permet de représenter le plateau après un enchaînement de coup
        vector<vector<piece*>> getPlateau(){return plateau;} //Accesseur du plateau
        piece* getPiece(int i,int j){return plateau[i-1][j-1];} //Accesseur de la pièce aux coordonnées i et j
        void print(); //Permet d'afficher le plateau
        bool isaPiece(int i, int j); //Vérifie si la case est vide
        int istwopawns();
};

#endif // ECHIQUIER_H
