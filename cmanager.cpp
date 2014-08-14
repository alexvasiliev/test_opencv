#include "cmanager.h"
#include <QDebug>
#include <QWidget>
#include <QMainWindow>

CManager::CManager(bool bAnalytic, bool bPTZControl)
    :   m_bAnalytics(bAnalytic)
    ,   m_bPTZControl(bPTZControl)
{
     m_pAnalytic = PAnalytic(new CAnalytic());

     m_nLowH = 5;
     m_nLowS = 95;
     m_nLowV = 10;

     m_nHighH = 80;
     m_nHighS = 255;
     m_nHighV = 255;
}


void CManager::CreateNonPtzThread()
{
    m_pCamNonPtzThread = PCamNonPtzThread(new CCamNonPtzThread());
    connect(m_pCamNonPtzThread.data(), SIGNAL(resultReady(cv::Mat)), this, SLOT(handleNonPTZFrame(cv::Mat)));
   // connect(m_pCamNonPtzThread.data(), SIGNAL(finished), m_pCamNonPtzThread.data(), SLOT(&QObject::deleteLater));
    m_pCamNonPtzThread->Start();
}


void CManager::CreateGUI()
{
    namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"
    moveWindow("Control", 700, 0);

    cvCreateTrackbar("LowH", "Control", &m_nLowH, 255); //Hue (0 - 179)//Create trackbars in "Control" window
    cvCreateTrackbar("HighH", "Control", &m_nHighH, 255);

    cvCreateTrackbar("LowS", "Control", &m_nLowS, 255); //Saturation (0 - 255)
    cvCreateTrackbar("HighS", "Control", &m_nHighS, 255);

    cvCreateTrackbar("LowV", "Control", &m_nLowV, 255); //Value (0 - 255)
    cvCreateTrackbar("HighV", "Control", &m_nHighV, 255);

    cvCreateTrackbar("Analytics", "Control", (int*) &m_bAnalytics, 1);
}


void CManager::handleNonPTZFrame(Mat img)
{
    Mat imgHSV;

    cvtColor(img , imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

    Mat imgThresholded;

    inRange(img, Scalar(m_nLowH, m_nLowS, m_nLowV), Scalar(m_nHighH, m_nHighS, m_nHighV), imgThresholded); //Threshold the image

     //morphological opening (remove small objects from the foreground)
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

      //morphological closing (fill small holes in the foreground)
    dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
    //cvtColor(imgThresholded, imgThresholded, COLOR_HSV2BGR);
    if(m_bAnalytics)
    {
        /*vector<Vec3f> circles = m_pAnalytic->findCircleBorders(img);
        for( size_t i = 0; i < circles.size(); i++ )
        {
             Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
             qDebug()<<"x: "<<cvRound(circles[i][0]) << "y: " << cvRound(circles[i][1]);
             int radius = cvRound(circles[i][2]);
             // draw the circle center
             circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
             // draw the circle outline
             circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );
        }*/


        vector<Vec3f> circles = m_pAnalytic->findCircleBorders(img);
        for( size_t i = 0; i < circles.size(); i++ )
        {
             Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
             cv::Vec3b bgr = imgThresholded.at<cv::Vec3b>(cvRound(circles[i][0]), cvRound(circles[i][1]));
             //qDebug()<< temp[0] << temp[1] << temp[2];
             //cv::Mat3b image = imgThresholded;
             //const cv::Vec3b& bgr = image(center);
             //qDebug()<<bgr[0]<< bgr[1]<<bgr[2];
             if(bgr[0] > 240 && bgr[1] > 240  && bgr[2] > 240 )
             {
                 qDebug()<<"x: "<<cvRound(circles[i][0]) << "y: " << cvRound(circles[i][1]);
                 int radius = cvRound(circles[i][2]);
                 // draw the circle center
                 circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
                 // draw the circle outline
                 circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );
             }

        }
    }
    imshow("Control", imgThresholded); //show the thresholded image*/
    m_pViewer->showImage(img);
    //imshow("orig", img);
}


void CManager::TurnAnaytic(bool on_or_off)
{
    m_bAnalytics = on_or_off;
}
