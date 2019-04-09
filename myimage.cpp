#include "myimage.h"
#include <QDebug>

MyImage::MyImage(const QPixmap &pixmap, QGraphicsItem *parent)
{
    setPixmap(pixmap);
}

void MyImage::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sendPos(event->pos().toPoint());
}
