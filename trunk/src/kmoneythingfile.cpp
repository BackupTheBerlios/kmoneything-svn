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
#include "kmoneythingcashaccount.h"

#include <qdatastream.h>

#include <kglobal.h>
#include <kmessagebox.h>

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

QString KMoneyThingFile::locale()
{
  return mLocale;
}

void KMoneyThingFile::setLocale(const QString &locale)
{
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

void KMoneyThingFile::addCategory(QString category)
{
  mCategories.append(category);
}

bool KMoneyThingFile::delCategory(Q_UINT32 id)
{
  return mCategories.remove(mCategories[id]);
}

bool KMoneyThingFile::delCategory(QString category)
{
  return mCategories.remove(category);
}

QString KMoneyThingFile::getCategory(Q_UINT32 id)
{
  return mCategories[id];
}

void KMoneyThingFile::setCategories(const QStringList &categories)
{
  mCategories.clear();
  mCategories = categories;
}

const QStringList& KMoneyThingFile::getCategories()
{
  return mCategories;
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
  
  stream << (QString) "KMoneyThing Document" << (QString) "pre1_draft";
  stream << (QString) "<name>" << mName << (QString) "</name>";
  stream << (QString) "<locale>" << mLocale << (QString) "</locale>";
  for (Q_UINT32 aI = 0; aI < accounts(); aI++)
  {
    KMoneyThingAccount* account = getAccount(aI);
    stream << (QString) "<account>";
    stream << (QString) "<type>" << account->type() << (QString) "</type>";
    stream << (QString) "<name>" << account->name() << (QString) "</name>";
    stream << (QString) "<description>" << account->description() << (QString) "</description>";
    stream << (QString) "<accountNumber>" << account->accountNumber() << (QString) "</accountNumber>";
    stream << (QString) "<institution>" << account->institution() << (QString) "</institution>";
    stream << (QString) "<locale>" << account->locale() << (QString) "</locale>";
    stream << (QString) "<balance>" << account->balance() << (QString) "</balance>";
    stream << (QString) "<startingBalance>" << account->startingBalance() << (QString) "</startingBalance>";
    for (Q_UINT32 tI = 0; tI < account->transactions(); tI++)
    {
      KMoneyThingTransaction* transaction = account->getTransaction(tI);
      stream << (QString) "<transaction>";
      stream << (QString) "<name>" << transaction->name() << (QString) "</name>";
      stream << (QString) "<type>" << transaction->type() << (QString) "</type>";
      stream << (QString) "<category>" << transaction->category() << (QString) "</category>";
      stream << (QString) "<payee>" << transaction->payee() << (QString) "</payee>";
      stream << (QString) "<state>" << transaction->state() << (QString) "</state>";
      stream << (QString) "<statement>" << transaction->statementId() << (QString) "</statement>";
      stream << (QString) "<split>" << transaction->split() << (QString) "</split>";
      stream << (QString) "<foreign>" << transaction->foreign() << (QString) "</foreign>";
      stream << (QString) "<exRate>" << transaction->exchangeRate() << (QString) "</exRate>";
      stream << (QString) "<accCurIn>" << transaction->accountCurrencyIn() << (QString) "</accCurIn>";
      stream << (QString) "<accCurOut>" << transaction->accountCurrencyOut() << (QString) "</accCurOut>";
      stream << (QString) "<trCurIn>" << transaction->transactionCurrencyIn() << (QString) "</trCurIn>";
      stream << (QString) "<trCurOut>" << transaction->transactionCurrencyOut() << (QString) "</trCurOut>";
      stream << (QString) "<trCurName>" << transaction->transactionCurrencyName() << (QString) "</trCurName>";
      for (Q_UINT32 stI = 0; stI < transaction->subTransactions(); stI++)
      {
        KMoneyThingSubTransaction* subTransaction = transaction->getSubTransaction(stI);
        stream << (QString) "<subTransaction>";
        stream << (QString) "<name>" << subTransaction->name() << (QString) "</name>";
        stream << (QString) "<category>" << subTransaction->category() << (QString) "</category>";
        stream << (QString) "<trCurIn>" << subTransaction->transactionCurrencyIn() << (QString) "</trCurIn>";
        stream << (QString) "<trCurOut>" << subTransaction->transactionCurrencyOut() << (QString) "</trCurOut>";
        stream << (QString) "</subTransaction>";
      }
      for (Q_UINT32 rI = 0; rI < transaction->references(); rI++)
      {
        KMoneyThingTransaction::Reference* reference = transaction->getReference(rI);
        stream << (QString) "<reference>";
        stream << (QString) "<refAccount>" << reference->accountName << (QString) "</refAccount>";
        stream << (QString) "<refTransaction>" << reference->transactionID << (QString) "</refTransaction>";
        stream << (QString) "</reference>";
      }
      stream << (QString) "</transaction>";
    }
    stream << (QString) "</account>";
  }
  for (Q_UINT32 cI = 0; cI < categories(); cI++)
    stream << (QString) "<category>" << *getCategory(cI) << (QString) "</category>";
  for (Q_UINT32 rI = 0; rI < recurrences(); rI++)
  {
    KMoneyThingRecurringTransaction* transaction = getRecurrence(rI);
    stream << (QString) "<recurrence>";
    // If KMoneyThingTransaction is changed, copy its new code from above,
    // overwriting from ***HERE*** ...
    stream << (QString) "<name>" << transaction->name() << (QString) "</name>";
    stream << (QString) "<type>" << transaction->type() << (QString) "</type>";
    stream << (QString) "<category>" << transaction->category() << (QString) "</category>";
    stream << (QString) "<state>" << transaction->state() << (QString) "</state>";
    stream << (QString) "<statement>" << transaction->statementId() << (QString) "</statement>";
    stream << (QString) "<split>" << transaction->split() << (QString) "</split>";
    stream << (QString) "<foreign>" << transaction->foreign() << (QString) "</foreign>";
    stream << (QString) "<exRate>" << transaction->exchangeRate() << (QString) "</exRate>";
    stream << (QString) "<accCurIn>" << transaction->accountCurrencyIn() << (QString) "</accCurIn>";
    stream << (QString) "<accCurOut>" << transaction->accountCurrencyOut() << (QString) "</accCurOut>";
    stream << (QString) "<trCurIn>" << transaction->transactionCurrencyIn() << (QString) "</trCurIn>";
    stream << (QString) "<trCurOut>" << transaction->transactionCurrencyOut() << (QString) "</trCurOut>";
    stream << (QString) "<trCurName>" << transaction->transactionCurrencyName() << (QString) "</trCurName>";
    for (Q_UINT32 stI = 0; stI < transaction->subTransactions(); stI++)
    {
      KMoneyThingSubTransaction* subTransaction = transaction->getSubTransaction(stI);
      stream << (QString) "<subTransaction>";
      stream << (QString) "<name>" << subTransaction->name() << (QString) "</name>";
      stream << (QString) "<category>" << subTransaction->category() << (QString) "</category>";
      stream << (QString) "<trCurIn>" << subTransaction->transactionCurrencyIn() << (QString) "</trCurIn>";
      stream << (QString) "<trCurOut>" << subTransaction->transactionCurrencyOut() << (QString) "</trCurOut>";
      stream << (QString) "</subTransaction>";
    }
    for (Q_UINT32 rI = 0; rI < transaction->references(); rI++)
    {
      KMoneyThingTransaction::Reference* reference = transaction->getReference(rI);
      stream << (QString) "<reference>";
      stream << (QString) "<refAccount>" << reference->accountName << (QString) "</refAccount>";
      stream << (QString) "<refTransaction>" << reference->transactionID << (QString) "</refTransaction>";
      stream << (QString) "</reference>";
    }
    // ... to ***HERE***
    stream << (QString) "<recurrency>" << transaction->recurrence() << (QString) "</recurrency>";
    stream << (QString) "<xDays>" << transaction->xDays() << (QString) "</xDays>";
    stream << (QString) "<firstDate>" << transaction->firstDate() << (QString) "</firstDate>";
    stream << (QString) "<daysOn>";
    for (char i = 0; i < 7; i++)
      stream << transaction->isDayOn(i);
    stream << (QString) "</daysOn>";
    stream << (QString) "</recurrence>";
  }
  
  stream.device()->close();
  return qCompress(output);
}

void KMoneyThingFile::loadDump(const QByteArray &savedData)
{
  QString temp1, temp2, temp3, temp4, temp5;
  double dTemp;
  QDataStream stream(qUncompress(savedData), IO_ReadOnly);
  
  stream >> temp1 >> temp2;
  
  if ((temp1 != "KMoneyThing Document") || (temp2 != "pre1_draft"))
  {
    KMessageBox::error(0, i18n("Unknown file format: %1 version %2").arg(temp1).arg(temp2));
    return;
  }
  
  clear();
  
  while (!stream.atEnd())
  {
    stream >> temp1;
    if (temp1 == "<name>")
    {
      stream >> temp2;
      setName(temp2);
      stream >> temp2;
      if (temp2 != "</name>")
      {
        KMessageBox::error(0, i18n("File is corrupt!"));
        return;
      }
    }
    else if (temp1 == "<locale>")
    {
      stream >> temp2;
      setLocale(temp2);
      stream >> temp2;
      if (temp2 != "</locale>")
      {
        KMessageBox::error(0, i18n("File is corrupt!"));
        return;
      }
    }
    else if (temp1 == "<account>")
    {
      KMoneyThingAccount *account;
      while (! stream.atEnd())
      {
        stream >> temp2;
        if (temp2 == "<type>")
        {
          stream >> temp3;
          if (temp3 == "cash")
            account = new KMoneyThingCashAccount();
          else
          {
            KMessageBox::error(0, i18n("Unrecognized account type: %1").arg(temp3));
            return;
          }
          stream >> temp3;
          if (temp3 != "</type>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp2 == "<name>")
        {
          stream >> temp3;
          account->setName(temp3);
          stream >> temp3;
          if (temp3 != "</name>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp2 == "<description>")
        {
          stream >> temp3;
          account->setDescription(temp3);
          stream >> temp3;
          if (temp3 != "</description>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp2 == "<accountNumber>")
        {
          stream >> temp3;
          account->setAccountNumber(temp3);
          stream >> temp3;
          if (temp3 != "</accountNumber>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp2 == "<institution>")
        {
          stream >> temp3;
          account->setInstitution(temp3);
          stream >> temp3;
          if (temp3 != "</institution>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp2 == "<locale>")
        {
          stream >> temp3;
          account->setLocale(temp3);
          stream >> temp3;
          if (temp3 != "</locale>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp2 == "<balance>")
        {
          stream >> dTemp;
          account->setBalance(dTemp);
          stream >> temp3;
          if (temp3 != "</balance>")
          {
            KMessageBox::error(0, i18n("File is corrupted!"));
            return;
          }
        }
        else if (temp2 == "<startingBalance>")
        {
          stream >> dTemp;
          account->setStartingBalance(dTemp);
          stream >> temp3;
          if (temp3 != "</startingBalance>")
          {
            KMessageBox::error(0, i18n("File is corrupted!"));
            return;
          }
        }
        else if (temp2 == "<transaction>")  // YAY! yet more recursion
        {
          KMoneyThingTransaction *transaction = new KMoneyThingTransaction();
          while (! stream.atEnd())
          {
            stream >> temp3;
            if (temp3 == "<name>")
            {
              stream >> temp4;
              transaction->setName(temp4);
              stream >> temp4;
              if (temp4 != "</name>")
              {
                KMessageBox::error(0, i18n("File is corrupt!"));
                return;
              }
            }
            else if (temp3 == "<type>")
            {
              stream >> temp4;
              transaction->setType(temp4);
              stream >> temp4;
              if (temp4 != "</type>")
              {
                KMessageBox::error(0, i18n("File is corrupt!"));
                return;
              }
            }
            else if (temp3 == "<category>")
            {
              stream >> temp4;
              transaction->setCategory(temp4);
              stream >> temp4;
              if (temp4 != "</category>")
              {
                KMessageBox::error(0, i18n("File is corrupt!"));
                return;
              }
            }
            else if (temp3 == "<payee>")
            {
              stream >> temp4;
              transaction->setPayee(temp4);
              stream >> temp4;
              if (temp4 != "</payee>")
              {
                KMessageBox::error(0, i18n("File is corrupt!"));
                return;
              }
            }
            else if (temp3 == "<state>")
            {
              KMoneyThingTransaction::ReconcileState state;
              stream >> (Q_UINT8) state;
              transaction->setState(state);
              stream >> temp4;
              if (temp4 != "</state>")
              {
                KMessageBox::error(0, i18n("File is corrupted!"));
                return;
              }
            }
            else if (temp3 == "<foreign>")
            {
              bool foreign;
              stream >> (Q_UINT8) foreign;
              transaction->setForeign(foreign);
              stream >> temp4;
              if (temp4 != "</foreign>")
              {
                KMessageBox::error(0, i18n("File is corrupted!"));
                return;
              }
            }
            else if (temp3 == "<exRate>")
            {
              float exRate;
              stream >> exRate;
              transaction->setExchangeRate(exRate);
              stream >> temp4;
              if (temp4 != "</exRate>")
              {
                KMessageBox::error(0, i18n("File is corrupted!"));
                return;
              }
            }
            else if (temp3 == "<accCurIn>")
            {
              double accCurIn;
              stream >> accCurIn;
              transaction->setAccountCurrencyIn(accCurIn);
              stream >> temp4;
              if (temp4 != "</accCurIn>")
              {
                KMessageBox::error(0, i18n("File is corrupted!"));
                return;
              }
            }
            else if (temp3 == "<accCurOut>")
            {
              double accCurOut;
              stream >> accCurOut;
              transaction->setAccountCurrencyOut(accCurOut);
              stream >> temp4;
              if (temp4 != "</accCurOut>")
              {
                KMessageBox::error(0, i18n("File is corrupted!"));
                return;
              }
            }
            else if (temp3 == "<trCurIn>")
            {
              double trCurIn;
              stream >> trCurIn;
              transaction->setTransactionCurrencyIn(trCurIn);
              stream >> temp4;
              if (temp4 != "</trCurIn>")
              {
                KMessageBox::error(0, i18n("File is corrupted!"));
                return;
              }
            }
            else if (temp3 == "<trCurOut>")
            {
              double trCurOut;
              stream >> trCurOut;
              transaction->setTransactionCurrencyOut(trCurOut);
              stream >> temp4;
              if (temp4 != "</trCurOut>")
              {
                KMessageBox::error(0, i18n("File is corrupted!"));
                return;
              }
            }
            else if (temp3 == "<trCurName>")
            {
              stream >> temp4;
              transaction->setTransactionCurrencyName(temp4);
              stream >> temp4;
              if (temp4 != "</trCurName>")
              {
                KMessageBox::error(0, i18n("File is corrupt!"));
                return;
              }
            }
            else if (temp3 == "<subTransaction>")
            {
              KMoneyThingSubTransaction* subTransaction = new KMoneyThingSubTransaction();
              while (! stream.atEnd())
              {
                stream >> temp4;
                if (temp4 == "<name>")
                {
                  stream >> temp5;
                  subTransaction->setName(temp5);
                  stream >> temp5;
                  if (temp5 != "</name>")
                  {
                    KMessageBox::error(0, i18n("File is corrupt!"));
                    return;
                  }
                }
                else if (temp4 == "<category>")
                {
                  stream >> temp5;
                  subTransaction->setCategory(temp5);
                  stream >> temp5;
                  if (temp5 != "</category>")
                  {
                    KMessageBox::error(0, i18n("File is corrupt!"));
                    return;
                  }
                }
                else if (temp4 == "<trCurIn>")
                {
                  double trCurIn;
                  stream >> trCurIn;
                  subTransaction->setTransactionCurrencyIn(trCurIn);
                  stream >> temp5;
                  if (temp5 != "</trCurIn>")
                  {
                    KMessageBox::error(0, i18n("File is corrupted!"));
                    return;
                  }
                }
                else if (temp4 == "<trCurOut>")
                {
                  double trCurOut;
                  stream >> trCurOut;
                  subTransaction->setTransactionCurrencyOut(trCurOut);
                  stream >> temp5;
                  if (temp5 != "</trCurOut>")
                  {
                    KMessageBox::error(0, i18n("File is corrupted!"));
                    return;
                  }
                }
                else if (temp4 == "</subTransaction>")
                {
                  transaction->addSubTransaction(subTransaction);
                  break;
                }
              }
            }
            else if (temp3 == "<reference>")
            {
              KMoneyThingTransaction::Reference *reference;
              while (! stream.atEnd())
              {
                stream >> temp4;
                if (temp4 == "<refAccount>")
                {
                  stream >> temp5;
                  reference->accountName = temp5;
                  stream >> temp5;
                  if (temp5 != "</refAccount>")
                  {
                    KMessageBox::error(0, i18n("File is corrupt!"));
                    return;
                  }
                }
                else if (temp4 == "<refTransaction>")
                {
                  Q_UINT32 trId;
                  stream >> trId;
                  reference->transactionID = trId;
                  stream >> temp5;
                  if (temp5 != "</refTransaction>")
                  {
                    KMessageBox::error(0, i18n("File is corrupted!"));
                    return;
                  }
                }
                else if (temp4 == "</reference>")
                {
                  transaction->addReference(reference);
                  break;
                }
              }
            }
            else if (temp3 == "</transaction>")
            {
              account->addTransaction(transaction);
              break;
            }
          }
        }
        else if (temp2 == "</account>")
        {
          addAccount(account);
          break;
        }
      }
    }
    else if (temp1 == "<category>")
    {
      stream >> temp3;
      addCategory(temp3);
      stream >> temp3;
      if (temp3 != "</category>")
      {
        KMessageBox::error(0, i18n("File is corrupted!"));
        return;
      }
    }
    else if (temp1 == "<recurrence>")
    {
      KMoneyThingRecurringTransaction *transaction;
      // If KMoneyThingTransaction changes, copy its new code from
      // ***HERE***... (while...)
      while (! stream.atEnd())
      {
        stream >> temp3;
        if (temp3 == "<name>")
        {
          stream >> temp4;
          transaction->setName(temp4);
          stream >> temp4;
          if (temp4 != "</name>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp3 == "<type>")
        {
          stream >> temp4;
          transaction->setType(temp4);
          stream >> temp4;
          if (temp4 != "</type>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp3 == "<category>")
        {
          stream >> temp4;
          transaction->setCategory(temp4);
          stream >> temp4;
          if (temp4 != "</category>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp3 == "<payee>")
        {
          stream >> temp4;
          transaction->setPayee(temp4);
          stream >> temp4;
          if (temp4 != "</payee>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp3 == "<state>")
        {
          KMoneyThingTransaction::ReconcileState state;
          stream >> (Q_UINT8) state;
          transaction->setState(state);
          stream >> temp4;
          if (temp4 != "</state>")
          {
            KMessageBox::error(0, i18n("File is corrupted!"));
            return;
          }
        }
        else if (temp3 == "<foreign>")
        {
          bool foreign;
          stream >> (Q_UINT8) foreign;
          transaction->setForeign(foreign);
          stream >> temp4;
          if (temp4 != "</foreign>")
          {
            KMessageBox::error(0, i18n("File is corrupted!"));
            return;
          }
        }
        else if (temp3 == "<exRate>")
        {
          float exRate;
          stream >> exRate;
          transaction->setExchangeRate(exRate);
          stream >> temp4;
          if (temp4 != "</exRate>")
          {
            KMessageBox::error(0, i18n("File is corrupted!"));
            return;
          }
        }
        else if (temp3 == "<accCurIn>")
        {
          double accCurIn;
          stream >> accCurIn;
          transaction->setAccountCurrencyIn(accCurIn);
          stream >> temp4;
          if (temp4 != "</accCurIn>")
          {
            KMessageBox::error(0, i18n("File is corrupted!"));
            return;
          }
        }
        else if (temp3 == "<accCurOut>")
        {
          double accCurOut;
          stream >> accCurOut;
          transaction->setAccountCurrencyOut(accCurOut);
          stream >> temp4;
          if (temp4 != "</accCurOut>")
          {
            KMessageBox::error(0, i18n("File is corrupted!"));
            return;
          }
        }
        else if (temp3 == "<trCurIn>")
        {
          double trCurIn;
          stream >> trCurIn;
          transaction->setTransactionCurrencyIn(trCurIn);
          stream >> temp4;
          if (temp4 != "</trCurIn>")
          {
            KMessageBox::error(0, i18n("File is corrupted!"));
            return;
          }
        }
        else if (temp3 == "<trCurOut>")
        {
          double trCurOut;
          stream >> trCurOut;
          transaction->setTransactionCurrencyOut(trCurOut);
          stream >> temp4;
          if (temp4 != "</trCurOut>")
          {
            KMessageBox::error(0, i18n("File is corrupted!"));
            return;
          }
        }
        else if (temp3 == "<trCurName>")
        {
          stream >> temp4;
          transaction->setTransactionCurrencyName(temp4);
          stream >> temp4;
          if (temp4 != "</trCurName>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp3 == "<subTransaction>")
        {
          KMoneyThingSubTransaction* subTransaction = new KMoneyThingSubTransaction();
          while (! stream.atEnd())
          {
            stream >> temp4;
            if (temp4 == "<name>")
            {
              stream >> temp5;
              subTransaction->setName(temp5);
              stream >> temp5;
              if (temp5 != "</name>")
              {
                KMessageBox::error(0, i18n("File is corrupt!"));
                return;
              }
            }
            else if (temp4 == "<category>")
            {
              stream >> temp5;
              subTransaction->setCategory(temp5);
              stream >> temp5;
              if (temp5 != "</category>")
              {
                KMessageBox::error(0, i18n("File is corrupt!"));
                return;
              }
            }
            else if (temp4 == "<trCurIn>")
            {
              double trCurIn;
              stream >> trCurIn;
              subTransaction->setTransactionCurrencyIn(trCurIn);
              stream >> temp5;
              if (temp5 != "</trCurIn>")
              {
                KMessageBox::error(0, i18n("File is corrupted!"));
                return;
              }
            }
            else if (temp4 == "<trCurOut>")
            {
              double trCurOut;
              stream >> trCurOut;
              subTransaction->setTransactionCurrencyOut(trCurOut);
              stream >> temp5;
              if (temp5 != "</trCurOut>")
              {
                KMessageBox::error(0, i18n("File is corrupted!"));
                return;
              }
            }
            else if (temp4 == "</subTransaction>")
            {
              transaction->addSubTransaction(subTransaction);
              break;
            }
          }
        }
        else if (temp3 == "<reference>")
        {
          KMoneyThingTransaction::Reference *reference;
          while (! stream.atEnd())
          {
            stream >> temp4;
            if (temp4 == "<refAccount>")
            {
              stream >> temp5;
              reference->accountName = temp5;
              stream >> temp5;
              if (temp5 != "</refAccount>")
              {
                KMessageBox::error(0, i18n("File is corrupt!"));
                return;
              }
            }
            else if (temp4 == "<refTransaction>")
            {
              Q_UINT32 trId;
              stream >> trId;
              reference->transactionID = trId;
              stream >> temp5;
              if (temp5 != "</refTransaction>")
              {
                KMessageBox::error(0, i18n("File is corrupted!"));
                return;
              }
            }
            else if (temp4 == "</reference>")
            {
              transaction->addReference(reference);
              break;
            }
          }
        }
      // ... to ***HERE*** (3 "}" after transaction->addReference(reference);\nbreak;)
        else if (temp3 == "<recurrency>")
        {
          KMoneyThingRecurringTransaction::Recurrence recurrence;
          stream >> (Q_UINT8) recurrence;
          transaction->setRecurrency(recurrence);
          stream >> temp4;
          if (temp4 != "</recurrency>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp3 == "<xDays>")
        {
          unsigned short xDays;
          stream >> xDays;
          transaction->setXDays(xDays);
          stream >> temp4;
          if (temp4 != "</xDays>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp3 == "<firstDate>")
        {
          QDate firstDate;
          stream >> firstDate;
          transaction->setFirstDate(firstDate);
          stream >> temp4;
          if (temp4 != "</firstDate>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp3 == "<daysOn>")
        {
          bool isOn;
          for (char i = 0; i < 7; i++)
          {
            stream >> (Q_UINT8) isOn;
            transaction->setDayOn(i, isOn);
          }
          stream >> temp4;
          if (temp4 != "</daysOn>")
          {
            KMessageBox::error(0, i18n("File is corrupt!"));
            return;
          }
        }
        else if (temp3 == "</recurrency>")
        {
          addRecurrence(transaction);
          break;
        }
      }
    }
  }
  
  stream.device()->close();
}
void KMoneyThingFile::clear()
{
  mAccounts.clear();
  mLocale = "";
  mName = "";
  mCategories.clear();
  mRecurrences.clear();
}

KMoneyThingFile::KMoneyThingFile()
{
  mLocale = KGlobal::locale()->country();
}

KMoneyThingFile::KMoneyThingFile(const QByteArray &savedData)
{
  KMoneyThingFile();
  loadDump(savedData);
}

KURL KMoneyThingFile::kurl()
{
  return mKurl;
}

void KMoneyThingFile::setKurl(const KURL &kurl)
{
  mKurl = kurl;
}

KMoneyThingFile::~KMoneyThingFile()
{
}


