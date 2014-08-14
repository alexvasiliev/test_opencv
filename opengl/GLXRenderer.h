#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include <QtWidgets/QWidget>
#include <QApplication>
#include <QDebug>

#include <stdio.h>
#include <stdlib.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>

#include "../Thread/ThreadImpl.h"
#include "../utils.h"


class CGLXRenderer: public CThreadImpl
{
    Q_OBJECT

public:
    CGLXRenderer(const QWidget& rWidget);

    void	Repaint();
    void    SetGeometry(int nWindowWidth, int nWindowHeight);

public slots:
    void            renderImage(PMat pFrame);

protected:
    virtual void    PrepareWork();
    virtual void	DoWork();
    virtual void	DoOnStop();

private:
    bool			m_bInitialized;
    cv::Mat         m_pFrameToRender;

    // Texture params
    GLuint			m_Texture;
    float			m_fTextureWidth;
    float			m_fTextureHeight;

    Display*                m_pDpy;
    Window                  m_WinHandle;
    GLXContext              m_GLContext;

    bool    m_bViewportInitialized;
    int     m_nWindowWidth;
    int     m_nWindowHeight;
    int     m_nInitialViewportWidth;
    int     m_nInitialViewportHeight;
    int     m_nFrameWidth;
    int     m_nFrameHeight;

    void    InitializeOriginViewport();
    void	InitViewport();
    void	InitOpenGL();
};

//typedef boost::shared_ptr<CGLXRenderer> PGLXRenderer;

#endif // OPENGLRENDERER_H
