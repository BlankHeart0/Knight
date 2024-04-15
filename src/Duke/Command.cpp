#include "Command.h"
#include "OS.h"
#include "Parser.h"

void CommandUsage(string command)
{   
    string usage=CommandUsage_map[command];
    command[0]=toupper(command[0]);
    
    cout<<command<<" Usage: \033[96m"<<usage<<"\033[0m"<<endl;
}



void Byebye::Excute()
{
    duke.is_stop=true;
    duke.HostOldTerminalRun("clear");
}

void _Command::Excute()
{
    for(auto& it:CommandUsage_map)
        cout<<"\033[96m* \033[92m"<<it.second<<"\033[0m"<<endl;
}

void History::Excute()
{
    for(int i=0;i<duke.history_command.size();i++)
    {
        cout<<"\033[96m"<<i<<"\t\033[92m"<<duke.history_command[i]<<"\033[0m"<<endl;
    }
}

void Echo::Excute()
{
    cout<<"\033[92m"<<something<<"\033[0m"<<endl;
}

void Again::Excute()
{
    duke.history_command.pop_back();// don't save again

    if(duke.history_command.size()>0)
    {
        string command_str=duke.history_command.back();
        Parser parser(command_str);
        if(parser.GetNameArg())
        {
            unique_ptr<Command> command_ptr=parser.GetCommand();
            if(command_ptr)
            {
                duke.history_command.push_back(command_str);
                command_ptr->Excute();
            }
        }
    }
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

void Uninstall::Excute()
{
    duke.HostOldTerminalRun("rm "+application);
}

void Run::Excute()
{
    duke.HostNewTerminalRun("steed "+application);
}
