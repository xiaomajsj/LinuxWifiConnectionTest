#include "blankpage.h"
#include "ui_blankpage.h"

BlankPage::BlankPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlankPage)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("QWidget#BlankPage{border-image:url(:/image/Test.png) 0 0 0 0 stretch stretch;}");
//       QPixmap bkgnd("url(:/image/Test.png)");
//        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
//        QPalette palette;
//        palette.setBrush(QPalette::Background, bkgnd);
//        this->setPalette(palette);
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

//    QPainter painter(this);
//    int radius=23;
//    QPainterPath path;
//    QRectF rect(50,50,this->width()/2,this->height()/2);
//    path.addRoundedRect(rect, radius, radius);
//    painter.setRenderHint(QPainter::Antialiasing,true);
//    painter.setRenderHint(QPainter::SmoothPixmapTransform,true);
//    painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
//    //painter.drawRoundedRect(_keyboard->rect(),20,20);
//    painter.fillPath(path,QBrush(Qt::black));

    //boiler plate code
    QPainter painter(this);
    QStyleOption o;
    o.initFrom(this);
    style()->drawPrimitive(QStyle::PE_Widget, &o, &painter, this);



}
