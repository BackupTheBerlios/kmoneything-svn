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

#ifndef _KMONEYTHING_H_
#define _KMONEYTHING_H_

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "kmoneythingmainwidget.h"

#include <kmainwindow.h>
#include <kaction.h>

/**
 * @short Application Main Window
 * @author Fred Emmott <mail@fredemmott.co.uk>
 * @version 0.1
 */
class KMoneyThing : public KMainWindow
{
  Q_OBJECT
private:
  KMoneyThingMainWidget *mainWidget;
  KAction *mOpenNewAction;
  KAction *mOpenAction;
  KAction *mOpenRecentAction;
  KAction *mSaveAction;
  KAction *mSaveAsAction;
  KAction *mCloseAction;
  KAction *mQuitAction;
  void setupActions();
public:
  /**
    * Default Constructor
    */
  KMoneyThing();

  /**
    * Default Destructor
    */
  virtual ~KMoneyThing();
public slots:
  void slotSearch();
  void slotUnimplemented();
  void slotSetStatus(const QString &status);
};

#endif // _KMONEYTHING_H_
