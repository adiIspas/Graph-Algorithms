#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <utility>

using namespace std;

int Verificare_MSaturat(int nr_noduri, int cuplaj[100])
    {
        int i;
        for(i = 1; i <= nr_noduri; i++)
            if(!cuplaj[i])
                return 0;

        return 1;
    }

int main()
{
    fstream f("input.in");
    vector<int> graf[100];
    vector<pair<int,int> > P, M, Reuniune, Perechi_Comune;
    pair<int,int> pereche;
    queue<int> coada;
    set<int> S, T, Vecini_S;
    set<int>::iterator it1;
    set<int>::iterator it2;

    int i, j, x, y, u;
    int sw, nod, nod_cuplat, gasit, culoare, nr_noduri, nr_muchii, terminat, intrare;
    int culori[100], cuplaj[100], lant[100], verificat[100];

    /// BEGIN - Citire graf
    f >> nr_noduri >> nr_muchii;

    for(i = 1; i <= nr_muchii; i++)
        {
            f >> x >> y;
            graf[x].push_back(y);
            graf[y].push_back(x);
        }
    /// END - Citire graf
    if(nr_noduri%2 != 0)
        {
            cout << "Nu exista cuplaj perfect!";
            return 0;
        }
    /// BEGIN - Initializare date
    for(i = 0; i <= nr_noduri; i++)
        {
            culori[i] = 0;
            cuplaj[i] = 0;
            lant[i] = 0;
            verificat[i] = 0;
        }
    terminat = 0;
    intrare = 0;
    /// END - Initializare date

    /// BEGIN - Determinare graf bipartit
    culoare = 1;
    culori[1] = culoare;
    coada.push(1);

    while(!coada.empty())
        {
            nod = coada.front();
            coada.pop();

            culoare = culori[nod];
            if(culoare == 1)
                culoare = 2;
            else
                culoare = 1;

            for(i = 0; i < graf[nod].size(); i++)
                if(!culori[graf[nod][i]])
                    {
                        culori[graf[nod][i]] = culoare;
                        coada.push(graf[nod][i]);
                    }
        }
    /// END - Determinare graf bipartit

    /// BEGIN - Verificare daca este bipartit
    for(i = 1; i <= nr_noduri; i++)
        for(j = 0; j < graf[i].size(); j++)
            if(culori[i] == culori[graf[i][j]])
                {
                    cout << "Nu este bipartit!";
                    return 0;
                }
    /// END - Verificare daca este bipartit

    /// BEGIN - Generare cuplaj de start
    for(i = 1; i <= nr_noduri; i++)
        if(!cuplaj[i])
            for(j = 0; j < graf[i].size(); j++)
                if(!cuplaj[graf[i][j]])
                    {
                        cuplaj[i] = graf[i][j];
                        cuplaj[graf[i][j]] = i;
                        break;
                    }
    /// END - Generare cuplaj de start

    /// BEGIN - Cautare cuplaj perfect
    while(Verificare_MSaturat(nr_noduri,cuplaj) == 0 && terminat == 0)
        {
            /// setam intrarea de bucla
            intrare = 0;

            /// golim S, T;
            S.clear();
            T.clear();

            /// BEGIN - Cautare u varf nesaturat
            for(i = 1; i <= nr_noduri; i++)
                if(!cuplaj[i])
                    {
                        u = i;
                        break;
                    }

            S.insert(u);
            /// END - Cautare u varf nesaturat

            /// BEGIN - Cautare noduri pentru S si T
            while(!intrare)
            {
                /// Salvam vecini lui S
                for(it1 = S.begin(); it1 != S.end(); ++it1)
                    for(i = 0; i < graf[*it1].size(); i++)
                        Vecini_S.insert(graf[*it1][i]);

                /// Verficam daca vecini lui S sunt nodurile lui T
                if(Vecini_S == T)
                    {
                        cout << "Nu exista cuplaj perfect!";
                        return 0;
                    }

                /// cautam un varf Y care apartine N(S) - T
                sw = 0;
                for(it1 = Vecini_S.begin(); it1 != Vecini_S.end(); ++it1)
                    if(sw == 0)
                        for(it2 = T.begin(); it2 != T.end(); ++it2)
                            if(*it1 != *it2 && verificat[*it1] == 0)
                                {
                                    y = *it1;
                                    verificat[y] = 1;
                                    sw = 1;
                                    break;
                                }

                /// verificam daca Y este saturat
                if(cuplaj[y])
                    {
                        T.insert(y);
                        S.insert(cuplaj[y]);
                    }
                else
                    intrare = 1;
            }
            /// END - Cautare noduri pentru S si T

            for(i = 1; i <= nr_noduri; i++)
                lant[i] = 0;

            /// BEGIN - Cautare lant P alternant
            gasit = 0;
            while(!gasit)
                {
                    if(lant[y] > 1)
                        {
                            cout << "Nu exista cuplaj perfect!";
                            return 0;
                        }

                    if(graf[y].size() == 0)
                        gasit = 1;

                    for(i = 0; i < graf[y].size(); i++)
                        if(cuplaj[graf[y][i]])
                            {
                                nod_cuplat = graf[y][i];
                                pereche = make_pair(y,nod_cuplat);
                                P.push_back(pereche);
                                pereche = make_pair(nod_cuplat,cuplaj[nod_cuplat]);
                                P.push_back(pereche);

                                lant[y]++;
                                lant[nod_cuplat]++;
                                lant[cuplaj[nod_cuplat]]++;

                                y = cuplaj[nod_cuplat];
                            }
                        else
                            if(graf[cuplaj[graf[y][i]]].size() == 0)
                                {
                                    gasit = 1;
                                    nod_cuplat = graf[y][i];

                                    pereche = make_pair(y,nod_cuplat);
                                    P.push_back(pereche);
                                }
                }
            /// END - Cautare lant P alternant

            /// BEGIN - Calculare diferenta simetrica
            /// Inserare muchii in M
            M.clear();
            for(i = 1; i <= nr_noduri; i++)
                verificat[i] = 0;

            for(i = 1; i <= nr_noduri; i++)
                if(cuplaj[i] != 0 && verificat[i] == 0)
                    {
                        verificat[i] = verificat[cuplaj[i]] = 1;

                        pereche = make_pair(i,cuplaj[i]);
                        M.push_back(pereche);
                    }

//            /// Calculam M \ P
//            for(i = 0; i < M.size(); i++)
//                for(j = 0; j < P.size(); j++)
//                    if((M[i].first != P[i].first && M[i].first != P[i].second) || (M[i].second != P[i].first && M[i].second != P[i].second))
//                        //cout << M[i].first << " " << M[i].second << endl;
//                        Reuniune.push_back(M[i]);
//
//            //cout << endl << endl;
//
//            /// Calculam P \ M
//            for(i = 0; i < P.size(); i++)
//                for(j = 0; j < M.size(); j++)
//                    if((P[i].first != M[i].first && P[i].first != M[i].second) || (P[i].second != M[i].first && P[i].second != M[i].second))
//                        cout << P[i].first << " " << P[i].second << endl;
//                        //Reuniune.push_back(P[i]);

            for(i = 0; i < M.size(); i++)
                for(j = 0; j < P.size(); j++)
                    if(M[i] == P[j])
                        Perechi_Comune.push_back(M[i]);

            for(i = 0; i < M.size(); i++)
                Reuniune.push_back(M[i]);
            for(i = 0; i < P.size(); i++)
                Reuniune.push_back(P[i]);

            for(i = 0; i < Perechi_Comune.size(); i++)
                for(j = 0; j < Reuniune.size(); j++)
                    if(Perechi_Comune[i] == Reuniune[j])
                        Reuniune.erase(Reuniune.begin() + j);
            /// END - Calculare diferenta simetrica

            /// Resetam cuplajele
            for(i = 1; i <= nr_noduri; i++)
                cuplaj[i] = 0;

            for(i = 0; i < Reuniune.size(); i++)
                {
                    cuplaj[Reuniune[i].first] = Reuniune[i].second;
                    cuplaj[Reuniune[i].second] = Reuniune[i].first;
                }
        }
    /// END - Cautare cuplaj perfect

    /// BEGIN - Afisare cuplaj
    for(i = 1; i <= nr_noduri; i++)
        if(!cuplaj[i])
            {
                cout << "Nu exista cuplaj perfect!";
                return 0;
            }

    for(i = 1; i <= nr_noduri; i++)
        verificat[i] = 0;

    cout << "Cuplajul perfect\n";
    for(i = 1; i <= nr_noduri; i++)
        if(!verificat[i])
        {
            cout << i << " " << cuplaj[i] << endl;
            verificat[i] = verificat[cuplaj[i]] = 1;
        }
    /// END - Afisare cuplaj

    return 0;
}
