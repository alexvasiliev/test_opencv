#ifndef	OVERLAY_WIDGET_H
#define	OVERLAY_WIDGET_H

#include <QLabel>
#include <QDebug>

class COverlayWidget : public QLabel
{
    Q_OBJECT
public:
	COverlayWidget(QWidget* pParent);

protected:
    void paintEvent(QPaintEvent*);
};

#endif	// OVERLAY_WIDGET_H
