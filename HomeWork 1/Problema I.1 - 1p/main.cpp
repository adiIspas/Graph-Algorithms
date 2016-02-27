#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

int main()
{
    ifstream f("date.txt");

    vector<int> v[100];
    int vizitat[100];
    queue<int> q;

    int n, m, i, j, x, y, nod, sursa, col = 1, sw = 1, B = 0;

    f >> n;
    f >> m;

    for(i = 1; i <= 100; i++)
         vizitat[i] = 0;

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

    cout << "\nParcurgerea in latime: ";

    vizitat[sursa] = col;
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
                    q.push(v[nod][i]);
                }
        }

    cout << endl << endl;

    for(i = 1; i < n; i++)
        for(j = 0; j < v[i].size(); j++)
            if(vizitat[i] == vizitat[v[i][j]])
            {
                cout << "Graful nu este bipartit!\n";
                return 0;
            }

    for(i = 1; i <= n; i++)
        if(vizitat[i] == 2)
            B++;

    for(i = 1; i <= n; i++)
        if(vizitat[i] == 1)
            if(v[i].size() != B)
                {
                    sw = 0;
                    break;
                }

    if (sw == 1)
        cout << "Graful este bipartit complet!";
    else
        cout << "Graful este bipartit!";

    cout << endl;
    cout << "Bipartitie: ";
    for(i = 0; i < n; i++)
        if(vizitat[i] == 1)
            cout << i << " ";

    cout << endl;

    return 0;
}
