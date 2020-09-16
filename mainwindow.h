#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QFileDialog>

#include <string>
#include "processmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_view_clicked();
    void showContextMenuListWidget(const QPoint &);
    void deleteItems();
    void deleteAllItems();
    void inject();

    void on_pushButton_inject_clicked();

    void on_toolButton_dllpath_clicked();

    bool InjectDLL(const int &pid, const std::string &DLL_Path);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
