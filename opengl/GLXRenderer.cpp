#include "GLXRenderer.h"
#include <QDebug>
#include <QGLWidget>
#include <QtGui/5.3.1/QtGui/qpa/qplatformnativeinterface.h>


CGLXRenderer::CGLXRenderer(const QWidget& rWidget)
    :   m_bInitialized(false)
    ,	m_Texture(0)
    ,	m_fTextureWidth(0.0f)
    ,	m_fTextureHeight(0.0f)
    ,   m_pDpy(0)
    ,   m_WinHandle(0)
{
    QPlatformNativeInterface* interface = QGuiApplication::platformNativeInterface();
    m_pDpy = static_cast<Display *>(interface->nativeResourceForWindow("display", rWidget.windowHandle()));
    //qDebug()<<"m_pDpy"<<m_pDpy;
    m_WinHandle = (Window)rWidget.winId();
    //qDebug()<<"m_WinHandle"<<m_WinHandle;
}

void CGLXRenderer::PrepareWork()
{
    // Wait until first frame comes
    if(!m_bAbort)
        Suspend();
}


void CGLXRenderer::DoOnStop()
{
    glXMakeCurrent(m_pDpy, None, NULL);
    glXDestroyContext(m_pDpy, m_GLContext);
    //XCloseDisplay(m_pDpy);
}

void CGLXRenderer::InitOpenGL()
{
    GLint attribs[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, None};
    XVisualInfo* pVi = glXChooseVisual(m_pDpy,  DefaultScreen(m_pDpy), attribs);

    m_GLContext = glXCreateContext(m_pDpy, pVi, NULL, GL_TRUE);
    glXMakeCurrent(m_pDpy, m_WinHandle, m_GLContext);

    glClearColor(0.664f, 1.0f, 1.0f, 0.2f); //);//(0.0f, 0.0f, 0.0f, 0.0f); //0.664f, 1.0f, 1.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_NEVER);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRasterPos2i(-1, 1);       // move to the upper left corner
    glPixelZoom(1.0, -1.0);     // top to bottom

    glXSwapBuffers(m_pDpy, m_WinHandle);

    m_bInitialized = true;
}

void CGLXRenderer::renderImage(PMat pFrame)
{
    Q_ASSERT(pFrame->data);
    {
        //boost::mutex::scoped_lock	Lock(m_FrameMutex);
        pFrame->copyTo(m_pFrameToRender);
    }

    Repaint();
}

void CGLXRenderer::SetGeometry(int nWindowWidth, int nWindowHeight)
{
    m_nWindowWidth = nWindowWidth;
    m_nWindowHeight = nWindowHeight;

    m_bViewportInitialized = false;
}

void CGLXRenderer::Repaint()
{
    // Resume thread to render current frame
    Resume();
}

void CGLXRenderer::InitializeOriginViewport()
{
    //Initialize origin viewport size
    double	fAspectRatio = (double) m_nFrameWidth / m_nFrameHeight;
    double  fWindowRatio = (double) m_nWindowWidth / m_nWindowHeight;
            // Fit frame into window
    if(fAspectRatio < fWindowRatio)
    {
        m_nInitialViewportHeight = m_nWindowHeight;
        m_nInitialViewportWidth = m_nWindowHeight * fAspectRatio;
    }
    else
    {
        m_nInitialViewportWidth = m_nWindowWidth;
        m_nInitialViewportHeight = m_nWindowWidth / fAspectRatio;

    }
}


void CGLXRenderer::InitViewport()
{
    InitializeOriginViewport();
    //SetViewportSizeToScale();

    int nViewportX = (m_nWindowWidth - m_nInitialViewportWidth) / 2;
    int nViewportY = (m_nWindowHeight - m_nInitialViewportHeight) / 2;

    glMatrixMode(GL_PROJECTION);
    //qDebug() << "InitViewport" << nViewportX << nViewportY << m_nInitialViewportWidth << m_nInitialViewportHeight;
    //glViewport(nViewportX, nViewportY, m_nInitialViewportWidth, m_nInitialViewportHeight);
    glPushAttrib(GL_VIEWPORT_BIT);
    glViewport(nViewportX, nViewportY, m_nInitialViewportWidth, m_nInitialViewportHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Make sure depth testing and lighting are disabled for 2D rendering until
    // we are finished rendering in 2D
    glPushAttrib( GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT );
    glDisable( GL_DEPTH_TEST );
    glDisable( GL_LIGHTING );

    m_bViewportInitialized = true;
}

void CGLXRenderer::DoWork()
{
    if(!m_bInitialized)
        InitOpenGL();

    // Render frame
    {
        //boost::mutex::scoped_lock	Lock(m_FrameMutex);
        if(m_pFrameToRender.data)
        {
            if(m_nWindowWidth && m_nWindowHeight)
            {
                //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glClearColor(1, 0, 0, 0);
                glClearColor(1, 0, 0, 1);

                m_nFrameWidth	= m_pFrameToRender.cols;
                m_nFrameHeight	= m_pFrameToRender.rows;

                if(!m_bViewportInitialized)
                    InitViewport();

                glEnable(GL_TEXTURE_2D);
                glGenTextures(1, &m_Texture);
                glBindTexture(GL_TEXTURE_2D, m_Texture);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //GL_NEAREST);

                QImage mRenderQtImg = QImage((const unsigned char*)(m_pFrameToRender.data),
                                      m_pFrameToRender.cols, m_pFrameToRender.rows,
                                      m_pFrameToRender.step, QImage::Format_RGB888).rgbSwapped();

                mRenderQtImg = QGLWidget::convertToGLFormat(mRenderQtImg);

                glTexImage2D(GL_TEXTURE_2D, 0, 3, m_nFrameWidth, m_nFrameHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, (const unsigned char*)(mRenderQtImg.bits()));
                //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, m_nFrameWidth, m_nFrameHeight, GL_RGB, GL_UNSIGNED_BYTE, m_pFrameToRender->GetBufferPointer());

                glBegin(GL_POLYGON);
                glTexCoord2i(0,	0);	glVertex2f(-1.0,  1.0);
                glTexCoord2i(1,	0);	glVertex2f( 1.0,  1.0);
                glTexCoord2i(1,	1);	glVertex2f( 1.0, -1.0);
                glTexCoord2i(0,	1);	glVertex2f(-1.0, -1.0);
                glEnd();

                glFlush();

                // Clear texture
                if(m_Texture)
                {
                    glDeleteTextures(1, &m_Texture);
                    m_Texture = 0;
                }

                //glDisable2D();
                glDisable(GL_TEXTURE_2D);

                glXSwapBuffers(m_pDpy, m_WinHandle);
            }
        }
    }

    // Wait for next frame to render
    if(!m_bAbort)
        Suspend();
}
