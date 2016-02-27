#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

vector<int> v[100], v2[100];
queue<int> q, q_ar1, q_ar2;

unsigned int vizitat[101], vizitat2[101], distanta[101], parinte[101], lant[101], culoare[100], culoare2[100], cod[100], cod2[100], nivele[100];
unsigned int n, m, i, j, x, y, nod, start, sfarsit, maxim, s = 0, nr_noduri, n_ar1, n_ar2;

void DFS(int nod)
    {
        unsigned i, info;

        culoare[nod] = 1;

        //cout << nod << " ";
        q.push(nod);

        for (i = 0; i < v[nod].size(); i++)
            {
                info = v[nod][i];

                if(!culoare[info])
                {
                    parinte[info] = nod;
                    culoare[info] = 1;
                    DFS(info);

                    if(nivele[nod] < nivele[info] + 1)
                        nivele[nod] = nivele[info] + 1;
                }
            }
    }

void DFS2(int nod)
    {
        unsigned i, info;

        culoare2[nod] = 1;

        for (i = 0; i < v[nod].size(); i++)
            {
                info = v[nod][i];

                if(!culoare2[info])
                {
                    parinte[info] = nod;
                    culoare2[info] = 1;
                    DFS2(info);

                    if(nivele[nod] > nivele[info])
                        cod[nod] += cod[info];
                }
            }
    }

int main()
{
    FILE *f = fopen("date.txt","r");

    fscanf(f,"%d",&n);
    m = n - 1;

    n_ar1 = nr_noduri = n;

    for(i = 0; i <= n; i++)
        cod[i] = 1;

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

    /*for(i = 1; i <= n; i++)
      if(maxim < distanta[i])
            maxim = distanta[i];

    cout << endl;
    cout << "Diametru: " << maxim + 1 << endl;*/

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

    //cout << "Centru: ";
    if(n%2 == 0)
        {
            //cout << lant[n/2] << " " << lant[n/2+1] << endl;
            v[0].push_back(lant[n/2]);
            v[0].push_back(lant[n/2+1]);

            for(i = 0; i < v[lant[n/2]].size(); i++)
                if(v[lant[n/2]][i] == lant[n/2+1])
                    break;

            v[lant[n/2]].erase(v[lant[n/2]].begin() + i);

            for(i = 0; i < v[lant[n/2+1]].size(); i++)
                if(v[lant[n/2+1]][i] == lant[n/2])
                    break;

            v[lant[n/2+1]].erase(v[lant[n/2+1]].begin() + i);
            DFS(0);
            DFS2(0);
        }
    else
        {
            //cout << lant[n/2 + 1] << endl;
            //cout << "Parcurgere DF: ";
            DFS(lant[n/2 + 1]);
            DFS2(lant[n/2 + 1]);
        }

    //cout << endl;
    //cout << "Cod arbore 1: ";
    n = q.size();
    for(i = 1; i <= n; i++)
    {
        x = q.front();
        q_ar1.push(x);
        q.pop();
        cod2[x] = cod[x];
        cod[x] = 1;
      //  cout << cod2[x] << " ";
    }

    //cout << endl;

    /// Al doilea arbore

    fscanf(f,"%d",&n);
    m = n - 1;

    n_ar2 = nr_noduri = n;

    for(i = 0; i <= n; i++)
        v[i].clear();

    for (i = 0; i < m; i++)
        {
            fscanf(f,"%d%d",&x,&y);
            v[x].push_back(y);
            v[y].push_back(x);
        }

    s = 0;
    for(i = 1; i <= n; i++)
        s += v[i].size();

    if(s != 2*(n - 1))
        {
            cout << "Nu e arbore!\n";
            return 0;
        }

    for(i = 0; i <= n; i++)
        {
            vizitat2[i] = 0;
            vizitat[i] = 0;
            nivele[i] = 0;
            culoare2[i] = 0;
            culoare[i] = 0;
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

    /*for(i = 1; i <= n; i++)
      if(maxim < distanta[i])
            maxim = distanta[i];

    cout << endl;
    cout << "Diametru: " << maxim + 1 << endl;*/

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

    //cout << "Centru: ";
    if(n%2 == 0)
        {
            //cout << lant[n/2] << " " << lant[n/2+1] << endl;
            v[0].push_back(lant[n/2]);
            v[0].push_back(lant[n/2+1]);

            for(i = 0; i < v[lant[n/2]].size(); i++)
                if(v[lant[n/2]][i] == lant[n/2+1])
                    break;

            v[lant[n/2]].erase(v[lant[n/2]].begin() + i);

            for(i = 0; i < v[lant[n/2+1]].size(); i++)
                if(v[lant[n/2+1]][i] == lant[n/2])
                    break;

            v[lant[n/2+1]].erase(v[lant[n/2+1]].begin() + i);
            DFS(0);
            DFS2(0);
        }
    else
        {
            //cout << lant[n/2 + 1] << endl;
            //cout << "Parcurgere DF: ";
            DFS(lant[n/2 + 1]);
            DFS2(lant[n/2 + 1]);
        }

    //cout << endl;
    //cout << "Cod arbore 2: ";
    n = q.size();
    for(i = 1; i <= n; i++)
    {
        x = q.front();
        q_ar2.push(x);
        q.pop();
        //cout << cod[x] << " ";
    }

    //cout << endl;

    if(n_ar1 != n_ar2)
        {
            cout << "Cei 2 arbori nu sunt izomorfi!\n";
            return 0;
        }

    cout << "Cei doi arbori sunt izomorfi!\n";
    q_ar1.pop();
    q_ar2.pop();

    n = cod[q_ar1.front()];

    for(i = 0; i < n; i++)
        {
            cout << q_ar1.front() << " " << q_ar2.front() << endl;
            q_ar1.pop();
            q_ar2.pop();
        }

    cout << endl;
    return 0;
}
