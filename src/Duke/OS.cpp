#include "OS.h"

OperatingSystem duke;

void OperatingSystem::PrintLogo()
{
    cout<<"\033[95m [======================================================]\033[0m"<<endl;
    cout<<"\033[95m |]====================================================[|\033[0m"<<endl;
    cout<<"\033[95m ||\033[0m                                                    \033[95m||\033[0m"<<endl;
    cout<<"\033[95m ||\033[0m  DDDDDD      UU      UU    KK   KKK    EEEEEEEE    \033[95m||\033[0m"<<endl;
    cout<<"\033[95m ||\033[0m  DD   DD     UU      UU    KK KKK      EE          \033[95m||\033[0m"<<endl; 
    cout<<"\033[95m ||\033[0m  DD    DD    UU      UU    KKKK        EE          \033[95m||\033[0m"<<endl;
    cout<<"\033[95m ||\033[0m  DD    DD    UU      UU    KK          EEEEEEE     \033[95m||\033[0m"<<endl;
    cout<<"\033[95m ||\033[0m  DD    DD    UU      UU    KKKK        EE          \033[95m||\033[0m"<<endl;
    cout<<"\033[95m ||\033[0m  DD   DD      UU    UU     KK KKK      EE          \033[95m||\033[0m"<<endl;
    cout<<"\033[95m ||\033[0m  DDDDDD        UUUUUU      KK   KKK    EEEEEEEE    \033[95m||\033[0m"<<endl;
    cout<<"\033[95m ||\033[0m                                                    \033[95m||\033[0m"<<endl;
    cout<<"\033[95m |]====================================================[|\033[0m"<<endl;
    cout<<"\033[95m [======================================================]\033[0m"<<endl;
    cout<<endl;
}

void OperatingSystem::Flash()
{
    HostOldTerminalRun("clear");
    PrintLogo();

    cout<<"\033[5m\033[93m                                                 ";
    cout<<"]_+_[\033[0m"  <<endl;

    cout<<"\033[92mDear knight,I am the Duke.What can I help you ? ";
    cout<<"\033[5m\033[96m\\\033[0m\033[96m(@_<)\033[5m/\033[0m"<<endl;
    cout<<endl;
}

void OperatingSystem::HostOldTerminalRun(string command)
{
    system(command.c_str());
}

void OperatingSystem::HostNewTerminalRun(string command)
{
    string new_command="gnome-terminal -- bash -c \'"+command+";read"+"\'";
    system(new_command.c_str());
}

void OperatingSystem::Run()
{
    is_stop=false;
    
    while(!is_stop)
    {        
        string command_str; 
        cout<<"\033[94mCommand >> \033[0m";
        getline(cin,command_str);

        Parser parser(command_str);
        if(parser.GetNameArg())
        {
            unique_ptr<Command> command_ptr=parser.GetCommand();
            if(command_ptr)
            {
                history_command.push_back(command_str);
                command_ptr->Excute();
            }
        }
    }
}