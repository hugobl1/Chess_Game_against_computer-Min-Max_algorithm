#include "piece.h"
#include "echiquier.h"
int piece::val()
{
    if (couleur==Blanc)
    {
        return type.getValeur();
    }
        if (couleur==Noir)
    {
        return -type.getValeur();
    }
    else{return 0;}
}

int piece::control(echiquier chess)
{
    int control=0;
    vector<vector<int>> relativattack= type.getAttack();
    vector<vector<int>>::iterator it;
    for(it=relativattack.begin();it!=relativattack.end();it++)
    {
        if(onBoard(*it)&&access(chess,*it))
        {
            if (couleur==Blanc)
            {
                //if(P==4)
                //{
                  //  cout<<(*it)[0]<<","<<(*it)[1]<<endl;
                //}
                control+=1;
            }
            if (couleur==Noir)
            {
                control-=1;
            }
        }
    }

    return control;
}

bool piece::onBoard(vector<int> relativ)
{
    vector<int> coord={relativ[0]+position[0],relativ[1]+position[1]};
    if(coord[0]<=8&&coord[0]>=1&&coord[1]<=8&&coord[1]>=1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool piece::isanAlly(echiquier chess,vector<int> relativ)
{
    vector<int> coord={relativ[0]+position[0],relativ[1]+position[1]};
    piece* goal=chess.getPiece(coord[0],coord[1]);
    if((goal!=0)&&(goal->type.getPIECE()!=None)&&(goal->couleur==couleur)) //vérifions s'il y a déjà une pièce sur la case ciblée et si elle est à l'alliée
    {
        return true;
    }
    else{
        return false;
    }
}

bool piece::isanOpponent(echiquier chess,vector<int> relativ)
{
    vector<int> coord={relativ[0]+position[0],relativ[1]+position[1]};
    piece* goal=chess.getPiece(coord[0],coord[1]);
    if((goal!=0)&&(goal->type.getPIECE()!=None)&&(goal->couleur==(1-couleur)) )//vérifions s'il y a déjà une pièce sur la case ciblée et si elle est à l'opposant
    {
        return true;
    }
    else{
        return false;
    }
}

bool piece::access(echiquier chess,vector<int> relativ)
{
    vector<int> coord={relativ[0]+position[0],relativ[1]+position[1]};
    PIECE auxtyp=type.getPIECE();
    switch(auxtyp){
                        case None:
                            return false;
                            break;
                        case Pion:
                            return true;
                            break;
                        case Cavalier:
                            return true;
                            break;
                        case Fou:
                            {
                            int first;
                            int second;
                            if((relativ[0]!=0)&&(relativ[1]!=0))
                               {
                                first=relativ[0]/abs(relativ[0]);
                                second= relativ[1]/abs(relativ[1]);
                               }
                            else if(relativ[1]!=0)
                                {
                                first=0;
                                second= relativ[1]/abs(relativ[1]);
                                }
                            else{
                                 first=relativ[0]/abs(relativ[0]);
                                 second=0;
                            }
                            int i=1;
                            if((first<0)&&(second<0))
                            {
                                while((position[0]+first*i>coord[0])||(position[1]+second*i>coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            else if((first>0)&&(second<0))
                            {
                            while((position[0]+first*i<coord[0])||(position[1]+second*i>coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            else if((first<0)&&(second>0))
                            {
                            while((position[0]+first*i>coord[0])||(position[1]+second*i<coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            else if((first>0)&&(second>0))
                            {
                                while((position[0]+first*i<coord[0])||(position[1]+second*i<coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            }
                            break;
                        case Tour:
                            {
                            int first;
                            int second;
                            if((relativ[0]!=0)&&(relativ[1]!=0))
                               {
                                first=relativ[0]/abs(relativ[0]);
                                second= relativ[1]/abs(relativ[1]);
                               }
                            else if(relativ[1]!=0)
                                {
                                first=0;
                                second= relativ[1]/abs(relativ[1]);
                                }
                            else{
                                 first=relativ[0]/abs(relativ[0]);
                                 second=0;
                            }
                            int i=1;
                            if((first<0)&&(second==0))
                            {
                                while((position[0]+first*i>coord[0]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            else if((first>0)&&(second==0))
                            {
                            while((position[0]+first*i<coord[0]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            else if((second>0)&&(first==0))
                            {
                            while((position[1]+second*i<coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            else if((second<0)&&(first==0))
                            {
                                while((position[1]+second*i>coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            }
                            break;
                        case Dame:
                            {
                            int first;
                            int second;
                            if((relativ[0]!=0)&&(relativ[1]!=0))
                               {
                                first=relativ[0]/abs(relativ[0]);
                                second= relativ[1]/abs(relativ[1]);
                               }
                            else if(relativ[1]!=0)
                                {
                                first=0;
                                second= relativ[1]/abs(relativ[1]);
                                }
                            else{
                                 first=relativ[0]/abs(relativ[0]);
                                 second=0;
                            }
                            int i=1;
                            if((first<0)&&(second<0))
                            {
                                while((position[0]+first*i>coord[0])||(position[1]+second*i>coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            else if((first>0)&&(second<0))
                            {
                            while((position[0]+first*i<coord[0])||(position[1]+second*i>coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            else if((first<0)&&(second>0))
                            {
                            while((position[0]+first*i>coord[0])||(position[1]+second*i<coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            else if((first>0)&&(second>0))
                            {
                                while((position[0]+first*i<coord[0])||(position[1]+second*i<coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            if((first<0)&&(second==0))
                            {
                                while((position[0]+first*i>coord[0]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            else if((first>0)&&(second==0))
                            {
                            while((position[0]+first*i<coord[0]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            else if((second>0)&&(first==0))
                            {
                            while((position[1]+second*i<coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            else if((second<0)&&(first==0))
                            {
                                while((position[1]+second*i>coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            return true;
                            }
                            }
                            break;
                        case Roi:
                            return true;
                            break;
                    }
}


bool piece::accessMove(echiquier chess,vector<int> relativ)
{
    vector<int> coord={relativ[0]+position[0],relativ[1]+position[1]};
    PIECE auxtyp=type.getPIECE();
    switch(auxtyp){
                        case None:
                            return false;
                            break;
                        case Pion:
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else if(((*this).isanOpponent(chess,relativ))&&((relativ[1]==1)||(relativ[1]==-1))&&(relativ[0]==0))//Si une pièce est devant le pion il ne peut pas avancer
                            {
                                return false;
                            }
                            else{
                                return true;
                            }

                            break;
                        case Cavalier:
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }

                            break;
                        case Fou:
                            {
                            int first;
                            int second;
                            if((relativ[0]!=0)&&(relativ[1]!=0))
                               {
                                first=relativ[0]/abs(relativ[0]);
                                second= relativ[1]/abs(relativ[1]);
                               }
                            else if(relativ[1]!=0)
                                {
                                first=0;
                                second= relativ[1]/abs(relativ[1]);
                                }
                            else{
                                 first=relativ[0]/abs(relativ[0]);
                                 second=0;
                            }
                            int i=1;
                            if((first<0)&&(second<0))
                            {
                                while((position[0]+first*i>coord[0])||(position[1]+second*i>coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }
                            }
                            else if((first>0)&&(second<0))
                            {

                            while((position[0]+first*i<coord[0])||(position[1]+second*i>coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }

                            }
                            else if((first<0)&&(second>0))
                            {
                            while((position[0]+first*i>coord[0])||(position[1]+second*i<coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }

                            }
                            else if((first>0)&&(second>0))
                            {
                                while((position[0]+first*i<coord[0])||(position[1]+second*i<coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }

                            }
                            }
                            break;
                        case Tour:
                            {
                            int first;
                            int second;
                            if((relativ[0]!=0)&&(relativ[1]!=0))
                               {
                                first=relativ[0]/abs(relativ[0]);
                                second= relativ[1]/abs(relativ[1]);
                               }
                            else if(relativ[1]!=0)
                                {
                                first=0;
                                second= relativ[1]/abs(relativ[1]);
                                }
                            else{
                                 first=relativ[0]/abs(relativ[0]);
                                 second=0;
                            }
                            int i=1;
                            if((first<0)&&(second==0))
                            {
                                while((position[0]+first*i>coord[0]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }
                            }
                            else if((first>0)&&(second==0))
                            {
                            while((position[0]+first*i<coord[0]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }
                            }
                            else if((second>0)&&(first==0))
                            {
                            while((position[1]+second*i<coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }
                            }
                            else if((second<0)&&(first==0))
                            {
                                while((position[1]+second*i>coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }
                            }
                            }
                            break;
                        case Dame:
                            {
                            int first;
                            int second;
                            if((relativ[0]!=0)&&(relativ[1]!=0))
                               {
                                first=relativ[0]/abs(relativ[0]);
                                second= relativ[1]/abs(relativ[1]);
                               }
                            else if(relativ[1]!=0)
                                {
                                first=0;
                                second= relativ[1]/abs(relativ[1]);
                                }
                            else{
                                 first=relativ[0]/abs(relativ[0]);
                                 second=0;
                            }
                            int i=1;
                            if((first<0)&&(second<0))
                            {
                                while((position[0]+first*i>coord[0])||(position[1]+second*i>coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }
                            }
                            else if((first>0)&&(second<0))
                            {
                            while((position[0]+first*i<coord[0])||(position[1]+second*i>coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }
                            }
                            else if((first<0)&&(second>0))
                            {
                            while((position[0]+first*i>coord[0])||(position[1]+second*i<coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }
                            }
                            else if((first>0)&&(second>0))
                            {
                                while((position[0]+first*i<coord[0])||(position[1]+second*i<coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }
                            }
                                                        if((first<0)&&(second==0))
                            {
                                while((position[0]+first*i>coord[0]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }
                            }
                            else if((first>0)&&(second==0))
                            {
                            while((position[0]+first*i<coord[0]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }
                            }
                            else if((second>0)&&(first==0))
                            {
                            while((position[1]+second*i<coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }
                            }
                            else if((second<0)&&(first==0))
                            {
                                while((position[1]+second*i>coord[1]))
                            {
                                if(chess.isaPiece(position[0]+first*i,position[1]+second*i))
                                {
                                    return false;
                                }
                                i+=1;
                            }
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }
                            }
                            }
                            break;
                        case Roi:
                            if((*this).isanAlly(chess,relativ))
                            {
                                return false;
                            }
                            else{
                                return true;
                            }

                            break;
                    }
}

void piece::print()
{
    cout<<"Cette pièce est :"<<endl;
    if (couleur==0)
    {
        cout<<"Noire"<<endl;
    }
    else
    {
        cout<<"Blanche"<<endl;
    }
    switch(type.getPIECE())
    {
    case Pion:
        cout<<"Pion"<<endl;
        break;
    case Tour:
        cout<<"Tour"<<endl;
        break;
    case Cavalier:
        cout<<"Cavalier"<<endl;
        break;
    case Fou:
        cout<<"Fou"<<endl;
        break;
    case Dame:
        cout<<"Dame"<<endl;
        break;
    case Roi:
        cout<<"Roi"<<endl;
        break;
    case None:
        cout<<"Pas de pièce ici"<<endl;
        break;
    }
}
