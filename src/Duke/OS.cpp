#include "OS.h"

OperatingSystem duke;

void OperatingSystem::PrintLogo()
{
    cout<<" [======================================================]"<<endl;
    cout<<" |]====================================================[|"<<endl;
    cout<<" ||                                                    ||"<<endl;
    cout<<" ||  DDDDDD      UU      UU    KK   KKK    EEEEEEEE    ||"<<endl;
    cout<<" ||  DD   DD     UU      UU    KK KKK      EE          ||"<<endl; 
    cout<<" ||  DD    DD    UU      UU    KKKK        EE          ||"<<endl;
    cout<<" ||  DD    DD    UU      UU    KK          EEEEEEE     ||"<<endl;
    cout<<" ||  DD    DD    UU      UU    KKKK        EE          ||"<<endl;
    cout<<" ||  DD   DD      UU    UU     KK KKK      EE          ||"<<endl;
    cout<<" ||  DDDDDD        UUUUUU      KK   KKK    EEEEEEEE    ||"<<endl;
    cout<<" ||                                                    ||"<<endl;
    cout<<" |]====================================================[|"<<endl;
    cout<<" [======================================================]"<<endl;
    cout<<endl;
}

void OperatingSystem::Flash()
{
    HostOldTerminalRun("clear");
    PrintLogo();
    cout<<"                                                 ]_+_["  <<endl;
    cout<<"Dear knight,I am the Duke.What can I help you ? \\(@_<)/"<<endl;
    cout<<endl;
}

void OperatingSystem::HostOldTerminalRun(string command)
{
    system(command.c_str());
}

void OperatingSystem::HostNewTerminalRun(string command)
{
    string new_command="gnome-terminal -- bash -c \'"+command+"\'";
    system(new_command.c_str());
}

void OperatingSystem::Run()
{
    is_stop=false;
    
    while(!is_stop)
    {        
        string command_str; 
        cout<<"Command >> ";
        getline(cin,command_str);

        Parser parser(command_str);
        if(parser.GetNameArg())
        {
            unique_ptr<Command> command_ptr=parser.GetCommand();
            if(command_ptr)command_ptr->Excute();
        }
    }
}