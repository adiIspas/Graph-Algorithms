#include <vector>
#include <fstream>

using namespace std;

vector<int> v[200001];

int culoare[200001];

void DFS(int nod)
    {
        int i, info;

        culoare[nod] = 1;

        for (i = 0; i < v[nod].size(); i++)
            {
                info = v[nod][i];

                if(!culoare[info])
                    DFS(info);
           }
    }

int main()
{
    int n, m, i, x, y, k = 0;

    //ifstream f("biconex.in");
    //ofstream g("biconex.out");

    FILE *f = fopen("dfs.in","r");
    FILE *g = fopen("dfs.out","w");

   // f >> n >> m;

   fscanf(f,"%d%d",&n,&m);

    for (i = 0; i < m; i++)
        {
            //f >> x >> y;
            fscanf(f,"%d%d",&x,&y);
            v[y].push_back(x);
            v[x].push_back(y);
        }

    for(i = 1; i <= n; i++)
        if(!culoare[i])
        {
            DFS(i);
            k++;
        }

    //g << k << "\n";
    fprintf(g,"%d",k);

    return 0;
}
