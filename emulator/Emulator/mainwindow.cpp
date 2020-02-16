#include "mainwindow.h"
#include "ui_mainwindow.h"

constexpr int GFX_W = 640;
constexpr int GFX_H = 360;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_gfxdelegate(nullptr)
{
    ui->setupUi(this);
    m_debugger = new DebuggerDialog(&m_mb, this);

    m_gfxtimer = new QTimer(this);

    m_gfxtimer->setInterval(20);
    m_gfxtimer->setSingleShot(false);
    connect(m_gfxtimer, &QTimer::timeout, this, &MainWindow::updateGfx);
    m_gfxtimer->start();

    registerGfxDelegate(m_mb.getGfxCore());
}

MainWindow::~MainWindow()
{
    delete m_debugger;
    delete ui;
    delete m_gfxtimer;
}

void MainWindow::startMegabrain()
{
    m_mb.start();
}

void MainWindow::showDebugger()
{
    m_debugger->show();
}


void MainWindow::updateGfx()
{
    if (m_gfxdelegate)
    {
        uint8_t* data = static_cast<uint8_t*>(m_gfxdelegate->getImageData());
        m_gfxImage = QImage(data, GFX_W, GFX_H, QImage::Format_RGB32);
        ui->gfxscreen->setPixmap(QPixmap::fromImage(m_gfxImage));
    }
}
