#include "MainWindow.h"

#include <opencv2/highgui/highgui.hpp>
#include <QGridLayout>

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_pCentralWidget = new QWidget;
    setCentralWidget(m_pCentralWidget);

//    m_pCVViewer = new CQtOpenCVViewerGl();
//    m_pCVViewer2 = new CQtOpenCVViewerGl();
//    m_pGlWidget = new COverlayWidget(this);
//    m_pRenderThread = new CGLXRenderer(*m_pGlWidget);
//    m_pRenderThread->SetGeometry(800, 600);
//    QGridLayout *pCentralLayout = new QGridLayout;
//    pCentralLayout->addWidget(m_pCVViewer, 0, 0);
//    pCentralLayout->addWidget(m_pCVViewer2, 0, 1);

    //m_pCentralWidget->setLayout(pCentralLayout);

    setWindowTitle(tr("OpenCV magic"));
    //resize(400, 300);
    SetupSignalsAndSlots();
}

void CMainWindow::SetupSignalsAndSlots()
{
    qRegisterMetaType<PMat>("PMat");

    connect(&m_CaptureThreadNonPTZ, SIGNAL(resultReady(PMat)), this, SLOT(onCapture(PMat)));
    connect(&m_CaptureThreadNonPTZ, SIGNAL(resultReady(PMat)), &m_AnalyticThread, SLOT(analyseImage(PMat)));

    connect(&m_CaptureThreadPTZ, SIGNAL(resultReady(PMat)), this, SLOT(onCapturePTZ(PMat)));
    //connect(&m_CaptureThreadPTZ, SIGNAL(resultReady(PMat)), &m_AnalyticThread, SLOT(analyseImage(PMat)));

    connect(&m_AnalyticThread, SIGNAL(sendThresholdedImg(PMat)), this, SLOT(onImgThresholded(PMat)));
    connect(&m_AnalyticThread, SIGNAL(sendCircle(int,int,int)), this, SLOT(onCircle(int,int,int)));

    connect(&m_AnalyticThread, SIGNAL(sendCircle(int,int,int)), &m_PTZControlThread, SLOT(getCoordinates(int,int, int)));


}


void CMainWindow::Start()
{
    //this->show();
    m_CaptureThreadNonPTZ.Init("rtsp://root:pass@192.230.1.33:554/ufirststream");

    m_CaptureThreadNonPTZ.Start();
    m_CaptureThreadPTZ.Init("rtsp://root:pass@192.230.1.109:554/ch0_unicast_firststream");
    m_CaptureThreadPTZ.Start();
    m_AnalyticThread.Start();
}

void CMainWindow::onCapture(PMat img)
{
    //m_pCVViewer->showImage(img);
    imshow("Original", *img.data());
}

void CMainWindow::onCapturePTZ(PMat img)
{
    //m_pCVViewer->showImage(img);
    imshow("PTZ", *img.data());
}

void CMainWindow::onImgThresholded(PMat img)
{
    //m_pCVViewer2->showImage(img);
    imshow("Threshold", *img.data());
}

void CMainWindow::onCircle(int x, int y, int radius)
{
    Q_UNUSED(x); Q_UNUSED(y); Q_UNUSED(radius);

    //emit sendCoord(x, y);
    // draw the circle center
    //circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
    // draw the circle outline
    //circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );
}
