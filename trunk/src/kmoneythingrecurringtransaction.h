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

#ifndef KMONEYTHINGRECURRINGTRANSACTION_H
#define KMONEYTHINGRECURRINGTRANSACTION_H

#include "kmoneythingtransaction.h"

#include <qdatetime.h>

/**
@author Fred Emmott
*/
class KMoneyThingRecurringTransaction : public KMoneyThingTransaction
{
public:
  enum Recurrence
  {
    recDaily,
    recWeekly,
    recMonthly,
    recYearly,
    recXDays,  // eg every 3 days
    recSomeDays,  // eg every <monday> and <wednesday>
    recSpecialMonthly  // eg <first> <tuesday> of the month
  };
private:
  KMoneyThingRecurringTransaction::Recurrence mRecurrence;
  bool mDaysOn[6];  // If recSomeDays, or recSpecial
  unsigned short mXDays;  // If recXDays
  QDate mFirstDate;
public:
  KMoneyThingRecurringTransaction::Recurrence recurrence();
  void setRecurrency(KMoneyThingRecurringTransaction::Recurrence newVal);
  bool isDayOn(unsigned char day); // day[0] == Monday
  void setDayOn(unsigned char day, bool on);
  unsigned short xDays();
  void setXDays(unsigned short days);
  QDate firstDate();
  void setFirstDate(QDate date);
  bool isDateOn(QDate date);
  
  KMoneyThingRecurringTransaction();
  ~KMoneyThingRecurringTransaction();
};

#endif
