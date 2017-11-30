#include "glview.h"
#include<iostream>
#include<vector>
#include<math.h>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<string>
using namespace std;
const GLfloat PI = 3.1415926536f;
//灰色:195,195,195
//黄色:255,243,0
//红色:237,28,36
//深灰色:126,126,126
int black[3] = { 0, 0, 0 };
int grey[3] = { 195, 195, 195 };
int yellow[3] = { 255, 243, 0 };
int red[3] = { 237, 28, 36 };
int darkGrey[3] = { 126, 126, 126 };
int white[3] = { 255, 255, 255 };
int half = 300;
int num = 0;
struct image
{
	int index_x;
	int index_y;
	int index_x1;
	int index_y1;
	int color;
	int type;
};
std::vector<image>to_draw;

int get_image(int x, int y)
{
	int choose_index = -1;
	double min_dis = 100000;
	int length = to_draw.size();
	qDebug() << "size = " << length;
	for (int i = 0; i < length; i++)
	{
		image image_now = to_draw[i];
		if (image_now.type == 1)		//Line
		{
			qDebug() << image_now.type;
			int x_first = image_now.index_x;
			int y_first = image_now.index_y;
			int x_after = image_now.index_x1;
			int y_after = image_now.index_y1;
			double n_x = x - x_first;
			double n_s = x_after - x_first;
			//double n_slope = (y - y_first) / n_x;
			//double slope = (y_after - y_first) / n_s;
			/*
			if (x_first < x && x_after > x && y_first > y && y_after < y && abs(n_slope - slope) < 0.1)
			{
				double temp_dis = (x - x_first) * (x - x_first) + (y - y_first) * (y - y_first);
				if (temp_dis < min_dis)
				{
					min_dis = temp_dis;
					choose_index = i;
				}
			}*/
			double s1 = sqrt((x - x_first) * (x - x_first) + (y - y_first) * (y - y_first));
			double s2 = sqrt((x - x_after) * (x - x_after) + (y - y_after) * (y - y_after));
			double ss = sqrt((x_after - x_first) * (x_after - x_first) + (y_after - y_first) * (y_after - y_first));
			qDebug() << s1 << " " << s2 << " " << ss;
			if ((s1 + s2) / ss < 1.015)
			{
				double temp_dis = (x - x_first) * (x - x_first) + (y - y_first) * (y - y_first);
				if (temp_dis < min_dis)
				{
					min_dis = temp_dis;
					choose_index = i;
				}
			}
			/*
			double distance = ((x - x_first)*(y_after - y_first) - (x_after - x_first)*(y - y_first)) / sqrt((x_after - x_first)*(x_after - x_first) + (y_after - y_first)*(y_after - y_first));
			if (distance <= 0.5)
			{
				double temp_dis = (x - x_first) * (x - x_first) + (y - y_first) * (y - y_first);
				if (temp_dis < min_dis)
				{
					min_dis = temp_dis;
					choose_index = i;
				}
			}
			*/
			else
			{
				continue;
			}
		}
		else if (image_now.type == 4 || image_now.type == 5)		//Rectangle or RoundRect
		{
			int x_first = image_now.index_x;
			int y_first = image_now.index_y;
			int x_after = image_now.index_x1;
			int y_after = image_now.index_y1;
			if (x_after < x_first)
			{
				int temp = x_after;
				x_after = x_first;
				x_first = temp;
				temp = y_after;
				y_after = y_first;
				y_first = temp;
			}
			if (x_first < x && x_after > x && y_first > y && y_after < y)
			{
				double temp_dis = (x - x_first) * (x - x_first) + (y - y_first) * (y - y_first);
				if (temp_dis < min_dis)
				{
					min_dis = temp_dis;
					choose_index = i;
				}
			}
			else
			{
				continue;
			}
		}
		else if (image_now.type == 3)		//Circle
		{
			qDebug() << image_now.type;
			int x_first = image_now.index_x;
			int y_first = image_now.index_y;
			int x_after = image_now.index_x1;
			int y_after = image_now.index_y1;
			double R_now = sqrt((x_first - x_after)*(x_first - x_after) + (y_first - y_after)*(y_first - y_after));
			double distance = sqrt((x_first - x)*(x_first - x) + (y_first - y)*(y_first - y));
			if (distance < R_now)
			{
				double temp_dis = (x - x_first) * (x - x_first) + (y - y_first) * (y - y_first);
				if (temp_dis < min_dis)
				{
					min_dis = temp_dis;
					choose_index = i;
				}
			}
			else
			{
				continue;
			}
		}
		else if (image_now.type == 2)		//Triangle
		{
			qDebug() << image_now.type;
			int x_first = image_now.index_x;
			int y_first = image_now.index_y;
			int x_after = image_now.index_x1;
			int y_after = image_now.index_y1;
			if (x_after > x_first)
			{
				x_after = x_first - (x_after - x_first);
			}
			//qDebug() << x << y << x_first << y_first << x_after << y_after;
			if (x < x_after || y<y_after || y>y_first || x>2 * x_first - x_after)
				continue;
			qDebug() << "pass continue";
			double xie_ori = double(y_first - y_after) / double(x_first - x_after);
			double xie1 = 0;
			double xie2 = 0;
			xie1 = double(y - y_after) / double(x - x_after); 
			xie2 = double(y - y_after) / double(2 * x_first - x_after - x);
			qDebug() << xie1 << " " << xie2;
			if (xie1 <= xie_ori&&xie2 <= xie_ori)
			{
				double temp_dis = (x - x_first) * (x - x_first) + (y - y_first) * (y - y_first);
				if (temp_dis < min_dis)
				{
					min_dis = temp_dis;
					choose_index = i;
				}
			}
			else
			{
				continue;
			}
		}
		else if (image_now.type == 6)		//Arc
		{
			int x_first = image_now.index_x;
			int y_first = image_now.index_y;
			int x_after = image_now.index_x1;
			int y_after = image_now.index_y1;
			double arcX = x_first + (x_after - x_first) * 1.0 / 2;
			double arcY = y_first + (x_after - x_first) * 1.0 / 2;
			double arcR = (x_after - x_first) * sqrt(2) / 2;
			double distance = sqrt((x - arcX) * (x - arcX) + (y - arcY) * (y - arcY));
			if (x_first < x && x_after > x && y < y_first && distance >= arcR - 6 && distance <= arcR + 6)
			{
				double temp_dis = (x - x_first) * (x - x_first) + (y - y_first) * (y - y_first);
				if (temp_dis < min_dis)
				{
					min_dis = temp_dis;
					choose_index = i;
				}
			}
			else
			{
				continue;
			}
		}
	}
	return choose_index;
}
//移动
void move_image(int index, int x1, int y1, int x2, int y2)
{
	int change_x = x2 - x1;
	int change_y = y2 - y1;
	to_draw[index].index_x = to_draw[index].index_x + change_x;
	to_draw[index].index_x1 = to_draw[index].index_x1 + change_x;
	to_draw[index].index_y = to_draw[index].index_y + change_y;
	to_draw[index].index_y1 = to_draw[index].index_y1 + change_y;
}
//删除
void delete_image(int index)
{
	std::vector<image>::iterator it = to_draw.begin();
	to_draw.erase(it + index);
}
//存储
void glview::write_out(const char * path)
{
	qDebug() << path;
	std::ofstream write_image(path, ios::binary);
	int temp_size = to_draw.size();
	write_image.write((char*)&(temp_size), sizeof(temp_size));
	for (int i = 0; i < to_draw.size(); i++)
	{
		image image_now = to_draw[i];
		qDebug() << i;
		write_image.write((char*)&(image_now.index_x), sizeof(image_now.index_x));
		write_image.write((char*)&(image_now.index_y), sizeof(image_now.index_y));
		write_image.write((char*)&(image_now.index_x1), sizeof(image_now.index_x1));
		write_image.write((char*)&(image_now.index_y1), sizeof(image_now.index_y1));
		write_image.write((char*)&(image_now.color), sizeof(image_now.color));
		write_image.write((char*)&(image_now.type), sizeof(image_now.type));
	}
	write_image.close();
}
//读取
void glview:: read_image(const char * path)
{
	to_draw.clear();
	//qDebug() << path;
	std::vector<image>original;
	std::ifstream read_image(path, ios::binary);
	int size_now;
	read_image.read((char*)&(size_now), sizeof(size_now));
	int offset_value = sizeof(int) * 6;
	for (int i = 0;i <= size_now; i++)
	{
		//qDebug() << i;
		int offset = offset_value*i;
		read_image.seekg(offset + sizeof(int));
		image temp;
		int x_now = 0;
		int y_now = 0;
		int x1_now = 0;
		int y1_now = 0;
		int type_now = 0;
		int color_now = 0;
		read_image.read((char*)&(x_now), sizeof(x_now));
		read_image.read((char*)&(y_now), sizeof(y_now));
		read_image.read((char*)&(x1_now), sizeof(x1_now));
		read_image.read((char*)&(y1_now), sizeof(y1_now));
		read_image.read((char*)&(color_now), sizeof(color_now));
		read_image.read((char*)&(type_now), sizeof(type_now));
		
		temp.index_x = x_now;
		temp.index_y = y_now;
		temp.index_x1 = x1_now;
		temp.index_y1 = y1_now;
		temp.color = color_now;
		temp.type = type_now;
		//qDebug() << temp.type;
		original.push_back(temp);
	}
	to_draw = original;
	read_image.close();
	updateGL();
}

void draw_circle(GLfloat x, GLfloat y, GLfloat R)
{
	glBegin(GL_LINE_STRIP);
	glLineWidth(5.0f);
	for (int i = 0; i <= 1000; i++)
		glVertex2f(R*cos(2 * PI / 1000 * i) + x, R*sin(2 * PI / 1000 * i) + y);
	glEnd();
}
void draw_rec(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(x1, y1);
	glVertex2f(x1, y2);
	glVertex2f(x2, y2);
	glVertex2f(x2, y1);
	glVertex2f(x1, y1);
	glEnd();
}

void draw_line_circle1(GLfloat x, GLfloat y, GLfloat R)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i <= 250; i++)
		glVertex2f(R*cos(2 * PI / 1000 * i) + x, R*sin(2 * PI / 1000 * i) + y);
	for (int i = 250; i >= 0; i--)
		glVertex2f(R*cos(2 * PI / 1000 * i) + x, R*sin(2 * PI / 1000 * i) + y);
	glEnd();
}
void draw_line_circle2(GLfloat x, GLfloat y, GLfloat R)
{
	glBegin(GL_LINE_LOOP);
	glLineWidth(100);
	for (int i = 250; i <= 500; i++)
		glVertex2f(R*cos(2 * PI / 1000 * i) + x, R*sin(2 * PI / 1000 * i) + y);
	for (int i = 500; i >= 250; i--)
		glVertex2f(R*cos(2 * PI / 1000 * i) + x, R*sin(2 * PI / 1000 * i) + y);
	glEnd();
}
void draw_line_circle4(GLfloat x, GLfloat y, GLfloat R)
{
	glBegin(GL_LINE_LOOP);
	glLineWidth(100);
	for (int i = 500; i <= 750; i++)
		glVertex2f(R*cos(2 * PI / 1000 * i) + x, R*sin(2 * PI / 1000 * i) + y);
	for (int i = 750; i >= 500; i--)
		glVertex2f(R*cos(2 * PI / 1000 * i) + x, R*sin(2 * PI / 1000 * i) + y);
	glEnd();
}
void draw_line_circle3(GLfloat x, GLfloat y, GLfloat R)
{
	glBegin(GL_LINE_LOOP);
	glLineWidth(100);
	for (int i = 750; i <= 1000; i++)
		glVertex2f(R*cos(2 * PI / 1000 * i) + x, R*sin(2 * PI / 1000 * i) + y);
	for (int i = 1000; i >= 750; i--)
		glVertex2f(R*cos(2 * PI / 1000 * i) + x, R*sin(2 * PI / 1000 * i) + y);
	glEnd();
}

void draw_line_smile(GLfloat x, GLfloat y, GLfloat R)
{
	glBegin(GL_LINE_LOOP);
	glLineWidth(100);
	for (int i = 625; i <= 875; i++)
		glVertex2f(R*cos(2 * PI / 1000 * i) + x, R*sin(2 * PI / 1000 * i) + y);
	for (int i = 875; i >= 625; i--)
		glVertex2f(R*cos(2 * PI / 1000 * i) + x, R*sin(2 * PI / 1000 * i) + y);
	glEnd();
}
//右上圆弧
void draw_robot()
{

	glBegin(GL_LINES);
	glVertex2f(-60, 255);
	glVertex2f(60, 255);

	glVertex2f(-75, 240);
	glVertex2f(-75, 195);

	glVertex2f(75, 240);
	glVertex2f(75, 195);

	glVertex2f(-60, 180);
	glVertex2f(60, 180);

	glVertex2f(-45, 255);
	glVertex2f(-45, 285);

	glVertex2f(45, 255);
	glVertex2f(45, 285);

	glVertex2f(-30, 165);
	glVertex2f(-30, 180);

	glVertex2f(30, 165);
	glVertex2f(30, 180);

	glVertex2f(67.5, 165);
	glVertex2f(-67.5, 165);

	glVertex2f(67.5, 0);
	glVertex2f(-67.5, 0);

	glVertex2f(-82.5, 150);
	glVertex2f(-82.5, 15);

	glVertex2f(82.5, 150);
	glVertex2f(82.5, 15);

	glVertex2f(90, 150);
	glVertex2f(82.5, 150);

	glVertex2f(90, 135);
	glVertex2f(82.5, 135);

	glVertex2f(-90, 150);
	glVertex2f(-82.5, 150);

	glVertex2f(-90, 135);
	glVertex2f(-82.5, 135);

	glVertex2f(96, 96);
	glVertex2f(96, 90);

	glVertex2f(-96, 96);
	glVertex2f(-96, 90);

	glVertex2f(105, 96);
	glVertex2f(105, 90);

	glVertex2f(-105, 96);
	glVertex2f(-105, 90);

	glVertex2f(-48, 0);
	glVertex2f(-48, -6);

	glVertex2f(-24, 0);
	glVertex2f(-24, -6);

	glVertex2f(48, 0);
	glVertex2f(48, -6);

	glVertex2f(24, 0);
	glVertex2f(24, -6);

	glVertex2f(-24, -6);
	glVertex2f(-48, -6);

	glVertex2f(24, -6);
	glVertex2f(48, -6);

	glVertex2f(-54, -13.5);
	glVertex2f(-54, -60);

	glVertex2f(-18, -13.5);
	glVertex2f(-18, -60);

	glVertex2f(54, -13.5);
	glVertex2f(54, -60);

	glVertex2f(18, -13.5);
	glVertex2f(18, -60);

	glVertex2f(-24, -66);
	glVertex2f(-48, -66);

	glVertex2f(24, -66);
	glVertex2f(48, -66);

	glVertex2f(46.5, -66);
	glVertex2f(46.5, -72);

	glVertex2f(-46.5, -66);
	glVertex2f(-46.5, -72);

	glVertex2f(25.5, -66);
	glVertex2f(25.5, -72);

	glVertex2f(-25.5, -66);
	glVertex2f(-25.5, -72);

	glEnd();

	draw_line_circle1(60, 240, 15);
	draw_line_circle2(-60, 240, 15);
	draw_line_circle3(60, 195, 15);
	draw_line_circle4(-60, 195, 15);
	draw_line_circle1(67.5, 150, 15);
	draw_line_circle2(-67.5, 150, 15);
	draw_line_circle3(67.5, 15, 15);
	draw_line_circle4(-67.5, 15, 15);
	draw_line_circle1(-24, -12, 6);
	draw_line_circle2(-48, -12, 6);
	draw_line_circle2(24, -12, 6);
	draw_line_circle1(48, -12, 6);
	draw_line_circle3(-24, -60, 6);
	draw_line_circle4(-48, -60, 6);
	draw_line_circle4(24, -60, 6);
	draw_line_circle3(48, -60, 6);

	draw_circle(30, 225, 10.5);
	draw_circle(-30, 225, 10.5);
	draw_circle(-100.5, 46.5, 7.5);
	draw_circle(100.5, 46.5, 7.5);
	draw_circle(0, 111, 9);

	glBegin(GL_LINE_LOOP);

	glVertex2f(0, 141);
	glVertex2f(30, 96);
	glVertex2f(-30, 96);

	glEnd();
	draw_line_smile(0, 225, 30);

	draw_rec(-96, 234, -78, 198);
	draw_rec(96, 234, 78, 198);
	draw_rec(-111, 153, -90, 96);
	draw_rec(111, 153, 90, 96);
	draw_rec(-111, 90, -90, 54);
	draw_rec(111, 90, 90, 54);
	draw_rec(-66, -72, -9.9, -90);
	draw_rec(66, -72, 9.9, -90);

}

glview::glview()
{
	
}

glview::glview(QWidget* parent)
	:QGLWidget(parent)
{
	this->control = 0;
	this->type = 0;
	this->color = 0;
	this->robot = false;
	/*
	connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
	timer.start(0);
	setFocusPolicy(Qt::StrongFocus);
	setMouseTracking(true);
	
	QSurfaceFormat format;  
    format.setRenderableType(QSurfaceFormat::OpenGL);  
    format.setProfile(QSurfaceFormat::CoreProfile);  
    format.setVersion(3,3);  
    setFormat(format); 
	*/
}


glview::~glview()
{
}

void glview::initializeGL()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//draw_robot();
}


void glview::paintGL()
{
	/*
	if (this->type == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
	}
	*/
	//qDebug() << this->type;
	/*
	if (this->type != 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glPushMatrix();
		glLineWidth(2);
		glColor3f(0.0, 0.0, 0.0);
		draw();
		//this->type = -1;
		glPopMatrix();
		//QMetaObject::invokeMethod(this, "updateGL", Qt::QueuedConnection);
	}
	*/
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glLineWidth(2);
	glColor3f(0.0, 0.0, 0.0);
	draw();
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(2);
	if (this->robot)
	{
		draw_robot();
	}
	return;
}

void glview::resizeGL(int width, int height)
{
	
	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width<height) {
		//如果高度大于宽度，则将高度视角扩大，图形显示居中
		glOrtho(-half, half, -half*height / width, half*height / width, -half, half);
	}
	else {
		//如果宽度大于高度，则将宽度视角扩大，图形显示居中
		glOrtho(-half*width / height, half*width / height, -half, half, -half, half);
	}
	//gluPerspective(45.0, (GLfloat)width / (GLfloat)height, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}
void glview::mouseDoubleClickEvent(QMouseEvent *event)
{
	qDebug() << event->x() << " " << event->y();
	if (windowState() &  Qt::WindowFullScreen)
		showNormal();
	else
		showFullScreen();
	
}
void glview::keyPressEvent(QKeyEvent *e)
{
	/*
	if (e->key() == Qt::Key_Escape)
		close();
	*/
}

image temp;
int move_index;
int move_x1, move_y1, move_x2, move_y2;
int delete_index;
void glview::mousePressEvent(QMouseEvent *event)
{
	//qDebug() << "----------mouseclick---------";
	//qDebug() << event->x() - half << " " << half - event->y();
	if (this->control == 1)		//Draw
	{
		temp.type = this->type;
		temp.color = this->color;
		temp.index_x = event->x() - half;
		temp.index_y = half - event->y();
	}
	else if (this->control == 2)		//Move
	{
		move_index = get_image(event->x() - half, half - event->y());
		move_x1 = event->x() - half;
		move_y1 = half - event->y();
	}
	else if (this->control == 3)		//Delete
	{
		delete_index = get_image(event->x() - half, half - event->y());
		//qDebug() << delete_index;
		if (delete_index != -1)
		{
			delete_image(delete_index);
		}
		updateGL();
	}
}

void glview::mouseReleaseEvent(QMouseEvent *event)
{
	//qDebug() << "----------mouserelease---------";
	//qDebug() << event->x() - half << " " << half - event->y();
	if (this->control == 1)		//Draw
	{
		temp.index_x1 = event->x() - half;
		temp.index_y1 = half - event->y();
		//qDebug() << temp.index_x1 << temp.index_y1;
		to_draw.push_back(temp);
		updateGL();
	}
	else if (this->control == 2)		//Move
	{
		move_x2 = event->x() - half;
		move_y2 = half - event->y();
		if (move_index != -1)
		{
			move_image(move_index, move_x1, move_y1, move_x2, move_y2);
		}
		
		updateGL();
		move_index = -1;
	}
}

void glview::mouseMoveEvent(QMouseEvent *event)
{
	if (this->control == 1)		//Draw
	{
		temp.index_x1 = event->x() - half;
		temp.index_y1 = half - event->y();
		//qDebug() << temp.index_x1 << temp.index_y1;
		to_draw.push_back(temp);
		updateGL();
		to_draw.pop_back();
	}
	else if (this->control == 2)		//Move
	{
		move_x2 = event->x() - half;
		move_y2 = half - event->y();
		if (move_index != -1)
		{
			move_image(move_index, move_x1, move_y1, move_x2, move_y2);
		}
		updateGL();
		//move_index = get_image(event->x() - half, half - event->y());
		move_x1 = event->x() - half;
		move_y1 = half - event->y();
		//move_index = -1;
	}
}
//画直线
void glLine(int x1, int y1, int x2, int y2)
{
	glBegin(GL_LINES);
	glColor3ub(black[0], black[1], black[2]);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}
//画弧线
void glArc(double x, double y, double start_angle, double end_angle, double radius, int mode)
{
	//开始绘制曲线
	glBegin(mode);
	//每次画增加的弧度
	double delta_angle = PI / 180;
	//画圆弧
	for (double i = start_angle; i <= end_angle; i += delta_angle)
	{
		//绝对定位加三角函数值
		double vx = x + radius * cos(i);
		double vy = y + radius*sin(i);
		glVertex2d(vx, vy);
	}
	//结束绘画
	glEnd();
}
//画三角形
void glTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int mode) {
	glBegin(mode);
	glVertex2d(x1, y1);
	glVertex2d(x2, y2);
	glVertex2d(x3, y3);
	glEnd();
}
//画填充三角形
void glFillTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color[3]) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3ub(black[0], black[1], black[2]);
	int linewid = 2;
	glLineWidth(linewid);
	glTriangle(x1, y1, x2, y2, x3, y3, GL_LINE_LOOP);
	glColor3ub(color[0], color[1], color[2]);
	glTriangle(x1 + linewid / 2, y1 + linewid / 2, x2 - linewid / 2, y2 + linewid / 2, x3, y3 - linewid / 2, GL_POLYGON);
}
//画矩形
void glRectangle(int x1, int y1, int x2, int y2, int mode) {
	glBegin(mode);
	glVertex2d(x1, y1);
	glVertex2d(x1, y2);
	glVertex2d(x2, y2);
	glVertex2d(x2, y1);
	glEnd();
}
//画填充矩形
void glFillRectangle(int x1, int y1, int x2, int y2, int color[3]) {
	glEnable(GL_LINE_SMOOTH);
	glColor3ub(black[0], black[1], black[2]);
	int linewid = 2;
	glLineWidth(linewid);
	//glPointSize(10);
	glRectangle(x1, y1, x2, y2, GL_LINE_LOOP);
	glColor3ub(color[0], color[1], color[2]);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glRectangle(x1, y1, x2, y2, GL_POLYGON);
}
//画圆角矩形
void glRoundRec(int centerX, int centerY, int width, int height, float cirR, int mode) {
	//二分之PI，一个象限的角度
	float PI_HALF = PI / 2;
	//划分程度,值越大画得越精细
	float divide = 20.0;
	//圆角矩形的坐标
	float tx, ty;
	//画封闭曲线
	glBegin(mode);
	//四个象限不同的操作符
	int opX[4] = { 1,-1,-1,1 };
	int opY[4] = { 1,1,-1,-1 };
	//用来计数，从第一象限到第四象限
	float x = 0;
	//x自增时加的值
	float part = 1 / divide;
	//计算内矩形宽高一半的数值
	int w = width / 2 - cirR;
	int h = height / 2 - cirR;
	//循环画线
	for (x = 0; x<4; x += part) {
		//求出弧度
		float rad = PI_HALF*x;
		//计算坐标值
		tx = cirR*cos(rad) + opX[(int)x] * w + centerX;
		ty = cirR*sin(rad) + opY[(int)x] * h + centerY;
		//传入坐标画线
		glVertex2f(tx, ty);
	}
	//结束画线
	glEnd();
}
//画填充圆角矩形
void glFillRoundRec(int centerX, int centerY, int width, int height, float cirR, int color[3]) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3ub(black[0], black[1], black[2]);
	int linewid = 2;
	glLineWidth(linewid);
	glRoundRec(centerX, centerY, width, height, cirR, GL_LINE_LOOP);
	glColor3ub(color[0], color[1], color[2]);
	glRoundRec(centerX, centerY, width, height, cirR, GL_POLYGON);
}
//画圆
void glCircle(double x, double y, double radius, int mode)
{
	std::cout << x << " " << y << std::endl;
	glArc(x, y, 0, 2 * PI, radius, mode);
}
//画填充圆形
void glFillCircle(double x, double y, double radius, int color[3]) {
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor3ub(black[0], black[1], black[2]);
	int linewid = 2;
	glLineWidth(linewid);
	glCircle(x, y, radius, GL_LINE_LOOP);
	glColor3ub(color[0], color[1], color[2]);
	glCircle(x, y, radius, GL_POLYGON);
}
//重绘
void glview::draw()
{
	for (int i = to_draw.size() - 1; i >= 0 ; i --)
	{
		int x1 = to_draw[i].index_x;
		int y1 = to_draw[i].index_y;
		int x2 = to_draw[i].index_x1;
		int y2 = to_draw[i].index_y1;
		int x3 = 0;
		int y3 = 0;
		int color[3];
		switch (to_draw[i].color)
		{
			case 0:
				for (int j = 0; j < 3; j++)
				{
					color[j] = white[j];
				}
				break;
			case 1:
				for (int j = 0; j < 3; j++)
				{
					color[j] = yellow[j];
				}
				break;
			case 2:
				for (int j = 0; j < 3; j++)
				{
					color[j] = red[j];
				}
				break;
			case 3:
				for (int j = 0; j < 3; j++)
				{
					color[j] = grey[j];
				}
				break;
			case 4:
				for (int j = 0; j < 3; j++)
				{
					color[j] = darkGrey[j];
				}
				break;
		}
		double radius = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
		int centerX = (x1 + x2) / 2;
		int centerY = (y1 + y2) / 2;
		float cirR = std::min(abs(x2 - x1), abs(y2 - y1)) * 1.0 / 8;
		double arcX = x1 + (x2 - x1) * 1.0 / 2;
		double arcY = y1 + (x2 - x1) * 1.0 / 2;
		double arcR = (x2 - x1) * sqrt(2) / 2;
		switch (to_draw[i].type)
		{
			case 1:		//Line
				glLine(x1, y1, x2, y2);
				break;
			case 2:		//Triangle
				x3 = x1 + (x1 - x2);
				y3 = y2;
				//glTriangle(x1, y1, x2, y2, x3, y3, GL_LINE_LOOP);
				glFillTriangle(x1, y1, x2, y2, x3, y3, color);
				break;
			case 3:		//Circle
				//glCircle(x1, y1, radius, GL_LINE_LOOP);
				glFillCircle(x1, y1, radius, color);
				break;
			case 4:		//Rect
				//glRectangle(x1, y1, x2, y2, GL_LINE_LOOP);
				glFillRectangle(x1, y1, x2, y2, color);
				break;
			case 5:		//RoundRect
				//glRoundRec(centerX, centerY, abs(x2 - x1), abs(y2 - y1), cirR, GL_LINE_LOOP);
				glFillRoundRec(centerX, centerY, abs(x2 - x1), abs(y2 - y1), cirR, color);
				break;
			case 6:		//Arc
				glArc(arcX, arcY, 5 * PI / 4, 7 * PI / 4, arcR, GL_LINE_STRIP);
		}
		/*
		if (to_draw[i].type == 1)
		{
			glBegin(GL_LINES);
			glVertex2f(to_draw[i].index_x, to_draw[i].index_y);
			glVertex2f(to_draw[i].index_x1, to_draw[i].index_y1);
			glEnd();
		}
		*/
	}
}