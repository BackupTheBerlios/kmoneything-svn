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
 : QWidget(parent, name)
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
  
  QGridLayout *grid = new QGridLayout(this, 4, 2);
  grid->setSpacing(hbox->spacing());
  mainLayout->addItem(grid);
  
  mName = new KLineEdit(this);
  mNameLabel = new QLabel(mName, i18n("Na&me:"), this);
  grid->addWidget(mNameLabel, 0, 0);
  grid->addWidget(mName, 0, 1);
  
  mInstitution = new KLineEdit(this);
  mInstitutionLabel = new QLabel(mInstitution, i18n("&Institution:"), this);
  grid->addWidget(mInstitutionLabel, 1, 0);
  grid->addWidget(mInstitution, 1, 1);
  
  mNumber = new KLineEdit(this);
  mNumberLabel = new QLabel(mNumber, i18n("N&umber:"), this);
  grid->addWidget(mNumberLabel, 2, 0);
  grid->addWidget(mNumber, 2, 1);
  
  mDescription = new KTextEdit(this);
  mDescriptionLabel = new QLabel(mDescription, i18n("&Description:"), this);
  grid->addWidget(mDescriptionLabel, 3, 0);
  grid->addWidget(mDescription, 3, 1);

  seperator = new QFrame(this);
  seperator->setFrameStyle(QFrame::HLine | QFrame::Sunken);
  mainLayout->add(seperator);
  
  hbox = new QHBoxLayout(this, 3);
  mainLayout->addItem(hbox);
  
  QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding);
  hbox->addItem(spacer);
  
  mApply = new KPushButton(SmallIconSet("apply"), i18n("&Apply"), this);
  connect(mApply, SIGNAL(clicked()), this, SLOT(slotUnimplemented()));
  hbox->add(mApply);
  
  mRemove = new KPushButton(SmallIconSet("fileclose"), i18n("&Remove"), this);
  connect(mRemove, SIGNAL(clicked()), this, SLOT(slotUnimplemented()));
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
  mApply->setEnabled(false);
  
  if (mFile->accounts() == 0)
  {
    mAccount = 0;
    
    mAccountCombo->setEnabled(false);
    
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
  
    mAccountCombo->setEnabled(true);
    mAccountCombo->setCurrentItem(id);
    
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
        mNumberLabel->setEnabled(true);
        mNumber->setEnabled(false);
        mNumber->setText("");
    }
    else
        KMessageBox::error(this, i18n("Unknown account type: %1").arg(mAccount->type()));
  }

}

void KMoneyThingAccountsView::slotUnimplemented()
{
  KMessageBox::sorry(this, i18n("Sorry, this feature is not implemented yet."));
}

KMoneyThingAccountsView::~KMoneyThingAccountsView()
{
}


#include "kmoneythingaccountsview.moc"
