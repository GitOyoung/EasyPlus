#include "qlightboxwidget.h"

#include <QPixmap>
#include <QEvent>
#include <QPaintEvent>
#include <QChildEvent>
#include <QPainter>

QLightBoxWidget::QLightBoxWidget(QWidget* _parent, bool _folowToHeadWidget) :
	QWidget(parent),
	m_isInUpdateSelf(false)
{
	//
	// Родительский виджет должен быть обязательно установлен
	//
	Q_ASSERT_X(parent, "", Q_FUNC_INFO);

	//
	// Если необходимо, делаем родителем самый "старший" виджет
	//
	if (_folowToHeadWidget) {
		while (parent->parentWidget() != 0) {
			parent = parent->parentWidget();
		}
		setParent(parent);
	}

	//
	// Следим за событиями родительского виджета, чтобы
	// иметь возможность перерисовать его, когда изменяется размер и т.п.
	//
	parent->installEventFilter(this);

	//
	// Скрываем виджет
	//
	setVisible(false);
}

bool QLightBoxWidget::eventFilter(QObject* object, QEvent* event)
{
	//
	// Виджету необходимо всегда быть последним ребёнком,
	// чтобы перекрывать остальные виджеты при отображении
	//
	if (event->type() == QEvent::ChildAdded) {
		QChildEvent* childEvent = dynamic_cast<QChildEvent*>(event);
		if (childEvent->child() != this) {
			QWidget* parent = parentWidget();
			setParent(0);
			setParent(parent);
		}
	}

	//
	// Если изменился размер родительского виджета, необходимо
	// перерисовать себя
	//
	if (isVisible()
		&& event->type() == QEvent::Resize) {
		updateSelf();
	}
	return QWidget::eventFilter(object, event);
}

void QLightBoxWidget::paintEvent(QPaintEvent* event)
{
	//
	// Рисуем фон
	//
	QPainter painter(this);
	// ... фото родительского виджета
	painter.drawPixmap(0, 0, width(), height(), m_parentWidgetPixmap);
	// ... накладываем затемнённую область
	painter.setBrush(QBrush(QColor(0, 0, 0, 220)));
	painter.drawRect(0, 0, width(), height());

	//
	// Рисуем всё остальное
	//
	QWidget::paintEvent(event);
}

void QLightBoxWidget::showEvent(QShowEvent* event)
{

	updateSelf();

	QWidget::showEvent(event);
}

void QLightBoxWidget::updateSelf()
{
	if (!_inUpdateSelf) {
		_inUpdateSelf = true;

		{
			//
			// Обновляем отображение
			//
			hide();
			resize(parentWidget()->size());
			_parentWidgetPixmap = grabParentWidgetPixmap();
			show();
		}

		_inUpdateSelf = false;
	}
}

QPixmap QLightBoxWidget::grabParentWidgetPixmap() const
{
	QPixmap parentWidgetPixmap;

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
	parentWidgetPixmap = parentWidget()->grab();
#else
	parentWidgetPixmap = QPixmap::grabWidget(parentWidget());
#endif

	return parentWidgetPixmap;
}
