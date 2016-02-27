#include <iostream>
#include <vector>
#include <fstream>
#include <utility>
#include <queue>

using namespace std;

int parinte[100], drum[100], distanta[100], puncte_control[100];

int main()
{
    fstream f("dijkstra.in");
    ofstream g("dijkstra.out");

    int i, punct_control, dist_minim = 999;
    int nr_noduri, nr_muchii, nod_plecare, nod_destinatie, pondere, nod_curent, nod_aux, cost, nr_pct_control;

    vector<pair<int,int> > graf[100];
    pair<int,int> pereche;
    queue<int> coada;

    f >> nr_noduri >> nr_muchii;

    for(i = 0; i < nr_muchii; i++)
        {
            f >> nod_plecare >> nod_destinatie >> pondere;
            pereche = make_pair(nod_destinatie,pondere);

            graf[nod_plecare].push_back(pereche);
        }

    for(i = 1; i <= nr_noduri; i++)
        distanta[i] = 999;

    cout << "Nodul de start: ";
    cin >> nod_plecare;
    cout << "Nr. de puncte de control: ";
    cin >> nr_pct_control;
    for(i = 0; i < nr_pct_control; i++)
        {
            cout << "Punctul " << i + 1 << " de control: ";
            cin >> puncte_control[i];
        }
    distanta[nod_plecare] = 0;

    coada.push(nod_plecare);
    while(!coada.empty())
        {
            nod_curent = coada.front();
            coada.pop();

            for(i = 0; i < graf[nod_curent].size(); i++)
                {
                    nod_aux = graf[nod_curent][i].first;
                    cost = graf[nod_curent][i].second;

                    if(distanta[nod_aux] > distanta[nod_curent] + cost)
                        {
                            distanta[nod_aux] = distanta[nod_curent] + cost;
                            coada.push(nod_aux);
                            parinte[nod_aux] = nod_curent;
                        }
                }
        }

    for(i = 0; i < nr_pct_control; i++)
       if(dist_minim > distanta[puncte_control[i]])
        {
            punct_control = puncte_control[i];
            dist_minim = distanta[puncte_control[i]];
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
