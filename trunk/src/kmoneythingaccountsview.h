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

#ifndef KMONEYTHINGACCOUNTSVIEW_H
#define KMONEYTHINGACCOUNTSVIEW_H

#include "kmoneythingview.h"
#include "kmoneythingfile.h"
#include "kmoneythingaccount.h"
#include "kmoneythingaccountwizard.h"
#include "kmoneythingutils.h"
#include "klanguagebutton.h"

#include <qlabel.h>

#include <kcombobox.h>
#include <kpushbutton.h>
#include <klineedit.h>
#include <ktextedit.h>
#include <knuminput.h>

/**
@author Fred Emmott
*/
class KMoneyThingAccountsView : public KMoneyThingView
{
Q_OBJECT
private:
  KMoneyThingFile *mFile;
  KMoneyThingAccount *mAccount;
  KComboBox* mAccountCombo;
  KPushButton* mNewAccount;
  QLabel* mLocaleLabel;
  KLanguageButton* mLocale;
  QLabel* mStartingBalanceLabel;
  KDoubleNumInput* mStartingBalance;
  QLabel* mNameLabel;
  KLineEdit* mName;
  QLabel* mInstitutionLabel;
  KLineEdit* mInstitution;
  QLabel* mNumberLabel;
  KLineEdit* mNumber;
  QLabel* mDescriptionLabel;
  KTextEdit* mDescription;
  KPushButton* mApply;
  KPushButton* mRemove;
public:
  virtual void setFile(KMoneyThingFile *file);
  void setAccount(Q_UINT32 id);
  virtual void undoChanges();
  virtual void saveChanges();
  
  KMoneyThingAccountsView(QWidget *parent = 0, const char *name = 0, KMoneyThingFile *currentFile = 0);

  ~KMoneyThingAccountsView();
protected:
  virtual void hideEvent(QHideEvent *event);
private slots:
  void slotApply();
  void slotAccountWizard();
  void slotLocaleChanged(const QString &id);
  void slotRemoveSelectedAccount();
  void slotSomethingChanged();
public slots:
  void slotAddAccount(KMoneyThingAccount* account);
  virtual void slotRefresh();
  void slotUnimplemented();
};

#endif
