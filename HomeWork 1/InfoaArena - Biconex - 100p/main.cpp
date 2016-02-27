#include <vector>
#include <stack>
#include <fstream>

using namespace std;

vector<int> v[200001], noduri[200001];

int culoare[200001], parinte[200001], nivel[200001], minim[200001], noduri2[200001];
char punct[200001];

stack<int> q;

int sursa, fii, x, y;

void DFS(int nod, int& k)
    {
        int i, info;

        culoare[nod] = 1;

        minim[nod] = nivel[nod];

        for (i = 0; i < v[nod].size(); i++)
            {
                info = v[nod][i];

                if(info != parinte[nod] && nivel[nod] > nivel[info])
                    {
                     q.push(info);
                     q.push(nod);
                    }

                if(!culoare[info])
                {
                    nivel[info] = nivel[nod] + 1;
                    parinte[info] = nod;

                    if(nod == sursa)
                        fii++;

                    DFS(info,k);

                    if(minim[nod] > minim[info])
                        minim[nod] = minim[info];

                    if(minim[info] >= nivel[nod])
                        {
                            do
                            {
                                x = q.top();
                                q.pop();

                                noduri[k].push_back(x);

                                y = q.top();
                                q.pop();

                                noduri[k].push_back(y);
                            }
                            while((x != nod || y != info) && (x != info || y != nod));

                            k++;
                        }
                }
                else
                    if(info != parinte[nod] && minim[nod] > nivel[info])
                        minim[nod] = nivel[info];
            }
    }

int main()
{
    int n, m, i, j, x, y, max, k = 0;

    //ifstream f("biconex.in");
    //ofstream g("biconex.out");

    FILE *f = fopen("biconex.in","r");
    FILE *g = fopen("biconex.out","w");

   // f >> n >> m;

   fscanf(f,"%d%d",&n,&m);

    for(i = 1; i <= n; i++)
         minim[i] = 999999;

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
            nivel[i] = 1;
            sursa = i;
            fii = 0;
            DFS(i,k);
            punct[sursa] = fii > 1;
        }

    //g << k << "\n";
    fprintf(g,"%d",k);
    fprintf(g,"\n");

    for(i = 0; i < k; i++)
        {
            max = 0;

            for(j = 0; j < noduri[i].size(); j++)
                {
                    noduri2[noduri[i][j]]++;
                    if(noduri[i][j] > max)
                        max = noduri[i][j];
                }
            for(j = 1; j <= max; j++)
                if(noduri2[j])
                    {
                        //g << j << " ";
                        fprintf(g,"%d ",j);
                        noduri2[j] = 0;
                    }

            //g << "\n";
            fprintf(g,"\n");
        }

    return 0;
}
