#include "debuggerdialog.h"
#include "ui_debuggerdialog.h"

#include <iostream>

DebuggerDialog::DebuggerDialog(MegaBrain* mb, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DebuggerDialog),
    m_megabrain(mb)
{
    ui->setupUi(this);
}

DebuggerDialog::~DebuggerDialog()
{
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
    }
}

void DebuggerDialog::onReset()
{
//    m_nanobrain->getCPU()->hardReset();
    m_megabrain->hardReset();
    updateDisassembly();
}

