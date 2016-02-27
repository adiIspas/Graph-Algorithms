#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <queue>

using namespace std;

int dg_minus[100], coada[100], distanta[100], parinte[100], puncte_control[100], drum[100];

int main()
{
    ifstream f("input.in");

    int i, j, dist_minim, punct_control;
    int nr_noduri, nr_muchii, nod_plecare, nod_destinatie, pondere, nod_aux, nod_curent, cost, nr_pct_control;

    vector<pair<int,int> > graf[100];
    pair<int,int> pereche;

    f >> nr_noduri >> nr_muchii;

    for(i = 0; i < nr_muchii; i++)
        {
            f >> nod_plecare >> nod_destinatie >> pondere;
            dg_minus[nod_destinatie]++;

            pereche = make_pair(nod_destinatie,pondere);
            graf[nod_plecare].push_back(pereche);
        }

    coada[0] = 0;
    for(i = 1; i <= nr_noduri; i++)
        {
            distanta[i] = 99;
            if(dg_minus[i] == 0)
                coada[++coada[0]] = i;
        }

    for(i = 1; i <= nr_noduri; i++)
        {
            nod_aux = coada[i];

            for(j = 0; j < graf[nod_aux].size(); j++)
                {
                    dg_minus[graf[nod_aux][j].first]--;
                    if(dg_minus[graf[nod_aux][j].first] == 0)
                        coada[++coada[0]] = graf[nod_aux][j].first;
                }
        }

    cout << "Nodul de start: ";
    cin >> nod_plecare;
    cout << "Nr. de puncte de control: ";
    cin >> nr_pct_control;
    for(i = 1; i <= nr_pct_control; i++)
        {
            cout << "Punctul " << i << " de control: ";
            cin >> puncte_control[i];
        }

    distanta[nod_plecare] = 0;
    for(j = 1; j <= nr_noduri; j++)
        {
            nod_curent = coada[j];

            for(i = 0; i < graf[nod_curent].size(); i++)
                {
                    nod_aux = graf[nod_curent][i].first;
                    cost = graf[nod_curent][i].second;

                    if(distanta[nod_aux] > distanta[nod_curent] + cost)
                        {
                            distanta[nod_aux] = distanta[nod_curent] + cost;
                            parinte[nod_aux] = nod_curent;
                        }
                }
        }

    dist_minim = 99;
    punct_control = 0;
    for(i = 1; i <= nr_pct_control; i++)
       if(dist_minim > distanta[puncte_control[i]])
        {
            punct_control = puncte_control[i];
            dist_minim = distanta[puncte_control[i]];
        }

    if(punct_control == 0)
        {
            cout << "\nNu exista!\n";
            return 0;
        }

    cout << "\nCel mai apropiat punct de control de " << nod_plecare << " este " << punct_control << " de cost " << dist_minim << "."<< endl;
    cout << "Drumul de la " << nod_plecare << " la " << punct_control << " este: ";
    i = 0;
    drum[i] = parinte[punct_control];
    while(parinte[punct_control])
        {
            parinte[punct_control] = parinte[parinte[punct_control]];
            if(parinte[punct_control])
                {
                    i++;
                    drum[i] = parinte[punct_control];
                }

        }

    while(i >= 0)
        {
            cout << drum[i] << " ";
            i--;
        }
    cout << punct_control << endl;

    return 0;
}
