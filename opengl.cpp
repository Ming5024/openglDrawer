#include "opengl.h"
#include "glview.h"

opengl::opengl(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//ui.scrollAreaWidgetContents->show();
	//ui.widget->show();
	connect(ui.checkBox, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(int)));

	ui.actionSave = new QAction(tr("Save"), this);
	//摄者打开文件的快捷方式  
	ui.actionSave->setShortcut(tr("Ctrl+S"));
	//设置打开文件动作提示信息  
	//ui.actionSave->setStatusTip("Save File");
	//关联打开文件动作的信号和槽  
	connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(fileSaveActionSlot()));

	ui.actionSaveAs = new QAction(tr("Save As"), this);
	//摄者打开文件的快捷方式  
	//ui.actionSave->setShortcut(tr("Ctrl+S"));
	//设置打开文件动作提示信息  
	//ui.actionSave->setStatusTip("Save File");
	//关联打开文件动作的信号和槽  
	connect(ui.actionSaveAs, SIGNAL(triggered()), this, SLOT(fileSaveAsActionSlot()));

	ui.actionLoad = new QAction(tr("Load"), this);
	//摄者打开文件的快捷方式  
	ui.actionLoad->setShortcut(tr("Ctrl+O"));
	//设置打开文件动作提示信息  
	//ui.actionSave->setStatusTip("Open File");
	//关联打开文件动作的信号和槽  
	connect(ui.actionLoad, SIGNAL(triggered()), this, SLOT(fileOpenActionSlot()));

	ui.menuMenu->addAction(ui.actionSave);
	ui.menuMenu->addAction(ui.actionSaveAs);
	ui.menuMenu->addAction(ui.actionLoad);
}

void opengl::fileSaveActionSlot()
{
	qDebug() << "saveslot";
	//QMessageBox::warning(this,tr("提示"),tr("打开文件"),QMessageBox::Yes|QMessageBox::No); 
	if (this->filename.isNull())
	{
		qDebug() << "if";
		saveas();
	}
	else
	{
		qDebug() << "else if";
		qDebug() << this->filename;
		const char* ch;
		QByteArray ba = this->filename.toLatin1();
		ch = ba.data();
		ui.widget->write_out(ch);
	}
}
	

void opengl::fileSaveAsActionSlot()
{
	qDebug() << "save as slot";
	saveas();
}

void opengl::fileOpenActionSlot()
{
	load();
}

void opengl::save()
{
	qDebug() << this->filename;
	const char* ch;
	QByteArray ba = this->filename.toLatin1();
	ch = ba.data();
	ui.widget->write_out(ch);
}

void opengl::saveas()
{
	qDebug() << "enter save as";
	QString file_name = QFileDialog::getSaveFileName(this,
		tr("Save File"),
		"",
		"",
		0);
	this->filename = file_name;
	if (!file_name.isNull())
	{
		//fileName是文件名
		const char* ch;
		QByteArray ba = file_name.toLatin1();
		ch = ba.data();
		ui.widget->write_out(ch);
	}
	else {
		//点的是取消
	}
}

void opengl::load()
{
	QString file_name = QFileDialog::getOpenFileName(this,
		tr("Open File"),
		"",
		"",
		0);
	this->filename = file_name;
	qDebug() << this->filename;
	if (!this->filename.isNull())
	{
		//fileName是文件名
		const char* ch;
		QByteArray ba = this->filename.toLatin1();
		ch = ba.data();
		ui.widget->read_image(ch);
	}
	else {
		//点的是取消
	}
}

void opengl::drawLine()
{
	//qDebug() << "draw begin";
	ui.widget->control = 1;
	ui.widget->type = 1;
}

void opengl::drawTriangle()
{
	ui.widget->control = 1;
	ui.widget->type = 2;
}

void opengl::drawCircle()
{
	ui.widget->control = 1;
	ui.widget->type = 3;
}

void opengl::drawRect()
{
	ui.widget->control = 1;
	ui.widget->type = 4;
}

void opengl::drawRoundRect()
{
	ui.widget->control = 1;
	ui.widget->type = 5;
}

void opengl::drawArc()
{
	ui.widget->control = 1;
	ui.widget->type = 6;
}

void opengl::move()
{
	ui.widget->control = 2;
}

void opengl::deletes()
{
	ui.widget->control = 3;
}

void opengl::white()
{
	ui.widget->color = 0;
}

void opengl::yellow()
{
	ui.widget->color = 1;
}

void opengl::red()
{
	ui.widget->color = 2;
}

void opengl::grey()
{
	ui.widget->color = 3;
}

void opengl::darkgrey()
{
	ui.widget->color = 4;
}

void opengl::onStateChanged(int state)
{
	if (state == Qt::Checked) // "选中"
	{
		ui.widget->robot = true;
		ui.widget->updateGL();
	}
	else // 未选中 - Qt::Unchecked
	{
		ui.widget->robot = false;
		ui.widget->updateGL();
	}
}