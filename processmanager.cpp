#include "processmanager.h"

processManager::processManager()
{

}

QList<QString> processManager::listaProcesos()
{
    QList<QString> list;

    DWORD aProcesses[1024], cbNeeded, cProcesses;
    if ( !EnumProcesses( aProcesses, //array----->contains process identifier ids
                         sizeof(aProcesses), // size 
                         &cbNeeded ) )//number of bytes returned in the pProcessIds array
    {

        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Error Enumerating Processes");
        msgBox.setInformativeText("...");
        msgBox.exec();
    }
    
    // Calculate how many process identifiers were returned.

    cProcesses = cbNeeded / sizeof(DWORD);//cant de procesos

    // Print the name and process identifier for each process.

    for ( int i = 0; i < cProcesses; i++ )
    {
        if( aProcesses[i] != 0 ) // obtains each processid to be called by obtenerlistadeprocesos
        {
            QString processes= ObtenerListaProcesos( aProcesses[i]);
            if (processes != "unknown")
                list.append(processes);
        }
    }
    return list;
}

QString processManager::ObtenerListaProcesos( DWORD processID )
{
    //GetProcessList();
    TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");

    // Get a handle to the process.

    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ,
                                   FALSE, processID );

    // Get the process name.

    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod),
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName,
                               sizeof(szProcessName)/sizeof(TCHAR) );
        }
    }

    // Print the process name and identifier.
    QString proc= QString::fromWCharArray(szProcessName);
    QString id= QString::number(processID);
    unsigned long PID= processID;
    //QString id= (LPSTR)processID;
    QString result= proc + ":" + id;
    if (proc != "<unknown>")
    {    
     qDebug()<<proc;

    //QList<QString> list;//ui->listWidget_procesos->addItem(result);
     return result;//proc+":"+id;//list.append(result);
    }
    return "unknown";

    CloseHandle( hProcess );
}
