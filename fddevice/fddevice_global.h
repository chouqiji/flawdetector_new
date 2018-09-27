#ifndef FDDEVICE_GLOBAL_H
#define FDDEVICE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FDDEVICE_LIBRARY)
#  define FDDEVICESHARED_EXPORT Q_DECL_EXPORT
#else
#  define FDDEVICESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FDDEVICE_GLOBAL_H
