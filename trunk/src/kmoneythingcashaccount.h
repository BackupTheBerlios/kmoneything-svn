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
 
#ifndef KMONEYTHINGCASHACCOUNT_H
#define KMONEYTHINGCASHACCOUNT_H

#include "kmoneythingaccount.h"

#include <qvaluevector.h>
/**
@author Fred Emmott
*/
class KMoneyThingCashAccount : public KMoneyThingAccount
{
private:
  double mBalance;
  QString mName;
  QValueVector<KMoneyThingTransaction> mTransactions;
  double mStartingBalance;
  QString mDescription;
  QString mType = "cash";
  QString mAccountDescription;
public:
   double balance();
   QString name();
   void setName(QString);
   Q_UINT32 transactions();
   bool addTransaction(KMoneyThingTransaction);
   bool replaceTransaction(Q_UINT32, KMoneyThingTransaction);
   bool delTransaction(Q_UINT32);
   KMoneyThingTransaction getTransaction(Q_UINT32);
   double startingBalance();
   bool setStartingBalance(double);
   QString description();
   void setDescription(QString);
   QString type();
   QString accountNumber();  // eg account number and sort code
   void setAccountNumber(QString);
   QString accountDescription();  // eg Fred's Barclays Account
   void setAccountDescription();
  
  KMoneyThingCashAccount(QString name = QString(), double startingBalance = 0);

  ~KMoneyThingCashAccount();

};

#endif
