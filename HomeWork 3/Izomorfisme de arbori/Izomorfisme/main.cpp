#include <vector>
#include <stack>
#include <fstream>
#include <iostream>

using namespace std;

vector<int> v[201];
stack<int> q;

int culoare[201], parinte[201], nivele_fii[201];

void DFS(int nod)
    {
        unsigned i, info;

        culoare[nod] = 1;

        cout << nod << " ";

        for (i = 0; i < v[nod].size(); i++)
            {
                info = v[nod][i];

                if(!culoare[info])
                {
                    parinte[info] = nod;
                    culoare[info] = 1;
                    DFS(info);
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

    return 0;
}
