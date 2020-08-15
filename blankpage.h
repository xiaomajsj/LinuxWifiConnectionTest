#ifndef BLANKPAGE_H
#define BLANKPAGE_H

#include <QWidget>

namespace Ui {
class BlankPage;
}

class BlankPage : public QWidget
{
    Q_OBJECT

public:
    explicit BlankPage(QWidget *parent = nullptr);
    ~BlankPage();

private slots:
    void on_NextPage_clicked();

private:
    Ui::BlankPage *ui;
};

#endif // BLANKPAGE_H
