/*
  guisupport.cpp

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2016 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "guisupport.h"

#include <core/metaobject.h>
#include <core/metaobjectrepository.h>

#include <common/metatypedeclarations.h>

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
#include <QGuiApplication>
#include <QOpenGLContext>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QScreen>
#include <QWindow>
#endif

#include <QFont>
#include <QPaintDevice>
#include <QPalette>
#include <QPen>

using namespace GammaRay;

GuiSupport::GuiSupport(GammaRay::ProbeInterface* probe, QObject* parent) :
    QObject(parent)
{
    Q_UNUSED(probe);

    registerMetaTypes();
}

void GuiSupport::registerMetaTypes()
{
    MetaObject *mo = Q_NULLPTR;

 #if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    MO_ADD_METAOBJECT1(QGuiApplication, QCoreApplication);
    MO_ADD_PROPERTY_ST(QGuiApplication, Qt::ApplicationState, applicationState);
    MO_ADD_PROPERTY_ST(QGuiApplication, bool, desktopSettingsAware);
    MO_ADD_PROPERTY_RO(QGuiApplication, qreal, devicePixelRatio);
    MO_ADD_PROPERTY_ST(QGuiApplication, QObject*, focusObject);
    MO_ADD_PROPERTY_ST(QGuiApplication, QWindow*, focusWindow);
    MO_ADD_PROPERTY_ST(QGuiApplication, QFont, font);
    MO_ADD_PROPERTY_ST(QGuiApplication, bool, isLeftToRight);
    MO_ADD_PROPERTY_ST(QGuiApplication, bool, isRightToLeft);
    MO_ADD_PROPERTY_ST(QGuiApplication, QPalette, palette);
    MO_ADD_PROPERTY_ST(QGuiApplication, QScreen*, primaryScreen);
#ifndef QT_NO_SESSIONMANAGER
    MO_ADD_PROPERTY_RO(QGuiApplication, bool, isSavingSession);
    MO_ADD_PROPERTY_RO(QGuiApplication, bool, isSessionRestored);
    MO_ADD_PROPERTY_RO(QGuiApplication, QString, sessionId);
    MO_ADD_PROPERTY_RO(QGuiApplication, QString, sessionKey);
#endif
#if QT_VERSION >= QT_VERSION_CHECK(5, 4, 0)
    MO_ADD_PROPERTY_ST(QGuiApplication, QWindowList, allWindows);
    MO_ADD_PROPERTY_ST(QGuiApplication, QWindowList, topLevelWindows);
#endif
#endif

    MO_ADD_METAOBJECT0(QPaintDevice);
    MO_ADD_PROPERTY_RO(QPaintDevice, int, colorCount);
    MO_ADD_PROPERTY_RO(QPaintDevice, int, heightMM);
    MO_ADD_PROPERTY_RO(QPaintDevice, int, logicalDpiX);
    MO_ADD_PROPERTY_RO(QPaintDevice, int, logicalDpiY);
    MO_ADD_PROPERTY_RO(QPaintDevice, bool, paintingActive);
    MO_ADD_PROPERTY_RO(QPaintDevice, int, physicalDpiX);
    MO_ADD_PROPERTY_RO(QPaintDevice, int, physicalDpiY);
    MO_ADD_PROPERTY_RO(QPaintDevice, int, widthMM);

#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    qRegisterMetaType<QScreen*>();

    MO_ADD_METAOBJECT0(QSurface);
    MO_ADD_PROPERTY_RO(QSurface, QSurfaceFormat, format);
    MO_ADD_PROPERTY_RO(QSurface, QSize, size);
    MO_ADD_PROPERTY_RO(QSurface, QSurface::SurfaceClass, surfaceClass);
    MO_ADD_PROPERTY_RO(QSurface, QSurface::SurfaceType, surfaceType);

    MO_ADD_METAOBJECT2(QWindow, QObject, QSurface);
    MO_ADD_PROPERTY_CR(QWindow, QSize, baseSize, setBaseSize);
#ifndef QT_NO_CURSOR
    MO_ADD_PROPERTY_CR(QWindow, QCursor, cursor, setCursor);
#endif
    MO_ADD_PROPERTY_RO(QWindow, qreal, devicePixelRatio);
    MO_ADD_PROPERTY_CR(QWindow, QString, filePath, setFilePath);
    MO_ADD_PROPERTY_RO(QWindow, QObject*, focusObject);
    MO_ADD_PROPERTY_RO(QWindow, QRect, frameGeometry);
    MO_ADD_PROPERTY_RO(QWindow, QMargins, frameMargins);
    MO_ADD_PROPERTY_CR(QWindow, QPoint, framePosition, setFramePosition);
    MO_ADD_PROPERTY_CR(QWindow, QRect, geometry, setGeometry);
    MO_ADD_PROPERTY_CR(QWindow, QIcon, icon, setIcon);
    MO_ADD_PROPERTY_RO(QWindow, bool, isExposed);
    MO_ADD_PROPERTY_RO(QWindow, bool, isTopLevel);
#if QT_VERSION >= QT_VERSION_CHECK(5, 1, 0)
    MO_ADD_PROPERTY_CR(QWindow, QRegion, mask, setMask);
#endif
    MO_ADD_PROPERTY_CR(QWindow, QPoint, position, setPosition);
    MO_ADD_PROPERTY_RO(QWindow, QSurfaceFormat, requestedFormat);
    MO_ADD_PROPERTY_RO(QWindow, QScreen*, screen);
    MO_ADD_PROPERTY_CR(QWindow, QSize, sizeIncrement, setSizeIncrement);
    MO_ADD_PROPERTY   (QWindow, Qt::WindowState, windowState, setWindowState);
    MO_ADD_PROPERTY_RO(QWindow, QWindow*, transientParent);
    MO_ADD_PROPERTY_RO(QWindow, Qt::WindowType, type);

    MO_ADD_METAOBJECT1(QOpenGLShader, QObject);
    MO_ADD_PROPERTY_RO(QOpenGLShader, bool, isCompiled);
    MO_ADD_PROPERTY_RO(QOpenGLShader, QString, log);
    MO_ADD_PROPERTY_RO(QOpenGLShader, uint, shaderId);
    MO_ADD_PROPERTY_RO(QOpenGLShader, QOpenGLShader::ShaderType, shaderType);
    MO_ADD_PROPERTY_RO(QOpenGLShader, QByteArray, sourceCode);

    MO_ADD_METAOBJECT1(QOpenGLShaderProgram, QObject);
    MO_ADD_PROPERTY_RO(QOpenGLShaderProgram, bool, isLinked);
    MO_ADD_PROPERTY_RO(QOpenGLShaderProgram, QString, log);
#if QT_VERSION >= QT_VERSION_CHECK(5, 1, 0)
// FIXME calling this asserts in debug builds of some newer Qt versions
//   MO_ADD_PROPERTY_RO(QOpenGLShaderProgram, int, maxGeometryOutputVertices);
    MO_ADD_PROPERTY   (QOpenGLShaderProgram, int, patchVertexCount, setPatchVertexCount);
#endif
    MO_ADD_PROPERTY_RO(QOpenGLShaderProgram, uint, programId);

    MO_ADD_METAOBJECT1(QOpenGLContext, QObject);
    MO_ADD_PROPERTY_RO(QOpenGLContext, uint, defaultFramebufferObject);
    // crashes if context isn't current
//     MO_ADD_PROPERTY_RO(QOpenGLContext, QSet<QByteArray>, extensions);
    MO_ADD_PROPERTY_RO(QOpenGLContext, QSurfaceFormat, format);
    MO_ADD_PROPERTY_RO(QOpenGLContext, bool, isValid);
    MO_ADD_PROPERTY_RO(QOpenGLContext, QScreen*, screen);
    MO_ADD_PROPERTY_RO(QOpenGLContext, QOpenGLContext*, shareContext);
    MO_ADD_PROPERTY_RO(QOpenGLContext, QOpenGLContextGroup*, shareGroup);
//     MO_ADD_PROPERTY_RO(QOpenGLContext, QSurface*, surface);
#endif
}

GuiSupportFactory::GuiSupportFactory(QObject* parent) :
    QObject(parent)
{
}

QString GuiSupportFactory::name() const
{
    return QString();
}

#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
Q_EXPORT_PLUGIN(GuiSupportFactory)
#endif