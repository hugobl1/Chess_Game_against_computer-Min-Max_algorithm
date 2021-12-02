#include <iostream>
#include<cmath>
#include<stdlib.h>
#include "position.h"

using namespace std ;

int co_to_int(int i,int j){return (i-1)*3+j-1;}

//La case vaut -1 si elle n'est pas occupée
class grille
{
  public :
  int grille_[9]={-1,-1,-1,-1,-1,-1,-1,-1,-1};
  //A faire un constructeur par copie
  int & operator()(int i,int j){return grille_[co_to_int(i,j)];}
  bool jouer(int i,int j,int joueur);
  int valeur();
  ~grille(){}
  void afficher_case(int,int);
  void afficher_grille();
  bool grille_pleine();
};

bool grille::grille_pleine(){
  for(int i=0;i<9;i++){if(grille_[i]==-1){return false;}}
    return true;
}

void grille::afficher_case(int i,int j)
{
  if(grille_[co_to_int(i,j)]==0)
  {
     std :: cout  << " O ";
  }
  if(grille_[co_to_int(i,j)]==1)
  {
     std :: cout  << " X ";
  }
  if(grille_[co_to_int(i,j)]==-1)
  {
     std :: cout  << "   ";
  }
  if(j==3)
  {
    std::cout << "]" << std :: endl ;
  }
}

void grille :: afficher_grille()
{
  for(int i=1;i<4;i++)
  {
    std :: cout << "[" ;
    for(int j=1;j<4;j++)
    {
      afficher_case(i,j);
    }
  }
}


int grille::valeur()
{
  //Renvoie 0 si c'est l'humain qui gagne 
  //Renvoie 1 si c'est la machine qui gagne
  //Renvoie 2 en cas de match nul
  int matche_nul = 2 ;
  //on teste les lignes
  for (int joueur=0;joueur<2;joueur++){
    for(int i=1;i<4;i++)
    {
      if ((grille_[(i-1)*3]==joueur) && (grille_[(i-1)*3+1]==joueur) && (grille_[(i-1)*3+2]==joueur))
      {
        return joueur;
      }
    }
    //on teste les colonnes
    for(int j=0;j<3;j++)
    {
      if ((grille_[j]==joueur) && (grille_[3+j]==joueur) && (grille_[6+j]==joueur))
      {
        return joueur ;
      }
    }
    //on teste les diagonales
    if ((grille_[0]==joueur) && (grille_[4]==joueur) && (joueur==grille_[8]))
    {
      return joueur;
    }
    if ((grille_[2]==joueur) && (grille_[4]==joueur) && (grille_[6]==joueur))
    {
      return joueur;
    }
  }
  return matche_nul ;
}

bool grille::jouer(int i,int j,int joueur){
    if(this->valeur()==1 || this->valeur()==0){return false;}
    if (grille_[co_to_int(i,j)]==-1 && i<4 && j<4){grille_[co_to_int(i,j)]=joueur;return true;}
    else 
      return false;
}
  


class position_tictactoe : public position
{
  public:
  grille position_actuelle ;
  virtual float valeur();
  position_tictactoe(int ,grille);
	virtual position_tictactoe* genererposition();
	~position_tictactoe(){};
  virtual void affiche(){position_actuelle.afficher_grille();}
	
};
  
position_tictactoe :: position_tictactoe(int j1,grille g1)
{
  psoeur = nullptr;
  pfille = nullptr;
	position_actuelle=g1;
  joueur=j1;
}

float position_tictactoe :: valeur()
{
  int val=position_actuelle.valeur();
  if(val==1)
  {
    return INFINITY ; 
  }
	if(val==0)
  {
    return -INFINITY; 
  }  
  return 0; 
}  


position_tictactoe* position_tictactoe::genererposition()
{
  position_tictactoe* currentPos; 
  int start=0;
  for(int i=1;i<4;i++)
  {
    for(int j=1;j<4;j++)
    {
      if(start==0)
      {
      grille position_fille=position_actuelle ;
        if (position_fille.jouer(i,j,1-joueur))
        { 
          pfille = new position_tictactoe(1-joueur,position_fille);
          start+=1;
          currentPos=dynamic_cast<position_tictactoe *>(pfille);
        }

      }
      
      else
      {
        grille position_fille=position_actuelle ;
        if (position_fille.jouer(i,j,1-joueur))
        {   
        currentPos->psoeur = new position_tictactoe(1-joueur,position_fille);
        currentPos=dynamic_cast<position_tictactoe *>(currentPos->psoeur);
        }
      }
    }
  }
  return dynamic_cast<position_tictactoe *>(pfille);
   
}


int main()
{
  int k=0;
  cout<<"Bonjour et bienvenu dans notre jeu."<<endl;
  while(k==0){
    grille g;
    position_tictactoe jeu(0,g);
    //humain 0 et machine 1
    while(jeu.position_actuelle.grille_pleine()== false || jeu.valeur()==0){
      int i,j;
      cout<<"A vous de jouer:"<<endl;
      cin>>i>>j;
      while(jeu.position_actuelle.jouer(i,j,0)==false && jeu.position_actuelle.grille_pleine()== false){;
        cout<<"Coup impossible :"<<endl;
        cin>>i>>j;
      }

      if (jeu.valeur()!=0){cout<<"Bravo !!"<<endl;break;}
      if(jeu.position_actuelle.grille_pleine()== true){cout<<"Match null"<<endl;break;}
      (dynamic_cast<position *>(&jeu))->joueur=0;
      jeu.affiche();
      cout<<endl;
      jeu=*dynamic_cast<position_tictactoe *>(minmax(9,&jeu));
      cout<<"Ordi joue :"<<endl;
      jeu.affiche();
      cout<<endl;
      if (jeu.valeur()!=0){cout<<"l'ordi a gagné"<<endl;break;}
      if(jeu.position_actuelle.grille_pleine()== true){cout<<"Match nul:"<<endl;}

    }
  cout<<"Si vous voulez rejouer pressez 0:"<<endl;
  cin>>k;
  }
  return 0 ;
}

/*
Pour activer le mode debug
g++ -ggdb tictactoe.cpp 
gdb -c core a.out 
bt full
*/

/* //test de la fonction generer
  jeu.genererposition();
  position_tictactoe* jeufille=dynamic_cast<position_tictactoe*>(jeu.pfille);
  position_tictactoe* courant=dynamic_cast<position_tictactoe*>(jeufille->psoeur);
  jeufille->affiche();
  while(courant!=0){
    dynamic_cast<position_tictactoe*>(courant)->affiche();
    courant=dynamic_cast<position_tictactoe*>(courant->psoeur);
  }*/