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
#include <qstring.h>

#include <kfiledialog.h>
#include <kmessagebox.h>
#include <kiconloader.h>
#include <klocale.h>
#include <kurl.h>
#include <ktempfile.h>
#include <kio/netaccess.h>

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
  connect(homeView, SIGNAL(undoOrSave(KMoneyThingView* )), this, SLOT(slotUndoOrSave(KMoneyThingView* )));
  
  accountsFrame = addPage(i18n("Accounts"), i18n("Accounts"), DesktopIcon("identity"));
  layout = new QVBoxLayout(accountsFrame);
  accountsView = new KMoneyThingAccountsView(accountsFrame, 0, mCurrentFile);
  layout->addWidget(accountsView);
  connect(this, SIGNAL(signalRefresh()), accountsView, SLOT(slotRefresh()));
  connect(accountsView, SIGNAL(undoOrSave(KMoneyThingView* )), this, SLOT(slotUndoOrSave(KMoneyThingView* )));
  
  calendarFrame = addPage(i18n("Schedule"), i18n("Schedule"), DesktopIcon("today"));
  
  categoriesFrame = addPage(i18n("Categories"), i18n("Categories"), DesktopIcon("folder"));
  layout = new QVBoxLayout(categoriesFrame);
  categoriesView = new KMoneyThingCategoriesView(categoriesFrame, 0, mCurrentFile);
  layout->addWidget(categoriesView);
  connect(this, SIGNAL(signalRefresh()), categoriesView, SLOT(slotRefresh()));
  connect(categoriesView, SIGNAL(undoOrSave(KMoneyThingView* )), this, SLOT(slotUndoOrSave(KMoneyThingView* )));
  
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
  KTempFile temp;
  QString fileName = mCurrentFile->kurl().path();
  
  if (fileName == "")
  {
    slotSaveAs();
    return;
  }
  
  if (!mCurrentFile->kurl().isLocalFile())
  {
    fileName = temp.name();
  }
  
  setStatus(i18n("Saving file..."));
  QByteArray dump = qCompress(mCurrentFile->dump());
  QFile file(fileName);
  file.open(IO_WriteOnly);
  QDataStream stream(&file);
  stream << (QString) "KMoneyThingFile" << dump;
  file.close();
  
  if (!mCurrentFile->kurl().isLocalFile())
  {
    setStatus(i18n("Uploading file..."));
    if (!KIO::NetAccess::upload(fileName, mCurrentFile->kurl(), this))
      KMessageBox::error(this, i18n("Failed to upload file."));
  }
  
  temp.unlink();
  
  setStatus(i18n("Ready."));
}

void KMoneyThingMainWidget::slotSaveAs()
{
  KURL kurl = KFileDialog::getSaveURL(0, i18n("*.kmt|KMoneyThing files (*.kmt)"), this);
  if (kurl.path() == "")
    return;
  mCurrentFile->setKurl(kurl);
  slotSave();
}

void KMoneyThingMainWidget::slotOpen()
{
  QString fileName;
  KURL kurl = KFileDialog::getOpenURL(0, i18n("*.kmt|KMoneyThing files (*.kmt)"), this);
  if (kurl.path() == "")
    return;
  mCurrentFile->setKurl(kurl);

  setStatus(i18n("Downloading file..."));
  KIO::NetAccess::download(kurl, fileName, this);
  
  setStatus(i18n("Reading file..."));
  QByteArray dump;
  QString temp;
  QFile file(fileName);
  file.open(IO_ReadOnly);
  QDataStream stream(&file);
  
  stream >> temp;
  if (temp != "KMoneyThingFile")
  {
    KMessageBox::error(this, i18n("Unknown file format: %1").arg(temp));
    file.close();
    KIO::NetAccess::removeTempFile(fileName);
    setStatus(i18n("Ready."));
    return;
  }
  stream >> dump;
  file.close();
  KIO::NetAccess::removeTempFile(fileName);
  
  setStatus(i18n("Parsing file..."));
  mCurrentFile->loadDump(qUncompress(dump));
  setStatus(i18n("Ready."));
  
  emit signalRefresh();
}

void KMoneyThingMainWidget::slotUndoOrSave(KMoneyThingView *view)
{
  int res = KMessageBox::warningYesNo(this, i18n(
    "There are unapplied changes in the active page.\n"
    "Do you want to apply the changes, or discard them?"), i18n("Unapplied Changes"), i18n("&Apply"), i18n("&Discard"));
  switch (res)
  {
    case KMessageBox::Yes:
      view->saveChanges();
      break;
    case KMessageBox::No:
      view->undoChanges();
      break;
  }
}

KMoneyThingMainWidget::~KMoneyThingMainWidget()
{
}

#include "kmoneythingmainwidget.moc"
