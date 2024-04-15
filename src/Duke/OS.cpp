#include "OS.h"

OperatingSystem duke;

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



void OperatingSystem::PrintLogo0()
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

void OperatingSystem::PrintLogo1()
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

void OperatingSystem::PrintLogo2()
{
    cout<<" [======================================================]"<<endl;
    cout<<" |]====================================================[|"<<endl;
    cout<<" ||                                                    ||"<<endl;
    cout<<" ||\033[95m  DDDDDD      UU      UU    KK   KKK    EEEEEEEE    \033[0m||"<<endl;
    cout<<" ||\033[95m  DD   DD     UU      UU    KK KKK      EE          \033[0m||"<<endl; 
    cout<<" ||\033[95m  DD    DD    UU      UU    KKKK        EE          \033[0m||"<<endl;
    cout<<" ||\033[95m  DD    DD    UU      UU    KK          EEEEEEE     \033[0m||"<<endl;
    cout<<" ||\033[95m  DD    DD    UU      UU    KKKK        EE          \033[0m||"<<endl;
    cout<<" ||\033[95m  DD   DD      UU    UU     KK KKK      EE          \033[0m||"<<endl;
    cout<<" ||\033[95m  DDDDDD        UUUUUU      KK   KKK    EEEEEEEE    \033[0m||"<<endl;
    cout<<" ||                                                    ||"<<endl;
    cout<<" |]====================================================[|"<<endl;
    cout<<" [======================================================]"<<endl;
    cout<<endl;
}

void OperatingSystem::Flash()
{
    HostOldTerminalRun("clear");
    //PrintLogo1();
    PrintLogo2();

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