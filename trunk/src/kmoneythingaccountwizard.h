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

#ifndef KMONEYTHINGACCOUNTWIZARD_H
#define KMONEYTHINGACCOUNTWIZARD_H

#include "kmoneythingfile.h"

#include "klanguagebutton.h"
#include "kmoneythingutils.h"

#include <qwizard.h>
#include <qvbox.h>
#include <qgrid.h>
#include <qstring.h>

#include <kwizard.h>
#include <kpushbutton.h>
#include <klineedit.h>
#include <ktextedit.h>
#include <kcombobox.h>
#include <knuminput.h>

/**
@author Fred Emmott
*/
class KMoneyThingAccountWizard : public KWizard
{
Q_OBJECT
private:
  KMoneyThingFile *mFile;
  
  QVBox* welcomePage;
  QGrid* standardInfoPage;
  QGrid* extendedInfoPage;
  QVBox* finishedPage;
  
  // standard info
  KComboBox *mType;
  KLineEdit *mName;
  KTextEdit *mDescription;
  KLanguageButton *mLocale;
  
  // extended info
  KDoubleNumInput *mStartingBalance;
  KLineEdit *mInstitution;
  KLineEdit *mAccountNumber;
  
  void setupWelcomePage();
  void setupStandardInfoPage();
  void setupExtendedInfoPage();
  void setupFinishedPage();
public:
  KMoneyThingAccountWizard(QWidget *parent, const char *name, KMoneyThingFile* currentFile);

  ~KMoneyThingAccountWizard();
protected slots:
  void nameChanged(const QString &text);
  void localeChanged(const QString &id);
  void pageChanged(const QString &title);
  void typeChanged(const QString &type);
  void accept();
signals:  
  void finished(KMoneyThingAccount *account);
};

#endif
