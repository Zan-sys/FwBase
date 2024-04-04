/*
    Версия 6 от 2024.04.04 автор ZAN
*/
#ifndef FW_BASE_HPP // Begin FW_BASE_HPP
#define FW_BASE_HPP
// ---------------------------------------------------------------------------
#include <cstring>
#include <string>
#include <string_view>
#include <regex>
#include <iostream>

#include <memory>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>

#include <locale>
#include <iomanip>
#include <codecvt>
#include <ctime>
#include <chrono>

#include <set>
#include <map>
#include <array>
#include <deque>
#include <list>

#include <mutex>
#include <atomic>
#include <thread>
#include <condition_variable>

#include <cmath>
#include <limits>

#if defined(EXPERIMENTAL_FILESYSTEM)
    #include <experimental/filesystem>
#else
    #include <filesystem>
#endif
// ---------------------------------------------------------------------------
#if defined(EXPERIMENTAL_FILESYSTEM)
    namespace stdfs = std::experimental::filesystem;
#else
    namespace stdfs = std::filesystem;
#endif
// ---------------------------------------------------------------------------
#ifdef WINDOWS
    #define localtime_r(_Time, _Tm) localtime_s(_Tm, _Time)
    #define gmtime_r(_Time, _Tm) gmtime_s(_Tm, _Time)
#endif
// ---------------------------------------------------------------------------
//
// Макросы для удобной кодировки строк
//
#define T_VOID_AUTO_ENCODING(VALUE)                 (VALUE = Framework::String::TEncoding<decltype(VALUE)>::Auto(VALUE))
#define T_VOID_AUTO_ENCODING_LOC(VALUE, LOC)        (VALUE = Framework::String::TEncoding<decltype(VALUE)>::Auto(VALUE, LOC))
#define VOID_AUTO_ENCODING(TYPE, VALUE)             (VALUE = Framework::String::TEncoding<TYPE>::Auto(VALUE))
#define VOID_AUTO_ENCODING_LOC(TYPE, VALUE, LOC)    (VALUE = Framework::String::TEncoding<TYPE>::Auto(VALUE, LOC))

#define T_AUTO_ENCODING(VALUE)                      Framework::String::TEncoding<decltype(VALUE)>::Auto(VALUE)
#define T_AUTO_ENCODING_LOC(VALUE, LOC)             Framework::String::TEncoding<decltype(VALUE)>::Auto(VALUE, LOC)
#define T_UTF8_CP1251_ENCODING(VALUE)               Framework::String::TEncoding<decltype(VALUE)>::Utf8ToCp1251(VALUE)
#define T_UTF8_CP1251_ENCODING_LOC(VALUE, LOC)      Framework::String::TEncoding<decltype(VALUE)>::Utf8ToCp1251(VALUE, LOC)
#define T_CP1251_UTF8_ENCODING(VALUE)               Framework::String::TEncoding<decltype(VALUE)>::Cp1251ToUtf8(VALUE)
#define T_CP1251_UTF8_ENCODING_LOC(VALUE, LOC)      Framework::String::TEncoding<decltype(VALUE)>::Cp1251ToUtf8(VALUE, LOC)

#define AUTO_ENCODING(TYPE, VALUE)                  Framework::String::TEncoding<TYPE>::Auto(VALUE)
#define AUTO_ENCODING_LOC(TYPE, VALUE, LOC)         Framework::String::TEncoding<TYPE>::Auto(VALUE, LOC)
#define UTF8_CP1251_ENCODING(TYPE, VALUE)           Framework::String::TEncoding<TYPE>::Utf8ToCp1251(VALUE)
#define UTF8_CP1251_ENCODING_LOC(TYPE, VALUE, LOC)  Framework::String::TEncoding<TYPE>::Utf8ToCp1251(VALUE, LOC)
#define CP1251_UTF8_ENCODING(TYPE, VALUE)           Framework::String::TEncoding<TYPE>::Cp1251ToUtf8(VALUE)
#define CP1251_UTF8_ENCODING_LOC(TYPE, VALUE, LOC)  Framework::String::TEncoding<TYPE>::Cp1251ToUtf8(VALUE, LOC)
// ---------------------------------------------------------------------------
namespace Framework {
    // ---------------------------------------------------------------------------
    //
    // Условная компиляция
    //
    namespace Constexpr
    {
        template<typename T> constexpr bool is_string = std::is_same<T, std::string>::value;
        template<typename T> constexpr bool is_wstring = std::is_same<T, std::wstring>::value;
        template<typename T> constexpr bool is_string_wstring = is_string<T> || is_wstring<T>;
        template<typename T> constexpr bool is_not_string_wstring = !is_string<T> && !is_wstring<T>;

        template<typename T> constexpr bool is_bool = std::is_same<T, bool>::value;
        template<typename T> constexpr bool is_uint8 = std::is_same<T, uint8_t>::value;
        template<typename T> constexpr bool is_int8 = std::is_same<T, int8_t>::value;
        template<typename T> constexpr bool is_integer = std::numeric_limits<T>::is_integer;
        template<typename T> constexpr bool is_float = std::is_floating_point<T>::value;
        template<typename T> constexpr bool is_integer_float = is_integer<T> || is_float<T>;
        template<typename T> constexpr bool is_mutex = std::is_same<T, std::mutex>::value;
        template<typename T> constexpr bool is_tmutex = std::is_same<T, std::timed_mutex>::value;
        template<typename T> constexpr bool is_any_mutex = is_mutex<T> || is_tmutex<T>;
    }
    // ---------------------------------------------------------------------------
    //
    // Работка со строками
    //
    namespace String
    {
        // ---------------------------------------------------------------------------
        //
        // Шаблон содержит статические методы для конвертирования строк
        //
        template<typename T> class TConverter
        {
        private:
            static_assert(Constexpr::is_string_wstring<T>, "This template requires the type std::string or std::wstring.");

            //
            // std::wstring to std::string
            //
            static std::string WStringToString(const std::wstring& w_str, const std::locale& loc = std::locale())
            {
                using namespace std;

                if (w_str.empty())
                {
                    return string();
                }

                // typedef wstring::traits_type::state_type state_type;
                using state_type = wstring::traits_type::state_type;
                // typedef codecvt<wchar_t, char, state_type> CVT;
                using CVT = codecvt<wchar_t, char, state_type>;

                const CVT& cvt = use_facet<CVT>(loc);

                string s_str(cvt.max_length() * size(w_str), '\0');
                state_type state = state_type();

                const wchar_t* from_beg(&w_str[0]);
                const wchar_t* from_end(from_beg + size(w_str));
                const wchar_t* from_nxt;

                char* to_beg(&s_str[0]);
                char* to_end(to_beg + size(s_str));
                char* to_nxt;

                string::size_type sz(0);
                codecvt_base::result r;

                do
                {
                    r = cvt.out(state, from_beg, from_end, from_nxt, to_beg, to_end, to_nxt);
                    switch (r)
                    {
                        case codecvt_base::error:
                            throw runtime_error("error converting wstring to string");

                        case codecvt_base::partial:
                            sz += to_nxt - to_beg;
                            s_str.resize(2 * size(s_str));
                            to_beg = &s_str[sz];
                            to_end = &s_str[0] + size(s_str);
                            break;

                        case codecvt_base::noconv:
                            s_str.resize(sz + (from_end - from_beg) * sizeof(wchar_t));
                            memcpy(&s_str[sz], from_beg, (from_end - from_beg) * sizeof(wchar_t));
                            r = codecvt_base::ok;
                            break;

                        case codecvt_base::ok:
                            sz += to_nxt - to_beg;
                            s_str.resize(sz);
                            break;
                    }
                } while (r != codecvt_base::ok);

                return s_str;
            }

            //
            // std::string to std::wstring
            //
            static std::wstring StringToWString(const std::string& s_str, const std::locale& loc = std::locale())
            {
                using namespace std;

                if (s_str.empty()) 
                {
                    return wstring();
                }

                // typedef string::traits_type::state_type state_type;
                using state_type = string::traits_type::state_type;
                // typedef codecvt<wchar_t, char, state_type> CVT;
                using CVT = codecvt<wchar_t, char, state_type>;

                const CVT& cvt = use_facet<CVT>(loc);
                
                wstring w_str(size(s_str), '\0');
                state_type state = state_type();

                const char* from_beg(&s_str[0]);
                const char* from_end = from_beg + size(s_str);
                const char* from_nxt;

                wchar_t* to_beg(&w_str[0]);
                wchar_t* to_end = to_beg + size(w_str);
                wchar_t* to_nxt;

                wstring::size_type sz(0);
                codecvt_base::result r;

                do
                {
                    r = cvt.in(state, from_beg, from_end, from_nxt, to_beg, to_end, to_nxt);
                    switch (r)
                    {
                        case codecvt_base::error:
                            throw runtime_error("Error converting string to wstring. Locale: " + loc.name());

                        case codecvt_base::partial:
                            sz += to_nxt - to_beg;
                            w_str.resize(2 * size(w_str));
                            to_beg = &w_str[sz];
                            to_end = &w_str[0] + size(w_str);
                            break;

                        case codecvt_base::noconv:
                            w_str.resize(sz + (from_end - from_beg));
                            memcpy(&w_str[sz], from_beg, (std::size_t)(from_end - from_beg));
                            r = codecvt_base::ok;
                            break;

                        case codecvt_base::ok:
                            sz += to_nxt - to_beg;
                            w_str.resize(sz);
                            break;
                    }
                } while (r != codecvt_base::ok);

                return w_str;
            }

        public:
            //
            // char* to std::string or std::wstring
            //
            static T ToString(const char* value, const std::locale& loc = std::locale())
            {
                if constexpr(Constexpr::is_string<T>) // Return std::string
                {
                    return std::string(value);
                }
                else // Return std::wstring
                {
                    return ToString(value, strlen(value), loc);
                }
            }
            //
            // char*(size) to std::string or std::wstring
            //
            static T ToString(const char* value, size_t size, const std::locale& loc = std::locale())
            {
                if constexpr(Constexpr::is_string<T>) // Return std::string
                {
                    return std::string(value, size);
                }
                else // Return std::wstring
                {
                    return ToString(std::string(value, size), loc);
                }
            }
            //
            // std::string to std::string or std::wstring
            //
            static T ToString(const std::string& value, const std::locale& loc = std::locale())
            {
                if constexpr(Constexpr::is_string<T>) // Return std::string
                {
                    return value;
                }
                else // Return std::wstring
                {
                    return StringToWString(value, loc);
                }
            }
            //
            // wchar_t* to std::string or std::wstring
            //
            static T ToString(const wchar_t* value, const std::locale& loc = std::locale())
            {
                if constexpr(Constexpr::is_string<T>) // Return std::string
                {
                    return ToString(std::wstring(value), loc);
                }
                else // Return std::wstring
                {
                    return std::wstring(value);
                }
            }
            //
            // wchar_t(size) to std::string or std::wstring
            //
            static T ToString(const wchar_t* value, size_t size, const std::locale& loc = std::locale())
            {
                if constexpr(Constexpr::is_string<T>) // Return std::string
                {
                    return ToString(std::wstring(value, size), loc);
                }
                else // Return std::wstring
                {
                    return std::wstring(value, size);
                }
            }
            //
            // std::wstring to std::string or std::wstring
            //
            static T ToString(const std::wstring& value, const std::locale& loc = std::locale())
            {
                if constexpr(Constexpr::is_string<T>) // Return std::string
                {
                    return WStringToString(value, loc);
                }
                else // Return std::wstring
                {
                    return value;
                }
            }
            //
            // char to std::string or std::wstring
            //
            static T ToString(const char value, const std::locale& loc = std::locale())
            {
                if constexpr(Constexpr::is_string<T>) // Return std::string
                {
                    return std::string(1, value);
                }
                else // Return std::wstring
                {
                    std::string temp(1, value);
                    return ToString(temp, loc);
                }
            }
            //
            // wchar_t to std::string or std::wstring
            //
            static T ToString(const wchar_t value, const std::locale& loc = std::locale())
            {
                if constexpr(Constexpr::is_string<T>) // Return std::string
                {
                    std::wstring temp(1, value);
                    return ToString(temp, loc);
                }
                else // Return std::wstring
                {
                    return std::wstring(1, value);
                }
            }
            //
            // u16string to std::string or std::wstring
            //
            static T ToString(const std::u16string& value, const std::locale& loc = std::locale())
            {
                std::wstring temp(value.begin(), value.end());

                if constexpr(Constexpr::is_string<T>)
                {
                    return WStringToString(temp, loc);
                }
                else
                {
                    return temp;
                }
            }
            //
            // std::string or std::wstring to u16string
            //
            static std::u16string ToU16string(const T& value, const std::locale& loc = std::locale())
            {
                std::wstring wstr;

                if constexpr(Constexpr::is_string<T>)
                {
                    wstr =  StringToWString(value, loc);
                }
                else
                {
                    wstr = value;
                }

                if (sizeof(wchar_t) == sizeof(char16_t))
                {
                    return std::u16string(wstr.begin(), wstr.end());
                }
                else
                {
                    const size_t max_len = 2 * wstr.length() + 1;
                    std::u16string result;

                    result.reserve(max_len);

                    for (const wchar_t& wc : wstr)
                    {
                        const std::wint_t chr = wc;

                        if (chr < 0 || chr > 0x10FFFF || (chr >= 0xD800 && chr <= 0xDFFF))
                        {
                            constexpr char16_t sentinel = u'\uFFFD';
                            result.push_back(sentinel);
                        }
                        else if ( chr < 0x10000UL )
                        {
                            result.push_back(static_cast<char16_t>(wc));
                        }
                        else
                        {
                            const char16_t leading = static_cast<char16_t>(((chr-0x10000UL) / 0x400U) + 0xD800U);
                            const char16_t trailing = static_cast<char16_t>(((chr-0x10000UL) % 0x400U) + 0xDC00U);
                            result.append({leading, trailing});
                        }
                    }

                    result.shrink_to_fit();
                    return result;
                }
            }
            //
            // stdfs::path to std::wstring to u16string
            //
            static T ToString(const stdfs::path& value, const std::locale& loc = std::locale())
            {
                if constexpr(Constexpr::is_string<T>) // Return std::string
                {
                    return value.string();
                }
                else // Return std::wstring
                {
                    return value.wstring();
                }
            }
            //
            // bool, int, float, double to std::string or std::wstring
            //
            // precision - точность для типов с плавающей запятой (std::numeric_limits<double>::max_digits10)
            // fixed - дробный тип с фиксированным положением разделителя
            //
            template<typename Type> static T ToString(Type value, const std::locale& loc = std::locale(), const int precision = -1, const bool fixed = false)
            {
                using namespace Constexpr;

                if constexpr(is_bool<Type>)
                {
                    if constexpr(is_string<T>) { return value ? "true" : "false"; }
                    else { return value ? L"true" : L"false"; }
                }
                if constexpr(is_integer<Type>)
                {
                    if constexpr(is_string<T>) { return std::to_string(value); }
                    else { return std::to_wstring(value); }
                }
                if constexpr(is_float<Type>)
                {
                    std::basic_stringstream<typename T::value_type, std::char_traits<typename T::value_type>, std::allocator<typename T::value_type>> stream;

                    if (fixed)
                    {
                        stream << std::fixed;
                    }

                    if (precision > 0)
                    {
                        stream << std::setprecision(precision);
                    }

                    stream << value;
                    return stream.str();
                }
                else
                {
                    static_assert(is_integer_float<Type>, "Expected types: int, unsigned int, long, unsigned long, long long, unsigned long long, float, double, long double.");
                }
            }
            //
            // int to hex string
            // Add_0x - добавлять префикс 0x к числу
            //
            template<typename Type> static T ToHexString(Type value, bool add_0x = true, bool uppercase = true, const std::locale& loc = std::locale())
            {
                using namespace std;
                using namespace Constexpr;

                static_assert(is_integer<Type>, "Expected types: int, unsigned int, long, unsigned long, long long, unsigned long long.");

                array<typename T::value_type, 17> hex;
                array<typename T::value_type, 3> hex_pref;

                if constexpr(is_string<T>)
                {
                    hex = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', '\0' };
                    hex_pref = { '0', 'x', '\0' };
                }
                else
                {
                    hex = { L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'a', L'b', L'c', L'd', L'e', L'f', L'\0' };
                    hex_pref = { L'0', L'x', L'\0' };
                }

                if (uppercase)
                {
                    std::transform(begin(hex), end(hex), begin(hex), [&](typename T::value_type value) {
                        return std::toupper<typename T::value_type>(value, loc);
                    });
                }

                unsigned char* _data = reinterpret_cast<decltype(_data)>(&value);
                vector<unsigned char> buffer(_data, _data + sizeof(Type));
                std::basic_stringstream<typename T::value_type, std::char_traits<typename T::value_type>, std::allocator<typename T::value_type>> sstream;

                if (add_0x)
                {
                    sstream << std::data(hex_pref);
                }

                for_each(rbegin(buffer), rend(buffer), [&](unsigned char _value) { sstream << hex.at(_value >> 4) << hex.at(_value & 0x0F); });

                return sstream.str();
            }
            //
            // std::string or std::wstring to TYPE
            // def - значение в случае ошибки при преобразовании
            //
            template<typename Type> static Type FromString(T value, const Type def, const std::locale& loc = std::locale())
            {
                using namespace std;
                using namespace Constexpr;

                if constexpr(is_float<Type>) // Убираем зависимость от разделителя дробной части
                {
                    typename T::value_type dot;
                    typename T::value_type comma;
                    typename T::value_type decimal_point = use_facet<numpunct<typename T::value_type>>(loc).decimal_point();

                    if constexpr(is_string<Type>) { dot = '.'; comma = ','; }
                    else { dot = L'.'; comma = L','; }
                    
                    if (value.find(decimal_point) == T::npos) // not found
                    {
                        if (decimal_point == dot)
                        {
                            if (auto f_comma = value.find(comma); f_comma != T::npos)
                            {
                                value.replace(f_comma, 1, 1, decimal_point);
                            }
                        }
                        else
                        {
                            if (auto f_dot = value.find(dot); f_dot != T::npos)
                            {
                                value.replace(f_dot, 1, 1, decimal_point);
                            }
                        }
                    }
                }

                Type t;
                std::basic_stringstream<typename T::value_type, std::char_traits<typename T::value_type>, std::allocator<typename T::value_type>> stream;

                if constexpr(is_bool<Type>) // stringstream понимает bool только в нижнем регистре, для bool добавляется флаг boolalpha
                {
                    transform(begin(value), end(value), begin(value), [&](typename T::value_type c) { return tolower<typename T::value_type>(c, loc); });

                    stream << std::boolalpha << value;
                    stream >> std::boolalpha >> t;
                }
                else if constexpr(is_uint8<Type>) // Интерпретируем uint8_t как число а не как символ
                {
                    uint16_t temp(0);
                    stream << value;
                    stream >> temp;
                    t = temp > (std::numeric_limits<uint8_t>::max)() ? def : static_cast<uint8_t>(temp);
                }
                else if constexpr(is_int8<Type>) // Интерпретируем int8_t как число а не как символ
                {
                    int16_t temp(0);
                    stream << value;
                    stream >> temp;

                    if (temp > 0)
                    {
                        t = temp > (std::numeric_limits<int8_t>::max)() ? def : static_cast<int8_t>(temp);
                    }
                    else
                    {
                        t = temp < (std::numeric_limits<int8_t>::min)() ? def : static_cast<int8_t>(temp);
                    }
                }
                else
                {
                    stream << value;
                    stream >> t;
                }

                if (stream.fail())
                    return def;
                else
                    return t;
            }
            //
            // Инициализация пустой строки
            //
            static T EmptyString()
            {
                if constexpr(Constexpr::is_string<T>) // Return std::string
                {
                    return std::string("");
                }
                else // Return std::wstring
                {
                    return std::wstring(L"");
                }
            }
        };

        using TStringConverter = TConverter<std::string>;
        using TWStringConverter = TConverter<std::wstring>;
        // ---------------------------------------------------------------------------
        //
        // Шаблон обеспечивает форматирование строк
        //
        template <typename T> class TFormater
        {
        private:
            static_assert(Constexpr::is_string_wstring<T>, "This template requires the type std::string or std::wstring.");

            static T _format(const T& format, std::vector<T> &str_list, const std::locale& loc)
            {
                T open, close;

                if constexpr(Constexpr::is_string<T>) { open = "{"; close = "}"; }
                else { open = L"{"; close = L"}"; }

                T result = format;

                for (size_t i = 0; i < size(str_list); i++)
                {
                    T temp = open + TConverter<T>::ToString(i, loc) + close;
                    ReplaceAll(result, temp, str_list.at(i));
                }
                
                return result;
            }

            template<typename Arg> static T _format(const T& format, std::vector<T>& str_list, const std::locale& loc, Arg arg)
            {
                str_list.push_back(TConverter<T>::ToString(arg, loc));
                return _format(format, str_list, loc);
            }

            template<typename Arg, typename... Args> static T _format(const T& format, std::vector<T>& str_list, const std::locale& loc, Arg arg, Args... args)
            {
                str_list.push_back(TConverter<T>::ToString(arg, loc));
                return _format(format, str_list, loc, args...);
            }

            static void _concatenate(T& source, std::vector<T> &str_list)
            {
                using namespace std;
                for_each(begin(str_list), end(str_list), [&](T value) { source += value; });
            }

            template<typename Arg> static void _concatenate(T& source, std::vector<T>& str_list, const std::locale& loc, Arg arg)
            {
                str_list.push_back(TConverter<T>::ToString(arg, loc));
                _concatenate(source, str_list);
            }

            template<typename Arg, typename... Args> static void _concatenate(T& source, std::vector<T>& str_list, const std::locale& loc, Arg arg, Args... args)
            {
                str_list.push_back(TConverter<T>::ToString(arg, loc));
                _concatenate(source, str_list, loc, args...);
            }

        public:
            //
            // Поиск и замена строки
            //
            static T& ReplaceAll(T& source, const T& search, const T& value)
            {
                size_t pos = source.find(search);

                while (pos != T::npos)
                {
                    source.replace(pos, search.length(), value);

                    pos += value.length();

                    pos = source.find(search, pos);
                }

                return source;
            }
            //
            // Поднятие в верхний регистр первого символа
            //
            static T& UpperFirst(T& source, const std::locale& loc = std::locale())
            {
                using namespace std;

                wstring temp (TConverter<wstring>::ToString(source, loc));

                temp.at(0) = toupper<wchar_t>(temp.at(0), loc);

                source = TConverter<T>::ToString(temp, loc);

                return source;
            }
            //
            // Преобразование строки в верхний регистр
            //
            static T& UpperCase(T& source, const std::locale& loc = std::locale())
            {
                using namespace std;

                wstring temp (TConverter<wstring>::ToString(source, loc));

                transform(begin(temp), end(temp), begin(temp), [&](wchar_t c) { return toupper<wchar_t>(c, loc); });

                source = TConverter<T>::ToString(temp, loc);

                return source;
            }
            //
            // Преобразование строки в нижний регистр
            //
            static T& LowerCase(T& source, const std::locale& loc = std::locale())
            {
                using namespace std;

                wstring temp (TConverter<wstring>::ToString(source, loc));

                transform(begin(temp), end(temp), begin(temp), [&](wchar_t c) { return tolower<wchar_t>(c, loc); });

                source = TConverter<T>::ToString(temp, loc);

                return source;
            }
            //
            // Форматированный вывод даты и времени. Шаблон по функции put_time.
            //
            static T LocalTime(const T& format, const std::locale& loc = std::locale())
            {
                std::tm _tm = {0};

                auto t = time(nullptr);

                localtime_r(&t, &_tm);

                std::basic_stringstream<typename T::value_type> stream;

                stream << std::put_time(&_tm, format.c_str());

                return stream.str();
            }
            //
            // Формирование строки по шаблону {0}{1}{2}
            //
            template<typename Arg, typename... Args> static T Format(const T& format, Arg arg, Args... args)
            {
                std::vector<T> str_list;
                return _format(format, str_list, std::locale(), arg, args...);
            }
            template<typename Arg, typename... Args> static T Format(const T& format, const std::locale& loc, Arg arg, Args... args)
            {
                std::vector<T> str_list;
                return _format(format, str_list, loc, arg, args...);
            }
            template<typename Arg, typename... Args> static void VoidFormat(T& dest, const T& format, Arg arg, Args... args)
            {
                dest = Format(format, arg, args...);
            }
            template<typename Arg, typename... Args> static void VoidFormat(T& dest, const T& format, const std::locale& loc, Arg arg, Args... args)
            {
                dest = Format(format, loc, arg, args...);
            }
            //
            // Соединение строк
            //
            template<typename Arg, typename... Args> static void VoidConcatenate(T& source, Arg arg, Args... args)
            {
                std::vector<T> str_list;
                _concatenate(source, str_list, std::locale(), arg, args...);
            }
            template<typename Arg, typename... Args> static void VoidConcatenate(T& source, const std::locale& loc, Arg arg, Args... args)
            {
                std::vector<T> str_list;
                _concatenate(source, str_list, loc, arg, args...);
            }
            template<typename Arg, typename... Args> static T Concatenate(Arg arg, Args... args)
            {
                T source;
                VoidConcatenate(source, arg, args...);
                return source;
            }
            template<typename Arg, typename... Args> static T Concatenate(const std::locale& loc, Arg arg, Args... args)
            {
                T source;
                VoidConcatenate(source, loc, arg, args...);
                return source;
            }
        };

        using TStringFormater = TFormater<std::string>;
        using TWStringFormater = TFormater<std::wstring>;
        // ---------------------------------------------------------------------------
        //
        // Шаблон содержит дополнительные функции для работы со строками
        //
        template <typename T> class TExtension
        {
        private:
            static_assert(Constexpr::is_string_wstring<T>, "This template requires the type std::string or std::wstring.");

        public:
            //
            // Сравнение строк
            //
            static bool Compare(const T& source1, const T& source2, bool case_insensitive = false, const std::locale& loc = std::locale())
            {
                if (case_insensitive)
                {
                    T temp1(source1);
                    TFormater<T>::LowerCase(temp1, loc);

                    T temp2(source2);
                    TFormater<T>::LowerCase(temp2, loc);
                    
                    return temp1.compare(temp2) == 0;
                }
                else
                {
                    return source1.compare(source2) == 0;
                }
            }
            //
            // Одна из строк source2 должна совпасть с source1
            //
            static bool Compare(const T& source1, const std::vector<T>& source2, bool case_insensitive = false, const std::locale& loc = std::locale())
            {
                bool result(false);

                for(const auto& value : source2)
                {
                    result = result || Compare(source1, value, case_insensitive, loc);
                    if (result) break;
                }

                return result;
            }
            //
            // source1 должен совпасть с одним из значений source2, возвращается значение под тем же индексом из result иначе def
            //
            template <typename Type> static Type Compare(const T& source1, const std::vector<T>& source2, const std::vector<Type>& result, const Type& def, bool case_insensitive = false, const std::locale& loc = std::locale())
            {
                using namespace std;

                if (size(source2) == size(result))
                {
                    for (auto i = begin(source2); i != end(source2); i++)
                    {
                        if (Compare(source1, *i, case_insensitive, loc))
                        {
                            size_t index = distance(begin(source2), i);
                            return result.at(index);
                        }
                    }
                }

                return def;
            }

            template <typename Type> static T Compare(const Type& source1, const std::vector<Type>& source2, const std::vector<T>& result, const T& def)
            {
                using namespace std;

                static_assert(Constexpr::is_not_string_wstring<Type>, "This template requires not string.");

                if (size(source2) == size(result))
                {
                    for (auto i = begin(source2); i != end(source2); i++)
                    {
                        if (source1 == *i)
                        {
                            size_t index = distance(begin(source2), i);
                            return result.at(index);
                        }
                    }
                }

                return def;
            }
            //
            // Разбиение строки
            //
            static std::vector<T> Split(const T& source, const typename T::value_type delimiter)
            {
                using namespace std;

                basic_stringstream<typename T::value_type, std::char_traits<typename T::value_type>, std::allocator<typename T::value_type>> stream(source);

                T item;

                vector<T> split;

                while (getline(stream, item, delimiter))
                {
                    split.push_back(item);
                }

                return split;
            }
            //
            // Сборка строки
            //
            static T UnSplit(const std::vector<T>& source, const typename T::value_type delimiter = 0)
            {
                using namespace std;

                T result;

                for_each(begin(source), end(source), [&](const T& str) { result += str; if (delimiter != 0) result += delimiter; });

                if (delimiter != 0) result.pop_back();

                return result;
            }

            static T UnSplit(const std::vector<T>& source, const T& delimiter)
            {
                using namespace std;

                T result;

                for_each(begin(source), end(source), [&](const T& str) { result += str; if (size(delimiter) > 0) result += delimiter; });

                if (size(delimiter) > 0)
                {
                    result.erase(size(result) - size(delimiter), size(delimiter));
                }

                return result;
            }

            static void VoidUnSplit(T& dest, const std::vector<T>& source, const typename T::value_type delimiter = 0)
            {
                dest = UnSplit(source, delimiter);
            }

            template<typename Type> static T TUnSplit(const std::vector<Type> source, const typename T::value_type delimiter, const std::locale& loc = std::locale(), const int precision = -1, const bool fixed = false)
            {
                using namespace std;

                static_assert(Constexpr::is_not_string_wstring<Type>, "This template requires not string.");
            
                T result;

                for_each(begin(source), end(source), [&](const Type& value)
                {
                    T str_value = String::TConverter<T>::ToString(value, loc, precision, fixed);

                    result += str_value;

                    if (delimiter != 0) result += delimiter;
                });

                if (delimiter != 0) result.pop_back();

                return result;
            }

            template<typename Type> static T TUnSplit(const std::vector<Type> source, const T& delimiter, const std::locale& loc = std::locale(), const int precision = -1, const bool fixed = false)
            {
                using namespace std;

                static_assert(Constexpr::is_not_string_wstring<Type>, "This template requires not string.");

                T result;

                for_each(begin(source), end(source), [&](const Type& value)
                {
                    T str_value = String::TConverter<T>::ToString(value, loc, precision, fixed);

                    result += str_value;

                    if (size(delimiter) > 0) result += delimiter;
                });

                if (size(delimiter) > 0)
                {
                    result.erase(size(result) - size(delimiter), size(delimiter));
                }

                return result;
            }

            //
            // Удаление пробельных символов с начала и конца строки
            //
            static T Trim(const T& source)
            {
                T whitespace;

                if constexpr(Constexpr::is_string<T>)
                {
                    whitespace = " \t\r\n";
                }
                else
                {
                    whitespace = L" \t\r\n";
                }

                const size_t first(source.find_first_not_of(whitespace));

                if (first != T::npos)
                {
                    const size_t last(source.find_last_not_of(whitespace));
                    return source.substr(first, (last - first + 1));
                }

                return TConverter<T>::EmptyString();
            }

            static void VoidTrim(T& source, const T& value)
            {
                if ((source.length() > 0) && (value.length() == 1))
                {
                    while (!source.empty() && (source.front() == value.front()))
                    {
                        source.erase(0, 1);
                    }
                    while (!source.empty() && (source.back() == value.front()))
                    {
                        source.erase(source.length() - 1, 1);
                    }
                }
            }

            static void VoidTrim(T& source)
            {
                source = Trim(source);
            }

            //
            // Строка является IP адресом
            //
            static bool IsIP(const T& ip, const std::locale& loc = std::locale())
            {
                T exp;

                if constexpr(Constexpr::is_string<T>)
                {
                    exp = "^(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$";
                }
                else
                {
                    exp = L"^(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$";
                }

                std::basic_regex<typename T::value_type> pattern(exp);

                return std::regex_match(ip, pattern);
            }

            //
            // Преобразование Ip адреса в маску 4 байта
            //
            static uint32_t IpToMask32(const T& ip, const std::locale& loc = std::locale())
            {
                using namespace std;

                typename T::value_type del;

                if constexpr(Constexpr::is_string<T>)
                {
                    del = '.';
                }
                else
                {
                    del = L'.';
                }

                if (IsIP(ip))
                {
                    auto temp = Split(ip, del);

                    uint32_t result(0);

                    for (auto i = begin(temp); i != end(temp); i++)
                    {
                        result |= String::TConverter<T>::FromString(*i, uint32_t(0), loc);

                        if (i != prev(end(temp)))
                        {
                            result = result << 8;
                        }
                    }

                    return result;
                }

                return 0;
            }
        };

        using TStringExtension = TExtension<std::string>;
        using TWStringExtension = TExtension<std::wstring>;
        // ---------------------------------------------------------------------------
        //
        // Класс обеспечивает работу с кодировками
        //
        template<typename T> class TEncoding
        {
        private:
            static_assert(Constexpr::is_string_wstring<T>, "This template requires the type std::string or std::wstring.");

            typedef struct { uint8_t cp1251; uint32_t unicode; } Cp1251;

            inline static const Cp1251 utf8_to_cp1251_table[] = {
                /* {0x98, 0x0098}, */
                {0xA0, 0x00A0}, /* NO-BREAK SPACE */
                {0xA4, 0x00A4}, /* CURRENCY SIGN */
                {0xA6, 0x00A6}, /* BROKEN BAR */
                {0xA7, 0x00A7}, /* SECTION SIGN */
                {0xA9, 0x00A9}, /* COPYRIGHT SIGN */
                {0xAB, 0x00AB}, /* LEFT-POINTING DOUBLE ANGLE QUOTATION MARK */
                {0xAC, 0x00AC}, /* NOT SIGN */
                {0xAD, 0x00AD}, /* SOFT HYPHEN */
                {0xAE, 0x00AE}, /* REGISTERED SIGN */
                {0xB0, 0x00B0}, /* DEGREE SIGN */
                {0xB1, 0x00B1}, /* PLUS-MINUS SIGN */
                {0xB5, 0x00B5}, /* MICRO SIGN */
                {0xB6, 0x00B6}, /* PILCROW SIGN */
                {0xB7, 0x00B7}, /* MIDDLE DOT */
                {0xBB, 0x00BB}, /* RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK */
                {0xA8, 0x0401}, /* CYRILLIC CAPITAL LETTER IO */
                {0x80, 0x0402}, /* CYRILLIC CAPITAL LETTER DJE */
                {0x81, 0x0403}, /* CYRILLIC CAPITAL LETTER GJE */
                {0xAA, 0x0404}, /* CYRILLIC CAPITAL LETTER UKRAINIAN IE */
                {0xBD, 0x0405}, /* CYRILLIC CAPITAL LETTER DZE */
                {0xB2, 0x0406}, /* CYRILLIC CAPITAL LETTER BYELORUSSIAN-UKRAINIAN I */
                {0xAF, 0x0407}, /* CYRILLIC CAPITAL LETTER YI */
                {0xA3, 0x0408}, /* CYRILLIC CAPITAL LETTER JE */
                {0x8A, 0x0409}, /* CYRILLIC CAPITAL LETTER LJE */
                {0x8C, 0x040A}, /* CYRILLIC CAPITAL LETTER NJE */
                {0x8E, 0x040B}, /* CYRILLIC CAPITAL LETTER TSHE */
                {0x8D, 0x040C}, /* CYRILLIC CAPITAL LETTER KJE */
                {0xA1, 0x040E}, /* CYRILLIC CAPITAL LETTER SHORT U */
                {0x8F, 0x040F}, /* CYRILLIC CAPITAL LETTER DZHE */
                {0xB8, 0x0451}, /* CYRILLIC SMALL LETTER IO */
                {0x90, 0x0452}, /* CYRILLIC SMALL LETTER DJE */
                {0x83, 0x0453}, /* CYRILLIC SMALL LETTER GJE */
                {0xBA, 0x0454}, /* CYRILLIC SMALL LETTER UKRAINIAN IE */
                {0xBE, 0x0455}, /* CYRILLIC SMALL LETTER DZE */
                {0xB3, 0x0456}, /* CYRILLIC SMALL LETTER BYELORUSSIAN-UKRAINIAN I */
                {0xBF, 0x0457}, /* CYRILLIC SMALL LETTER YI */
                {0xBC, 0x0458}, /* CYRILLIC SMALL LETTER JE */
                {0x9A, 0x0459}, /* CYRILLIC SMALL LETTER LJE */
                {0x9C, 0x045A}, /* CYRILLIC SMALL LETTER NJE */
                {0x9E, 0x045B}, /* CYRILLIC SMALL LETTER TSHE */
                {0x9D, 0x045C}, /* CYRILLIC SMALL LETTER KJE */
                {0xA2, 0x045E}, /* CYRILLIC SMALL LETTER SHORT U */
                {0x9F, 0x045F}, /* CYRILLIC SMALL LETTER DZHE */
                {0xA5, 0x0490}, /* CYRILLIC CAPITAL LETTER GHE WITH UPTURN */
                {0xB4, 0x0491}, /* CYRILLIC SMALL LETTER GHE WITH UPTURN */
                {0x96, 0x2013}, /* EN DASH */
                {0x97, 0x2014}, /* EM DASH */
                {0x91, 0x2018}, /* LEFT SINGLE QUOTATION MARK */
                {0x92, 0x2019}, /* RIGHT SINGLE QUOTATION MARK */
                {0x82, 0x201A}, /* SINGLE LOW-9 QUOTATION MARK */
                {0x93, 0x201C}, /* LEFT DOUBLE QUOTATION MARK */
                {0x94, 0x201D}, /* RIGHT DOUBLE QUOTATION MARK */
                {0x84, 0x201E}, /* DOUBLE LOW-9 QUOTATION MARK */
                {0x86, 0x2020}, /* DAGGER */
                {0x87, 0x2021}, /* DOUBLE DAGGER */
                {0x95, 0x2022}, /* BULLET */
                {0x85, 0x2026}, /* HORIZONTAL ELLIPSIS */
                {0x89, 0x2030}, /* PER MILLE SIGN */
                {0x8B, 0x2039}, /* SINGLE LEFT-POINTING ANGLE QUOTATION MARK */
                {0x9B, 0x203A}, /* SINGLE RIGHT-POINTING ANGLE QUOTATION MARK */
                {0x88, 0x20AC}, /* EURO SIGN */
                {0xB9, 0x2116}, /* NUMERO SIGN */
                {0x99, 0x2122}  /* TRADE MARK SIGN */
            };

            inline static const int cp1251_to_utf8_table[128] = {
                0x82D0, 0x83D0, 0x9A80E2, 0x93D1,
                0x9E80E2, 0xA680E2, 0xA080E2, 0xA180E2, 0xAC82E2, 0xB080E2,
                0x89D0, 0xB980E2, 0x8AD0, 0x8CD0, 0x8BD0, 0x8FD0, 0x92D1,
                0x9880E2, 0x9980E2, 0x9C80E2, 0x9D80E2, 0xA280E2, 0x9380E2,
                0x9480E2, 0, 0xA284E2, 0x99D1, 0xBA80E2, 0x9AD1, 0x9CD1,
                0x9BD1, 0x9FD1, 0xA0C2, 0x8ED0, 0x9ED1, 0x88D0, 0xA4C2,
                0x90D2, 0xA6C2, 0xA7C2, 0x81D0, 0xA9C2, 0x84D0, 0xABC2,
                0xACC2, 0xADC2, 0xAEC2, 0x87D0, 0xB0C2, 0xB1C2, 0x86D0,
                0x96D1, 0x91D2, 0xB5C2, 0xB6C2, 0xB7C2, 0x91D1, 0x9684E2,
                0x94D1, 0xBBC2, 0x98D1, 0x85D0, 0x95D1, 0x97D1, 0x90D0,
                0x91D0, 0x92D0, 0x93D0, 0x94D0, 0x95D0, 0x96D0, 0x97D0,
                0x98D0, 0x99D0, 0x9AD0, 0x9BD0, 0x9CD0, 0x9DD0, 0x9ED0,
                0x9FD0, 0xA0D0, 0xA1D0, 0xA2D0, 0xA3D0, 0xA4D0, 0xA5D0,
                0xA6D0, 0xA7D0, 0xA8D0, 0xA9D0, 0xAAD0, 0xABD0, 0xACD0,
                0xADD0, 0xAED0, 0xAFD0, 0xB0D0, 0xB1D0, 0xB2D0, 0xB3D0,
                0xB4D0, 0xB5D0, 0xB6D0, 0xB7D0, 0xB8D0, 0xB9D0, 0xBAD0,
                0xBBD0, 0xBCD0, 0xBDD0, 0xBED0, 0xBFD0, 0x80D1, 0x81D1,
                0x82D1, 0x83D1, 0x84D1, 0x85D1, 0x86D1, 0x87D1, 0x88D1,
                0x89D1, 0x8AD1, 0x8BD1, 0x8CD1, 0x8DD1, 0x8ED1, 0x8FD1
            };

            //
            // Метод конвертирует строку с кодировкой utf8 в строку с кодировкой cp1251
            // Размер буфера cp1251 должен быть равен size(utf8) + 1
            // Функция возвращает размер новой строки или -1 в случае ошибки
            //
            static int utf8_to_cp1251(const char* utf8, char* cp1251)
            {
                const size_t MAX_NUMBER_OF_UTF8_OCTETS(6);

                const Cp1251* customCp1251Table = 0;
                size_t customCp1251TableSize = 0;

                const uint8_t b0000_0000(0);
                const uint8_t b1000_0000(128);
                const uint8_t b1100_0000(192);
                const uint8_t b1110_0000(224);
                const uint8_t b1111_0000(240);
                const uint8_t b1111_1000(248);
                const uint8_t b1111_1100(252);
                const uint8_t b1111_1110(254);

                const uint8_t firstOctetMask[MAX_NUMBER_OF_UTF8_OCTETS] = { b1000_0000, b1110_0000, b1111_0000, b1111_1000, b1111_1100, b1111_1110 };
                const uint8_t firstOctetTemplate[MAX_NUMBER_OF_UTF8_OCTETS] = { b0000_0000, b1100_0000, b1110_0000, b1111_0000, b1111_1000, b1111_1100 };

                const uint8_t secondOctetMask(b1100_0000);
                const uint8_t secondOctetTemplate(b1000_0000);

                size_t numberOfRemainingOctets(0);
                uint32_t unicode(0);
                size_t i(0);
                size_t cp1251_i(0);

                while (utf8[i] != '\0')
                {
                    const uint8_t octet(utf8[i++]);

                    if (numberOfRemainingOctets == 0)
                    {
                        bool error(true);

                        for (size_t j = 0; j < MAX_NUMBER_OF_UTF8_OCTETS; j++)
                        {
                            const uint8_t octetMask(firstOctetMask[j]);
                            const uint8_t octetTemplate(firstOctetTemplate[j]);

                            if ((octet & octetMask) == octetTemplate) {
                                unicode = octet & ~octetMask;

                                if (j == 0)
                                {
                                    //
                                    // Обнаружен символ US-ASCII
                                    //
                                    cp1251[cp1251_i++] = unicode;
                                }

                                numberOfRemainingOctets = j;
                                error = false;
                                break;
                            }
                        }

                        if (error) return -1; // Ошибка UTF-8
                    }
                    else
                    {
                        if ((octet & secondOctetMask) == secondOctetTemplate)
                        {
                            unicode <<= 6;
                            unicode |= octet & ~secondOctetMask;
                            numberOfRemainingOctets--;

                            if (numberOfRemainingOctets == 0)
                            {
                                if (0x410 <= unicode && unicode <= 0x44F)
                                {
                                    cp1251[cp1251_i++] = 0xC0 + unicode - 0x410;
                                }
                                else
                                {
                                    const Cp1251* tables[] = { customCp1251Table, utf8_to_cp1251_table };
                                    const size_t tableSizes[] = { customCp1251TableSize, sizeof(utf8_to_cp1251_table) / sizeof(Cp1251) };

                                    size_t t;

                                    for (t = 0; t < 2; t++)
                                    {
                                        const Cp1251 key = { 0, unicode };

                                        const Cp1251* conversion = (const Cp1251*)bsearch(&key, tables[t], tableSizes[t], sizeof(Cp1251), [](const void* s1, const void* s2) -> int
                                            {
                                                return ((Cp1251*)s1)->unicode - ((Cp1251*)s2)->unicode;
                                            }
                                        );

                                        if (conversion)
                                        {
                                            cp1251[cp1251_i++] = conversion->cp1251;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        else
                        {
                            return -1; // Ошибка UTF-8
                        }
                    }
                }

                cp1251[cp1251_i] = '\0';

                return  static_cast<int>(cp1251_i);
            }

            //
            // Проверка, что строка в кодировке utf8
            //
            static bool is_utf8(const char* string)
            {
                if (!string) return true;

                const unsigned char* bytes = (const unsigned char*)string;
                int num;

                while (*bytes != 0x00)
                {
                    if ((*bytes & 0x80) == 0x00)
                    {
                        // U+0000 to U+007F 
                        num = 1;
                    }
                    else if ((*bytes & 0xE0) == 0xC0)
                    {
                        // U+0080 to U+07FF 
                        num = 2;
                    }
                    else if ((*bytes & 0xF0) == 0xE0)
                    {
                        // U+0800 to U+FFFF 
                        num = 3;
                    }
                    else if ((*bytes & 0xF8) == 0xF0)
                    {
                        // U+10000 to U+10FFFF 
                        num = 4;
                    }
                    else
                    {
                        return false;
                    }

                    bytes += 1;
                    for (int i = 1; i < num; ++i)
                    {
                        if ((*bytes & 0xC0) != 0x80)
                            return false;
                        bytes += 1;
                    }
                }

                return true;
            }

            //
            // Расчёт размера для строки с кодировкой utf8
            //
            static size_t cp1251_to_utf8_size(const char* cp1251)
            {
                size_t size(0);

                for (; *cp1251; cp1251++)
                {
                    if (*cp1251 & 0x80)
                    {
                        if (int v = cp1251_to_utf8_table[(int)(0x7f & *cp1251)]; v)
                        {
                            size += sizeof(wchar_t);

                            if (v >>= 16)
                            {
                                size += sizeof(char);
                            }
                        }
                    }
                    else
                    {
                        size += sizeof(char);
                    }
                }

                return size > 0 ? size + 1 : size;
            }

            //
            // Метод конвертирует строку с кодировкой cp1251 в строку с кодировкой utf8
            // Размер буфера utf8 должен быть равен size(utf8) * sizeof(wchar_t) + 1
            //
            static void cp1251_to_utf8(const char* cp1251, char* utf8, std::size_t utf8_size)
            {
                while (*cp1251)
                {
                    if (*cp1251 & 0x80)
                    {
                        if (int v = cp1251_to_utf8_table[(int)(0x7f & *cp1251++)]; v)
                        {
                            if (utf8_size < 2) break;

                            *utf8++     = (char)v;
                            *utf8++     = (char)(v >> 8);

                            utf8_size   -= 2;

                            if (v >>= 16)
                            {
                                if (utf8_size == 0) break;

                                *utf8++ = (char)v;

                                utf8_size--;
                            }
                        }
                    }
                    else
                    {
                        if (utf8_size == 0) break;

                        *utf8++ = *cp1251++;

                        utf8_size--;
                    }
                }

                if (utf8_size > 0)
                {
                    *utf8 = 0;
                }
            }

        public:
            //
            // Конвертирование строки с кодировкой utf8 в строку с кодировкой cp1251
            //
            static T Utf8ToCp1251(const T& value, const std::locale& loc = std::locale())
            {
                using namespace std;

                string utf8 = TConverter<string>::ToString(value, loc);

                string ascii(size(utf8) + 1, '\0');

                if (utf8_to_cp1251(utf8.c_str(), data(ascii)) > 0)
                {
                    T result = TConverter<T>::ToString(ascii, loc);

                    result.erase(find(begin(result), end(result), 0), end(result));

                    return result;
                }

                return TConverter<T>::EmptyString();
            }

            //
            // Конвертирование строки с кодировкой cp1251 в строку с кодировкой utf8
            //
            static T Cp1251ToUtf8(const T& value, const std::locale& loc = std::locale())
            {
                using namespace std;

                string ascii = TConverter<string>::ToString(value, loc);

                string utf8(cp1251_to_utf8_size(ascii.c_str()), 0);

                cp1251_to_utf8(ascii.c_str(), data(utf8), size(utf8));

                utf8.erase(find(begin(utf8), end(utf8), 0), end(utf8));

                return TConverter<T>::ToString(utf8, loc);
            }

            //
            // Строка с кодировкой utf8
            //
            static bool IsUtf8(const T& value, const std::locale& loc = std::locale())
            {
                using namespace std;

                string ascii = TConverter<string>::ToString(value, loc);

                return is_utf8(ascii.c_str());
            }
            
            //
            // Автоматическое конвертирование строки в зависимости от операционной системы
            //
            static T Auto(const T& value, const std::locale& loc = std::locale())
            {
                bool is_utf = IsUtf8(value, loc);
#ifdef WINDOWS
                return is_utf ? Utf8ToCp1251(value, loc) : value;
#else
                return is_utf ? value : Cp1251ToUtf8(value, loc);
#endif
            }
        
            //
            // Конвертирование строки в UTF8
            //
            static T ToUtf8(const T& value, const std::locale& loc = std::locale())
            {
                return IsUtf8(value, loc) ? value : Cp1251ToUtf8(value, loc);
            }

            //
            // Конвертирование строки в cp1251
            //
            static T ToCp1251(const T& value, const std::locale& loc = std::locale())
            {
                return IsUtf8(value, loc) ? Utf8ToCp1251(value, loc) : value;
            }
        };

        using TStringEncoding = TEncoding<std::string>;
        using TWStringEncoding = TEncoding<std::wstring>;
    }
    //
    // Расширение функционала стандартной библиотеки
    //
    namespace StdExtension
    {
        //
        // Шаблон умного указателя
        //
        template <typename T> using deleted_unique_ptr = std::unique_ptr<T, std::function<void(T*)>>;
        //
        // Доступ к данным строки
        //
        template<typename Type> const typename Type::value_type* C_STR(const Type& value)
        {
            static_assert(Constexpr::is_string_wstring<Type>, "This template requires the type std::string or std::wstring.");
            return value.c_str();
        }
        //
        // Первый элемент контейнера
        //
        template <typename Type> typename Type::value_type& FRONT(Type& container)
        {
            return container.front();
        }
        //
        // Последний элемент контейнера
        //
        template <typename Type> typename Type::value_type& BACK(Type& container)
        {
            return container.back();
        }
        //
        // Цикл по элементам контейнера с индексом
        //
        template<typename TIterator, typename TFunc> void FOR_EACH(TIterator first, TIterator last, TFunc func)
        {
            for (TIterator _first(first); _first != last; _first++)
            {
                func(std::distance(first, _first), *_first);
            }
        }
        //
        // Удаление дубликатов из вектора
        //
        template<typename Type> void UniqueVector(std::vector<Type>& vec, std::function<bool(const Type& value1, const Type& value2)> f_sort = nullptr, std::function<bool(const Type& value1, const Type& value2)> f_unique = nullptr)
        {
            using namespace std;

            if (f_sort == nullptr) sort(begin(vec), end(vec));
            else sort(begin(vec), end(vec), f_sort);

            if (f_unique == nullptr) vec.erase(unique(begin(vec), end(vec)), end(vec));
            else vec.erase(unique(begin(vec), end(vec), f_unique), end(vec));
        }
        //
        // Сравнение двух чисел с плавающей запятой
        //
        template<typename Type> bool AreSame(Type a, Type b)
        {
            static_assert(Constexpr::is_float<Type>, "This template requires the type float or double.");
            Type value(std::fabs(a - b));
            return value < std::numeric_limits<Type>::epsilon();
        }
        //
        // Вывод аргументов командной строки
        //
        template<typename Type = std::string> bool LinuxCmdArgs(std::vector<Type>& cmd_argc)
        {
            static_assert(Constexpr::is_string_wstring<Type>, "This template requires the type std::string or std::wstring.");

            cmd_argc.clear();
#if defined(WINDOWS)
#elif defined(LINUX)
            if (std::ifstream cmd_ifs("/proc/self/cmdline", std::ifstream::in); cmd_ifs.is_open())
            {
                for (std::string arg; std::getline(cmd_ifs, arg, '\0');)
                {
                    auto value = String::TConverter<Type>::ToString(arg);

                    cmd_argc.push_back(value);
                }
                cmd_ifs.close();
            }
#endif

            return !cmd_argc.empty();
        }
        //
        // Локальное время или глобальное время
        //
        template<typename Type = uint8_t> void GetTime(const std::chrono::time_point<std::chrono::system_clock>& now_time, std::tm& time, uint16_t& milliseconds, bool add_year1900_month1, bool UTC = false)
        {
            auto seconds       = std::chrono::time_point_cast<std::chrono::seconds>(now_time);
            auto fraction      = now_time - seconds;
            auto _milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(fraction);

            time_t t_now = std::chrono::system_clock::to_time_t(now_time);

            if (UTC)
            {
                gmtime_r(&t_now, &time);
            }
            else
            {
                localtime_r(&t_now, &time);
            }

            if (add_year1900_month1)
            {
                time.tm_year += 1900;
                time.tm_mon  += 1;
            }

            milliseconds = static_cast<uint16_t>(_milliseconds.count());
        }
        //
        // Локальное время или глобальное время
        //
        template<typename Type = uint8_t> void GetTime(std::tm& time, uint16_t& milliseconds, bool add_year1900_month1, bool UTC = false)
        {
            GetTime(std::chrono::system_clock::now(), time, milliseconds, add_year1900_month1, UTC);
        }
        //
        // Выравнивание строк в таблице
        //
        enum class TTableAlign { None, Left, Right, Center };
        template<typename Type> bool TableAlign(Type& table, TTableAlign align)
        {
            using namespace std;

            static_assert(
                is_same<Type, std::vector<std::vector<std::string>>>::value ||
                is_same<Type, std::vector<std::vector<std::wstring>>>::value
                , "This template requires the type std::vector<std::string|std::wstring>."
            );

            if (align != TTableAlign::None)
            {
                if (size_t row_len(size(table) > 0 ? size(table.at(0)) : 0); row_len > 0)
                {
                    typename Type::value_type::value_type::value_type blank;
                    //
                    // Инициализация символа-пробела
                    //
                    if constexpr(Constexpr::is_string<typename Type::value_type::value_type>)
                    {
                        blank = ' '; 
                    }
                    else
                    {
                        blank = L' ';
                    }
                    //
                    // Массив для хранения максимальной длинны строки для каждого столбца
                    //
                    vector<std::size_t> max_size(row_len, 0);
                    //
                    // Определение максимальной длинны строки в таблице
                    //
                    for (size_t i(0), k(0); k < size(max_size); )
                    {
                        if (size(table.at(i)) == row_len)
                        {
                            VOID_AUTO_ENCODING(typename Type::value_type::value_type, table.at(i).at(k));

                            size_t length(size(table.at(i).at(k)));

                            if (length > max_size.at(k))
                            {
                                max_size.at(k) = length;
                            }
                            if (i++; i >= size(table))
                            {
                                i = 0; k++;
                            }
                        }
                        else
                        {
                            return false; // НЕТ ВЫВОДА, НАРУШЕНА СТРУКТУРА ТАБЛИЦЫ
                        }
                    }
                    //
                    // Выравнивание
                    //
                    for (size_t i(0), k(0); k < size(max_size); )
                    {
                        size_t add_blanks = max_size.at(k) - size(table.at(i).at(k));

                        if (align == TTableAlign::Left)
                        {
                            table.at(i).at(k).insert(end(table.at(i).at(k)), add_blanks, blank);
                        }
                        else if (align == TTableAlign::Right)
                        {
                            table.at(i).at(k).insert(begin(table.at(i).at(k)), add_blanks, blank);
                        }
                        else // Center
                        {
                            size_t left(0), right(0);

                            if (add_blanks % 2 == 0)
                            {
                                left = add_blanks / 2;
                                right = left;
                            }
                            else
                            {
                                left = add_blanks / 2;
                                right = add_blanks - left;
                            }

                            table.at(i).at(k).insert(begin(table.at(i).at(k)), left, blank);
                            table.at(i).at(k).insert(end(table.at(i).at(k)), right, blank);
                        }

                        if (i++; i >= size(table))
                        {
                            i = 0; k++;
                        }
                    }
                }
                else return false;
            }

            return true;
        }
        //
        // Вывод сообщения в консоль
        //
        template<typename Arg = std::size_t> void ConsoleOut(bool end_line, std::vector<std::string>& concat_string)
        {
            for (const auto& value : concat_string)
            {
                std::cout << value;
            }

            if (end_line)
            {
                std::cout << std::endl;
            }
        }

        template<typename Arg> void ConsoleOut(bool end_line, std::vector<std::string>& concat_string, Arg arg)
        {
            std::string value = String::TConverter<std::string>::ToString(arg);
            T_VOID_AUTO_ENCODING(value);
            concat_string.push_back(value);
            ConsoleOut(end_line, concat_string);
        }

        template<typename Arg, typename... Args> void ConsoleOut(bool end_line, std::vector<std::string>& concat_string, Arg arg, Args... args)
        {
            std::string value = String::TConverter<std::string>::ToString(arg);
            T_VOID_AUTO_ENCODING(value);
            concat_string.push_back(value);
            ConsoleOut(end_line, concat_string, args...);
        }

        template<typename Arg, typename... Args> void ConsoleOut(bool end_line, Arg arg, Args... args)
        {
            std::vector<std::string> concat_string;
            ConsoleOut(end_line, concat_string, arg, args...);
        }

        template<typename Type> void ConsoleOut(const Type& value, bool end_line = true)
        {
            if constexpr((std::is_same<std::vector<std::string>, Type>::value) || (std::is_same<std::vector<std::wstring>, Type>::value)) // vector<string> || vector<wstring>
            {
                for (const auto& str : value)
                {
                    std::string _value = String::TConverter<decltype(_value)>::ToString(str);

                    T_VOID_AUTO_ENCODING(_value);

                    std::cout << _value;

                    if (end_line)
                    {
                        std::cout << std::endl;
                    }
                }
            }
            else if constexpr(std::is_same<std::vector<std::pair<std::wstring, std::wstring>>, Type>::value)
            {
                auto cout_list(value);
                //
                // Поиск максимальной длинной строки
                //
                std::size_t max_str_len(0);
                for(auto& _value : cout_list)
                {
                    //
                    // Преобразование в требуемую кодировку
                    //
                    T_VOID_AUTO_ENCODING(_value.first);
                    T_VOID_AUTO_ENCODING(_value.second);
                    //
                    // Поиск максимальной длинной строки
                    //
                    if (max_str_len < std::size(_value.first))
                    {
                        max_str_len = std::size(_value.first);
                    }
                }

                max_str_len++;
                //
                // Вывод данных
                //
                for(auto& _value : cout_list)
                {
                    std::wstring temp(_value.first);
                    temp.insert(std::end(temp), max_str_len - std::size(temp), L' ');
                    temp += _value.second;

                    std::string s_temp = String::TConverter<decltype(s_temp)>::ToString(temp);

                    std::cout << s_temp;

                    if (end_line)
                    {
                        std::cout << std::endl;
                    }

                }
            }
            else if constexpr(std::is_same<std::vector<std::vector<std::wstring>>, Type>::value)
            {
                auto table = value;
                //
                // Формирование отступов
                //
                for (auto& column : table)
                {
                    std::size_t max_size(0);

                    for (size_t i(0); i < size(column); i++)
                    {
                        std::wstring row = column[i];
                        T_VOID_AUTO_ENCODING(row);
                        column[i] = row;

                        if (max_size < std::size(row))
                        {
                            max_size = std::size(row);
                        }
                    }

                    max_size += 10;

                    for (auto& row : column)
                    {
                        std::size_t row_size = (max_size - std::size(row)) / 2;
                        row.insert(std::begin(row), row_size, L' ');
                        row.insert(std::end(row), row_size, L' ');
                    }
                }
                //
                // Выравнивание
                //
                for (auto& column : table)
                {
                    std::size_t max_size(0);

                    for (auto& row : column)
                    {
                        if (max_size < std::size(row))
                        {
                            max_size = std::size(row);
                        }
                    }

                    for (auto& row : column)
                    {
                        row.insert(std::end(row), max_size - std::size(row), L' ');
                    }
                }
                //
                // Вывод
                //
                for (std::size_t r(0); r < std::size(table.front()); r++)
                {
                    std::string row;
                    std::string line;

                    for (std::size_t c(0); c < std::size(table); c++)
                    {
                        if (r == 0)
                        {
                            line.insert(std::end(line), std::size(table[c][r]), '-');
                        }
                        row += String::TConverter<decltype(row)>::ToString(table[c][r]);
                    }

                    std::cout << row << std::endl;

                    if (r == 0)
                    {
                        std::cout << line << std::endl;
                    }
                }
            }
            else
            {
                std::string _value = String::TConverter<decltype(_value)>::ToString(value);

                T_VOID_AUTO_ENCODING(_value);

                std::cout << _value;

                if (end_line)
                {
                    std::cout << std::endl;
                }
            }
        }
        //
        // Класс описывает пару строк (с разбиением входной строки по разделителю)
        //
        template <typename T> class TSamePair : public std::pair<T, T>
        {
        private:
            static_assert(Constexpr::is_string_wstring<T>, "This template requires the type std::string or std::wstring.");

            std::basic_regex<typename T::value_type> reg_value; // Правило для проверки пары
            std::basic_regex<typename T::value_type> reg_empty_value; // Правило для проверки пары с пустым значением

            typename T::value_type _delimiter; // Разделитель пары
            bool is_matched; // Пара разобрана
            
            //
            // Формирование разделителя под регулярное выражение
            //
            T GetDelimiter(typename T::value_type delimiter)
            {
                using namespace std;

                T result;
                vector<typename T::value_type> check;

                if constexpr(Constexpr::is_string<T>)
                {
                    result = "\\";
                    check = { '[', ']', '\\', '/', '^', '$', '.', '|', '?', '*', '+', '(', ')', '{', '}' };
                }
                else
                {
                    result = L"\\";
                    check = { L'[', L']', L'\\', L'/', L'^', L'$', L'.', L'|', L'?', L'*', L'+', L'(', L')', L'{', L'}' };
                }

                auto _find = find(begin(check), end(check), delimiter);

                if (_find != end(check))
                {
                    result += delimiter;
                }
                else
                {
                    result = delimiter;
                }

                return result;
            }

        public:
            //
            // Конструктор 1
            //
            TSamePair(typename T::value_type delimiter) : _delimiter(delimiter), is_matched(false)
            {
                T rule;
                T empty_rule;

                if constexpr(Constexpr::is_string<T>)
                {
                    rule = "^.+" + GetDelimiter(_delimiter);
                    empty_rule = rule;

                    rule += ".+$";
                    empty_rule += "$";
                }
                else
                {
                    rule = L"^.+" + GetDelimiter(_delimiter);
                    empty_rule = rule;

                    rule += L".+$";
                    empty_rule += L"$";
                }

                reg_value.assign(rule);
                reg_empty_value.assign(empty_rule);
            }
            //
            // Конструктор 2
            //
            TSamePair(typename T::value_type delimiter, const T& value) : TSamePair(delimiter)
            {
                Set(value);
            }
            //
            // Формирование пары
            //
            bool Set(const T& value)
            {
                is_matched = false;

                if (regex_match(value, reg_value) || regex_match(value, reg_empty_value))
                {
                    size_t delimiter = value.find(_delimiter);

                    this->first = value.substr(0, delimiter);
                    String::TExtension<T>::VoidTrim(this->first);

                    this->second = value.substr(delimiter + 1);
                    String::TExtension<T>::VoidTrim(this->second);

                    is_matched = true;
                }

                return is_matched;
            }
            //
            // Пара разобрана
            //
            bool IsMatched()
            {
                return is_matched;
            }
        };

        namespace Events
        {
            template<typename T> class TEventAccessor; // Доступ к защищённым члена класса TEvent
            //
            // Шаблон описывает потокобезопасное событие
            //
            template<typename T> class TEvent
            {
            public:
                using TEventProc =      std::function<void(T&)>;
                using TEventHandle =    std::shared_ptr<TEventProc>;
                friend class TEventAccessor<T>;

            private:
                mutable std::mutex lock;
                std::set<TEventHandle> event_list;

            protected:
                //
                // Вызов обработчиков события
                //
                void Invoke(T& _arg)
                {
                    std::lock_guard<decltype(lock)> locker(lock);

                    for (auto& handle : event_list)
                    {
                        (*handle)(_arg);
                    }
                }

            public:
                //
                // Конструктор
                //
                TEvent() {}

                //
                // Деструктор
                //
                ~TEvent() {}

                //
                // Установка одного обработчика события
                //
                TEventHandle Set(const TEventProc& event_proc)
                {
                    if (event_proc != nullptr)
                    {
                        std::lock_guard<decltype(lock)> locker(lock);

                        event_list.clear();

                        TEventHandle handle(new TEventProc(event_proc));

                        event_list.insert(handle);

                        return handle;
                    }

                    return nullptr;
                }

                TEventHandle operator=(const TEventProc& event_proc)
                {
                    return Set(event_proc);
                }

                //
                // Добавить обработчик события
                //
                TEventHandle Add(const TEventProc& event_proc)
                {
                    if (event_proc != nullptr)
                    {
                        std::lock_guard<decltype(lock)> locker(lock);

                        TEventHandle handle(new TEventProc(event_proc));

                        event_list.insert(handle);

                        return handle;
                    }

                    return nullptr;
                }

                TEventHandle operator+=(const TEventProc& event_proc)
                {
                    return Add(event_proc);
                }

                //
                // Удаление обработчика события
                //
                void Remove(TEventHandle handle)
                {
                    std::lock_guard<decltype(lock)> locker(lock);

                    auto _handle = event_list.find(handle);

                    if (_handle != end(event_list))
                    {
                        event_list.erase(_handle);
                    }
                }

                void operator-=(TEventHandle handle)
                {
                    Remove(handle);
                }
            };

            //
            // Доступ к защищённым члена класса TEvent
            //
            template<typename T> class TEventAccessor
            {
            private:
                TEvent<T>& event;

            public:
                //
                // Конструктор
                //
                TEventAccessor(TEvent<T>& _event) : event(_event) {}
                //
                // Вызов обработчиков события
                //
                void Invoke(T& _arg)
                {
                    event.Invoke(_arg);
                }
            };
        }

        namespace Threading
        {
            //
            // Максимальное количество одновременно выполняемых потоков 
            //
            template<typename Type = uint32_t> unsigned int GetHardwareConcurrency()
            {
                unsigned int max_threads = std::thread::hardware_concurrency();
                return max_threads == 0 ? 1 : max_threads;
            }
            
            //
            // Безопасное удаление мьютекса
            //
            template<typename Type> void DeletePtrMutex(Type* mtx)
            {
                static_assert(Constexpr::is_any_mutex<Type>, "This template requires any mutex.");
                if (mtx)
                {
                    mtx->try_lock();
                    mtx->unlock();
                    delete mtx;
                }
            }
            //
            // Базовый класс потока
            //
            template <typename T = uint32_t> class TBaseTh
            {
            private:
                bool terminated; // Запрос на остановку потока
                bool _create_suspended; // Запуск потока
                std::unique_ptr<std::thread> base_thread; // Поток

                //
                // Запуск потока
                //
                void Run()
                {
                    if (base_thread == nullptr)
                    {
                        base_thread = std::make_unique<std::thread>(&TBaseTh<T>::Execute, this);
                    }
                }

                //
                // Остановка потока
                //
                void Join()
                {
                    if (base_thread && base_thread->joinable())
                    {
                        base_thread->join();
                    }
                }

            protected:
                virtual void Execute() = 0; // Исполнительный метод потока
                bool Terminated() { return terminated; } // Метод возвращает запрос на завершение потока
                // !!!ВАЖНО!!! Вызывать в конструкторе дочернего класса после инициализации всех параметров
                void ThreadRun() { if (_create_suspended == false) Run(); } // Запуск потока из конструктора дочернего класса

            public:
                //
                // Конструктор
                //
                TBaseTh(bool create_suspended = false) : terminated(false), _create_suspended(create_suspended), base_thread(nullptr) {}
                //
                // Деструктор
                //
                virtual ~TBaseTh()
                {
                    terminated = true;
                    Join();
                    base_thread = nullptr;
                }
                //
                // Запуск потока
                //
                void Start() { Run(); }
                //
                // Остановка потока
                //
                void Terminate() { terminated = true; }
                //
                // Ожидание завершения потока
                //
                void Wait() { Join(); }
                //
                // Ожидание потока, миллисекунды
                //
                static void Sleep(std::size_t milliseconds)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
                }
            };

            using TBaseThread = TBaseTh<>;

            //
            // Семафор
            //
            template <typename T = uint32_t> class TBaseSemaphore
            {
            private:
                std::mutex mtx;
                std::condition_variable cv;
                size_t counter;

            public:
                //
                // Конструктор
                //
                TBaseSemaphore() : TBaseSemaphore(0) {}

                //
                // Конструктор
                //
                TBaseSemaphore(size_t initial_counter) : counter(initial_counter) {}

                //
                // Деструктор
                //
                ~TBaseSemaphore() {}

                //
                // Захват семафора
                //
                inline void Wait()
                {
                    std::unique_lock<decltype(mtx)> lock(mtx);
                    cv.wait(lock, [&]() { return counter > 0; });

                    if (counter > 0)
                    {
                        counter--;
                    }
                }

                inline bool WaitFor(size_t ms)
                {
                    std::unique_lock<decltype(mtx)> lock(mtx);

                    if (!cv.wait_for(lock, std::chrono::milliseconds(ms), [&]() { return counter > 0; }))
                    {
                        return false;
                    }
                    else if (counter > 0)
                    {
                        counter--;
                    }
                    return true;
                }

                //
                // Освобождение семафора
                //
                inline void Release(size_t count = 1)
                {
                    if (count == 0) count++;
                    {
                        std::lock_guard<decltype(mtx)> lock(mtx);
                        counter += count;
                    }
                    if (count > 1) cv.notify_all();
                    else cv.notify_one();
                }

                //
                // Сброс счётчика семафора (сброс счётчика до 0, закрытие доступа к ресурсу)
                //
                inline void ToZero()
                {
                    std::lock_guard<decltype(mtx)> lock(mtx);
                    counter = 0;
                }
            };

            using TSemaphore = TBaseSemaphore<>;
            //
            // Безопасная очередь
            //
            template <typename T> class TSafeQueue
            {
            private:
                std::mutex locker; // Обеспечивает монопольный доступ к данным класса
                TSemaphore read_semaphore; // Объект ожидания данных во время чтения
                TSemaphore write_semaphore; // Объект ожидания данных во время записи

                size_t max_items; // Максимальное количество записей в очереди
                std::deque<T> queue; // Очередь

            public:
                //
                // Конструктор
                //
                TSafeQueue() : TSafeQueue((std::numeric_limits<size_t>::max)()) {}
                //
                // Конструктор
                //
                TSafeQueue(size_t _max_items) :
                    max_items(_max_items == 0 ? (std::numeric_limits<size_t>::max)() : _max_items),
                    read_semaphore(0),
                    write_semaphore(_max_items == 0 ? (std::numeric_limits<size_t>::max)() : _max_items)
                    {}
                //
                // Деструктор
                //
                ~TSafeQueue()
                {
                    while (!queue.empty()) { queue.pop_back(); }
                }

                //
                // Запись данных в очередь
                //
                bool Push(const T& data, std::size_t ms_wait = (std::numeric_limits<size_t>::max)())
                {
                    if (ms_wait == (std::numeric_limits<size_t>::max)())
                    {
                        write_semaphore.Wait();
                    }
                    else
                    {
                        if (!write_semaphore.WaitFor(ms_wait)) return false;
                    }
                    {
                        std::lock_guard<decltype(locker)> lg(locker);

                        queue.push_back(data);

                        read_semaphore.Release();
                    }

                    return true;
                }

                //
                // Чтение данных из очереди
                //
                bool Pop(T& data, size_t ms_wait = (std::numeric_limits<size_t>::max)())
                {
                    while (true)
                    {
                        if (ms_wait == (std::numeric_limits<size_t>::max)())
                        {
                            read_semaphore.Wait();
                        }
                        else
                        {
                            if (!read_semaphore.WaitFor(ms_wait)) return false;
                        }
                        {
                            std::lock_guard<decltype(locker)> lg(locker);

                            if (queue.empty())
                            {
                                continue;
                            }

                            data = queue.front();
                            queue.pop_front();

                            write_semaphore.Release();
                        }
                        break;
                    }

                    return true;
                }

                //
                // Чтение данных из очереди без удаления элемента
                //
                bool First(T& data)
                {
                    std::lock_guard<decltype(locker)> lg(locker);

                    bool not_empty = !queue.empty();

                    if (not_empty)
                    {
                        data = queue.front();
                    }

                    return not_empty;
                }

                //
                // Количество элементов в очереди
                //
                std::size_t Size()
                {
                    std::lock_guard<decltype(locker)> lg(locker);
                    return std::size(queue);
                }

                //
                // Максимальное количество элементов в очереди
                //
                std::size_t MaxSize() { return max_items; }

                //
                // Пустая очередь или нет
                //
                bool IsEmpty()
                {
                    std::lock_guard<decltype(locker)> lg(locker);
                    return queue.empty();
                }

                //
                // Полная очередь или нет
                //
                bool IsFull()
                {
                    std::lock_guard<decltype(locker)> lg(locker);
                    return std::size(queue) == max_items;
                }

                //
                // Очистка очереди
                //
                void Clear(std::function<void(T)> data_routine = nullptr)
                {
                   std::lock_guard<decltype(locker)> lg(locker);

                    size_t count(std::size(queue));

                    while(!queue.empty())
                    {
                        if (data_routine)
                        {
                            data_routine(queue.front());
                        }

                        queue.pop_front();
                    }

                    write_semaphore.Release(count);
                    read_semaphore.ToZero();
                }
            };

            //
            // Пул памяти
            //
            template <typename T = int8_t> class TSafeMemoryPool
            {
                private:
                    std::mutex locker;              // Обеспечивает монопольный доступ к данным класса

                    std::size_t _num_elements;      // Количество элементов в одном блоке памяти

                    std::deque<T*> all_mem_blocks;  // Список всех блоков памяти

                    std::deque<T*> used_mem_blocks; // Список используемых блоков памяти

                    //
                    // Инициализация нового блока памяти
                    //
                    T* NewMemBlock() { return _num_elements > 1 ? new T[_num_elements] : new T; }

                    //
                    // Освобождение памяти выделенной под блок памяти
                    //
                    void FreeMemBlock(T* mem_block)
                    {
                        if (mem_block)
                        {
                            if (_num_elements > 1)
                                delete [] mem_block;
                            else
                                delete mem_block;
                        }
                    }

                public:
                    //
                    // Конструктор
                    //
                    TSafeMemoryPool(std::size_t num_elements) : _num_elements(num_elements == 0 ? 1 : num_elements) {}

                    //
                    // Деструктор
                    //
                    ~TSafeMemoryPool()
                    {
                        using namespace std;
                        //
                        // Освобождение памяти
                        //
                        for_each(begin(all_mem_blocks), end(all_mem_blocks), bind(&TSafeMemoryPool<T>::FreeMemBlock, this, placeholders::_1));
                        //
                        // Очистка списков
                        //
                        all_mem_blocks.clear();
                        used_mem_blocks.clear();
                    }

                    //
                    // Выделение памяти
                    //
                    T* New(std::function<void(T*, std::size_t)> data_routine = nullptr)
                    {
                        T* mem_block(nullptr);

                        {
                            std::lock_guard<decltype(locker)> lg(locker);

                            if (used_mem_blocks.empty())
                            {
                                mem_block = NewMemBlock();

                                all_mem_blocks.push_back(mem_block);
                            }
                            else
                            {
                                mem_block = used_mem_blocks.front();

                                used_mem_blocks.pop_front();
                            }
                        }

                        if (data_routine) data_routine(mem_block, _num_elements);

                        return mem_block;
                    }

                    //
                    // Быстрый возврат памяти в пул
                    //
                    void Delete(T* mem_block, std::function<void(T*, std::size_t)> data_routine = nullptr)
                    {
                        if (mem_block)
                        {
                            if (data_routine) data_routine(mem_block, _num_elements);

                            {
                                std::lock_guard<decltype(locker)> lg(locker);

                                used_mem_blocks.push_back(mem_block);
                            }
                        }
                    }

                    //
                    // Безопасный возврат памяти в пул
                    //
                    void SafeDelete(T* mem_block, std::function<void(T*, std::size_t)> data_routine = nullptr)
                    {
                        if (mem_block)
                        {
                            if (data_routine) data_routine(mem_block, _num_elements);

                            {
                                std::lock_guard<decltype(locker)> lg(locker);

                                if (auto check(find(begin(all_mem_blocks), end(all_mem_blocks), mem_block)); check != end(all_mem_blocks))
                                {
                                    used_mem_blocks.push_back(mem_block);
                                }
                            }
                        }
                    }

                    //
                    // Количество элементов в блоке памяти
                    //
                    std::size_t NumElements() { return _num_elements; }

                    //
                    // Размер блока памяти в байтах
                    //
                    std::size_t SizeMemBlock() { return _num_elements * sizeof(T); }
            };

            //
            // Безопасная очередь для передачи массива данных
            //
            template <typename T = int8_t> class TSafeArrayQueue : private TSafeQueue<T*>
            {
            private:
                TSafeMemoryPool<T> mem_pool;    // Пул для управления памятью

            public:
                //
                // Конструктор
                //
                TSafeArrayQueue(std::size_t num_elemets) : TSafeArrayQueue(num_elemets, (std::numeric_limits<size_t>::max)()) {}

                //
                // Конструктор
                //
                TSafeArrayQueue(std::size_t num_elemets, size_t max_items) : TSafeQueue<T*>(max_items), mem_pool(num_elemets) {}

                //
                // Деструктор
                //
                ~TSafeArrayQueue() {}

                //
                // Запись данных в очередь
                //
                bool Push(const void* data, std::size_t data_size, std::size_t ms_wait = (std::numeric_limits<size_t>::max)())
                {
                    if (data && (data_size <= mem_pool.SizeMemBlock()))
                    {
                        T* mem_block = mem_pool.New();

                        std::memcpy(mem_block, data, data_size);

                        if (TSafeQueue<T*>::Push(mem_block, ms_wait))
                        {
                            return true;
                        }

                        mem_pool.Delete(mem_block);
                    }

                    return false;
                }

                //
                // Чтение данных из очереди
                //
                bool Pop(void* data, std::size_t data_size, std::size_t ms_wait = (std::numeric_limits<size_t>::max)())
                {
                    if (data && (data_size >= mem_pool.SizeMemBlock()))
                    {
                        if (T* mem_block(nullptr); TSafeQueue<T*>::Pop(mem_block, ms_wait) && mem_block)
                        {
                            std::memcpy(data, mem_block, mem_pool.SizeMemBlock());

                            mem_pool.Delete(mem_block);

                            return true;
                        }
                    }

                    return false;
                }

                //
                // Чтение данных из очереди без удаления элемента
                //
                bool First(void* data, std::size_t data_size)
                {
                    if (data && (data_size >= mem_pool.SizeMemBlock()))
                    {
                        if (T* mem_block(nullptr); TSafeQueue<T*>::First(mem_block) && mem_block)
                        {
                            std::memcpy(data, mem_block, mem_pool.SizeMemBlock());

                            return true;
                        }
                    }

                    return false;
                }

                //
                // Количество элементов в очереди
                //
                using TSafeQueue<T*>::Size;

                //
                // Максимальное количество элементов в очереди
                //
                using TSafeQueue<T*>::MaxSize;

                //
                // Пустая очередь или нет
                //
                using TSafeQueue<T*>::IsEmpty;

                //
                // Полная очередь или нет
                //
                using TSafeQueue<T*>::IsFull;

                //
                // Очистка очереди
                //
                void Clear() { TSafeQueue<T*>::Clear([this](T* mem_block) { mem_pool.Delete(mem_block); }); }

                //
                // Размер в байтах одного блока
                //
                std::size_t DataSize() { return mem_pool.SizeMemBlock(); }
            };

            //
            // Безопасный буфер
            //
            template <typename T = int8_t> class TSafeBuffer
            {
            private:
                std::mutex locker;          // Обеспечивает монопольный доступ к данным класса
                std::vector<T> buffer;      // Буфер для хранения данных
                std::size_t buffer_size;    // Размер буфера в байтах

            public:
                //
                // Конструктор
                //
                TSafeBuffer(std::size_t num_elemets)
                {
                    num_elemets = num_elemets == 0 ? 1 : num_elemets;

                    buffer.resize(num_elemets);

                    buffer_size = num_elemets * sizeof(T);
                }

                //
                // Конструктор
                //
                TSafeBuffer(std::size_t num_elemets, const T& value)
                {
                    num_elemets = num_elemets == 0 ? 1 : num_elemets;

                    buffer.resize(num_elemets, value);

                    buffer_size = num_elemets * sizeof(T);
                }

                //
                // Конструктор
                //
                TSafeBuffer(std::size_t num_elemets, std::function<void(T&)> data_routine) : TSafeBuffer(num_elemets)
                {
                    if (data_routine)
                    {
                        std::for_each(std::begin(buffer), std::end(buffer), data_routine);
                    }
                }

                //
                // Деструктор
                //
                ~TSafeBuffer() {}

                //
                // Запись данных в очередь
                //
                bool Write(const void* data, std::size_t data_size)
                {
                    if (data && (data_size <= buffer_size))
                    {
                        std::lock_guard<decltype(locker)> lg(locker);

                        std::memcpy(std::data(buffer), data, data_size);

                        return true;
                    }

                    return false;
                }

                //
                // Чтение данных из буфера
                //
                bool Read(void* data, std::size_t data_size)
                {
                    if (data && (data_size >= buffer_size))
                    {
                        std::lock_guard<decltype(locker)> lg(locker);

                        std::memcpy(data, std::data(buffer), buffer_size);

                        return true;
                    }

                    return false;
                }

                //
                // Размер в байтах одного блока
                //
                std::size_t BufferSize() { return buffer_size; }
            };
        }
    }
    //
    // Работа с контрольными суммами
    //
    namespace Crypto
    {
        template<typename T = std::string> class TCRC {
        private:
            static_assert(Constexpr::is_string_wstring<T>, "This template requires the type std::string or std::wstring.");
            //
            // Таблица для быстрого расчета контрольной суммы CRC32-IEEE 802.3
            //
            inline static const uint32_t crc32table[256] = {
                0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F,
                0xE963A535, 0x9E6495A3, 0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
                0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91, 0x1DB71064, 0x6AB020F2,
                0xF3B97148, 0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
                0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9,
                0xFA0F3D63, 0x8D080DF5, 0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
                0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B, 0x35B5A8FA, 0x42B2986C,
                0xDBBBC9D6, 0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,
                0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423,
                0xCFBA9599, 0xB8BDA50F, 0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
                0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D, 0x76DC4190, 0x01DB7106,
                0x98D220BC, 0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
                0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D,
                0x91646C97, 0xE6635C01, 0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
                0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457, 0x65B0D9C6, 0x12B7E950,
                0x8BBEB8EA, 0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,
                0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7,
                0xA4D1C46D, 0xD3D6F4FB, 0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
                0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9, 0x5005713C, 0x270241AA,
                0xBE0B1010, 0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
                0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81,
                0xB7BD5C3B, 0xC0BA6CAD, 0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
                0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683, 0xE3630B12, 0x94643B84,
                0x0D6D6A3E, 0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,
                0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB,
                0x196C3671, 0x6E6B06E7, 0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
                0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5, 0xD6D6A3E8, 0xA1D1937E,
                0x38D8C2C4, 0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
                0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55,
                0x316E8EEF, 0x4669BE79, 0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
                0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F, 0xC5BA3BBE, 0xB2BD0B28,
                0x2BB45A92, 0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,
                0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F,
                0x72076785, 0x05005713, 0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
                0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21, 0x86D3D2D4, 0xF1D4E242,
                0x68DDB3F8, 0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
                0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69,
                0x616BFFD3, 0x166CCF45, 0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
                0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB, 0xAED16A4A, 0xD9D65ADC,
                0x40DF0B66, 0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,
                0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693,
                0x54DE5729, 0x23D967BF, 0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
                0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D };

            inline static const uint32_t crc32table_kdg[] = {
                0x0, 0x4C11DB7, 0x9823B6E, 0xD4326D9, 0x130476DC, 0x17C56B6B, 0x1A864DB2,
                0x1E475005, 0x2608EDB8, 0x22C9F00F, 0x2F8AD6D6, 0x2B4BCB61, 0x350C9B64,
                0x31CD86D3, 0x3C8EA00A, 0x384FBDBD, 0x4C11DB70, 0x48D0C6C7, 0x4593E01E,
                0x4152FDA9, 0x5F15ADAC, 0x5BD4B01B, 0x569796C2, 0x52568B75, 0x6A1936C8,
                0x6ED82B7F, 0x639B0DA6, 0x675A1011, 0x791D4014, 0x7DDC5DA3, 0x709F7B7A,
                0x745E66CD, 0x9823B6E0, 0x9CE2AB57, 0x91A18D8E, 0x95609039, 0x8B27C03C,
                0x8FE6DD8B, 0x82A5FB52, 0x8664E6E5, 0xBE2B5B58, 0xBAEA46EF, 0xB7A96036,
                0xB3687D81, 0xAD2F2D84, 0xA9EE3033, 0xA4AD16EA, 0xA06C0B5D, 0xD4326D90,
                0xD0F37027, 0xDDB056FE, 0xD9714B49, 0xC7361B4C, 0xC3F706FB, 0xCEB42022,
                0xCA753D95, 0xF23A8028, 0xF6FB9D9F, 0xFBB8BB46, 0xFF79A6F1, 0xE13EF6F4,
                0xE5FFEB43, 0xE8BCCD9A, 0xEC7DD02D, 0x34867077, 0x30476DC0, 0x3D044B19,
                0x39C556AE, 0x278206AB, 0x23431B1C, 0x2E003DC5, 0x2AC12072, 0x128E9DCF,
                0x164F8078, 0x1B0CA6A1, 0x1FCDBB16, 0x18AEB13, 0x54BF6A4, 0x808D07D,
                0xCC9CDCA, 0x7897AB07, 0x7C56B6B0, 0x71159069, 0x75D48DDE, 0x6B93DDDB,
                0x6F52C06C, 0x6211E6B5, 0x66D0FB02, 0x5E9F46BF, 0x5A5E5B08, 0x571D7DD1,
                0x53DC6066, 0x4D9B3063, 0x495A2DD4, 0x44190B0D, 0x40D816BA, 0xACA5C697,
                0xA864DB20, 0xA527FDF9, 0xA1E6E04E, 0xBFA1B04B, 0xBB60ADFC, 0xB6238B25,
                0xB2E29692, 0x8AAD2B2F, 0x8E6C3698, 0x832F1041, 0x87EE0DF6, 0x99A95DF3,
                0x9D684044, 0x902B669D, 0x94EA7B2A, 0xE0B41DE7, 0xE4750050, 0xE9362689,
                0xEDF73B3E, 0xF3B06B3B, 0xF771768C, 0xFA325055, 0xFEF34DE2, 0xC6BCF05F,
                0xC27DEDE8, 0xCF3ECB31, 0xCBFFD686, 0xD5B88683, 0xD1799B34, 0xDC3ABDED,
                0xD8FBA05A, 0x690CE0EE, 0x6DCDFD59, 0x608EDB80, 0x644FC637, 0x7A089632,
                0x7EC98B85, 0x738AAD5C, 0x774BB0EB, 0x4F040D56, 0x4BC510E1, 0x46863638,
                0x42472B8F, 0x5C007B8A, 0x58C1663D, 0x558240E4, 0x51435D53, 0x251D3B9E,
                0x21DC2629, 0x2C9F00F0, 0x285E1D47, 0x36194D42, 0x32D850F5, 0x3F9B762C,
                0x3B5A6B9B, 0x315D626, 0x7D4CB91, 0xA97ED48, 0xE56F0FF, 0x1011A0FA,
                0x14D0BD4D, 0x19939B94, 0x1D528623, 0xF12F560E, 0xF5EE4BB9, 0xF8AD6D60,
                0xFC6C70D7, 0xE22B20D2, 0xE6EA3D65, 0xEBA91BBC, 0xEF68060B, 0xD727BBB6,
                0xD3E6A601, 0xDEA580D8, 0xDA649D6F, 0xC423CD6A, 0xC0E2D0DD, 0xCDA1F604,
                0xC960EBB3, 0xBD3E8D7E, 0xB9FF90C9, 0xB4BCB610, 0xB07DABA7, 0xAE3AFBA2,
                0xAAFBE615, 0xA7B8C0CC, 0xA379DD7B, 0x9B3660C6, 0x9FF77D71, 0x92B45BA8,
                0x9675461F, 0x8832161A, 0x8CF30BAD, 0x81B02D74, 0x857130C3, 0x5D8A9099,
                0x594B8D2E, 0x5408ABF7, 0x50C9B640, 0x4E8EE645, 0x4A4FFBF2, 0x470CDD2B,
                0x43CDC09C, 0x7B827D21, 0x7F436096, 0x7200464F, 0x76C15BF8, 0x68860BFD,
                0x6C47164A, 0x61043093, 0x65C52D24, 0x119B4BE9, 0x155A565E, 0x18197087,
                0x1CD86D30, 0x29F3D35, 0x65E2082, 0xB1D065B, 0xFDC1BEC, 0x3793A651,
                0x3352BBE6, 0x3E119D3F, 0x3AD08088, 0x2497D08D, 0x2056CD3A, 0x2D15EBE3,
                0x29D4F654, 0xC5A92679, 0xC1683BCE, 0xCC2B1D17, 0xC8EA00A0, 0xD6AD50A5,
                0xD26C4D12, 0xDF2F6BCB, 0xDBEE767C, 0xE3A1CBC1, 0xE760D676, 0xEA23F0AF,
                0xEEE2ED18, 0xF0A5BD1D, 0xF464A0AA, 0xF9278673, 0xFDE69BC4, 0x89B8FD09,
                0x8D79E0BE, 0x803AC667, 0x84FBDBD0, 0x9ABC8BD5, 0x9E7D9662, 0x933EB0BB,
                0x97FFAD0C, 0xAFB010B1, 0xAB710D06, 0xA6322BDF, 0xA2F33668, 0xBCB4666D,
                0xB8757BDA, 0xB5365D03, 0xB1F740B4};

        public:
            //
            // Расчёт контрольной суммы CRC32
            //
            static uint32_t CRC32(const char* buffer, size_t size, uint32_t crcin = 0)
            {
                uint32_t crc = crcin == 0 ? 0xFFFFFFFFUL : crcin ^ 0xFFFFFFFFUL;
                while (size--)
                    crc = (crc >> 8) ^ crc32table[(crc ^ *buffer++) & 0xFF];
                return crc ^ 0xFFFFFFFFUL;
            }
            //
            // Расчёт контрольной суммы CRC32 KDG (Специфичная функция, для ЛМЗ)
            //
            static uint32_t CRC32KDG(const char* buffer, size_t size, uint32_t crcin = 0)
            {
                uint32_t crc = crcin == 0 ? 0xFFFFFFFFUL : ~crcin;
                for (uint32_t i(0); i < size; i++) {
                    uint8_t index = (crc >> 24) ^ buffer[i];
                    crc = (crc << 8) ^ crc32table_kdg[index];
                }
                return ~crc;
            }
            //
            // Расчёт hash суммы 32 бита
            //
            static uint32_t Normal_HASH32(const T& hash, const std::locale& loc = std::locale())
            {
                std::string _hash = String::TConverter<decltype(_hash)>::ToString(hash, loc);
                return CRC32(StdExtension::C_STR(_hash), size(_hash));
            }
            //
            // Расчёт hash суммы 32 бита
            //
            static uint32_t UPPER_HASH32(const T& hash, const std::locale& loc = std::locale())
            {
                std::string _hash = String::TConverter<decltype(_hash)>::ToString(hash, loc);
                String::TFormater<decltype(_hash)>::UpperCase(_hash, loc);
                return CRC32(StdExtension::C_STR(_hash), size(_hash));
            }
            //
            // Расчёт hash суммы size_t
            //
            static size_t UPPER_HASH(const T& hash, const std::locale& loc = std::locale())
            {
                T _hash(hash);
                String::TFormater<T>::UpperCase(_hash, loc);
                return std::hash<T>()(_hash);
            }
            //
            // Расчёт hash суммы size_t
            //
            static size_t HASH(const T& hash, const std::locale& loc = std::locale())
            {
                return std::hash<T>()(hash);
            }
            //
            // Расчёт hash суммы по алгоритму фирмы InSys использовалась на LMZ (много коллизий использовать не рекомендуется)
            //
            static uint32_t InSysHASH(const T& hash, const std::locale& loc = std::locale())
            {
                if (hash.empty()) return 0;

                std::string _hash = String::TConverter<decltype(_hash)>::ToString(hash, loc);
                String::TFormater<decltype(_hash)>::UpperCase(_hash, loc);

                const unsigned long c = (unsigned long)0xF0000000UL;
                unsigned long var1, var2;
                unsigned long prev = 0;

                for (size_t s = 0; s < std::size(_hash); s++)
                {
                    var1 = static_cast<unsigned char>(_hash[s]) + ((prev << 4) | (prev >> (sizeof(prev) * 8 - 4)));
                    var2 = var1 & c;
                    if (var2 != 0)
                        prev = (~c) & (((var2 >> 24) | (var2 << (sizeof(var2) * 8 - 24))) ^ var1);
                    else
                        prev = var1;
                }
                return prev;
            }
        };
    }
    //
    // Работа с файловой системой
    //
    namespace FileSystem {
        //
        // Шаблон содержит методы для работы с файлом
        //
        template<typename T> class TFile
        {
        private:
            static_assert(Constexpr::is_string_wstring<T>, "This template requires the type std::string or std::wstring.");
        public:
            //
            // Чтение файла целиком
            // Входные параметры:
            //          path - путь к файлу
            //          error - переменная для возврата описания ошибки
            //          loc - локализация.
            // Возвращаемое значение:
            //          first умный указатель на буфер с данными, second - размер файла.
            //          Если возникла ошибка то first равен nullptr, second равен 0.
            //          Переменная error содержит описание ошибки
            //
            static std::pair<std::shared_ptr<char>, size_t> ReadAll(const stdfs::path& path, T& error, const std::locale& loc = std::locale())
            {
                using namespace std;

                error = String::TConverter<T>::EmptyString();

                if (stdfs::exists(path))
                {
                    //
                    // Определяем размер файла
                    //
                    size_t fsize = static_cast<decltype(fsize)>(stdfs::file_size(path));
                    //
                    // Подготовка буфера для чтения файла
                    //
                    size_t buffer_size(fsize + 1);
                    shared_ptr<char> buffer (new char[buffer_size], default_delete<char[]>());
                    memset(buffer.get(), 0, buffer_size * sizeof(char));
                    //
                    // Чтение файла
                    //
                    if (ifstream _file(path, ifstream::binary | ifstream::in); _file.is_open())
                    {
                        _file.read(buffer.get(), fsize);
                        _file.close();

                        return pair(buffer, fsize);
                    }
                    else
                    {
                        String::TFormater<T>::VoidConcatenate(error, loc, "Could not open file: ", path.string());
                    }
                }
                else
                {
                    String::TFormater<T>::VoidConcatenate(error, loc, "File does not exist: ", path.string());
                }

                return pair(nullptr, 0);
            }
        };
        //
        // Интерфейс описывает базовые низкоуровневые методы для работы с ini файлами
        //
        template <typename T> class TIniBaseInterface
        {
        public:
            //
            // Конструктор
            //
            TIniBaseInterface() {}
            //
            // Деструктор
            //
            virtual ~TIniBaseInterface() {}
            //
            // Список групп
            //
            virtual void GetGroups(std::vector<std::string>& groups) = 0;
            //
            // Метод возвращает дескриптор группы
            //
            virtual void* GetGroup(const std::string& group, bool create, const std::locale& loc) = 0;
            //
            // Метод возвращает список параметров в группе
            //
            virtual void GetValues(void* group_handle, std::vector<std::pair<std::string, std::string>>& values) = 0;
            //
            // Метод возвращает параметр группы
            //
            virtual std::string* GetValue(void* group_handle, const std::string& key, const std::locale& loc) = 0;
            //
            // Метод добавляет параметр в группу (даже если он существует)
            //
            virtual void AddValue(void* group_handle, const std::string& key, const std::string& value, const std::locale& loc) = 0;
            //
            // Метод записывает параметр в группу, если параметр уже существует, объединяет значение
            //
            virtual void MergeValue(void* group_handle, const std::string& key, const std::string& value, const std::locale& loc) = 0;
        };
        //
        // Шаблон реализует интерфейс TIniBaseInterface, операции поиска и сравнения идут со строками
        //
        template <typename T = std::string> class TIniStringStorage : public TIniBaseInterface<T>
        {
        private:
            using TKeyValueList = std::vector<std::pair<std::string, std::string>>;
            using TGroup        = std::pair<std::string, TKeyValueList>;

        protected:
            std::vector<TGroup> ini; // ini файла

        public:
            //
            // Список групп
            //
            void GetGroups(std::vector<std::string>& groups) override
            {
                using namespace std;

                groups.resize(size(ini));

                transform(begin(ini), end(ini), begin(groups), [] (const TGroup& value) { return value.first; });
            }
            //
            // Метод возвращает дескриптор группы
            //
            void* GetGroup(const std::string& group, bool create, const std::locale& loc = std::locale()) override
            {
                using namespace std;

                if (auto group_it = find_if(begin(ini), end(ini), [&group, &loc](const TGroup& value) { return String::TExtension<string>::Compare(group, value.first, true, loc); }); group_it != end(ini))
                {
                    return &(group_it->second);
                }
                else if (create)
                {
                    ini.push_back(TGroup(group, TKeyValueList()));
                    return &(ini.back().second);
                }

                return nullptr;
            }
            //
            // Метод возвращает список параметров в группе
            //
            void GetValues(void* group_handle, std::vector<std::pair<std::string, std::string>>& values) override
            {
                if (TKeyValueList* key_value_list(static_cast<TKeyValueList*>(group_handle)); key_value_list)
                {
                    values = *key_value_list;
                }
                else
                {
                    values.clear();
                }
            }
            //
            // Метод возвращает параметр группы
            //
            std::string* GetValue(void* group_handle, const std::string& key, const std::locale& loc = std::locale()) override
            {
                using namespace std;

                if (TKeyValueList* key_value_list(static_cast<TKeyValueList*>(group_handle)); key_value_list)
                {
                    if (auto key_value_it = find_if(begin(*key_value_list), end(*key_value_list), [&key, &loc](const pair<string, string>& value) { return String::TExtension<string>::Compare(value.first, key, true, loc); }); key_value_it != end(*key_value_list))
                    {
                        return &(key_value_it->second);
                    }
                }

                return nullptr;
            }
            //
            // Метод добавляет параметр в группу (даже если он существует)
            //
            void AddValue(void* group_handle, const std::string& key, const std::string& value, const std::locale& loc = std::locale()) override
            {
                if (TKeyValueList* key_value_list(static_cast<TKeyValueList*>(group_handle)); key_value_list)
                {
                    key_value_list->push_back(std::pair(key, value));
                }
            }
            //
            // Метод записывает параметр в группу, если параметр уже существует, объединяет значение
            //
            void MergeValue(void* group_handle, const std::string& key, const std::string& value, const std::locale& loc = std::locale()) override
            {
                using namespace std;

                if (string* _value = GetValue(group_handle, key, loc); _value)
                {
                    *_value = value;
                }
                else
                {
                    AddValue(group_handle, key, value, loc);
                }
            }
        };
        //
        // Шаблон реализует интерфейс TIniBaseInterface, операции поиска и сравнения идут с HASH суммой
        //
        template <typename T = std::string> class TIniHashStorage : public TIniBaseInterface<T>
        {
        private:
            struct TKeyValue { std::string name; uint32_t hash; std::string value; };

            using TKeyValueList = std::vector<TKeyValue>;

            struct TGroup { std::string name; uint32_t hash; TKeyValueList key_value_list; };

        protected:
            std::vector<TGroup> ini; // ini файла
            //
            // Формирование HASH суммы
            //
            uint32_t MakeHash(const std::string& value, const std::locale& loc = std::locale())
            {
                return Crypto::TCRC<std::string>::UPPER_HASH32(value, loc);
            }

        public:
            //
            // Список групп
            //
            void GetGroups(std::vector<std::string>& groups) override
            {
                using namespace std;

                groups.resize(size(ini));

                std::transform(begin(ini), end(ini), begin(groups), [] (const TGroup& value) { return value.name; });
            }
            //
            // Метод возвращает дескриптор группы
            //
            void* GetGroup(const std::string& group, bool create, const std::locale& loc = std::locale()) override
            {
                uint32_t group_hash(MakeHash(group, loc));
                //
                // Возвращаем существующий набор опций
                //
                if (auto group_it = find_if(begin(ini), end(ini), [group_hash](const TGroup& value) { return value.hash == group_hash; }); group_it != end(ini))
                {
                    return &(group_it->key_value_list);
                }
                else if (create) // Создаём новый набор опций
                {
                    ini.push_back( { group, group_hash, {} } );
                    return &(ini.back().key_value_list);
                }

                return nullptr;
            }
            //
            // Метод возвращает список параметров в группе
            //
            void GetValues(void* group_handle, std::vector<std::pair<std::string, std::string>>& values) override
            {
                if (TKeyValueList* key_value_list(static_cast<TKeyValueList*>(group_handle)); key_value_list)
                {
                    values.resize(size(*key_value_list));
                    transform(begin(*key_value_list), end(*key_value_list), begin(values), [](const TKeyValue& _value) { return std::pair(_value.name, _value.value); });
                }
                else
                {
                    values.clear();
                }
            }
            //
            // Метод возвращает параметр группы
            //
            std::string* GetValue(void* group_handle, const std::string& key, const std::locale& loc = std::locale()) override
            {
                if (TKeyValueList* key_value_list(static_cast<TKeyValueList*>(group_handle)); key_value_list)
                {
                    uint32_t key_hash(MakeHash(key, loc));

                    if (auto key_value_it = find_if(begin(*key_value_list), end(*key_value_list), [key_hash](const TKeyValue& _value) { return _value.hash == key_hash; }); key_value_it != end(*key_value_list))
                    {
                        return &(key_value_it->value);
                    }
                }

                return nullptr;
            }
            //
            // Метод добавляет параметр в группу (даже если он существует)
            //
            void AddValue(void* group_handle, const std::string& key, const std::string& value, const std::locale& loc = std::locale()) override
            {
                if (TKeyValueList* key_value_list(static_cast<TKeyValueList*>(group_handle)); key_value_list)
                {
                    key_value_list->push_back( { key, MakeHash(key, loc), value } );
                }
            }
            //
            // Метод записывает параметр в группу, если параметр уже существует, объединяет значение
            //
            void MergeValue(void* group_handle, const std::string& key, const std::string& value, const std::locale& loc = std::locale()) override
            {
                using namespace std;

                if (string* _value = GetValue(group_handle, key, loc); _value)
                {
                    *_value = value;
                }
                else
                {
                    AddValue(group_handle, key, value, loc);
                }
            }
        };
        //
        // Шаблон описывает базовый класс для работы с ini файлом
        //
        template <typename T, typename StorageClass = TIniStringStorage<T>> class TIniBase
        {
        private:
            static_assert(Constexpr::is_string_wstring<T>, "This template requires the type std::string or std::wstring.");

        protected:
            std::unique_ptr<TIniBaseInterface<T>> base_interface = std::make_unique<StorageClass>();

        public:
            //
            // Чтение списка групп ini файла
            //
            void GetGroups(std::vector<T>& groups, const std::locale& loc = std::locale())
            {
                using namespace std;

                if constexpr(Constexpr::is_string<T>) // std::string
                {
                    base_interface->GetGroups(groups);
                }
                else // std::wstring
                {
                    vector<string> _groups;

                    base_interface->GetGroups(_groups);

                    groups.clear();

                    for (const auto& _group : _groups)
                    {
                        groups.push_back(String::TConverter<wstring>::ToString(_group, loc));
                    }
                }
            }
            //
            // Чтение списка параметров в группе
            //
            bool GetValues(const T& group, std::vector<std::pair<T, T>>& key_value, const std::locale& loc = std::locale())
            {
                using namespace std;

                if constexpr(Constexpr::is_string<T>) // std::string
                {
                    if (void* group_handle(base_interface->GetGroup(group, false, loc)); group_handle)
                    {
                        base_interface->GetValues(group_handle, key_value);

                        return true;
                    }
                }
                else // std::wstring
                {
                    string _group = String::TConverter<decltype(_group)>::ToString(group, loc);

                    if (void* group_handle(base_interface->GetGroup(_group, false, loc)); group_handle)
                    {
                        vector<pair<string, string>> _key_value;

                        base_interface->GetValues(group_handle, _key_value);

                        key_value.clear();

                        for (const auto& [ _key, _value] : _key_value)
                        {
                            key_value.push_back( {
                                String::TConverter<T>::ToString(_key, loc),
                                String::TConverter<T>::ToString(_value, loc)
                            });
                        }

                        return true;
                    }
                }

                return false;
            }
            //
            // Чтение параметров ini файла
            //
            template<typename Type = T> Type GetValue(const T& group, const T& key, const Type& def, bool def_if_empty = false, const std::locale& loc = std::locale())
            {
                using namespace std;
                using namespace Constexpr;

                string _group, _key;

                if constexpr(Constexpr::is_wstring<T>)
                {
                    _group  = String::TConverter<string>::ToString(group, loc);
                    _key    = String::TConverter<string>::ToString(key, loc);
                }
                else
                {
                    _group  = group;
                    _key    = key;
                }

                if (void* group_handle = base_interface->GetGroup(_group, false, loc); group_handle)
                {
                    if (string* value = base_interface->GetValue(group_handle, _key, loc); value)
                    {
                        if constexpr(is_string_wstring<Type>) // string or wstring
                        {
                            return def_if_empty && value->empty() ? def : String::TConverter<Type>::ToString(*value, loc);
                        }
                        else
                        {
                            return String::TConverter<string>::FromString<Type>(*value, def, loc);
                        }
                    }
                }

                return def;
            }
            //
            // Чтение параметров ini файла, путь
            //
            stdfs::path GetValue(const T& group, const T& key, const stdfs::path& def, bool def_if_empty = false, const std::locale& loc = std::locale())
            {
                using namespace std;

                basic_string<typename T::value_type, std::char_traits<typename T::value_type>, std::allocator<typename T::value_type>> def_path;

                if constexpr(Constexpr::is_string<T>)
                {
                    def_path = def.string();
                }
                else
                {
                    def_path = def.wstring();
                }

                return GetValue(group, key, def_path, def_if_empty, loc);
            }
            //
            // Запись параметра в ini файл
            //
            template<typename Type = T> void SetValue(const T& group, const T& key, const Type& value, const std::locale& loc = std::locale())
            {
                using namespace std;
                using namespace Constexpr;

                string _group, _key, _value;
                //
                // Группа и параметр
                //
                if constexpr(Constexpr::is_wstring<T>)
                {
                    _group  = String::TConverter<string>::ToString(group, loc);
                    _key    = String::TConverter<string>::ToString(key, loc);
                }
                else
                {
                    _group  = group;
                    _key    = key;
                }
                //
                // Значение параметра
                //
                if constexpr(is_string<Type>)
                {
                    _value = value;
                }
                else if constexpr(is_float<Type>)
                {
                    _value = String::TConverter<decltype(_value)>::ToString(value, loc, std::numeric_limits<Type>::max_digits10);
                }
                else
                {
                    _value = String::TConverter<decltype(_value)>::ToString(value, loc);
                }
                //
                // Сохраняем результат
                //
                if (void* group_handle = base_interface->GetGroup(_group, true, loc); group_handle)
                {
                    base_interface->MergeValue(group_handle, _key, _value, loc);
                }
            }
            //
            // Запись параметра в ini файл, путь
            //
            void SetValue(const T& group, const T& key, const stdfs::path& value, const std::locale& loc = std::locale())
            {
                std::basic_string<typename T::value_type, std::char_traits<typename T::value_type>, std::allocator<typename T::value_type>> str_path;

                if constexpr(Constexpr::is_string<T>)
                {
                    str_path = value.string();
                }
                else
                {
                    str_path = value.wstring();
                }

                SetValue(group, key, str_path, loc);
            }
        };
        //
        // Шаблон обеспечивает чтение данных из ini файла
        //
        template <typename T, typename StorageClass = TIniStringStorage<T>> class TIniReader : public TIniBase<T, StorageClass>
        {
        public:
            //
            // Разбор ini файла
            //
            bool Parse(const stdfs::path& path, T& error, const std::locale& loc = std::locale())
            {
                using namespace std;

                if (stdfs::exists(path))
                {
                    if (ifstream ini_file(path.string(), ios::in); ini_file.is_open())
                    {
                        bool result(true);

                        string ini_line;
                        void* ini_group = nullptr;

                        smatch base_match;

                        regex comment("^\\s*(?:[;#]|[Rr][Ee][Mm]\\s|//).*$");
                        regex group("^\\s*\\[.+\\]\\s*$");
                        regex param_with_comment("^(.+=.+?)(?:\\s[;#]|\\s//|\\s[Rr][Ee][Mm]\\s).*$");

                        for (size_t line_counter(1); !ini_file.eof(); line_counter++)
                        {
                            std::getline(ini_file, ini_line);

                            T_VOID_AUTO_ENCODING(ini_line);

                            String::TExtension<string>::VoidTrim(ini_line);
                            //
                            // Пустая строка или найден комментарий
                            //
                            if (ini_line.empty() || regex_match(ini_line, comment))
                            {
                                continue;
                            }
                            else if(regex_match(ini_line, group)) // Найдена группа
                            {
                                ini_line = ini_line.erase(0, 1).erase(size(ini_line) - 1, 1);

                                String::TExtension<string>::VoidTrim(ini_line);

                                ini_group = TIniBase<T, StorageClass>::base_interface->GetGroup(ini_line, true, loc);
                            }
                            else // Найден параметр
                            {
                                StdExtension::TSamePair<string> ini_pair('=');
                                //
                                // Найден параметр с комментарием
                                //
                                if (regex_match(ini_line, base_match, param_with_comment) && (size(base_match) == 2))
                                {
                                    ini_pair.Set(base_match[1].str());
                                }
                                else // Найден параметр без комментариев
                                {
                                    ini_pair.Set(ini_line);
                                }
                                //
                                // Проверка на корректность структуры параметра
                                //
                                if (ini_pair.IsMatched())
                                {
                                    if (ini_group)
                                    {
                                        String::TExtension<string>::VoidTrim(ini_pair.second, "\"");
                                        String::TExtension<string>::VoidTrim(ini_pair.second, "\'");

                                        TIniBase<T, StorageClass>::base_interface->MergeValue(ini_group, ini_pair.first, ini_pair.second, loc);
                                    }
                                    else
                                    {
                                        String::TFormater<T>::VoidFormat(error, String::TConverter<T>::ToString("Error in the structure of the ini file. Group not found. Line {0}. Text:{1}."), loc, line_counter, ini_line);
                                        result = false;
                                        break;
                                    }
                                }
                                else // Ошибка в структуре ini файла
                                {
                                    String::TFormater<T>::VoidFormat(error, String::TConverter<T>::ToString("Error in the structure of the ini file. Line {0}. Text:{1}."), loc, line_counter, ini_line);
                                    result = false;
                                    break;
                                }
                            }
                        }

                        ini_file.close();

                        return result;
                    }
                    else
                    {
                        String::TFormater<T>::VoidConcatenate(error, loc, "Could not open file: ", path.string());
                    }
                }
                else
                {
                    String::TFormater<T>::VoidConcatenate(error, loc, "File does not exist: ", path.string());
                }

                return false;
            }
        };
        //
        // Шаблон обеспечивает запись данных в ini файл
        //
        template <typename T, typename StorageClass = TIniStringStorage<T>> class TIniWriter : public TIniBase<T, StorageClass>
        {
        public:
            //
            // Запись ini файла
            //
            bool Write(const stdfs::path& path, T& error, const std::locale& loc = std::locale())
            {
                using namespace std;

                if (ofstream ini_file(path.string(), ios::out | ios::trunc); ini_file.is_open())
                {
                    vector<string> groups;
                    vector<pair<string, string>> key_value;

                    TIniBase<T, StorageClass>::base_interface->GetGroups(groups);

                    for (const auto& group : groups)
                    {
                        ini_file << "[" << group << "]" << endl;

                        if (void* group_handle = TIniBase<T, StorageClass>::base_interface->GetGroup(group, false, loc); group_handle)
                        {
                            TIniBase<T, StorageClass>::base_interface->GetValues(group_handle, key_value);

                            for (auto& [key, value] : key_value)
                            {
                                ini_file << key << " = " << value << endl;
                            }
                        }

                        ini_file << endl;
                    }

                    ini_file.close();

                    return true;
                }

                return false;
            }
        };

        using TStringIniBase = TIniBase<std::string, TIniStringStorage<std::string>>;
        using TWStringIniBase = TIniBase<std::wstring, TIniStringStorage<std::wstring>>;

        using TStringIniReader = TIniReader<std::string, TIniStringStorage<std::string>>;
        using TWStringIniReader = TIniReader<std::wstring, TIniStringStorage<std::wstring>>;

        using TStringIniWrite = TIniWriter<std::string, TIniStringStorage<std::string>>;
        using TWStringIniWrite = TIniWriter<std::wstring, TIniStringStorage<std::wstring>>;
    }
}
// ---------------------------------------------------------------------------
#endif // End FW_BASE_HPP