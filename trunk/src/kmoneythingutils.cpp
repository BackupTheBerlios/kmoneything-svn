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

#include "kmoneythingutils.h"

#include <qstring.h>
#include <qstringlist.h>
#include <qiconset.h>

#include <kglobal.h>
#include <klocale.h>
#include <ksimpleconfig.h>
#include <kstandarddirs.h>
#include <kicontheme.h>

namespace KMoneyThingUtils
{
  /*
  * Modified from KCMLocale
  *
  * Copyright (c) 1998 Matthias Hoelzer (hoelzer@physik.uni-wuerzburg.de)
  * Copyright (c) 1999 Preston Brown <pbrown@kde.org>
  * Copyright (c) 1999-2003 Hans Petter Bieker <bieker@kde.org>
  * Copyright (c) 2004 Frederick Emmott <mail@fredemmott.co.uk>
  */
  void loadCountryList(KLanguageButton *comboCountry)
  {
    KLocale locale("KMoneyThing");
  
    QString sub = QString::fromLatin1("l10n/");
  
    // clear the list
    comboCountry->clear();
  
    QStringList regionlist = KGlobal::dirs()->findAllResources("locale",
                                  sub + QString::fromLatin1("*.desktop"));
  
    for ( QStringList::ConstIterator it = regionlist.begin();
      it != regionlist.end();
      ++it )
    {
      QString tag = *it;
      int index;
  
      index = tag.findRev('/');
      if (index != -1)
        tag = tag.mid(index + 1);
  
      index = tag.findRev('.');
      if (index != -1)
        tag.truncate(index);
  
      KSimpleConfig entry(*it);
      entry.setGroup("KCM Locale");
      QString name = entry.readEntry("Name",
                                    locale.translate("without name"));
  
      QString map( locate( "locale",
                            QString::fromLatin1( "l10n/%1.png" )
                            .arg(tag) ) );
      QIconSet icon;
      if ( !map.isNull() )
        icon = KGlobal::iconLoader()->loadIconSet(map, KIcon::Small);
      comboCountry->insertSubmenu( icon, name, tag, sub, -2 );
    }
  
    // add all languages to the list
    QStringList countrylist = KGlobal::dirs()->findAllResources
      ("locale", sub + QString::fromLatin1("*/entry.desktop"));
  
    for ( QStringList::ConstIterator it = countrylist.begin();
          it != countrylist.end(); ++it )
    {
      KSimpleConfig entry(*it);
      entry.setGroup("KCM Locale");
      QString name = entry.readEntry("Name",
                                    locale.translate("without name"));
      QString submenu = entry.readEntry("Region");
  
      QString tag = *it;
      int index = tag.findRev('/');
      tag.truncate(index);
      index = tag.findRev('/');
      tag = tag.mid(index + 1);
      int menu_index = submenu.isEmpty() ? -1 : -2;
  
      QString flag( locate( "locale",
                            QString::fromLatin1( "l10n/%1/flag.png" )
                            .arg(tag) ) );
      QIconSet icon( KGlobal::iconLoader()->loadIconSet(flag, KIcon::Small) );
      comboCountry->insertItem( icon, name, tag, submenu, menu_index );
    }
  }
}
