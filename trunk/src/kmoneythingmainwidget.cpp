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
 
#include "kmoneythingmainwidget.h"

#include <qlayout.h>

#include <kiconloader.h>
#include <klocale.h>

KMoneyThingMainWidget::KMoneyThingMainWidget(QWidget *parent, const char *name, int face)
 : KJanusWidget(parent, name, face)
{
  QVBoxLayout *layout;

  homeFrame = addPage(i18n("Home"), i18n("Home"), DesktopIcon("folder_home"));
  layout = new QVBoxLayout(homeFrame);
  homeView = new KMoneyThingHomeView(homeFrame);
  layout->addWidget(homeView);
  
  accountsFrame = addPage(i18n("Accounts"), i18n("Accounts"), DesktopIcon("identity"));
  calendarFrame = addPage(i18n("Schedule"), i18n("Schedule"), DesktopIcon("today"));
  categoriesFrame = addPage(i18n("Categories"), i18n("Categories"), DesktopIcon("folder"));
  findFrame = addPage(i18n("Find"), i18n("Find"), DesktopIcon("find"));
  transactionsFrame = addPage(i18n("Transactions"), i18n("Transactions"), DesktopIcon("view_text"));
}

void KMoneyThingMainWidget::activatePage(KMoneyThingMainWidget::Page page)
{
  switch(page)
  {
    case homePage:
      showPage(pageIndex(homeFrame));
      break;
    case accountsPage:
      showPage(pageIndex(accountsFrame));
      break;
    case calendarPage:
      showPage(pageIndex(calendarFrame));
      break;
    case categoriesPage:
      showPage(pageIndex(categoriesFrame));
      break;
    case findPage:
      showPage(pageIndex(findFrame));
      break;
    case transactionsPage:
      showPage(pageIndex(transactionsFrame));
      break;
  }
}

KMoneyThingMainWidget::~KMoneyThingMainWidget()
{
}

#include "kmoneythingmainwidget.moc"
