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

#include <qlabel.h>

#include <kglobal.h>
#include <klocale.h>
#include <kmessagebox.h>

KMoneyThingAccountWizard::KMoneyThingAccountWizard(QWidget *parent, const char *name)
 : KWizard(parent, name, true)
{
  setupWelcomePage();
  setupStandardInfoPage();
  setupExtendedInfoPage();
  setupFinishedPage();
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
  
  label = new QLabel(i18n("N&ame: "), standardInfoPage);
  mName = new KLineEdit(standardInfoPage);
  label->setBuddy(mName);
  
  label = new QLabel(i18n("&Description: "), standardInfoPage);
  mDescription = new KTextEdit(standardInfoPage);
  label->setBuddy(mDescription);
  
  label = new QLabel(i18n("&Locale: "), standardInfoPage);
  mLocale = new KLanguageButton(standardInfoPage);
  label->setBuddy(mLocale);
  KMoneyThingUtils::loadCountryList(mLocale);
  mLocale->setCurrentItem(KGlobal::locale()->country());
  
  addPage(standardInfoPage, i18n("Basic Information"));
  setNextEnabled(standardInfoPage, true); // TODO: can't advance until account name is checked
  setHelpEnabled(standardInfoPage, false);
}

void KMoneyThingAccountWizard::setupExtendedInfoPage()
{
}

void KMoneyThingAccountWizard::setupFinishedPage()
{
}

KMoneyThingAccountWizard::~KMoneyThingAccountWizard()
{
}


#include "kmoneythingaccountwizard.moc"
