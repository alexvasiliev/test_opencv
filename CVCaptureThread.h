#ifndef CV_CAPTURE_THREAD_H
#define CV_CAPTURE_THREAD_H

#include "Thread/ThreadImpl.h"

#include "utils.h"
#include <opencv2/highgui/highgui.hpp>
#include <QSharedPointer>

class CCVCaptureThread : public CThreadImpl
{
    Q_OBJECT
public:
    CCVCaptureThread();
    ~CCVCaptureThread();

    void Init(const std::string& sUrl);

protected:
    virtual void DoWork();

private:
    IplImage*       m_pResizedFrame;
    CvCapture*      m_pCapture;
    bool            m_bIsResized;

signals:
    void            resultReady(PMat img);
};


#endif // CV_CAPTURE_THREAD_H
