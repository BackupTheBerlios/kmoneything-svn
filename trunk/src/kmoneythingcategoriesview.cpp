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

#include "kmoneythingcategoriesview.h"

#include <qlayout.h>

#include <kiconloader.h>

KMoneyThingCategoriesView::KMoneyThingCategoriesView(QWidget *parent, const char *name, KMoneyThingFile *file)
 : KMoneyThingView(parent, name, file)
{
  setFile(file);
  
  QVBoxLayout *layout = new QVBoxLayout(this, 3);
  mCategories = new KEditListBox(this,0,0,3);
  layout->addWidget(mCategories);
  
  QHBoxLayout *bottomLayout = new QHBoxLayout(this, 2);
  layout->addItem(bottomLayout);
    
  QSpacerItem *spacer = new QSpacerItem(0,0, QSizePolicy::Expanding, QSizePolicy::Minimum);
  bottomLayout->addItem(spacer);
  
  mApply = new KPushButton(SmallIconSet("ok"), i18n("&Apply"), this);
  connect(mApply, SIGNAL(clicked()), this, SLOT(slotApply()));
  bottomLayout->add(mApply);
}


KMoneyThingCategoriesView::~KMoneyThingCategoriesView()
{
}


#include "kmoneythingcategoriesview.moc"
