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
#ifndef KMONEYTHINGHOMEVIEW_H
#define KMONEYTHINGHOMEVIEW_H

#include <qwidget.h>

#include <khtml_part.h>
#include <khtmlview.h>

/**
@author Fred Emmott
*/
class KMoneyThingHomeView : public QWidget
{
Q_OBJECT
private:
  KHTMLPart *khtmlPart;
public:
  KMoneyThingHomeView(QWidget *parent = 0, const char *name = 0);

  ~KMoneyThingHomeView();
};

#endif
