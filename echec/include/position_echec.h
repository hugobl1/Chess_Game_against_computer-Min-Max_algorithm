#ifndef POSITION_ECHEC_H
#define POSITION_ECHEC_H

#include <vector>
#include "echiquier.h"

class position_echec
{
    public:
        vector<coup> liste;
        position_echec* pfille;
        position_echec* psoeur;
        int joueur; //On considère que le joueur blanc a pour indicateur 1 et le noir a pour indicateur 0, joueur qui doit jouer la position

        ~position_echec();
        position_echec(){liste={};pfille=0; psoeur=0;}
        position_echec(vector<coup> l,int joueur):liste(l),joueur(joueur){pfille=0; psoeur=0;}
        //les fonctions
        position_echec* getSoeur(){return psoeur;}
        position_echec* getFille(){return pfille;}
        float valeur(float alpha=1,float beta=1,float gamma=1, Couleur ordiCouleur=Blanc);
        position_echec* genererpositionfils();
        void print(){echiquier chess(liste);chess.print();}
        position_echec& operator=(const position_echec& pos){liste=pos.liste; pfille=pos.pfille;psoeur=pos.psoeur;joueur=pos.joueur;}
        bool check();
        bool checkmate();
};


inline double minmax_val(int deep,position_echec* P,Couleur ordiCouleur1){
	if (deep==0){return P->valeur(1,0.5,0.25,ordiCouleur1);}
	P->genererpositionfils();
	if (P->getFille() ==0){return P->valeur(1,0.5,0.25,ordiCouleur1);}
	double extremum=minmax_val(deep-1,P->getFille(),ordiCouleur1);
	position_echec* courant=(P->getFille())->getSoeur();

	if (courant==0){return extremum;}
	if (courant->joueur==1){
		//max
		while(courant!=0){
			double temp=minmax_val(deep-1,courant,ordiCouleur1);
			if(temp >= extremum){extremum=temp;}
				courant=courant->getSoeur();
			}
		}

	if (courant==0){return extremum;}
	if (courant->joueur==0){
	//min
		while(courant!=0){
			double temp =minmax_val(deep-1,courant,ordiCouleur1);
			if(temp <= extremum){extremum=temp;}
				courant=courant->getSoeur();
			}
	}
	return extremum;
}

inline position_echec* minmax(int deep,position_echec* P,Couleur ordiCouleur){
	P->genererpositionfils();
	position_echec* extremum=P->pfille;
	if(extremum==0){return P;}
	position_echec* courant=(P->pfille)->psoeur;
	while(courant!=0){
		//max
		if(minmax_val(deep-1,extremum,ordiCouleur)<=minmax_val(deep-1,courant,ordiCouleur)){extremum=courant;}
		courant=courant->psoeur;
	}
	return extremum;
}

#endif // POSITION_ECHEC_H
