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

#include <qdatastream.h>

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

QByteArray KMoneyThingFile::dump()
{
  QByteArray output;
  QDataStream stream(output, IO_WriteOnly);
  stream << "KMoneyThing Document" << "Version" << "pre1_draft";
  stream << "<name>" << mName << "</name>";
  stream << "<locale>" << mLocale->country() << "</locale>";
  for (Q_UINT32 aI = 0; aI < accounts(); aI++)
  {
    KMoneyThingAccount* account = getAccount(aI);
    stream << "<account>";
    stream << "<type>" << account->type() << "</type>";
    stream << "<name>" << account->name() << "</name>";
    stream << "<description>" << account->description() << "</description>";
    stream << "<accountNumber>" << account->accountNumber() << "</accountNumber>";
    stream << "<balance>" << account->balance() << "</balance>";
    stream << "<startingBalance>" << account->startingBalance() << "</startingBalance>";
    for (Q_UINT32 tI = 0; tI < account->transactions(); tI++)
    {
      KMoneyThingTransaction* transaction = account->getTransaction(tI);
      stream << "<transaction>";
      stream << "<name>" << transaction->name() << "</name>";
      stream << "<type>" << transaction->type() << "</type>";
      stream << "<category>" << transaction->category() << "</category>";
      stream << "<state>" << transaction->state() << "</state>";
      stream << "<statement>" << transaction->statementId() << "</statement>";
      stream << "<split>" << transaction->split() << "</split>";
      stream << "<foreign>" << transaction->foreign() << "</foreign>";
      stream << "<exRate>" << transaction->exchangeRate() << "</exRate>";
      stream << "<accCurIn>" << transaction->accountCurrencyIn() << "</accCurIn>";
      stream << "<accCurOut>" << transaction->accountCurrencyOut() << "</accCurOut>";
      stream << "<trCurIn>" << transaction->transactionCurrencyIn() << "</trCurIn>";
      stream << "<trCurOut>" << transaction->transactionCurrencyOut() << "</trCurOut>";
      stream << "<trCurName>" << transaction->transactionCurrencyName() << "</trCurName>";
      for (Q_UINT32 stI = 0; stI < transaction->subTransactions(); stI++)
      {
        KMoneyThingSubTransaction* subTransaction = transaction->getSubTransaction(stI);
        stream << "<subTransaction>";
        stream << "<name>" << subTransaction->name() << "</name>";
        stream << "<category>" << subTransaction->category() << "</category>";
        stream << "<trCurIn>" << subTransaction->transactionCurrencyIn() << "</trCurIn>";
        stream << "<trCurOut>" << subTransaction->transactionCurrencyOut() << "</trCurOut>";
        stream << "</subTransaction>";
      }
      for (Q_UINT32 rI = 0; rI < transaction->references(); rI++)
      {
        KMoneyThingTransaction::Reference* reference = transaction->getReference(rI);
        stream << "<reference>";
        stream << "<refAccount>" << reference->accountName << "</refAccount>";
        stream << "<refTransaction>" << reference->transactionID << "</refTransaction>";
        stream << "</reference>";
      }
      stream << "</transaction>";
    }
    stream << "</account>";
  }
  for (Q_UINT32 cI = 0; cI < categories(); cI++)
    stream << "<category>" << *getCategory(cI) << "</category>";
  for (Q_UINT32 rI = 0; rI < recurrences(); rI++)
  {
    KMoneyThingRecurringTransaction* transaction = getRecurrence(rI);
    stream << "<recurrence>";
    // If KMoneyThingTransaction is changed, copy it's new code from above,
    // overwriting from ***HERE*** ...
    stream << "<name>" << transaction->name() << "</name>";
    stream << "<type>" << transaction->type() << "</type>";
    stream << "<category>" << transaction->category() << "</category>";
    stream << "<state>" << transaction->state() << "</state>";
    stream << "<statement>" << transaction->statementId() << "</statement>";
    stream << "<split>" << transaction->split() << "</split>";
    stream << "<foreign>" << transaction->foreign() << "</foreign>";
    stream << "<exRate>" << transaction->exchangeRate() << "</exRate>";
    stream << "<accCurIn>" << transaction->accountCurrencyIn() << "</accCurIn>";
    stream << "<accCurOut>" << transaction->accountCurrencyOut() << "</accCurOut>";
    stream << "<trCurIn>" << transaction->transactionCurrencyIn() << "</trCurIn>";
    stream << "<trCurOut>" << transaction->transactionCurrencyOut() << "</trCurOut>";
    stream << "<trCurName>" << transaction->transactionCurrencyName() << "</trCurName>";
    for (Q_UINT32 stI = 0; stI < transaction->subTransactions(); stI++)
    {
      KMoneyThingSubTransaction* subTransaction = transaction->getSubTransaction(stI);
      stream << "<subTransaction>";
      stream << "<name>" << subTransaction->name() << "</name>";
      stream << "<category>" << subTransaction->category() << "</category>";
      stream << "<trCurIn>" << subTransaction->transactionCurrencyIn() << "</trCurIn>";
      stream << "<trCurOut>" << subTransaction->transactionCurrencyOut() << "</trCurOut>";
      stream << "</subTransaction>";
    }
    for (Q_UINT32 rI = 0; rI < transaction->references(); rI++)
    {
      KMoneyThingTransaction::Reference* reference = transaction->getReference(rI);
      stream << "<reference>";
      stream << "<refAccount>" << reference->accountName << "</refAccount>";
      stream << "<refTransaction>" << reference->transactionID << "</refTransaction>";
      stream << "</reference>";
    }
    // ... to ***HERE***
    stream << "<recurrency>" << transaction->recurrence() << "</recurrency>";
    stream << "<xDays>" << transaction->xDays() << "</xDays>";
    stream << "<firstDate>" << transaction->firstDate() << "</firstDate>";
    stream << "<daysOn>";
    for (char i = 0; i < 7; i++)
      stream << transaction->isDayOn(i);
    stream << "</daysOn>";
    stream << "</recurrence>";
  }
  
  stream.device()->close();
  return output;
}

KMoneyThingFile::KMoneyThingFile()
{
  mLocale = new KLocale("KMoneyThing");
}

KMoneyThingFile::~KMoneyThingFile()
{
}


