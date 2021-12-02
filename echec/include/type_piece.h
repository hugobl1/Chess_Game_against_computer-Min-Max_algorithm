#ifndef TYPE_PIECE_H
#define TYPE_PIECE_H
#include <vector>
using namespace std;

enum PIECE{Pion, Cavalier, Fou, Tour, Dame, Roi,None};
class type_piece
{
    private:
        PIECE type;
        int valeur;
        bool moved=false;
        vector<vector<int> > relativattack;
        vector<vector<int>> relativmove;

    public:
        type_piece():type(None),valeur(0){}
        type_piece(PIECE P, int v, vector<vector<int> > attack, vector<vector<int>> move):type(P),valeur(v), relativattack(attack),relativmove(move){}
        type_piece(const type_piece& P):type(P.type),valeur(P.valeur),relativattack(P.relativattack),relativmove(P.relativmove),moved(P.moved){}
        type_piece & operator=(const type_piece& t){type=t.type;valeur=t.valeur; relativattack=t.relativattack; relativmove=t.relativmove; moved=t.moved;return *this;}
        PIECE getPIECE(){return type;}
        int getValeur(){return valeur;}
        bool getMoved(){return moved;}
        void setMoved(bool c){moved=c;}
        vector<vector<int>> getAttack(){return relativattack;}
        vector<vector<int>> getMove(){return relativmove;}
        void setPIECE(PIECE t){type=t;}
        void setValeur(int v){valeur=v;}

};

#endif // TYPE_PIECE_H
