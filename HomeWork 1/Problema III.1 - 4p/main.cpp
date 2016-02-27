#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

vector<int> v[100];

int culoare[100], parinte[100], nivel[100], minim[100];
char punct[100];

queue<int> q;

int sursa, fii;

void DFS(int nod)
    {
        int i, j, info;

        culoare[nod] = 1;
        minim[nod] = nivel[nod];

        for (i = 0; i < v[nod].size(); i++)
            {
                info = v[nod][i];

                if(!culoare[info])
                {
                    nivel[info] = nivel[nod] + 1;
                    parinte[info] = nod;

                    if(nod == sursa)
                        fii++;

                    DFS(info);

                    if(minim[nod] > minim[info])
                        minim[nod] = minim[info];

                    if(minim[info] >= nivel[nod])
                        punct[nod] = 1;

                    if(minim[info] > nivel[nod])
                        cout << nod << " " << info << endl;
                }
                else
                    if(minim[info] != parinte[nod] && minim[nod] > nivel[info])
                        minim[nod] = nivel[info];
            }
    }

int main()
{
    int n, m, i, x, y;

    ifstream f("date.txt");

    f >> n >> m;

    for(i = 1; i <= n; i++)
        {
         culoare[i] = 0;
         parinte[i] = 0;
         nivel[i] = 0;
         minim[i] = 99;
        }

    for (i = 0; i < m; i++)
        {
            f >> x >> y;
            v[y].push_back(x);
            v[x].push_back(y);
        }

    cout << "Muchii critice\n";

    for(i = 1; i <= n; i++)
        if(!culoare[i])
        {
            nivel[i] = 1;
            sursa = i;
            fii = 0;
            DFS(i);
            punct[sursa] = fii > 1;
        }

    /*cout << "Nod: ";
    for(i = 1; i <= n; i++)
        cout << i << " ";
    cout << endl << "Niv: ";
    for(i = 1; i <= n; i++)
        cout << nivel[i] << " ";
    cout << endl << "Min: ";
    for(i = 1; i <= n; i++)
        cout << minim[i] << " ";
    cout << endl << "Tat: ";
    for(i = 1; i <= n; i++)
        cout << parinte[i] << " ";
    */

    cout << endl << "Puncte critice: ";

    for(i = 1; i <= n; i++)
        if(punct[i])
            cout << i << " ";

    cout << endl;

    return 0;
}
