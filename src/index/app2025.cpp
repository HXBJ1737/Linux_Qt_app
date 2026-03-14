#include <QDebug>
#include <QMessageBox>
#include <QFileInfo>
#include <QDebug>
#include <QDir>
#include "app2025.h"
#include "src/cam/cam.h"
#include "src/gallery/gallery.h"
#include "src/yoloapp/yolo_app.h"
#include "src/test/test.h"
#include "src/distance/distance.h"
#include <QMouseEvent>
#include <QFile>
#include <QScreen>
#include <QApplication>
#include <QTimer>
#include <QDateTime>

// #ifdef __aarch64__
// extern "C"
// {
//     void touch_init();
//     void touch_simulate(int x, int y);
//     void touch_cleanup();
// }
// #endif

app2025::app2025(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_app2025)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    process = new QProcess(this);
// #ifdef __aarch64__
//     touch_init();
// #endif
    QByteArray ba = qgetenv("PROJECT_ROOT");
    QString projectRoot = ba.isEmpty() ? QString() : QString::fromUtf8(ba);

    // 初始化时间标签
    ui->time_label->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &app2025::updateTimeLabel);
    timer->start(1000);
}

app2025::~app2025()
{
// #ifdef __aarch64__
//     touch_cleanup();
// #endif
    delete ui;
}

void app2025::on_close_btn_clicked()
{

    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("退出应用"));
    msgBox.setText(tr("确定退出吗？"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    msgBox.setStyleSheet(R"(
    QMessageBox {
        font-size: 16pt;
    }
    QPushButton {
        font-size: 16pt;
        min-width: 120px;
        min-height: 50px;
    }
)");

    if (msgBox.exec() != QMessageBox::Yes)
    {
        return;
    }
#ifdef __aarch64__
    QMessageBox::warning(this, tr("退出失败"), tr("底层界面，不允许退出！！！"));
#else
    QApplication::quit();
#endif
}

void app2025::on_app1_btn_clicked()
{
    cam *c = new cam;
    c->show();
}

void app2025::on_app2_btn_clicked()
{
    gallery *g = new gallery;
    g->show();
}

void app2025::on_app3_btn_clicked()
{

#ifdef __aarch64__
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("启动应用"));
    msgBox.setText(tr("确定启动 QDesktop 吗？"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    // 使用样式表进一步放大按钮和最小尺寸
    msgBox.setStyleSheet(R"(
    QMessageBox {
        font-size: 16pt;
    }
    QPushButton {
        font-size: 16pt;
        min-width: 120px;
        min-height: 50px;
    }
    )");

    if (msgBox.exec() != QMessageBox::Yes)
    {
        return;
    }

    // 禁用其它按钮，防止重复点击
    ui->app1_btn->setEnabled(false);
    ui->app2_btn->setEnabled(false);
    ui->close_btn->setEnabled(false);
    ui->app3_btn->setEnabled(false);

    // 结束或出错时恢复按钮（使用 Qt::UniqueConnection 避免重复连接）
    connect(process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), this, [this](int, QProcess::ExitStatus)
            {
                ui->app1_btn->setEnabled(true);
                ui->app2_btn->setEnabled(true);
                ui->close_btn->setEnabled(true);
                ui->app3_btn->setEnabled(true); }, Qt::UniqueConnection);

    connect(process, &QProcess::errorOccurred, this, [this](QProcess::ProcessError)
            {
                ui->app1_btn->setEnabled(true);
                ui->app2_btn->setEnabled(true);
                ui->close_btn->setEnabled(true);
                ui->app3_btn->setEnabled(true);
                QMessageBox::warning(this, tr("启动失败"), tr("无法启动 QDesktop")); }, Qt::UniqueConnection);

    process->start("/hxbj/QDesktop");

    // 若需要立即检查启动是否成功，可以短暂等待（可去掉以避免阻塞）
    if (!process->waitForStarted(1000))
    {
        ui->app1_btn->setEnabled(true);
        ui->app2_btn->setEnabled(true);
        ui->close_btn->setEnabled(true);
        ui->app3_btn->setEnabled(true);
        QMessageBox::warning(this, tr("启动失败"), tr("无法启动 QDesktop"));
    }
#else
    QMessageBox::warning(this, tr("启动失败"), tr("此应用仅可在__aarch64__上运行"));
#endif
}

void app2025::on_app4_btn_clicked()
{
#ifdef __aarch64__
    yolo_app *y = new yolo_app;
    y->show();
#else
    QMessageBox::warning(this, tr("启动失败"), tr("此应用仅可在__aarch64__上运行"));
#endif
}

void app2025::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = true;
        m_dragPosition = event->globalPos() - this->frameGeometry().topLeft();
        event->accept();
    }
}

void app2025::mouseMoveEvent(QMouseEvent *event)
{
    if (m_dragging && (event->buttons() & Qt::LeftButton))
    {
        move(event->globalPos() - m_dragPosition);
        event->accept();
    }
}

void app2025::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragging = false;
        event->accept();
    }
}

void app2025::updateTimeLabel()
{
    ui->time_label->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
}

void app2025::on_poweroff_pushButton_clicked()
{
#ifdef __aarch64__
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("关闭电源"));
    msgBox.setText(tr("确定关机吗？"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    msgBox.setStyleSheet(R"(
    QMessageBox {
        font-size: 16pt;
    }
    QPushButton {
        font-size: 16pt;
        min-width: 120px;
        min-height: 50px;
    }
)");

    if (msgBox.exec() != QMessageBox::Yes)
    {
        return;
    }
    QApplication::quit();
    process->start("poweroff");
#else
    QMessageBox::warning(this, tr("启动失败"), tr("此应用仅可在__aarch64__上运行"));
#endif
}

void app2025::on_reboot_pushButton_clicked()
{
#ifdef __aarch64__
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("重新启动"));
    msgBox.setText(tr("确定重启吗？"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);

    msgBox.setStyleSheet(R"(
    QMessageBox {
        font-size: 16pt;
    }
    QPushButton {
        font-size: 16pt;
        min-width: 120px;
        min-height: 50px;
    }
)");

    if (msgBox.exec() != QMessageBox::Yes)
    {
        return;
    }
    QApplication::quit();
    process->start("reboot");
#else
    QMessageBox::warning(this, tr("启动失败"), tr("此应用仅可在__aarch64__上运行"));
#endif
}

void app2025::on_test_pushButton_clicked()
{
    test *t = new test;
    t->show();
}

void app2025::on_pushButton_clicked()
{
#ifdef __aarch64__
    distance *d = new distance;
    d->show();
#else
    QMessageBox::warning(this, tr("启动失败"), tr("此应用仅可在__aarch64__上运行"));
#endif
}
