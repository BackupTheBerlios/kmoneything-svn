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
 
#include "kmoneything.h"
#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <klocale.h>

static const char description[] =
    I18N_NOOP("A personal finance manager for KDE");

static const char version[] = "Pre-0.1: $Rev$";

static KCmdLineOptions options[] =
{
//    { "+[URL]", I18N_NOOP( "Document to open." ), 0 },
    KCmdLineLastOption
};

int main(int argc, char **argv)
{
    KAboutData about("kmoneything", I18N_NOOP("KMoneyThing"), version, description,
                     KAboutData::License_GPL, "(c) 2004 Fred Emmott", 0, "http://kmoneything.fredemmott.co.uk", "mail@fredemmott.co.uk");
    about.addAuthor( "Fred Emmott", I18N_NOOP("Lead developer"), "mail@fredemmott.co.uk", "http://www.fredemmott.co.uk" );
    about.addCredit( "Hans Petter Bieker", I18N_NOOP("Locale tools from KCMLocale"), "bieker@kde.org" );
    about.addCredit( "Martijn Klingens", I18N_NOOP("Locale tools from KCMLocale"), "mklingens@yahoo.com" );
    KCmdLineArgs::init(argc, argv, &about);
    KCmdLineArgs::addCmdLineOptions( options );
    KApplication app;
    KMoneyThing *mainWin = 0;

    if (app.isRestored())
    {
        RESTORE(KMoneyThing);
    }
    else
    {
        // no session.. just start up normally
        KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

        /// @todo do something with the command line args here

        mainWin = new KMoneyThing();
        app.setMainWidget( mainWin );
        mainWin->show();

        args->clear();
    }

    // mainWin has WDestructiveClose flag by default, so it will delete itself.
    return app.exec();
}

