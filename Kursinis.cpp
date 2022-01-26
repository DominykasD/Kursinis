#include <iostream>
#include <iomanip>
#include <cmath>
#include <time.h>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;

#define max_Bombos 99
#define max_Dydis 25
#define max_ejimu 526


int Dydis;
int Bombos;

int eil;
int stulp;

class PasirinkSunkuma {

    protected:
        int Dydis;
        int Bombos;
        int var;

    public:
        void Sunkumas(int a, int b, int c)
        {
            Dydis = a;
            Bombos = b;
            var = c;

            if (var == 0)
            {
                Dydis = 9;
                Bombos = 10;
            }
            else
            if (var == 1)
            {
                Dydis = 16;
                Bombos = 40;
            }
            else
            if(var == 2)
            {
                Dydis = 24;
                Bombos = 99;
            }
            else
			exit(0);
        }


};

class MinuLaukas : public PasirinkSunkuma {

public:

    void zaisti()
	{
		bool zaidimo_pabaiga = false;

		int liko_ejimu = Dydis * Dydis - Bombos;

		int bombos[max_Bombos][2]; //saugo eilutes ir stulpelius visu bombu

		char lenta[max_Dydis][max_Dydis], mano_lenta[max_Dydis][max_Dydis];

		pradinis(lenta, mano_lenta);

        SudetiBombas(bombos, lenta);

		int x, y;

		int pradinis_ejimas = 0;

		while(zaidimo_pabaiga == false)
		{
			cout << "Dabartine lenta: " << endl;
			rodyti_lenta(mano_lenta);
			ejimas(&x,&y);

			//jei pirmas bandymas mina
			if(pradinis_ejimas == 0)
			{
				if(yra_bombu(x, y, lenta) == true) // jei pirmas bandymas mina
					pakeisti_bomba(x, y, lenta); //pakeicia mina toj vietos
			}

			pradinis_ejimas++;

			zaidimo_pabaiga = zaidzia(mano_lenta, lenta, bombos, x, y, &liko_ejimu);

			if((zaidimo_pabaiga == false) && (liko_ejimu == 0))
			{
				cout << "Jus laimejote!" << endl;
				zaidimo_pabaiga = true;
				exit(0);
			}
		}


	}

	void pradinis(char lenta[][max_Dydis], char mano_lenta[][max_Dydis])
	{
		srand(time(NULL)); //random lenta, kad nesikartotu

		for(int i = 0; i < Dydis; i++)
			for(int j = 0; j < Dydis; j++)
			{
				mano_lenta[i][j] = lenta[i][j] = '-';
			}
			return;
	}

	void rodyti_lenta(char mano_lenta[][max_Dydis])
	{
		printf("\n\n\t\t\t    ");

		for(int i = 0; i < Dydis; i++)
		{
			if (i > 9) printf("%d ", i / 10);
			else printf("  ");
		}

		printf("\n\t\t\t    ");

		for(int i = 0; i < Dydis; i++) printf("%d ", i % 10);

		printf("\n\n");

		for(int i = 0; i < Dydis; i++)
		{
			printf("\t\t\t    ");
			for(int j = 0; j < Dydis; j++){
				printf("%c ", mano_lenta[i][j]);
			}
			printf(" %2d",i);
			printf("\n");
		}
		return;
	}

	void ejimas(int *x,int *y)
	{
		printf("\nIveskite ejima (eilute, stulpelis) ");
		scanf("%d %d", x, y);
		return;
	}

	bool ArGalima(int eilute, int stulpelis)
	{
		return (eilute >= 0) && (eilute < Dydis) && (stulpelis >= 0) && (stulpelis < Dydis);
	}

	void SudetiBombas(int bombos[][2], char lenta[][max_Dydis])
	{
		bool pazymeti[max_Dydis * max_Dydis];

		memset(pazymeti, false, sizeof(pazymeti)); // uzpildo pazymeti bombu vietomis

		for(int i = 0; i < Bombos;)
		{
			int random = rand() % (Dydis * Dydis);
			int x = random / Dydis;
			int y = random % Dydis;

			if(pazymeti[random] == false) //prideti mina jei random pozicijoje jos nera
			{
				bombos[i][0] = x;
				bombos[i][1] = y;

				lenta[bombos[i][0]][bombos[i][1]] = '*';
				pazymeti[random] = true;
				i++;
			}
		}
	}

	bool yra_bombu(int eilute, int stulpelis, char lents[][max_Dydis])
	{
		if(lents[eilute][stulpelis] == '*') return true;
		else return false;
	}

	int skaic_greta(int eilute, int stulpelis, int bombos[][2], char lenta[][max_Dydis])
	{
		int count = 0;

		// jei galimas tokia eilute stulpelis, ir jei ten bomba ++
		if(ArGalima(eilute - 1, stulpelis) == true)
		{
			if(yra_bombu(eilute - 1, stulpelis, lenta) == true) count++;
		}
		if(ArGalima(eilute + 1, stulpelis) == true)
		{
			if(yra_bombu(eilute + 1, stulpelis, lenta) == true) count++;
		}

		if(ArGalima(eilute, stulpelis + 1) == true)
		{
			if(yra_bombu(eilute, stulpelis + 1, lenta)==true) count++;
		}
		if(ArGalima(eilute, stulpelis - 1) == true)
		{
			if(yra_bombu(eilute, stulpelis - 1, lenta) == true) count++;
		}
		if(ArGalima(eilute - 1, stulpelis - 1) == true)
		{
			if(yra_bombu(eilute - 1, stulpelis - 1, lenta) == true) count++;
		}
		if(ArGalima(eilute - 1, stulpelis + 1) == true)
		{
			if(yra_bombu(eilute - 1, stulpelis + 1, lenta) == true) count++;
		}
		if(ArGalima(eilute + 1, stulpelis - 1) == true)
		{
			if(yra_bombu(eilute + 1, stulpelis - 1, lenta) == true) count++;
		}
		if(ArGalima(eilute + 1, stulpelis + 1) == true)
		{
			if(yra_bombu(eilute + 1, stulpelis + 1, lenta) == true) count++;
		}
		return count;

	}

	void pakeisti_bomba(int eilute, int stulpelis, char lents[][max_Dydis])
		{

			// pakeicia, kad pirmas nebutu bomba
			for(int i = 0; i < Dydis; i++)
			{
				for(int j = 0; j < Dydis; j++)
				{
					if(lents[i][j] != '*')
					{
						lents[i][j] = '*';
						lents[eilute][stulpelis]='-';
						return;
					}
				}

			}

		}

    bool zaidzia(char mano_lenta[][max_Dydis], char lenta[][max_Dydis], int bombos[][2], int eilute, int stulpelis, int *liko_ejimu)
	{
		if(mano_lenta[eilute][stulpelis] != '-') return false;

		if(lenta[eilute][stulpelis] == '*')
		{
			mano_lenta[eilute][stulpelis] = '*';
			for(int i = 0; i < Bombos; i++) mano_lenta[bombos[i][0]][bombos[i][1]] = '*';
			rodyti_lenta(mano_lenta);
			cout << "Jus pralaimejote!" << endl;
			exit(0);
			return true;
		}
		else
		{
			int count = skaic_greta(eilute, stulpelis, bombos, lenta);
			(*liko_ejimu)--;

			mano_lenta[eilute][stulpelis] = count + '0';

			if(!count)
			{

				if(ArGalima(eilute - 1, stulpelis) == true)
				{
					if(yra_bombu(eilute - 1, stulpelis, lenta) == false)
						zaidzia(mano_lenta, lenta, bombos, eilute - 1, stulpelis, liko_ejimu);
				}


				if (ArGalima(eilute + 1, stulpelis) == true)
				{
					if (yra_bombu(eilute + 1, stulpelis, lenta) == false)
						zaidzia(mano_lenta, lenta, bombos, eilute + 1, stulpelis, liko_ejimu);
				}

				if (ArGalima(eilute, stulpelis + 1) == true)
				{
					if (yra_bombu(eilute, stulpelis + 1, lenta) == false)
						zaidzia(mano_lenta, lenta, bombos, eilute, stulpelis + 1, liko_ejimu);
				}

				if (ArGalima(eilute, stulpelis - 1) == true)
				{
					if (yra_bombu(eilute, stulpelis - 1, lenta) == false)
						zaidzia(mano_lenta, lenta, bombos, eilute, stulpelis - 1, liko_ejimu);
				}

				if (ArGalima(eilute - 1, stulpelis + 1) == true)
				{
					if (yra_bombu(eilute - 1, stulpelis + 1, lenta) == false)
						zaidzia(mano_lenta, lenta, bombos, eilute - 1, stulpelis + 1, liko_ejimu);
				}

				if (ArGalima(eilute - 1, stulpelis - 1) == true)
				{
					if (yra_bombu(eilute - 1, stulpelis - 1, lenta) == false)
						zaidzia(mano_lenta, lenta, bombos, eilute - 1, stulpelis - 1, liko_ejimu);
				}

				if (ArGalima(eilute + 1, stulpelis + 1) == true)
				{
					if (yra_bombu(eilute + 1, stulpelis + 1, lenta) == false)
						zaidzia(mano_lenta, lenta, bombos, eilute + 1, stulpelis + 1, liko_ejimu);
				}

				if (ArGalima(eilute + 1, stulpelis - 1) == true)
				{
					if (yra_bombu(eilute + 1, stulpelis - 1, lenta) == false)
						zaidzia(mano_lenta, lenta, bombos, eilute + 1, stulpelis - 1, liko_ejimu);
				}
			}
			return false;
		}
	}

};


int main ()
{
    int var;
    cout << "Iveskite norima sudetingumo lygi: " << endl;
    cout << "0 - pradedantysis, 1 - vidutinis, 2 - sunkus" << endl;
    cin >> var;

    int *x, *y;
    char lenta[max_Dydis][max_Dydis], mano_lenta[max_Dydis][max_Dydis];
    int eilute, stulpelis;
    char lents[max_Dydis][max_Dydis];
    int bombos[max_Bombos][2]; //saugo eilutes ir stulpelius visu bombu
    int *liko_ejimu;


    PasirinkSunkuma sunku;
    sunku.Sunkumas(Dydis, Bombos, var);

    ////////////////////

    MinuLaukas play;
    PasirinkSunkuma *sunkuzaid = &play;
    sunkuzaid->Sunkumas(Dydis, Bombos, var);
    play.zaisti();
    play.pradinis(lenta, mano_lenta);
    play.SudetiBombas(bombos, lenta);
    play.rodyti_lenta(mano_lenta);
    //
    play.ejimas(x, y);
    ////
    play.ArGalima(eilute, stulpelis);
    play.yra_bombu(eilute, stulpelis, lents);
    play.skaic_greta(eilute, stulpelis, bombos, lenta);
    play.pakeisti_bomba(eilute, stulpelis, lents);
    play.zaidzia(mano_lenta, lenta, bombos, eilute, stulpelis, liko_ejimu);
    return 0;
}
