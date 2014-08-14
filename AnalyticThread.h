#ifndef CANALYTIC_H
#define CANALYTIC_H

#include "Thread/ThreadImpl.h"
#include "utils.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace cv;

class CAnalyticThread : public CThreadImpl
{
    Q_OBJECT
public:
    CAnalyticThread();
    void                ConvertColorToHSV();
    void                ThresholdImage(const Mat& image);
    void                FindCircleBorders(const Mat& image);

public slots:
    void    analyseImage(PMat img);

signals:
    void    sendThresholdedImg(PMat img);
    void    sendCircle(int x, int y, int radius);

protected:
    void DoWork();

private:
    int                     m_nLowH;
    int                     m_nHighH;
    int                     m_nLowS ;
    int                     m_nHighS;
    int                     m_nLowV;
    int                     m_nHighV;

    Mat                     m_imgRGB;
    Mat                     m_imgHSV;
    Mat                     m_imgThresholded;

    QMutex                  m_pMutex;

    void        CreateTrackBar();
};


#endif // CANALYTIC_H
