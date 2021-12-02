#ifndef position_H
#define position_H

#include<iostream>
#include<stdlib.h>
/////On a joueur machine=1 et joueur humain=0

class position
{
public:
	position* psoeur;
	position* pfille;
	int joueur;
	//les fonctions
	virtual float valeur()=0;
	virtual position* genererposition()=0;
};



double minmax_val(int deep,position* P){
	if (deep==0){return P->valeur();}
	P->genererposition();
	if (P->pfille ==0){return P->valeur();}
	double extremum=minmax_val(deep-1,P->pfille);
	position* courant=(P->pfille)->psoeur;

	if (courant==0){return extremum;}
	if (courant->joueur==1){//joueur=1 C'est une machine
		//max
		while(courant!=0){//joueur=0 C'est un humain
			double temp=minmax_val(deep-1,courant);
			if(temp >= extremum){extremum=temp;}
				courant=courant->psoeur;
			}
		}

	if (courant==0){return extremum;}
	if (courant->joueur==0){
	//min
		while(courant!=0){
			double temp =minmax_val(deep-1,courant);
			if(temp <= extremum){extremum=temp;}
				courant=courant->psoeur;
			}
	}
	return extremum;
}

position* minmax(int deep,position* P){
	P->genererposition();
	position* extremum=P->pfille;
	if(extremum==0){return P;}
	position* courant=(P->pfille)->psoeur;
	while(courant!=0){
		//max
		if(minmax_val(deep-1,extremum)<=minmax_val(deep-1,courant))
			{extremum=courant;}
		courant=courant->psoeur;	
	}
	return extremum;
}

#endif