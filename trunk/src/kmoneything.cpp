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
 
#include "kmoneything.h"
#include "kmoneythingmainwidget.h"

#include <kstatusbar.h>
#include <kmenubar.h>
#include <kaction.h>
#include <kpopupmenu.h>
#include <kmainwindow.h>
#include <kmessagebox.h>
#include <klocale.h>

KMoneyThing::KMoneyThing()
    : KMainWindow( 0, "KMoneyThing" )
{
  toolBar();
  menuBar();
  statusBar();
  
  setAutoSaveSettings();
  
  mainWidget = new KMoneyThingMainWidget(this);
  connect(mainWidget, SIGNAL(setStatus(const QString& )), this, SLOT(slotSetStatus(const QString& )));
  setCentralWidget(mainWidget);
  
  setupActions();
  statusBar()->message(i18n("Ready."));
}

void KMoneyThing::slotSearch()
{
  mainWidget->activatePage(KMoneyThingMainWidget::findPage);
}

void KMoneyThing::slotUnimplemented()
{
  KMessageBox::sorry(this, i18n("Sorry, this feature is not implemented yet."));
}

void KMoneyThing::setupActions()
{
  toolBar()->setText(i18n("Main Toolbar"));  
  KPopupMenu *fileMenu = new KPopupMenu;
  
  mOpenNewAction = KStdAction::openNew(this, SLOT(slotUnimplemented()), actionCollection());
  mOpenNewAction->plug(fileMenu);
  mOpenNewAction->plug(toolBar());
  
  mOpenAction = KStdAction::open(mainWidget, SLOT(slotOpen()), actionCollection());
  mOpenAction->plug(fileMenu);
  mOpenAction->plug(toolBar());
  
  mOpenRecentAction = KStdAction::openRecent(this, SLOT(slotUnimplemented()), actionCollection());
  mOpenRecentAction->plug(fileMenu);
  
  fileMenu->insertSeparator();
  
  mSaveAction = KStdAction::save(mainWidget, SLOT(slotSave()), actionCollection());
  mSaveAction->plug(fileMenu);
  mSaveAction->plug(toolBar());
  
  mSaveAsAction = KStdAction::saveAs(mainWidget, SLOT(slotSaveAs()), actionCollection());
  mSaveAsAction->plug(fileMenu);
  mSaveAsAction->plug(toolBar());
  
  fileMenu->insertSeparator();
  
  mCloseAction = KStdAction::close(this, SLOT(slotUnimplemented()), actionCollection());
  mCloseAction->plug(fileMenu);
  mCloseAction->plug(toolBar());
  
  fileMenu->insertSeparator();
  
  mQuitAction = KStdAction::quit(this, SLOT(slotUnimplemented()), actionCollection());
  mQuitAction->plug(fileMenu);
    
  menuBar()->insertItem(i18n("&File"), fileMenu);
  
  KPopupMenu *help = helpMenu();
  menuBar()->insertItem(i18n("&Help"), help);
  
  KStdAction::find(this, SLOT(slotSearch()), actionCollection())->plug(toolBar());
}

void KMoneyThing::slotSetStatus(const QString &status)
{
  statusBar()->message(status);
}

KMoneyThing::~KMoneyThing()
{
}

#include "kmoneything.moc"
