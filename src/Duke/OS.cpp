#include "OS.h"
//gnome-terminal -- bash -c 'echo Hello && ls && sleep 2 && echo Goodbye && sleep 2'
OperatingSystem duke;

void OperatingSystem::PrintLogo()
{
    cout<<"|======================================================|"<<endl;
    cout<<"||====================================================||"<<endl;
    cout<<"||                                                    ||"<<endl;
    cout<<"||  DDDDDD      UU      UU    KK   KKK    EEEEEEEE    ||"<<endl;
    cout<<"||  DD   DD     UU      UU    KK KKK      EE          ||"<<endl; 
    cout<<"||  DD    DD    UU      UU    KKKK        EE          ||"<<endl;
    cout<<"||  DD    DD    UU      UU    KK          EEEEEEE     ||"<<endl;
    cout<<"||  DD    DD    UU      UU    KKKK        EE          ||"<<endl;
    cout<<"||  DD   DD      UU    UU     KK KKK      EE          ||"<<endl;
    cout<<"||  DDDDDD        UUUUUU      KK   KKK    EEEEEEEE    ||"<<endl;
    cout<<"||                                                    ||"<<endl;
    cout<<"||====================================================||"<<endl;
    cout<<"|======================================================|"<<endl;
    cout<<endl;
}

void OperatingSystem::Flash()
{
    system("clear");
    PrintLogo();
    cout<<"                                                 ]_+_["<<endl;
    cout<<"Dear knight,I am the Duke.What can I help you ? \\(@_<)/"<<endl;
    cout<<endl<<"Command >> ";
}

void OperatingSystem::Run()
{
    string command_str;
    cin>>command_str;

    while(command_str!="byebye")
    {
        cout<<"Command >> ";
        cin>>command_str;
    }
}