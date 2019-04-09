#pragma once

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QtWidgets>

class MyImage :  public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    MyImage(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);

signals:
    void sendPos(QPoint pos);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};
