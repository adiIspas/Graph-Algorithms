#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream f("input.txt");
    ofstream g("output.txt");

    int nr_noduri, grade[100], i, j, s = 0, sw, nod1, nod2;

    f >> nr_noduri;

    for(i = 0; i < nr_noduri; i++)
       {
         f >> grade[i];
         s += grade[i];
       }

    if(s%2)
        {
            cout << "Nu poate fi multisetul gradelor unui graf neorientat!";
            return 0;
        }

    for(i = 0; i < nr_noduri; i++)
        if(grade[i] >= 2)
            while(grade[i] > 1)
            {
                cout << i + 1 << " " << i + 1 << endl;
                grade[i] -= 2;
            }


    sw = 0;
    for(i = 0; i < nr_noduri; i++)
        {
            if(sw == 0)
                if(grade[i] == 1)
                    {
                        nod1 = i + 1;
                        grade[i]--;
                        sw++;
                    }
            if(sw == 1)
                if(grade[i] == 1)
                    {
                        nod2 = i + 1;
                        grade[i]--;
                        sw++;
                    }
            if(sw == 2)
                {
                    cout << nod1 << " " << nod2 << endl;
                    sw = 0;
                }

        }

    return 0;
}
