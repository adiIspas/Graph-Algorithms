///Arborele partial de cost minim KRUSKAL

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int p[201], h[201];

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
    FILE *f = fopen("online.in","r");
    FILE *g = fopen("online.out","w");

    vector<pair<int,int> > muchii[10001];
    vector<pair<int,int> > sortare[251];
    pair<int,int> pereche;

    int i, j, l, n, m, x, y, z, k, sw, max_pondere = 0, s_pondere = 0;

    fscanf(f,"%d%d",&n,&m);

    for(i = 1; i <= m; i++)
        {
            fscanf(f,"%d%d%d",&x,&y,&z);

            pereche = make_pair(y,z);
            muchii[x].push_back(pereche);

            pereche = make_pair(x,z);
            muchii[y].push_back(pereche);

            pereche = make_pair(x,y);
            sortare[z].push_back(pereche);

            if(max_pondere < z)
                max_pondere = z;
        }

    m = 0;

    for(i = 0; i <= max_pondere; i++)
        for(j = 0; j < sortare[i].size(); j++)
            if(FindSet(sortare[i][j].first) != FindSet(sortare[i][j].second))
                {
                    Union(sortare[i][j].first,sortare[i][j].second);
                    m++;
                    s_pondere += i;

                    if(m == n - 1)
                        break;
                }

    fprintf(g,"%d\n",s_pondere);
    fscanf(f,"%d",&k);

    for(i = 0; i < k; i++)
        {
            fscanf(f,"%d%d%d",&x,&y,&z);

            for(j = 1; j <= 200; j++)
                p[j] = h[j] = 0;

            m = 0;
            s_pondere = 0;
            sw = 0;

            for(j = 0; j < muchii[x].size(); j++)
                if(muchii[x][j].first == y)
                    {
                        sw = 1;
                        break;
                    }

            if(sw == 0)
                {
                    pereche = make_pair(y,z);
                    muchii[x].push_back(pereche);

                    pereche = make_pair(x,z);
                    muchii[y].push_back(pereche);

                    pereche = make_pair(x,y);
                    sortare[z].push_back(pereche);

                    if(max_pondere < z)
                        max_pondere = z;

                    for(l = 0; l <= max_pondere; l++)
                        for(j = 0; j < sortare[l].size(); j++)
                            if(FindSet(sortare[l][j].first) != FindSet(sortare[l][j].second))
                                {
                                    Union(sortare[l][j].first,sortare[l][j].second);
                                    m++;
                                    s_pondere += l;

                                    if(m == n - 1)
                                        break;
                                }

                    fprintf(g,"%d\n",s_pondere);
            }

            if(sw == 1)
                {
                    for(j = 0; j < muchii[x].size(); j++)
                        if(muchii[x][j].first == y)
                            {
                                muchii[x].erase(muchii[y].begin() + j);

                                pereche = make_pair(y,z);
                                muchii[x].push_back(pereche);
                            }

                    for(j = 0; j < muchii[y].size(); j++)
                        if(muchii[y][j].first == x)
                            {
                                muchii[y].erase(muchii[y].begin() + j);

                                pereche = make_pair(x,z);
                                muchii[y].push_back(pereche);
                            }

                    for(l = 0; l <= max_pondere; l++)
                        for(j = 0; j < sortare[l].size(); j++)
                            if((sortare[l][j].first == x && sortare[l][j].second == y) || (sortare[l][j].first == y && sortare[l][j].second == x))
                                {
                                    sortare[l].erase(sortare[l].begin() + j);
                                    pereche = make_pair(x,y);
                                    sortare[z].push_back(pereche);
                                    break;
                                }

                    if(max_pondere < z)
                        max_pondere = z;

                    for(l = 0; l <= max_pondere; l++)
                        for(j = 0; j < sortare[l].size(); j++)
                            if(FindSet(sortare[l][j].first) != FindSet(sortare[l][j].second))
                                {
                                    Union(sortare[l][j].first,sortare[l][j].second);
                                    m++;
                                    s_pondere += l;

                                    if(m == n - 1)
                                        break;
                                }

                    fprintf(g,"%d\n",s_pondere);
                }
        }

    return 0;
}
