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
        vector<vector<piece*>>  plateau; //Plateau avec les diff�rentes pi�ces restantes
    public:
        echiquier(); //Permet d'initialiser un plateau de d�but de jeu
        echiquier(vector<coup> liste);  //Permet de repr�senter le plateau apr�s un encha�nement de coup
        vector<vector<piece*>> getPlateau(){return plateau;} //Accesseur du plateau
        piece* getPiece(int i,int j){return plateau[i-1][j-1];} //Accesseur de la pi�ce aux coordonn�es i et j
        void print(); //Permet d'afficher le plateau
        bool isaPiece(int i, int j); //V�rifie si la case est vide
        int istwopawns();
};

#endif // ECHIQUIER_H
