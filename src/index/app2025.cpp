#include "app2025.h"
#include "src/cam/cam.h"
#include "src/gallery/gallery.h"
#include <QDebug>
#include <QMessageBox>
app2025::app2025(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_app2025)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    process = new QProcess(this);
}

app2025::~app2025()
{
    delete ui;
}

void app2025::on_close_btn_clicked()
{
        // 使用 QMessageBox 实例以便设置最小尺寸（避免 QMessageBox::question 无法调整尺寸的问题）
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("退出应用"));
    msgBox.setText(tr("确定退出吗？"));
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

    if (msgBox.exec() != QMessageBox::Yes) {
        return;
    }

    QApplication::quit();
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

    if (msgBox.exec() != QMessageBox::Yes) {
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
}
