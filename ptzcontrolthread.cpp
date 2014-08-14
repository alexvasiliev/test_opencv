#include "ptzcontrolthread.h"
#include "qmath.h"
#define     xconst              16
#define     yconst              136
#define     zconst              50
#define     camNonPTZViewAngleX 91
#define     camNonPTZViewAngleY 60
#define     camPTZViewAngleX    58
#define     camPTZViewAngleY    35
#define     sizeOfBall          4


CPTZControlThread::CPTZControlThread()
    :   m_nCurP(75)
    ,   m_nCurT(70)
    ,   m_nCurZ(0)
    ,   m_sAdress("http://root:pass@192.230.1.109//nvc-cgi/ptz/ptz2.fcgi?ptzid=1&apantiltzoommove=")
{
    nam = new QNetworkAccessManager(this);
    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(getReply(QNetworkReply*)));
    setPosition();
}



void    CPTZControlThread::setPosition()
{
    QString addAdress = QString("=" + QString::number(m_nCurP) + "," + QString::number(m_nCurT) + "," + QString::number(m_nCurZ));
    QUrl url(m_sAdress + addAdress);
    qDebug() << m_sAdress + addAdress;
    nam->get(QNetworkRequest(url));
}

void    CPTZControlThread::getCoordinates(int x, int y, int r)
{
    calculateNewCoord(x, y, r);
}

void    CPTZControlThread::getReply(QNetworkReply* reply)
{
    qDebug() << reply->readLine();
}

void    CPTZControlThread::calculateNewCoord(int x, int y, int r)
{
    double alpha1 = camNonPTZViewAngleX / 2 * (abs(220 - x)) / 220;
    double alpha2 = camNonPTZViewAngleY / 2 * (abs(165 - y)) / 165;
    double xK1 = 220 * qTan(alpha1 * M_PI / 180);
    double zK1 = 165 * qTan(alpha2 * M_PI / 180);
    qreal xTemp = (x * qTan(alpha1 * M_PI / 180) - xK1 + xconst);
    qreal zTemp = 330 - (y * qTan(alpha2 * M_PI / 180) -  zK1 + yconst) ;
    double alpha3 = alpha1 * (abs(x - r)) / x;
    double alpha4 = 2 * (alpha1 - alpha3);
    double yK1 = sizeOfBall / qTan(alpha4 * M_PI / 180);
    qreal yTemp = yconst - yK1;
    //qDebug() << xTemp << yTemp;
    qreal nCurT = qFloor (185 - abs((qAtan (qreal(yTemp/xTemp)) * 180 / M_PI)));
    qreal nCurP = qFloor (290 - (qAtan (qSqrt((xTemp * xTemp + yTemp * yTemp) / zTemp)) * 180 / M_PI));
    qDebug() << nCurP << nCurT;
    if(abs(m_nCurP - nCurP) > 5 || abs(m_nCurT - nCurT) > 5)
    {
        m_nCurP = nCurP;
        m_nCurT = nCurT;
        setPosition();
    }
}



