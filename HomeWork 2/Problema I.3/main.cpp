#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream f("date.txt");

    int n, i, nr_muchii, vf_terminal, vf_neterminal, v[100], s = 0;

    nr_muchii = 0;
    vf_terminal = 1;

    f >> n;

    for(i = 0; i < n; i++)
        {
            f >> v[i];
            s+=v[i];
        }

    if(s != 2 * (n - 1))
    {
        cout << "Nu e secventa!";
        return 0;
    }

    while(nr_muchii < n - 1)
    {
        while(v[vf_neterminal] == 1)
            vf_neterminal++;

        nr_muchii++;

        cout << vf_terminal << " " << vf_neterminal << endl;

        v[vf_neterminal]--;
        vf_terminal++;
    }

    return 0;
}
