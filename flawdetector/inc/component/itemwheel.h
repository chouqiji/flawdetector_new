#ifndef COMPONENT_ITEMWHEEL_H
#define COMPONENT_ITEMWHEEL_H

#include <QWidget>

class QLabel;

namespace Component {

class ItemWheel : public QWidget
{
    Q_OBJECT
public:
    explicit ItemWheel(int count, QWidget *parent = nullptr);
    ~ItemWheel();
    void selectNext();
    void selectPrev();
    int currentIndex();
    void setIndex(int index);
    void setList(const QStringList & list);

signals:
    void currentTextChanged(const QString&);

private:
    class ImplItemWheel;
    QScopedPointer<ImplItemWheel> pImpl;
};

}

#endif // COMPONENT_ITEMWHEEL_H
