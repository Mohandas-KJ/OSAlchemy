//Imports
#include <stdio.h>
#include <windows.h>

//Linkers
#pragma comment(lib,"winmm.lib")
#pragma comment(lib, "advapi32.lib")

//Function to Check Constantly
int waitForAudioService(){
    
    //Connect to SCM Database
    SC_HANDLE scm = OpenSCManager(NULL,NULL,SC_MANAGER_CONNECT);

    //Verify
    if(!scm){
        return 0;
    }

    //Search for a query
    SC_HANDLE service = OpenService(scm,"Audiosrv",SERVICE_QUERY_STATUS);

    //Verify
    if (!service){
        CloseServiceHandle(scm);
        return 0;
    }

    //DWORD to save status
    SERVICE_STATUS status;

    //Check constantly
    while (1){
        QueryServiceStatus(service,&status);

        if(status.dwCurrentState == SERVICE_RUNNING){
            break;
        }

        Sleep(1000);
    }
    
    CloseServiceHandle(scm);
    CloseServiceHandle(service);
    return 1;

}

int main(){
    waitForAudioService();

    PlaySound(TEXT("C:\\JarvisS\\Jarvis_Intro.wav"),NULL,SND_FILENAME | SND_SYNC);

    return 0;
}