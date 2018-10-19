#ifndef DEVICEARG_VIEWPORT_H
#define DEVICEARG_VIEWPORT_H

#include <QObject>

namespace DeviceArg {

class Signals : public QObject {
    Q_OBJECT
signals:
    void nameChanged();
    void valueChanged();
    void unitChanged();
    void argChanged(const QString &keyType, const QVariant &value);
    void committed(const QVariant &value);
};

class ViewPort {
public:
    virtual QVariant value() const = 0;
    virtual QString displayedName() const = 0;
    virtual QString displayedUnit() const = 0;
    virtual ~ViewPort() = default;

    template <typename Func1, typename Func2>
    QMetaObject::Connection connect(Func1 signal, Func2 method)
    {
        return QObject::connect(&mSignal, std::forward<Func1>(signal), std::forward<Func2>(method));
    }
    template <typename Func1, typename Func2>
    QMetaObject::Connection connect(Func1 signal, const QObject* context, Func2 method)
    {
        return QObject::connect(&mSignal, std::forward<Func1>(signal), std::forward<const QObject*>(context), std::forward<Func2>(method));
    }
    template <typename Func1, typename Func2>
    QMetaObject::Connection connect(Func1 signal, const typename QtPrivate::FunctionPointer<Func2>::Object *receiver, Func2 slot)
    {
        return QObject::connect(&mSignal, std::forward<Func1>(signal), std::forward<decltype(receiver)>(receiver), std::forward<Func2>(slot));
    }
    template <typename Func1, typename Func2>
    QMetaObject::Connection connect(Func1 signal, const QObject *receiver, Func2 method, Qt::ConnectionType type)
    {
        return QObject::connect(&mSignal, std::forward<Func1>(signal), std::forward<const QObject *>(receiver), std::forward<Func2>(method), type);
    }

protected:
    Signals mSignal;
};

}

#endif // DEVICEARG_VIEWPORT_H
