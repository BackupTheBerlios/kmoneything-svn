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
#include <qfile.h>
#include <qcstring.h>
#include <qlayout.h>

#include <kmessagebox.h>
#include <kiconloader.h>
#include <klocale.h>

KMoneyThingMainWidget::KMoneyThingMainWidget(QWidget *parent, const char *name, int face)
 : KJanusWidget(parent, name, face)
{
  mCurrentFile = new KMoneyThingFile();
  setupPages();
}

void KMoneyThingMainWidget::setupPages()
{
  QVBoxLayout *layout;

  homeFrame = addPage(i18n("Home"), i18n("Home"), DesktopIcon("folder_home"));
  layout = new QVBoxLayout(homeFrame);
  homeView = new KMoneyThingHomeView(homeFrame, 0, mCurrentFile);
  layout->addWidget(homeView);
  connect(this, SIGNAL(signalRefresh()), homeView, SLOT(slotRefresh()));
  
  accountsFrame = addPage(i18n("Accounts"), i18n("Accounts"), DesktopIcon("identity"));
  layout = new QVBoxLayout(accountsFrame);
  accountsView = new KMoneyThingAccountsView(accountsFrame, 0, mCurrentFile);
  layout->addWidget(accountsView);
  connect(this, SIGNAL(signalRefresh()), accountsView, SLOT(slotRefresh()));
  
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

void KMoneyThingMainWidget::slotSave()
{
  // TODO: Write this properly
  QByteArray dump = mCurrentFile->dump();
  QFile file("/tmp/foo");
  file.open(IO_WriteOnly);
  QDataStream stream(&file);
  stream << (QString) "KMoneyThingFile" << dump;
  file.close();
  KMessageBox::information(this, "Written to /tmp/foo");
}

void KMoneyThingMainWidget::slotOpen()
{
  //TODO: Write this properly
  QByteArray dump;
  QString temp;
  QFile file("/tmp/foo");
  file.open(IO_ReadOnly);
  QDataStream stream(&file);
  
  stream >> temp;
  if (temp != "KMoneyThingFile")
  {
    KMessageBox::error(this, i18n("Unknown file format: %1").arg(temp));
    return;
  }
  stream >> dump;
  file.close();
  mCurrentFile->loadDump(dump);
  KMessageBox::information(this, "Loaded from /tmp/foo");
  
  emit signalRefresh();
}
KMoneyThingMainWidget::~KMoneyThingMainWidget()
{
}

#include "kmoneythingmainwidget.moc"
