#include "displaywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DisplayWidget w;
	QString title = "kruskal";
	w.setWindowTitle(title);
	w.setWindowIcon(QIcon("Image.bmp"));
	w.setWindowIconText("kruskal");
	w.show();
	a.exec();
	return 0;
}
