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
 
#include "kmoneythingsubtransaction.h"

double KMoneyThingSubTransaction::transactionCurrencyIn()
{
  return mTransactionCurrencyIn;
}
void KMoneyThingSubTransaction::setTransactionCurrencyIn(double newVal)
{
  mTransactionCurrencyIn = newVal;
}

double KMoneyThingSubTransaction::transactionCurrencyOut()
{
  return mTransactionCurrencyOut;
}
void KMoneyThingSubTransaction::setTransactionCurrencyOut(double newVal)
{
  mTransactionCurrencyOut = newVal;
}

QString KMoneyThingSubTransaction::name()
{
  return mName;
}
void KMoneyThingSubTransaction::setName(QString newVal)
{
  mName = newVal;
}

QString KMoneyThingSubTransaction::category()
{
  return mCategory;
}
void KMoneyThingSubTransaction::setCategory(QString newVal)
{
  mCategory = newVal;
}

KMoneyThingSubTransaction::KMoneyThingSubTransaction()
{
}


KMoneyThingSubTransaction::~KMoneyThingSubTransaction()
{
}


