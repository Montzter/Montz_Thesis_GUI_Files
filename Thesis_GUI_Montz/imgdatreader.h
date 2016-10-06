#ifndef IMGDATREADER_H
#define IMGDATREADER_H

#include <QObject>
#include <QString>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QFile>
#include <QTextStream>

class ImgdatReader : public QWidget
{
    Q_OBJECT
public:
    explicit ImgdatReader(QWidget *parent = 0);
    enum colormapEnum {thermal = 0,
                       fire = 1,
                       dawn = 2,
                       redblue = 3,
                       dusk = 4,
                       ice = 5,
                       kryptonite = 6,
                       seashore = 7,
                       gray = 8,
                       reds = 9,
                       golds = 10,
                       greens = 11,
                       teals = 12,
                       blues = 13,
                       purples = 14};
signals:
    void scenePressed(int pixelValue, QPointF clickPosition, int histLocation);
    void updateImg();
public slots:
    void setColormap_SLOT(int colormapIndex);
    void loadImgdat(QString &fullPathString, int colormapInt);
    //Label get functions
    QLabel* getDateLabel();
    QLabel* getImageTypeLabel();
    QLabel* getLatLabel();
    QLabel* getLonLabel();
    QLabel* getAziLabel();
    QLabel* getWidthLabel();
    QLabel* getHeightLabel();
    QLabel* getMinValLabel();
    QLabel* getMaxValLabel();
    QLabel* getAvgValLabel();
    QLabel* getBytesPerPixelLabel();
    QLabel* getBitsPerPixelLabel();
    QLabel* getOriginalDataFormatLabel();
    QLabel* getCameraPartNumLabel();
    QLabel* getCameraUsedLabel();
    QLabel* getLensUsedLabel();
    QLabel* getFovLabel();
    //QGraphicsView get functions
    QImage* getImgImage();
    QImage* getImgColorbar();
    int* getHistogram();
    void colormapInverterChanged();
    void SceneClicked(QPointF clickPos);
    void maxImgScaleChanged(int max);
    void minImgScaleChanged(int min);
    void maxImgScaleChanged(qreal max);
    void minImgScaleChanged(qreal min);
    void saveCsvFile(QString fileDirectory);

private:
    //Label set functions
    void setDateLabel(QString &dateString);
    void setImageTypeLabel(QString &imgTypeString);
    void setLatLabel(QString &latString);
    void setLonLabel(QString &lonString);
    void setAziLabel(QString &aziString);
    void setWidthLabel(QString &widthString);
    void setHeightLabel(QString &heightString); 
    void setMaxValLabel(int maxValInt);
    void setMinValLabel(int minValInt);
    void setAvgValLabel(int avgValInt);
    void setBytesPerPixelLabel(QString &bytesPerPixelString);
    void setBitsPerPixelLabel(QString &bitsPerPixelString);
    void setOriginalDataFormatLabel(QString &originalDataFormatString);
    void setCameraPartNumLabel(QString &cameraPartNumString);
    void setCameraUsedLabel(QString &cameraUsedString);
    void setLensUsedLabel(QString &LensUsedString);
    void setFovLabel(QString &fovString);
    //Image set function
    void setImgData(QString &imgDataString);
    //Colormap Set Functions
    void genDawnColortable();
    void genFireColortable();
    void genGrayColortable();
    void genIceColortable();
    void genPurplesColortable();
    void genRedsColortable();
    void genTealsColortable();
    void genBluesColortable();
    void genDuskColortable();
    void genGoldsColortable();
    void genGreensColortable();
    void genKryptoniteColortable();
    void genRedBlueColortable();
    void genSeashoreColortable();
    void genThermalColortable();
    void rescaleImageColors();
    //Colormap Items
    QVector<QRgb> *colorTable;
    int currentColormap;
    bool colormapInverted;
    bool myImgIntArrayExists;
    //Image variables
    int imgWidth;
    int imgHeight;
    int imgBytesPerPixel;
    int imgBitsPerPixel;
    int imgMax;
    int imgMin;
    int imgAvg;
    int scaleMin;
    int scaleMax;
    //Label objects
    QLabel *dateLabel;
    QLabel *imageTypeLabel;
    QLabel *latLabel;
    QLabel *lonLabel;
    QLabel *aziLabel;
    QLabel *widthLabel;
    QLabel *heightLabel;
    QLabel *maxValLabel;
    QLabel *minValLabel;
    QLabel *avgValLabel;
    QLabel *bytesPerPixelLabel;
    QLabel *bitsPerPixelLabel;
    QLabel *originalDataFormatLabel;
    QLabel *cameraPartNumLabel;
    QLabel *cameraUsedLabel;
    QLabel *lensUsedLabel;
    QLabel *fovLabel;
    //Image graphics items
    QByteArray *tmpByteArray;
    int *myImgIntArray;
    QImage *imgData;
    QImage *imgColorbar;
    //Histogram
    int histo[256];
};

#endif // IMGDATREADER_H
