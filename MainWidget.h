#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

using namespace Qt;

#define RESIZE_BORDER_SIZE 8
#define TITLE_BAR_HEIGHT 32

class MainWidget : public QWidget
{
	Q_OBJECT

public:
	MainWidget(QWidget *parent = nullptr);
	~MainWidget();

protected:
	void resizeOrMove(const QPointF &p);
	bool event(QEvent *event) override;

private slots:
	void on_titleBarMinimizePushButton_released();
	void on_titleBarMaximizePushButton_released();
	void on_titleBarClosePushButton_released();

private:
	Ui::MainWidget *ui;

	void changeCursorShape(const QPointF &p);
};
#endif // MAINWIDGET_H
