#ifndef PTZCONTROLTHREAD_H
#define PTZCONTROLTHREAD_H

//#include "Thread/ThreadImpl.h"
#include <QtNetwork>


class CPTZControlThread : public QObject
{
    Q_OBJECT
public:
    CPTZControlThread();
public slots:
    void    getCoordinates(int x, int y, int r);
    void    getReply(QNetworkReply* pReply);

private:
    void    calculateNewCoord(int x, int y, int r);
    void    sendCoord();
    void    setPosition();

    QNetworkAccessManager*      nam;
    qreal                       m_nCurP;
    qreal                       m_nCurT;
    qreal                       m_nCurZ;
    QString                     m_sAdress;
};

#endif // PTZCONTROLTHREAD_H
