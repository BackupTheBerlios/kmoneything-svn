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
 
#include "kmoneythingtransaction.h"

Q_UINT32 KMoneyThingTransaction::id()
{
  return mId;
}
void KMoneyThingTransaction::setId(Q_UINT32 newId)
{
  mId = newId;
}

double KMoneyThingTransaction::balance()
{
  return mBalance;
}
void KMoneyThingTransaction::setBalance(double newBalance)
{
  mBalance = newBalance;
}

bool KMoneyThingTransaction::split()
{
  return mSplit;
}
void KMoneyThingTransaction::setSplit(bool newVal)
{
  mSplit = newVal;
}

Q_UINT32 KMoneyThingTransaction::subTransactions()
{
  return mSubTransactions.size();
}

void KMoneyThingTransaction::addSubTransaction(KMoneyThingSubTransaction transaction)
{
  mSubTransactions.append(transaction);
}

bool KMoneyThingTransaction::replaceSubTransaction(Q_UINT32 trId, KMoneyThingSubTransaction transaction)
{
  if (trId >= mSubTransactions.size())
    return false;
  mSubTransactions[trId] = transaction;
  return true;
}

bool KMoneyThingTransaction::delSubTransaction(Q_UINT32 trId)
{
  if (trId >= mSubTransactions.size())
    return false;
  mSubTransactions.erase(&mSubTransactions[trId]);
  return true;
}

KMoneyThingSubTransaction KMoneyThingTransaction::getSubTransaction(Q_UINT32 trId)
{
  if (trId >= mSubTransactions.size())
    return KMoneyThingSubTransaction();
  return mSubTransactions[trId];
}

bool KMoneyThingTransaction::foreign()
{
  return mForeign;
}
void KMoneyThingTransaction::setForeign(bool isForeign)
{
  mForeign = isForeign;
}

QString KMoneyThingTransaction::transactionCurrencyName()
{
  return mTransactionCurrencyName;
}
void KMoneyThingTransaction::setTransactionCurrencyName(QString currencyName)
{
  mTransactionCurrencyName = currencyName;
}

double KMoneyThingTransaction::transactionCurrencyIn()
{
  return mTransactionCurrencyIn;
}
void KMoneyThingTransaction::setTransactionCurrencyIn(double newVal)
{
  mTransactionCurrencyIn = newVal;
}

double KMoneyThingTransaction::transactionCurrencyOut()
{
  return mTransactionCurrencyOut;
}
void KMoneyThingTransaction::setTransactionCurrencyOut(double newVal)
{
  mTransactionCurrencyOut = newVal;
}

float KMoneyThingTransaction::exchangeRate()
{
  return mExchangeRate;
}
void KMoneyThingTransaction::setExchangeRate(float newVal)
{
  mExchangeRate = newVal;
}

double KMoneyThingTransaction::accountCurrencyIn()
{
  return mAccountCurrencyIn;
}
void KMoneyThingTransaction::setAccountCurrencyIn(double newVal)
{
  mAccountCurrencyIn = newVal;
}

double KMoneyThingTransaction::accountCurrencyOut()
{
  return mAccountCurrencyOut;
}
void KMoneyThingTransaction::setAccountCurrencyOut(double newVal)
{
  mAccountCurrencyOut = newVal;
}

KMoneyThingTransaction::ReconcileState KMoneyThingTransaction::state()
{
  return mState;
}
void KMoneyThingTransaction::setState(KMoneyThingTransaction::ReconcileState newState)
{
  mState = newState;
}

QString KMoneyThingTransaction::name()
{
  return mName;
}
void KMoneyThingTransaction::setName(QString newVal)
{
  mName = newVal;
}

QString KMoneyThingTransaction::category()
{
  return mCategory;
}
void KMoneyThingTransaction::setCategory(QString newVal)
{
  mCategory = newVal;
}

QString KMoneyThingTransaction::statementId()
{
  return mStatementId;
}
void KMoneyThingTransaction::setStatementId(QString newVal)
{
  mStatementId = newVal;
}

QString KMoneyThingTransaction::type()
{
  return mType;
}
void KMoneyThingTransaction::setType(QString newVal)
{
  mType = newVal;
}

KMoneyThingTransaction::Reference KMoneyThingTransaction::reference()
{
  return mReference;
}
void KMoneyThingTransaction::setReference(KMoneyThingTransaction::Reference newVal)
{
  mReference = newVal;
}
  
KMoneyThingTransaction::KMoneyThingTransaction(Q_UINT32 Id)
{
  mId = Id;
}

KMoneyThingTransaction::~KMoneyThingTransaction()
{
}


