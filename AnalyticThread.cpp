#include "AnalyticThread.h"
#include <QDebug>

//mask for orange.mp4
//m_nLowH = 5;
//m_nLowS = 95;
//m_nLowV = 10;

//m_nHighH = 80;
//m_nHighS = 255;
//m_nHighV = 255;

CAnalyticThread::CAnalyticThread()
{
    m_nLowH = 5;
    m_nLowS = 95;
    m_nLowV = 10;

    m_nHighH = 80;
    m_nHighS = 255;
    m_nHighV = 255;

    CreateTrackBar();
}

void CAnalyticThread::analyseImage(PMat img)
{
    m_pMutex.lock();
    img->copyTo(m_imgRGB);
    m_pMutex.unlock();

    Resume();
}


void CAnalyticThread::ConvertColorToHSV()
{
    cvtColor(m_imgRGB , m_imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
}

void CAnalyticThread::ThresholdImage(const Mat& img)
{
    inRange(img, Scalar(m_nLowH, m_nLowS, m_nLowV), Scalar(m_nHighH, m_nHighS, m_nHighV), m_imgThresholded); //Threshold the image

    //morphological opening (remove small objects from the foreground)
    erode(m_imgThresholded, m_imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( m_imgThresholded, m_imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );

    //morphological closing (fill small holes in the foreground)
    /*dilate(m_imgThresholded, m_imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    erode(m_imgThresholded, m_imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );*/

    PMat pImg = PMat(new Mat(m_imgThresholded));
    emit sendThresholdedImg(pImg);
}


void CAnalyticThread::FindCircleBorders(const Mat& image)
{
    //Mat gray;
    //cvtColor(image, gray, CV_BGR2GRAY);


    // smooth it, otherwise a lot of false circles may be detected
    GaussianBlur( m_imgThresholded, m_imgThresholded, Size(5, 5), 2, 2 );
    vector<Vec3f> circles;
    HoughCircles(m_imgThresholded, circles, CV_HOUGH_GRADIENT, 2, m_imgThresholded.rows/4, 80, 50);

    for( size_t i = 0; i < circles.size(); i++ )
    {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        //cv::Vec3b bgr = m_imgThresholded.at<cv::Vec3b>(cvRound(circles[i][0]), cvRound(circles[i][1]));
        //qDebug()<< temp[0] << temp[1] << temp[2];
        //cv::Mat3b image = imgThresholded;
        //const cv::Vec3b& bgr = image(center);
        //qDebug()<<bgr[0]<< bgr[1]<<bgr[2];
       // if(bgr[0] > 240 && bgr[1] > 240  && bgr[2] > 240 )
       // {
            int radius = cvRound(circles[i][2]);
            qDebug()<<"x: "<< center.x << "y: " << center.y << "radius: " << radius;
            emit sendCircle(center.x, center.y, radius);
       // }

    }
}

void CAnalyticThread::CreateTrackBar()
{
    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    moveWindow("Control", 700, 0);

    cvCreateTrackbar("LowH", "Control", &m_nLowH, 255); //Hue (0 - 179)//Create trackbars in "Control" window
    cvCreateTrackbar("HighH", "Control", &m_nHighH, 255);

    cvCreateTrackbar("LowS", "Control", &m_nLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &m_nHighS, 255);

    cvCreateTrackbar("LowV", "Control", &m_nLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &m_nHighV, 255);
}

void CAnalyticThread::DoWork()
{
    if(m_imgRGB.data)
    {
        //we should synchronize only m_imgRGB;
        m_pMutex.lock();
        ConvertColorToHSV();

        ThresholdImage(m_imgHSV);
        FindCircleBorders(m_imgRGB);

        m_pMutex.unlock();
    }

    if(!m_bAbort)
        Suspend();
}
