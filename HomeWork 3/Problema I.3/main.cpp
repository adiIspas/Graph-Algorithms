#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <cstring>
#include <stdlib.h>

using namespace std;

struct Cod
    {
        char c[100];

    }codificare1[100];

struct Cod2
    {
        char c[100];

    }codificare2[100];


vector<int> v1[100], v2[100], nivele_cod1[100][100], nivele_cod2[100][100], ordine1[10], ordine_aux1[10], ordine2[10], ordine_aux2[10];
queue<int> q1, q2, q_ar1, q_ar2, q_nod1[100], q_nod2[100];

unsigned int vizitat1[101], vizitat2[101], vizitat3[101], vizitat4[101], parinte1[101], parinte2[100], lant1[101], lant2[101], culoare1[100], culoare2[100], culoare3[100], culoare4[100], nivele1[100], nivele2[100];
unsigned int n, m, i, j, x, y, nod, start, n_ar1, n_ar2;

void DFS1(int nod)
    {
        unsigned i, info;

        culoare1[nod] = 1;

        for (i = 0; i < v1[nod].size(); i++)
            {
                info = v1[nod][i];

                if(!culoare1[info])
                {
                    culoare1[info] = 1;
                    DFS1(info);

                    if(nivele1[nod] < nivele1[info] + 1)
                        nivele1[nod] = nivele1[info] + 1;
                }
            }
    }

void DFS2(int nod)
    {
        unsigned i, info;

        culoare2[nod] = 1;

        for (i = 0; i < v2[nod].size(); i++)
            {
                info = v2[nod][i];

                if(!culoare2[info])
                {
                    culoare2[info] = 1;
                    DFS2(info);

                    if(nivele2[nod] < nivele2[info] + 1)
                        nivele2[nod] = nivele2[info] + 1;
                }
            }
    }

void DFS3(int nod)
    {
        unsigned i, j, k, l, info, max_nivele;
        char x[2];

        culoare3[nod] = 1;

        for (i = 0; i < v1[nod].size(); i++)
            {
                info = v1[nod][i];
                if(!culoare3[info])
                {
                    culoare3[info] = 1;
                    DFS3(info);

                    q_nod1[nod].push(info);

                    if(nivele1[info] == 0)
                       strcat(codificare1[info].c,"1");

                    if(nivele1[nod] > nivele1[info])
                        nivele_cod1[nod][nivele1[info]].push_back(info);
                }
            }

     for(i = 0; i < nivele1[nod]; i++)
        {
            max_nivele = 0;
            for(j = 0; j < nivele_cod1[nod][i].size(); j++)
                {
                    if(max_nivele < strlen(codificare1[nivele_cod1[nod][i][j]].c))
                        max_nivele = strlen(codificare1[nivele_cod1[nod][i][j]].c);
                }

            for(j = 0; j < nivele_cod1[nod][i].size(); j++)
                ordine1[int(codificare1[nivele_cod1[nod][i][j]].c[0] - 48)].push_back(nivele_cod1[nod][i][j]);

            for(j = 0; j < 10; j++)
                {
                    for(k = 0; k < ordine1[j].size(); k++)
                        ordine_aux1[j].push_back(ordine1[j][k]);
                    ordine1[j].clear();
                }

            for(l = 1; l < max_nivele; l++)
                {for(j = 0; j < 10; j++)
                    {for(k = 0; k < ordine_aux1[j].size(); k++)
                        if(int(codificare1[ordine_aux1[j][k]].c[l] - 48) >= 0 && int(codificare1[ordine_aux1[j][k]].c[l] - 48) <= 9)
                            ordine1[int(codificare1[ordine_aux1[j][k]].c[l] - 48)].push_back(ordine_aux1[j][k]);
                        else
                            ordine1[0].push_back(ordine_aux1[j][k]);
                    }

                 for(j = 0; j < 10; j++)
                    ordine_aux1[j].clear();

                 for(j = 0; j < 10; j++)
                    for(k = 0; k < ordine1[j].size(); k++)
                        ordine_aux1[j].push_back(ordine1[j][k]);

                 for(j = 0; j < 10; j++)
                    ordine1[j].clear();
                }

            nivele_cod1[nod][i].clear();
            for(j = 0; j < 10; j++)
                for(k = 0; k < ordine_aux1[j].size(); k++)
                    nivele_cod1[nod][i].push_back(ordine_aux1[j][k]);

            for(j = 0; j < 10; j++)
                ordine_aux1[j].clear();
        }

    for(i = 0; i < nivele1[nod]; i++)
        if(nivele_cod1[nod][i].size())
            for(j = 0; j < nivele_cod1[nod][i].size(); j++)
                {
                    strcat(codificare1[nod].c,codificare1[nivele_cod1[nod][i][j]].c);
                    q_ar1.push(nivele_cod1[nod][i][j]);
                }

    if(strlen(codificare1[nod].c))
        {
            itoa(strlen(codificare1[nod].c) + 1,x,10);
            strcat(codificare1[nod].c,x);
        }
    }

void DFS4(int nod)
    {
        unsigned i, j, k, l, info, max_nivele;
        char x[2];

        culoare4[nod] = 1;

        for (i = 0; i < v2[nod].size(); i++)
            {
                info = v2[nod][i];
                if(!culoare4[info])
                {
                    culoare4[info] = 1;
                    DFS4(info);

                    q_nod2[nod].push(info);

                    if(nivele2[info] == 0)
                       strcat(codificare2[info].c,"1");

                    if(nivele2[nod] > nivele2[info])
                        nivele_cod2[nod][nivele2[info]].push_back(info);
                }
            }

     for(i = 0; i < nivele2[nod]; i++)
        {
            max_nivele = 0;
            for(j = 0; j < nivele_cod2[nod][i].size(); j++)
                {
                    if(max_nivele < strlen(codificare2[nivele_cod2[nod][i][j]].c))
                        max_nivele = strlen(codificare2[nivele_cod2[nod][i][j]].c);
                }

            for(j = 0; j < nivele_cod2[nod][i].size(); j++)
                ordine2[int(codificare2[nivele_cod2[nod][i][j]].c[0] - 48)].push_back(nivele_cod2[nod][i][j]);

            for(j = 0; j < 10; j++)
                {
                    for(k = 0; k < ordine2[j].size(); k++)
                        ordine_aux2[j].push_back(ordine2[j][k]);
                    ordine2[j].clear();
                }

            for(l = 1; l < max_nivele; l++)
                {for(j = 0; j < 10; j++)
                    {for(k = 0; k < ordine_aux2[j].size(); k++)
                        if(int(codificare2[ordine_aux2[j][k]].c[l] - 48) >= 0 && int(codificare2[ordine_aux2[j][k]].c[l] - 48) <= 9)
                            ordine2[int(codificare2[ordine_aux2[j][k]].c[l] - 48)].push_back(ordine_aux2[j][k]);
                        else
                            ordine2[0].push_back(ordine_aux2[j][k]);
                    }

                 for(j = 0; j < 10; j++)
                    ordine_aux2[j].clear();

                 for(j = 0; j < 10; j++)
                    for(k = 0; k < ordine2[j].size(); k++)
                        ordine_aux2[j].push_back(ordine2[j][k]);

                 for(j = 0; j < 10; j++)
                    ordine2[j].clear();
                }

            nivele_cod2[nod][i].clear();
            for(j = 0; j < 10; j++)
                for(k = 0; k < ordine_aux2[j].size(); k++)
                    nivele_cod2[nod][i].push_back(ordine_aux2[j][k]);

            for(j = 0; j < 10; j++)
                ordine_aux2[j].clear();
        }

    for(i = 0; i < nivele2[nod]; i++)
        if(nivele_cod2[nod][i].size())
            for(j = 0; j < nivele_cod2[nod][i].size(); j++)
                {
                    strcat(codificare2[nod].c,codificare2[nivele_cod2[nod][i][j]].c);
                    q_ar2.push(nivele_cod2[nod][i][j]);
                }


    if(strlen(codificare2[nod].c))
        {
            itoa(strlen(codificare2[nod].c) + 1,x,10);
            strcat(codificare2[nod].c,x);
        }
    }

int main()
{
    int sw = 0, s = 0, k1, k2, x1, x2, n1, n2;

    FILE *f = fopen("date.txt","r");

    fscanf(f,"%d",&n);
    m = n - 1;

    n_ar1 = n;

    for (i = 0; i < m; i++)
        {
            fscanf(f,"%d%d",&x,&y);
            v1[x].push_back(y);
            v1[y].push_back(x);
        }

    for(i = 1; i <= n; i++)
        s += v1[i].size();

   if(s != 2*(n - 1))
        {
            cout << "Nu e arbore!\n";
            return 0;
        }

    start = 1;
    vizitat1[start] = 1;
    q1.push(start);

    while (!q1.empty())
        {
         nod = q1.front();
         q1.pop();

         for(i = 0; i < v1[nod].size(); i++)
            if(!vizitat1[v1[nod][i]])
                {
                    vizitat1[v1[nod][i]] = 1;
                    q1.push(v1[nod][i]);
                }
        }

    start = nod;
    vizitat2[start] = 1;
    q1.push(start);

    while (!q1.empty())
        {
         nod = q1.front();
         q1.pop();

         for(i = 0; i < v1[nod].size(); i++)
            if(!vizitat2[v1[nod][i]])
                {
                    vizitat2[v1[nod][i]] = 1;
                    parinte1[v1[nod][i]] = nod;
                    q1.push(v1[nod][i]);
                }
        }

    i = nod;
    lant1[1] = nod;
    n = 2;

    while(parinte1[i] != start)
    {
        lant1[n] = parinte1[i];
        i = parinte1[i];
        n++;
    }

    lant1[n] = start;

    if(n%2 == 0)
        {
            v1[0].push_back(lant1[n/2]);
            v1[0].push_back(lant1[n/2+1]);

            for(i = 0; i < v1[lant1[n/2]].size(); i++)
                if(v1[lant1[n/2]][i] == lant1[n/2+1])
                    break;

            v1[lant1[n/2]].erase(v1[lant1[n/2]].begin() + i);

            for(i = 0; i < v1[lant1[n/2+1]].size(); i++)
                if(v1[lant1[n/2+1]][i] == lant1[n/2])
                    break;

            v1[lant1[n/2+1]].erase(v1[lant1[n/2+1]].begin() + i);

            DFS1(0);
            DFS3(0);

            sw = 1;
        }
    else
        {
            DFS1(lant1[n/2 + 1]);
            DFS3(lant1[n/2 + 1]);
            sw = 2;
        }

    cout << "Cod arbore 1: ";
    if(sw == 1)
        {
            for(i = strlen(codificare1[0].c) - 1; i > 0; i--)
                cout << codificare1[0].c[i];
            cout << codificare1[0].c[0];
            k1 = 0;
        }
    else
        {
            for(i = strlen(codificare1[lant1[n/2 + 1]].c) - 1; i > 0; i--)
                cout << codificare1[lant1[n/2 + 1]].c[i];
            cout << codificare1[lant1[n/2 + 1]].c[0];
            k1 = lant1[n/2 + 1];
        }
    cout << endl;

    /// Al doilea arbore

    fscanf(f,"%d",&n);
    m = n - 1;

    n_ar2 = n;

    for (i = 0; i < m; i++)
        {
            fscanf(f,"%d%d",&x,&y);
            v2[x].push_back(y);
            v2[y].push_back(x);
        }

    s = 0;
    for(i = 1; i <= n; i++)
        s += v2[i].size();

    if(s != 2*(n - 1))
        {
            cout << "Nu e arbore!\n";
            return 0;
        }

    start = 1;
    vizitat3[start] = 1;
    q2.push(start);

    while (!q2.empty())
        {
         nod = q2.front();
         q2.pop();

         for(i = 0; i < v2[nod].size(); i++)
            if(!vizitat3[v2[nod][i]])
                {
                    vizitat3[v2[nod][i]] = 1;
                    q2.push(v2[nod][i]);
                }
        }

    start = nod;
    vizitat4[start] = 1;
    q2.push(start);

    while (!q2.empty())
        {
         nod = q2.front();
         q2.pop();

         for(i = 0; i < v2[nod].size(); i++)
            if(!vizitat4[v2[nod][i]])
                {
                    vizitat4[v2[nod][i]] = 1;
                    parinte2[v2[nod][i]] = nod;
                    q2.push(v2[nod][i]);
                }
        }

    i = nod;
    lant2[1] = nod;
    n = 2;

    while(parinte2[i] != start)
    {
        lant2[n] = parinte2[i];
        i = parinte2[i];
        n++;
    }

    lant2[n] = start;

    sw = 0;
    if(n%2 == 0)
        {
            v2[0].push_back(lant2[n/2]);
            v2[0].push_back(lant2[n/2+1]);

            for(i = 0; i < v2[lant2[n/2]].size(); i++)
                if(v2[lant2[n/2]][i] == lant2[n/2+1])
                    break;

            v2[lant2[n/2]].erase(v2[lant2[n/2]].begin() + i);

            for(i = 0; i < v2[lant2[n/2+1]].size(); i++)
                if(v2[lant2[n/2+1]][i] == lant2[n/2])
                    break;

            v2[lant2[n/2+1]].erase(v2[lant2[n/2+1]].begin() + i);
            DFS2(0);
            DFS4(0);

            sw = 1;
        }
    else
        {
            DFS2(lant2[n/2 + 1]);
            DFS4(lant2[n/2 + 1]);
            sw = 2;
        }

    cout << "Cod arbore 2: ";
    if(sw == 1)
        {
            for(i = strlen(codificare2[0].c) - 1; i > 0; i--)
                cout << codificare2[0].c[i];
            cout << codificare2[0].c[0];
            k2 = 0;
        }
    else
        {
            for(i = strlen(codificare2[lant2[n/2 + 1]].c) - 1; i > 0; i--)
                cout << codificare2[lant2[n/2 + 1]].c[i];
            cout << codificare2[lant2[n/2 + 1]].c[0];
            k2 = lant2[n/2 + 1];
        }
    cout << endl;

    if(n_ar1 != n_ar2)
        {
            cout << "\nCei doi arbori nu sunt izomorfi!\n";
            return 0;
        }

    if(strcmp(codificare1[k1].c,codificare2[k2].c))
        {
            cout << "\nCei doi arbori nu sunt izomorfi!\n";
            return 0;
        }

    cout << "\nCei doi arbori sunt izomorfi!\n" << endl;

    n1 = q_ar1.size();

    for(i = 0; i < n1; i++)
        {

            if(strlen(codificare1[q_ar1.front()].c) > 1)
                {
                    x1 = q_ar1.front();
                    break;
                }

            q_ar1.pop();
        }

    n2 = q_ar2.size();

    for(i = 0; i < n2; i++)
        {

            if(strlen(codificare2[q_ar2.front()].c) > 1)
                {
                    x2 = q_ar2.front();
                    break;
                }

            q_ar2.pop();
        }

    n1 = q_nod1[x1].size();

    cout << x1 << " - > " << x2 << endl;

    for(i = 0; i < n1; i++)
    {
        cout << q_nod1[x1].front() << " - > " << q_nod2[x2].front() << endl;

        q_nod2[x2].pop();
        q_nod1[x1].pop();
    }

    return 0;
}
