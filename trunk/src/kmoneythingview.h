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

#ifndef KMONEYTHINGVIEW_H
#define KMONEYTHINGVIEW_H

#include "kmoneythingfile.h"

#include <qwidget.h>
#include <qevent.h>

/**
@author Fred Emmott
*/
class KMoneyThingView : public QWidget
{
Q_OBJECT
public:
  virtual void setFile(KMoneyThingFile* file) = 0;
  virtual void undoChanges(){};
  virtual void saveChanges(){};
  KMoneyThingView(QWidget *parent = 0, const char *name = 0, KMoneyThingFile* file = 0);

  ~KMoneyThingView();
public slots:
  virtual void slotRefresh() = 0;
signals:
  void undoOrSave(KMoneyThingView *view);
};

#endif
