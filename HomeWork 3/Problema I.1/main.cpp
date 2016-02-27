#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

vector<int> v[100000];
queue<int> q;

int vizitat[100001], vizitat2[100001], distanta[100001], parinte[100001], lant[100001];
int n, m, i, j, x, y, nod, start, sfarsit, maxim, s = 0;

int main()
{
    FILE *f = fopen("date.txt","r");

    fscanf(f,"%d",&n);
    m = n - 1;

    for (i = 0; i < m; i++)
        {
            fscanf(f,"%d%d",&x,&y);
            v[x].push_back(y);
            v[y].push_back(x);
        }

    for(i = 1; i <= n; i++)
        s += v[i].size();

    if(s != 2*(n - 1))
        {
            cout << "Nu e arbore!\n";
            return 0;
        }

    start = 1;
    vizitat[start] = 1;
    q.push(start);

    while (!q.empty())
        {
         nod = q.front();
         q.pop();

         for(i = 0; i < v[nod].size(); i++)
            if(!vizitat[v[nod][i]])
                {
                    vizitat[v[nod][i]] = 1;
                    q.push(v[nod][i]);
                }
        }

    start = nod;
    vizitat2[start] = 1;
    q.push(start);

    while (!q.empty())
        {
         nod = q.front();
         q.pop();

         for(i = 0; i < v[nod].size(); i++)
            if(!vizitat2[v[nod][i]])
                {
                    vizitat2[v[nod][i]] = 1;
                    parinte[v[nod][i]] = nod;
                    distanta[v[nod][i]] = distanta[nod] + 1;
                    q.push(v[nod][i]);
                }
        }

    for(i = 1; i <= n; i++)
      if(maxim < distanta[i])
            maxim = distanta[i];

    cout << endl;
    cout << "Diametru: " << maxim + 1 << endl;

    i = nod;
    lant[1] = nod;
    n = 2;


    while(parinte[i] != start)
    {
        lant[n] = parinte[i];
        i = parinte[i];
        n++;
    }

    lant[n] = start;

    cout << "Centru: ";
    if(n%2 == 0)
        cout << lant[n/2] << " " << lant[n/2+1];
    else
        cout << lant[n/2 + 1];

    cout << endl;
    return 0;
}
