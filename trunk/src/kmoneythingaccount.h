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
 
#ifndef KMONEYTHINGACCOUNT_H
#define KMONEYTHINGACCOUNT_H

#include "kmoneythingtransaction.h"

#include <qcstring.h>
#include <qstring.h>
#include <qptrlist.h>

/**
@author Fred Emmott
*/
class KMoneyThingAccount{
private:
  double mBalance;
  QString mName;
  QPtrList<KMoneyThingTransaction> mTransactions;
  double mStartingBalance;
  QString mDescription;
public:
  double balance();
  QString name();
   void setName(QString name);
  Q_UINT32 transactions();
  void addTransaction(KMoneyThingTransaction* transaction);
  bool delTransaction(Q_UINT32 id);
  bool delTransaction(KMoneyThingTransaction* transaction);
  KMoneyThingTransaction* getTransaction(Q_UINT32 id);
  double startingBalance();
  void setStartingBalance(double balance);
  QString description();
  void setDescription(QString description);
  virtual QString type() = 0;
  QString accountNumber();  // eg account number and sort code
  void setAccountNumber(QString number);
  QString institution();
  void setInstitution(QString institution);

  KMoneyThingAccount(QString name = QString(), double startingBalance = 0);
  virtual ~KMoneyThingAccount();
};

#endif
