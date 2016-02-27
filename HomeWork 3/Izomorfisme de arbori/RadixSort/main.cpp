#include<iostream>
#include<cstring>
#include<fstream>

using namespace std;

ifstream fin("date.txt");
char txt[255],*ord[255],sep[]=",;.?! \t\n",*p;
int i,j;

int main()
{
        fin.read(txt, 255);
        //fin.get(txt,255);
        p=strtok(txt,sep);
        i=j=0;
        while (p)
        {
                cout<<p<<endl;
                ord[i++]=p;
                p=strtok(NULL,sep);
        }
        //ordonezi acum dupa valoarea lui ord[j][0]
        //iteram aici ca sa vezi cine este ord
        j=0; cout.put('\n')<<'\n';
        while(j<i)
        {
                cout<<ord[j]<<" valoarea lui ord["<<j<<"]="<<(int)ord[j][0]<<endl;
                j++;
        }

        return 0;
}
