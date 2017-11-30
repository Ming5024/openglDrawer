#pragma once
#ifndef WIDGET_H  
#define WIDGET_H

#include <QWidget>  
#include <QtOpenGL/QtOpenGL>
#include <gl/GLU.h>
#include <GL/GL.h>
#include <glut.h>

class glview :
	public QGLWidget
{
public:
	glview();
	glview(QWidget* widget);
	~glview();
	void drawline();
	void draw();
	int control;	//定义画图操作或者移动删除保存操作
	int type;
	int color;
	bool robot;
	void write_out(const char * path);
	void read_image(const char * path);

signals:

public slots :
	void  repaint(int x, int y, int w, int h, bool erase = FALSE);

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	//void paintEvent(QPaintEvent *e);

private:
	GLfloat Point[5][3];
	QTimer timer;
};

#endif // WIDGET_H 

