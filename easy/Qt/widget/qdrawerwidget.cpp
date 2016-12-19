#include "qdrawerwidget.h"

#include <QList>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

QDrawerWidget::QDrawerWidget(QWidget *parent)
    : QWidget(parent)
    , ui({0, 40, 160})
{
//    connect(this, SIGNAL(countChanged(int)), SLOT(updateItems()));
    connect(this, SIGNAL(currentChanged(int)), SLOT(setCurrentIndex(int)));
}

int QDrawerWidget::addItem(QDrawerItem *item)
{
    int length = 0;
    item->setParent(this);
    item->installEventFilter(this);
    ui.items.append(item);
    length = ui.items.length();
    emit countChanged(length);
    return length;
}

void QDrawerWidget::setCurrentIndex(int index)
{
    ui.currentIndex = index;
    updateItems();
}

int QDrawerWidget::count() const
{
    return ui.items.length();
}

int QDrawerWidget::indexOf(QDrawerItem * const &item) const
{
    return ui.items.indexOf(item);
}

void QDrawerWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    int y = 0;
    int topCount = ui.currentIndex + 1;

    auto geo = geometry();

    auto h = ui.headerHeight;

    for(int i = 0; i < topCount; ++i) {
        auto item = this->ui.items.at(i);
        geo.setY(y);
        geo.setHeight(i == ui.currentIndex ? h + ui.contentHeight: h);
        item->setGeometry(geo);
        y += ui.headerHeight;
    }
    int cnt = count();
    y  = height() - (cnt - topCount) * ui.headerHeight;

    for(int i = topCount; i < cnt; ++i) {
        auto item = this->ui.items.at(i);
        geo.setY(y);
        geo.setHeight(h);
        item->setGeometry(geo);
        y += ui.headerHeight;
    }

}

void QDrawerWidget::updateItems()
{
    int y = 0;
    int topCount = ui.currentIndex + 1;
    auto animationCreate = [this, &y](int i) {
        auto item = this->ui.items.at(i);
        auto geo = item->geometry();
        if(geo.y() != y) {
            auto animation = new QPropertyAnimation(item, "geometry");
            animation->setStartValue(geo);
            geo.setY(y);
            if(i == ui.currentIndex) {
                geo.setHeight(ui.headerHeight + ui.contentHeight);
            } else {
                geo.setHeight(ui.headerHeight);
            }
            animation->setEndValue(geo);
           return animation;
        }
        return (QPropertyAnimation *)nullptr;
    };

    auto animationGroup = new QParallelAnimationGroup(this);
    for(int i = 0; i < topCount; ++i) {
        auto animation = animationCreate(i);
        if(animation)  animationGroup->addAnimation(animation);
        y += ui.headerHeight;
    }

    y  = height() - (count() - topCount) * ui.headerHeight;

    for(int i = topCount, cnt = count(); i < cnt; ++i) {
        auto animation = animationCreate(i);
        if(animation)  animationGroup->addAnimation(animation);
        y += ui.headerHeight;
    }
    animationGroup->start(QPropertyAnimation::DeleteWhenStopped);
}

bool QDrawerWidget::eventFilter(QObject *watched, QEvent *event)
{
    QList<QEvent::Type> events;
    events.append(QEvent::MouseButtonPress);
    events.append(QEvent::MouseButtonRelease);
    if(events.contains(event->type())) {

        auto item = qobject_cast<QDrawerItem *>(watched);
        if(item) {
            int index = indexOf(item);
            emit currentChanged(index);
            return true;
        }
    }

    return false;
}
