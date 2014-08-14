#ifndef CMANAGER_H
#define CMANAGER_H

#include <opencv/highgui.h>
#include <QObject>
#include "canalytic.h"
#include <opencv2/opencv.hpp>
#include "opengl/QtOpenCVViewerGl.h"

class CManager : public QObject
{
    Q_OBJECT
public:
    CManager(bool bAnalytic, bool bPTZControl);

    void                    CreateNonPtzThread();
    void                    CreateGUI();
    void                    TurnAnaytic(bool on_or_off);

private:
    //PCamNonPtzThread        m_pCamNonPtzThread;
    PAnalytic               m_pAnalytic;
    CQtOpenCVViewerGl*      m_pViewer;

    bool                    m_bAnalytics;
    bool                    m_bPTZControl;

    int                     m_nLowH;
    int                     m_nHighH;
    int                     m_nLowS ;
    int                     m_nHighS;
    int                     m_nLowV;
    int                     m_nHighV;




public slots:
    void                    handleNonPTZFrame(cv::Mat img);
};

typedef QSharedPointer <CManager> PManager;


#endif // CMANAGER_H
