#include "mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
{
    Q_UNUSED(parent);

    dialog = new QFileDialog;

    auto scene = new QGraphicsScene;

    auto btnMistake = new QPushButton("Сделать ошибку");
    auto btnSource = new QPushButton("Вернуть в первичное состояние");
    auto btnChoose = new QPushButton("Выбрать изображение");

    pix = new MyImage(QPixmap(":/first.png"));
    pix->setPos(0,0);
    scene->addItem(pix);

    pixBinary = new MyImage(QPixmap(":/first.png"));
    pixBinary->setPos(pix->pixmap().width(),0);
    scene->addItem(pixBinary);

    pixGray = new MyImage(QPixmap(":/first.png"));
    pixGray->setPos(pix->pixmap().width()*2,0);
    scene->addItem(pixGray);

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

    text1 = new QGraphicsSimpleTextItem("Изначальный цвет\n");
    text2 = new QGraphicsSimpleTextItem("Цвет с ошибкой в двоичной системе");
    text3 = new QGraphicsSimpleTextItem("Цвет с ошибкой в системе Грея");

    text1->setPos(0,0);
    text2->setPos(0,80);
    text3->setPos(0,160);

    sceneResult = new QGraphicsScene;
    auto viewResult = new QGraphicsView(sceneResult);

    sceneResult->addItem(text1);
    sceneResult->addItem(text2);
    sceneResult->addItem(text3);

    sceneResult->addItem(pix1);
    sceneResult->addItem(pix2);
    sceneResult->addItem(pix3);

    connect(btnChoose, SIGNAL(clicked()), SLOT(openImg()));
    connect(btnMistake, SIGNAL(clicked()), SLOT(doMistake()));
    connect(btnSource, SIGNAL(clicked()), SLOT(goToSource()));

    connect(pix, SIGNAL(sendPos(QPoint)), SLOT(showFail(QPoint)));
    connect(pixBinary, SIGNAL(sendPos(QPoint)), SLOT(showFail(QPoint)));
    connect(pixGray, SIGNAL(sendPos(QPoint)), SLOT(showFail(QPoint)));

    view = new QGraphicsView(scene);
    view->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
    view->setRenderHints( QPainter::Antialiasing );
    view->setFixedSize(pix->pixmap().width()*3+3, pix->pixmap().height()+3);

    viewResult->setRenderHints( QPainter::Antialiasing );
    viewResult->setFixedSize(200, 300);

    auto hLay1 = new QHBoxLayout;

    hLay1->setAlignment(Qt::AlignLeft);
    hLay1->addWidget(btnMistake);
    hLay1->addWidget(btnSource);

    auto vLay1 = new QVBoxLayout;
    vLay1->addWidget(view);
    vLay1->addLayout(hLay1);

    auto vLay2 = new QVBoxLayout;
    vLay2->addWidget(viewResult);
    vLay2->addWidget(btnChoose);

    auto generalLay = new QHBoxLayout;
    generalLay->addLayout(vLay1);
    generalLay->addLayout(vLay2);

    setLayout(generalLay);
}

MainWindow::~MainWindow()
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

        pixBinary->setPixmap(QPixmap::fromImage(*binaryImg));
        pixBinary->setPos(pix->pixmap().width()+3, 0);

        pixGray->setPixmap(QPixmap::fromImage(*grayImg));
        pixGray->setPos(pix->pixmap().width()*2+6, 0);

        view->setFixedSize(pix->pixmap().width()*3+3, pix->pixmap().height()+3);
    }
}

void MainWindow::goToSource()
{
    if(firstImg != nullptr)
    {
        binaryImg = new QImage(*firstImg);
        grayImg = new QImage(*firstImg);

        pixBinary->setPixmap(QPixmap::fromImage(*firstImg));
        pixGray->setPixmap(QPixmap::fromImage(*firstImg));
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

void MainWindow::doFail(unsigned short& bin, unsigned short& gray)
{

    unsigned short _bin = bin;

    int countBin = 0;

    while(_bin)
    {
        _bin >>= 1;
        ++countBin;
    }

    if (!bin)
    {
        int i = QRandomGenerator::global()->bounded(0, 7);
        bin ^= static_cast<unsigned short>(qPow(2, i));
        gray ^= static_cast<unsigned short>(qPow(2, i));
    }
    else
    {
        int i = QRandomGenerator::global()->bounded(0, countBin);
        bin ^= static_cast<unsigned short>(qPow(2, i));
        gray ^= static_cast<unsigned short>(qPow(2, i));
    }

}

void MainWindow::doMistake()
{

    if(firstImg != nullptr)
    {
        for(int i = 0; i < firstImg->width(); ++i)
        {

            for(int j = 0; j < firstImg->height(); ++j)
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


                int temp = QRandomGenerator::global()->bounded(1, 7);

                switch (temp)
                {
                case 1 :

                    doFail(b_r, g_r);
                    break;

                case 2:
                    doFail(b_g, g_g);
                    break;

                case 3:
                    doFail(b_b, g_b);
                    break;

                case 4:
                    doFail(b_r, g_r);
                    doFail(b_g, g_g);
                    break;

                case 5:
                    doFail(b_r, g_r);
                    doFail(b_b, g_b);
                    break;

                case 6:
                    doFail(b_g, g_g);
                    doFail(b_b, g_b);
                    break;

                case 7:
                    doFail(b_r, g_r);
                    doFail(b_g, g_g);
                    doFail(b_b, g_b);
                    break;
                }

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
        pixBinary->setPixmap(QPixmap::fromImage(*binaryImg));
        pixGray->setPixmap(QPixmap::fromImage(*grayImg));
    }
}
