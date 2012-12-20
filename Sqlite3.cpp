#include "pch.h"
#include "Sqlite3.h"
#include "windows.h"
#include <vector>

using namespace Sqlite;
using namespace Platform;
using namespace std;

const int Error = 1;

vector<char> convert_to_utf8_buffer(String^ str)
{
    if (!str || str->Length() == 0)
    {
        return vector<char>();
    }

    // Get the size of the utf-8 string
    int size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, str->Data(), str->Length(), nullptr, 0, nullptr, nullptr);
    if (size == 0)
    {
        return vector<char>();
    }

    // Allocate the buffer and do the conversion
    vector<char> buffer(size + 1 /* null */);
    if (WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, str->Data(), str->Length(), buffer.data(), size, nullptr, nullptr) == 0)
    {
        return vector<char>();
    }

    return std::move(buffer);
}

String^ convert_to_string(char const* str)
{
    if (!str)
    {
        return ref new String();
    }

    // Get the size of the wide string
    int size = MultiByteToWideChar(CP_UTF8, WC_ERR_INVALID_CHARS, str, -1, nullptr, 0);
    if (size == 0)
    {
        return ref new String();
    }

    // Allocate the buffer and do the conversion
    vector<wchar_t> buffer(size + 1 /* null */);
    if (MultiByteToWideChar(CP_UTF8, WC_ERR_INVALID_CHARS, str, -1, buffer.data(), size) == 0)
    {
        return ref new String();
    }

    return ref new String(buffer.data());
}

template<typename T> T intptr_cast(IntPtr p)
{
    return reinterpret_cast<T>(p.operator void *(p));
}

int Sqlite3::sqlite3_open(String^ filename, IntPtr* db)
{
    if (!filename || !db)
    {
        return Error;
    }

    auto filename_buffer = convert_to_utf8_buffer(filename);
    if (filename_buffer.empty())
    {
        return Error;
    }

    // Use sqlite3_open instead of sqlite3_open16 so that the default code page for stored strings is UTF-8 and not UTF-16
    sqlite3* actual_db = nullptr;
    int result = ::sqlite3_open(filename_buffer.data(), &actual_db);
    *db = ref new IntPtr(actual_db);
    return result;
}

int Sqlite3::sqlite3_open_v2(String^ filename, IntPtr* db, int flags, String^ zVfs)
{
    if (!filename || !db)
    {
        return Error;
    }

    auto filename_buffer = convert_to_utf8_buffer(filename);
    if (filename_buffer.empty())
    {
        return Error;
    }

    auto zVfs_buffer = convert_to_utf8_buffer(zVfs);

    sqlite3* actual_db = nullptr;
    int result = ::sqlite3_open_v2(filename_buffer.data(), &actual_db, flags, zVfs_buffer.empty() ? nullptr : zVfs_buffer.data());
    *db = ref new IntPtr(actual_db);
    return result;
}

int Sqlite3::sqlite3_close(IntPtr db)
{
    return::sqlite3_close(intptr_cast<sqlite3*>(db));
}

int Sqlite3::sqlite3_busy_timeout(IntPtr db, int miliseconds)
{
    return ::sqlite3_busy_timeout(intptr_cast<sqlite3*>(db), miliseconds);
}

int Sqlite3::sqlite3_changes(IntPtr db)
{
    return ::sqlite3_changes(intptr_cast<sqlite3*>(db));
}

int Sqlite3::sqlite3_prepare_v2(IntPtr db, String^ query, IntPtr* statement)
{
    if (!query || !statement)
    {
        return Error;
    }

    sqlite3_stmt* actual_statement = nullptr;
    int result = ::sqlite3_prepare16_v2(intptr_cast<sqlite3*>(db), query->Data(), query->Length() * sizeof(wchar_t) /* in bytes */, &actual_statement, nullptr);
    *statement = ref new IntPtr(actual_statement);
    return result;
}

int Sqlite3::sqlite3_step(IntPtr statement)
{
    return ::sqlite3_step(intptr_cast<sqlite3_stmt*>(statement));
}

int Sqlite3::sqlite3_reset(IntPtr statement)
{
    return ::sqlite3_reset(intptr_cast<sqlite3_stmt*>(statement));
}

int Sqlite3::sqlite3_finalize(IntPtr statement)
{
    return ::sqlite3_finalize(intptr_cast<sqlite3_stmt*>(statement));
}

int64 Sqlite3::sqlite3_last_insert_rowid(IntPtr db)
{
    return ::sqlite3_last_insert_rowid(intptr_cast<sqlite3*>(db));
}

String^ Sqlite3::sqlite3_errmsg(IntPtr db)
{
    return convert_to_string(::sqlite3_errmsg(intptr_cast<sqlite3*>(db)));
}

int Sqlite3::sqlite3_bind_parameter_index(IntPtr statement, String^ name)
{
    auto name_buffer = convert_to_utf8_buffer(name);
    if (name_buffer.empty())
    {
        return Error;
    }
    return ::sqlite3_bind_parameter_index(intptr_cast<sqlite3_stmt*>(statement), name_buffer.data());
}

int Sqlite3::sqlite3_bind_null(IntPtr statement, int index)
{
    return ::sqlite3_bind_null(intptr_cast<sqlite3_stmt*>(statement), index);
}

int Sqlite3::sqlite3_bind_int(IntPtr statement, int index, int value)
{
    return ::sqlite3_bind_int(intptr_cast<sqlite3_stmt*>(statement), index, value);
}

int Sqlite3::sqlite3_bind_int64(IntPtr statement, int index, int64 value)
{
    return ::sqlite3_bind_int64(intptr_cast<sqlite3_stmt*>(statement), index, value);
}

int Sqlite3::sqlite3_bind_double(IntPtr statement, int index, double value)
{
    return ::sqlite3_bind_double(intptr_cast<sqlite3_stmt*>(statement), index, value);
}

int Sqlite3::sqlite3_bind_text(IntPtr statement, int index, String^ value)
{
    // Use transient here so that the data gets copied by sqlite
    return ::sqlite3_bind_text16(intptr_cast<sqlite3_stmt*>(statement), index, value->Data(), value->Length(), SQLITE_TRANSIENT);
}

int Sqlite3::sqlite3_bind_blob(IntPtr statement, int index, const Array<uint8>^ value)
{
    // Use transient here so that the data gets copied by sqlite
    return ::sqlite3_bind_blob(intptr_cast<sqlite3_stmt*>(statement), index, value->Data, value->Length, SQLITE_TRANSIENT);
}

int Sqlite3::sqlite3_column_count(IntPtr statement)
{
    return ::sqlite3_column_count(intptr_cast<sqlite3_stmt*>(statement));
}

String^ Sqlite3::sqlite3_column_name(IntPtr statement, int index)
{
    return convert_to_string(::sqlite3_column_name(intptr_cast<sqlite3_stmt*>(statement), index));
}

int Sqlite3::sqlite3_column_type(IntPtr statement, int index)
{
    return ::sqlite3_column_type(intptr_cast<sqlite3_stmt*>(statement), index);
}

int Sqlite3::sqlite3_column_int(IntPtr statement, int index)
{
    return ::sqlite3_column_int(intptr_cast<sqlite3_stmt*>(statement), index);
}

int64 Sqlite3::sqlite3_column_int64(IntPtr statement, int index)
{
    return ::sqlite3_column_int64(intptr_cast<sqlite3_stmt*>(statement), index);
}

double Sqlite3::sqlite3_column_double(IntPtr statement, int index)
{
    return ::sqlite3_column_double(intptr_cast<sqlite3_stmt*>(statement), index);
}

String^ Sqlite3::sqlite3_column_text(IntPtr statement, int index)
{
    return ref new String(reinterpret_cast<wchar_t const*>(::sqlite3_column_text16(intptr_cast<sqlite3_stmt*>(statement), index)));
}

Array<uint8>^ Sqlite3::sqlite3_column_blob(IntPtr statement, int index)
{
    int count = Sqlite3::sqlite3_column_bytes(statement, index);
    Array<uint8>^ blob = ref new Array<uint8>(count < 0 ? 0 : count);

    if (count > 0)
    {
        auto data = static_cast<uint8 const*>(::sqlite3_column_blob(intptr_cast<sqlite3_stmt*>(statement), index));
        std::copy(data, data + count, blob->Data);
    }

    return blob;
}

int Sqlite3::sqlite3_column_bytes(IntPtr statement, int index)
{
    return ::sqlite3_column_bytes(intptr_cast<sqlite3_stmt*>(statement), index);
}

