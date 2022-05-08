#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include <QLabel>
#include <QPainter>
#include <QPoint>
#include <cmath>
#include "kruskal.h"

namespace Ui {
	class DisplayWidget;
}

class DisplayWidget : public QWidget
{
	Q_OBJECT

public:
	explicit DisplayWidget(QWidget* parent = 0);
	~DisplayWidget();

	KRUSKAL m_kruskal;     
	bool m_currentID;
	int m_CurrentPoint;
	QPushButton *start;

	void init();//初始化数据
	void shanshuo(int i);
	//执行克鲁斯卡尔图

protected:
	void paintEvent(QPaintEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent* event);
	//绘图事件

private slots:
	void startKruskal();
	
private:
	Ui::DisplayWidget* ui;
};

#endif // GRAPHVIEW_H