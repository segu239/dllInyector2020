#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include<windows.h>
#include <psapi.h>
#include<QList>
#include<qDebug>
#include <QMessageBox>
# include <string>
# include <iostream>

class processManager
{
public:
    
    processManager();
    QList<QString>listaProcesos();

private:
    
    QString ObtenerListaProcesos( DWORD processID );
    
};

#endif // PROCESSMANAGER_H
