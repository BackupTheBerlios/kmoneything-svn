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

#include "kmoneythingfile.h"

Q_UINT32 KMoneyThingFile::accounts()
{
  return mAccounts.count();
}

void KMoneyThingFile::addAccount(KMoneyThingAccount* account)
{
  if (account == 0) return;
  mAccounts.append(account);
}

bool KMoneyThingFile::delAccount(Q_UINT32 id)
{
  return mAccounts.remove(id);
}

bool KMoneyThingFile::delAccount(KMoneyThingAccount* account)
{
  return mAccounts.remove(account);
}

KMoneyThingAccount* KMoneyThingFile::getAccount(Q_UINT32 id)
{
  return mAccounts.at(id);
}

KLocale* KMoneyThingFile::locale()
{
  return mLocale;
}

void KMoneyThingFile::setLocale(KLocale* locale)
{
  if (locale == 0) return;
  delete mLocale;
  mLocale = locale;
}

QString KMoneyThingFile::name()
{
  return mName;
}

void KMoneyThingFile::setName(QString name)
{
  mName = name;
}

Q_UINT32 KMoneyThingFile::categories()
{
  return mCategories.count();
}

void KMoneyThingFile::addCategory(QString* category)
{
  if (category == 0) return;
  mCategories.append(category);
}

bool KMoneyThingFile::delCategory(Q_UINT32 id)
{
  return mCategories.remove(id);
}

bool KMoneyThingFile::delCategory(QString* category)
{
  return mCategories.remove(category);
}

QString* KMoneyThingFile::getCategory(Q_UINT32 id)
{
  return mCategories.at(id);
}

Q_UINT32 KMoneyThingFile::recurrences()
{
  return mRecurrences.count();
}

void KMoneyThingFile::addRecurrence(KMoneyThingRecurringTransaction* transaction)
{
  if (transaction == 0) return;
  mRecurrences.append(transaction);
}

bool KMoneyThingFile::delRecurrence(Q_UINT32 id)
{
  return mRecurrences.remove(id);
}

bool KMoneyThingFile::delRecurrence(KMoneyThingRecurringTransaction* transaction)
{
  return mRecurrences.remove(transaction);
}

KMoneyThingRecurringTransaction* KMoneyThingFile::getRecurrence(Q_UINT32 id)
{
  return mRecurrences.at(id);
}

KMoneyThingFile::KMoneyThingFile()
{
  mLocale = new KLocale("KMoneyThing");
}

KMoneyThingFile::~KMoneyThingFile()
{
}


