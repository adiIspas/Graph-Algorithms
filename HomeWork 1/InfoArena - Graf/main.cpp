#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

int vizitat1[14001], vizitat2[14001], viz[14001], noduri[14001];

int main()
{
    ifstream f("graf.in");
    ofstream g("graf.out");

    vector<int> v[14001];
    int d1[14001], d2[14001];
    queue<int> q;

    unsigned int n, m, i, x, y, nod, sursa1, sursa2, k = 0;

    f >> n;
    f >> m;
    f >> sursa1;
    f >> sursa2;

    for(i = 1; i <= n; i++)
        {
         d1[i] = 99999;
         d2[i] = 99999;
        }

    for (i = 0; i < m; i++)
        {
            f >> x >> y;
            v[x].push_back(y);
            v[y].push_back(x);
        }

    vizitat1[sursa1] = 1;
    d1[sursa1] = 0;
    q.push(sursa1);

    while (!q.empty())
        {
         nod = q.front();
         q.pop();

         for(i = 0; i < v[nod].size(); i++)
            {
             if(vizitat1[v[nod][i]] == 0)
                {
                    viz[v[nod][i]] = viz[nod];
                    vizitat1[v[nod][i]] = 1;
                    d1[v[nod][i]] = d1[nod] + 1;
                    q.push(v[nod][i]);
                }
            else
                if(d1[v[nod][i]] == d1[nod] + 1)
                    viz[v[nod][i]]++;
            }
        }

    vizitat2[sursa2] = 1;
    d2[sursa2] = 0;
    q.push(sursa2);

    while (!q.empty())
        {
         nod = q.front();
         q.pop();

         for(i = 0; i < v[nod].size(); i++)
            {
             if(vizitat2[v[nod][i]] == 0)
                {
                    vizitat2[v[nod][i]] = 1;
                    d2[v[nod][i]] = d2[nod] + 1;
                    q.push(v[nod][i]);
                }
            }
        }

    for(i = 1; i <= n; i++)
        if((d1[i] + d2[i]) == d1[sursa2])
            if(viz[i] == viz[sursa2])
                {
                    k++;
                    noduri[i] = 1;
                }

    if(noduri[sursa1] == 0)
        k++;

    noduri[sursa1] = 1;

    g << k << endl;

    for(i = 1; i <= n; i++)
        if(noduri[i])
            g << i << " ";
    return 0;
}
