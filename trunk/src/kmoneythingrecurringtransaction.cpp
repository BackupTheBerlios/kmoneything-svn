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

#include "kmoneythingrecurringtransaction.h"

#include <kmessagebox.h>
#include <klocale.h>

KMoneyThingRecurringTransaction::Recurrence KMoneyThingRecurringTransaction::recurrence()
{
  return mRecurrence;
}

void KMoneyThingRecurringTransaction::setRecurrency(KMoneyThingRecurringTransaction::Recurrence newVal)
{
  mRecurrence = newVal;
}

bool KMoneyThingRecurringTransaction::isDayOn(unsigned char day)
{
  if (day > 6) return false;
  return mDaysOn[day];
}

void KMoneyThingRecurringTransaction::setDayOn(unsigned char day, bool on)
{
  if (day > 6) return;
  mDaysOn[day] = on;
}

unsigned short KMoneyThingRecurringTransaction::xDays()
{
  return mXDays;
}

void KMoneyThingRecurringTransaction::setXDays(unsigned short days)
{
  mXDays = days;
}

QDate KMoneyThingRecurringTransaction::firstDate()
{
  return mFirstDate;
}

void KMoneyThingRecurringTransaction::setFirstDate(QDate date)
{
  mFirstDate = date;
}

bool KMoneyThingRecurringTransaction::isDateOn(QDate date)
{
  if (mFirstDate.daysTo(date) < 0) return false;
  
  switch (mRecurrence)
  {
    case recDaily:
      return true;
    case recWeekly:
      if (mFirstDate.dayOfWeek() == date.dayOfWeek()) return true;
      return false;
    case recMonthly:
      if (mFirstDate.day() == date.day()) return true;
      return false;
    case recYearly:
      if ((mFirstDate.day() == date.day()) && (mFirstDate.month() == date.month())) return true;
      return false;
    case recXDays:
      if (mFirstDate.daysTo(date) % mXDays == 0) return true;
      return false;
    case recSomeDays:
      if (isDayOn(date.dayOfWeek() - 1)) return true;
      return false;
    case recSpecialMonthly:
      if (mFirstDate.dayOfWeek() != date.dayOfWeek()) return false;
      // Work out what week of month it's supposed to be in (0 -> 3)
      if (((mFirstDate.day() - (mFirstDate.day() % 7)) / 7) != ((date.day() - (date.day() % 7)) / 7)) return false;
      return true;
    default:
      KMessageBox::error(0, i18n("Unrecognized recurrence type: %1").arg(mRecurrence));
      return false;
  }
}

KMoneyThingRecurringTransaction::KMoneyThingRecurringTransaction()
 : KMoneyThingTransaction()
{
}


KMoneyThingRecurringTransaction::~KMoneyThingRecurringTransaction()
{
}


