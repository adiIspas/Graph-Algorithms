///Arborele partial de cost minim KRUSKAL

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

int p[200000], h[200000];

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

    vector<int> muchii[100000];
    vector<pair<int,int> > sortare[2001];

    pair<int,int> pereche;

    int i, j, n, m, x, y, z, max_pondere = 0, nr_muchii = 0, s_pondere = 0;

    fscanf(f,"%d%d",&n,&m);

    for(i = 0; i < m; i++)
        {
            fscanf(f,"%d%d%d",&x,&y,&z);

            if(max_pondere < z + 1000)
                max_pondere = z + 1000;

            pereche = make_pair(x,y);

            sortare[z + 1000].push_back(pereche);
        }

    m = 0;
    for(i = 0; i <= max_pondere; i++)
        for(j = 0; j < sortare[i].size(); j++)
            if(FindSet(sortare[i][j].first) != FindSet(sortare[i][j].second))
                {
                    muchii[sortare[i][j].first].push_back(sortare[i][j].second);
                    Union(sortare[i][j].first,sortare[i][j].second);

                    m++;
                    nr_muchii++;
                    s_pondere += i;

                    if(m == n - 1)
                        break;
                }

    fprintf(g,"%d\n%d\n",s_pondere - nr_muchii * 1000, nr_muchii);
    for(i = 1; i <= nr_muchii + 1; i++)
        for(j = 0; j < muchii[i].size(); j++)
            fprintf(g,"%d %d\n",i, muchii[i][j]);

    return 0;
}
