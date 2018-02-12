#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tree
{
	char matrice[3][3];
	int dim;
	int tip;
	struct tree **fiu;
}tree;

int castigator(char matrice[3][3])
{
	if(matrice[0][0]==matrice[0][1] && matrice[0][1]==matrice[0][2] && matrice[0][2]!='-')
		return 1;
	if(matrice[1][0]==matrice[1][1] && matrice[1][1]==matrice[1][2] && matrice[1][2]!='-')
		return 1;
	if(matrice[2][0]==matrice[2][1] && matrice[2][1]==matrice[2][2] && matrice[2][2]!='-')
		return 1;

	if(matrice[0][0]==matrice[1][0] && matrice[1][0]==matrice[2][0] && matrice[2][0]!='-')
		return 1;
	if(matrice[0][1]==matrice[1][1] && matrice[1][1]==matrice[2][1] && matrice[2][1]!='-')
		return 1;
	if(matrice[0][2]==matrice[1][2] && matrice[1][2]==matrice[2][2] && matrice[2][2]!='-')
		return 1;

	if(matrice[0][0]==matrice[1][1] && matrice[1][1]==matrice[2][2] && matrice[2][2]!='-')
		return 1;
	if(matrice[0][2]==matrice[1][1] && matrice[1][1]==matrice[2][0] && matrice[2][0]!='-')
		return 1;

	return 0;
}

void copie_matrice(char matrice[3][3],char copie[3][3])
{
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			copie[i][j]= matrice[i][j];
}

int nrlinii(char matrice[3][3])
{
	int nrspatii=0;
	int i,j;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(matrice[i][j]=='-')
					nrspatii++;
	return nrspatii;
}

void arbore(tree** tabla, char jucator,int nrspatii_init,FILE* iesire)
{
	//cat timp nu s a castigat si nu s au terminat casutele
	int nrspatii;
	int i,j,k;
	nrspatii=nrlinii((*tabla)->matrice);
	int nrfiu=0;
	(*tabla)->dim = 0;
	if(castigator((*tabla)->matrice)==1)
	{
		(*tabla)->tip=1;
		return;
	}

	if(nrspatii==0)
	{	
		if(castigator((*tabla)->matrice)==0)
			(*tabla)->tip=0;
		return;
	}

	if(castigator((*tabla)->matrice)==0 && nrspatii!=0)
	{
		(*tabla)->fiu=(tree**)calloc((nrspatii),sizeof(tree*));
		for(k=0;k<nrspatii;k++)
		{	
			(*tabla)->fiu[k]=(tree*)calloc((nrspatii),sizeof(tree));
		}
		for(i=0;i<3;i++)
			for(j=0;j<3;j++)
				if((*tabla)->matrice[i][j]=='-')
				{
					
					copie_matrice((*tabla)->matrice,(*tabla)->fiu[nrfiu]->matrice);
					(*tabla)->fiu[nrfiu]->matrice[i][j]= jucator;
					(*tabla)->dim++;

					if(jucator=='X')
						arbore((&(*tabla)->fiu[nrfiu]),'O',nrspatii_init,iesire);
					else
						arbore((&(*tabla)->fiu[nrfiu]),'X',nrspatii_init,iesire);

					nrfiu++;

				}
	}

}

/*void task2(tree** tabla)
{
	int i;

	if(castigator((*tabla)->matrice)==1)
	{
		(*tabla)->tip=1;
		return;
	}

	if(nrspatii==0)
	{	
		if(castigator((*tabla)->matrice)==0)
			(*tabla)->tip=0;
		return;
	}	

	if(castigator((*tabla)->matrice)==0 && nrspatii!=0)
		for(i=0;i<(*tabla)->dim;i++)
				if((*tabla)->fiu[i])



}*/

void afisare(tree* tabla,FILE* iesire, int nrspatii_init)
{
	if(tabla==NULL)
		return;

	int nrfii;
	nrfii=nrlinii(tabla->matrice);
	int i,j;
	int k;
	k = nrspatii_init - nrfii;//nivelul

	for(i=0;i<3;i++)
	{

		for(j=0;j<k;j++)
			fprintf(iesire, "\t");
		fprintf(iesire, "%c %c %c\n",tabla->matrice[i][0],tabla->matrice[i][1],tabla->matrice[i][2]);
	}
	fprintf(iesire, "\n" );

	for(i=0;i<tabla->dim;i++)
	{	
		afisare(tabla->fiu[i],iesire,nrspatii_init);
	}

}

void delete_tree(tree *tabla)
{
    int i = 0;

    if((tabla )->dim==0)
    {

       free(tabla);
    }
    else
    {
        for(i = 0; i < (tabla)->dim; i ++)
        {

                delete_tree(tabla -> fiu[i]);
          
        }
        free(tabla);
    }
    free((tabla)->fiu);
    //free(tabla);
}

int main(int argc, char *argv[])
{
	FILE* intrare;
	FILE* iesire;
	intrare = fopen(argv[2],"r");
	iesire = fopen(argv[3],"w");
	int i,j;
	char mutare;
	char pozitie;
	char next;

	if(argc == 1 || argc == 2 || argc ==3)
	{
		printf("[Eroare]: Nu s-au dat nr coresp de argumente de comanda.\n ");
		return 1;
	}

	if(argv[1][2]=='1')
	{
		fscanf(intrare,"%c",&mutare);
		fscanf(intrare,"%c",&next);
		tree *tabla;
		tabla = (tree*)calloc(1,sizeof(tree));
		tabla->fiu = NULL;  

		int nrspatii = 0;

		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{	
				fscanf(intrare,"%c",&pozitie);
				fscanf(intrare,"%c",&next);
				tabla->matrice[i][j]= pozitie;
				if(tabla->matrice[i][j]=='-')
					nrspatii++;
			}
		}

		if(mutare=='X')
			arbore(&tabla,'X',nrspatii,iesire);
		else
			arbore(&tabla,'O',nrspatii,iesire);

		afisare(tabla,iesire,nrspatii);

		delete_tree(tabla);
		//free(tabla);
	}

	fclose(intrare);
	fclose(iesire);
	return 0;

}
