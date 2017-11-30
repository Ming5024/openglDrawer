#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_opengl.h"

class opengl : public QMainWindow
{
	Q_OBJECT

public:
	opengl(QWidget *parent = Q_NULLPTR);
	int type;
	QString filename;

private:
	Ui::openglClass ui;

private slots:
	void drawLine();
	void drawTriangle();
	void drawCircle();
	void drawRect();
	void drawRoundRect();
	void drawArc();
	void move();
	void deletes();

	void white();
	void yellow();
	void red();
	void grey();
	void darkgrey();
	void onStateChanged(int state);
	void save();
	void saveas();
	void load();
	void fileOpenActionSlot();
	void fileSaveActionSlot();
	void fileSaveAsActionSlot();
};
