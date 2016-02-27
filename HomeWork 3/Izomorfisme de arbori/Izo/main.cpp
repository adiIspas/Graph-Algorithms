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


vector<int> v[100], v2[100], nivele_cod[100][100], cod_nod[100], ordine[10], ordine_aux[10], v_aux;
queue<int> q, q_ar1, q_ar2, q_ar1_1, q_ar2_2;

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

                    /// daca e frunza va avea codul 1
                    if(nivele[info] == 0)
                       strcat(codificare[info].c,"1");

                    /// introducem in vectorul de nivele fii nodului curent
                    if(nivele[nod] > nivele[info])
                        nivele_cod[nod][nivele[info]].push_back(info);
                }
            }

    /// codificam intr-un vector in baza 10 fiecare cod de pe nivele

    /*for(i = 0; i < v[nod].size(); i++)
        for(j = 0; j < strlen(codificare[v[nod][i]].c); j++)
            cod_nod[v[nod][i]].push_back(int(codificare[v[nod][i]].c[j] - 48));*/

    /*for(i = 0; i < nivele[nod]; i++)
        {
            for(j = 0; j < nivele_cod[nod][i].size(); j++)
                v_aux.push_back(nivele_cod[nod][i][j]);

            for(j = 0; j < nivele_cod[nod][i].size(); j++)
                for(k = j + 1; k < nivele_cod[nod][i].size(); k++)
                    {
                        if(strcmp(codificare[nivele_cod[nod][i][j]].c,codificare[nivele_cod[nod][i][k]].c) < 0)
                        {
                            aux = v_aux[j];
                            v_aux[j] = v_aux[k];
                            v_aux[k] = aux;
                        }
                    }
            nivele_cod[nod][i].clear();
            for(j = 0; j < v_aux.size(); j++)
                nivele_cod[nod][i].push_back(v_aux[j]);

            v_aux.clear();
        }*/

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
                strcat(codificare[nod].c,codificare[nivele_cod[nod][i][j]].c);


    if(strlen(codificare[nod].c))
        {
            itoa(strlen(codificare[nod].c) + 1,x,10);
            strcat(codificare[nod].c,x);
        }

    {
        /*for(i = 0; i < nivele[nod]; i++)
        {
            cout << nod << " " << i << ": ";
            for(j = 0; j < nivele_cod[nod][i].size(); j++)
                cout << nivele_cod[nod][i][j] << " " << codificare[nivele_cod[nod][i][j]].c << " ";
            cout << endl;
        }*/

    /*for(i = 0; i < v[nod].size(); i++)
        {
            cout << v[nod][i] << ": ";
            for(j = 0; j < cod_nod[v[nod][i]].size(); j++)
                cout << cod_nod[v[nod][i]][j] << " ";
            cout << endl;
        }*/

    /*for(i = 0; i < nivele[nod]; i++)
        for(j = 0; j < nivele_cod[nod][i].size(); j++)
            {//cout << nod << " " << i << " " << j << ": ";
            if(index < strlen(codificare[nivele_cod[nod][i][j]].c))
                    index = strlen(codificare[nivele_cod[nod][i][j]].c);

             for(k = 0; k < strlen(codificare[nivele_cod[nod][i][j]].c); k++)
                {
                    x2[0] = codificare[nivele_cod[nod][i][j]].c[k];
                    x2[1] = '\n';
                    c_int = atoi(x2);
                    //cout << c_int << " ";
                    cod_nod[nivele_cod[nod][i][j]].push_back(c_int);
                }
                //cout << endl;
            }

    //cout << endl;

    /// sortam cu radix-sort
    //for(m = 0; m < 4; m++)
    for(i = 0; i < nivele[nod]; i++)
        {
            for(j = 0; j < nivele_cod[nod][i].size(); j++)
            {
                //cout << nod << " " << i << " " << nivele_cod[nod][i][j] << ": ";
                //for(k = 0; k < cod_nod[nivele_cod[nod][i][j]].size(); k++)
                    ordine[cod_nod[nivele_cod[nod][i][j]][0]].push_back(nivele_cod[nod][i][j]);
                    //cout << cod_nod[nivele_cod[nod][i][j]][k] << " ";
                //cout << endl;
            }

            /*cout << nod << " " << i << "\n";
            for(j = 0; j < 10; j++)
            {
                cout << j << ": ";
                for(k = 0; k < ordine[j].size(); k++)
                    cout << ordine[j][k] << " ";
                cout << endl;

                ordine[j].clear();
            }


        //cout << endl;
        }

    //cout << nod << " " << index << endl;
    for(i = 1; i < index; i++)
        {
            for(j = 0; j < 10; j++)
                {
                  //cout << j << ": ";
                  for(k = 0; k < ordine[j].size(); k++)
                    {

                         info = ordine[j][k];
                         if(cod_nod[info].size() == index)
                            ordine_aux[cod_nod[info][index - 1]].push_back(info);
                            //cout << info << " " << cod_nod[info][index - 1] << endl;
                      //   ordine_aux[cod_nod[l][ordine[j][k]][k]].push_back(nivele_cod[nod][ordine[j][k]][l]);
                    }
                //cout << endl;
                }

            for(j = 0; j < 10; j++)
                ordine[j].clear();
            //cout << endl;

            for(j = 0; j < 10; j++)
               {
                   for(k = 0; k < ordine_aux[j].size(); k++)
                    {
                        aux = ordine_aux[j][k];
                        cout << aux << " ";
                        ordine[j].push_back(aux);
                    }
               // cout << endl;
               }

            for(j = 0; j < 10; j++)
                if(ordine[j].size())
                    {
                        ///cout << j << ": ";
                        for(k = 0; k < ordine[j].size(); k++);
                          //  cout << ordine[j][k] << " ";
                        //cout << endl;
                    }

             for(j = 0; j < 10; j++)
                ordine_aux[j].clear();

        }


           /* for(j = 0; j < 10; j++)
                ordine[j].clear();

            for(j = 0; j < 10; j++)
               {
                   for(k = 0; k < ordine_aux[j].size(); k++)
                    {
                        aux = ordine_aux[j][k];
                       // cout << aux << " ";
                       // ordine[j].push_back(aux);
                    }
                cout << endl;
               }

    for(j = 0; j < 10; j++)
        ordine_aux[j].clear();
        }

    //for(i = 0; i < 10; i++)
       // ordine[i].clear();


    for(i = 0; i < nivele[nod]; i++)
        for(j = 0; j < nivele_cod[nod][i].size(); j++)
            cod_nod[j].clear();
*/
   // for(i = 0; i < v[nod].size(); i++)
       /* {
            //cout << nod << " " << nivele[nod] << endl;
            /// concatenam in ordinea crescatoare a nivelelor;

            for(i = 0; i <= nivele[nod]; i++)
                if(nivele_cod[nod][i].size())
                    for(j = 0; j < nivele_cod[nod][i].size(); j++)
                        strcat(codificare[nod].c,codificare[nivele_cod[nod][i][j]].c);
        }

    if(strlen(codificare[nod].c))
        {
            /// adaugam si ultima cifra din codificarea nodului
            itoa(strlen(codificare[nod].c) + 1,x,10);
            strcat(codificare[nod].c,x);
        }

    /*for(i = 0; i < nivele[nod]; i++)
        if(nivele_cod[nod][i].size() && nivele[nod])
            {
                cout << nod << " " << i << ": ";

                for(j = 0; j < nivele_cod[nod][i].size(); j++)
                    cout << nivele_cod[nod][i][j] << " ";
                cout << endl;
            }

     for(i = 0; i < 10; i++)
        nivele_cod[nod][i].clear(); */}
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

   /*if(s != 2*(n - 1))
        {
            cout << "Nu e arbore!\n";
            return 0;
        }
    */

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
        }
    else
        {
            DFS(lant[n/2 + 1]);
            DFS2(lant[n/2 + 1]);
        }

    cout << endl;
    for(i = 0; i < nr_noduri; i++)
        cout << i << ": " << codificare[i].c << endl;

    return 0;
}
