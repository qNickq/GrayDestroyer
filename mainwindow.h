#pragma once

#include <QFileDialog>
#include <QRandomGenerator>
#include "graycolor.h"
#include "myimage.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void doFail(unsigned short &bin , unsigned short &gray);

public slots:
    void openImg();
    void doMistake();
    void goToSource();
    void showFail(QPoint pos);

private:

    QFileDialog* dialog;
    QGraphicsView* view;
    QGraphicsScene* sceneResult;

    QGraphicsPixmapItem* pix1;
    QGraphicsPixmapItem* pix2;
    QGraphicsPixmapItem* pix3;

    QGraphicsSimpleTextItem* text1;
    QGraphicsSimpleTextItem* text2;
    QGraphicsSimpleTextItem* text3;

    QImage* img1 = nullptr;
    QImage* img2 = nullptr;
    QImage* img3 = nullptr;

    //Три изображения
    QImage* firstImg = nullptr;
    QImage* binaryImg = nullptr;
    QImage* grayImg = nullptr;

    MyImage* pix = nullptr;
    MyImage* pixBinary = nullptr;
    MyImage* pixGray = nullptr;

    //Слои интерфейса
    QHBoxLayout* generalLay;  //Главный слой. Содержит: слои v_lay1 и v_lay2.
    QHBoxLayout* hLay1;       //Слой содержит: Кнопку mistake. Cпинбоксы: mis_x, mis_y. Чекбоксы: ch_red, ch_green, ch_blue.

    QVBoxLayout* vLay1; //Слой содержит: Область отображения сцены - view. Cлой h_lay1. Кнопку source.
    QVBoxLayout* vLay2; //Слой содержит: Кнопку choose.



};
