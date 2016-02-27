#include <vector>
#include <stack>
#include <fstream>
#include <iostream>

using namespace std;

vector<int> v[201];
stack<int> q;

int culoare[201], parinte[201], nivele_fii[201], frecventa[100][3], cod_neville[100];

void DFS(int nod)
    {
        unsigned i, info;

        culoare[nod] = 1;
        for (i = 0; i < v[nod].size(); i++)
            {
                info = v[nod][i];

                if(!culoare[info])
                {
                    parinte[info] = nod;
                    culoare[info] = 1;
                    DFS(info);

                    if(nivele_fii[nod] < nivele_fii[info] + 1)
                        nivele_fii[nod] = nivele_fii[info] + 1;

                }
            }

    }

int main()
{
    int n, m, i, x, y;

    FILE *f = fopen("date.txt","r");

    fscanf(f,"%d",&n);
    m = n - 1;

    for (i = 0; i < m; i++)
        {
            fscanf(f,"%d%d",&x,&y);
            v[y].push_back(x);
            v[x].push_back(y);
        }

    for(i = 1; i <= n; i++)
        if(!culoare[i])
            DFS(i);

    for(i = 1; i <= n; i++)
        frecventa[nivele_fii[i]][0]++;

    frecventa[0][1] = 0;

    for(i = 1; i <= n; i++)
        if(frecventa[i][0])
            frecventa[i][1] = frecventa[i - 1][0] + frecventa[i - 1][1];
        else
            break;

    for(i = 1; i <= n; i++)
        {
            cod_neville[frecventa[nivele_fii[i]][1] + frecventa[nivele_fii[i]][2]] = parinte[i];
            frecventa[nivele_fii[i]][2]++;
        }

    cout << endl;

    cout << "Cod Neville: ";
    for(i = 0; i < n - 2; i++)
        cout << cod_neville[i];

    cout << endl;

    return 0;
}
