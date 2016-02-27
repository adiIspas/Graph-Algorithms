#include <iostream>
#include <fstream>
#include <cstdlib>
#include <set>

using namespace std;

int main()
{
    fstream f("input.in");

    int i, j, k, sw;
    int nr_noduri, nr_muchii, nod_1, nod_2, cost_nod, ex_min, centr, ex_min_lin, centr_lin, diametru;
    int graf[25][25], cost[25][25], distanta[100][100], parinte[100][100];

    set<int> centru;
    set<int>::iterator it;

    f >> nr_noduri >> nr_muchii;

    for(i = 0; i <= nr_noduri; i++)
        for(j = 0; j <= nr_noduri; j++)
            {
                graf[i][j] = 0;
                cost[i][j] = 0;

                if(i == j)
                    distanta[i][j] = 0;
                else
                    distanta[i][j] = 99;
            }

    for(i = 1; i <= nr_muchii; i++)
        {
            f >> nod_1 >> nod_2 >> cost_nod;

            graf[nod_1][nod_2] = 1;
            graf[nod_2][nod_1] = 1;

            cost[nod_1][nod_2] = cost_nod;
            cost[nod_2][nod_1] = cost_nod;
        }

    for(i = 1; i <= nr_noduri; i++)
        for(j = 1; j <= nr_noduri; j++)
            if(graf[i][j])
                distanta[i][j] = cost[i][j];


    for(k = 1; k <= nr_noduri; k++)
        for(i = 1; i <= nr_noduri; i++)
            for(j = 1; j <= nr_noduri; j++)
                if(distanta[i][j] > distanta[i][k] + distanta[k][j])
                    distanta[i][j] = distanta[i][k] + distanta[k][j];

    ex_min = 99;
    diametru = 0;
    for(i = 1; i <= nr_noduri; i++)
        {
            ex_min_lin = 0;
            for(j = 1; j <= nr_noduri; j++)
                {
                    if(distanta[i][j] > diametru)
                        diametru = distanta[i][j];

                    if(distanta[i][j] > ex_min_lin)
                        {
                            ex_min_lin = distanta[i][j];
                            centr_lin = i;
                        }
                }

            if(ex_min > ex_min_lin)
                {
                    //centr = centr_lin;
                    //centru.insert(centr_lin);
                    ex_min = ex_min_lin;
                }
        }

    cout << "Diametru: " << diametru << endl;
    cout << "Raza: " << ex_min << endl;

    for(i = 1; i <= nr_noduri; i++)
        {
            sw = 1;
            for(j = 1; j <= nr_noduri; j++)
                if(distanta[i][j] > ex_min)
                    {
                        sw = 0;
                        break;
                    }
            if(sw)
                centru.insert(i);
        }

    cout << "Centru: ";
    for(it = centru.begin(); it != centru.end(); ++it)
        cout << *it << " ";

    return 0;
}
