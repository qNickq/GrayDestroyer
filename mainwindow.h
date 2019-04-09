#pragma once

#include <QFileDialog>

#include "graycolor.h"
#include "myimage.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void doFail(unsigned short bin , unsigned short gray);

public slots:
    void openImg();
    void doMistake();
    void goToSource();
    void showFail(QPoint pos);

private:

    QFileDialog* dialog;

    QGraphicsScene* scene_result;

    QGraphicsPixmapItem* pix1;
    QGraphicsPixmapItem* pix2;
    QGraphicsPixmapItem* pix3;

    QGraphicsSimpleTextItem* text1;
    QGraphicsSimpleTextItem* text2;
    QGraphicsSimpleTextItem* text3;

    QImage* img1 = nullptr;
    QImage* img2 = nullptr;
    QImage* img3 = nullptr;

    QCheckBox* ch_red;
    QCheckBox* ch_green;
    QCheckBox* ch_blue;

    //Три изображения
    QImage* firstImg = nullptr;
    QImage* binaryImg = nullptr;
    QImage* grayImg = nullptr;

    MyImage* pix = nullptr;
    MyImage* pix_binary = nullptr;
    MyImage* pix_gray = nullptr;

    //Слои интерфейса
    QHBoxLayout* general_lay;  //Главный слой. Содержит: слои v_lay1 и v_lay2.
    QHBoxLayout* h_lay1;       //Слой содержит: Кнопку mistake. Cпинбоксы: mis_x, mis_y. Чекбоксы: ch_red, ch_green, ch_blue.

    QVBoxLayout* v_lay1; //Слой содержит: Область отображения сцены - view. Cлой h_lay1. Кнопку source.
    QVBoxLayout* v_lay2; //Слой содержит: Кнопку choose.



};
