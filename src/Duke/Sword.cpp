#include "Sword.h"
#include "OS.h"

void Sword::Blank(int n)
{
    for(int i=0;i<n;i++)cout<<" ";
}

void Sword::Whole()
{
    cout<<endl;
    cout<<"                                         /|\\"<<endl;
    cout<<"                                         \\|$\\"<<endl;
    cout<<"  ________________________________________|@#\\            |>"<<endl;
    cout<<" /   ///////   Made By PJD   *--*--*--*<<<((((|=============\\"<<endl;
    cout<<"<-=-=-=-=-=-=#X#X#X#X#X#X#X#=-=-=-=-=-=-=>{>>>(}<}<}<}<}<}<}<0)"<<endl;
    cout<<" \\________________________________________((((|=============/"<<endl;
    cout<<"                                          |@#/            |>"<<endl;
    cout<<"                                         /|$/"<<endl;
    cout<<"                                         \\|/"<<endl;
    cout<<endl;
}

void Sword::Fly()
{
    int move_item=5;
    int move_times=18;

    // Fly-Whole
    while(move_times>=0)
    {
        duke.HostOldTerminalRun("clear");
        cout<<endl;

        Blank(move_item*move_times);cout<<"                                         /|\\"<<endl;
        Blank(move_item*move_times);cout<<"                                         \\|$\\"<<endl;
        Blank(move_item*move_times);cout<<"  ________________________________________|@#\\            |>"<<endl;
        Blank(move_item*move_times);cout<<" /   ///////  Made By PJD :) *--*--*--*<<<((((|=============\\"<<endl;
        Blank(move_item*move_times);cout<<"<-=-=-=-=-=-=#X#X#X#X#X#X#X#=-=-=-=-=-=-=>{>>>(}<}<}<}<}<}<}<0)"<<endl;
        Blank(move_item*move_times);cout<<" \\________________________________________((((|=============/"<<endl;
        Blank(move_item*move_times);cout<<"                                          |@#/            |>"<<endl;
        Blank(move_item*move_times);cout<<"                                         /|$/"<<endl;
        Blank(move_item*move_times);cout<<"                                         \\|/"<<endl;

        cout<<endl;
        move_times--;

        usleep(1000*150);
    }


    //Fly-Part
    
}