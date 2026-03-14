#ifndef USAGE_H
#define USAGE_H

#include <QWidget>

namespace Ui {
class usage;
}

class usage : public QWidget
{
    Q_OBJECT

public:
    explicit usage(QWidget *parent = nullptr);
    ~usage();

private slots:
    void on_backBtn_clicked();

private:
    Ui::usage *ui;
};

#endif // USAGE_H
