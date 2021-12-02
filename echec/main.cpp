#include <iostream>
#include "echiquier.h"
#include "position_echec.h"
using namespace std;



position_echec* choisircoup(Couleur couleur, position_echec* chessboard)
{
    piece vide;
    echiquier board(chessboard->liste);
    string caseastr,casebstr;
    int numa=0,numb=0,casea,caseb;
    bool erreur=true;
    piece p;
    coup roque1;
    coup roque2;
    while(erreur)
    {
        erreur=false;
        cout<<"Quelle est la case de départ de la pièce jouée (exemple: e 6) ou dîtes PR pour le petit roque et GR pour le grand roque (puis 1 sur la ligne suivante)?"<<endl;
        cin>>caseastr>>numa;
        if(caseastr=="a")
        {   casea=1;
        }
        else if(caseastr=="b")
        {   casea=2;
        }
        else if(caseastr=="c")
        {   casea=3;
        }
        else if(caseastr=="d")
        {   casea=4;
        }
        else if(caseastr=="e")
        {   casea=5;
        }
        else if(caseastr=="f")
        {   casea=6;
        }
        else if(caseastr=="g")
        {   casea=7;
        }
        else if(caseastr=="h")
        {   casea=8;
        }
        else if(caseastr=="PR")
        {

        }
        else if(caseastr=="GR")
        {

        }
        else{
            cout<<"Veuillez choisir une case du plateau!";
            erreur=true;
        }
        cout<<"Quelle est la case d'arrivée de la pièce jouée ou dîtes PR pour le petit roque et GR pour le grand roque ou dîtes PR pour le petit roque et GR pour le grand roque (puis 1 sur la ligne suivante)?"<<endl;
        cin>>casebstr>>numb;
        if(casebstr=="a")
        {   caseb=1;
        }
        else if(casebstr=="b")
        {   caseb=2;
        }
        else if(casebstr=="c")
        {   caseb=3;
        }
        else if(casebstr=="d")
        {   caseb=4;
        }
        else if(casebstr=="e")
        {   caseb=5;
        }
        else if(casebstr=="f")
        {   caseb=6;
        }
        else if(casebstr=="g")
        {   caseb=7;
        }
        else if(casebstr=="h")
        {   caseb=8;
        }
        else if(caseastr=="PR")
        {
        }
        else if(caseastr=="GR")
        {
        }
        else{
            cout<<"Veuillez choisir une case du plateau!";
            erreur=true;
        }
        if(caseastr=="PR")
        {
            if (couleur==Blanc)
            {
                piece vide;
                coup joue(*board.getPiece(5,1),vector<int>{5,1},vector<int>{7,1},vide,Usual);
                roque1=joue;
                coup joue1(*board.getPiece(8,1),vector<int>{8,1},vector<int>{6,1},vide,Usual);
                roque2=joue1;
            }
            else if(couleur==Noir)
            {
                piece vide;
                coup joue(*board.getPiece(5,8),vector<int>{5,8},vector<int>{7,8},vide,Usual);
                roque1=joue;
                coup joue1(*board.getPiece(8,8),vector<int>{8,8},vector<int>{6,8},vide,Usual);
                roque2=joue1;
            }
        }
        else if(caseastr=="GR")
        {
            if (couleur==Blanc)
            {
                piece vide;
                coup joue(*board.getPiece(5,1),vector<int>{5,1},vector<int>{3,1},vide,Usual);
                roque1=joue;
                coup joue1(*board.getPiece(1,1),vector<int>{1,1},vector<int>{4,1},vide,Usual);
                roque2=joue1;
            }
            else if(couleur==Noir)
            {
                piece vide;
                coup joue(*board.getPiece(5,8),vector<int>{5,8},vector<int>{3,8},vide,Usual);
                roque1=joue;
                coup joue1(*board.getPiece(1,8),vector<int>{1,8},vector<int>{4,8},vide,Usual);
                roque2=joue1;
            }
        }
        else if(((!erreur)&&(board.isaPiece(casea,numa)))&&(board.getPiece(casea,numa)->getCouleur()==couleur))
        {
                p=*board.getPiece(casea,numa);
        }
        else{
            cout<<"Vous n'avez pas choisi une case contenant une pièce de votre couleur! Veuillez recommencer..."<<endl;
            erreur=true;
        }
    }
    if((caseastr!="PR")&&(caseastr!="GR"))
    {
        coup joue(p,vector<int>{casea,numa},vector<int>{caseb,numb},vide,Usual);
        vector<coup> coups = chessboard->liste;
        coups.push_back(joue);
        position_echec* posActuel=new position_echec(coups,1-couleur);
        return posActuel;
    }
    else{
        vector<coup> coups = chessboard->liste;
        coups.push_back(roque1);
        coups.push_back(roque2);
        position_echec* posActuel=new position_echec(coups,1-couleur);
        return posActuel;
    }

}

int main()
{
    //Début de la partie//
    echiquier chess;
    //cout<<chess.isaPiece(1,1)<<chess.isaPiece(1,2)<<chess.isaPiece(1,3)<<endl;
    chess.print();
    //TESTS//
    //cout<<"Veuillez jouer un coup!"<<endl;
    //piece p=*chess.getPiece(b,1);
    ///////////////////Test
    //vector<int> pos=p.getPosition();
    //int first=pos[0];
    //int second=pos[1];
    //cout<<first<<second<<endl;
    ///////////
    //piece vide;
    //coup co(p,vector<int>{b,1},vector<int>{c,3},vide,Usual);
    //echiquier update({co});
    //update.print();
    //position_echec posi({co},Noir);
    //cout<<posi.valeur(0.5,0.5);
    //cout<<"Le pointeur vaut"<<posi.getSoeur()<<endl;
    //position_echec* pPosi=(posi.getFille());
    /*for(int j=1;j<=8;j++)
    {
        for(int i=1;i<=8;i++)
        {
            if(update.isaPiece(i,j))
            {
            update.getPiece(i,j)->print();
            }

        }
    }

    position_echec* ptest= posi.genererpositionfils();
    cout<<"On affiche les différents coups possibles"<<endl;
    int compteur=0;
    while ((ptest!=0)&&(compteur<6))
    {
        cout<<"----------------------------------------"<<endl;
        ptest->print();
        ptest=ptest->getSoeur();
        //cout<<ptest<<endl;
        cout<<"----------------------------------------"<<endl;
        compteur+=1;
    }
    //Fin des tests
    */

    Couleur choixcouleur;
    Couleur choixcouleurpc;
    string choix;
    bool boolchoix=true;
    while(boolchoix)
    {
        cout<<"Quelle couleur voulez-vous jouer?"<<endl;
        cin>>choix;
        if (choix=="Blanc")
        {
            choixcouleur=Blanc;
            boolchoix=false;
            choixcouleurpc=Noir;
        }
        else if(choix=="Noir")
        {
            choixcouleur=Noir;
            boolchoix=false;
            choixcouleurpc=Blanc;
        }
        else{
            cout<<"Veuillez choisir l'une des couleurs possibles!"<<endl;
        }
    }
    cout<<"Bonne partie!"<<endl;
    if(choixcouleur==Blanc)
    {
        position_echec* pPosi=new position_echec({},Blanc);
        pPosi=choisircoup(Blanc,pPosi);
        pPosi->print();
        position_echec* newone = minmax(2,pPosi,choixcouleurpc);
        newone->print();
        //cout<<newone->check()<<endl;
        cout<<endl;
        while(true)
        {
            newone=choisircoup(Blanc,newone);
            newone->print();
            //cout<<newone->check()<<endl;
            if(newone->checkmate())
            {
                cout<<"Vous avez gagné!"<<endl;
                break;
            }
            newone = minmax(2,newone,choixcouleurpc);
            newone->print();
            if(newone->checkmate())
            {
                cout<<"L'ordinateur vous a battu!"<<endl;
                break;
            }
        }
    }
    else if(choixcouleur==Noir)
    {
            position_echec* pPosi=new position_echec({},Blanc);
            position_echec* newone = minmax(2,pPosi,choixcouleurpc);
            newone->print();
            newone=choisircoup(Noir,newone);
            newone->print();
            //cout<<newone->check()<<endl;
            cout<<endl;
            while(true)
            {
                newone = minmax(2,newone,choixcouleurpc);
                newone->print();
                //cout<<newone->check()<<endl;
                if(newone->checkmate())
                {
                    cout<<"Vous avez gagné!"<<endl;
                    break;
                }
                newone=choisircoup(Noir,newone);
                newone->print();
                //cout<<newone->check()<<endl;
                if(newone->checkmate())
                {
                    cout<<"L'ordinateur vous a battu!"<<endl;
                    break;
                }
            }
    }


    return 0;
}
