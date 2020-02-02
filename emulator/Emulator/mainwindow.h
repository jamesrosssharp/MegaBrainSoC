#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "megabrain.h"

#include "debuggerdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void startMegabrain();
    void showDebugger();

private:
    Ui::MainWindow *ui;

    DebuggerDialog* m_debugger;
    MegaBrain m_mb;
};

#endif // MAINWINDOW_H
