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

#include "kmoneythingaccount.h"
KMoneyThingAccount::KMoneyThingAccount(QString name, double startingBalance)
{
  mName = name;
  mStartingBalance = startingBalance;
  mBalance = startingBalance;
}

double KMoneyThingAccount::balance()
{
  return mBalance;
}

void KMoneyThingAccount::setBalance(double balance)
{
  mBalance = balance;
}

QString KMoneyThingAccount::name()
{
  return mName;
}

void KMoneyThingAccount::setName(QString name)
{
  mName = name;
}

Q_UINT32 KMoneyThingAccount::transactions()
{
  return mTransactions.count();
}

void KMoneyThingAccount::addTransaction(KMoneyThingTransaction* transaction)
{
  if (transaction == 0) return;
  mTransactions.append(transaction);
}

bool KMoneyThingAccount::delTransaction(Q_UINT32 id)
{
  return mTransactions.remove(id);
}

bool KMoneyThingAccount::delTransaction(KMoneyThingTransaction* transaction)
{
  return mTransactions.remove(transaction);
}

KMoneyThingTransaction* KMoneyThingAccount::getTransaction(Q_UINT32 id)
{
  return mTransactions.at(id);
}

double KMoneyThingAccount::startingBalance()
{
  return mStartingBalance;
}

void KMoneyThingAccount::setStartingBalance(double balance)
{
  mBalance = balance;
}

QString KMoneyThingAccount::description()
{
  return mDescription;
}

void KMoneyThingAccount::setDescription(const QString &description)
{
  mDescription = description;
}

QString KMoneyThingAccount::accountNumber()
{
  return mAccountNumber;
}

void KMoneyThingAccount::setAccountNumber(const QString &number)
{
  mAccountNumber = number;
  return;
}

QString KMoneyThingAccount::institution()
{
  return mInstitution;
}

void KMoneyThingAccount::setInstitution(const QString &institution)
{
  mInstitution = institution;
  return;
}

QString KMoneyThingAccount::locale()
{
  return mLocale;
}

void KMoneyThingAccount::setLocale(const QString &locale)
{
  mLocale = locale;
}

KMoneyThingAccount::~ KMoneyThingAccount()
{
}
