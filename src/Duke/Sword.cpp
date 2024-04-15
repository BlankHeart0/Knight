#include "Sword.h"
#include "OS.h"

void Sword::Blank(int n)
{
    for(int i=0;i<n;i++)cout<<" ";
}

void Sword::Endl(int n)
{
    for(int i=0;i<n;i++)cout<<endl;
}

void Sword::Whole()
{
    Endl(12);
    
    for(string sword_line:sword)
        cout<<sword_line<<endl;

    Endl(1);
}

void Sword::Fly()
{
    int move_item=5;
    int move_times=20;

    // Fly-Whole
    while(move_times>=0)
    {
        duke.HostOldTerminalRun("clear");

        Endl(12);
        for(string& line_sword:sword)
        {
            Blank(move_item*move_times);
            cout<<line_sword<<endl;
        }

        move_times--;
        usleep(1000*150);
    }

    //Fly-Part
    bool done=false;
    move_times=1;
    while(!done)
    {
        duke.HostOldTerminalRun("clear");

        Endl(12);
        done=true;
        int begin=move_times*move_item;
        for(string& line_sword:sword)
        {
            int size=line_sword.size();
            if(begin<size)
            {
                cout<<line_sword.substr(begin,size-begin);
                done=false;
            }
            Endl(1);
        }

        move_times++;
        usleep(1000*150);
    }
}