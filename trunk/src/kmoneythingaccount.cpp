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
  return mTransactions.size();
}

bool KMoneyThingAccount::addTransaction(KMoneyThingTransaction transaction)
{
  if (transaction.accountCurrencyIn() < 0) return false;
  if (transaction.accountCurrencyOut() < 0) return false;
  if (transaction.transactionCurrencyIn() < 0) return false;
  if (transaction.transactionCurrencyOut() < 0) return false;
  
  mTransactions.append(transaction);
  return true;
}

bool KMoneyThingAccount::replaceTransaction(Q_UINT32 id, KMoneyThingTransaction transaction)
{
  if (transaction.accountCurrencyIn() < 0) return false;
  if (transaction.accountCurrencyOut() < 0) return false;
  if (transaction.transactionCurrencyIn() < 0) return false;
  if (transaction.transactionCurrencyOut() < 0) return false;
  if (id >= mTransactions.size()) return false;
  
  mTransactions[id] = transaction;
  return true;
}

KMoneyThingTransaction KMoneyThingAccount::getTransaction(Q_UINT32 id)
{
  if (id >= mTransactions.size()) return KMoneyThingTransaction();
  
  return mTransactions[id];
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

void KMoneyThingAccount::setDescription(QString description)
{
  mDescription = description;
}

QString KMoneyThingAccount::accountNumber()
{
  return QString("");
}

void KMoneyThingAccount::setAccountNumber(QString number)
{
  number = "";
  return;
}

KMoneyThingAccount::~ KMoneyThingAccount()
{
}
