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

#include <kaction.h>
#include <kmenubar.h>
#include <kpopupmenu.h>
#include <kmainwindow.h>
#include <kmessagebox.h>
#include <klocale.h>

KMoneyThing::KMoneyThing()
    : KMainWindow( 0, "KMoneyThing" )
{
  KMenuBar *menu = menuBar();
  
  KPopupMenu *fileMenu = new KPopupMenu;
  
  KStdAction::openNew(this, SLOT(slotUnimplemented()), actionCollection())->plug(fileMenu);
  KStdAction::open(this, SLOT(slotUnimplemented()), actionCollection())->plug(fileMenu);
  KStdAction::openRecent(this, SLOT(slotUnimplemented()), actionCollection())->plug(fileMenu);
  fileMenu->insertSeparator();
  KStdAction::save(this, SLOT(slotUnimplemented()), actionCollection())->plug(fileMenu);
  KStdAction::saveAs(this, SLOT(slotUnimplemented()), actionCollection())->plug(fileMenu);
  fileMenu->insertSeparator();
  KStdAction::close(this, SLOT(slotUnimplemented()), actionCollection())->plug(fileMenu);
  fileMenu->insertSeparator();
  KStdAction::quit(this, SLOT(slotUnimplemented()), actionCollection())->plug(fileMenu);
    
  menu->insertItem(i18n("&File"), fileMenu);
  
  KPopupMenu *help = helpMenu();
  menu->insertItem(i18n("&Help"), help);  
  setAutoSaveSettings();
  
  KMoneyThingMainWidget *mainWidget = new KMoneyThingMainWidget(this);
  setCentralWidget(mainWidget);
}

void KMoneyThing::slotUnimplemented()
{
  KMessageBox::sorry(this, i18n("Sorry, this feature is not implemented yet."), "KMoneyThing");
}

KMoneyThing::~KMoneyThing()
{
}

#include "kmoneything.moc"
