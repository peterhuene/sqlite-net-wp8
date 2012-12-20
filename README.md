sqlite-net-wp8
==============

A C++/CX wrapper for sqlite functions that sqlite.net depends on.

This library can be used to directly call into sqlite3.dll on Windows Phone 8 from sqlite.net.

Requirements
============

* Visual Studio 2012
* Windows Phone 8.0 SDK
* SQLite for Windows Phone (install via the "Tools -> Extensions and Updates" menu item in Visual Studio).

Remarks
======

This library is intended to be used with [sqlite-net](https://github.com/praeclarum/sqlite-net).

However, sqlite-net currently won't work with this library.  It has a dependency on [csharp-sqlite](http://code.google.com/p/csharp-sqlite/) instead, which is a C# re-implementation of sqlite.

Instead, [use my fork of sqlite-net](https://github.com/peterhuene/sqlite-net) that does.  I'll work on getting the sqlite-net changes pushed upstream (needs more work to make it build against both sqlite-net-wp8 and csharp-sqlite),

Using sqlite-net-wp8
====================

* Clone or copy the sqlite-net-wp8 source files into your solution directory.
* Add the project to your solution.
* From your Windows Phone project, add a project reference to the SQLite project.
* Clone or copy the [sqlite-net](https://github.com/peterhuene/sqlite-net) source files into your Windows Phone project.
* Use sqlite.net.
