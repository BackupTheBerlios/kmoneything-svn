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
 
#include "kmoneythinghomeview.h"

#include <qstring.h>

#include <khtml_part.h>
#include <khtmlview.h>
#include <klocale.h>

KMoneyThingHomeView::KMoneyThingHomeView(QWidget *parent, const char *name, KMoneyThingFile* currentFile)
 : QWidget(parent, name)
{
  currentFile == 0
    ? mCurrentFile = new KMoneyThingFile
    : mCurrentFile = currentFile;
    
  layout = new QHBoxLayout(this);
  khtmlPart = new KHTMLPart(this);
  layout->addWidget(khtmlPart->view());
  doHTML();
}

void KMoneyThingHomeView::doHTML()
{
  KLocale *locale = new KLocale("KMoneyThing");  

  khtmlPart->begin();
  khtmlPart->write("<html>");
  khtmlPart->write("<head><style type='text/css'>th, tr { text-align: left; padding-right: 1em }</style></head>");
  khtmlPart->write("<body><h1>");
  khtmlPart->write(i18n("Welcome to KMoneyThing") + " pre0.1");
  khtmlPart->write("</h1><hr><p>");
  khtmlPart->write(i18n("This application is still under development, and is not yet suitable for general use."));
  khtmlPart->write("</p>");
  khtmlPart->write("<h2>" + i18n("Summary") + "</h2>");
  khtmlPart->write("<table>");
  khtmlPart->write("<tr><th>" + i18n("Account") + "</th><th>" + i18n("Balance") + "</th></tr>");
  // TODO: International accounts
  for (Q_UINT32 i = 0; i < mCurrentFile->accounts(); i++)
  {
    QString accountName = mCurrentFile->getAccount(i)->name();
    QString accountBalance = mCurrentFile->getAccount(i)->name();
    khtmlPart->write(QString("<tr><td>%1</td><td>%2</td></tr>").arg(accountName).arg(accountBalance));
  }
  QString totalBalance = locale->formatMoney(0.0);
  khtmlPart->write("<tr><th>" + i18n("Total:") + "</th><th>" + totalBalance + "</th></tr>");
  khtmlPart->write("</table>");
  khtmlPart->write("</body></html>");
  khtmlPart->end();
  
  delete locale;
}

void KMoneyThingHomeView::slotRefresh()
{
  doHTML();
}

KMoneyThingHomeView::~KMoneyThingHomeView()
{
}


#include "kmoneythinghomeview.moc"
