#include "imgdatreader.h"
#include <QDebug>
#include <QElapsedTimer>

ImgdatReader::ImgdatReader(QWidget *parent) : QWidget(parent)
{

    tmpByteArray = new QByteArray;
    myImgIntArrayExists = false;
    currentColormap = 0;
    colormapInverted = 0;
    colorTable = new QVector<QRgb>;
    //initColorTables();
    //genColortables();

    //Label objects
    dateLabel = new QLabel("Date: N/A",this);
    imageTypeLabel = new QLabel("Image Type: N/A",this);
    latLabel = new QLabel("Latitude: ",this);
    lonLabel = new QLabel("Longitude: ",this);
    aziLabel = new QLabel("Azimuth: ",this);
    widthLabel = new QLabel("Image Width: N/A",this);
    heightLabel = new QLabel("Image Height: N/A",this);
    maxValLabel = new QLabel("Minimum: N/A",this);
    minValLabel = new QLabel("Maximum: N/A",this);
    avgValLabel = new QLabel("Average: N/A",this);
    bytesPerPixelLabel = new QLabel("Bytes Per Pixel: N/A",this);
    bitsPerPixelLabel = new QLabel("Bits per pixel: N/A");
    originalDataFormatLabel = new QLabel("Original Data Format: N/A",this);
    cameraPartNumLabel = new QLabel("Camera Part Number: N/A",this);
    cameraUsedLabel = new QLabel("Camera Used: N/A",this);
    lensUsedLabel = new QLabel("Lens Used: N/A",this);
    fovLabel = new QLabel("Field of View: N/A",this);

    //ImageData
    imgData = new QImage;
    imgColorbar = new QImage;
    *imgData = QImage(imgWidth,imgHeight,QImage::Format_Indexed8);
    *imgColorbar = QImage(14,260,QImage::Format_Indexed8);

    genGrayColortable();

    imgData->fill(0x00);
    imgColorbar->fill(QColor(0,0,0));
    imgData->setColorTable(*colorTable);
    imgColorbar->setColorTable(*colorTable);


    //Make empty histogram
    for(int k = 0; k<256; k++) histo[k] = 1;

}

//Load image data file
void ImgdatReader::loadImgdat(QString &fullPathString, int colormapInt)
{

    QString dateString,imageTypeString,latString,lonString,aziString,widthString,heightString,
            bytesPerPixelString,bitsPerPixelString,originalDataFormatString,cameraPartNumberString,cameraUsedString,lensUsedString,fovString,imageString;

    QFile mFile(fullPathString);
    if(!mFile.open(QFile::ReadOnly | QFile::Text))
    {
        qDebug() << "oops";
        return;
    }

    QTextStream textStream(&mFile);
    if(textStream.atEnd())
    {mFile.close();return;}
    dateString = textStream.readLine(0);
    if(textStream.atEnd())
    {mFile.close();return;}
    imageTypeString = textStream.readLine(0);
    if(textStream.atEnd())
    {mFile.close();return;}
    latString = textStream.readLine(0);
    if(textStream.atEnd())
    {mFile.close();return;}
    lonString = textStream.readLine(0);
    if(textStream.atEnd())
    {mFile.close();return;}
    aziString = textStream.readLine(0);
    if(textStream.atEnd())
    {mFile.close();return;}
    widthString = textStream.readLine(0);
    if(textStream.atEnd())
    {mFile.close();return;}
    heightString = textStream.readLine(0);
    if(textStream.atEnd())
    {mFile.close();return;}
    bytesPerPixelString = textStream.readLine(0);
    if(textStream.atEnd())
    {mFile.close();return;}
    bitsPerPixelString = textStream.readLine(0);
    if(textStream.atEnd())
    {mFile.close();return;}
    originalDataFormatString = textStream.readLine(0);
    if(textStream.atEnd())
    {mFile.close();return;}
    cameraPartNumberString = textStream.readLine(0);
    if(textStream.atEnd())
    {mFile.close();return;}
    cameraUsedString = textStream.readLine(0);
    if(textStream.atEnd())
    {mFile.close();return;}
    lensUsedString = textStream.readLine(0);
    if(textStream.atEnd())
    {mFile.close();return;}
    fovString = textStream.readLine(0);
    if(textStream.atEnd())
    {mFile.close();return;}

    imageString = textStream.readAll();

    mFile.close();

    setDateLabel(dateString);
    setImageTypeLabel(imageTypeString);
    setLatLabel(latString);
    setLonLabel(lonString);
    setAziLabel(aziString);
    setWidthLabel(widthString);
    setHeightLabel(heightString);
    setBytesPerPixelLabel(bytesPerPixelString);
    setBitsPerPixelLabel(bitsPerPixelString);
    setOriginalDataFormatLabel(originalDataFormatString);
    setCameraPartNumLabel(cameraPartNumberString);
    setCameraUsedLabel(cameraUsedString);
    setLensUsedLabel(lensUsedString);
    setFovLabel(fovString);

    currentColormap = colormapInt;

    setImgData(imageString);

}

//Label set functions
void ImgdatReader::setDateLabel(QString &dateString)
{
    QString tmpDate = dateString.left(10);
    QString tmpTime = dateString.right(8).replace('-',':');
    QString tmpCombo;
    tmpCombo = "Date: " + tmpDate.mid(5,2) + '/' + tmpDate.right(2) + '/' + tmpDate.left(4) + " Time: " + tmpTime;
    dateLabel->setText(tmpCombo);
}

void ImgdatReader::setImageTypeLabel(QString &imgTypeString)
{
    bool OK;
    int tmpInt = imgTypeString.toInt(&OK, 10);
    if(!OK)
        return;

    QString tmp("Image Type: ");

    switch(tmpInt)
    {
        case 0: tmp.append("Empty Image"); break;
        case 1: tmp.append("Original Image, Band 4"); break;
        case 2: tmp.append("Original Image, Band 5"); break;
        case 3: tmp.append("Rotated & Translated Image, Band 5"); break;
        case 4: tmp.append("Wen and Rose Algorith Output"); break;
        default: break;
    }
    imageTypeLabel->setText(tmp);
}

void ImgdatReader::setLatLabel(QString &latString)
{
    bool OK;
    QString tmp = "Latitude: " + QString::number(latString.toDouble(&OK),'f',3);
    if(!OK)
        return;

    latLabel->setText(tmp);
}

void ImgdatReader::setLonLabel(QString &lonString)
{
    bool OK;
    QString tmp = "Longitude: " + QString::number(lonString.toDouble(&OK),'f',3);

    if(!OK)
        return;
    lonLabel->setText(tmp);
}

void ImgdatReader::setAziLabel(QString &aziString)
{
    bool OK;
    QString tmp = "Azimuth : " + QString::number(aziString.toDouble(&OK),'f',3);

    if(!OK)
        return;
    aziLabel->setText(tmp);
}

void ImgdatReader::setWidthLabel(QString &widthString)
{
    QString tmp = "Image Width: " + widthString + "px";
    widthLabel->setText(tmp);
    bool OK;
    imgWidth = widthString.toInt(&OK,10);
}

void ImgdatReader::setHeightLabel(QString &heightString)
{
    QString tmp = "Image Height: " + heightString + "px";
    heightLabel->setText(tmp);
    bool OK;
    imgHeight = heightString.toInt(&OK,10);
}

void ImgdatReader::setMaxValLabel(int maxValInt)
{
    QString tmp;
    tmp = "Max Pixel Value: " + QString::number(maxValInt,10);
    maxValLabel->setText(tmp);
}

void ImgdatReader::setMinValLabel(int minValInt)
{
    QString tmp;
    tmp = "Min Pixel Value: " + QString::number(minValInt,10);
    minValLabel->setText(tmp);
}

void ImgdatReader::setAvgValLabel(int avgValInt)
{
    QString tmp;
    tmp = "Avg Pixel Value: " + QString::number(avgValInt,10);
    avgValLabel->setText(tmp);
}

void ImgdatReader::setBytesPerPixelLabel(QString &bytesPerPixelString)
{
    QString tmp = "Bytes Per Pixel: " + bytesPerPixelString + " Bytes";
    bytesPerPixelLabel->setText(tmp);
    bool OK;
    imgBytesPerPixel = bytesPerPixelString.toInt(&OK,10);
}

void ImgdatReader::setBitsPerPixelLabel(QString &bitsPerPixelString)
{
    QString tmp = "Bits Per Pixel: " + bitsPerPixelString + " Bits";
    bitsPerPixelLabel->setText(tmp);
    bool OK;
    imgBitsPerPixel = bitsPerPixelString.toInt(&OK,10);
}

void ImgdatReader::setOriginalDataFormatLabel(QString &originalDataFormatString)
{
    QString tmp = "Original Data Format: " + originalDataFormatString;
    originalDataFormatLabel->setText(tmp);
}

void ImgdatReader::setCameraPartNumLabel(QString &cameraPartNumString)
{
    QString tmp = "Camera Part Number: " + cameraPartNumString;
    cameraPartNumLabel->setText(tmp);
}

void ImgdatReader::setCameraUsedLabel(QString &cameraUsedString)
{
    QString tmp = "Camera Used: " + cameraUsedString;
    cameraUsedLabel->setText(tmp);
}

void ImgdatReader::setLensUsedLabel(QString &LensUsedString)
{
    QString tmp = "Lens Used: " + LensUsedString;
    lensUsedLabel->setText(tmp);
}

void ImgdatReader::setFovLabel(QString &fovString)
{
    QString tmp = "Field of View: " + fovString;
    fovLabel->setText(tmp);
}

//Label get functions
QLabel* ImgdatReader::getDateLabel()
{
    return dateLabel;
}

QLabel*  ImgdatReader::getImageTypeLabel()
{
    return imageTypeLabel;
}

QLabel*  ImgdatReader::getLatLabel()
{
    return latLabel;
}

QLabel*  ImgdatReader::getLonLabel()
{
    return lonLabel;
}

QLabel*  ImgdatReader::getAziLabel()
{
    return aziLabel;
}

QLabel*  ImgdatReader::getWidthLabel()
{
    return widthLabel;
}

QLabel*  ImgdatReader::getHeightLabel()
{
    return heightLabel;
}

QLabel* ImgdatReader::getMinValLabel()
{
    return minValLabel;
}

QLabel* ImgdatReader::getMaxValLabel()
{
    return maxValLabel;
}

QLabel* ImgdatReader::getAvgValLabel()
{
    return avgValLabel;
}

QLabel*  ImgdatReader::getBytesPerPixelLabel()
{
    return bytesPerPixelLabel;
}

QLabel* ImgdatReader::getBitsPerPixelLabel()
{
    return bitsPerPixelLabel;
}

QLabel*  ImgdatReader::getOriginalDataFormatLabel()
{
    return originalDataFormatLabel;
}

QLabel*  ImgdatReader::getCameraPartNumLabel()
{
    return cameraPartNumLabel;
}

QLabel* ImgdatReader::getCameraUsedLabel()
{
    return cameraUsedLabel;
}

QLabel*  ImgdatReader::getLensUsedLabel()
{
    return lensUsedLabel;
}

QLabel*  ImgdatReader::getFovLabel()
{
    return fovLabel;
}

//Set imagedata
void ImgdatReader::setImgData(QString &imgDataString)
{
    QString tmpnewline = imgDataString.simplified().replace(" ","");

    *tmpByteArray = tmpnewline.toLocal8Bit();

    if(myImgIntArrayExists)
        delete[] myImgIntArray;

    int arraySize = imgWidth*imgHeight;
    myImgIntArray = new int[arraySize];
    myImgIntArrayExists = true;



    *imgData = QImage(imgWidth,imgHeight,QImage::Format_Indexed8);
    *imgColorbar = QImage(14,260,QImage::Format_Indexed8);

    imgData->fill(0x00);
    imgColorbar->fill(QColor(0,0,0));

    switch(currentColormap)
    {
    case thermal:   genThermalColortable();break;
    case fire:      genFireColortable();break;
    case dawn:      genDawnColortable();break;
    case redblue:   genRedBlueColortable();break;
    case dusk:      genDuskColortable();break;
    case ice:       genIceColortable();break;
    case kryptonite:genKryptoniteColortable();break;
    case seashore:  genSeashoreColortable();break;
    case gray:      genGrayColortable();break;
    case reds:      genRedsColortable();break;
    case golds:     genGoldsColortable();break;
    case greens:    genGreensColortable();break;
    case teals:     genTealsColortable();break;
    case blues:     genBluesColortable();break;
    case purples:   genPurplesColortable();break;
    default: return;
    }

    imgData->setColorTable(*colorTable);
    imgColorbar->setColorTable(*colorTable);

    for(int i = 2; i<12; i++)
    {
        for(int j = 2; j<258;j++)
        {
            imgColorbar->setPixel(i,j,257-j);
        }
    }

    //Loop about 4 times faster than QByteArray::mid().toInt();
    //***
    char tmp1, tmp2;
    int byteValue;
    int segmentLength = imgBytesPerPixel*2;
    int maxKeeper = 0;
    int minKeeper = 37707;
    unsigned long long sumKeeper = 0;
    double avgKeeper = 0.0;

    //For each pixel
    for(int i=0;i<arraySize;i++)
    {
        //for each byte
        myImgIntArray[i] = 0;
        for(int j = 0; j<imgBytesPerPixel;j++)
        {
            //load each byte, load into integer
            byteValue = 0;
            int j2 = 2*j;
            int backJ = (imgBytesPerPixel - 1 - j);

            tmp1 = tmpByteArray->at(i*segmentLength+j2);
            tmp2 = tmpByteArray->at(i*segmentLength+j2+1);


            switch((int)tmp1)
            {
                case 48: byteValue = 0x00; break;//'0'
                case 49: byteValue = 0x10; break;//'1'
                case 50: byteValue = 0x20; break;//'2'
                case 51: byteValue = 0x30; break;//'3'
                case 52: byteValue = 0x40; break;//'4'
                case 53: byteValue = 0x50; break;//'5'
                case 54: byteValue = 0x60; break;//'6'
                case 55: byteValue = 0x70; break;//'7'
                case 56: byteValue = 0x80; break;//'8'
                case 57: byteValue = 0x90; break;//'9'
                case 65: byteValue = 0xA0; break;//'A'
                case 66: byteValue = 0xB0; break;//'B'
                case 67: byteValue = 0xC0; break;//'C'
                case 68: byteValue = 0xD0; break;//'D'
                case 69: byteValue = 0xE0; break;//'E'
                case 70: byteValue = 0xF0; break;//'F'
                case 97: byteValue = 0xA0; break;//'a'
                case 98: byteValue = 0xB0; break;//'b'
                case 99: byteValue = 0xC0; break;//'c'
                case 100: byteValue = 0xD0; break;//'d'
                case 101: byteValue = 0xE0; break;//'e'
                case 102: byteValue = 0xF0; break;//'f'
                default: break;
            }

            switch((int)tmp2)
            {
                case 48: byteValue = byteValue + 0x00; break;//'0'
                case 49: byteValue = byteValue + 0x01; break;//'1'
                case 50: byteValue = byteValue + 0x02; break;//'2'
                case 51: byteValue = byteValue + 0x03; break;//'3'
                case 52: byteValue = byteValue + 0x04; break;//'4'
                case 53: byteValue = byteValue + 0x05; break;//'5'
                case 54: byteValue = byteValue + 0x06; break;//'6'
                case 55: byteValue = byteValue + 0x07; break;//'7'
                case 56: byteValue = byteValue + 0x08; break;//'8'
                case 57: byteValue = byteValue + 0x09; break;//'9'
                case 65: byteValue = byteValue + 0x0A; break;//'A'
                case 66: byteValue = byteValue + 0x0B; break;//'B'
                case 67: byteValue = byteValue + 0x0C; break;//'C'
                case 68: byteValue = byteValue + 0x0D; break;//'D'
                case 69: byteValue = byteValue + 0x0E; break;//'E'
                case 70: byteValue = byteValue + 0x0F; break;//'F'
                case 97: byteValue = byteValue + 0x0A; break;//'a'
                case 98: byteValue = byteValue + 0x0B; break;//'b'
                case 99: byteValue = byteValue + 0x0C; break;//'c'
                case 100: byteValue = byteValue + 0x0D; break;//'d'
                case 101: byteValue = byteValue + 0x0E; break;//'e'
                case 102: byteValue = byteValue + 0x0F; break;//'f'
                default: break;
            }
            myImgIntArray[i] += byteValue << (8*backJ);
        }
    imgData->setPixel(i%640,i/640,(myImgIntArray[i] & 0x3FFF)>> (imgBitsPerPixel - 8));

    sumKeeper += myImgIntArray[i];
    if(myImgIntArray[i] > maxKeeper)
        maxKeeper = myImgIntArray[i];
    if(myImgIntArray[i] < minKeeper)
        minKeeper = myImgIntArray[i];

    }
    avgKeeper = (double)sumKeeper/((double)imgHeight*(double)imgWidth);

    imgMax = maxKeeper;
    scaleMax = 255;
    imgMin = minKeeper;
    scaleMin = 0;
    imgAvg = avgKeeper;

    setMaxValLabel(imgMax);
    setMinValLabel(imgMin);
    setAvgValLabel(imgAvg);


    //Calculate histogram
    for(int k = 0; k<256; k++) histo[k] = 0;
    double histoBucketWidth = (imgMax - imgMin)/255;
    for(int i = 0; i<arraySize; i++)
    {
        histo[(int)(((double)myImgIntArray[i] - (double)imgMin)/histoBucketWidth)]++;
    }

    return;
}

//Get QGraphicsView functions
QImage* ImgdatReader::getImgImage()
{
    return imgData;
}

QImage* ImgdatReader::getImgColorbar()
{
    return imgColorbar;
}

int* ImgdatReader::getHistogram()
{
    return histo;
}

//set colormap
void ImgdatReader::setColormap_SLOT(int colormapIndex)
{
    currentColormap = colormapIndex;

    switch(colormapIndex)
    {
        case thermal:   genThermalColortable();break;
        case fire:      genFireColortable();break;
        case dawn:      genDawnColortable();break;
        case redblue:   genRedBlueColortable();break;
        case dusk:      genDuskColortable();break;
        case ice:       genIceColortable();break;
        case kryptonite:genKryptoniteColortable();break;
        case seashore:  genSeashoreColortable();break;
        case gray:      genGrayColortable();break;
        case reds:      genRedsColortable();break;
        case golds:     genGoldsColortable();break;
        case greens:    genGreensColortable();break;
        case teals:     genTealsColortable();break;
        case blues:     genBluesColortable();break;
        case purples:   genPurplesColortable();break;
        default: return;
    }
    imgData->setColorTable(*colorTable);
    imgColorbar->setColorTable(*colorTable);
}

void ImgdatReader::colormapInverterChanged()
{
    colormapInverted = !colormapInverted;
    setColormap_SLOT(currentColormap);
}

void ImgdatReader::SceneClicked(QPointF clickPos)
{
    bool OK;

    if(tmpByteArray->isNull() | tmpByteArray->isEmpty())
        return;
    int pixValue = tmpByteArray->mid(((int)clickPos.y()*640 + (int)clickPos.x())*4,4).toInt(&OK,16);

    int histPos = (int)((double)(pixValue-imgMin) /((double)(imgMax-imgMin)/255.0));


    emit scenePressed(pixValue,clickPos,histPos);
}

void ImgdatReader::maxImgScaleChanged(int max)
{
    if((max <0) | (max > 255))
        return;
    scaleMax = max;
    rescaleImageColors();
}

void ImgdatReader::minImgScaleChanged(int min)
{
    if((min <0) | (min > 255))
        return;
    scaleMin = min;
    rescaleImageColors();
}

void ImgdatReader::maxImgScaleChanged(qreal max)
{
    if(((int)max <0) | ((int)max > 255))
        return;

    scaleMax = (int)max;
    rescaleImageColors();
}

void ImgdatReader::minImgScaleChanged(qreal min)
{
    if(((int)min <0) | ((int)min > 255))
        return;

    scaleMin = (int)min;
    rescaleImageColors();
}

void ImgdatReader::rescaleImageColors()
{
//    double multiplier = ((double)scaleMax - (double)scaleMin)/255.0;
//    int tmpInt = 0;

//    for(int i = 0; i<(imgData->width() * imgData->height());i++)
//    {
//        tmpInt = (myImgIntArray[i] & 0x3FFF)>> 6;
//        if(tmpInt < scaleMin)
//            imgData->setPixel(i%640,i/640,0);
//        else if(tmpInt > scaleMax)
//            imgData->setPixel(i%640,i/640,255);
//        else
//            imgData->setPixel(i%640,i/640,(tmpInt-scaleMin)/multiplier);
//    }



    if(scaleMin >=scaleMax)
        return;

    double scaleIncrement,multiplier;
    int minV,maxV,newV;

    scaleIncrement = ((double)imgMax - (double)imgMin)/255.0;
    minV = scaleMin*scaleIncrement;
    maxV = scaleMax*scaleIncrement;
    multiplier = ((double)maxV - (double)minV)/255.0;

    for(int i = 0; i< (imgData->width() * imgData->height());i++)
    {
        newV = (double)(myImgIntArray[i] - minV)/multiplier;
        if(myImgIntArray[i] < minV)
            imgData->setPixel(i%640,i/640,0);
        else if(myImgIntArray[i] > maxV)
            imgData->setPixel(i%640,i/640,255);
        else
            imgData->setPixel(i%640,i/640,newV);
    }

    int colorbarVal;
    double cbmultiplier = (double)(scaleMax - scaleMin)/255.0;
    for(int i = 2; i<12; i++)
    {
        for(int j = 2; j<258;j++)
        {
            colorbarVal = 257-j;
            if(colorbarVal > scaleMax)
                imgColorbar->setPixel(i,j,255);
            else if(colorbarVal < scaleMin)
                imgColorbar->setPixel(i,j,0);
            else
                imgColorbar->setPixel(i,j,(double)(colorbarVal-scaleMin)/cbmultiplier);
        }
    }

    emit updateImg();
}

void ImgdatReader::saveCsvFile(QString fileDirectory)
{
    QString tmp;
    QFile file(fileDirectory);
    QTextStream fileOut(&file);
    file.open(QIODevice::WriteOnly);
    for(int i = 0; i < imgHeight; i++)
    {
        tmp.clear();
        for(int j = 0; j < imgWidth;j++)
        {
            tmp.append(QString::number(myImgIntArray[i*640 + j],10));
            tmp.append(",");
        }
        tmp.chop(1);
        //tmp.remove(i*640 + imgWidth - 2,1);
        tmp.append("\r\n");
        fileOut << tmp;
    }
    file.close();
}
