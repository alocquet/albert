// albert - a simple application launcher for linux
// Copyright (C) 2014 Manuel Schneider
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include <QApplication>
#include <pwd.h>
#include <unistd.h>
#include "settings.h"
#include "albert.h"
#include "albertengine.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setStyleSheet(QString::fromLocal8Bit("file:///:/resources/basicskin.qss"));

	// Load system settings
	Settings::instance()->load();

	// Override with user settings
	std::string userSettings(getpwuid(getuid())->pw_dir);
	userSettings += "/.config/albert/config";
	Settings::instance()->load(userSettings);

	// Build the indizes
	AlbertEngine::instance()->buildIndex();

	// Create the app
	AlbertWidget w;

	// Enter eventloop
	int retval = a.exec();

	// Store settings
	Settings::instance()->save(userSettings);

	return retval;
}