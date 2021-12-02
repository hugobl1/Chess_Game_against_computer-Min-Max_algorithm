#include<stdlib.h>
#ifndef POSITION
#define POSITION
class position
{
public:
	position* pfille;
	position* psoeur;
	int joueur;
	//les fonctions
    position(){psoeur=new position; pfille=new position;};
	~position();
};



#endif // POSITION

