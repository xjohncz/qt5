/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui/QOffscreenSurface>
#include "qeglpbuffer_p.h"
#include "qeglconvenience_p.h"

QT_BEGIN_NAMESPACE

QEGLPbuffer::QEGLPbuffer(EGLDisplay display, const QSurfaceFormat &format, QOffscreenSurface *offscreenSurface)
    : QPlatformOffscreenSurface(offscreenSurface)
    , m_format(format)
    , m_display(display)
    , m_pbuffer(EGL_NO_SURFACE)
{
    EGLConfig config = q_configFromGLFormat(m_display, m_format, false, EGL_PBUFFER_BIT);

    if (config) {
        const EGLint attributes[] = {
            EGL_WIDTH, offscreenSurface->size().width(),
            EGL_HEIGHT, offscreenSurface->size().height(),
            EGL_LARGEST_PBUFFER, EGL_FALSE,
            EGL_NONE
        };

        m_pbuffer = eglCreatePbufferSurface(m_display, config, attributes);

        if (m_pbuffer != EGL_NO_SURFACE)
            m_format = q_glFormatFromConfig(m_display, config);
    }
}

QEGLPbuffer::~QEGLPbuffer()
{
    eglDestroySurface(m_display, m_pbuffer);
}

QT_END_NAMESPACE
