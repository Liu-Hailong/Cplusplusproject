#include "displaywidget.h"
#include "ui_displaywidget.h"

DisplayWidget::DisplayWidget(QWidget* parent) 
	: QWidget(parent)
	, ui(new Ui::DisplayWidget)
{
	ui->setupUi(this);
	this->setAutoFillBackground(true);
	this->resize(1024,768);
	start = new QPushButton(this);
	start->setText("start");
	QFont ft;
	ft.setBold(true);
	ft.setFamily("Consolas");
	ft.setPointSize(19);
	QPalette pa;
	QColor color(110,110,255);
	pa.setColor(QPalette::ButtonText,color);
	pa.setColor(QPalette::Window,QColor(255,165,0));
	this->setPalette(pa);
	start->setPalette(pa);
	start->setFont(ft);
	start->resize(start->width()*1.5, start->height()*1.5);
	start->move(this->geometry().x() + this->width()/2 - 35, this->geometry().y() + this->height() - start->height());
	connect(start,SIGNAL(clicked()),this,SLOT(startKruskal()));
	init();
	update();
}

DisplayWidget::~DisplayWidget()
{
	delete ui;
}

void DisplayWidget::init()
{
	m_kruskal.initpoint();
	m_kruskal.initedge();
	m_kruskal.initdad();
	m_currentID = false;
}

void DisplayWidget::startKruskal()
{
	if (!m_currentID)
	{
		m_kruskal.sort();//边的排序
		m_currentID = true;
		int num = 0;
		for (int i = 0; i < edgeNum; i++)
		{
			if (m_kruskal.edges[i].weight == 0)continue;
			m_kruskal.edges[i].isOpen = true;
			shanshuo(i);
			if (m_kruskal.getfather(m_kruskal.edges[i].front->number) != m_kruskal.getfather(m_kruskal.edges[i].rear->number))
			{
				m_kruskal.edges[i].front->isChoose=true;
				m_kruskal.edges[i].rear->isChoose=true;
				m_kruskal.edges[i].isChoose = true;
				m_kruskal.merge(m_kruskal.edges[i].front->number, m_kruskal.edges[i].rear->number);
				num++;
			}
			else
			{
				m_kruskal.edges[i].isOpen = false;
				repaint();
			}
			if (num >= 7)break;
		}
		start->setText("quit");
	}//执行克鲁斯卡尔算法不断刷新屏幕显示内容
	else this->close();
}

void DisplayWidget::shanshuo(int i)
{
	for (int j = 0; j < 5; j++) {
		m_kruskal.edges[i].isOpen = false;
		repaint();
		_sleep(100);
		m_kruskal.edges[i].isOpen = true;
		repaint();
		_sleep(100);
	}
}

void DisplayWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);

	QFont font("Consolas");
	QPen pen;
	
	pen.setWidth(10); 
	pen.setColor(QColor(220, 220, 220));
	painter.setPen(pen);//配置画笔
	for (int i = 0; i < edgeNum; i++)
	{
		if (m_kruskal.edges[i].weight == 0)continue;
		QPoint a(m_kruskal.edges[i].front->x + this->geometry().width() / 2, m_kruskal.edges[i].front->y + this->geometry().height() / 2);
		QPoint b(m_kruskal.edges[i].rear->x + this->geometry().width() / 2, m_kruskal.edges[i].rear->y + this->geometry().height() / 2);
		QLine temp(a, b);
		painter.drawLine(temp);
	}
	if (m_currentID == true)
	{
		pen.setColor(QColor(0, 0, 0));//设置线条的颜色
		painter.setPen(pen);//加载线条的颜色

		for (int i = 0; i < edgeNum; i++)
		{
			if (m_kruskal.edges[i].weight == 0)continue;//排除无权值的线
			if (!m_kruskal.edges[i].isOpen)continue;
			QPoint a(m_kruskal.edges[i].front->x + this->geometry().width() / 2, m_kruskal.edges[i].front->y + this->geometry().height() / 2);
			QPoint b(m_kruskal.edges[i].rear->x + this->geometry().width() / 2, m_kruskal.edges[i].rear->y + this->geometry().height() / 2);
			QLine temp(a, b);//找点
			painter.drawLine(temp);//绘制线条
		}
	}
	//画线

	font.setPointSize(13);//设置字体的大小
	painter.setFont(font);//加载权值的字体
	for (int i = 0; i < edgeNum; i++)
	{
		if (m_kruskal.edges[i].weight == 0)continue;
		QPoint a(m_kruskal.edges[i].front->x + this->geometry().width()/2, m_kruskal.edges[i].front->y + this->geometry().height()/2);
		QPoint b(m_kruskal.edges[i].rear->x + this->geometry().width()/2, m_kruskal.edges[i].rear->y + this->geometry().height()/2);
		QLine temp(a, b);
		pen.setColor(QColor(255, 0, 0));//权值的颜色
		painter.setPen(pen);//加载绘画笔
		painter.drawText(temp.center().x(), temp.center().y(), QString::number(m_kruskal.edges[i].weight, 10));//绘制权值
	}
	//画线权值

	font.setPointSize(18);
	painter.setFont(font);
	painter.setPen(QPen(QColor(255,48,48)));//点内标记内容的颜色
	painter.setBrush(QBrush(QColor(0, 255, 255)));//点的颜色
	for (int i = 0; i < 8; i++)
	{
		QPoint c(m_kruskal.allpoint[i].x+ this->geometry().width()/2, m_kruskal.allpoint[i].y+ this->geometry().height()/2);
		painter.drawEllipse(c, 20, 20);
		QPoint temp(m_kruskal.allpoint[i].x - 7+ this->geometry().width()/2, m_kruskal.allpoint[i].y + 7+ this->geometry().height()/2);
		painter.drawText(temp, QString::number(m_kruskal.allpoint[i].number, 10));
	}
	//画点

	//三个边框，已选择点，已选择边，权值和
	
	int Interval = 10;//方框间隔
	int height = 100;
	int width = 120;//方框宽度
	QPoint loca(this->geometry().width() - width, 0);

	font.setPointSize(10);
	painter.setFont(font);
	painter.setBrush(QBrush(QColor(255, 255, 255)));//方框颜色
	painter.drawRoundRect(loca.x() - Interval, loca.y() + Interval, width, height, 10, 10);
	painter.drawText(loca.x()-5, loca.y() + 25, "Have chose nodes");
	{//内容

		int length = 0;
		int high = 20;
		font.setPointSize(18);
		painter.setFont(font);
		painter.setPen(QPen(QColor(255, 48, 48)));//点内标记内容的颜色
		painter.setBrush(QBrush(QColor(0, 255, 255)));//点的颜色
		for (int i = 0; i < maxNodenum; i++) 
		{
			if (length >= width)
			{
				length = 0;
				high += 20;
			}
			if (m_kruskal.allpoint[i].isChoose) 
			{
				QPoint c(loca.x()+length,loca.y() + 20 +high);
				painter.drawEllipse(c, 10, 10);
				painter.drawText(c.x()-7,c.y()+8, QString::number(m_kruskal.allpoint[i].number, 10));
				length += 20;
			}
		}
	}//方框一号

	font.setPointSize(10);
	painter.setFont(font);
	painter.setBrush(QBrush(QColor(255, 255, 255)));//方框颜色
	loca.setY(loca.y() + height + Interval);
	painter.drawRoundRect(loca.x() - Interval, loca.y() + Interval, width, height, 10, 10);
	painter.drawText(loca.x()-5, loca.y() + 25, "Have chose edges");
	{//内容
		int high = 20;
		int length = -5;
		font.setPointSize(18);
		painter.setFont(font);
		painter.setPen(QPen(QColor(255, 48, 48)));//点内标记内容的颜色
		painter.setBrush(QBrush(QColor(0, 255, 255)));//点的颜色
		for (int i = 0; i < edgeNum; i++)
		{
			if (length+60 >= width)
			{
				length = -5;
				high += 20;
			}
			if (m_kruskal.edges[i].isChoose)
			{
				QPoint c(loca.x()+length, loca.y() + 20 + high);
				painter.drawText(c.x() - 7, c.y() + 8, '('+QString::number(m_kruskal.edges[i].front->number, 10)+','+ QString::number(m_kruskal.edges[i].rear->number, 10)+')');
				length += 60;
			}
		}

	}//方框二号

	font.setPointSize(10);
	painter.setFont(font);
	painter.setBrush(QBrush(QColor(255, 255, 255)));//方框颜色
	loca.setY(loca.y() + height + Interval);
	painter.drawRoundRect(loca.x() - Interval, loca.y() + Interval, width, 40, 10, 10);
	{//内容
		font.setPointSize(10);
		painter.setFont(font);
		int num = 0;
		for (int i = 0; i < edgeNum; i++)
		{
			if (m_kruskal.edges[i].isChoose)
			{
				num += m_kruskal.edges[i].weight;
			}
		}
		painter.drawText(loca.x() - 5, loca.y() + 25, "Sum of weights: ");
		painter.drawText(loca.x() - 5, loca.y() + 50, QString::number(num, 10));
	}//方框三号

	this->start->move(this->width() / 2 - start->width()/2, this->height() - start->height());//刷新按钮位置
}

void DisplayWidget::mousePressEvent(QMouseEvent* event)
{
	QPoint CurrentMousePoint = event->pos();
	m_CurrentPoint = -1;
	for (int i = 0; i < maxNodenum; i++)
	{
		int dx = CurrentMousePoint.x() - (m_kruskal.allpoint[i].x+this->geometry().width()/2);
		int dy = CurrentMousePoint.y() - (m_kruskal.allpoint[i].y+this->geometry().height()/2);

		int dist = sqrt(dx * dx + dy * dy);

		if (dist < 20)
		{
			m_CurrentPoint = i;
			break;
		}
	}//锁定点的位置
}

void DisplayWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (m_CurrentPoint == -1)
		return;
	m_kruskal.allpoint[m_CurrentPoint].x = event->pos().x()-this->geometry().width()/2;
	m_kruskal.allpoint[m_CurrentPoint].y = event->pos().y()-this->geometry().height()/2;
	update();//移动已锁定点的位置
}

void DisplayWidget::mouseReleaseEvent(QMouseEvent* event)
{
	m_CurrentPoint = -1;//释放锁定的点
}
 