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

#ifndef KMONEYTHINGFILE_H
#define KMONEYTHINGFILE_H

#include "kmoneythingaccount.h"
#include "kmoneythingrecurringtransaction.h"

#include <qptrlist.h>
#include <qstringlist.h>
#include <qcstring.h>
#include <qstring.h>

#include <kurl.h>
#include <klocale.h>

/**
@author Fred Emmott
*/
class KMoneyThingFile{
private:
  QPtrList<KMoneyThingAccount> mAccounts;
  QString mLocale;
  QString mName;
  QStringList mCategories;
  QPtrList<KMoneyThingRecurringTransaction> mRecurrences;
  
  KURL mKurl;
public:
  void clear();
  Q_UINT32 accounts();
  void addAccount(KMoneyThingAccount* account);
  bool delAccount(Q_UINT32 id);
  bool delAccount(KMoneyThingAccount* account);
  KMoneyThingAccount* getAccount(Q_UINT32 id);
  QString locale();
  void setLocale(const QString &locale);
  QString name();
  void setName(QString name);
  Q_UINT32 categories();
  void addCategory(QString category);
  bool delCategory(Q_UINT32 id);
  bool delCategory(QString category);
  QString getCategory(Q_UINT32 id);
  const QStringList &getCategories();
  void setCategories(const QStringList& categories);
  Q_UINT32 recurrences();
  void addRecurrence(KMoneyThingRecurringTransaction* transaction);
  bool delRecurrence(Q_UINT32 id);
  bool delRecurrence(KMoneyThingRecurringTransaction* transaction);
  KMoneyThingRecurringTransaction* getRecurrence(Q_UINT32 id);
  
  KURL kurl();
  void setKurl(const KURL &kurl);
  
  QByteArray dump();
  void loadDump(const QByteArray &savedData);

  KMoneyThingFile();
  KMoneyThingFile(const QByteArray &savedData);

  ~KMoneyThingFile();
};

#endif
