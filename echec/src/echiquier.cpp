#include "echiquier.h"

vector<vector<int>> attackF{{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{-1,-1},{-2,-2},{-3,-3},{-4,-4},{-5,-5},{-6,-6},{-7,-7},{-1,1},{-2,2},{-3,3},{-4,4},{-5,5},{-6,6},{-7,7},{1,-1},{2,-2},{3,-3},{4,-4},{5,-5},{6,-6},{7,-7}};
vector<vector<int>> attackC{{1,2},{2,1},{-1,2},{-2,1},{-1,-2},{-2,-1},{1,-2},{2,-1}};
vector<vector<int>> attackT{{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{-1,0},{-2,0},{-3,0},{-4,0},{-5,0},{-6,0},{-7,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,-1},{0,-2},{0,-3},{0,-4},{0,-5},{0,-6},{0,-7}};
vector<vector<int>> attackD{{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{-1,-1},{-2,-2},{-3,-3},{-4,-4},{-5,-5},{-6,-6},{-7,-7},{-1,1},{-2,2},{-3,3},{-4,4},{-5,5},{-6,6},{-7,7},{1,-1},{2,-2},{3,-3},{4,-4},{5,-5},{6,-6},{7,-7},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{-1,0},{-2,0},{-3,0},{-4,0},{-5,0},{-6,0},{-7,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,-1},{0,-2},{0,-3},{0,-4},{0,-5},{0,-6},{0,-7}};
vector<vector<int>> attackR{{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{-1,1},{1,-1}};
vector<vector<int>> attackPn{{-1,-1},{1,-1}};
vector<vector<int>> attackPb{{1,1},{-1,1}};

vector<vector<int>> moveF{{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{-1,-1},{-2,-2},{-3,-3},{-4,-4},{-5,-5},{-6,-6},{-7,-7},{-1,1},{-2,2},{-3,3},{-4,4},{-5,5},{-6,6},{-7,7},{1,-1},{2,-2},{3,-3},{4,-4},{5,-5},{6,-6},{7,-7}};
vector<vector<int>> moveC{{1,2},{2,1},{-1,2},{-2,1},{-1,-2},{-2,-1},{1,-2},{2,-1}};
vector<vector<int>> moveT{{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{-1,0},{-2,0},{-3,0},{-4,0},{-5,0},{-6,0},{-7,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,-1},{0,-2},{0,-3},{0,-4},{0,-5},{0,-6},{0,-7}};
vector<vector<int>> moveD{{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{-1,-1},{-2,-2},{-3,-3},{-4,-4},{-5,-5},{-6,-6},{-7,-7},{-1,1},{-2,2},{-3,3},{-4,4},{-5,5},{-6,6},{-7,7},{1,-1},{2,-2},{3,-3},{4,-4},{5,-5},{6,-6},{7,-7},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{-1,0},{-2,0},{-3,0},{-4,0},{-5,0},{-6,0},{-7,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,-1},{0,-2},{0,-3},{0,-4},{0,-5},{0,-6},{0,-7}};
vector<vector<int>> moveR{{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{-1,1},{1,-1}};
vector<vector<int>> movePn{{0,-1}};
vector<vector<int>> movePb{{0,1}};

echiquier::echiquier()
{
    plateau= vector<vector<piece*> >(8, vector<piece*>(8));
    for(int j=0;j<=7;j++)
    {
        switch(j){
        case 0:
            for(int i=0;i<=7;i++)
            {
                plateau[i][j]=new piece;
                plateau[i][j]->setCouleur(Blanc);
                plateau[i][j]->setPosition(i+1,j+1);
                switch(i){
                case(0):
                    {
                    type_piece auxtpiece(Tour,5,attackT,moveT);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(1):
                    {
                    type_piece auxtpiece(Cavalier,3,attackC, moveC);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(2):
                    {
                    type_piece auxtpiece(Fou,3,attackF, moveF);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(3):
                    {
                    type_piece auxtpiece(Dame,9,attackD, moveD);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(4):
                    {
                    type_piece auxtpiece(Roi,0,attackR,moveR);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(5):
                    {
                    type_piece auxtpiece(Fou,3,attackF,moveF);
                    plateau[i][j]->setType(auxtpiece);
                    }

                    break;
                case(6):
                    {
                    type_piece auxtpiece(Cavalier,3,attackC,moveC);
                    plateau[i][j]->setType(auxtpiece);
                    }

                    break;
                case(7):
                    {
                    type_piece auxtpiece(Tour,5,attackT,moveT);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                }
            }
            break;
        case 1:
            for(int i=0;i<=7;i++)
            {
                plateau[i][j]=new piece;
                plateau[i][j]->setCouleur(Blanc);
                plateau[i][j]->setPosition(i+1,j+1);
                type_piece auxtpiece(Pion,1,attackPb,movePb);
                plateau[i][j]->setType(auxtpiece);
            }
            break;
        case 6:
            for(int i=0;i<=7;i++)
            {
                plateau[i][j]=new piece;
                plateau[i][j]->setCouleur(Noir);
                plateau[i][j]->setPosition(i+1,j+1);
                type_piece auxtpiece(Pion,1,attackPn,movePn);
                plateau[i][j]->setType(auxtpiece);
            }
            break;
        case 7:
            for(int i=0;i<=7;i++)
            {
                plateau[i][j]=new piece;
                plateau[i][j]->setCouleur(Noir);
                plateau[i][j]->setPosition(i+1,j+1);
                switch(i){
                case(0):
                    {
                    type_piece auxtpiece(Tour,5,attackT,moveT);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(1):
                    {
                    type_piece auxtpiece(Cavalier,3,attackC,moveC);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(2):
                    {
                    type_piece auxtpiece(Fou,3,attackF,moveF);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(3):
                    {
                    type_piece auxtpiece(Dame,9,attackD,moveD);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(4):
                    {
                    type_piece auxtpiece(Roi,0,attackR,moveR);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(5):
                    {
                    type_piece auxtpiece(Fou,3,attackF,moveF);
                    plateau[i][j]->setType(auxtpiece);
                    }

                    break;
                case(6):
                    {
                    type_piece auxtpiece(Cavalier,3,attackC,moveC);
                    plateau[i][j]->setType(auxtpiece);
                    }

                    break;
                case(7):
                    {
                    type_piece auxtpiece(Tour,5,attackT,moveT);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                }
            }
            break;
        default:
            for(int i=0;i<=7;i++)
            {
                plateau[i][j]=0;
            }
        }

    }
}

echiquier::echiquier(vector<coup> liste)
{
    plateau= vector<vector<piece*> >(8, vector<piece*>(8));//On initialise un plateau avec les pièces au position de départ
    for(int j=0;j<=7;j++)
    {
        switch(j){
        case 0:
            for(int i=0;i<=7;i++)
            {
                plateau[i][j]=new piece;
                plateau[i][j]->setCouleur(Blanc);
                plateau[i][j]->setPosition(i+1,j+1);
                switch(i){
                case(0):
                    {
                    type_piece auxtpiece(Tour,5,attackT,moveT);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(1):
                    {
                    type_piece auxtpiece(Cavalier,3,attackC,moveC);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(2):
                    {
                    type_piece auxtpiece(Fou,3,attackF,moveF);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(3):
                    {
                    type_piece auxtpiece(Dame,9,attackD,moveD);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(4):
                    {
                    type_piece auxtpiece(Roi,0,attackR,moveR);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(5):
                    {
                    type_piece auxtpiece(Fou,3,attackF,moveF);
                    plateau[i][j]->setType(auxtpiece);
                    }

                    break;
                case(6):
                    {
                    type_piece auxtpiece(Cavalier,3,attackC,moveC);
                    plateau[i][j]->setType(auxtpiece);
                    }

                    break;
                case(7):
                    {
                    type_piece auxtpiece(Tour,5,attackT,moveT);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                }
            }
            break;
        case 1:
            for(int i=0;i<=7;i++)
            {
                plateau[i][j]=new piece;
                plateau[i][j]->setCouleur(Blanc);
                plateau[i][j]->setPosition(i+1,j+1);
                type_piece auxtpiece(Pion,1,attackPb,movePb);
                plateau[i][j]->setType(auxtpiece);
            }
            break;
        case 6:
            for(int i=0;i<=7;i++)
            {
                plateau[i][j]=new piece;
                plateau[i][j]->setCouleur(Noir);
                plateau[i][j]->setPosition(i+1,j+1);
                type_piece auxtpiece(Pion,1,attackPn,movePn);
                plateau[i][j]->setType(auxtpiece);
            }
            break;
        case 7:
            for(int i=0;i<=7;i++)
            {
                plateau[i][j]=new piece;
                plateau[i][j]->setCouleur(Noir);
                plateau[i][j]->setPosition(i+1,j+1);
                switch(i){
                case(0):
                    {
                    type_piece auxtpiece(Tour,5,attackT,moveT);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(1):
                    {
                    type_piece auxtpiece(Cavalier,3,attackC,moveC);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(2):
                    {
                    type_piece auxtpiece(Fou,3,attackF,moveF);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(3):
                    {
                    type_piece auxtpiece(Dame,9,attackD,moveD);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(4):
                    {
                    type_piece auxtpiece(Roi,0,attackR,moveR);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                case(5):
                    {
                    type_piece auxtpiece(Fou,3,attackF,moveF);
                    plateau[i][j]->setType(auxtpiece);
                    }

                    break;
                case(6):
                    {
                    type_piece auxtpiece(Cavalier,3,attackC,moveC);
                    plateau[i][j]->setType(auxtpiece);
                    }

                    break;
                case(7):
                    {
                    type_piece auxtpiece(Tour,5,attackT,moveT);
                    plateau[i][j]->setType(auxtpiece);
                    }
                    break;
                }
            }
            break;
        default:
            for(int i=0;i<=7;i++)
            {
                plateau[i][j]=0;
            }
        }

    }
    vector<coup>::iterator it;
    piece playpiece;
    vector<int> lastpos;
    vector<int> newpos;
    piece pieceprise;
    special coupspecial;
    for(it=liste.begin();it!=liste.end();it++)
    {
        playpiece=it->playpiece;
        pieceprise=it->pieceprise;
        lastpos=it->lastpos;
        newpos=it->newpos;
        coupspecial=it->coupspecial;
        if(coupspecial==Usual)
        {
            piece vide;
            plateau[lastpos[0]-1][lastpos[1]-1]=0;
            plateau[newpos[0]-1][newpos[1]-1]=new piece;
            plateau[newpos[0]-1][newpos[1]-1]->setType(playpiece.getType());
            plateau[newpos[0]-1][newpos[1]-1]->setCouleur(playpiece.getCouleur());
            plateau[newpos[0]-1][newpos[1]-1]->setPosition(newpos[0],newpos[1]);
        }
        if(coupspecial==GR)
        {
            if(playpiece.getCouleur()==Blanc)
            {
                piece vide;
                *plateau[2][7]=piece(type_piece(Roi,0,attackR,moveR),Blanc,vector<int>{2,7});
                *plateau[3][7]=piece(type_piece(Tour,5,attackT,moveT),Blanc,vector<int>{3,7});
                *plateau[4][7]=vide;
                *plateau[0][7]=vide;
            }
            if(playpiece.getCouleur()==Noir)
            {
                piece vide;
                *plateau[2][0]=piece(type_piece(Roi,0,attackR,moveR),Noir,vector<int>{2,0});
                *plateau[3][0]=piece(type_piece(Tour,5,attackT,moveT),Noir,vector<int>{3,0});
                *plateau[4][0]=vide;
                *plateau[0][0]=vide;
            }
        }
        if(coupspecial==PR)
        {
            if(playpiece.getCouleur()==Blanc)
            {
                piece vide;
                *plateau[6][7]=piece(type_piece(Roi,0,attackR,moveR),Blanc,vector<int>{6,7});
                *plateau[5][7]=piece(type_piece(Tour,5,attackT,moveT),Blanc,vector<int>{5,7});
                *plateau[4][7]=vide;
                *plateau[7][7]=vide;
            }
            if(playpiece.getCouleur()==Noir)
            {
                piece vide;
                *plateau[6][0]=piece(type_piece(Roi,0,attackR,moveR),Noir,vector<int>{6,0});
                *plateau[5][7]=piece(type_piece(Tour,5,attackT,moveT),Noir,vector<int>{5,0});
                *plateau[4][0]=vide;
                *plateau[7][0]=vide;
            }
        }
    }
}



void echiquier::print()
{   Couleur auxC;
    piece* auxP;
    PIECE auxtyp;
    for(int j=7; j>=0;j--)
    {
        for(int i=0; i<=7;i++)
        {
            auxP=(plateau[i][j]);
            if(auxP!=0)
            {
                auxC=auxP->getCouleur();
                auxtyp=auxP->getType().getPIECE();
                if(auxC==Noir)
                {
                    switch(auxtyp){
                        case None:
                            break;
                        case Pion:
                            cout<<" "<<"Pn"<<" ";
                            break;
                        case Cavalier:
                            cout<<" "<<"Cn"<<" ";
                            break;
                        case Fou:
                            cout<<" "<<"Fn"<<" ";
                            break;
                        case Tour:
                            cout<<" "<<"Tn"<<" ";
                            break;
                        case Dame:
                            cout<<" "<<"Dn"<<" ";
                            break;
                        case Roi:
                            cout<<" "<<"Rn"<<" ";
                            break;
                    }
                }
                if(auxC==Blanc)
                {
                    switch(auxtyp){
                        case None:
                            cout<<"Pas normal"<<" ";
                            break;
                        case Pion:
                            cout<<" "<<"Pb"<<" ";
                            break;
                        case Cavalier:
                            cout<<" "<<"Cb"<<" ";
                            break;
                        case Fou:
                            cout<<" "<<"Fb"<<" ";
                            break;
                        case Tour:
                            cout<<" "<<"Tb"<<" ";
                            break;
                        case Dame:
                            cout<<" "<<"Db"<<" ";
                            break;
                        case Roi:
                            cout<<" "<<"Rb"<<" ";
                            break;
                    }
                }
            }
            else
            {
                cout<<" "<<"  "<<" ";
            }
        }
        cout<<j+1<<endl;
    }
    cout<<" a   b   c   d   e   f   g   h"<<endl;
}

bool echiquier::isaPiece(int i, int j)
{
    piece* goal=plateau[i-1][j-1];
    if((goal==0)||(goal->getType().getPIECE()==None)) //vérifions s'il y a déjà une pièce sur la case ciblée
    {
        return false;
    }
    else{
        return true;
    }
}


int echiquier :: istwopawns()
{
    int nb_colonne_doubleeb = 0 ;
    int nb_colonne_doubleen = 0 ;
    //On parcourt chaque colonne
    for(int i=1;i<=8;i++)
        {
            int nb_pawnb = 0 ;
            int nb_pawnn =0;
            for(int j=1;j<=8;j++)
                {
                    if(isaPiece(i,j))
                    {
                     piece * piece_ij = getPiece(i,j);
                    if((piece_ij->getType().getPIECE()==Pion)&&(piece_ij->getCouleur()==Blanc))
                        {
                            nb_pawnb += 1;
                        }
                    else if((piece_ij->getType().getPIECE()==Pion)&&(piece_ij->getCouleur()==Noir))
                    {
                            nb_pawnn += 1;
                    }
                    }
                }
            //Si la colonne i est doublee on rajoute 1 a nb_colonne_doublee
            if (nb_pawnb > 1)
                {
                    nb_colonne_doubleeb +=1 ;
                }
            if (nb_pawnn > 1)
                {
                    nb_colonne_doubleen +=1 ;
                }

        }
    //cout << "il y a " << nb_colonne_doubleen+nb_colonne_doubleeb << " colonnes doublees" << endl ;
    /*if(nb_colonne_doubleeb+nb_colonne_doubleen>0)
    {
        print();
    }*/
    return nb_colonne_doubleen-nb_colonne_doubleeb ;
}
