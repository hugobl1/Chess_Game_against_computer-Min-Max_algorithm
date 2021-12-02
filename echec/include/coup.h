#ifndef COUP_H
#define COUP_H
#include "piece.h"

enum special{PR, GR, Usual };

class coup
{
    public:
        piece playpiece;
        vector<int> lastpos;
        vector<int> newpos;
        piece pieceprise;
        special coupspecial;
        coup();
        coup(piece p,vector<int> a, vector<int> b,piece prise, special c){playpiece=p; lastpos=a; newpos=b;pieceprise=prise;coupspecial=c;}
        piece getPlaypiece(){return playpiece;} //Retourne la pièce joué par ce coup
};

#endif // COUP_H

