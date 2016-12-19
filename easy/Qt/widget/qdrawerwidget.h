#ifndef QDRAWERWIDGET_H
#define QDRAWERWIDGET_H

#include <QWidget>
#include <QColor>
#include <QPainter>
#include <QBrush>

class QDrawerItem: public  QWidget {

    Q_OBJECT
public:
    QDrawerItem(QWidget *parent = nullptr)
        : QWidget(parent)
    {

    }

    void paintEvent(QPaintEvent *event) {
        QPainter p(this);
        p.fillRect(geometry(), QBrush(_backgroundColor));
    }

    void setBackgroundColor(const QColor &color) {
        _backgroundColor = color;
    }
private:
    QColor _backgroundColor;
};

class QDrawerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QDrawerWidget(QWidget *parent = 0);

    void setHeaderSize(const QSize& size);
    int addItem(QDrawerItem *item);
    int indexOf(QDrawerItem *const &item) const;
    int count() const;
    QDrawerItem *item(int index) const;
protected:
    void showEvent(QShowEvent *event);
    bool eventFilter(QObject *watched, QEvent *event);
signals:
    void currentChanged(int);
    void countChanged(int);
public slots:
    void setCurrentIndex(int index);
    void updateItems();
private:
    struct {
        int currentIndex;
        int headerHeight;
        int contentHeight;
        QList<QDrawerItem *> items;
    } ui;
};

#endif // QDRAWERWIDGET_H
