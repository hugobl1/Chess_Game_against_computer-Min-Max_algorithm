#include "position_echec.h"
#include "math.h"
#include <limits>
vector<vector<int>> moveDpromo{{1,1},{2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{-1,-1},{-2,-2},{-3,-3},{-4,-4},{-5,-5},{-6,-6},{-7,-7},{-1,1},{-2,2},{-3,3},{-4,4},{-5,5},{-6,6},{-7,7},{1,-1},{2,-2},{3,-3},{4,-4},{5,-5},{6,-6},{7,-7},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{-1,0},{-2,0},{-3,0},{-4,0},{-5,0},{-6,0},{-7,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,-1},{0,-2},{0,-3},{0,-4},{0,-5},{0,-6},{0,-7}};
position_echec::~position_echec()
{
    delete psoeur;
    delete pfille;
}



/*
float position_echec::valeur(float alpha, float beta, float gamma)
{
    echiquier update(liste);
    int val;
    piece* current;
    PIECE P;
    //On calcule la valeur par rapport au nombre de pièces
    for(int j=1;j<=8;j++)
    {
        for(int i=1;i<=8;i++)
        {
            if (update.isaPiece(i,j))
            {
                current=update.getPiece(i,j);
                val+=current->val();
            }
        }
    }
    val=float(val)*float(alpha);
    float valaux=0;
    for(int j=1;j<=8;j++)
    {
        for(int i=1;i<=8;i++)
        {
            if (update.isaPiece(i,j))
            {
                current=update.getPiece(i,j);
                //Vérification:
                //P=current->getType().getPIECE();
                //cout<<"Cette pièce "<<P<<" controle "<<current->control(update)<<"cases"<<endl;
                valaux+=current->control(update);
            }
        }
    }
    valaux=float(valaux)*beta;
    val+=valaux;
    return val;
}*/

position_echec* position_echec::genererpositionfils()
{

    position_echec* currentPos;
    echiquier update(liste);
    piece* current;
    vector<vector<int>> currentmove;
    int first=0;
    //Parcous sur le plateau
    for(int j=1;j<=8;j++)
    {
        for(int i=1;i<=8;i++)
        {
            if (update.isaPiece(i,j))//Si on est sur une pièce on regarde les mouvements possibles
            {
                current=update.getPiece(i,j);
                vector<int> posactuel=current->getPosition();
                if(current->getCouleur()==joueur)
                {
                vector<vector<int>>::iterator it;
                currentmove = (current->getType()).getMove();
                if(current->getType().getPIECE()==Pion)//On fait le cas particulier des pions qui peuvent avancer de 2 cases au début de la partie et qui n'ont pas la même façon d'attaquer et de bouger
                {
                    vector<vector<int>> currentattack=current->getType().getAttack();
                    for(it=currentattack.begin();it!=currentattack.end();it++)//On regarde chacun des moves possibles
                    {
                        vector<int> relativ=*it;
                        if((current->onBoard(relativ))&&(current->isanOpponent(update,relativ)))
                        {
                            currentmove.push_back(relativ);
                        }

                    }
                    if((current->getCouleur()==Blanc)&&(posactuel[1]==2)&&(!(current->isanOpponent(update,{0,2}))))
                    {
                            vector<int> init={0,2};
                            currentmove.push_back(init);
                    }
                    if((current->getCouleur()==Noir)&&(posactuel[1]==7)&&(!(current->isanOpponent(update,{0,-2}))))
                    {
                            vector<int> init={0,-2};
                            currentmove.push_back(init);
                    }
                }

                for(it=currentmove.begin();it!=currentmove.end();it++)//On regarde chacun des moves possibles
                {

                        if((current->onBoard(*it))&&(current->accessMove(update,*it)))//Si le coup est légal on continue
                        {

                            if(first==0)
                            {
                            vector<int> start=current->getPosition();//Position de départ
                            vector<int> goal={(*it)[0]+start[0],(*it)[1]+start[1]};//Position d'arrivée
                            piece take;                                                 //Est ce qu'une pièce est prise?
                            if(update.isaPiece(goal[0],goal[1]))
                            {
                                take=*(update.getPiece(goal[0],goal[1]));
                            }
                                                                                    //
                            coup currentcoup( *current, start, goal,take, Usual);
                            vector<coup> nouveau =liste;
                            nouveau.push_back(currentcoup);
                            position_echec checktest(nouveau,joueur);
                            if(checktest.check())
                            {
                                //Le coup met en échec et ne peut donc pas être joué
                            }
                            else{
                                piece playpiece=currentcoup.getPlaypiece();
                                if(playpiece.getType().getPIECE()==Roi)//Dans le cas particulier du Roi il faut vérifier si il a bougé pour le Roque
                                {
                                    playpiece.getType().setMoved(true);
                                    coup currentcouproi( playpiece, start, goal,take, Usual);
                                    nouveau =liste;
                                    nouveau.push_back(currentcouproi);
                                }
                                if(playpiece.getType().getPIECE()==Tour)//Dans le cas particulier de la Tour il faut vérifier si elle a bougé pour le Roque
                                {
                                    playpiece.getType().setMoved(true);
                                    coup currentcouprook( playpiece, start, goal,take, Usual);
                                    nouveau =liste;
                                    nouveau.push_back(currentcouprook);
                                }
                                if((playpiece.getType().getPIECE()==Pion)&&(joueur==Blanc)&&(goal[1]==8))
                                {
                                    cout<<"Promotion"<<endl;
                                    type_piece typepromo(Dame,9, moveDpromo,moveDpromo);
                                    playpiece.setType(typepromo);
                                    playpiece.getType().setValeur(9);
                                    playpiece.getType().setPIECE(Dame);
                                    coup currentcoup( playpiece, start, goal,take, Usual);
                                    nouveau =liste;
                                    nouveau.push_back(currentcoup);
                                    echiquier updatebis(nouveau);
                                    updatebis.print();

                                }
                                if((playpiece.getType().getPIECE()==Pion)&&(joueur==Noir)&&(goal[1]==1))
                                {
                                    cout<<"Promotion"<<endl;
                                    type_piece typepromo(Dame,9, moveDpromo,moveDpromo);
                                    playpiece.setType(typepromo);
                                    coup currentcoup( playpiece, start, goal,take, Usual);
                                    nouveau =liste;
                                    nouveau.push_back(currentcoup);
                                    echiquier updatebis(nouveau);
                                    updatebis.print();
                                }
                                pfille=new position_echec(nouveau,1-joueur);
                                //cout<<endl;
                                //cout<<first<<endl;
                                first+=1;
                                currentPos=pfille;
                                //currentPos->print();

                            }

                            }
                            else if(first==1)
                            {

                            vector<int> start=current->getPosition();//Position de départ
                            vector<int> goal={(*it)[0]+start[0],(*it)[1]+start[1]};//Position d'arrivée
                            piece take;                                                 //Est ce qu'une pièce est prise?
                            if(update.isaPiece(goal[0],goal[1]))
                            {
                                take=*(update.getPiece(goal[0],goal[1]));
                            }                                                           //

                            coup currentcoup( *current, start, goal,take, Usual);
                            vector<coup> nouveau =liste;
                            nouveau.push_back(currentcoup);
                            position_echec checktest(nouveau,joueur);
                            if(checktest.check())
                            {
                                //Le coup met en échec et ne peut donc pas être joué
                            }
                            else{
                                piece playpiece=currentcoup.getPlaypiece();
                                if(playpiece.getType().getPIECE()==Roi)//Dans le cas particulier du Roi il faut vérifier si il a bougé pour le Roque
                                {
                                    playpiece.getType().setMoved(true);
                                    coup currentcouproi( playpiece, start, goal,take, Usual);
                                    nouveau =liste;
                                    nouveau.push_back(currentcouproi);
                                }
                                if(playpiece.getType().getPIECE()==Tour)//Dans le cas particulier de la Tour il faut vérifier si elle a bougé pour le Roque
                                {
                                    playpiece.getType().setMoved(true);
                                    coup currentcouprook( playpiece, start, goal,take, Usual);
                                    nouveau =liste;
                                    nouveau.push_back(currentcouprook);
                                }
                                if((playpiece.getType().getPIECE()==Pion)&&(joueur==Blanc)&&(goal[1]==8))
                                {
                                    cout<<"Promotion"<<endl;
                                    type_piece typepromo(Dame,9, moveDpromo,moveDpromo);
                                    playpiece.setType(typepromo);
                                    coup currentcoup( playpiece, start, goal,take, Usual);
                                    nouveau =liste;
                                    nouveau.push_back(currentcoup);
                                    echiquier updatebis(nouveau);
                                    updatebis.print();
                                }
                                if((playpiece.getType().getPIECE()==Pion)&&(joueur==Noir)&&(goal[1]==1))
                                {
                                    cout<<"Promotion"<<endl;
                                    type_piece typepromo(Dame,9, moveDpromo,moveDpromo);
                                    playpiece.setType(typepromo);
                                    coup currentcoup( playpiece, start, goal,take, Usual);
                                    nouveau =liste;
                                    nouveau.push_back(currentcoup);
                                    echiquier updatebis(nouveau);
                                    updatebis.print();
                                }

                                if(checktest.check())
                                {
                                //Le coup met en échec
                                }
                                else{
                                currentPos->psoeur=new position_echec(nouveau,1-joueur);
                                currentPos=currentPos->psoeur;
                                //currentPos->print();
                                //cout<<first<<endl;
                                }
                            }
                            }
                        }
                    }
                   if(current->getType().getPIECE()==Roi)//On regarde les critères pour le Roque
                    {
                        if(!(current->getType().getMoved()))//Il faut que le roi n'ait pas bougé
                        {
                                //Conditions à vérifier: case vide entre la tour et le roi et pas de position d'échec si on bouge le roi entre ces cases
                                //Testons les cases vides:
                                if((joueur==Noir)&&!(update.isaPiece(2,8))&&!(update.isaPiece(3,8))&&!(update.isaPiece(4,8)))
                                {
                                    piece* leftrook=update.getPiece(1,8);
                                    if((leftrook->getType().getPIECE()==Tour)&&(!(leftrook->getType().getMoved())))//Grand Roque // Il faut que la tour n'ait pas bougé
                                    {
                                        piece vide;
                                        coup moverook(*leftrook,vector<int>{1,8}, vector<int>{d,8}, vide, GR);
                                        coup aux1(*current,vector<int>{e,8},vector<int>{d,8},vide,GR);
                                        coup aux2(*current,vector<int>{e,8},vector<int>{c,8},vide,GR);
                                        coup aux3(*current,vector<int>{e,8},vector<int>{b,8},vide,GR);
                                        vector<coup> aux1l=liste;
                                        aux1l.push_back(aux1);
                                        vector<coup> aux2l=liste;
                                        aux2l.push_back(aux2);
                                        vector<coup> aux3l=liste;
                                        aux3l.push_back(aux3);
                                        position_echec posaux1(aux1l,joueur);
                                        position_echec posaux2(aux2l, joueur);
                                        position_echec posaux3(aux3l,joueur);
                                        if(!(posaux1.check())&&!(posaux2.check())&&(posaux3.check())&&!((*this).check()))
                                        {
                                            leftrook->getType().setMoved(true);
                                            current->getType().setMoved(true);
                                            posaux2.liste.push_back(moverook);
                                            currentPos->psoeur=new position_echec(posaux2.liste,1-joueur);
                                            currentPos=currentPos->psoeur;

                                        }
                                    }
                                }
                                else if((joueur==Blanc)&&!(update.isaPiece(2,1))&&!(update.isaPiece(3,1))&&!(update.isaPiece(4,1)))
                                {
                                    piece* leftrook=update.getPiece(1,1);
                                    if((leftrook->getType().getPIECE()==Tour)&&(!(leftrook->getType().getMoved())))//Grand Roque // Il faut que la tour n'ait pas bougé
                                    {
                                        piece vide;
                                        coup moverook(*leftrook,vector<int>{1,1}, vector<int>{d,1}, vide, GR);
                                        coup aux1(*current,vector<int>{e,1},vector<int>{d,1},vide,GR);
                                        coup aux2(*current,vector<int>{e,1},vector<int>{c,1},vide,GR);
                                        coup aux3(*current,vector<int>{e,1},vector<int>{b,1},vide,GR);
                                        vector<coup> aux1l=liste;
                                        aux1l.push_back(aux1);
                                        vector<coup> aux2l=liste;
                                        aux2l.push_back(aux2);
                                        vector<coup> aux3l=liste;
                                        aux3l.push_back(aux3);
                                        position_echec posaux1(aux1l,joueur);
                                        position_echec posaux2(aux2l, joueur);
                                        position_echec posaux3(aux3l,joueur);
                                        if(!(posaux1.check())&&!(posaux2.check())&&(posaux3.check())&&!((*this).check()))
                                        {
                                            leftrook->getType().setMoved(true);
                                            current->getType().setMoved(true);
                                            posaux2.liste.push_back(moverook);
                                            currentPos->psoeur=new position_echec(posaux2.liste,1-joueur);
                                            currentPos=currentPos->psoeur;

                                        }
                                    }
                                }
                                //Conditions à vérifier: case vide entre la tour et le roi et pas de position d'échec si on bouge le roi entre ces cases
                                //Testons les cases vides:
                                if((joueur==Noir)&&!(update.isaPiece(6,8))&&!(update.isaPiece(7,8)))
                                {
                                    piece* rightrook=update.getPiece(8,8);
                                    if((rightrook->getType().getPIECE()==Tour)&&(!(rightrook->getType().getMoved())))//Petit Roque // Il faut que la tour n'ait pas bougé
                                    {
                                        piece vide;
                                        coup moverook(*rightrook,vector<int>{8,8}, vector<int>{6,8}, vide, PR);
                                        coup aux1(*current,vector<int>{e,8},vector<int>{f,8},vide,PR);
                                        coup aux2(*current,vector<int>{e,8},vector<int>{g,8},vide,PR);
                                        vector<coup> aux1l=liste;
                                        aux1l.push_back(aux1);
                                        vector<coup> aux2l=liste;
                                        aux2l.push_back(aux2);
                                        position_echec posaux1(aux1l,joueur);
                                        position_echec posaux2(aux2l, joueur);
                                        if(!(posaux1.check())&&!(posaux2.check())&&!((*this).check()))
                                        {
                                            rightrook->getType().setMoved(true);
                                            current->getType().setMoved(true);
                                            posaux2.liste.push_back(moverook);
                                            currentPos->psoeur=new position_echec(posaux2.liste,1-joueur);
                                            currentPos=currentPos->psoeur;

                                        }
                                    }
                                }
                                else if((joueur==Blanc)&&!(update.isaPiece(6,1))&&!(update.isaPiece(7,1)))
                                {
                                    piece* rightrook=update.getPiece(8,1);
                                    if((rightrook->getType().getPIECE()==Tour)&&(!(rightrook->getType().getMoved())))//Petit Roque // Il faut que la tour n'ait pas bougé
                                    {
                                        piece vide;
                                        coup moverook(*rightrook,vector<int>{1,1}, vector<int>{d,1}, vide, PR);
                                        coup aux1(*current,vector<int>{e,1},vector<int>{f,1},vide,PR);
                                        coup aux2(*current,vector<int>{e,1},vector<int>{g,1},vide,PR);
                                        vector<coup> aux1l=liste;
                                        aux1l.push_back(aux1);
                                        vector<coup> aux2l=liste;
                                        aux2l.push_back(aux2);
                                        position_echec posaux1(aux1l,joueur);
                                        position_echec posaux2(aux2l, joueur);
                                        if(!(posaux1.check())&&!(posaux2.check())&&!((*this).check()))
                                        {
                                            rightrook->getType().setMoved(true);
                                            current->getType().setMoved(true);
                                            posaux2.liste.push_back(moverook);
                                            currentPos->psoeur=new position_echec(posaux2.liste,1-joueur);
                                            currentPos=currentPos->psoeur;

                                        }
                                    }
                                }
                }
                    }
                }
            }
        }
    }
    return pfille;


}

bool position_echec::check()
{
    bool checkbool=false;
    echiquier update(liste);
    piece* current;
    //Première partie: Trouver le roi du joueur courant
    //Parcous sur le plateau
    vector<int> posroi;
    for(int j=1;j<=8;j++)
    {
        for(int i=1;i<=8;i++)
        {
                if(update.isaPiece(i,j))
                {
                    if((update.getPiece(i,j)->getType().getPIECE()==Roi)&&(update.getPiece(i,j)->getCouleur()==joueur))
                {
                    current=update.getPiece(i,j);//?
                }
                }
        }
    }
    posroi=current->getPosition();//?
    //Seconde partie: vérifier si l'une des pièces adverses a accès au roi

    for(int j=1;j<=8;j++)
    {
        for(int i=1;i<=8;i++)
        {
            if(update.isaPiece(i,j))
                {
                current=update.getPiece(i,j);
                vector<int> currentpos=current->getPosition();
                vector<int> relativ={posroi[0]-currentpos[0],posroi[1]-currentpos[1]};
                vector<vector<int>> attack= current->getType().getAttack();
                bool in=false;
                for(int i=0;i<=attack.size();i++)
                {
                    if(attack[i]==relativ)
                    {
                        in=true;
                    }
                }
                if(in)
                {
                    if(update.getPiece(i,j)->accessMove(update,relativ))
                    {
                        checkbool=true;
                    }
                }
                }
        }
    }

    return checkbool;
}

bool position_echec::checkmate()
{
    if(check())
    {
    bool aux= true;
    position_echec* currentPos;
    echiquier update(liste);
    piece* current;
    vector<vector<int>> currentmove;
    int first=0;
    //Parcous sur le plateau
    for(int j=1;j<=8;j++)
    {
        for(int i=1;i<=8;i++)
        {
            if (update.isaPiece(i,j))//Si on est sur une pièce on regarde les mouvements possibles
            {
                current=update.getPiece(i,j);
                if(current->getCouleur()==joueur)
                {
                vector<vector<int>>::iterator it;
                currentmove = (current->getType()).getMove();
                currentmove = (current->getType()).getMove();
                if(current->getType().getPIECE()==Pion)
                {
                    vector<vector<int>> currentattack=current->getType().getAttack();
                    currentmove.insert(currentmove.end(), currentattack.begin(), currentattack.end());
                }
                for(it=currentmove.begin();it!=currentmove.end();it++)//On regarde chacun des moves possibles
                {
                    if((current->onBoard(*it))&&(current->accessMove(update,*it)))//Si le coup est légal on continue
                        {
                            vector<int> start=current->getPosition();//Position de départ
                            vector<int> goal={(*it)[0]+start[0],(*it)[1]+start[1]};//Position d'arrivée
                            piece take;                                                 //Est ce qu'une pièce est prise?
                            if(update.isaPiece(goal[0],goal[1]))
                            {
                                take=*(update.getPiece(goal[0],goal[1]));
                            }                                                           //
                            coup currentcoup( *current, start, goal,take, Usual);
                            vector<coup> nouveau =liste;
                            nouveau.push_back(currentcoup);
                            position_echec checktest(nouveau,joueur);
                            if(checktest.check())
                            {
                                //Le coup me en échec
                            }
                            else{
                                aux=false;
                            }
                        }
                }
                }
            }
        }
    }
    return(aux);
    }
    else{
        return false;
    }
}

float position_echec::valeur(float alpha, float beta, float gamma, Couleur ordiCouleur)
{
    echiquier update(liste);
    float val=0;
    piece* current;
    PIECE P;
    //On calcule la valeur par rapport au nombre de pièces
    for(int j=1;j<=8;j++)
    {
        for(int i=1;i<=8;i++)
        {
            if (update.isaPiece(i,j))
            {
                current=update.getPiece(i,j);
                val+=current->val();
            }
        }
    }
    val=float(val)*float(alpha);
    //cout<<val<<endl;
    float valaux=0;
    for(int j=1;j<=8;j++)
    {
        for(int i=1;i<=8;i++)
        {
            if (update.isaPiece(i,j))
            {
                current=update.getPiece(i,j);
                //Vérification:
                //P=current->getType().getPIECE();
                //cout<<"Cette pièce "<<P<<" controle "<<current->control(update)<<"cases"<<endl;
                valaux+=current->control(update);
            }
        }
    }
    valaux=float(valaux)*float(beta);
    //cout<<valaux<<endl;
    val+=valaux;
    val+=(gamma*update.istwopawns());
    //cout<<gamma*update.istwopawns()<<endl;
    //cout<<val<<endl;
    //update.print();
    if(ordiCouleur==Blanc)
    {
        if(checkmate())
        {
            return -std::numeric_limits<int>::max();
        }
        else{
        return val;
        }

    }
    else{
    if(checkmate())
        {
            return -std::numeric_limits<int>::max();
        }
    else{
        return -val;
    }

    }

}
