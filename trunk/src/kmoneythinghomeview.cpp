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
 
#include "kmoneythinghomeview.h"

#include <qlayout.h>

#include <khtml_part.h>
#include <khtmlview.h>
#include <klocale.h>

KMoneyThingHomeView::KMoneyThingHomeView(QWidget *parent, const char *name)
 : QWidget(parent, name)
{
  QHBoxLayout *layout = new QHBoxLayout(this);
  khtmlPart = new KHTMLPart(this);
  khtmlPart->begin();
  khtmlPart->write("<html><body><h1>");
  khtmlPart->write(i18n("Welcome to KMoneyThing") + "<br>pre0.1: $Rev$");
  khtmlPart->write("</h1><hr><p>");
  khtmlPart->write(i18n("This application is still under development, and is not yet suitable for general use."));
  khtmlPart->write("</p></body></html>");
  khtmlPart->end();
  layout->addWidget(khtmlPart->view());
}


KMoneyThingHomeView::~KMoneyThingHomeView()
{
}


#include "kmoneythinghomeview.moc"
