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

#include "kmoneythingaccountsview.h"

#include <qlayout.h>
#include <qframe.h>
#include <qlabel.h>

#include <kmessagebox.h>
#include <kiconloader.h>

KMoneyThingAccountsView::KMoneyThingAccountsView(QWidget *parent, const char *name, KMoneyThingFile *currentFile)
 : KMoneyThingView(parent, name)
{
  QHBoxLayout *hbox;
  QFrame *seperator;
  
  QVBoxLayout *mainLayout = new QVBoxLayout(this, 7);
  
  hbox = new QHBoxLayout(this, 2);
  mainLayout->addItem(hbox);
  
  mAccountCombo = new KComboBox(this);
  mAccountCombo->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
  hbox->add(mAccountCombo);
  
  mNewAccount = new KPushButton(SmallIconSet("filenew"), i18n("&New..."), this);
  connect(mNewAccount, SIGNAL(clicked()), this, SLOT(slotAccountWizard()));
  hbox->add(mNewAccount);
  
  seperator = new QFrame(this);
  seperator->setFrameStyle(QFrame::HLine | QFrame::Sunken);
  mainLayout->add(seperator);
  
  QGridLayout *grid = new QGridLayout(this, 6, 2);
  grid->setSpacing(hbox->spacing());
  mainLayout->addItem(grid);
  
  mLocale = new KLanguageButton(this);
  mLocaleLabel = new QLabel(mLocale, i18n("&Locale:"), this);
  grid->addWidget(mLocaleLabel, 0, 0);
  grid->addWidget(mLocale, 0, 1);
  KMoneyThingUtils::loadCountryList(mLocale);
  connect(mLocale, SIGNAL(activated(const QString& )), this, SLOT(slotLocaleChanged(const QString& )));
  connect(mLocale, SIGNAL(activated(const QString& )), this, SLOT(slotSomethingChanged()));
  
  mStartingBalance = new KDoubleNumInput(this);
  mStartingBalanceLabel = new QLabel(mStartingBalance, i18n("&Starting Balance:"), this);
  grid->addWidget(mStartingBalanceLabel, 1, 0);
  grid->addWidget(mStartingBalance, 1, 1);
  connect(mStartingBalance, SIGNAL(valueChanged(double)), this, SLOT(slotSomethingChanged()));
  
  mName = new KLineEdit(this);
  mNameLabel = new QLabel(mName, i18n("Na&me:"), this);
  grid->addWidget(mNameLabel, 2, 0);
  grid->addWidget(mName, 2, 1);
  connect(mName, SIGNAL(textChanged(const QString& )), this, SLOT(slotSomethingChanged()));
  
  mInstitution = new KLineEdit(this);
  mInstitutionLabel = new QLabel(mInstitution, i18n("&Institution:"), this);
  grid->addWidget(mInstitutionLabel, 3, 0);
  grid->addWidget(mInstitution, 3, 1);
  connect(mInstitution, SIGNAL(textChanged(const QString& )), this, SLOT(slotSomethingChanged()));
  
  mNumber = new KLineEdit(this);
  mNumberLabel = new QLabel(mNumber, i18n("N&umber:"), this);
  grid->addWidget(mNumberLabel, 4, 0);
  grid->addWidget(mNumber, 4, 1);
  connect(mNumber, SIGNAL(textChanged(const QString& )), this, SLOT(slotSomethingChanged()));
  
  mDescription = new KTextEdit(this);
  mDescriptionLabel = new QLabel(mDescription, i18n("&Description:"), this);
  grid->addWidget(mDescriptionLabel, 5, 0);
  grid->addWidget(mDescription, 5, 1);
  connect(mDescription, SIGNAL(textChanged()), this, SLOT(slotSomethingChanged()));

  seperator = new QFrame(this);
  seperator->setFrameStyle(QFrame::HLine | QFrame::Sunken);
  mainLayout->add(seperator);
  
  hbox = new QHBoxLayout(this, 3);
  mainLayout->addItem(hbox);
  
  QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding);
  hbox->addItem(spacer);
  
  mApply = new KPushButton(SmallIconSet("ok"), i18n("&Apply"), this);
  connect(mApply, SIGNAL(clicked()), this, SLOT(slotApply()));
  hbox->add(mApply);
  
  mRemove = new KPushButton(SmallIconSet("fileclose"), i18n("&Remove"), this);
  connect(mRemove, SIGNAL(clicked()), this, SLOT(slotRemoveSelectedAccount()));
  hbox->add(mRemove);
  
  setFile(currentFile);
}

void KMoneyThingAccountsView::slotAccountWizard()
{
  KMoneyThingAccountWizard *wizard = new KMoneyThingAccountWizard(this, 0, mFile);
  connect(wizard, SIGNAL(finished(KMoneyThingAccount* )), this, SLOT(slotAddAccount(KMoneyThingAccount* )));
  wizard->show();
}

void KMoneyThingAccountsView::slotAddAccount(KMoneyThingAccount* account)
{
  Q_UINT32 number = mFile->accounts();
  mFile->addAccount(account);
  mAccountCombo->insertItem(account->name());
  mAccountCombo->setCurrentItem(mAccountCombo->count() - 1);
  setAccount(number);
}

void KMoneyThingAccountsView::setFile(KMoneyThingFile *file)
{
  file == 0
    ? mFile = new KMoneyThingFile()
    : mFile = file;
  
  mAccountCombo->clear();
  for (Q_UINT32 i = 0; i < mFile->accounts(); i++)
    mAccountCombo->insertItem(mFile->getAccount(0)->name());
  
  setAccount(0);
}

void KMoneyThingAccountsView::setAccount(Q_UINT32 id)
{
  if (id >= mFile->accounts())
  {
    mAccount = 0;
    
    mAccountCombo->setEnabled(false);
    
    mLocaleLabel->setEnabled(false);
    mLocale->setEnabled(false);
    mLocale->setCurrentItem(KGlobal::locale()->country());
    mStartingBalanceLabel->setEnabled(false);
    mStartingBalance->setEnabled(false);
    mStartingBalance->setValue(0);
    mStartingBalance->setPrefix(KGlobal::locale()->currencySymbol());
    mStartingBalance->setPrecision(KGlobal::locale()->fracDigits());
    mNameLabel->setEnabled(false);
    mName->setEnabled(false);
    mName->setText("");
    mInstitutionLabel->setEnabled(false);
    mInstitution->setEnabled(false);
    mInstitution->setText("");
    mNumberLabel->setEnabled(false);
    mNumber->setEnabled(false);
    mNumber->setText("");
    mDescriptionLabel->setEnabled(false);
    mDescription->setEnabled(false);
    mDescription->setText("");    
    mRemove->setEnabled(false);
  }
  else
  {
    mAccount = mFile->getAccount(id);  

    KLocale locale("KMoneyThing");
    locale.setCountry(mAccount->locale());
    
    mAccountCombo->setEnabled(true);
    mAccountCombo->setCurrentItem(id);
    
    mLocaleLabel->setEnabled(true);
    mLocale->setEnabled(true);
    mLocale->setCurrentItem(mAccount->locale());
    mStartingBalanceLabel->setEnabled(true);
    mStartingBalance->setEnabled(true);
    mStartingBalance->setValue(mAccount->startingBalance());
    mStartingBalance->setPrefix(locale.currencySymbol());
    mStartingBalance->setPrecision(locale.fracDigits());
    mNameLabel->setEnabled(true);
    mName->setEnabled(true);
    mName->setText(mAccount->name());
    mDescriptionLabel->setEnabled(true);
    mDescription->setEnabled(true);
    mDescription->setText(mAccount->description());
    mRemove->setEnabled(true);
    if (mAccount->type() == "cash")
    {
        mInstitutionLabel->setEnabled(false);
        mInstitution->setEnabled(false);
        mInstitution->setText("");
        mNumberLabel->setEnabled(false);
        mNumber->setEnabled(false);
        mNumber->setText("");
    }
    else
        KMessageBox::error(this, i18n("Unknown account type: %1").arg(mAccount->type()));
  }
    mApply->setEnabled(false);
}

void KMoneyThingAccountsView::undoChanges()
{
  setFile(mFile);
}

void KMoneyThingAccountsView::saveChanges()
{
  slotApply();
  setFile(mFile);
}

void KMoneyThingAccountsView::slotApply()
{
  double newBalance;
  
  newBalance = mAccount->balance() + (mStartingBalance->value() - mAccount->startingBalance());
  
  mAccount->setAccountNumber(mNumber->text());
  mAccount->setBalance(newBalance);
  mAccount->setDescription(mDescription->text());
  mAccount->setInstitution(mInstitution->text());
  mAccount->setLocale(mLocale->current());
  mAccount->setName(mName->text());
  mAccount->setStartingBalance(mStartingBalance->value());
  mApply->setEnabled(false);
}

void KMoneyThingAccountsView::hideEvent(QHideEvent *event)
{
  if (mApply->isEnabled())
    emit undoOrSave(this);
  QWidget::hideEvent(event);
}

void KMoneyThingAccountsView::slotRemoveSelectedAccount()
{
  int RetVal = KMessageBox::warningYesNo(this, i18n("Are you sure you want to delete the account?"));
  if (RetVal == KMessageBox::Yes)
  {
// TODO: check referenced transactions
    delete mFile->getAccount(mAccountCombo->currentItem());
    mFile->delAccount(mAccountCombo->currentItem());
    setFile(mFile);
  }
}

void KMoneyThingAccountsView::slotRefresh()
{
  setAccount(0);
}

void KMoneyThingAccountsView::slotLocaleChanged(const QString &id)
{
  KLocale locale("KMoneyThing");
  locale.setCountry(id);
  mStartingBalance->setPrefix(locale.currencySymbol());
  mStartingBalance->setPrecision(locale.fracDigits());
}

void KMoneyThingAccountsView::slotSomethingChanged()
{
  mApply->setEnabled(true);
}

void KMoneyThingAccountsView::slotUnimplemented()
{
  KMessageBox::sorry(this, i18n("Sorry, this feature is not implemented yet."));
}

KMoneyThingAccountsView::~KMoneyThingAccountsView()
{
}


#include "kmoneythingaccountsview.moc"
