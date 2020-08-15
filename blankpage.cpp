#include "blankpage.h"
#include "ui_blankpage.h"

BlankPage::BlankPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlankPage)
{
    ui->setupUi(this);
}

BlankPage::~BlankPage()
{
    delete ui;
}

void BlankPage::on_NextPage_clicked()
{
    this->hide();
}
