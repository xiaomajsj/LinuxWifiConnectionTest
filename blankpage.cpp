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
void BlankPage::paintEvent(QPaintEvent *e)
{

    QPainter painter(this);
    int radius=23;
    QPainterPath path;
    QRectF rect(50,50,this->width()/2,this->height()/2);
    path.addRoundedRect(rect, radius, radius);
    painter.setRenderHint(QPainter::Antialiasing,true);
    painter.setRenderHint(QPainter::SmoothPixmapTransform,true);
    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    //painter.drawRoundedRect(_keyboard->rect(),20,20);
    painter.fillPath(path,QBrush(Qt::white));
}
