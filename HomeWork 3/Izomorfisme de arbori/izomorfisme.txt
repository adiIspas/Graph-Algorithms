#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <climits>

using namespace std;

struct Cod
    {
        char c[100];

    }codificare[100];

struct Cod2
    {
        char c[100];

    }codificare2[100];


vector<int> v[100], v2[100], nivele_cod[100][100], cod_nod[100], ordine[10], ordine_aux[10], v_aux;
queue<int> q, q_ar1, q_ar2, q_ar1_1, q_ar2_2, q_nod[100];

unsigned int vizitat[101], vizitat2[101], distanta[101], parinte[101], lant[101], culoare[100], culoare2[100], cod[100], cod2[100], nivele[100];
unsigned int n, m, i, j, x, y, nod, start, sfarsit, maxim, s = 0, nr_noduri, n_ar1, n_ar2;

void DFS(int nod)
    {
        unsigned i, info;

        culoare[nod] = 1;

        q.push(nod);

        for (i = 0; i < v[nod].size(); i++)
            {
                info = v[nod][i];

                if(!culoare[info])
                {
                    parinte[info] = nod;
                    culoare[info] = 1;
                    DFS(info);

                    q_nod[nod].push(info);

                    if(nivele[nod] < nivele[info] + 1)
                        nivele[nod] = nivele[info] + 1;
                }
            }
    }

void DFS2(int nod)
    {
        unsigned i, j, k, l, m, info, c_int, index = 0, aux, max_nivele;
        char x[2], x2[2];

        culoare2[nod] = 1;

        for (i = 0; i < v[nod].size(); i++)
            {
                info = v[nod][i];
                if(!culoare2[info])
                {
                    parinte[info] = nod;
                    culoare2[info] = 1;
                    DFS2(info);

                    if(nivele[info] == 0)
                       strcat(codificare[info].c,"1");

                    if(nivele[nod] > nivele[info])
                        nivele_cod[nod][nivele[info]].push_back(info);
                }
            }

     for(i = 0; i < nivele[nod]; i++)
        {
            max_nivele = 0;
            for(j = 0; j < nivele_cod[nod][i].size(); j++)
                {
                    v_aux.push_back(nivele_cod[nod][i][j]);
                    if(max_nivele < strlen(codificare[nivele_cod[nod][i][j]].c))
                        max_nivele = strlen(codificare[nivele_cod[nod][i][j]].c);
                }

            for(j = 0; j < nivele_cod[nod][i].size(); j++)
                ordine[int(codificare[nivele_cod[nod][i][j]].c[0] - 48)].push_back(nivele_cod[nod][i][j]);

            for(j = 0; j < 10; j++)
                {
                    for(k = 0; k < ordine[j].size(); k++)
                        ordine_aux[j].push_back(ordine[j][k]);
                    ordine[j].clear();
                }

            for(l = 1; l < max_nivele; l++)
                {for(j = 0; j < 10; j++)
                    {for(k = 0; k < ordine_aux[j].size(); k++)
                        if(int(codificare[ordine_aux[j][k]].c[l] - 48) >= 0 && int(codificare[ordine_aux[j][k]].c[l] - 48) <= 9)
                            ordine[int(codificare[ordine_aux[j][k]].c[l] - 48)].push_back(ordine_aux[j][k]);
                        else
                            ordine[0].push_back(ordine_aux[j][k]);
                    }

                 for(j = 0; j < 10; j++)
                    ordine_aux[j].clear();

                 for(j = 0; j < 10; j++)
                    for(k = 0; k < ordine[j].size(); k++)
                        ordine_aux[j].push_back(ordine[j][k]);

                 for(j = 0; j < 10; j++)
                    ordine[j].clear();
                }

            nivele_cod[nod][i].clear();
            for(j = 0; j < 10; j++)
                for(k = 0; k < ordine_aux[j].size(); k++)
                    nivele_cod[nod][i].push_back(ordine_aux[j][k]);

            for(j = 0; j < 10; j++)
                ordine_aux[j].clear();

            v_aux.clear();
        }

    for(i = 0; i < nivele[nod]; i++)
        if(nivele_cod[nod][i].size())
            for(j = 0; j < nivele_cod[nod][i].size(); j++)
                {
                    strcat(codificare[nod].c,codificare[nivele_cod[nod][i][j]].c);
                   // if(nivele[nivele_cod[nod][i][j]] == 0)
                        q_ar1.push(nivele_cod[nod][i][j]);
                }

    if(strlen(codificare[nod].c))
        {
            itoa(strlen(codificare[nod].c) + 1,x,10);
            strcat(codificare[nod].c,x);
        }
    }

void DFS3(int nod)
    {
        unsigned i, j, k, l, m, info, c_int, index = 0, aux, max_nivele;
        char x[2], x2[2];

        culoare2[nod] = 1;

        for (i = 0; i < v[nod].size(); i++)
            {
                info = v[nod][i];
                if(!culoare2[info])
                {
                    parinte[info] = nod;
                    culoare2[info] = 1;
                    DFS3(info);

                    if(nivele[info] == 0)
                       strcat(codificare2[info].c,"1");

                    if(nivele[nod] > nivele[info])
                        nivele_cod[nod][nivele[info]].push_back(info);
                }
            }

     for(i = 0; i < nivele[nod]; i++)
        {
            max_nivele = 0;
            for(j = 0; j < nivele_cod[nod][i].size(); j++)
                {
                    v_aux.push_back(nivele_cod[nod][i][j]);
                    if(max_nivele < strlen(codificare2[nivele_cod[nod][i][j]].c))
                        max_nivele = strlen(codificare2[nivele_cod[nod][i][j]].c);
                }

            for(j = 0; j < nivele_cod[nod][i].size(); j++)
                ordine[int(codificare2[nivele_cod[nod][i][j]].c[0] - 48)].push_back(nivele_cod[nod][i][j]);

            for(j = 0; j < 10; j++)
                {
                    for(k = 0; k < ordine[j].size(); k++)
                        ordine_aux[j].push_back(ordine[j][k]);
                    ordine[j].clear();
                }

            for(l = 1; l < max_nivele; l++)
                {for(j = 0; j < 10; j++)
                    {for(k = 0; k < ordine_aux[j].size(); k++)
                        if(int(codificare2[ordine_aux[j][k]].c[l] - 48) >= 0 && int(codificare2[ordine_aux[j][k]].c[l] - 48) <= 9)
                            ordine[int(codificare2[ordine_aux[j][k]].c[l] - 48)].push_back(ordine_aux[j][k]);
                        else
                            ordine[0].push_back(ordine_aux[j][k]);
                    }

                 for(j = 0; j < 10; j++)
                    ordine_aux[j].clear();

                 for(j = 0; j < 10; j++)
                    for(k = 0; k < ordine[j].size(); k++)
                        ordine_aux[j].push_back(ordine[j][k]);

                 for(j = 0; j < 10; j++)
                    ordine[j].clear();
                }

            nivele_cod[nod][i].clear();
            for(j = 0; j < 10; j++)
                for(k = 0; k < ordine_aux[j].size(); k++)
                    nivele_cod[nod][i].push_back(ordine_aux[j][k]);

            for(j = 0; j < 10; j++)
                ordine_aux[j].clear();

            v_aux.clear();
        }

    for(i = 0; i < nivele[nod]; i++)
        if(nivele_cod[nod][i].size())
            for(j = 0; j < nivele_cod[nod][i].size(); j++)
                strcat(codificare2[nod].c,codificare2[nivele_cod[nod][i][j]].c);


    if(strlen(codificare2[nod].c))
        {
            itoa(strlen(codificare2[nod].c) + 1,x,10);
            strcat(codificare2[nod].c,x);
        }
    }

int main()
{
    int sw = 0, k1, k2;

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

    if(n%2 == 0)
        {
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
            sw = 1;
        }
    else
        {
            DFS(lant[n/2 + 1]);
            DFS2(lant[n/2 + 1]);
            sw = 2;
        }

    cout << "Cod arbore 1: ";
    if(sw == 1)
        {
            cout << codificare[0].c;
            k1 = 0;
        }
    else
        {
            cout << codificare[lant[n/2 + 1]].c;
            k1 = lant[n/2 + 1];
        }
    cout << endl;

    /// Al doilea arbore

    for(i = 0; i < 100; i++)
        for(j = 0; j < 100; j++)
            nivele_cod[i][j].clear();

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

    sw = 0;
    if(n%2 == 0)
        {
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
            DFS3(0);
            sw = 1;
        }
    else
        {
            DFS(lant[n/2 + 1]);
            DFS3(lant[n/2 + 1]);
            sw = 2;
        }

    cout << "Cod arbore 2: ";
    if(sw == 1)
        {
            cout << codificare2[0].c;
            k2 = 0;
        }
    else
        {
            cout << codificare2[lant[n/2 + 1]].c;
            k2 = lant[n/2 + 1];
        }
    cout << endl;

    if(n_ar1 != n_ar2)
        {
            cout << "Cei doi arbori nu sunt izomorfi!";
            return 0;
        }

    if(strcmp(codificare[k1].c,codificare2[k2].c))
        {
            cout << "Cei doi arbori nu sunt izomorfi!";
            return 0;
        }

    cout << "Cei doi arbori sunt izomorfi!" << endl;

    int x;
    n = q_ar1.size();
    cout << endl;

    for(i = 0; i < n; i++)
        {

            if(strlen(codificare[q_ar1.front()].c) > 1)
                {
                    x = q_ar1.front();
                    cout << codificare[q_ar1.front()].c << " ";
                    break;
                }

            q_ar1.pop();
        }


    n = q_nod[x].size();

    cout << x << " ";

    for(i = 0; i < n / 2; i++)
    {
        cout << q_nod[x].front() << " ";
        q_nod[x].pop();
    }

    return 0;
}
