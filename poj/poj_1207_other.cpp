#include<iostream>
#include<string>
#include<algorithm>
#include<cstdio>
#include<cctype>
using namespace std;
const int kMaxn(107);

int main()
{
    /*
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    //*/

    int T(0);
    string line1,line2;
    while(getline(cin,line1) && getline(cin,line2))
    {
        T++;
        if(T!=1)
            cout<<endl;

        string var;
        for(int i=0;i<line1.size();i++)
            if(isalpha(line1[i]))
                var+=line1[i];
        sort(var.begin(),var.end());

        int cnt(0);
        char ch1,ch2,x[kMaxn],y[kMaxn];
        for(int i=0,j=0;i<line2.size();i++)
        {
            if(isalpha(line2[i]))
            {
                j++;
                if(j&1)
                    ch1=line2[i];
                else
                {
                    ch2=line2[i];
                    cnt++;
                    x[cnt]=ch1;
                    y[cnt]=ch2;
                }
            }
        }

        do
        {
            bool success(true);
            for(int i=1;i<=cnt;i++)
                if(find(var.begin(),var.end(),y[i])-find(var.begin(),var.end(),x[i])<0)
                {
                    success=false;
                    break;
                }
            if(success)
                cout<<var<<endl;
        }while(next_permutation(var.begin(),var.end()));
    }

    return 0;
}