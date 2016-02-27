#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

int main()
{
    ifstream f("date.txt");

    vector<int> v[100];
    int vizitat[100], control[100], parinte[100], distanta[100];
    queue<int> q;

    int n, m, i, j, x, y, nod, sursa, col = 1, d, min = 999;

    f >> n;
    f >> m;

    for(i = 1; i <= 100; i++)
        {
         vizitat[i] = 0;
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

    cout << "Nr. puncte control: ";
    cin >> x;

    for (i = 0; i < x; i++)
        {
            cout << "Punct de control " << i + 1 << ": ";
            cin >> control[i];
        }

    if(sursa > n)
        return 0;

    cout << endl;

    vizitat[sursa] = col;
    distanta[sursa] = 0;
    q.push(sursa);

    while (!q.empty())
        {
         nod = q.front();
         q.pop();

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

    for(i = 0; i < x; i++)
        if(distanta[control[i]] < min)
            {
                min = distanta[control[i]];
                y = control[i];
            }

    cout << "Lantul de lungime minima " << distanta[y] << " este: ";

    n = d = distanta[y] + 1;
    vizitat[d] = y;
    d--;
    i = y;

    while(parinte[i])
    {
        vizitat[d] = parinte[i];
        i = parinte[i];
        d--;
    }

    for(i = 1; i <= n; i++)
        cout << vizitat[i] << " ";

    cout << endl;

    return 0;
}
