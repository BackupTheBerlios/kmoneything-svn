/***************************************************************************
 *   Copyright (C) 2004 by Fred Emmott                                     *
 *   mail@fredemmott.co.uk                                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
 
// $Id$
 
#ifndef KMONEYTHINGMAINWIDGET_H
#define KMONEYTHINGMAINWIDGET_H

#include "kmoneythinghomeview.h"
#include "kmoneythingaccountsview.h"
#include "kmoneythingfile.h"

#include <qframe.h>
#include <kjanuswidget.h>

/**
@author Fred Emmott
*/
class KMoneyThingMainWidget : public KJanusWidget
{
  Q_OBJECT
public:
  enum Page{
    homePage,
    accountsPage,
    calendarPage,
    categoriesPage,
    findPage,
    transactionsPage
  };
private:
  QFrame* homeFrame;
  KMoneyThingHomeView* homeView;
  QFrame* accountsFrame;
  KMoneyThingAccountsView* accountsView;
  QFrame* calendarFrame;
  QFrame* categoriesFrame;
  QFrame* findFrame;
  QFrame* transactionsFrame;
  KMoneyThingFile* mCurrentFile;
  void setupPages();
public:
  void activatePage(KMoneyThingMainWidget::Page page);
  KMoneyThingMainWidget(QWidget *parent=0, const char *name=0, int face = KJanusWidget::IconList);

  ~KMoneyThingMainWidget();
public slots:
  void slotSave();
  void slotOpen();
signals:
  void signalRefresh();
};

#endif
