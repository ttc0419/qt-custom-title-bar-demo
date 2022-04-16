#include "MainWidget.h"
#include "./ui_MainWidget.h"

#include <QWindow>
#include <QMouseEvent>

MainWidget::MainWidget(QWidget *parent) : QWidget(parent, FramelessWindowHint), ui(new Ui::MainWidget)
{
	ui->setupUi(this);
	this->setAttribute(WA_Hover);
}

MainWidget::~MainWidget()
{
	delete ui;
}

void MainWidget::resizeOrMove(const QPointF &p)
{
	Edges edges;
	if (p.x() > width() - RESIZE_BORDER_SIZE)
		edges |= RightEdge;
	if (p.x() < RESIZE_BORDER_SIZE)
		edges |= LeftEdge;
	if (p.y() < RESIZE_BORDER_SIZE)
		edges |= TopEdge;
	if (p.y() > height() - RESIZE_BORDER_SIZE)
		edges |= BottomEdge;

	if (edges != 0) {
		/* Resize the window if the event is triggered inside the borders area */
		if (this->windowHandle()->startSystemResize(edges))
			qInfo() << "[Info] startSystemResize() is supported";
		else
			qInfo() << "[Info] startSystemResize() is NOT supported";
	} else if (p.x() > RESIZE_BORDER_SIZE && p.x() <= width() - RESIZE_BORDER_SIZE && p.y() >= RESIZE_BORDER_SIZE && p.y() <= TITLE_BAR_HEIGHT + RESIZE_BORDER_SIZE) {
		/* Move the window if the event is triggered inside the title bar area */
		if (this->windowHandle()->startSystemMove())
			qInfo() << "[Info] startSystemMove() is supported";
		else
			qInfo() << "startSystemMove() is NOT supported";
	}
}

bool MainWidget::event(QEvent *event)
{
	switch (event->type()) {
		case QEvent::HoverMove:
			changeCursorShape(static_cast<QHoverEvent *>(event)->position());
			return true;
		case QEvent::MouseButtonPress:
			/* Mouse press event for mouse click */
			resizeOrMove(static_cast<QMouseEvent *>(event)->position());
			return true;
		case QEvent::TouchBegin:
			/* Touch begin event for tocuch screen */
			resizeOrMove(static_cast<QTouchEvent *>(event)->points().first().position());
			return true;
		case QEvent::TouchUpdate:
			/* Touch update event for tocuch screen */
			resizeOrMove(static_cast<QTouchEvent *>(event)->points().first().position());
			return true;
		case QEvent::TouchEnd:
			/* Touch end event for tocuch screen */
			return true;
		default:
			return QWidget::event(event);
	}
}

void MainWidget::on_titleBarMinimizePushButton_released()
{
	showMinimized();
}

void MainWidget::on_titleBarMaximizePushButton_released()
{
	showMaximized();
}

void MainWidget::on_titleBarClosePushButton_released()
{
	close();
}

void MainWidget::changeCursorShape(const QPointF &p)
{
	if (p.x() < RESIZE_BORDER_SIZE && p.y() < RESIZE_BORDER_SIZE || p.x() >= width() - RESIZE_BORDER_SIZE && p.y() >= height() - RESIZE_BORDER_SIZE) {
		/* Top left or bottom right corner */
		if (this->cursor().shape() != CursorShape::SizeFDiagCursor)
			this->setCursor(QCursor(CursorShape::SizeFDiagCursor));
	} else if (p.x() >= width() - RESIZE_BORDER_SIZE && p.y() < RESIZE_BORDER_SIZE || p.x() < RESIZE_BORDER_SIZE && p.y() >= height() - RESIZE_BORDER_SIZE) {
		/* Top right or bottom left corner */
		if (this->cursor().shape() != CursorShape::SizeBDiagCursor)
			this->setCursor(QCursor(CursorShape::SizeBDiagCursor));
	} else if (p.x() < RESIZE_BORDER_SIZE || p.x() >= width() - RESIZE_BORDER_SIZE) {
		/* Left or right edge */
		if (this->cursor().shape() != CursorShape::SizeHorCursor)
			this->setCursor(QCursor(CursorShape::SizeHorCursor));
	} else if (p.y() < RESIZE_BORDER_SIZE || p.y() >= height() - RESIZE_BORDER_SIZE) {
		/* Top or bottom edge */
		if (this->cursor().shape() != CursorShape::SizeVerCursor)
			this->setCursor(QCursor(CursorShape::SizeVerCursor));
	}  else {
		/* Content area */
		if (this->cursor().shape() != CursorShape::ArrowCursor)
			this->setCursor(QCursor(CursorShape::ArrowCursor));
	}
}
