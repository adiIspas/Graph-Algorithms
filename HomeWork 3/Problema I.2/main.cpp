#include <vector>
#include <stack>
#include <fstream>
#include <iostream>

using namespace std;

vector<int> v[100];
stack<int> q;

int culoare[1000], parinte[100], grad[100], cod_prufer[100], aparitie[100];

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
                }
            }

    }

int main()
{
    int n, m, i, x, y, k, minim, index;

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
        grad[i] = v[i].size();

    for(k = 1; k <= n; k++)
        if(minim > k && grad[k] == 1)
                minim = k;

    index = x = minim;

    for(i = 1; i <= n - 2; i++)
        {
            y = parinte[x];
            cod_prufer[i] = y;
            grad[y]--;

            if(y < index && grad[y] == 1)
                x = y;
            else
            {
                index++;
                while(grad[index] > 1)
                    index++;

                x = index;
            }
        }

    cout << "Codificare: ";
    for(i = 1; i <= n - 2; i++)
        cout << cod_prufer[i] << " ";
    cout << endl << endl;

    fscanf(f,"%d",&n);
    for(i = 1; i <= n; i++)
        {
            fscanf(f,"%d",&cod_prufer[i]);
            aparitie[cod_prufer[i]]++;
        }

    for(i = 1; i <= n + 2; i++)
        aparitie[i]++;

    for(k = 1; k <= n + 2; k++)
        if(aparitie[k] == 1)
            {
                minim = k;
                break;
            }

    index = x = minim;

    cout << "Decodificare\n";
    for(i = 1; i <= n; i++)
        {
            y = cod_prufer[i];
            cout << x << " " << y << endl;
            aparitie[y]--;

            if(y < index && aparitie[y] == 1)
                x = y;
            else
            {
                index++;
                while(aparitie[index] > 1)
                    index++;

                x = index;
            }
        }

        cout << y << " " << n + 2;

    return 0;
}
