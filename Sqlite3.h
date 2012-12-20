#pragma once
#include "headers\sqlite3.h"

namespace Sqlite
{
    /*
    This class is simply a C++/CX wrapper around sqlite3 exports that sqlite.net depends on.
    Consult the sqlite documentation on what they do.
    */
    public ref class Sqlite3 sealed
    {
    public:
        static int sqlite3_open(Platform::String^ filename, Platform::IntPtr* db);
        static int sqlite3_open_v2(Platform::String^ filename, Platform::IntPtr* db, int flags, Platform::String^ zVfs);
        static int sqlite3_close(Platform::IntPtr db);
        static int sqlite3_busy_timeout(Platform::IntPtr db, int miliseconds);
        static int sqlite3_changes(Platform::IntPtr db);
        static int sqlite3_prepare_v2(Platform::IntPtr db, Platform::String^ query, Platform::IntPtr* statement);
        static int sqlite3_step(Platform::IntPtr statement);
        static int sqlite3_reset(Platform::IntPtr statement);
        static int sqlite3_finalize(Platform::IntPtr statement);
        static int64 sqlite3_last_insert_rowid(Platform::IntPtr db);
        static Platform::String^ sqlite3_errmsg(Platform::IntPtr db);
        static int sqlite3_bind_parameter_index(Platform::IntPtr statement, Platform::String^ name);
        static int sqlite3_bind_null(Platform::IntPtr statement, int index);
        static int sqlite3_bind_int(Platform::IntPtr statement, int index, int value);
        static int sqlite3_bind_int64(Platform::IntPtr statement, int index, int64 value);
        static int sqlite3_bind_double(Platform::IntPtr statement, int index, double value);
        static int sqlite3_bind_text(Platform::IntPtr statement, int index, Platform::String^ value);
        static int sqlite3_bind_blob(Platform::IntPtr statement, int index, const Platform::Array<uint8>^ value);	
        static int sqlite3_column_count(Platform::IntPtr statement);
        static Platform::String^ sqlite3_column_name(Platform::IntPtr statement, int index);
        static int sqlite3_column_type(Platform::IntPtr statement, int index);
        static int sqlite3_column_int(Platform::IntPtr statement, int index);
        static int64 sqlite3_column_int64(Platform::IntPtr statement, int index);
        static double sqlite3_column_double(Platform::IntPtr statement, int index);
        static Platform::String^ sqlite3_column_text(Platform::IntPtr statement, int index);
        static Platform::Array<uint8>^ sqlite3_column_blob(Platform::IntPtr statement, int index);
        static int sqlite3_column_bytes(Platform::IntPtr statement, int index);
    };
}