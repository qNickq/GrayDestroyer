#include "mainwindow.h"
#include <cstdlib>
#include <time.h>
MainWindow::MainWindow(QWidget *parent)
{
    Q_UNUSED(parent);

    auto scene = new QGraphicsScene;

    dialog = new QFileDialog;

    scene_result = new QGraphicsScene;
    auto view_result = new QGraphicsView(scene_result);

    auto btn_mistake = new QPushButton("Сделать ошибку");
    auto btn_source = new QPushButton("Вернуть в первичное состояние");
    auto btn_choose = new QPushButton("Выбрать изображение");

    pix = new MyImage(QPixmap(":/first.png"));
    pix->setPos(0,0);
    scene->addItem(pix);

    pix_binary = new MyImage(QPixmap(":/first.png"));
    pix_binary->setPos(pix->pixmap().width(),0);
    scene->addItem(pix_binary);

    pix_gray = new MyImage(QPixmap(":/first.png"));
    pix_gray->setPos(pix->pixmap().width()*2,0);
    scene->addItem(pix_gray);

    img1 = new QImage(64, 64, QImage::Format_RGB32);
    img2 = new QImage(64, 64, QImage::Format_RGB32);
    img3 = new QImage(64, 64, QImage::Format_RGB32);

    img1->fill(Qt::black);
    img2->fill(Qt::black);
    img3->fill(Qt::black);

    pix1 = new QGraphicsPixmapItem(QPixmap::fromImage(*img1));
    pix2 = new QGraphicsPixmapItem(QPixmap::fromImage(*img2));
    pix3 = new QGraphicsPixmapItem(QPixmap::fromImage(*img3));

    pix1->setPos(0,15);
    pix2->setPos(0, 95);
    pix3->setPos(0, 175);

    text1 = new QGraphicsSimpleTextItem("Изначальный цвет");
    text2 = new QGraphicsSimpleTextItem("Цвет с ошибкой в двоичной системе");
    text3 = new QGraphicsSimpleTextItem("Цвет с ошибкой в системе Грея");

    text1->setPos(0,0);
    text2->setPos(0,80);
    text3->setPos(0,160);

    scene_result->addItem(text1);
    scene_result->addItem(text2);
    scene_result->addItem(text3);

    scene_result->addItem(pix1);
    scene_result->addItem(pix2);
    scene_result->addItem(pix3);

    ch_red = new QCheckBox("Красный");
    ch_green = new QCheckBox("Зеленый");
    ch_blue = new QCheckBox("Синий");

    connect(btn_choose, SIGNAL(clicked()), SLOT(openImg()));
    connect(btn_mistake, SIGNAL(clicked()), SLOT(doMistake()));
    connect(btn_source, SIGNAL(clicked()), SLOT(goToSource()));

    connect(pix, SIGNAL(sendPos(QPoint)), SLOT(fail(QPoint)));
    connect(pix_binary, SIGNAL(sendPos(QPoint)), SLOT(showFail(QPoint)));
    connect(pix_gray, SIGNAL(sendPos(QPoint)), SLOT(showFail(QPoint)));

    auto view = new QGraphicsView(scene);
    view->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    //view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    view->setRenderHints( QPainter::Antialiasing );
    //view->setFixedSize(pix->pixmap().width()*3+3, pix->pixmap().height()+3);

    //view_result->setFixedSize(70,200);

    auto h_lay1 = new QHBoxLayout;
    h_lay1->setAlignment(Qt::AlignLeft);
    h_lay1->addWidget(btn_mistake);

    h_lay1->addWidget(ch_red);
    h_lay1->addWidget(ch_green);
    h_lay1->addWidget(ch_blue);
    h_lay1->addWidget(btn_source);

    auto v_lay1 = new QVBoxLayout;
    v_lay1->addWidget(view);
    v_lay1->addLayout(h_lay1);

    auto v_lay2 = new QVBoxLayout;
    v_lay2->addWidget(view_result);
    v_lay2->addWidget(btn_choose);

    auto general_lay = new QHBoxLayout;
    general_lay->addLayout(v_lay1);
    general_lay->addLayout(v_lay2);

    setLayout(general_lay);
}

MainWindow::~MainWindow()
{

}

void MainWindow::doFail(unsigned short bin, unsigned short gray)
{

}

void MainWindow::openImg()
{
    QString img = dialog->getOpenFileName(nullptr, "Выберите изображение", "D:/Projects/Qt/GrayDestroyer/img", "*.png *.jpg *.bmp");

    if(img != nullptr)
    {
        if(firstImg != nullptr) delete firstImg;
        firstImg = new QImage(img);

        if(binaryImg != nullptr) delete binaryImg;
        binaryImg = new QImage(img);

        if(grayImg != nullptr) delete grayImg;
        grayImg = new QImage(img);

        pix->setPixmap(QPixmap::fromImage(*firstImg));

        pix_binary->setPixmap(QPixmap::fromImage(*binaryImg));
        pix_binary->setPos(pix->pixmap().width(),0);

        pix_gray->setPixmap(QPixmap::fromImage(*grayImg));
        pix_gray->setPos(pix->pixmap().width()*2,0);

    }
}

void MainWindow::goToSource()
{
    if(firstImg != nullptr)
    {
        binaryImg = new QImage(*firstImg);
        grayImg = new QImage(*firstImg);
        pix_binary->setPixmap(QPixmap::fromImage(*firstImg));
        pix_gray->setPixmap(QPixmap::fromImage(*firstImg));
    }
}

void MainWindow::showFail(QPoint pos)
{

    if(firstImg != nullptr)
    {
        img1->fill(firstImg->pixelColor(pos.x(), pos.y()));
        img2->fill(binaryImg->pixelColor(pos.x(), pos.y()));
        img3->fill(grayImg->pixelColor(pos.x(), pos.y()));

        pix1->setPixmap(QPixmap::fromImage(*img1));
        pix2->setPixmap(QPixmap::fromImage(*img2));
        pix3->setPixmap(QPixmap::fromImage(*img3));
    }

}

void MainWindow::doMistake()
{
    std::srand(static_cast<unsigned int>(time(nullptr)));

    if(firstImg != nullptr)
    {
        for(int i = 0; i < firstImg->height(); ++i)
        {
            for(int j = 0; j < firstImg->width(); ++j)
            {

                QColor colorB = binaryImg->pixelColor(i, j);
                QColor colorG = grayImg->pixelColor(i, j);

                GrayColor gray(colorG);

                unsigned short g_r = gray.red();
                unsigned short g_g = gray.green();
                unsigned short g_b = gray.blue();

                unsigned short b_r = static_cast<unsigned short>(colorB.red());
                unsigned short b_g = static_cast<unsigned short>(colorB.green());
                unsigned short b_b = static_cast<unsigned short>(colorB.blue());

                /*if(ch_red->isChecked())
                {
                    b_r == 255 ? b_r = 0 : ++b_r;

                    if (convert2Bin(g_r) == 255){ gray.setRed(0);}
                    else gray.setRed(nextGray(g_r));
                }
                if(ch_green->isChecked())
                {
                    b_g == 255 ? b_g = 0 : ++b_g;

                    if (convert2Bin(g_g) == 255){ gray.setGreen(0);}
                    else gray.setGreen(nextGray(g_g));
                }
                if(ch_blue->isChecked())
                {
                    b_b == 255 ? b_b = 0 : ++b_b;

                    if (convert2Bin(g_b) == 255){ gray.setBlue(0);}
                    else gray.setBlue(nextGray(g_b));
                }

                if(!ch_red->isChecked() && !ch_green->isChecked() && !ch_blue->isChecked())
                {*/


                    std::srand(time(NULL));

                    int temp = 1 + std::rand() % 7;

                    switch (temp) {
                    case 1 :
                        /*b_r == 255 ? b_r = 0 : ++b_r;

                        if (convert2Bin(g_r) == 255){ gray.setRed(0);}
                        else gray.setRed(nextGray(g_r));
                        */

                        doFail(b_r, g_r);


                        break;

                    case 2:
                        b_g == 255 ? b_g = 0 : ++b_g;

                        if (convert2Bin(g_g) == 255){ gray.setGreen(0);}
                        else gray.setGreen(nextGray(g_g));
                        break;

                    case 3:
                        b_b == 255 ? b_b = 0 : ++b_b;

                        if (convert2Bin(g_b) == 255){ gray.setBlue(0);}
                        else gray.setBlue(nextGray(g_b));
                        break;

                    case 4:
                        b_r == 255 ? b_r = 0 : ++b_r;
                        b_g == 255 ? b_g = 0 : ++b_g;

                        if (convert2Bin(g_r) == 255){ gray.setRed(0);}
                        else gray.setRed(nextGray(g_r));
                        if (convert2Bin(g_g) == 255){ gray.setGreen(0);}
                        else gray.setGreen(nextGray(g_g));
                        break;

                    case 5:
                        b_r == 255 ? b_r = 0 : ++b_r;
                        b_b == 255 ? b_b = 0 : ++b_b;

                        if (convert2Bin(g_r) == 255){ gray.setRed(0);}
                        else gray.setRed(nextGray(g_r));

                        if (convert2Bin(g_b) == 255){ gray.setBlue(0);}
                        else gray.setBlue(nextGray(g_b));
                        break;

                    case 6:
                        b_g == 255 ? b_g = 0 : ++b_g;
                        b_b == 255 ? b_b = 0 : ++b_b;

                        if (convert2Bin(g_g) == 255){ gray.setGreen(0);}
                        else gray.setGreen(nextGray(g_g));

                        if (convert2Bin(g_b) == 255){ gray.setBlue(0);}
                        else gray.setBlue(nextGray(g_b));
                        break;

                    case 7:
                        b_r == 255 ? b_r = 0 : ++b_r;
                        b_g == 255 ? b_g = 0 : ++b_g;
                        b_b == 255 ? b_b = 0 : ++b_b;

                        if (convert2Bin(g_r) >= 253){ gray.setRed(0);}
                        else gray.setRed(nextGray(g_r));

                        if (convert2Bin(g_g) >= 253){ gray.setGreen(0);}
                        else gray.setGreen(nextGray(g_g));

                        if (convert2Bin(g_b) >= 253){ gray.setBlue(0);}
                        else gray.setBlue(nextGray(g_b));
                        break;
                    }
               // }

                colorB.setRed(b_r);
                colorB.setGreen(b_g);
                colorB.setBlue(b_b);

                colorG.setRed(convert2Bin(gray.red()));
                colorG.setGreen(convert2Bin(gray.green()));
                colorG.setBlue(convert2Bin(gray.blue()));

                binaryImg->setPixelColor(i, j, colorB);
                grayImg->setPixelColor(i, j, colorG);

            }
        }
        pix_binary->setPixmap(QPixmap::fromImage(*binaryImg));
        pix_gray->setPixmap(QPixmap::fromImage(*grayImg));
    }
}
