#include "OverlayWidget.h"
#include <QApplication>

#define DRAG_SENSITY	20

COverlayWidget::COverlayWidget(QWidget* pParent)
:	QLabel(pParent)
{
	setAttribute(Qt::WA_SetCursor);
    setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NativeWindow);
    setAttribute(Qt::WA_PaintUnclipped);
    setAttribute(Qt::WA_TranslucentBackground);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setWindowFlags(Qt::FramelessWindowHint);
    setAutoFillBackground(false);
}

void COverlayWidget::paintEvent (QPaintEvent * event )
{
    Q_UNUSED(event);
}
