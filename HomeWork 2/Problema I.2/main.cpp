#include <fstream>

using namespace std;

int grade[2][5001];

int main()
{
    ifstream f("grade.in");
    ofstream g("grade.out");

    int i, j, n, aux;

    f >> n;

    for(i = 1; i <= n; i++)
        grade[1][i] = i;

    for(i = 1; i <= n; i++)
        f >> grade[2][i];

    while(grade[2][1] > 0)
    {for(i = 1; i <=n; i++)
        for(j = i; j <= n; j++)
            if(grade[2][i] < grade[2][j])
            {
                aux = grade[2][i];
                grade[2][i] = grade[2][j];
                grade[2][j] = aux;

                aux = grade[1][i];
                grade[1][i] = grade[1][j];
                grade[1][j] = aux;
            }

     for(i = 2; i <= grade[2][1] + 1; i++)
        {g << grade[1][1] << " " << grade[1][i] << endl;
         grade[2][i]--;

         if(grade[2][i] < 0)
         {
             g << "Nu se poate!";
             return 0;
        }
        }

     grade[2][1] = 0;

     for(i = 1; i <=n; i++)
        for(j = i; j <= n; j++)
            if(grade[2][i] < grade[2][j])
            {
                aux = grade[2][i];
                grade[2][i] = grade[2][j];
                grade[2][j] = aux;

                aux = grade[1][i];
                grade[1][i] = grade[1][j];
                grade[1][j] = aux;
            }
    }

    return 0;
}
