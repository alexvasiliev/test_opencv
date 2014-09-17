#include "CVCaptureThread.h"

using namespace cv;
CCVCaptureThread::CCVCaptureThread()
    :   m_pResizedFrame(0)
    ,   m_pCapture(0)
    ,   m_bIsResized(true)
{   
}

void CCVCaptureThread::Init(const std::string& sUrl)
{
    m_pCapture = cvCreateFileCapture(sUrl.c_str());
    m_pResizedFrame = cvCreateImage(cvSize(440, 330), 8, 3);
}

CCVCaptureThread::~CCVCaptureThread()
{
    cvReleaseCapture(&m_pCapture);
    cvReleaseImage(&m_pResizedFrame);
}

void CCVCaptureThread::DoWork()
{
    // получаем кадр
    IplImage* pFrame = cvQueryFrame( m_pCapture );

    if(pFrame)
    {
        if(m_bIsResized)
        {
            // изменияем размер кадра
            if(!m_pResizedFrame)
                m_pResizedFrame = cvCreateImage(cvSize(440, 330), pFrame->depth, pFrame->nChannels);
            cvResize(pFrame, m_pResizedFrame);
            pFrame = m_pResizedFrame;
        }

        // отправляем кадр
        PMat pImg = PMat(new Mat(pFrame, true/*copy data*/)); //to avoid memory corruption
        emit resultReady(pImg);
        msleep(30);
    }
}
