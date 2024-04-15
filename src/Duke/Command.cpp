#include "Command.h"
#include "OS.h"

void CommandUsage(string command)
{   
    string usage=CommandUsage_map[command];
    command[0]=toupper(command[0]);
    
    cout<<command<<" Usage: "<<usage<<endl;
}



void Byebye::Excute()
{
    duke.is_stop=true;
}

void _Command::Excute()
{
    for(auto& it:CommandUsage_map)
        cout<<it.second<<endl;
}

void Clear::Excute()
{
    duke.Flash();
}

void Draw::Excute()
{
    Sword::Fly();
    duke.Flash();
}

void List::Excute()
{
    switch(type)
    {
        case L_ALL:duke.HostOldTerminalRun("ls | grep -E '\\.ks$|^[^.]+$'");   break;
        case L_PKG:duke.HostOldTerminalRun("ls | grep '\\.ks$'");              break;
        case L_APP:duke.HostOldTerminalRun("ls | grep -v '\\..*$'");           break;
    }
}

void Run::Excute()
{
    duke.HostNewTerminalRun("steed "+application);
}
