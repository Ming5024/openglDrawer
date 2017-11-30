#include "opengl.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	opengl w;
	w.show();
	return a.exec();
}
