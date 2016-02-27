///Arborele partial de cost minim KRUSKAL

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>

using namespace std;

int p[1000], h[1000], muchii[100][100], vizitat[100], cost_arbore[100][100], cost_graf[100][100], maxim[100][100], afisare_primul_arbore[100][100], afisare_al_doile_arbore[100][100];

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
    //FILE *g = fopen("apm.out","w");

    vector<int> muchii_graf[100], primul_arbore[100], al_doilea_arbore[25][100];
    vector<pair<int,int> > sortare[100], muchii_maxime[100];
    queue<int> q;
    pair<int,int> pereche;
    int i, j, n, m, x, y, z, nod, max_pondere = 0, cost_arbore_minim = 0, nr_arbori = 0, second_arbore, second_cost = 999;

    fscanf(f,"%d%d",&n,&m);

    for(i = 0; i < m; i++)
        {
            fscanf(f,"%d%d%d",&x,&y,&z);
            muchii[x][y] = 1;
            cost_graf[x][y] = z;
            cost_graf[y][x] = z;

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
                    primul_arbore[sortare[i][j].second].push_back(sortare[i][j].first);

                    muchii[sortare[i][j].first][sortare[i][j].second] = 0;
                    muchii[sortare[i][j].second][sortare[i][j].first] = 0;

                    cost_arbore[sortare[i][j].first][sortare[i][j].second] = i;
                    cost_arbore[sortare[i][j].second][sortare[i][j].first] = i;

                    Union(sortare[i][j].first,sortare[i][j].second);
                    sortare[i].erase(sortare[i].begin() + j);

                    m++;
                    cost_arbore_minim += i;

                    if(m == n - 1)
                        break;
                }

   /* fprintf(g,"%d\n",cost_arbore_minim);
    for(i = 1; i <= n; i++)
        for(j = 0; j < primul_arbore[i].size(); j++)
            fprintf(g,"%d %d\n",i, primul_arbore[i][j]);*/

    for(i = 1; i <= n; i++)
        for(j = 1; j <= n; j++)
            if(muchii[i][j])
                muchii_graf[i].push_back(j);

    /// muchii ramase
    /*for(i = 1; i <= n; i++)
        for(j = 0; j < muchii_graf[i].size(); j++)
            cout << i << " " << muchii_graf[i][j] << endl;

    for(i = 1; i <= max_pondere; i++)
        for(j = 0; j < sortare[i].size(); j++)
            cout << sortare[i][j].first << " " << sortare[i][j].second << endl;*/

   // cout << endl;

    for(i = 1; i <= n; i++)
        {

            q.push(i);
            while(!q.empty())
                {
                    nod = q.front();
                    q.pop();
                    vizitat[nod] = 1;

                    //cout << nod << " ";

                    for(j = 0; j < primul_arbore[nod].size(); j++)
                        if(!vizitat[primul_arbore[nod][j]])
                            {
                                q.push(primul_arbore[nod][j]);
                                vizitat[primul_arbore[nod][j]] = 1;
                                //parinte[primul_arbore[nod][j]] = nod;

                                if(cost_arbore[nod][primul_arbore[nod][j]] > maxim[i][primul_arbore[nod][j]])
                                    {
                                        maxim[i][primul_arbore[nod][j]] = cost_arbore[nod][primul_arbore[nod][j]];
                                        maxim[primul_arbore[nod][j]][i] = cost_arbore[nod][primul_arbore[nod][j]];
                                        pereche = make_pair(nod,primul_arbore[nod][j]);

                                        if(!muchii_maxime[cost_arbore[nod][primul_arbore[nod][j]]].size())
                                            muchii_maxime[cost_arbore[nod][primul_arbore[nod][j]]].push_back(pereche);
                                        else
                                        {
                                            muchii_maxime[cost_arbore[nod][primul_arbore[nod][j]]].clear();
                                            muchii_maxime[cost_arbore[nod][primul_arbore[nod][j]]].push_back(pereche);
                                        }
                                    }
                                //cout << nod << " " << primul_arbore[nod][j] << " " << cost_arbore[nod][primul_arbore[nod][j]] << endl;
                            }
                }

            for(j = 1; j <= n; j++)
                {
                    vizitat[j] = 0;
                    //parinte[j] = 0;
                }

           // cout << endl;

        }

    /// muchii maxime
   /* for(i = 1; i <= n; i++)
        {
            for(j = 1; j <= n; j++)
                if(muchii_maxime[maxim[i][j]].size())
                    cout << i << " " << j << " " << maxim[i][j] << " " << muchii_maxime[maxim[i][j]][0].first << " " << muchii_maxime[maxim[i][j]][0].second << endl;
            //cout << endl;

    */

    /// merge :)
    /*for(i = 1; i <= max_pondere; i++)
        for(j = 0; j < sortare[i].size(); j++)
            {
                cout << sortare[i][j].first << " " << sortare[i][j].second;
                if(muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]].size())
                    cout << " <-> " << muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].first << " " << muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].second << endl;

            }
    */

    for(i = 1; i <= max_pondere; i++)
        for(j = 0; j < sortare[i].size(); j++)
            {
                //cout << sortare[i][j].first << " " << sortare[i][j].second;

                nr_arbori++;
                for(x = 1; x <= n; x++)
                    for(y = 0; y < primul_arbore[x].size(); y++)
                        al_doilea_arbore[nr_arbori][x].push_back(primul_arbore[x][y]);

               /* if(muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]].size())
                    {
                        for(x = 0; x < al_doilea_arbore[nr_arbori][sortare[i][j].first].size(); x++)
                            if(al_doilea_arbore[nr_arbori][sortare[i][j].first][x] == sortare[i][j].second)
                                {
                                    al_doilea_arbore[nr_arbori][sortare[i][j].first].erase(al_doilea_arbore[nr_arbori][sortare[i][j].first].begin() + x);
                                    al_doilea_arbore[nr_arbori][muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].first].push_back(muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].second);
                                    break;
                                }
                */

                if(muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]].size())
                    {
                        for(x = 0; x < al_doilea_arbore[nr_arbori][muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].first].size(); x++)
                            if(al_doilea_arbore[nr_arbori][muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].first][x] == muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].second)
                                {
                                    al_doilea_arbore[nr_arbori][muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].first].erase(al_doilea_arbore[nr_arbori][muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].first].begin() + x);
                                    al_doilea_arbore[nr_arbori][sortare[i][j].first].push_back(sortare[i][j].second);
                                    break;
                                }

                        for(x = 0; x < al_doilea_arbore[nr_arbori][muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].second].size(); x++)
                            if(al_doilea_arbore[nr_arbori][muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].second][x] == muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].first)
                                {
                                    al_doilea_arbore[nr_arbori][muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].second].erase(al_doilea_arbore[nr_arbori][muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].second].begin() + x);
                                    al_doilea_arbore[nr_arbori][sortare[i][j].first].push_back(sortare[i][j].second);
                                    break;
                                }

                        x = cost_graf[muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].first][muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].second];
                        y = cost_graf[sortare[i][j].first][sortare[i][j].second];

                        if(second_cost > cost_arbore_minim - x + y)
                        {
                            second_cost = cost_arbore_minim - x + y;
                            second_arbore = nr_arbori;
                        }
                    }
                  //cout << " <-> " << muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].first << " " << muchii_maxime[maxim[sortare[i][j].first][sortare[i][j].second]][0].second << endl;
            }

    cout << "Primul arbore de cost " << cost_arbore_minim << endl;
    for(i = 1; i <= n; i++)
        for(j = 0; j < primul_arbore[i].size(); j++)
            if(!afisare_primul_arbore[i][primul_arbore[i][j]])
                {
                    cout << i << " " << primul_arbore[i][j] << endl;
                    afisare_primul_arbore[i][primul_arbore[i][j]] = 1;
                    afisare_primul_arbore[primul_arbore[i][j]][i] = 1;
                }
    cout << endl;

    cout << "Al doilea arbore de cost " << second_cost << endl;
    for(i = 1; i <= n; i++)
        for(j = 0; j < al_doilea_arbore[second_arbore][i].size(); j++)
            if(!afisare_al_doile_arbore[i][al_doilea_arbore[second_arbore][i][j]])
                {
                    cout << i << " " << al_doilea_arbore[second_arbore][i][j] << endl;
                    afisare_al_doile_arbore[i][al_doilea_arbore[second_arbore][i][j]] = 1;
                    afisare_al_doile_arbore[al_doilea_arbore[second_arbore][i][j]][i] = 1;
                }

    return 0;
}
