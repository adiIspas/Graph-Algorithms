#include <vector>
#include <queue>
#include <fstream>

using namespace std;

int vizitat[100000], suma[100000];

int main()
{
    //ifstream f("sate.in");
   // ofstream g("sate.out");

    FILE *f = fopen("sate.in","r");
    FILE *g = fopen("sate.out","w");

    vector<int> v[100000], dist[100000];
    queue<int> q;

    unsigned int n, m, i, start, sfarsit, x, y, nod, d, info, dist_info;

   // f >> n >> m >> start >> sfarsit;

   fscanf(f,"%d%d%d%d",&n,&m,&start,&sfarsit);

    for (i = 0; i < m; i++)
        {
           // f >> x >> y >> d;
            fscanf(f,"%d%d%d",&x,&y,&d);

            v[x].push_back(y);
            dist[x].push_back(d);

            v[y].push_back(x);
            dist[y].push_back(d);
        }

    vizitat[start] = 1;
    q.push(start);

    while (!q.empty())
        {
         nod = q.front();
         q.pop();

         for(i = 0; i < v[nod].size(); i++)
         {
            info = v[nod][i];
            dist_info = dist[nod][i];

            if(vizitat[info] == 0)
                {
                    vizitat[info] = 1;

                    if(nod > info)
                        suma[info] = suma[nod] - dist_info;

                    if(nod < info)
                        suma[info] = suma[nod] + dist_info;

                    if(info == sfarsit)
                        {
                           // g << suma[sfarsit];
                            fprintf(g,"%d",suma[sfarsit]);
                            return 0;
                        }

                    q.push(info);
                }
            }
        }

   // g << suma[sfarsit];
   fprintf(g,"%d",suma[sfarsit]);

    return 0;
}
