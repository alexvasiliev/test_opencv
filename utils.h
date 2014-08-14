#ifndef UTILS_H
#define UTILS_H

#include <QMetaType>
#include <opencv/cv.h>

typedef QSharedPointer<cv::Mat> PMat;
/*struct NewMat{
    QSharedPointer<cv::Mat> m_pMat;
    int
};*/

Q_DECLARE_METATYPE(PMat)
//qRegisterMetaType<cv::Mat>("cv::Mat");
//qRegisterMetaType<PMat>("PMat");

#endif // UTILS_H
