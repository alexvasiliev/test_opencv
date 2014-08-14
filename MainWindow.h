#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QSignalMapper>

#include "ptzcontrolthread.h"
#include "CVCaptureThread.h"
#include "AnalyticThread.h"

#include "opengl/GLXRenderer.h"
#include "opengl/OverlayWidget.h"
#include "opengl/QtOpenCVViewerGl.h"

class CMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit    CMainWindow(QWidget *parent = 0);
    void        Start();

signals:
    void    sendCoord(int x, int y);

public slots:
    void        onCapture(PMat img);
    void        onCapturePTZ(PMat img);
    void        onImgThresholded(PMat img);
    void        onCircle(int x, int y, int radius);

private:
    QWidget*                m_pCentralWidget;
    CQtOpenCVViewerGl*      m_pCVViewer;
    CQtOpenCVViewerGl*      m_pCVViewer2;
    COverlayWidget*         m_pGlWidget;
    CGLXRenderer*           m_pRenderThread;

    CCVCaptureThread        m_CaptureThreadNonPTZ;
    CCVCaptureThread        m_CaptureThreadPTZ;
    CAnalyticThread         m_AnalyticThread;
    CPTZControlThread       m_PTZControlThread;


    void        SetupSignalsAndSlots();
    void        CreateTrackBar();
};

#endif // MAINWINDOW_H
