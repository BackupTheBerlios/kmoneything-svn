# set the include path for X, qt and KDE
INCLUDES = -I$(top_srcdir)/src $(all_includes)

# these are the headers for your project
noinst_HEADERS = kmoneything.h kmoneythingmainwidget.h kmoneythingaccount.h kmoneythingtransaction.h kmoneythingtransaction.h kmoneythingsubtransaction.h kmoneythingcashaccount.h kmoneythingfile.h kmoneythingrecurringtransaction.h kmoneythingaccountsview.h kmoneythingaccountwizard.h klanguagebutton.h kmoneythingutils.h kmoneythingview.h

# let automoc handle all of the meta source files (moc)
METASOURCES = AUTO

messages: rc.cpp
	$(XGETTEXT) *.cpp -o $(podir)/kmoneything.pot

KDE_ICON = kmoneything

#########################################################################
# APPLICATION SECTION
#########################################################################
# this is the program that gets installed.  it's name is used for all
# of the other Makefile.am variables
bin_PROGRAMS = kmoneything

# the application source, library search path, and link libraries
kmoneything_SOURCES = main.cpp kmoneything.cpp kmoneythingui.rc kmoneythingmainwidget.cpp kmoneythinghomeview.cpp kmoneythingtransaction.cpp kmoneythingsubtransaction.cpp kmoneythingcashaccount.cpp kmoneythingaccount.cpp kmoneythingfile.cpp kmoneythingrecurringtransaction.cpp kmoneythingaccountsview.cpp kmoneythingaccountwizard.cpp klanguagebutton.cpp kmoneythingutils.cpp kmoneythingview.cpp
kmoneything_LDFLAGS = $(KDE_RPATH) $(all_libraries)
kmoneything_LDADD = $(LIB_KIO) $(LIB_KHTML) $(LIB_KDEUI)

# this is where the desktop file will go 
shelldesktopdir = $(kde_appsdir)/Utilities
shelldesktop_DATA = kmoneything.desktop

# this is where the shell's XML-GUI resource file goes
shellrcdir = $(kde_datadir)/kmoneything
shellrc_DATA = kmoneythingui.rc

