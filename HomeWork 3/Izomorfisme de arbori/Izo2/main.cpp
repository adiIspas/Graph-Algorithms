#include <iostream>
#include <vector>

struct cod
    {
        int n;
        char c[100];

    }codificare[100];

using namespace std;

int main()
{
    int n, i, j, k, l;
    vector<int> v1[100], v2[100];

    //cout << int(s[1] - 48);
    cin >> n;

    for(i = 0; i < n; i++)
    {
        cin.get();
        cin.get(codificare[i].c,100);
        codificare[i].n = i;
    }


    for(i = 0; i < n; i++)
        {
            v1[int(codificare[i].c[0] - 48)].push_back(codificare[i].n);
            v2[int(codificare[i].c[0] - 48)].push_back(codificare[i].n);
        }

    for(i = 0; i < n; i++)
        v1[i].clear();

    for(i = 1; i < 3; i++)
        for(j = 0; j < 10; j++)
            {
            // for(k = 0; k < n; k++)
                {
                    for(l = 0; l < v2[j].size(); l++)
                        v1[int(codificare[v2[j][l]].c[i] - 48)].push_back(v2[j][l]);
                }

             for(k = 0; k < n; k++)
                v2[k].clear();

             for(k = 0; k < n; k++)
                for(l = 0; l < v1[k].size(); l++)
                    {
                       // cout << v1[k][l] << " ";
                        v2[k].push_back(v1[k][l]);
                    }

             for(k = 0; k < n; k++)
                v1[k].clear();
            }

    for(i = 0; i < 3; i++)
    {
        if(v2[i].size())
        {
            cout << i << ": ";
            for(j = 0; j < v2[i].size(); j++)
                cout << v2[i][j] << " ";
            cout << endl;
        }
    }

    return 0;
}
