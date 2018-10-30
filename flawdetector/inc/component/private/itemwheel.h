#ifndef COMPONENT_ITEMWHEEL_H
#define COMPONENT_ITEMWHEEL_H

#include <QScrollArea>

namespace Component {

class ItemWheel : public QScrollArea
{
    Q_OBJECT
public:
    explicit ItemWheel(int viewportSize, QWidget *parent = nullptr);
    ~ItemWheel() override;
    void selectNext();
    void selectPrev();
    int currentIndex() const;
    void setIndex(int index);
    void setList(const QStringList & list);

protected:
    virtual void showEvent(QShowEvent *) override;

signals:
    void currentTextChanged(const QString&);

private:
    class Impl;
    QScopedPointer<Impl> pImpl;
};

}

#endif // COMPONENT_ITEMWHEEL_H
