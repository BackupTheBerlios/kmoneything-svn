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

#include "kmoneythingaccountwizard.h"

#include "kmoneythingcashaccount.h"

#include <qlabel.h>
#include <qhbox.h>

#include <kglobal.h>
#include <klocale.h>
#include <kmessagebox.h>

KMoneyThingAccountWizard::KMoneyThingAccountWizard(QWidget *parent, const char *name, KMoneyThingFile *currentFile)
 : KWizard(parent, name, true)
{
  mFile = currentFile;
  setupWelcomePage();
  setupStandardInfoPage();
  setupExtendedInfoPage();
  setupFinishedPage();
  
  connect(this, SIGNAL(selected(const QString& )), this, SLOT(pageChanged(const QString& )));
}

void KMoneyThingAccountWizard::setupWelcomePage()
{
  welcomePage = new QVBox(this);
  new QLabel(i18n("Welcome to the KMoneyThing New Account wizard.\n\n"
    "This wizard will guide you through the process of making a new account."), welcomePage);
  
  addPage(welcomePage, i18n("Welcome"));
  setNextEnabled(welcomePage, true);
  setHelpEnabled(welcomePage, false);
}

void KMoneyThingAccountWizard::setupStandardInfoPage()
{
  QLabel *label;
  
  standardInfoPage = new QGrid(2, this);
  
  label = new QLabel(i18n("&Type: "), standardInfoPage);
  mType = new KComboBox(standardInfoPage);
  label->setBuddy(mType);
  mType->insertItem(i18n("Cash"));
  mType->setCurrentItem(0);
  connect(mType, SIGNAL(activated(const QString& )), this, SLOT(typeChanged(const QString& )));
  
  label = new QLabel(i18n("N&ame: "), standardInfoPage);
  mName = new KLineEdit(standardInfoPage);
  label->setBuddy(mName);
  connect(mName, SIGNAL(textChanged(const QString& )), this, SLOT(nameChanged(const QString& )));
  
  label = new QLabel(i18n("&Description: "), standardInfoPage);
  mDescription = new KTextEdit(standardInfoPage);
  label->setBuddy(mDescription);
  
  label = new QLabel(i18n("&Locale: "), standardInfoPage);
  mLocale = new KLanguageButton(standardInfoPage);
  label->setBuddy(mLocale);
  KMoneyThingUtils::loadCountryList(mLocale);
  mLocale->setCurrentItem(KGlobal::locale()->country());
  connect(mLocale, SIGNAL(activated(const QString& )), this, SLOT(localeChanged(const QString& )));
  
  addPage(standardInfoPage, i18n("Basic Information"));
  setNextEnabled(standardInfoPage, false);
  setHelpEnabled(standardInfoPage, false);
}

void KMoneyThingAccountWizard::setupExtendedInfoPage()
{
  QLabel *label;
  
  extendedInfoPage = new QGrid(2, this);
  
  label = new QLabel(i18n("&Starting Balance: "), extendedInfoPage);
  mStartingBalance = new KDoubleNumInput(extendedInfoPage);
  mStartingBalance->setPrefix(KGlobal::locale()->currencySymbol());
  label->setBuddy(mStartingBalance);
  
  label = new QLabel(i18n("&Institution: "), extendedInfoPage);
  mInstitution = new KLineEdit(extendedInfoPage);
  label->setBuddy(mInstitution);
  mInstitution->setEnabled(false);
  
  label = new QLabel(i18n("A&ccount Number: "), extendedInfoPage);
  mAccountNumber = new KLineEdit(extendedInfoPage);
  label->setBuddy(mAccountNumber);
  mAccountNumber->setEnabled(false);
  
  addPage(extendedInfoPage, i18n("Extended Information"));
  setNextEnabled(extendedInfoPage, true);
  setHelpEnabled(extendedInfoPage, false);
}

void KMoneyThingAccountWizard::setupFinishedPage()
{
  finishedPage = new QVBox(this);
  
  new QLabel(i18n("Congratulations!\n\nKMyMoneyThing now has all the information needed to create your account.\n"
    "Click 'Finish' to create your account."), finishedPage);
  
  addPage(finishedPage, i18n("Finished!"));
  setFinishEnabled(finishedPage, true);
  setHelpEnabled(finishedPage, false);
}

void KMoneyThingAccountWizard::nameChanged(const QString &text)
{
  if (text == "")
  {
    setNextEnabled(standardInfoPage, false);
    return;
  }
  
  for (Q_UINT32 i = 0; i < mFile->accounts(); i++)
    if (text == mFile->getAccount(i)->name())
    {
      setNextEnabled(standardInfoPage, false);
      return;
    }
  
  setNextEnabled(standardInfoPage, true);
}

void KMoneyThingAccountWizard::localeChanged(const QString &id)
{
  KLocale locale("KMyMoney");
  locale.setCountry(id);
  mStartingBalance->setPrefix(locale.currencySymbol());
}

void KMoneyThingAccountWizard::pageChanged(const QString &title)
{
  // TODO: set focus appropriately
  if (title == QWizard::title(standardInfoPage))
    nameChanged(mName->text());
}

void KMoneyThingAccountWizard::typeChanged(const QString &type)
{
  if (type == i18n("Cash"))
  {
    mInstitution->setEnabled(false);
    mAccountNumber->setEnabled(false);
  }
  else
  {
    mInstitution->setEnabled(true);
    mAccountNumber->setEnabled(true);
  }
}

void KMoneyThingAccountWizard::accept()
{
  KMoneyThingAccount *newAccount;
  
  if (mType->currentText() == i18n("Cash"))
    newAccount = new KMoneyThingCashAccount();
  else
  {
    KMessageBox::error(this, i18n("Unknown account type: %1").arg(mType->currentText()));
  }
  newAccount->setAccountNumber(mAccountNumber->text());
  newAccount->setDescription(mDescription->text());
  newAccount->setInstitution(mInstitution->text());
  newAccount->setLocale(mLocale->current());
  newAccount->setName(mName->text());
  newAccount->setStartingBalance(mStartingBalance->value());
  emit finished(newAccount);
  QDialog::accept();
}

KMoneyThingAccountWizard::~KMoneyThingAccountWizard()
{
}


#include "kmoneythingaccountwizard.moc"
