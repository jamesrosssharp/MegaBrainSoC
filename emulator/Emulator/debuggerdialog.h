#pragma once

#include <QDialog>
#include <QKeyEvent>

#include "megabrain.h"

namespace Ui {
class DebuggerDialog;
}

class DebuggerDialog : public QDialog
{
    Q_OBJECT

public slots:

    void onRun();
    void onPause();
    void onStep();
    void onReset();

public:
    explicit DebuggerDialog(MegaBrain* mb, QWidget *parent = 0);
    ~DebuggerDialog();

private:

    void keyPressEvent(QKeyEvent * e);

    void updateDisassembly();

    Ui::DebuggerDialog *ui;
    MegaBrain*              m_megabrain;
};


