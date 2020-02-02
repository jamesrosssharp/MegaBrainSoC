#include "debuggerdialog.h"
#include "ui_debuggerdialog.h"

#include <iostream>

static void pauseCallback(void* theThis)
{
    reinterpret_cast<DebuggerDialog*>(theThis)->markRefresh();
}

DebuggerDialog::DebuggerDialog(MegaBrain* mb, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DebuggerDialog),
    m_megabrain(mb)
{
    ui->setupUi(this);

    m_megabrain->registerPauseCallback(pauseCallback, this);

    m_timer = new QTimer();
    m_timer->setSingleShot(false);
    m_timer->setInterval(100);

    connect(m_timer, &QTimer::timeout, this, &DebuggerDialog::runRefresh);

    m_timer->start();
}

void DebuggerDialog::runRefresh()
{
    if (m_refresh)
    {
        m_refresh = false;
        updateDisassembly();
    }
}

DebuggerDialog::~DebuggerDialog()
{
    m_timer->stop();
    delete m_timer;
    delete ui;
}

void DebuggerDialog::onRun()
{
    m_megabrain->start();
}

void DebuggerDialog::onPause()
{
    m_megabrain->pause();

    updateDisassembly();
}

void DebuggerDialog::onStep()
{
//    m_nanobrain->getCPU()->singleStep();

    m_megabrain->singleStep();

    updateDisassembly();
}

void DebuggerDialog::updateDisassembly()
{
    std::string registers = m_megabrain->dumpRegisters();

    ui->textWidget->clear();
    ui->textWidget->insertPlainText(QString(registers.c_str()));

    std::string disas = m_megabrain->dumpDisas();

    ui->disasWidget->clear();
    ui->disasWidget->insertPlainText(QString(disas.c_str()));

    // Do memory dump

    uint32_t address = static_cast<uint32_t>(strtol(ui->memAddress->text().toStdString().c_str(), nullptr, 16));

    std::string dump = m_megabrain->dumpMemory(address);

    ui->memoryWidget->clear();
    ui->memoryWidget->insertPlainText(QString(dump.c_str()));
}

void DebuggerDialog::keyPressEvent(QKeyEvent * e)
{
    switch (e->key())
    {
        case Qt::Key_S:
            onStep();
            break;
        case Qt::Key_P:
            onPause();
            break;
        case Qt::Key_R:
            onRun();
            break;
        case Qt::Key_O:
            onStepOver();
            break;
    }
}

void DebuggerDialog::onReset()
{
//    m_nanobrain->getCPU()->hardReset();
    m_megabrain->hardReset();
    updateDisassembly();
}

void DebuggerDialog::onStepOver()
{
    fflush(nullptr);
    m_megabrain->stepOver();
}
