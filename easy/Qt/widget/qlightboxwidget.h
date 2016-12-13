#ifndef QLIGHTBOXWIDGET_H
#define QLIGHTBOXWIDGET_H

#include <QWidget>


/**
 * @brief Класс перекрытия
 */
class QLightBoxWidget : public QWidget
{
	Q_OBJECT

public:
	explicit QLightBoxWidget(QWidget* parent, bool folowToHeadWidget = false);

protected:
	/**
	 * @brief Переопределяется для отслеживания собитий родительского виджета
	 */
	bool eventFilter(QObject* object, QEvent* event);

	/**
	 * @brief Переопределяется для того, чтобы эмитировать эффект перекрытия
	 */
	void paintEvent(QPaintEvent* event);

	/**
	 * @brief Переопределяется для того, чтобы перед отображением настроить внешний вид
	 */
	void showEvent(QShowEvent* event);

private:
	/**
	 * @brief Обновить размер и картинку фона
	 */
	void updateSelf();

	/**
	 * @brief Разрешает конфликт рекурсивного обновления
	 */
	bool _inUpdateSelf;

	/**
	 * @brief Обновить картинку фона
	 */
	QPixmap grabParentWidgetPixmap() const;

	/**
	 * @brief Картинка фона
	 */
	QPixmap _parentWidgetPixmap;
};

#endif // QLIGHTBOXWIDGET_H
