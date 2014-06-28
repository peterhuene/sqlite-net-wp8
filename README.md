Call for contributors
=====================

I no longer have a Windows Phone device or the time to properly maintain this project. Therefore, I'm asking for someone to take over this project as either the official fork or I can add that person as a contributor to this repository.  Please contact me at \<mygithubusername\>@gmail.com.  Thanks!

sqlite-net-wp8
==============

A C++/CX wrapper for SQLite functions that [sqlite-net](https://github.com/praeclarum/sqlite-net) depends on.

This library can be used to directly call into sqlite3.dll on Windows Phone 8 from sqlite-net.

Requirements
============

* Visual Studio 2012 or later
* Windows Phone 8.0 SDK
* [SQLite for Windows Phone 8](http://www.sqlite.org/download.html) extension
* [sqlite-net source files](https://github.com/praeclarum/sqlite-net)

Using sqlite-net-wp8
====================

* Install the [sqlite-net-wp8 nuget package](https://www.nuget.org/packages/sqlite-net-wp8/) into your WP8 project:
    * Select Project -> Manage NuGet Packages...
	* Select Online -> nuget.org
	* Search for `sqlite-net-wp8` and install the package.
* Add a reference to the "SQLite for Windows Phone" extension.
    * Select Project -> Add Reference...
	* Select Windows Phone -> Extensions
	* Check "SQLite for Windows Phone" and click OK
* Copy the [sqlite-net](https://github.com/praeclarum/sqlite-net) source files (src/SQLite.cs and src/SQLiteAsync.cs) into your WP8 project.
* Add "USE_WP8_NATIVE_SQLITE" as a conditional build symbol to your project containing the sqlite-net source files (without this, SQLite will use csharp-sqlite):
    * Project -> Properties
    * Click on the Build tab.
    * In the "Configuration" dropdown, select "All configurations".
    * In the "Platform" dropdown, select "All platforms".
    * Append ";USE_WP8_NATIVE_SQLITE" to the "Conditional compilation symbols" textbox.
* Use sqlite-net as you normally would.

Setting the SQLite Temporary Directory
======================================

If you are executing SQLite commands that require the temporary directory to be set,
call `Sqlite3.set_temp_directory` before opening your database with `sqlite-net`:

    Sqlite3.set_temp_directory(Windows.Storage.ApplicationData.Current.LocalFolder.Path);

I will open a pull request to `sqlite-net` to automatically do this when opening a database,
but for now you can call this method directly.
