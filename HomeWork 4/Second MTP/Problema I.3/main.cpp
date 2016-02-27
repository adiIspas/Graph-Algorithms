///Arborele partial de cost minim KRUSKAL

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

int p[100], h[100], vizitat[100], parinte[100], cost_lant[100][100], noduri_arbore[100], maxim[100][100];

int FindSet(int u)
    {
        if(p[u] == 0)
            return u;

        p[u] = FindSet(p[u]);
        return p[u];
    }

void Union(int u, int v)
    {
        u = FindSet(u);
        v = FindSet(v);

        if(h[u] > h[v])
            p[v] = u;
        else
            {
                p[u] = v;
                if(h[u] == h[v])
                    h[v]++;
            }
    }

int main ()
{
    FILE *f = fopen("apm.in","r");
    FILE *g = fopen("apm.out","w");

    int i, j, l, n, m, x, y, z, k, u, v, sw1, sw, info;
    int max_pondere = 0, cost_arbore_minim = 0, first, second, arbore_minim;
    int cost_minim = 999, cost_muchie, nr_arbore = 1, nod, costuri_arbore[100][100], costuri_graf[100][100];

    vector<int> muchii[100], pondere[100], pondere_arbore[100], primul_arbore[100], al_doilea_arbore[100][100];
    vector<pair<int,int> > sortare[100], sortare_arbore[100];
    //vector<pair<int,pair<int,int> > > maxim[100][100];
    pair<int,int> pereche, muchie;
    pair<int,pair<int,int> > pereche2;
    queue<int> q;

    fscanf(f,"%d%d",&n,&m);

    for(i = 0; i < m; i++)
        {
            fscanf(f,"%d%d%d",&x,&y,&z);

            muchii[x].push_back(y);
            pondere[x].push_back(z);
            costuri_graf[x][y] = z;

            //muchii[y].push_back(x);
            //pondere[y].push_back(z);

            costuri_graf[y][z] = z;

            if(max_pondere < z)
                max_pondere = z;

            pereche = make_pair(x,y);

            sortare[z].push_back(pereche);
        }

    m = 0;
    for(i = 0; i <= max_pondere; i++)
        for(j = 0; j < sortare[i].size(); j++)
            if(FindSet(sortare[i][j].first) != FindSet(sortare[i][j].second))
                {
                    primul_arbore[sortare[i][j].first].push_back(sortare[i][j].second);
                    costuri_arbore[sortare[i][j].first][sortare[i][j].second] = i;
                    costuri_arbore[sortare[i][j].second][sortare[i][j].first] = i;
                    pereche = make_pair(sortare[i][j].first,sortare[i][j].second);
                   // sortare_arbore[i].push_back(pereche);
                    Union(sortare[i][j].first,sortare[i][j].second);

                    for(l = 0; l < muchii[sortare[i][j].first].size(); l++)
                        if(muchii[sortare[i][j].first][l] == sortare[i][j].second)
                            {
                                muchii[sortare[i][j].first].erase(muchii[sortare[i][j].first].begin() + l);
                                pondere[sortare[i][j].first].erase(pondere[sortare[i][j].first].begin() + l);
                            }

                    for(l = 0; l < muchii[sortare[i][j].second].size(); l++)
                        if(muchii[sortare[i][j].second][l] == sortare[i][j].first)
                            {
                                muchii[sortare[i][j].second].erase(muchii[sortare[i][j].second].begin() + l);
                                pondere[sortare[i][j].second].erase(pondere[sortare[i][j].second].begin() + l);
                            }

                    sortare[i].erase(sortare[i].begin() + j);

                    m++;
                    cost_arbore_minim += i;

                    if(m == n - 1)
                        break;
                }

    /// Primul arbore de cost minim

     for(i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            if(!costuri_arbore[i][j])
                costuri_arbore[i][j] = 0;

     /*for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= n; j++)
            cout <<costuri_arbore[i][j] << " ";
            cout << endl;
        }

    cout << endl;*/

    fprintf(g,"%d\n",cost_arbore_minim);
    for(i = 1; i <= n; i++)
        for(j = 0; j < primul_arbore[i].size(); j++)
            fprintf(g,"%d %d\n",i, primul_arbore[i][j]);


    /// Al doilea arbore de cost minim

    for(i = 1; i <= n; i++)
        {
            for(j = 0; j < muchii[i].size(); j++)
                {
                    for(l = 1; l <= n; l++)
                        for(k = 0; k < primul_arbore[l].size(); k++)
                            al_doilea_arbore[nr_arbore][l].push_back(primul_arbore[l][k]);


                    vizitat[i] = 1;
                    q.push(i);

                    while (!q.empty())
                        {
                            nod = q.front();
                            q.pop();
                            //cout << nod << " ";
                            vizitat[nod] = 1;
                            for(l = 0; l < al_doilea_arbore[nr_arbore][nod].size(); l++)
                                if(vizitat[al_doilea_arbore[nr_arbore][nod][l]] == 0)
                                    {
                                        vizitat[al_doilea_arbore[nr_arbore][nod][l]] = 1;
                                        parinte[al_doilea_arbore[nr_arbore][nod][l]] = nod;

                                        //cout << nod << " " << al_doilea_arbore[nr_arbore][nod][l] << endl;
                                        q.push(al_doilea_arbore[nr_arbore][nod][l]);
                                    }
                        }

                    nod =  muchii[i][j];
                    cost_muchie = 0;
                    while(parinte[nod])
                    {
                        if(costuri_arbore[nod][parinte[nod]] > cost_muchie)
                            {
                                first = nod;
                                second = parinte[nod];
                                cost_muchie = costuri_arbore[nod][parinte[nod]];
                            }

                        nod = parinte[nod];
                    }

                    cout << first << " " << second << " " << cost_muchie << endl;
                    cout << i << " " << muchii[i][j] << " " << costuri_graf[i][muchii[i][j]] << endl;
                    cout << cost_arbore_minim << " " << cost_arbore_minim - cost_muchie + costuri_graf[i][muchii[i][j]] << endl << endl;

                    if(cost_minim > cost_arbore_minim - cost_muchie + costuri_graf[i][muchii[i][j]])
                        {
                            cost_minim = cost_arbore_minim - cost_muchie + costuri_graf[i][muchii[i][j]];
                            arbore_minim = nr_arbore;
                        }

                    //cout << cost_minim << endl << endl;

                    for(l = 0; l < al_doilea_arbore[nr_arbore][first].size(); l++)
                        if(al_doilea_arbore[nr_arbore][first][l] == second)
                            {
                                al_doilea_arbore[nr_arbore][first].erase(al_doilea_arbore[nr_arbore][first].begin() + l);
                                break;
                            }

                    for(l = 0; l < al_doilea_arbore[nr_arbore][second].size(); l++)
                        if(al_doilea_arbore[nr_arbore][second][l] == first)
                            {
                                al_doilea_arbore[nr_arbore][second].erase(al_doilea_arbore[nr_arbore][second].begin() + l);
                                break;
                            }

                    if(first == i)
                        al_doilea_arbore[nr_arbore][first].push_back(muchii[i][j]);
                    else
                    if(first == muchii[i][j])
                        al_doilea_arbore[nr_arbore][first].push_back(i);

                    /*else
                    if(second == i)
                        al_doilea_arbore[nr_arbore][second].push_back(muchii[i][j]);
                    else
                    if(second == muchii[i][j])
                        al_doilea_arbore[nr_arbore][second].push_back(i);*/

                    cout << cost_minim << endl;
                    for(l = 1; l <= n; l++)
                        for(k = 0; k < al_doilea_arbore[nr_arbore][l].size(); k++)
                            cout << l << " " << al_doilea_arbore[nr_arbore][l][k] << endl;

                    cout << endl << endl;

                    for(l = 1; l <= n; l++)
                        {
                            vizitat[l] = 0;
                            parinte[l] = 0;
                        }

                    nr_arbore++;
                }
        }

    cout << nr_arbore;

    return 0;
}
