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

#ifndef KMONEYTHINGTRANSACTION_H
#define KMONEYTHINGTRANSACTION_H

#include "kmoneythingsubtransaction.h"

#include <qstring.h>
#include <qptrlist.h>

/**
@author Fred Emmott
*/

class KMoneyThingTransaction{
public:
  enum ReconcileState{
    notCleared,
    cleared,
    reconciled
  };
  
  struct Reference {
    QString accountName;
    Q_UINT32 transactionID;
  };
private:
  double mBalance;  // not used internally, just potential optimization for account
  bool mSplit;
  QPtrList<KMoneyThingSubTransaction> mSubTransactions;
  bool mForeign;
  QString mTransactionCurrencyName;
  double mTransactionCurrencyIn;
  double mTransactionCurrencyOut;
  float mExchangeRate;
  double mAccountCurrencyIn;
  double mAccountCurrencyOut;
  ReconcileState mState;
  QString mName;
  QString mCategory;
  QString mStatementId;
  QString mType; // Credit card, direct debit, standing order, etc
  QPtrList<KMoneyThingTransaction::Reference> mReferences;
  QString mPayee;
public:
  double balance();
  void setBalance(double newBalance);
  bool split();
  void setSplit(bool newVal);
  Q_UINT32 subTransactions();
  void addSubTransaction(KMoneyThingSubTransaction* transaction);
  bool delSubTransaction(Q_UINT32 trId);
  bool delSubTransaction(KMoneyThingSubTransaction* transaction);
  KMoneyThingSubTransaction* getSubTransaction(Q_UINT32 trId);
  bool foreign();
  void setForeign(bool isForeign);
  QString transactionCurrencyName();
  void setTransactionCurrencyName(QString currencyName); 
  double transactionCurrencyIn();
  void setTransactionCurrencyIn(double newVal);
  double transactionCurrencyOut();
  void setTransactionCurrencyOut(double newVal);
  float exchangeRate();
  void setExchangeRate(float newVal);
  double accountCurrencyIn();
  void setAccountCurrencyIn(double newVal);
  double accountCurrencyOut();
  void setAccountCurrencyOut(double newVal);
  KMoneyThingTransaction::ReconcileState state();
  void setState(KMoneyThingTransaction::ReconcileState newState);
  QString name();
  void setName(QString newVal);
  QString category();
  void setCategory(QString newVal);
  QString statementId();
  void setStatementId(QString newVal);
  QString type();
  void setType(QString newVal);
  Q_UINT32 references();
  void addReference(KMoneyThingTransaction::Reference* reference);
  bool delReference(Q_UINT32 trId);
  bool delReference(KMoneyThingTransaction::Reference* reference);
  KMoneyThingTransaction::Reference* getReference(Q_UINT32 trId);
  QString payee();
  void setPayee(QString payee);
    
  KMoneyThingTransaction();
  ~KMoneyThingTransaction();
};

#endif
