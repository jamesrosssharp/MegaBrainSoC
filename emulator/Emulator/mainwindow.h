#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QImage>

#include "megabrain.h"

#include "debuggerdialog.h"

#include "igfxdevicedelegate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void registerGfxDelegate(IGfxDeviceDelegate* delegate) { m_gfxdelegate = delegate; }

public slots:
    void startMegabrain();
    void showDebugger();
    void updateGfx();

private:
    Ui::MainWindow *ui;

    DebuggerDialog* m_debugger;
    MegaBrain m_mb;

    IGfxDeviceDelegate* m_gfxdelegate;

    QTimer* m_gfxtimer;
    QImage m_gfxImage;
};

#endif // MAINWINDOW_H
