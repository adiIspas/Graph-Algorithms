#include <fstream>
#include <iostream>

int grade[2][5005];

int main()
{
    FILE *f = fopen("grade.in","r");
    FILE *g = fopen("grade.out","w");

    int i, j, n, aux, index, grad, poz, nod;

    fscanf(f,"%d",&n);

    for(i = 1; i <= n; i++)
        grade[1][i] = i;

    for(i = 1; i <= n; i++)
         {
             fscanf(f,"%d",&nod);
             grade[2][i] = nod;
         }

    for(i = 1; i <= n; i++)
        for(j = i; j <= n; j++)
            if(grade[2][i] > grade[2][j])
            {
                aux = grade[2][i];
                grade[2][i] = grade[2][j];
                grade[2][j] = aux;

                aux = grade[1][i];
                grade[1][i] = grade[1][j];
                grade[1][j] = aux;
            }

    poz = 1;

    while(grade[2][poz])
    {
        index = n;
        grad = grade[2][poz];

        for(j = 0; j < grad; j++)
            {
                if(grade[1][poz] == grade[1][index])
                {
                    fprintf(g,"Nu se poate!");
                    return 0;
                }
                fprintf(g,"%d %d\n",grade[1][poz],grade[1][index]);
                grade[2][index]--;
                grade[2][poz]--;
                index--;
            }

    for(i = 1; i <= n; i++)
        for(j = i; j <= n; j++)
            if(grade[2][i] > grade[2][j])
            {
                aux = grade[2][i];
                grade[2][i] = grade[2][j];
                grade[2][j] = aux;

                aux = grade[1][i];
                grade[1][i] = grade[1][j];
                grade[1][j] = aux;
            }

    if(poz < n)
        poz++;
    }

    return 0;
}
