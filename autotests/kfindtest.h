/*
    This file is part of the KDE project
    SPDX-FileCopyrightText: 2004 Arend van Beelen jr. <arend@auton.nl>
    SPDX-FileCopyrightText: 2010 David Faure <faure@kde.org>

    SPDX-License-Identifier: LGPL-2.0-only
*/

#ifndef KFINDTEST_H
#define KFINDTEST_H

#include <QObject>
#include <QStringList>
#include <ktextwidgets_export.h>

class KFind;

class KFindRecorder : public QObject
{
    Q_OBJECT

public:
    explicit KFindRecorder(const QStringList &text)
        : QObject(nullptr)
        , m_find(nullptr)
        , m_text(text)
        , m_line(0)
    {
    }

    void find(const QString &pattern, long options = 0);
    bool findNext(const QString &pattern = QString());

    void changeText(int line, const QString &text);

    const QStringList &hits() const
    {
        return m_hits;
    }
    void clearHits()
    {
        m_hits.clear();
    }

public Q_SLOTS:
    void slotHighlight(const QString &text, int index, int matchedLength);
    void slotHighlight(int id, int index, int matchedLengthlength);

private:
    KFind *m_find;
    QStringList m_text;
    int m_line;
    QStringList m_hits;
};

class TestKFind : public QObject
{
    Q_OBJECT

public:
    TestKFind();

private Q_SLOTS:

#if KTEXTWIDGETS_BUILD_DEPRECATED_SINCE(5, 70)
    void testStaticFindString_data();
    void testStaticFindString();
#endif
    void testStaticFindRegexp_data();
    void testStaticFindRegexp();

    void testSimpleSearch();
    void testSimpleRegexp();

#if KTEXTWIDGETS_BUILD_DEPRECATED_SINCE(5, 70)
    void testLineBeginRegexp();
#endif

    void testLineBeginRegularExpression();
    void testFindIncremental();
    void testFindIncrementalDynamic();

private:
    QString m_text;
};

#endif
