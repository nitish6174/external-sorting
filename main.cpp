#include <bits/stdc++.h>
using namespace std;

void display(std::vector<int> v,int l,int r,bool mode);

int main(int argc, char **argv)
{
    int no_of_buffer, key_per_page, buffer_per_input,buffer_available,keys;
    char filename[100];
    string s;
    int n, num, i;
    std::vector<int> a, b, c;
    int pass, run, last;
    fstream f;

    if(argc!=5)
        cout<<"Usage:"<<endl<<"./filename <number of buffers> <keys per page> <buffer per input> <input file>"<<endl;
    else
    {
        no_of_buffer = atoi(argv[1]);
        key_per_page = atoi(argv[2]);
        buffer_per_input = atoi(argv[3]);
        strcpy(filename, argv[4]);

        if(3*buffer_per_input>no_of_buffer)
            cout<<"This set of parameters is invalid"<<endl;
        else
        {
            f.open(filename,ios::in);
            while(getline(f,s))
                a.push_back(atoi(s.c_str()));
            n = a.size();

            cout<<"Input :"<<endl;
            display(a,0,n,0);
            cout<<"----------"<<endl<<endl;

            buffer_available = no_of_buffer/buffer_per_input;
            keys = no_of_buffer * key_per_page;

            pass = 0;
            run = 1;
            cout<<"Pass "<<pass<<":"<<endl;
            for( i=0 ; i<n ; i+=keys )
            {
                b.push_back(i);
                cout<<"  Run "<<run<<":"<<endl;
                last = i + keys;
                if( last > n )
                    last = n;
                cout<<"    ";
                display(a,i,last,0);
                sort(a.begin() + i, a.begin() + last);
                cout<<"    Output:"<<endl;
                cout<<"    ";
                display(a,i,last,0);
                run++;
            }
            cout<<"Total Input Runs in Pass "<<pass<<": "<<n<<endl;
            cout<<"Total Output Runs Produced after Pass "<<pass<<": "<<run-1<<endl;
            pass++;
            while(b.size()>1)
            {
                cout<<endl;
                cout<<"Pass "<<pass<<":"<<endl;
                run = 1;
                for( i=0 ; i<b.size() ; i+=(buffer_available-1) )
                {
                    c.push_back(b[i]);
                    if((i+buffer_available-1)>=b.size())
                        last = n;
                    else
                        last = b[i+buffer_available-1];
                    cout<<"  Run"<<run<<":"<<endl;
                    cout<<"    ";
                    display(a,b[i],last,0);
                    sort(a.begin()+b[i], a.begin()+last);
                    cout<<"    Output:"<<endl;
                    cout<<"    ";
                    display(a,b[i],last,0);
                    run++;
                }
                cout<<"Total Input Runs in Pass "<<pass<<": "<<b.size()<<endl;
                cout<<"Total Output Runs Produced after Pass "<<pass<<": "<<run-1<<endl ;
                b=c;
                c.clear();
                pass++;
            }
        }
    }

    return 0;
}

void display(std::vector<int> v,int l,int r,bool mode=0)
{
    if(mode) cout<<"[ ";
    cout<<v[l];
    for(int i=l+1;i<r;i++)
    {
        if(mode) cout<<",";
        cout<<" "<<v[i];
    }
    if(mode) cout<<" ]";
    cout<<endl;
}
