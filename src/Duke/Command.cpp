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
        CommandParser parser(command_str);
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

void Install::Excute()
{
    cout<<"\033[93mInstalling ... ...\033[0m"<<endl<<endl;
    sleep(2);

    FileManager file_manager;
    if(file_manager.InstallInitialize(package)&&file_manager.Open())
    {
        string line_code=file_manager.ReadLine();
        while(line_code!="")
        {
            InstructionParser parser(line_code);
            if(parser.opcode_str=="perm"||parser.opcode_str=="PERM")
            {
                cout<<"Require permission: \033[96m"<<parser.operand1_str<<"\033[0m, yes or no? (y/n)"<<endl;
                
                string selection;
                getline(cin,selection);
                while(selection!="y"&&selection!="n")
                {
                    cout<<"Input invalid,please input your selection again!"<<endl;
                    getline(cin,selection);
                }

                file_manager.Write(parser.opcode_str);
                file_manager.Write("\t");
                file_manager.Write(parser.operand1_str);
                file_manager.Write(",");
                file_manager.Write(selection=="y"?"1":"0");
            }
            else 
            {
                file_manager.Write(line_code);
            }
            file_manager.WriteEndl();

            line_code=file_manager.ReadLine();
        }

        file_manager.Close();
        sleep(2);
        cout<<endl<<"\033[92mInstall Done :)\033[0m"<<endl<<endl;
    }
}

void Uninstall::Excute()
{
    duke.HostOldTerminalRun("rm "+application);
}

void Chperm::Excute()
{
    cout<<"Change \033[93m"+application+"\033[0m's permission"<<endl<<endl;
    sleep(1);

    FileManager file_manager;
    if(file_manager.ChpermInitialize(application)&&file_manager.Open())
    {
        string line_code=file_manager.ReadLine();
        while(line_code!="")
        {
            InstructionParser parser(line_code);
            if(parser.opcode_str=="perm"||parser.opcode_str=="PERM")
            {
                cout<<"Require permission: \033[96m"<<parser.operand1_str<<"\033[0m, yes or no? (y/n)"<<endl;
                
                string selection;
                getline(cin,selection);
                while(selection!="y"&&selection!="n")
                {
                    cout<<"Input invalid,please input your selection again!"<<endl;
                    getline(cin,selection);
                }

                file_manager.Write(parser.opcode_str);
                file_manager.Write("\t");
                file_manager.Write(parser.operand1_str);
                file_manager.Write(",");
                file_manager.Write(selection=="y"?"1":"0");
            }
            else 
            {
                file_manager.Write(line_code);
            }
            file_manager.WriteEndl();

            line_code=file_manager.ReadLine();
        }

        file_manager.Close();
        file_manager.Remove();
        sleep(1);
        cout<<endl<<"\033[92mChange Done :)\033[0m"<<endl<<endl;
    }
}

void Run::Excute()
{
    duke.HostNewTerminalRun("sleep 1;steed "+application);
}
