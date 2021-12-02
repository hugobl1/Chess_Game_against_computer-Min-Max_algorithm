#ifndef PIECE_H
#define PIECE_H
#include "type_piece.h"

class echiquier;
enum Lettre{a=1, b=2,c=3,d=4,e=5,f=6,g=7,h=8};
enum Couleur{Noir, Blanc};
class piece
{
    private:
        type_piece type;
        Couleur couleur;
        vector<int> position;

    public:
        piece():type(){}
        piece(type_piece t, Couleur c, vector<int> p):type(t),couleur(c),position(p){}
        piece(const piece& a){type=a.type;couleur=a.couleur; position=a.position;}
        Couleur getCouleur(){return couleur;}
        vector<int> getPosition(){return position;}
        type_piece getType(){return type;}
        void setCouleur(Couleur c){couleur=c;}
        void setType(type_piece t){type=t;}
        void setPosition(int i,int j){position=vector<int>(2);position[0]=i;position[1]=j;}
        piece& operator=(const piece& a){type=a.type;couleur=a.couleur; position=a.position; return *this;}
        int val();
        int control(echiquier chess);
        bool onBoard(vector<int> relativ); //vérifie si un coup relatif reste dans le plateau
        bool access(echiquier chess,vector<int> relativ); //vérifie si la pièce accès à une zone du plateau
        bool isanAlly(echiquier chess,vector<int> relativ);
        bool isanOpponent(echiquier chess,vector<int> relativ);
        bool accessMove(echiquier chess,vector<int> relativ);
        void print();

};

#endif // PIECE_H
