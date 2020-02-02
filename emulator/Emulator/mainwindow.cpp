#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_debugger = new DebuggerDialog(&m_mb, this);
}

MainWindow::~MainWindow()
{
    delete m_debugger;
    delete ui;
}

void MainWindow::startMegabrain()
{
    m_mb.start();
}

void MainWindow::showDebugger()
{
    m_debugger->show();
}

