#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

int main()
{
    ifstream f("date.txt");

    vector<int> v[100];
    int vizitat[100], culoare[100], parinte[100], distanta[100];
    queue<int> q;

    int n, m, i, j, x, y, nod, sursa, col = 1, k = 1, cc = 1;

    f >> n;
    f >> m;

    for(i = 1; i <= 100; i++)
        {
         vizitat[i] = 0;
         culoare[i] = 0;
         parinte[i] = 0;
         distanta[i] = 999;
        }

    for (i = 0; i < m; i++)
        {
            f >> x >> y;
            v[x].push_back(y);
            v[y].push_back(x);
        }

    cout << "Nod de start: ";
    cin >> sursa;

    if(sursa > n)
        return 0;

    while(vizitat[sursa] == 0)
    {

        cout << "\nComponenta conexa " << cc << ": ";

    vizitat[sursa] = col;
    distanta[sursa] = 0;
    q.push(sursa);

    while (!q.empty())
        {
         nod = q.front();
         q.pop();
         cout << nod << " ";

         col = vizitat[nod];

         if(col == 1)
            col = 2;
         else
            col = 1;

         for(i = 0; i < v[nod].size(); i++)
            if(vizitat[v[nod][i]] == 0)
                {
                    vizitat[v[nod][i]] = col;
                    parinte[v[nod][i]] = nod;
                    distanta[v[nod][i]] = distanta[nod] + 1;
                    q.push(v[nod][i]);
                }
        }

    for(i = 1; i <= n; i++)
        if(vizitat[i] == 0)
            {sursa = i;
             k++;
            }
    cc++;
    cout << endl;
    }

    return 0;
}
