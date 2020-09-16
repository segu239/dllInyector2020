#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->listWidget_processes->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listWidget_processes, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenuListWidget(QPoint)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_view_clicked()
{
    ui->listWidget_processes->clear();
    processManager processes;
    ui->listWidget_processes->addItems(processes.listaProcesos());
    // qDebug()<< processes.listaProcesos();
}

void MainWindow::showContextMenuListWidget(const QPoint &pos)
{
    // Handle global position
        QPoint globalPos = ui->listWidget_processes->mapToGlobal(pos);

        // Create menu and insert some actions
        QMenu myMenu;
        myMenu.addAction("clear", this, SLOT(deleteAllItems()));
        //myMenu.addAction("Insert", this, SLOT(addItem()));
        myMenu.addAction("delete item",  this, SLOT(deleteItems()));
        myMenu.addAction("inject",  this, SLOT(inject()));
        // Show context menu at handling position
        myMenu.exec(globalPos);
}

void MainWindow::deleteItems()
{
    // If multiple selection is on, we need to erase all selected items
    for (int i = 0; i < ui->listWidget_processes->selectedItems().size(); ++i) {
        // Get curent item on selected row
        QListWidgetItem *item = ui->listWidget_processes->takeItem(ui->listWidget_processes->currentRow());
        // And remove it
        delete item;
    }
}

void MainWindow::deleteAllItems()
{
    ui->listWidget_processes->clear();
}

void MainWindow::inject()
{

   QListWidgetItem *item = ui->listWidget_processes->currentItem();//ui->listWidget_processes->takeItem(ui->listWidget_processes->currentRow());
   if (item != nullptr)
   {
   qDebug() << item->text();
   int ind= item->text().lastIndexOf(':');
   qDebug() << "PID:" << item->text().right(item->text().length() - (ind+1));
   int pid= item->text().right(item->text().length() - (ind+1)).toInt();
//   qDebug() << "PID:" << item->text().right(item->text().length() - (ind-1));
//   qDebug() << "PID:" << item->text().left(ind);
   InjectDLL(pid , ui->lineEdit_dllpath->text().toStdString());
   }
   else
   {
     MessageBox(0, L"Please Select a Process to inject", L"ERROR",MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
   }
}

void MainWindow::on_pushButton_inject_clicked()
{
    if(ui->lineEdit_dllpath->text().length() > 1)
    {
        inject();
    }
    else
    {
         MessageBox(0, L"Please Select a DLL to inject", L"ERROR",MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
    }
}

void MainWindow::on_toolButton_dllpath_clicked()
{
     QString Filename= QFileDialog::getOpenFileName(this,"choose dll","C://");
     ui->lineEdit_dllpath->setText(Filename);
}
