// ---------------------------------------------------------------------------
#include <gtest/gtest.h>
#include <fw_base.hpp>
// ---------------------------------------------------------------------------
//
// Тип операционной системы
//
#if defined(WINDOWS)
    #define TSTR(VALUE) VALUE

    inline const char os_type[] = "Windows";
    inline const char locale_name[] = "Russian_Russia.1251";
#elif defined(LINUX)
    #define TSTR(VALUE) VALUE

    inline const char os_type[] = "Linux";
    inline const char locale_name[] = "ru_RU.UTF8";
#else
    inline const char os_type[] = "";
    inline const char locale_name[] = "";
#endif
// ---------------------------------------------------------------------------
#define CRC_CHECK
// ---------------------------------------------------------------------------
using TSConverter = Framework::String::TConverter<std::string>;
using TWConverter = Framework::String::TConverter<std::wstring>;

using TSFormater = Framework::String::TFormater<std::string>;
using TWFormater = Framework::String::TFormater<std::wstring>;

using TSExtension = Framework::String::TExtension<std::string>;
using TWExtension = Framework::String::TExtension<std::wstring>;

using TSEncoding = Framework::String::TEncoding<std::string>;
using TWEncoding = Framework::String::TEncoding<std::wstring>;

using TSSamePair = Framework::StdExtension::TSamePair<std::string>;
using TWSamePair = Framework::StdExtension::TSamePair<std::wstring>;

using TSCRC = Framework::Crypto::TCRC<std::string>;
using TWCRC = Framework::Crypto::TCRC<std::wstring>;
// ---------------------------------------------------------------------------
#pragma region TConverter
TEST(TConverter, ToStringCharPrt)
{
    //
    // TSConverter (eng)
    //
    {
        const char input[] = "Hello World";
        std::string output("Hello World");
        {
            auto result = TSConverter::ToString(input);
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }

        {
            auto result = TSConverter::ToString(input, strlen(input));
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }
    }
    //
    // TSConverter (ru)
    //
    {
        std::locale _locale(locale_name);

        const char input[] = "Привет Мир";
        std::string output("Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        {
            auto result = TSConverter::ToString(input, _locale);
            T_VOID_AUTO_ENCODING_LOC(result, _locale);
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }

        {
            auto result = TSConverter::ToString(input, strlen(input), _locale);
            T_VOID_AUTO_ENCODING_LOC(result, _locale);
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }
    }
    //
    // TWConverter (eng)
    //
    {
        const char input[] = "Hello World";
        std::wstring output(L"Hello World");
        {
            auto result = TWConverter::ToString(input);
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }

        {
            auto result = TWConverter::ToString(input, strlen(input));
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }
    }
    //
    // TWConverter (ru)
    //
    {
        std::locale _locale(locale_name);

        const char input[] = "Привет Мир";
        std::wstring output(L"Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        {
            auto result = TWConverter::ToString(input, _locale);
            T_VOID_AUTO_ENCODING_LOC(result, _locale);
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }

        {
            auto result = TWConverter::ToString(input, strlen(input), _locale);
            T_VOID_AUTO_ENCODING_LOC(result, _locale);
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }
    }
}
// ---------------------------------------------------------------------------
TEST(TConverter, ToStringString)
{
    //
    // TSConverter (eng)
    //
    {
        std::string input("Hello World");
        std::string output("Hello World");

        auto result = TSConverter::ToString(input);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TSConverter (ru)
    //
    {
        std::locale _locale(locale_name);

        std::string input("Привет Мир");
        std::string output("Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TSConverter::ToString(input, _locale);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWConverter (eng)
    //
    {
        std::string input("Hello World");
        std::wstring output(L"Hello World");

        auto result = TWConverter::ToString(input);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWConverter (ru)
    //
    {
        std::locale _locale(locale_name);

        std::string input("Привет Мир");
        std::wstring output(L"Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TWConverter::ToString(input, _locale);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
TEST(TConverter, ToStringWCharPrt)
{
    //
    // TSConverter (eng)
    //
    {
        const wchar_t input[] = L"Hello World";
        std::string output("Hello World");

        {
            auto result = TSConverter::ToString(input);
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }

        {
            auto result = TSConverter::ToString(input, wcslen(input));
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }
    }
    //
    // TSConverter (ru)
    //
    {
        std::locale _locale(locale_name);

        const wchar_t input[] = L"Привет Мир";
        std::string output("Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        {
            auto result = TSConverter::ToString(input, _locale);
            T_VOID_AUTO_ENCODING_LOC(result, _locale);
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }

        {
            auto result = TSConverter::ToString(input, wcslen(input), _locale);
            T_VOID_AUTO_ENCODING_LOC(result, _locale);
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }
    }
    //
    // TWConverter (eng)
    //
    {
        const wchar_t input[] = L"Hello World";
        std::wstring output(L"Hello World");

        {
            auto result = TWConverter::ToString(input);
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }

        {
            auto result = TWConverter::ToString(input, wcslen(input));
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }
    }
    //
    // TWConverter (ru)
    //
    {
        std::locale _locale(locale_name);

        const wchar_t input[] = L"Привет Мир";
        std::wstring output(L"Привет Мир");
        
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        {
            auto result = TWConverter::ToString(input, _locale);
            T_VOID_AUTO_ENCODING_LOC(result, _locale);
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }

        {
            auto result = TWConverter::ToString(input, wcslen(input), _locale);
            T_VOID_AUTO_ENCODING_LOC(result, _locale);
            ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
            ASSERT_EQ(output, result);
        }
    }
}
// ---------------------------------------------------------------------------
TEST(TConverter, ToStringWString)
{
    //
    // TSConverter (eng)
    //
    {
        std::wstring input(L"Hello World");
        std::string output("Hello World");

        auto result = TSConverter::ToString(input);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TSConverter (ru)
    //
    {
        std::locale _locale(locale_name);

        std::wstring input(L"Привет Мир");
        std::string output("Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TSConverter::ToString(input, _locale);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWConverter (eng)
    //
    {
        std::wstring input(L"Hello World");
        std::wstring output(L"Hello World");

        auto result = TWConverter::ToString(input);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWConverter (ru)
    //
    {
        std::locale _locale(locale_name);

        std::wstring input(L"Привет Мир");
        std::wstring output(L"Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TWConverter::ToString(input, _locale);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
TEST(TConverter, ToStringChar)
{
    //
    // TSConverter (eng)
    //
    {
        char input = 'H';
        std::string output("H");

        auto result = TSConverter::ToString(input);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWConverter (eng)
    //
    {
        char input = 'H';
        std::wstring output(L"H");

        auto result = TWConverter::ToString(input);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
TEST(TConverter, ToStringWChar)
{
    //
    // TSConverter (eng)
    //
    {
        wchar_t input = L'H';
        std::string output("H");

        auto result = TSConverter::ToString(input);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWConverter (eng)
    //
    {
        wchar_t input = L'H';
        std::wstring output(L"H");

        auto result = TWConverter::ToString(input);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
TEST(TConverter, ToStringU16String)
{
    //
    // TSConverter (eng)
    //
    {
        std::u16string input(u"Hello World");
        std::string output("Hello World");

        auto result = TSConverter::ToString(input);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TSConverter (ru)
    //
    {
        std::locale _locale(locale_name);

        std::u16string input(u"Привет Мир");
        std::string output("Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TSConverter::ToString(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(result, _locale);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWConverter (eng)
    //
    {
        std::u16string input(u"Hello World");
        std::wstring output(L"Hello World");

        auto result = TWConverter::ToString(input);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWConverter (ru)
    //
    {
        std::locale _locale(locale_name);

        std::u16string input(u"Привет Мир");
        std::wstring output(L"Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TWConverter::ToString(input);
        T_VOID_AUTO_ENCODING_LOC(result, _locale);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
TEST(TConverter, ToU16StringString)
{
    //
    // TSConverter (eng)
    //
    {
        std::string input("Hello World");
        std::u16string output(u"Hello World");

        auto result = TSConverter::ToU16string(input);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWConverter (eng)
    //
    {
        std::wstring input(L"Hello World");
        std::u16string output(u"Hello World");

        auto result = TWConverter::ToU16string(input);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
TEST(TConverter, ToHexString)
{
    //
    // TSConverter
    //
    {
        int8_t input(std::numeric_limits<int8_t>::max());
        std::string output("0x7F");

        auto result = TSConverter::ToHexString(input, true, true);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        uint8_t input(std::numeric_limits<uint8_t>::max());
        std::string output("FF");

        auto result = TSConverter::ToHexString(input, false, true);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        int16_t input(std::numeric_limits<int16_t>::max());
        std::string output("7fff");

        auto result = TSConverter::ToHexString(input, false, false);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        uint16_t input(std::numeric_limits<uint16_t>::max());
        std::string output("ffff");

        auto result = TSConverter::ToHexString(input, false, false);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        int32_t input(std::numeric_limits<int32_t>::max());
        std::string output("0x7FFFFFFF");

        auto result = TSConverter::ToHexString(input, true, true);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        uint32_t input(std::numeric_limits<uint32_t>::max());
        std::string output("ffffffff");

        auto result = TSConverter::ToHexString(input, false, false);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        int64_t input(std::numeric_limits<int64_t>::max());
        std::string output("0x7FFFFFFFFFFFFFFF");

        auto result = TSConverter::ToHexString(input, true, true);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        uint64_t input(std::numeric_limits<uint64_t>::max());
        std::string output("FFFFFFFFFFFFFFFF");

        auto result = TSConverter::ToHexString(input, false, true);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWConverter
    //
    {
        int8_t input(std::numeric_limits<int8_t>::max());
        std::wstring output(L"0x7F");

        auto result = TWConverter::ToHexString(input, true, true);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        uint8_t input(std::numeric_limits<uint8_t>::max());
        std::wstring output(L"FF");

        auto result = TWConverter::ToHexString(input, false, true);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        int16_t input(std::numeric_limits<int16_t>::max());
        std::wstring output(L"7fff");

        auto result = TWConverter::ToHexString(input, false, false);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        uint16_t input(std::numeric_limits<uint16_t>::max());
        std::wstring output(L"ffff");

        auto result = TWConverter::ToHexString(input, false, false);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        int32_t input(std::numeric_limits<int32_t>::max());
        std::wstring output(L"0x7FFFFFFF");

        auto result = TWConverter::ToHexString(input, true, true);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        uint32_t input(std::numeric_limits<uint32_t>::max());
        std::wstring output(L"ffffffff");

        auto result = TWConverter::ToHexString(input, false, false);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        int64_t input(std::numeric_limits<int64_t>::max());
        std::wstring output(L"0x7FFFFFFFFFFFFFFF");

        auto result = TWConverter::ToHexString(input, true, true);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        uint64_t input(std::numeric_limits<uint64_t>::max());
        std::wstring output(L"FFFFFFFFFFFFFFFF");

        auto result = TWConverter::ToHexString(input, false, true);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
TEST(TConverter, FromString)
{
    //
    // TSConverter
    //
    {
        std::string input("-128");
        int8_t output(std::numeric_limits<int8_t>::min());

        auto result = TSConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::string input("255");
        uint8_t output(std::numeric_limits<uint8_t>::max());

        auto result = TSConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::string input("256");

        auto result = TSConverter::FromString<uint8_t>(input, 0);
        ASSERT_EQ(typeid(uint8_t), typeid(decltype(result)));
        ASSERT_EQ(uint8_t(0), result);
    }

    {
        std::string input("255");

        auto result = TSConverter::FromString<int8_t>(input, 0);
        ASSERT_EQ(typeid(int8_t), typeid(decltype(result)));
        ASSERT_EQ(int8_t(0), result);
    }

    {
        std::string input("127");

        auto result = TSConverter::FromString<int8_t>(input, 0);
        ASSERT_EQ(typeid(int8_t), typeid(decltype(result)));
        ASSERT_EQ(int8_t(127), result);
    }

    {
        std::string input("-255");

        auto result = TSConverter::FromString<int8_t>(input, 0);
        ASSERT_EQ(typeid(int8_t), typeid(decltype(result)));
        ASSERT_EQ(int8_t(0), result);
    }

    {
        std::string input("-128");

        auto result = TSConverter::FromString<int8_t>(input, 0);
        ASSERT_EQ(typeid(int8_t), typeid(decltype(result)));
        ASSERT_EQ(int8_t(-128), result);
    }

    {
        std::string input("-32768");
        int16_t output(std::numeric_limits<int16_t>::min());

        auto result = TSConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::string input("65535");
        uint16_t output(std::numeric_limits<uint16_t>::max());

        auto result = TSConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::string input("-2147483648");
        int32_t output(std::numeric_limits<int32_t>::min());

        auto result = TSConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::string input("4294967295");
        uint32_t output(std::numeric_limits<uint32_t>::max());

        auto result = TSConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::string input("-9223372036854775808");
        int64_t output(std::numeric_limits<int64_t>::min());

        auto result = TSConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::string input("18446744073709551615");
        uint64_t output(std::numeric_limits<uint64_t>::max());

        auto result = TSConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::string input("18446744073709551615");
        uint64_t output(std::numeric_limits<uint64_t>::max());

        auto result = TSConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::string input("1.175494351E-38");
        float output(std::numeric_limits<float>::min());

        auto result = TSConverter::FromString<decltype(output)>(input, 0.0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::string input("3,402823466E+38");
        float output(std::numeric_limits<float>::max());

        auto result = TSConverter::FromString<decltype(output)>(input, 0.0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::string input("2.2250738585072014E-308");
        double output(std::numeric_limits<double>::min());

        auto result = TSConverter::FromString<decltype(output)>(input, 0.0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::string input("1,7976931348623158E+308");
        double output(std::numeric_limits<double>::max());

        auto result = TSConverter::FromString<decltype(output)>(input, 0.0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWConverter
    //
    {
        std::wstring input(L"-128");
        int8_t output(std::numeric_limits<int8_t>::min());

        auto result = TWConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::wstring input(L"255");
        uint8_t output(std::numeric_limits<uint8_t>::max());

        auto result = TWConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::wstring input(L"-32768");
        int16_t output(std::numeric_limits<int16_t>::min());

        auto result = TWConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::wstring input(L"65535");
        uint16_t output(std::numeric_limits<uint16_t>::max());

        auto result = TWConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::wstring input(L"-2147483648");
        int32_t output(std::numeric_limits<int32_t>::min());

        auto result = TWConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::wstring input(L"4294967295");
        uint32_t output(std::numeric_limits<uint32_t>::max());

        auto result = TWConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::wstring input(L"-9223372036854775808");
        int64_t output(std::numeric_limits<int64_t>::min());

        auto result = TWConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::wstring input(L"18446744073709551615");
        uint64_t output(std::numeric_limits<uint64_t>::max());

        auto result = TWConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::wstring input(L"18446744073709551615");
        uint64_t output(std::numeric_limits<uint64_t>::max());

        auto result = TWConverter::FromString<decltype(output)>(input, 0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::wstring input(L"1.175494351E-38");
        float output(std::numeric_limits<float>::min());

        auto result = TWConverter::FromString<decltype(output)>(input, 0.0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::wstring input(L"3,402823466E+38");
        float output(std::numeric_limits<float>::max());

        auto result = TWConverter::FromString<decltype(output)>(input, 0.0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::wstring input(L"2.2250738585072014E-308");
        double output(std::numeric_limits<double>::min());

        auto result = TWConverter::FromString<decltype(output)>(input, 0.0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }

    {
        std::wstring input(L"1,7976931348623158E+308");
        double output(std::numeric_limits<double>::max());

        auto result = TWConverter::FromString<decltype(output)>(input, 0.0);
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
TEST(TConverter, EmptyString)
{
    //
    // TSConverter
    //
    {
        std::string output;
        auto result = TSConverter::EmptyString();
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWConverter
    //
    {
        std::wstring output;
        auto result = TWConverter::EmptyString();
        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
#pragma endregion
// ---------------------------------------------------------------------------
#pragma region TSFormater
TEST(TFormater, ReplaceAll)
{
    //
    // TSFormater (eng)
    //
    {
        std::string input = "Hello test_World!!!";
        std::string output("Hello World:)");

        TSFormater::ReplaceAll(input, "test_", "");
        auto result = TSFormater::ReplaceAll(input, "!!!", ":)");

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TSFormater (ru)
    //
    {
        std::locale _locale(locale_name);

        std::string input = "Привет тест_Мир!!!";
        std::string output("Привет Мир:)");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        TSFormater::ReplaceAll(input, AUTO_ENCODING_LOC(std::string, "тест_", _locale), "");
        auto result = TSFormater::ReplaceAll(input, "!!!", ":)");

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWFormater (eng)
    //
    {
        std::wstring input = L"Hello test_World!!!";
        std::wstring output(L"Hello World:)");

        TWFormater::ReplaceAll(input, L"test_", L"");
        auto result = TWFormater::ReplaceAll(input, L"!!!", L":)");

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWFormater (ru)
    //
    {
        std::locale _locale(locale_name);

        std::wstring input = L"Привет тест_Мир!!!";
        std::wstring output(L"Привет Мир:)");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        TWFormater::ReplaceAll(input, AUTO_ENCODING_LOC(std::wstring, L"тест_", _locale), L"");
        auto result = TWFormater::ReplaceAll(input, L"!!!", L":)");

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
TEST(TFormater, UpperFirst)
{
    //
    // TSFormater (eng)
    //
    {
        std::string input = "hello World";
        std::string output("Hello World");

        auto result = TSFormater::UpperFirst(input);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TSFormater (ru)
    //
    {
        std::locale _locale(locale_name);

        std::string input = "привет Мир";
        std::string output("Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TSFormater::UpperFirst(input, _locale);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWFormater (eng)
    //
    {
        std::wstring input = L"hello World";
        std::wstring output(L"Hello World");

        auto result = TWFormater::UpperFirst(input);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWFormater (ru)
    //
    {
        std::locale _locale(locale_name);

        std::wstring input = L"привет Мир";
        std::wstring output(L"Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TWFormater::UpperFirst(input, _locale);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
TEST(TFormater, UpperCase)
{
    //
    // TSFormater (eng)
    //
    {
        std::string input = "Hello World";
        std::string output("HELLO WORLD");

        auto result = TSFormater::UpperCase(input);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TSFormater (ru)
    //
    {
        std::locale _locale(locale_name);

        std::string input = "Привет Мир";
        std::string output("ПРИВЕТ МИР");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TSFormater::UpperCase(input, _locale);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWFormater (eng)
    //
    {
        std::wstring input = L"Hello World";
        std::wstring output(L"HELLO WORLD");

        auto result = TWFormater::UpperCase(input);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWFormater (ru)
    //
    {
        std::locale _locale(locale_name);

        std::wstring input = L"Привет Мир";
        std::wstring output(L"ПРИВЕТ МИР");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TWFormater::UpperCase(input, _locale);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
TEST(TFormater, LowerCase)
{
    //
    // TSFormater (eng)
    //
    {
        std::string input = "HeLLo WorLd";
        std::string output("hello world");

        auto result = TSFormater::LowerCase(input);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TSFormater (ru)
    //
    {
        std::locale _locale(locale_name);

        std::string input = "ПрИВеТ МиР";
        std::string output("привет мир");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TSFormater::LowerCase(input, _locale);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWFormater (eng)
    //
    {
        std::wstring input = L"HeLLo WorLd";
        std::wstring output(L"hello world");

        auto result = TWFormater::LowerCase(input);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWFormater (ru)
    //
    {
        std::locale _locale(locale_name);

        std::wstring input = L"ПрИВеТ МиР";
        std::wstring output(L"привет мир");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TWFormater::LowerCase(input, _locale);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
TEST(TFormater, Format)
{
    //
    // TSFormater (eng)
    //
    {
        std::string output("Server version: 10.4.0.584 LMZ inc 2021");

        auto result = TSFormater::Format("{0} version: {2}.{1}.{3}.{4} {5} inc {6}",
                        L"Server", 4, 10, 0, 584, std::string("LMZ"), 2021);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TSFormater (ru)
    //
    {
        std::locale _locale(locale_name);

        std::string output("Сервер version: 10.4.0.584 ЛМЗ inc 2021");

        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TSFormater::Format("{0} version: {2}.{1}.{3}.{4} {5} inc {6}", _locale,
                         AUTO_ENCODING_LOC(std::wstring, L"Сервер", _locale), 4, 10, 0, 584, AUTO_ENCODING_LOC(std::string, "ЛМЗ", _locale), 2021);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWFormater (eng)
    //
    {
        std::wstring output(L"Server version: 10.4.0.584 LMZ inc 2021");

        auto result = TWFormater::Format(L"{0} version: {2}.{1}.{3}.{4} {5} inc {6}",
                        L"Server", 4, 10, 0, 584, std::string("LMZ"), 2021);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWFormater (ru)
    //
    {
        std::locale _locale(locale_name);

        std::wstring output(L"Сервер version: 10.4.0.584 ЛМЗ inc 2021");

        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TWFormater::Format(L"{0} version: {2}.{1}.{3}.{4} {5} inc {6}", _locale,
                        AUTO_ENCODING_LOC(std::wstring, L"Сервер", _locale), 4, 10, 0, 584, AUTO_ENCODING_LOC(std::string, "ЛМЗ", _locale), 2021);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
TEST(TSFormater, Concatenate)
{
    //
    // TSFormater (eng)
    //
    {
        std::string output("Server version: 10.4.0.584 LMZ inc 2021");

        auto result = TSFormater::Concatenate(std::wstring(L"Server version: "), 10, ".", 4, ".", 0, ".", 584, std::string(" LMZ inc "), 2021);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TSFormater (ru)
    //
    {
        std::locale _locale(locale_name);

        std::string output("Сервер version: 10.4.0.584 ЛМЗ inc 2021");

        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TSFormater::Concatenate(_locale,
            AUTO_ENCODING_LOC(std::wstring, L"Сервер ", _locale),
            "version: ", 10, ".", 4, ".", 0, ".", 584,
            AUTO_ENCODING_LOC(std::string, " ЛМЗ ", _locale),
            "inc ", 2021);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWFormater (eng)
    //
    {
        std::wstring output(L"Server version: 10.4.0.584 LMZ inc 2021");

        auto result = TWFormater::Concatenate(std::wstring(L"Server version: "), 10, ".", 4, ".", 0, ".", 584, std::string(" LMZ inc "), 2021);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWFormater (ru)
    //
    {
        std::locale _locale(locale_name);

        std::wstring output(L"Сервер version: 10.4.0.584 ЛМЗ inc 2021");

        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TWFormater::Concatenate(_locale,
            AUTO_ENCODING_LOC(std::wstring, L"Сервер ", _locale),
            "version: ", 10, ".", 4, ".", 0, ".", 584,
            AUTO_ENCODING_LOC(std::string, " ЛМЗ ", _locale),
            "inc ", 2021);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
#pragma endregion
// ---------------------------------------------------------------------------
#pragma region TExtension
TEST(TExtension, Compare01)
{
    //
    // TSExtension (eng)
    //
    {
        std::string first("Hello World");
        std::string second("Hello World");
        std::string third("HeLLo WoRld");

        ASSERT_TRUE(TSExtension::Compare(first, second));
        ASSERT_FALSE(TSExtension::Compare(first, third));
        ASSERT_TRUE(TSExtension::Compare(first, third, true));
    }
    //
    // TSExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::string first("Привет Мир");
        std::string second("Привет Мир");
        std::string third("ПрИВет МИР");

        T_VOID_AUTO_ENCODING_LOC(first, _locale);
        T_VOID_AUTO_ENCODING_LOC(second, _locale);
        T_VOID_AUTO_ENCODING_LOC(third, _locale);

        ASSERT_TRUE(TSExtension::Compare(first, second, false, _locale));
        ASSERT_FALSE(TSExtension::Compare(first, third, false, _locale));
        ASSERT_TRUE(TSExtension::Compare(first, third, true, _locale));
    }
    //
    // TWExtension (eng)
    //
    {
        std::wstring first(L"Hello World");
        std::wstring second(L"Hello World");
        std::wstring third(L"HeLLo WoRld");

        ASSERT_TRUE(TWExtension::Compare(first, second));
        ASSERT_FALSE(TWExtension::Compare(first, third));
        ASSERT_TRUE(TWExtension::Compare(first, third, true));
    }
    //
    // TWExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::wstring first(L"Привет Мир");
        std::wstring second(L"Привет Мир");
        std::wstring third(L"ПрИВет МИР");

        T_VOID_AUTO_ENCODING_LOC(first, _locale);
        T_VOID_AUTO_ENCODING_LOC(second, _locale);
        T_VOID_AUTO_ENCODING_LOC(third, _locale);

        ASSERT_TRUE(TWExtension::Compare(first, second, false, _locale));
        ASSERT_FALSE(TWExtension::Compare(first, third, false, _locale));
        ASSERT_TRUE(TWExtension::Compare(first, third, true, _locale));
    }
}
// ---------------------------------------------------------------------------
TEST(TExtension, Compare02)
{
    //
    // TSExtension (eng)
    //
    {
        std::vector<std::string> _vector {"Hello World", "Extension", "Play Music"};
        std::string first("Hello World");
        std::string second("HeLLo WoRld");

        ASSERT_TRUE(TSExtension::Compare(first, _vector));
        ASSERT_FALSE(TSExtension::Compare(second, _vector));
        ASSERT_TRUE(TSExtension::Compare(second, _vector, true));
    }
    //
    // TSExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::vector<std::string> _vector {"Привет мир", "Тестирование", "Маленький принц"};
        std::string first("Тестирование");
        std::string second("МАленькИй прИнц");

        std::for_each(std::begin(_vector), std::end(_vector), [&](std::string& value) { value = AUTO_ENCODING_LOC(std::string, value, _locale); });
        T_VOID_AUTO_ENCODING_LOC(first, _locale);
        T_VOID_AUTO_ENCODING_LOC(second, _locale);

        ASSERT_TRUE(TSExtension::Compare(first, _vector, false, _locale));
        ASSERT_FALSE(TSExtension::Compare(second, _vector, false, _locale));
        ASSERT_TRUE(TSExtension::Compare(second, _vector, true, _locale));
    }
    //
    // TWExtension (eng)
    //
    {
        std::vector<std::wstring> _vector {L"Hello World", L"Extension", L"Play Music"};
        std::wstring first(L"Hello World");
        std::wstring second(L"HeLLo WoRld");

        ASSERT_TRUE(TWExtension::Compare(first, _vector));
        ASSERT_FALSE(TWExtension::Compare(second, _vector));
        ASSERT_TRUE(TWExtension::Compare(second, _vector, true));
    }
    //
    // TSExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::vector<std::wstring> _vector {L"Привет мир", L"Тестирование", L"Маленький принц"};
        std::wstring first(L"Тестирование");
        std::wstring second(L"МАленькИй прИнц");

        std::for_each(std::begin(_vector), std::end(_vector), [&](std::wstring& value) { value = AUTO_ENCODING_LOC(std::wstring, value, _locale); });
        T_VOID_AUTO_ENCODING_LOC(first, _locale);
        T_VOID_AUTO_ENCODING_LOC(second, _locale);

        ASSERT_TRUE(TWExtension::Compare(first, _vector, false, _locale));
        ASSERT_FALSE(TWExtension::Compare(second, _vector, false, _locale));
        ASSERT_TRUE(TWExtension::Compare(second, _vector, true, _locale));
    }
}
// ---------------------------------------------------------------------------
TEST(TExtension, Compare03)
{
    //
    // TSExtension (eng)
    //
    {
        enum class TTestEnum { THelloWorld, TExtension, TPlayMusic };

        std::vector<std::string> _vector_in {"Hello World", "Extension", "Play Music"};
        std::vector<TTestEnum> _vector_out {TTestEnum::THelloWorld, TTestEnum::TExtension, TTestEnum::TPlayMusic};

        std::string first("Extension");
        std::string second("ExtEnSiOn");

        ASSERT_EQ(TSExtension::Compare<TTestEnum>(first, _vector_in, _vector_out, TTestEnum::THelloWorld), TTestEnum::TExtension);
        ASSERT_EQ(TSExtension::Compare<TTestEnum>(second, _vector_in, _vector_out, TTestEnum::THelloWorld), TTestEnum::THelloWorld);
        ASSERT_EQ(TSExtension::Compare<TTestEnum>(second, _vector_in, _vector_out, TTestEnum::THelloWorld, true), TTestEnum::TExtension);
    }
    //
    // TSExtension (ru)
    //
    {
        enum class TTestEnum { THelloWorld, TExtension, TPlayMusic };

        std::locale _locale(locale_name);

        std::vector<std::string> _vector_in {"Привет Мир", "Тестирование", "Война и Мир"};
        std::vector<TTestEnum> _vector_out {TTestEnum::THelloWorld, TTestEnum::TExtension, TTestEnum::TPlayMusic};

        std::string first("Тестирование");
        std::string second("ТестИровАние");

        std::for_each(std::begin(_vector_in), std::end(_vector_in), [&](std::string& value) { value = AUTO_ENCODING_LOC(std::string, value, _locale); });
        T_VOID_AUTO_ENCODING_LOC(first, _locale);
        T_VOID_AUTO_ENCODING_LOC(second, _locale);

        ASSERT_EQ(TSExtension::Compare<TTestEnum>(first, _vector_in, _vector_out, TTestEnum::THelloWorld, false, _locale), TTestEnum::TExtension);
        ASSERT_EQ(TSExtension::Compare<TTestEnum>(second, _vector_in, _vector_out, TTestEnum::THelloWorld, false, _locale), TTestEnum::THelloWorld);
        ASSERT_EQ(TSExtension::Compare<TTestEnum>(second, _vector_in, _vector_out, TTestEnum::THelloWorld, true, _locale), TTestEnum::TExtension);
    }
    //
    // TWExtension (eng)
    //
    {
        enum class TTestEnum { THelloWorld, TExtension, TPlayMusic };

        std::vector<std::wstring> _vector_in {L"Hello World", L"Extension", L"Play Music"};
        std::vector<TTestEnum> _vector_out {TTestEnum::THelloWorld, TTestEnum::TExtension, TTestEnum::TPlayMusic};

        std::wstring first(L"Extension");
        std::wstring second(L"ExTenSion");

        ASSERT_EQ(TWExtension::Compare<TTestEnum>(first, _vector_in, _vector_out, TTestEnum::THelloWorld), TTestEnum::TExtension);
        ASSERT_EQ(TWExtension::Compare<TTestEnum>(second, _vector_in, _vector_out, TTestEnum::THelloWorld), TTestEnum::THelloWorld);
        ASSERT_EQ(TWExtension::Compare<TTestEnum>(second, _vector_in, _vector_out, TTestEnum::THelloWorld, true), TTestEnum::TExtension);
    }
    //
    // TWExtension (ru)
    //
    {
        enum class TTestEnum { THelloWorld, TExtension, TPlayMusic };

        std::locale _locale(locale_name);

        std::vector<std::wstring> _vector_in {L"Привет Мир", L"Тестирование", L"Война и Мир"};
        std::vector<TTestEnum> _vector_out {TTestEnum::THelloWorld, TTestEnum::TExtension, TTestEnum::TPlayMusic};

        std::wstring first(L"Тестирование");
        std::wstring second(L"ТестИровАние");

        std::for_each(std::begin(_vector_in), std::end(_vector_in), [&](std::wstring& value) { value = AUTO_ENCODING_LOC(std::wstring, value, _locale); });
        T_VOID_AUTO_ENCODING_LOC(first, _locale);
        T_VOID_AUTO_ENCODING_LOC(second, _locale);

        ASSERT_EQ(TWExtension::Compare<TTestEnum>(first, _vector_in, _vector_out, TTestEnum::THelloWorld, false, _locale), TTestEnum::TExtension);
        ASSERT_EQ(TWExtension::Compare<TTestEnum>(second, _vector_in, _vector_out, TTestEnum::THelloWorld, false, _locale), TTestEnum::THelloWorld);
        ASSERT_EQ(TWExtension::Compare<TTestEnum>(second, _vector_in, _vector_out, TTestEnum::THelloWorld, true, _locale), TTestEnum::TExtension);
    }
}
// ---------------------------------------------------------------------------
TEST(TExtension, Compare04)
{
    //
    // TSExtension (eng)
    //
    {
        enum class TTestEnum { None, THelloWorld, TExtension, TPlayMusic };

        std::vector<TTestEnum> _vector_in { TTestEnum::THelloWorld, TTestEnum::TExtension, TTestEnum::TPlayMusic };
        std::vector<std::string> _vector_out { "Hello World", "Extension", "Play Music" };
        std::string def(":)");

        ASSERT_EQ(TSExtension::Compare(TTestEnum::TExtension, _vector_in, _vector_out, def), _vector_out.at(1));
        ASSERT_EQ(TSExtension::Compare(TTestEnum::None, _vector_in, _vector_out, def), def);
    }
    //
    // TSExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        enum class TTestEnum { None, THelloWorld, TExtension, TPlayMusic };

        std::vector<TTestEnum> _vector_in { TTestEnum::THelloWorld, TTestEnum::TExtension, TTestEnum::TPlayMusic };
        std::vector<std::string> _vector_out { "Привет Мир", "Тестирование", "Война и Мир" };
        std::string def(":)");

        std::for_each(std::begin(_vector_out), std::end(_vector_out), [&](std::string& value) { value = AUTO_ENCODING_LOC(std::string, value, _locale); });

        ASSERT_EQ(TSExtension::Compare(TTestEnum::TExtension, _vector_in, _vector_out, def), _vector_out.at(1));
        ASSERT_EQ(TSExtension::Compare(TTestEnum::None, _vector_in, _vector_out, def), def);
    }
    //
    // TWExtension (eng)
    //
    {
        enum class TTestEnum { None, THelloWorld, TExtension, TPlayMusic };

        std::vector<TTestEnum> _vector_in { TTestEnum::THelloWorld, TTestEnum::TExtension, TTestEnum::TPlayMusic };
        std::vector<std::wstring> _vector_out { L"Hello World", L"Extension", L"Play Music" };
        std::wstring def(L":)");

        ASSERT_EQ(TWExtension::Compare(TTestEnum::TExtension, _vector_in, _vector_out, def), _vector_out.at(1));
        ASSERT_EQ(TWExtension::Compare(TTestEnum::None, _vector_in, _vector_out, def), def);
    }
    //
    // TWExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        enum class TTestEnum { None, THelloWorld, TExtension, TPlayMusic };

        std::vector<TTestEnum> _vector_in { TTestEnum::THelloWorld, TTestEnum::TExtension, TTestEnum::TPlayMusic };
        std::vector<std::wstring> _vector_out { L"Привет Мир", L"Тестирование", L"Война и Мир" };
        std::wstring def(L":)");

        std::for_each(std::begin(_vector_out), std::end(_vector_out), [&](std::wstring& value) { value = AUTO_ENCODING_LOC(std::wstring, value, _locale); });

        ASSERT_EQ(TWExtension::Compare(TTestEnum::TExtension, _vector_in, _vector_out, def), _vector_out.at(1));
        ASSERT_EQ(TWExtension::Compare(TTestEnum::None, _vector_in, _vector_out, def), def);
    }
}
// ---------------------------------------------------------------------------
TEST(TExtension, Split)
{
    //
    // TSExtension (eng)
    //
    {
        std::string input("First;Second;Third;");
        std::vector<std::string> output {"First", "Second", "Third"};

        auto result = TSExtension::Split(input, ';');
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(std::size(result), std::size(output));

        for (std::size_t i(0); i < std::size(result); i++)
        {
            ASSERT_EQ(result.at(i), output.at(i));
        }
    }
    //
    // TSExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::string input("Первый;Второй;Третий");
        std::vector<std::string> output {"Первый", "Второй", "Третий"};

        T_VOID_AUTO_ENCODING_LOC(input, _locale);

        auto result = TSExtension::Split(input, ';');
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(std::size(result), std::size(output));

        for (std::size_t i(0); i < std::size(result); i++)
        {
            output[i] = AUTO_ENCODING_LOC(std::string, output.at(i), _locale);

            ASSERT_EQ(result.at(i), output.at(i));
        }
    }
    //
    // TWExtension (eng)
    //
    {
        std::wstring input(L"First!Second!Third!");
        std::vector<std::wstring> output {L"First", L"Second", L"Third"};

        auto result = TWExtension::Split(input, L'!');
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(std::size(result), std::size(output));

        for (std::size_t i(0); i < std::size(result); i++)
        {
            ASSERT_EQ(result.at(i), output.at(i));
        }
    }
    //
    // TWExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::wstring input(L"Первый#Второй#Третий");
        std::vector<std::wstring> output {L"Первый", L"Второй", L"Третий"};

        T_VOID_AUTO_ENCODING_LOC(input, _locale);

        auto result = TWExtension::Split(input, L'#');
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(std::size(result), std::size(output));

        for (std::size_t i(0); i < std::size(result); i++)
        {
            output[i] = AUTO_ENCODING_LOC(std::wstring, output.at(i), _locale);

            ASSERT_EQ(result.at(i), output.at(i));
        }
    }
}
// ---------------------------------------------------------------------------
TEST(TExtension, UnSplit01)
{
    //
    // TSExtension (eng)
    //
    {
        std::vector<std::string> input {"First", "Second", "Third" };
        std::string output("First;Second;Third");

        auto result = TSExtension::UnSplit(input, ';');

        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::vector<std::string> input {"Первый", "Второй", "Третий" };
        std::string output("Первый#Второй#Третий");

        std::for_each(std::begin(input), std::end(input), [&](std::string& value) { value = AUTO_ENCODING_LOC(std::string, value, _locale); });
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TSExtension::UnSplit(input, '#');

        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension (eng)
    //
    {
        std::vector<std::wstring> input {L"First", L"Second", L"Third" };
        std::wstring output(L"First;Second;Third");

        auto result = TWExtension::UnSplit(input, L';');

        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::vector<std::wstring> input {L"Первый", L"Второй", L"Третий" };
        std::wstring output(L"Первый#Второй#Третий");

        std::for_each(std::begin(input), std::end(input), [&](std::wstring& value) { value = AUTO_ENCODING_LOC(std::wstring, value, _locale); });
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TWExtension::UnSplit(input, L'#');

        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
}
// ---------------------------------------------------------------------------
TEST(TExtension, UnSplit02)
{
    //
    // TSExtension (eng)
    //
    {
        std::vector<std::string> input {"First", "Second", "Third" };
        std::string output("First->Second->Third");

        auto result = TSExtension::UnSplit(input, "->");

        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::vector<std::string> input {"Первый", "Второй", "Третий" };
        std::string output("Первый---Второй---Третий");

        std::for_each(std::begin(input), std::end(input), [&](std::string& value) { value = AUTO_ENCODING_LOC(std::string, value, _locale); });
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TSExtension::UnSplit(input, "---");

        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension (eng)
    //
    {
        std::vector<std::wstring> input {L"First", L"Second", L"Third" };
        std::wstring output(L"First->Second->Third");

        auto result = TWExtension::UnSplit(input, L"->");

        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::vector<std::wstring> input {L"Первый", L"Второй", L"Третий" };
        std::wstring output(L"Первый--|--Второй--|--Третий");

        std::for_each(std::begin(input), std::end(input), [&](std::wstring& value) { value = AUTO_ENCODING_LOC(std::wstring, value, _locale); });
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TWExtension::UnSplit(input, L"--|--");

        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
}
// ---------------------------------------------------------------------------
TEST(TExtension, TUnSplit01)
{
    std::vector<double> temp_double { 0.23324, 98.34534, 654.2751, 84.287 };
    std::vector<uint32_t> temp_uint32 { 10, 98, 654, 84 };
    //
    // TSExtension
    //
    {
        std::string output("0.23324;98.34534;654.2751;84.287");

        std::string result = TSExtension::TUnSplit<double>(temp_double, ';', std::locale(), 7);

        ASSERT_EQ(result, output);
    }
    {
        std::string output("10-98-654-84");

        std::string result = TSExtension::TUnSplit<uint32_t>(temp_uint32, '-');

        ASSERT_EQ(result, output);
    }
    //
    // TWExtension
    //
    {
        std::wstring output(L"0.23324;98.34534;654.2751;84.287");

        std::wstring result = TWExtension::TUnSplit<double>(temp_double, L';', std::locale(), 7);

        ASSERT_EQ(result, output);
    }
    {
        std::wstring output(L"10-98-654-84");

        std::wstring result = TWExtension::TUnSplit<uint32_t>(temp_uint32, L'-');

        ASSERT_EQ(result, output);
    }
}
// ---------------------------------------------------------------------------
TEST(TExtension, TUnSplit02)
{
    std::vector<double> temp_double { 0.23324, 98.34534, 654.2751, 84.287 };
    std::vector<uint32_t> temp_uint32 { 10, 98, 654, 84 };
    //
    // TSExtension
    //
    {
        std::string output("0.23324->98.34534->654.2751->84.287");

        std::string result = TSExtension::TUnSplit<double>(temp_double, "->", std::locale(), 7);

        ASSERT_EQ(result, output);
    }
    {
        std::string output("10--98--654--84");

        std::string result = TSExtension::TUnSplit<uint32_t>(temp_uint32, "--");

        ASSERT_EQ(result, output);
    }
    //
    // TWExtension
    //
    {
        std::wstring output(L"0.23324->98.34534->654.2751->84.287");

        std::wstring result = TWExtension::TUnSplit<double>(temp_double, L"->", std::locale(), 7);

        ASSERT_EQ(result, output);
    }
    {
        std::wstring output(L"10--98--654--84");

        std::wstring result = TWExtension::TUnSplit<uint32_t>(temp_uint32, L"--");

        ASSERT_EQ(result, output);
    }
}
// ---------------------------------------------------------------------------
TEST(TExtension, Trim)
{
    //
    // TSExtension (eng)
    //
    {
        std::string input("Hello World");
        std::string output("Hello World");
        auto result = TSExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension (eng)
    //
    {
        std::string input("\t \r \n Hello World \r \n \t");
        std::string output("Hello World");

        auto result = TSExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension (eng)
    //
    {
        std::string input("Hello World \r \n \t");
        std::string output("Hello World");

        auto result = TSExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension (eng)
    //
    {
        std::string input("\t \r \n Hello World");
        std::string output("Hello World");

        auto result = TSExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::string input("Привет Мир");
        std::string output("Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TSExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::string input("\t \r \n Привет Мир \r \n \t");
        std::string output("Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TSExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::string input("\t \r \n Привет Мир \r \n \t");
        std::string output("Привет Мир");

        auto result = TSExtension::Trim(input);

        T_VOID_AUTO_ENCODING_LOC(result, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension
    //
    {
        std::string input("   ");
        std::string output("");

        auto result = TSExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension
    //
    {
        std::string input("\t\t\t\t");
        std::string output("");

        auto result = TSExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension
    //
    {
        std::string input("\r\r\r\r");
        std::string output("");

        auto result = TSExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension
    //
    {
        std::string input("\n\n\n\n");
        std::string output("");

        auto result = TSExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension
    //
    {
        std::string input("  \t   \r   \n   ");
        std::string output("");

        auto result = TSExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension
    //
    {
        std::string input(" ");
        std::string output("");

        auto result = TSExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension
    //
    {
        std::string input("");
        std::string output("");

        auto result = TSExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension (eng)
    //
    {
        std::wstring input(L"Hello World");
        std::wstring output(L"Hello World");
        auto result = TWExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension (eng)
    //
    {
        std::wstring input(L"\t \r \n Hello World \r \n \t");
        std::wstring output(L"Hello World");

        auto result = TWExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension (eng)
    //
    {
        std::wstring input(L"\t \r \n Hello World");
        std::wstring output(L"Hello World");

        auto result = TWExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension (eng)
    //
    {
        std::wstring input(L"Hello World \r \n \t");
        std::wstring output(L"Hello World");

        auto result = TWExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::wstring input(L"Привет Мир");
        std::wstring output(L"Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TWExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::wstring input(L"\t \r \n Привет Мир \r \n \t");
        std::wstring output(L"Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        auto result = TWExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::wstring input(L"\t \r \n Привет Мир \r \n \t");
        std::wstring output(L"Привет Мир");

        auto result = TWExtension::Trim(input);

        T_VOID_AUTO_ENCODING_LOC(result, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension
    //
    {
        std::wstring input(L"   ");
        std::wstring output(L"");

        auto result = TWExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension
    //
    {
        std::wstring input(L"\t\t\t\t");
        std::wstring output(L"");

        auto result = TWExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension
    //
    {
        std::wstring input(L"\r\r\r\r");
        std::wstring output(L"");

        auto result = TWExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension
    //
    {
        std::wstring input(L"\n\n\n\n");
        std::wstring output(L"");

        auto result = TWExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension
    //
    {
        std::wstring input(L"  \t   \r   \n   ");
        std::wstring output(L"");

        auto result = TWExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TWExtension
    //
    {
        std::wstring input(L" ");
        std::wstring output(L"");

        auto result = TWExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
    //
    // TSExtension
    //
    {
        std::wstring input(L"");
        std::wstring output(L"");

        auto result = TWExtension::Trim(input);
        ASSERT_EQ(typeid(result), typeid(output));
        ASSERT_EQ(result, output);
    }
}
// ---------------------------------------------------------------------------
TEST(TExtension, VoidTrim)
{
    //
    // TSExtension (eng)
    //
    {
        std::string input("KKKHello WorldKKK");
        std::string output("Hello World");

        TSExtension::VoidTrim(input, "K");

        ASSERT_EQ(typeid(input), typeid(output));
        ASSERT_EQ(input, output);
    }
    //
    // TSExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::string input("###Привет Мир###");
        std::string output("Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        TSExtension::VoidTrim(input, "#");

        ASSERT_EQ(typeid(input), typeid(output));
        ASSERT_EQ(input, output);
    }
    //
    // TSExtension
    //
    {
        std::string input("\"\"");
        std::string output("");

        TSExtension::VoidTrim(input, "\"");

        ASSERT_EQ(typeid(input), typeid(output));
        ASSERT_EQ(input, output);
    }
    //
    // TWExtension (eng)
    //
    {
        std::wstring input(L"KKKHello WorldKKK");
        std::wstring output(L"Hello World");

        TWExtension::VoidTrim(input, L"K");

        ASSERT_EQ(typeid(input), typeid(output));
        ASSERT_EQ(input, output);
    }
    //
    // TWExtension (ru)
    //
    {
        std::locale _locale(locale_name);

        std::wstring input(L"!!!Привет Мир!!!");
        std::wstring output(L"Привет Мир");

        T_VOID_AUTO_ENCODING_LOC(input, _locale);
        T_VOID_AUTO_ENCODING_LOC(output, _locale);

        TWExtension::VoidTrim(input, L"!");

        ASSERT_EQ(typeid(input), typeid(output));
        ASSERT_EQ(input, output);
    }
    //
    // TWExtension
    //
    {
        std::wstring input(L"\"\"");
        std::wstring output(L"");

        TWExtension::VoidTrim(input, L"\"");

        ASSERT_EQ(typeid(input), typeid(output));
        ASSERT_EQ(input, output);
    }
}
// ---------------------------------------------------------------------------
TEST(TExtension, IsIP)
{
    //
    // TSExtension
    //
    {
        std::string ip_01("192.168.0.1");
        std::string ip_02("192.168.0000.1");
        std::string ip_03("192.168.1");
        std::string ip_04("255.255.255.255");

        ASSERT_TRUE(TSExtension::IsIP(ip_01));
        ASSERT_FALSE(TSExtension::IsIP(ip_02));
        ASSERT_FALSE(TSExtension::IsIP(ip_03));
        ASSERT_TRUE(TSExtension::IsIP(ip_04));
    }
    //
    // TWExtension
    //
    {
        std::wstring ip_01(L"192.168.0.1");
        std::wstring ip_02(L"192.168.0000.1");
        std::wstring ip_03(L"192.168.1");
        std::wstring ip_04(L"255.255.255.255");

        ASSERT_TRUE(TWExtension::IsIP(ip_01));
        ASSERT_FALSE(TWExtension::IsIP(ip_02));
        ASSERT_FALSE(TWExtension::IsIP(ip_03));
        ASSERT_TRUE(TWExtension::IsIP(ip_04));
    }
}
// ---------------------------------------------------------------------------
TEST(TExtension, IpToMask32)
{
    //
    // TSExtension
    //
    {
        std::string ip_01("192.168.0.1");
        std::string ip_02("10.2.52.1");
        std::string ip_03("255.255.255.255");

        uint32_t mask_01(0xC0A80001);
        uint32_t mask_02(0x0A023401);
        uint32_t mask_03(0xFFFFFFFF);

        ASSERT_EQ(TSExtension::IpToMask32(ip_01), mask_01);
        ASSERT_EQ(TSExtension::IpToMask32(ip_02), mask_02);
        ASSERT_EQ(TSExtension::IpToMask32(ip_03), mask_03);
    }
    //
    // TWExtension
    //
    {
        std::wstring ip_01(L"192.168.0.1");
        std::wstring ip_02(L"10.2.52.1");
        std::wstring ip_03(L"255.255.255.255");

        uint32_t mask_01(0xC0A80001);
        uint32_t mask_02(0x0A023401);
        uint32_t mask_03(0xFFFFFFFF);

        ASSERT_EQ(TWExtension::IpToMask32(ip_01), mask_01);
        ASSERT_EQ(TWExtension::IpToMask32(ip_02), mask_02);
        ASSERT_EQ(TWExtension::IpToMask32(ip_03), mask_03);
    }
}
#pragma endregion
// ---------------------------------------------------------------------------
#pragma region TEncoding
TEST(TEncoding, Utf8ToCp1251)
{
    //
    // TSEncoding (eng)
    //
    {
        std::string utf8("Hello World");
        char cp1251[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x00};

        auto result = TSEncoding::Utf8ToCp1251(utf8);

        ASSERT_STREQ(result.c_str(), cp1251);
    }
    //
    // TSEncoding (ru)
    //
    {
        std::string utf8("Привет Мир");
        char cp1251[] = {static_cast<char>(0xCF),
                    static_cast<char>(0xF0),
                    static_cast<char>(0xE8),
                    static_cast<char>(0xE2),
                    static_cast<char>(0xE5),
                    static_cast<char>(0xF2),
                    static_cast<char>(0x20),
                    static_cast<char>(0xCC),
                    static_cast<char>(0xE8),
                    static_cast<char>(0xF0),
                    static_cast<char>(0x00)};


        auto result = TSEncoding::Utf8ToCp1251(utf8, std::locale(locale_name));

        ASSERT_STREQ(result.c_str(), cp1251);
    }
    //
    // TWEncoding (eng)
    //
    {
        std::wstring utf8(L"Hello World");
        wchar_t cp1251[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x00};

        auto result = TWEncoding::Utf8ToCp1251(utf8);

        ASSERT_STREQ(result.c_str(), cp1251);
    }
    //
    // TWEncoding (ru)
    //
    #ifdef WINDOWS
    {
        std::wstring utf8(L"Привет Мир");
        wchar_t cp1251[] = { 1055, 1088, 1080, 1074, 1077, 1090, 32, 1052, 1080, 1088, 0 };

        auto result = TWEncoding::Utf8ToCp1251(utf8, std::locale(locale_name));

        ASSERT_STREQ(result.c_str(), cp1251);
    }
    #endif
}
// ---------------------------------------------------------------------------
TEST(TEncoding, Cp1251ToUtf8)
{
    //
    // TSEncoding (eng)
    //
    {
        char _cp1251[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x00};

        std::string cp1251(_cp1251, strlen(_cp1251));

        std::string utf8("Hello World");

        auto result = TSEncoding::Cp1251ToUtf8(cp1251);

        ASSERT_EQ(typeid(result), typeid(utf8));
        ASSERT_EQ(result, utf8);
    }
    //
    // TSEncoding (ru)
    //
    {
        char _cp1251[] = {static_cast<char>(0xCF),
            static_cast<char>(0xF0),
            static_cast<char>(0xE8),
            static_cast<char>(0xE2),
            static_cast<char>(0xE5),
            static_cast<char>(0xF2),
            static_cast<char>(0x20),
            static_cast<char>(0xCC),
            static_cast<char>(0xE8),
            static_cast<char>(0xF0),
            static_cast<char>(0x00)};


        std::string cp1251(_cp1251, strlen(_cp1251));

        std::string utf8("Привет Мир");

        auto result = TSEncoding::Cp1251ToUtf8(cp1251, std::locale(locale_name));

        ASSERT_EQ(typeid(result), typeid(utf8));
        ASSERT_EQ(result, utf8);
    }
    //
    // TWEncoding (eng)
    //
    {
        wchar_t _cp1251[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x00};

        std::wstring cp1251(_cp1251, wcslen(_cp1251));

        std::wstring utf8(L"Hello World");

        auto result = TWEncoding::Cp1251ToUtf8(cp1251);

        ASSERT_EQ(typeid(result), typeid(utf8));
        ASSERT_EQ(result, utf8);
    }
    //
    // TWEncoding (ru)
    //
    #ifdef WINDOWS
    {
        wchar_t _cp1251[] = { 1055, 1088, 1080, 1074, 1077, 1090, 32, 1052, 1080, 1088, 0 };

        std::wstring cp1251(_cp1251, wcslen(_cp1251));

        std::wstring utf8(L"Привет Мир");

        auto result = TWEncoding::Cp1251ToUtf8(cp1251, std::locale(locale_name));

        ASSERT_EQ(typeid(result), typeid(utf8));
        ASSERT_EQ(result, utf8);
    }
    #endif
}
// ---------------------------------------------------------------------------
TEST(TEncoding, IsUtf8)
{
    //
    // TSEncoding (eng)
    //
    {
        char _cp1251[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x00};
        std::string cp1251(_cp1251, strlen(_cp1251));
        std::string utf8("Hello World");

        ASSERT_TRUE(TSEncoding::IsUtf8(cp1251));
        ASSERT_TRUE(TSEncoding::IsUtf8(utf8));
    }
    //
    // TSEncoding (ru)
    //
    {
        std::locale _locale(locale_name);

        char _cp1251[] = {static_cast<char>(0xCF),
            static_cast<char>(0xF0),
            static_cast<char>(0xE8),
            static_cast<char>(0xE2),
            static_cast<char>(0xE5),
            static_cast<char>(0xF2),
            static_cast<char>(0x20),
            static_cast<char>(0xCC),
            static_cast<char>(0xE8),
            static_cast<char>(0xF0),
            static_cast<char>(0x00)};


        std::string cp1251(_cp1251, strlen(_cp1251));

        std::string utf8("Привет Мир");

        ASSERT_FALSE(TSEncoding::IsUtf8(cp1251, _locale));
        ASSERT_TRUE(TSEncoding::IsUtf8(utf8, _locale));
    }
    //
    // TWEncoding (eng)
    //
    {
        wchar_t _cp1251[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x00};
        std::wstring cp1251(_cp1251, wcslen(_cp1251));
        std::wstring utf8(L"Hello World");

        ASSERT_TRUE(TWEncoding::IsUtf8(cp1251));
        ASSERT_TRUE(TWEncoding::IsUtf8(utf8));
    }
    //
    // TWEncoding (ru)
    //
    #ifdef WINDOWS
    {
        std::locale _locale(locale_name);

        wchar_t _cp1251[] = { 1055, 1088, 1080, 1074, 1077, 1090, 32, 1052, 1080, 1088, 0 };

        std::wstring cp1251(_cp1251, wcslen(_cp1251));

        std::wstring utf8(L"Привет Мир");

        ASSERT_FALSE(TWEncoding::IsUtf8(cp1251, _locale));
        ASSERT_TRUE(TWEncoding::IsUtf8(utf8, _locale));
    }
    #endif
}
#pragma endregion
// ---------------------------------------------------------------------------
#pragma region StdExtension
TEST(StdExtension, deleted_unique_ptr)
{
    std::size_t counter(1);
    {
        Framework::StdExtension::deleted_unique_ptr<std::size_t> pointer(new std::size_t(counter), [&](std::size_t* value)
        {
            ASSERT_EQ(typeid(decltype(value)), typeid(std::size_t*));
            ASSERT_NE(value, nullptr);
            ASSERT_EQ(*value, 1);
            delete value;
            counter--;
        });
    }
    ASSERT_EQ(counter, 0);
}
// ---------------------------------------------------------------------------
TEST(StdExtension, C_STR)
{
    std::string first("First value");
    std::wstring second(L"Second value");

    auto first_result = Framework::StdExtension::C_STR(first);
    auto second_result = Framework::StdExtension::C_STR(second);

    ASSERT_EQ(typeid(decltype(first_result)), typeid(decltype(first.c_str())));
    ASSERT_EQ(first.c_str(), first_result);
    ASSERT_STREQ(first.c_str(), first_result);

    ASSERT_EQ(typeid(decltype(second_result)), typeid(decltype(second.c_str())));
    ASSERT_EQ(second.c_str(), second_result);
    ASSERT_STREQ(second.c_str(), second_result);
}
// ---------------------------------------------------------------------------
TEST(StdExtension, FrontBack)
{
    std::vector<std::size_t> values {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::size_t& front_value = Framework::StdExtension::FRONT(values);
    std::size_t& back_value = Framework::StdExtension::BACK(values);

    ASSERT_EQ(front_value, values.front());
    ASSERT_EQ(back_value, values.back());

    front_value = 10;
    back_value = 1;

    ASSERT_EQ(front_value, values.front());
    ASSERT_EQ(back_value, values.back());
}
// ---------------------------------------------------------------------------
TEST(StdExtension, FOR_EACH_Value_True)
{
    std::vector<uint32_t> values { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    Framework::StdExtension::FOR_EACH(std::begin(values), std::end(values), [](std::size_t index, uint32_t value)
    {
        ASSERT_EQ(index, static_cast<std::size_t>(value));
    });
}
// ---------------------------------------------------------------------------
TEST(StdExtension, FOR_EACH_Value_False)
{
    std::vector<uint32_t> values { 0, 1, 2, 3, 4, 5, 5, 7, 8, 9, 10 };

    Framework::StdExtension::FOR_EACH(std::begin(values), std::end(values), [](std::size_t index, uint32_t value)
    {
        if (index == 6)
        {
            ASSERT_NE(index, static_cast<std::size_t>(value));
        }
        else
        {
            ASSERT_EQ(index, static_cast<std::size_t>(value));
        }
    });
}
// ---------------------------------------------------------------------------
TEST(StdExtension, FOR_EACH_Const_Ref_True)
{
    std::vector<uint32_t> values { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    Framework::StdExtension::FOR_EACH(std::begin(values), std::end(values), [](std::size_t index, const uint32_t& value)
    {
        ASSERT_EQ(index, static_cast<std::size_t>(value));
    });
}
// ---------------------------------------------------------------------------
TEST(StdExtension, FOR_EACH_Const_Ref_False)
{
    std::vector<uint32_t> values { 0, 1, 2, 3, 4, 5, 5, 7, 8, 9, 10 };

    Framework::StdExtension::FOR_EACH(std::begin(values), std::end(values), [](std::size_t index, const uint32_t& value)
    {
        if (index == 6)
        {
            ASSERT_NE(index, static_cast<std::size_t>(value));
        }
        else
        {
            ASSERT_EQ(index, static_cast<std::size_t>(value));
        }
    });
}
// ---------------------------------------------------------------------------
TEST(StdExtension, FOR_EACH_Ref_True)
{
    std::vector<uint32_t> values { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    Framework::StdExtension::FOR_EACH(std::begin(values), std::end(values), [](std::size_t index, uint32_t& value)
    {
        ASSERT_EQ(index, static_cast<std::size_t>(value));
    });
}
// ---------------------------------------------------------------------------
TEST(StdExtension, FOR_EACH_Ref_False)
{
    std::vector<uint32_t> values { 0, 1, 2, 3, 4, 5, 5, 7, 8, 9, 10 };

    Framework::StdExtension::FOR_EACH(std::begin(values), std::end(values), [](std::size_t index, uint32_t& value)
    {
        if (index == 6)
        {
            ASSERT_NE(index, static_cast<std::size_t>(value));
        }
        else
        {
            ASSERT_EQ(index, static_cast<std::size_t>(value));
        }
    });
}
// ---------------------------------------------------------------------------
TEST(StdExtension, FOR_EACH_Ref_Change)
{
    std::vector<int32_t> result { 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };
    std::vector<int32_t> values { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    Framework::StdExtension::FOR_EACH(std::begin(values), std::end(values), [](std::size_t index, int32_t& value)
    {
        value *= -1;
    });

    ASSERT_EQ(std::size(result), std::size(values));

    for (std::size_t i(0); i < std::size(result); i++)
    {
        ASSERT_EQ(result.at(i), values.at(i));
    }
}
// ---------------------------------------------------------------------------
TEST(StdExtension, UniqueVector)
{
    std::vector<std::size_t> input01 {1, 2, 3, 3, 4, 5, 5, 5, 6, 7, 8, 8, 8, 9, 10};
    std::vector<std::size_t> output01 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    ASSERT_NE(std::size(input01), std::size(output01));

    Framework::StdExtension::UniqueVector(input01);

    ASSERT_EQ(std::size(input01), std::size(output01));
    for (std::size_t i(0); i < std::size(input01); i++)
    {
        ASSERT_EQ(input01.at(i), output01.at(i));
    }

    std::vector<std::pair<std::string, std::size_t>> input02 {{"First", 1}, {"First", 1}, {"First", 1}, {"Second", 2}, {"Third", 3}, {"Third", 3}};
    std::vector<std::pair<std::string, std::size_t>> output02 {{"First", 1}, {"Second", 2}, {"Third", 3}};

    ASSERT_NE(std::size(input02), std::size(output02));

    Framework::StdExtension::UniqueVector<std::pair<std::string, std::size_t>>(input02,
    [](const std::pair<std::string, std::size_t>& value1, const std::pair<std::string, std::size_t>& value2) -> bool
    {
        return value1.second < value2.second;
    },
    [](const std::pair<std::string, std::size_t>& value1, const std::pair<std::string, std::size_t>& value2) -> bool
    {
        return value1.second == value2.second;
    });

    ASSERT_EQ(std::size(input02), std::size(output02));
    for (std::size_t i(0); i < std::size(input02); i++)
    {
        ASSERT_EQ(input02.at(i).first, output02.at(i).first);
        ASSERT_EQ(input02.at(i).second, output02.at(i).second);
    }
}
// ---------------------------------------------------------------------------
TEST(StdExtension, AreSame)
{
    double first01(0.123213);
    double second01(0.123213);
    ASSERT_TRUE(Framework::StdExtension::AreSame(first01, second01));

    first01 = (first01 * 2)/3;
    second01 = (second01 * 2)/3;
    ASSERT_TRUE(Framework::StdExtension::AreSame(first01, second01));

    double first02(0.123213);
    double second02(0.123213000002);
    ASSERT_FALSE(Framework::StdExtension::AreSame(first02, second02));

    first02 = (first02 * 2)/3;
    second02 = (second02 * 2)/3;
    ASSERT_FALSE(Framework::StdExtension::AreSame(first02, second02));
}
// ---------------------------------------------------------------------------
TEST(StdExtension, GetTimeUTC)
{
    auto now = std::chrono::system_clock::now();

    std::tm time = {0};
    uint16_t milliseconds(0);

    Framework::StdExtension::GetTime(now, time, milliseconds, true, true);
    //
    // с 01.01.1970
    //
    auto now_epoch = now.time_since_epoch();

    typedef std::chrono::duration<uint32_t, std::ratio_multiply<std::chrono::hours::period, std::ratio<24>>::type> chrono_days;

    auto days = std::chrono::duration_cast<chrono_days>(now_epoch);
    now_epoch -= days;

    auto hours = std::chrono::duration_cast<std::chrono::hours>(now_epoch);
    now_epoch -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(now_epoch);
    now_epoch -= minutes;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now_epoch);
    now_epoch -= seconds;

    auto _milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now_epoch);
    //
    // Вычисляем текущий год
    //
    std::size_t year(1970);
    std::size_t _days(days.count());
    for (; _days > 365; year++, _days -= year % 4 == 0 ? 366 : 365) {}
    //
    // Вычисляем текущий месяц
    //
    std::size_t month(0);
    std::array<uint8_t, 12> day_in_month = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 4 == 0) day_in_month[1] = 29;

    for (; month < std::size(day_in_month); month++)
    {
        if (_days >= day_in_month[month])
        {
            _days -= day_in_month[month];
        }
        else
        {
            month += 1;
            break;
        }
    }
    //
    // Вычисляем текущий день
    //
    _days += year % 4 == 0 ? 2 : 1;
    //
    // Сравниваем значения
    //
    ASSERT_EQ(year, static_cast<std::size_t>(time.tm_year));
    ASSERT_EQ(month, static_cast<std::size_t>(time.tm_mon));
    ASSERT_EQ(_days, static_cast<std::size_t>(time.tm_mday));
    ASSERT_EQ(static_cast<std::size_t>(hours.count()), static_cast<std::size_t>(time.tm_hour));
    ASSERT_EQ(static_cast<std::size_t>(minutes.count()), static_cast<std::size_t>(time.tm_min));
    ASSERT_EQ(static_cast<std::size_t>(seconds.count()), static_cast<std::size_t>(time.tm_sec));
    ASSERT_EQ(static_cast<std::size_t>(_milliseconds.count()), static_cast<std::size_t>(milliseconds));
}
// ---------------------------------------------------------------------------
TEST(StdExtension, GetTimeLocal)
{
    auto now = std::chrono::system_clock::now();

    std::tm time = {0};
    uint16_t milliseconds(0);

    Framework::StdExtension::GetTime(now, time, milliseconds, true, false);
    //
    // с 01.01.1970
    //
    auto now_epoch = now.time_since_epoch();

    typedef std::chrono::duration<uint32_t, std::ratio_multiply<std::chrono::hours::period, std::ratio<24>>::type> chrono_days;

    auto days = std::chrono::duration_cast<chrono_days>(now_epoch);
    now_epoch -= days;

    auto hours = std::chrono::duration_cast<std::chrono::hours>(now_epoch);
    now_epoch -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(now_epoch);
    now_epoch -= minutes;

    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(now_epoch);
    now_epoch -= seconds;

    auto _milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now_epoch);
    //
    // Вычисляем текущий год
    //
    std::size_t year(1970);
    std::size_t _days(days.count());
    for (; _days > 365; year++, _days -= year % 4 == 0 ? 366 : 365) {}
    //
    // Вычисляем текущий месяц
    //
    std::size_t month(0);
    std::array<uint8_t, 12> day_in_month = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (year % 4 == 0) day_in_month[1] = 29;

    for (; month < std::size(day_in_month); month++)
    {
        if (_days >= day_in_month[month])
        {
            _days -= day_in_month[month];
        }
        else
        {
            month += 1;
            break;
        }
    }
    //
    // Вычисляем текущий день
    //
    _days += year % 4 == 0 ? 2 : 1;
    //
    // Сравниваем значения
    //
    ASSERT_EQ(year, static_cast<std::size_t>(time.tm_year));
    ASSERT_EQ(month, static_cast<std::size_t>(time.tm_mon));
    ASSERT_EQ(_days, static_cast<std::size_t>(time.tm_mday));
    ASSERT_EQ(static_cast<std::size_t>(hours.count() + 3), static_cast<std::size_t>(time.tm_hour));
    ASSERT_EQ(static_cast<std::size_t>(minutes.count()), static_cast<std::size_t>(time.tm_min));
    ASSERT_EQ(static_cast<std::size_t>(seconds.count()), static_cast<std::size_t>(time.tm_sec));
    ASSERT_EQ(static_cast<std::size_t>(_milliseconds.count()), static_cast<std::size_t>(milliseconds));
}
// ---------------------------------------------------------------------------
TEST(StdExtension, LinuxCmdArgs)
{
#ifdef LINUX
    {
        std::vector<std::string> cmd_argc;

        ASSERT_TRUE(Framework::StdExtension::LinuxCmdArgs(cmd_argc));
        ASSERT_GE(std::size(cmd_argc), 1);
        ASSERT_EQ(typeid(std::string), typeid(cmd_argc.front()));

        stdfs::path _path(cmd_argc.front());

        ASSERT_EQ(_path.filename().string(), std::string("FwBaseTest"));
    }
    {
        std::vector<std::wstring> cmd_argc;

        ASSERT_TRUE(Framework::StdExtension::LinuxCmdArgs<std::wstring>(cmd_argc));
        ASSERT_GE(std::size(cmd_argc), 1);
        ASSERT_EQ(typeid(std::wstring), typeid(cmd_argc.front()));

        stdfs::path _path(cmd_argc.front());

        ASSERT_EQ(_path.filename().wstring(), std::wstring(L"FwBaseTest"));
    }
#endif
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TableAlignS)
{
    //
    // Left
    //
    {
        std::vector<std::vector<std::string>> table = {
            { "_Value1_", "__Value2__", "___Value3___", "____Value4____" },
            { "Temp1", "Temp2", "Temp3", "Temp4" },
            { "1", "2", "3", "4" }
        };

        ASSERT_TRUE(Framework::StdExtension::TableAlign(table, Framework::StdExtension::TTableAlign::Left));

        std::vector<std::size_t> max_size;

        for (const auto& value : table.at(0))
        {
            max_size.push_back(std::size(value));
        }

        for (std::size_t i(0); i < std::size(table); i++)
        {
            for (std::size_t k(0); k < std::size(table.at(i)); k++)
            {
                ASSERT_EQ(max_size.at(k), std::size(table.at(i).at(k)));

                if (i != 0)
                {
                    ASSERT_NE(table.at(i).at(k).front(), ' ');
                    ASSERT_EQ(table.at(i).at(k).back(), ' ');
                }
            }
        }
    }
    //
    // Right
    //
    {
        std::vector<std::vector<std::string>> table = {
            { "_Value1_", "__Value2__", "___Value3___", "____Value4____" },
            { "Temp1", "Temp2", "Temp3", "Temp4" },
            { "1", "2", "3", "4" }
        };

        ASSERT_TRUE(Framework::StdExtension::TableAlign(table, Framework::StdExtension::TTableAlign::Right));

        std::vector<std::size_t> max_size;

        for (const auto& value : table.at(0))
        {
            max_size.push_back(std::size(value));
        }

        for (std::size_t i(0); i < std::size(table); i++)
        {
            for (std::size_t k(0); k < std::size(table.at(i)); k++)
            {
                ASSERT_EQ(max_size.at(k), std::size(table.at(i).at(k)));

                if (i != 0)
                {
                    ASSERT_EQ(table.at(i).at(k).front(), ' ');
                    ASSERT_NE(table.at(i).at(k).back(), ' ');
                }
            }
        }
    }
    //
    // Center
    //
    {
        std::vector<std::vector<std::string>> table = {
            { "_Value1_", "__Value2__", "___Value3___", "____Value4____" },
            { "Temp1", "Temp2", "Temp3", "Temp4" },
            { "1", "2", "3", "4" }
        };

        ASSERT_TRUE(Framework::StdExtension::TableAlign(table, Framework::StdExtension::TTableAlign::Center));

        std::vector<std::size_t> max_size;

        for (const auto& value : table.at(0))
        {
            max_size.push_back(std::size(value));
        }

        for (std::size_t i(0); i < std::size(table); i++)
        {
            for (std::size_t k(0); k < std::size(table.at(i)); k++)
            {
                ASSERT_EQ(max_size.at(k), std::size(table.at(i).at(k)));

                if (i != 0)
                {
                    ASSERT_EQ(table.at(i).at(k).front(), ' ');
                    ASSERT_EQ(table.at(i).at(k).back(), ' ');
                }
            }
        }
    }
    //
    // None
    //
    {
        std::vector<std::vector<std::string>> table = {
            { "_Value1_", "__Value2__", "___Value3___", "____Value4____" },
            { "Temp1", "Temp2", "Temp3", "Temp4" },
            { "1", "2", "3", "4" }
        };

        ASSERT_TRUE(Framework::StdExtension::TableAlign(table, Framework::StdExtension::TTableAlign::None));

        for (std::size_t i(0); i < std::size(table); i++)
        {
            for (std::size_t k(0); k < std::size(table.at(i)); k++)
            {
                ASSERT_NE(table.at(i).at(k).front(), ' ');
                ASSERT_NE(table.at(i).at(k).back(), ' ');
            }
        }
    }
    //
    // Error
    //
    {
        std::vector<std::vector<std::string>> table = {
            { "_Value1_", "__Value2__", "___Value3___", "____Value4____" },
            { "Temp1", "Temp2", "Temp3", "Temp4", "Temp5" }, // Temp5 - error
            { "1", "2", "3", "4" }
        };

        ASSERT_FALSE(Framework::StdExtension::TableAlign(table, Framework::StdExtension::TTableAlign::Left));
    }
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TableAlignW)
{
    //
    // Left
    //
    {
        std::vector<std::vector<std::wstring>> table = {
            { L"_Value1_", L"__Value2__", L"___Value3___", L"____Value4____" },
            { L"Temp1", L"Temp2", L"Temp3", L"Temp4" },
            { L"1", L"2", L"3", L"4" }
        };

        ASSERT_TRUE(Framework::StdExtension::TableAlign(table, Framework::StdExtension::TTableAlign::Left));

        std::vector<std::size_t> max_size;

        for (const auto& value : table.at(0))
        {
            max_size.push_back(std::size(value));
        }

        for (std::size_t i(0); i < std::size(table); i++)
        {
            for (std::size_t k(0); k < std::size(table.at(i)); k++)
            {
                ASSERT_EQ(max_size.at(k), std::size(table.at(i).at(k)));

                if (i != 0)
                {
                    ASSERT_NE(table.at(i).at(k).front(), L' ');
                    ASSERT_EQ(table.at(i).at(k).back(), L' ');
                }
            }
        }
    }
    //
    // Right
    //
    {
        std::vector<std::vector<std::wstring>> table = {
            { L"_Value1_", L"__Value2__", L"___Value3___", L"____Value4____" },
            { L"Temp1", L"Temp2", L"Temp3", L"Temp4" },
            { L"1", L"2", L"3", L"4" }
        };

        ASSERT_TRUE(Framework::StdExtension::TableAlign(table, Framework::StdExtension::TTableAlign::Right));

        std::vector<std::size_t> max_size;

        for (const auto& value : table.at(0))
        {
            max_size.push_back(std::size(value));
        }

        for (std::size_t i(0); i < std::size(table); i++)
        {
            for (std::size_t k(0); k < std::size(table.at(i)); k++)
            {
                ASSERT_EQ(max_size.at(k), std::size(table.at(i).at(k)));

                if (i != 0)
                {
                    ASSERT_EQ(table.at(i).at(k).front(), L' ');
                    ASSERT_NE(table.at(i).at(k).back(), L' ');
                }
            }
        }
    }
    //
    // Center
    //
    {
        std::vector<std::vector<std::wstring>> table = {
            { L"_Value1_", L"__Value2__", L"___Value3___", L"____Value4____" },
            { L"Temp1", L"Temp2", L"Temp3", L"Temp4" },
            { L"1", L"2", L"3", L"4" }
        };

        ASSERT_TRUE(Framework::StdExtension::TableAlign(table, Framework::StdExtension::TTableAlign::Center));

        std::vector<std::size_t> max_size;

        for (const auto& value : table.at(0))
        {
            max_size.push_back(std::size(value));
        }

        for (std::size_t i(0); i < std::size(table); i++)
        {
            for (std::size_t k(0); k < std::size(table.at(i)); k++)
            {
                ASSERT_EQ(max_size.at(k), std::size(table.at(i).at(k)));

                if (i != 0)
                {
                    ASSERT_EQ(table.at(i).at(k).front(), L' ');
                    ASSERT_EQ(table.at(i).at(k).back(), L' ');
                }
            }
        }
    }
    //
    // None
    //
    {
        std::vector<std::vector<std::wstring>> table = {
            { L"_Value1_", L"__Value2__", L"___Value3___", L"____Value4____" },
            { L"Temp1", L"Temp2", L"Temp3", L"Temp4" },
            { L"1", L"2", L"3", L"4" }
        };

        ASSERT_TRUE(Framework::StdExtension::TableAlign(table, Framework::StdExtension::TTableAlign::None));

        for (std::size_t i(0); i < std::size(table); i++)
        {
            for (std::size_t k(0); k < std::size(table.at(i)); k++)
            {
                ASSERT_NE(table.at(i).at(k).front(), L' ');
                ASSERT_NE(table.at(i).at(k).back(), L' ');
            }
        }
    }
    //
    // Error
    //
    {
        std::vector<std::vector<std::wstring>> table = {
            { L"_Value1_", L"__Value2__", L"___Value3___", L"____Value4____" },
            { L"Temp1", L"Temp2", L"Temp3", L"Temp4", L"Temp5" }, // Temp5 - error
            { L"1", L"2", L"3", L"4" }
        };

        ASSERT_FALSE(Framework::StdExtension::TableAlign(table, Framework::StdExtension::TTableAlign::Left));
    }
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSamePair)
{
    //
    // TSSamePair
    //
    {
        TSSamePair value01('=', "Hello=Word");
        ASSERT_TRUE(value01.IsMatched());
        ASSERT_EQ(value01.first, std::string("Hello"));
        ASSERT_EQ(value01.second, std::string("Word"));

        TSSamePair value02('!', "Hello!Word");
        ASSERT_TRUE(value02.IsMatched());
        ASSERT_EQ(value02.first, std::string("Hello"));
        ASSERT_EQ(value02.second, std::string("Word"));

        TSSamePair value03('#', "Hello#Word");
        ASSERT_TRUE(value03.IsMatched());
        ASSERT_EQ(value03.first, std::string("Hello"));
        ASSERT_EQ(value03.second, std::string("Word"));
    }
    {
        TSSamePair value01('=');
        value01.Set("Hello=Word");
        ASSERT_TRUE(value01.IsMatched());
        ASSERT_EQ(value01.first, std::string("Hello"));
        ASSERT_EQ(value01.second, std::string("Word"));

        value01.Set("World=Hello");
        ASSERT_TRUE(value01.IsMatched());
        ASSERT_EQ(value01.first, std::string("World"));
        ASSERT_EQ(value01.second, std::string("Hello"));
    }
    //
    // TWSamePair
    //
    {
        TWSamePair value01(L'=', L"Hello=Word");
        ASSERT_TRUE(value01.IsMatched());
        ASSERT_EQ(value01.first, std::wstring(L"Hello"));
        ASSERT_EQ(value01.second, std::wstring(L"Word"));

        TWSamePair value02(L'!', L"Hello!Word");
        ASSERT_TRUE(value02.IsMatched());
        ASSERT_EQ(value02.first, std::wstring(L"Hello"));
        ASSERT_EQ(value02.second, std::wstring(L"Word"));

        TWSamePair value03(L'#', L"Hello#Word");
        ASSERT_TRUE(value03.IsMatched());
        ASSERT_EQ(value03.first, std::wstring(L"Hello"));
        ASSERT_EQ(value03.second, std::wstring(L"Word"));
    }
    {
        TWSamePair value01(L'=');
        value01.Set(L"Hello=Word");
        ASSERT_TRUE(value01.IsMatched());
        ASSERT_EQ(value01.first, std::wstring(L"Hello"));
        ASSERT_EQ(value01.second, std::wstring(L"Word"));

        value01.Set(L"World=Hello");
        ASSERT_TRUE(value01.IsMatched());
        ASSERT_EQ(value01.first, std::wstring(L"World"));
        ASSERT_EQ(value01.second, std::wstring(L"Hello"));
    }

}
// ---------------------------------------------------------------------------
TEST(StdExtension, TEvent)
{
    int32_t counter(0);

    auto inc_counter = [](int32_t& value) { value++; };
    auto dec_counter = [](int32_t& value) { value--; };

    Framework::StdExtension::Events::TEvent<int32_t> event;
    Framework::StdExtension::Events::TEventAccessor<int32_t> event_accessor(event);

    ASSERT_EQ(counter, 0);

    event.Set(inc_counter);
    event_accessor.Invoke(counter);
    ASSERT_EQ(counter, 1);

    auto dec_handle(event = dec_counter);
    event_accessor.Invoke(counter);
    ASSERT_EQ(counter, 0);

    event.Remove(dec_handle);
    event_accessor.Invoke(counter);
    ASSERT_EQ(counter, 0);

    event.Add(inc_counter);
    dec_handle = event += dec_counter;
    event_accessor.Invoke(counter);
    ASSERT_EQ(counter, 0);

    event -= dec_handle;
    event_accessor.Invoke(counter);
    ASSERT_EQ(counter, 1);

    event = dec_counter;
    event_accessor.Invoke(counter);
    ASSERT_EQ(counter, 0);
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSemaphore1)
{
    bool stop(false);
    std::size_t counter(0);
    Framework::StdExtension::Threading::TSemaphore semaphore(0);

    std::thread thread_inc([&]()
    {
        while (true)
        {
            semaphore.Wait();
            counter++;
            if (stop) break;
        }
        
    });

    Framework::StdExtension::Threading::TBaseThread::Sleep(100);

    for (std::size_t i(0); i < 100; i++)
    {
        if (i == 99)
        {
            Framework::StdExtension::Threading::TBaseThread::Sleep(100);
            stop = true;
        }
        semaphore.Release();
    }

    thread_inc.join();

    ASSERT_EQ(counter, 100);
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSemaphore2)
{
    Framework::StdExtension::Threading::TSemaphore semaphore;

    bool stopped01(false);
    std::thread thread01([&]() 
    {
        Framework::StdExtension::Threading::TBaseThread::Sleep(300);
        semaphore.Release(3);
        stopped01 = true;
    });

    bool stopped02(false);
    std::thread thread02([&]()
    { 
        semaphore.Wait();
        stopped02 = true;
    });

    bool stopped03(false);
    std::thread thread03([&]()
    {
        semaphore.Wait();
        stopped03 = true;
    });

    bool stopped04(false);
    std::thread thread04([&]()
    {
        semaphore.Wait();
        stopped04 = true;
    });


    thread01.join();
    thread02.join();
    thread03.join();
    thread04.join();

    ASSERT_TRUE(stopped01);
    ASSERT_TRUE(stopped02);
    ASSERT_TRUE(stopped03);
    ASSERT_TRUE(stopped04);
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSemaphore3)
{
    std::size_t counter(4), sleep_time(100);
    Framework::StdExtension::Threading::TSemaphore semaphore;

    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>> times;

    auto thread_func_semaphore1 = [&]()
    {
        semaphore.Wait();

        times.push_back(high_resolution_clock::now());
        if (counter > 1) times.push_back(high_resolution_clock::now());

        Framework::StdExtension::Threading::TBaseThread::Sleep(static_cast<uint32_t>(sleep_time));

        if (counter > 0)
        {
            counter--;
            semaphore.Release();
        }
    };

    std::thread thread01(thread_func_semaphore1);
    std::thread thread02(thread_func_semaphore1);
    std::thread thread03(thread_func_semaphore1);
    std::thread thread04(thread_func_semaphore1);

    times.push_back(high_resolution_clock::now());
    Framework::StdExtension::Threading::TBaseThread::Sleep(static_cast<uint32_t>(sleep_time));
    times.push_back(high_resolution_clock::now());

    times.push_back(high_resolution_clock::now());
    Framework::StdExtension::Threading::TBaseThread::Sleep(static_cast<uint32_t>(sleep_time));
    semaphore.Release();

    thread01.join();
    thread02.join();
    thread03.join();
    thread04.join();

    ASSERT_EQ(counter, 0);

    ASSERT_EQ(std::size(times), 10);

    while(std::size(times) > 0)
    {
        auto t2 = times.back();
        times.pop_back();

        auto t1 = times.back();
        times.pop_back();

        auto ms_int = duration_cast<milliseconds>(t2 - t1);

        ASSERT_GE(static_cast<std::size_t>(ms_int.count()), sleep_time);
    }
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSemaphore4)
{
    std::array<bool, 4> result { false, false, false, false };

    Framework::StdExtension::Threading::TSemaphore semaphore;

    std::thread thread01([&]() { semaphore.Wait(); result[0] = true; });
    std::thread thread02([&]() { semaphore.Wait(); result[1] = true; });
    std::thread thread03([&]() { semaphore.Wait(); result[2] = true; });
    std::thread thread04([&]() { semaphore.Wait(); result[3] = true; });

    std::size_t true_result = std::count_if(std::begin(result), std::end(result), [](bool value) { return value == true; });

    ASSERT_EQ(true_result, 0);

    semaphore.Release(4);

    thread01.join();
    thread02.join();
    thread03.join();
    thread04.join();

    true_result = std::count_if(std::begin(result), std::end(result), [](bool value) { return value == true; });

    ASSERT_EQ(true_result, 4);
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSemaphore5)
{
    std::size_t sleep_time(100);

    std::mutex mtx;
    Framework::StdExtension::Threading::TSemaphore semaphore;

    auto my_thread_func_semaphore5 = [&]()
    {
        semaphore.Wait();
    };

    std::thread thread01(my_thread_func_semaphore5);
    std::thread thread02(my_thread_func_semaphore5);
    std::thread thread03(my_thread_func_semaphore5);
    std::thread thread04(my_thread_func_semaphore5);

    std::thread temp([&]()
    {
        Framework::StdExtension::Threading::TBaseThread::Sleep(static_cast<uint32_t>(sleep_time));
        semaphore.Release(4);
    });

    auto t1 = std::chrono::high_resolution_clock::now();
    thread01.join();
    thread02.join();
    thread03.join();
    thread04.join();
    auto t2 = std::chrono::high_resolution_clock::now();
    temp.join();

    auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

    ASSERT_GE(static_cast<std::size_t>(ms_int.count()), sleep_time);
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSemaphore6)
{
    std::mutex counter_thread_mutex;
    std::size_t counter_thread_counter(0);
    bool counter_thread_stop(false);
    std::thread counter_thread([&]()
    {
        while(!counter_thread_stop)
        {
            {
                std::lock_guard lock(counter_thread_mutex);
                counter_thread_counter++;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    });

    Framework::StdExtension::Threading::TSemaphore semaphore;

    std::size_t th1_begin(0), th1_end(0);
    std::thread th1([&]()
    {
        {
            std::lock_guard lock(counter_thread_mutex);
            th1_begin = counter_thread_counter;
        }
        semaphore.Wait();
        {
            std::lock_guard lock(counter_thread_mutex);
            th1_end = counter_thread_counter;
        }
    });

    std::size_t th2_begin(0), th2_end(0);
    std::thread th2([&]()
    {
        {
            std::lock_guard lock(counter_thread_mutex);
            th2_begin = counter_thread_counter;
        }
        semaphore.Wait();
        {
            std::lock_guard lock(counter_thread_mutex);
            th2_end = counter_thread_counter;
        }
    });

    std::size_t th3_begin(0), th3_end(0);
    std::thread th3([&]()
    {
        {
            std::lock_guard lock(counter_thread_mutex);
            th3_begin = counter_thread_counter;
        }
        semaphore.Wait();
        {
            std::lock_guard lock(counter_thread_mutex);
            th3_end = counter_thread_counter;
        }
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    semaphore.Release(3);
    th1.join();
    th2.join();
    th3.join();

    counter_thread_stop = true;
    counter_thread.join();

    ASSERT_GT((th1_end - th1_begin), std::size_t(0));
    ASSERT_GT((th2_end - th2_begin), std::size_t(0));
    ASSERT_GT((th3_end - th3_begin), std::size_t(0));
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSemaphore7)
{
    Framework::StdExtension::Threading::TSemaphore semaphore;

    bool th_stop(false);
    std::size_t th1_counter(0);
    std::thread th1([&]()
    {
        while(!th_stop)
        {
            semaphore.Wait();
            th1_counter++;
        }
    });

    std::size_t th2_counter(0);
    std::thread th2([&]()
    {
        while(!th_stop)
        {
            semaphore.Wait();
            th2_counter++;
        }
    });

    bool signal_stop(false);
    std::size_t signal_counter(0);
    std::thread signal([&]()
    {
        while(!signal_stop)
        {
            semaphore.Release(2);
            signal_counter++;
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        semaphore.Release(2);
        signal_counter++;
    });

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    th_stop = true;
    signal_stop = true;

    th1.join();
    th2.join();
    signal.join();

    ASSERT_NE(th1_counter, 0);
    ASSERT_NE(th2_counter, 0);
    ASSERT_EQ(th1_counter + th2_counter, signal_counter * 2);
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeQueue)
{
    Framework::StdExtension::Threading::TSafeQueue<std::size_t> queue;

    std::thread _thread([&]()
    {
        Framework::StdExtension::Threading::TBaseThread::Sleep(100);
        queue.Push(10);
        Framework::StdExtension::Threading::TBaseThread::Sleep(200);
        queue.Push(20);
        Framework::StdExtension::Threading::TBaseThread::Sleep(300);
        queue.Push(30);
        Framework::StdExtension::Threading::TBaseThread::Sleep(400);
        queue.Push(40);
        Framework::StdExtension::Threading::TBaseThread::Sleep(500);
        queue.Push(50);
    });

    std::size_t value(0);

    queue.Pop(value);
    ASSERT_EQ(value, 10);

    queue.Pop(value);
    ASSERT_EQ(value, 20);

    queue.Pop(value);
    ASSERT_EQ(value, 30);

    queue.Pop(value);
    ASSERT_EQ(value, 40);

    queue.Pop(value);
    ASSERT_EQ(value, 50);

    _thread.join();
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeMemoryPool)
{
    std::vector<std::string> stings;
    std::vector<char*> mem_blocks;
    Framework::StdExtension::Threading::TSafeMemoryPool<char> safe_memory_pool(255);
    //
    // Выделение памяти
    //
    for (std::size_t i(0); i < 5; i++)
    {
        std::string str = Framework::String::TFormater<std::string>::Format("Hello world {0}", i);

        stings.push_back(str);

        char* pool_buffer = safe_memory_pool.New([](char* value, size_t block_size) { memset(value, 0, block_size); });

        memcpy(pool_buffer, str.c_str(), str.length());

        mem_blocks.push_back(pool_buffer);
    }
    //
    // Возврат памяти в пул
    //
    for (char* mem_block : mem_blocks)
    {
        safe_memory_pool.Delete(mem_block);
    }
    mem_blocks.clear();
    //
    // Повторное выделение памяти
    //
    for (std::size_t i(0); i < 5; i++)
    {
        mem_blocks.push_back(safe_memory_pool.New());
    }

    ASSERT_EQ(mem_blocks.size(), stings.size());

    for (std::size_t i(0); i < stings.size(); i++)
    {
        std::string temp(mem_blocks.at(i), strlen(mem_blocks.at(i)));

        ASSERT_EQ(temp, stings.at(i));
    }
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeArrayQueueTrue)
{
    std::size_t num_elemets(100);
    Framework::StdExtension::Threading::TSafeArrayQueue<std::size_t> queue(num_elemets);
    //
    // Формирование проверочных данных
    //
    std::vector<std::vector<std::size_t>> expected_result;
    for (size_t i(0); i < 10; i++)
    {
        expected_result.push_back(std::vector<std::size_t> (num_elemets, i));
    }
    //
    // Проверка некоторых методов очереди
    //
    ASSERT_TRUE(queue.IsEmpty());
    ASSERT_FALSE(queue.IsFull());
    ASSERT_EQ(queue.Size(), std::size_t(0));
    ASSERT_EQ(queue.DataSize(), num_elemets * sizeof(std::size_t));

    std::thread _thread([&]()
    {
        Framework::StdExtension::Threading::TBaseThread::Sleep(100);

        for (std::size_t i(0); i < std::size(expected_result); i++)
        {
            queue.Push(std::data(expected_result.at(i)), std::size(expected_result.at(i)) * sizeof(std::size_t));
            Framework::StdExtension::Threading::TBaseThread::Sleep(100 * i);
        }
    });

    std::vector<std::size_t> buffer(num_elemets, 0);


    for (size_t i(0); i < expected_result.size(); i++)
    {
        ASSERT_TRUE(queue.Pop(buffer.data(), buffer.size() * sizeof(std::size_t)));
        ASSERT_TRUE(memcmp(buffer.data(), expected_result.at(i).data(), buffer.size() * sizeof(std::size_t)) == 0);
    }

    _thread.join();

    ASSERT_TRUE(queue.IsEmpty());
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeArrayQueueSize)
{
    std::size_t num_elemets(100);
    {
        Framework::StdExtension::Threading::TSafeArrayQueue<int8_t> queue(num_elemets, num_elemets);

        ASSERT_TRUE(queue.IsEmpty());
        ASSERT_FALSE(queue.IsFull());
        ASSERT_EQ(queue.DataSize(), num_elemets);
        ASSERT_EQ(queue.MaxSize(), num_elemets);
    }
    {
        Framework::StdExtension::Threading::TSafeArrayQueue<int8_t> queue(num_elemets, 0);

        ASSERT_TRUE(queue.IsEmpty());
        ASSERT_FALSE(queue.IsFull());
        ASSERT_EQ(queue.DataSize(), num_elemets);
        ASSERT_EQ(queue.MaxSize(), (std::numeric_limits<size_t>::max)());
    }
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeArrayQueueFirst)
{
    std::size_t num_elemets(100);

    Framework::StdExtension::Threading::TSafeArrayQueue<int8_t> queue(num_elemets);

    std::vector<int8_t> buffer(num_elemets, -50);

    ASSERT_TRUE(queue.IsEmpty());

    ASSERT_FALSE(queue.First(buffer.data(), buffer.size()));

    ASSERT_TRUE(queue.Push(buffer.data(), buffer.size()));

    ASSERT_FALSE(queue.First(buffer.data(), buffer.size() - 1));

    ASSERT_TRUE(queue.First(buffer.data(), buffer.size()));
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeArrayQueueFalse01)
{
    std::size_t num_elemets(100);

    Framework::StdExtension::Threading::TSafeArrayQueue<int8_t> queue(num_elemets);

    std::vector<int8_t> buffer(num_elemets * 2, 50);

    ASSERT_FALSE(queue.Push(buffer.data(), buffer.size()));

    ASSERT_GE(buffer.size(), num_elemets);

    ASSERT_TRUE(queue.Push(buffer.data(), num_elemets));

    ASSERT_FALSE(queue.Pop(buffer.data(), num_elemets -1));

    ASSERT_TRUE(queue.Pop(buffer.data(), buffer.size()));
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeArrayQueueFalse02)
{
    std::size_t num_elemets(100);

    Framework::StdExtension::Threading::TSafeArrayQueue<int8_t> queue(num_elemets);

    std::vector<int8_t> buffer(num_elemets, 50);

    ASSERT_FALSE(queue.Pop(buffer.data(), buffer.size(), 1000));
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeArrayQueueFalse03)
{
    std::size_t num_elemets(100);

    Framework::StdExtension::Threading::TSafeArrayQueue<int8_t> queue(num_elemets);

    std::vector<int8_t> buffer(num_elemets, 50);

    ASSERT_FALSE(queue.Pop(buffer.data(), buffer.size(), 1000));
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeArrayQueueFalse04)
{
    std::size_t num_elemets(100);

    Framework::StdExtension::Threading::TSafeArrayQueue<int8_t> queue(num_elemets, 1);

    ASSERT_EQ(queue.MaxSize(), std::size_t(1));

    std::vector<int8_t> buffer(num_elemets, 50);

    ASSERT_TRUE(queue.Push(buffer.data(), buffer.size(), 1000));

    ASSERT_TRUE(queue.IsFull());

    ASSERT_FALSE(queue.IsEmpty());

    ASSERT_FALSE(queue.Push(buffer.data(), buffer.size(), 1000));
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeBuffer01)
{
    std::vector<int8_t> buffer(100, -1);

    std::vector<int8_t> read_buffer(buffer.size() , 0);

    ASSERT_EQ(buffer.size(), read_buffer.size());

    ASSERT_FALSE(memcmp(buffer.data(), read_buffer.data(), buffer.size()) == 0);

    Framework::StdExtension::Threading::TSafeBuffer<int8_t> safe_buffer(buffer.size(), -1);

    ASSERT_TRUE(safe_buffer.Read(read_buffer.data(), read_buffer.size()));

    ASSERT_TRUE(memcmp(buffer.data(), read_buffer.data(), buffer.size()) == 0);
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeBuffer02)
{
    std::vector<uint8_t> buffer(100);

    Framework::StdExtension::FOR_EACH(std::begin(buffer), std::end(buffer), [] (std::size_t index, uint8_t& value) {
        value = static_cast<uint8_t>(index);
    });

    std::vector<int8_t> read_buffer(buffer.size() , 0);

    ASSERT_EQ(buffer.size(), read_buffer.size());

    ASSERT_FALSE(memcmp(buffer.data(), read_buffer.data(), buffer.size()) == 0);

    uint8_t index(0);

    Framework::StdExtension::Threading::TSafeBuffer<uint8_t> safe_buffer(buffer.size(), [&index](uint8_t& value) {
        value = index;
        index++;
    });

    ASSERT_TRUE(safe_buffer.Read(read_buffer.data(), read_buffer.size()));

    ASSERT_TRUE(memcmp(buffer.data(), read_buffer.data(), buffer.size()) == 0);
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeBufferWrite)
{
    std::vector<uint8_t> buffer(100, 0);

    Framework::StdExtension::Threading::TSafeBuffer<int8_t> safe_buffer(buffer.size() - 1);

    ASSERT_FALSE(safe_buffer.Write(buffer.data(), buffer.size()));

    ASSERT_TRUE(safe_buffer.Write(buffer.data(), buffer.size() - 1));
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeBufferRead)
{
    std::vector<uint8_t> buffer(100, 0);

    Framework::StdExtension::Threading::TSafeBuffer<int8_t> safe_buffer(buffer.size(), 0);

    ASSERT_FALSE(safe_buffer.Read(buffer.data(), buffer.size() -1));

    ASSERT_TRUE(safe_buffer.Read(buffer.data(), buffer.size()));
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeBufferWriteRead)
{
    std::vector<uint8_t> buffer(100, -1);

    std::vector<uint8_t> read_buffer(buffer.size(), 0);

    ASSERT_EQ(buffer.size(), read_buffer.size());

    ASSERT_FALSE(memcmp(buffer.data(), read_buffer.data(), buffer.size()) == 0);

    Framework::StdExtension::Threading::TSafeBuffer<int8_t> safe_buffer(buffer.size());

    ASSERT_EQ(buffer.size(), safe_buffer.BufferSize());

    ASSERT_TRUE(safe_buffer.Read(read_buffer.data(), read_buffer.size()));

    ASSERT_FALSE(memcmp(buffer.data(), read_buffer.data(), buffer.size()) == 0);

    ASSERT_TRUE(safe_buffer.Write(buffer.data(), buffer.size()));

    ASSERT_TRUE(safe_buffer.Read(read_buffer.data(), read_buffer.size()));

    ASSERT_TRUE(memcmp(buffer.data(), read_buffer.data(), buffer.size()) == 0);
}
// ---------------------------------------------------------------------------
TEST(StdExtension, TSafeBufferSize)
{
    std::vector<double> buffer(100);

    Framework::StdExtension::Threading::TSafeBuffer<double> safe_buffer(buffer.size());

    ASSERT_EQ(buffer.size() * sizeof(double), safe_buffer.BufferSize());
}
#pragma endregion
// ---------------------------------------------------------------------------
#pragma region Crypto
namespace
{
    void MakeRandomStrings(std::vector<std::string>& strings, std::size_t count, bool upper = false)
    {
        auto rand_char = [upper]() -> char
        {
            const char charset[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
            const char charset_up[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

            const std::size_t max_index = upper ? (sizeof(charset_up) - 1) : (sizeof(charset) - 1);

            const std::size_t charset_index = std::rand() % max_index;

            return upper ? charset_up[charset_index] : charset[charset_index];
        };

        auto rand_len = [](int32_t min, int32_t max) -> int32_t
        {
            return min + std::rand() % (max - min);
        };

        while(count > 0)
        {
            if (int32_t str_len = rand_len(1, 255); str_len > 0)
            {
                std::string str(str_len, 0);
                std::generate_n(str.begin(), str_len, rand_char);
                strings.push_back(str);
                count--;
            }
        }
    }
};
// ---------------------------------------------------------------------------
TEST(TCRC, CRC32)
{
    {
        char input[] = "Hello World\n";
        uint32_t output(0xB095E5E3);

        auto result = TSCRC::CRC32(input, strlen(input));

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    {
        char input[] = "Привет Мир\n";
        uint32_t output(0x1A585841);

        auto result = TSCRC::CRC32(input, strlen(input));

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
TEST(TCRC, NormalHASH32)
{
    {
        std::string input("Hello World\n");
        uint32_t output(0xB095E5E3);

        auto result = TSCRC::Normal_HASH32(input);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    {
        std::locale _locale(locale_name);

        std::string input(TSTR("Привет Мир\n"));
        uint32_t output(0x1A585841);

        auto result = TSCRC::Normal_HASH32(input, _locale);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    {
        std::wstring input(L"Hello World\n");
        uint32_t output(0xB095E5E3);

        auto result = TWCRC::Normal_HASH32(input);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
#ifdef CRC_CHECK
TEST(TCRC, NormalHASH32_Generator)
{
    //
    // 1000
    //
    {
        std::size_t count(1000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<uint32_t> crc32_hash(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), crc32_hash.begin(), [](const std::string& value) -> uint32_t { return TSCRC::Normal_HASH32(value); });

        std::sort(crc32_hash.begin(), crc32_hash.end());
        crc32_hash.erase(std::unique(crc32_hash.begin(), crc32_hash.end()), crc32_hash.end());

        std::size_t collisions(rand_str.size() - crc32_hash.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

        ASSERT_LE(collisions, size_t(0));
    }
    //
    // 10000
    //
    {
        std::size_t count(10000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<uint32_t> crc32_hash(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), crc32_hash.begin(), [](const std::string& value) -> uint32_t { return TSCRC::Normal_HASH32(value); });

        std::sort(crc32_hash.begin(), crc32_hash.end());
        crc32_hash.erase(std::unique(crc32_hash.begin(), crc32_hash.end()), crc32_hash.end());

        std::size_t collisions(rand_str.size() - crc32_hash.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

        ASSERT_LE(collisions, size_t(0));
    }
    //
    // 100000
    //
    {
        std::size_t count(100000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<uint32_t> crc32_hash(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), crc32_hash.begin(), [](const std::string& value) -> uint32_t { return TSCRC::Normal_HASH32(value); });

        std::sort(crc32_hash.begin(), crc32_hash.end());
        crc32_hash.erase(std::unique(crc32_hash.begin(), crc32_hash.end()), crc32_hash.end());

        std::size_t collisions(rand_str.size() - crc32_hash.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

        ASSERT_LE(collisions, size_t(10));
    }
    //
    // 1000000
    //
    {
        std::size_t count(1000000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<uint32_t> crc32_hash(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), crc32_hash.begin(), [](const std::string& value) -> uint32_t { return TSCRC::Normal_HASH32(value); });

        std::sort(crc32_hash.begin(), crc32_hash.end());
        crc32_hash.erase(std::unique(crc32_hash.begin(), crc32_hash.end()), crc32_hash.end());

        std::size_t collisions(rand_str.size() - crc32_hash.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

        ASSERT_LE(collisions, size_t(150));
    }
}
#endif
// ---------------------------------------------------------------------------
TEST(TCRC, NormalHASH32SameCrc)
{
    {
        std::string input1("oxueekz");
        std::string input2("pyqptgs");

        auto result1 = TSCRC::Normal_HASH32(input1);
        auto result2 = TSCRC::Normal_HASH32(input2);

        ASSERT_EQ(result1, result2);
    }
    {
        std::string input1("nktteme");
        std::string input2("qjpatal");

        auto result1 = TSCRC::Normal_HASH32(input1);
        auto result2 = TSCRC::Normal_HASH32(input2);

        ASSERT_EQ(result1, result2);
    }
    {
        std::string input1("nuktjcj");
        std::string input2("bimxkml");

        auto result1 = TSCRC::Normal_HASH32(input1);
        auto result2 = TSCRC::Normal_HASH32(input2);

        ASSERT_EQ(result1, result2);
    }
    {
        std::string input1("atimtna");
        std::string input2("nfxqcvx");

        auto result1 = TSCRC::Normal_HASH32(input1);
        auto result2 = TSCRC::Normal_HASH32(input2);

        ASSERT_EQ(result1, result2);
    }
    {
        std::string input1("tgnvsia");
        std::string input2("kfjcbeh");

        auto result1 = TSCRC::Normal_HASH32(input1);
        auto result2 = TSCRC::Normal_HASH32(input2);

        ASSERT_EQ(result1, result2);
    }
}
// ---------------------------------------------------------------------------
TEST(TCRC, UPPERHASH32)
{
    //
    // TSCRC (eng)
    //
    {
        std::string input("Hello World\n");
        uint32_t output(0xCEE96B69);

        auto result = TSCRC::UPPER_HASH32(input);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWCRC (eng)
    //
    {
        std::wstring input(L"Hello World\n");
        uint32_t output(0xCEE96B69);

        auto result = TWCRC::UPPER_HASH32(input);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
// ---------------------------------------------------------------------------
#ifdef CRC_CHECK
TEST(TCRC, UPPERHASH_Generator)
{
    //
    // 1000
    //
    {
        std::size_t count(1000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count, true);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<std::size_t> hashs(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), hashs.begin(), [](const std::string& value)  { return TSCRC::UPPER_HASH(value); });

        std::sort(hashs.begin(), hashs.end());
        hashs.erase(std::unique(hashs.begin(), hashs.end()), hashs.end());

        std::size_t collisions(rand_str.size() - hashs.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

        ASSERT_EQ(collisions, size_t(0));
    }
    //
    // 10000
    //
    {
        std::size_t count(10000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count, true);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<std::size_t> hashs(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), hashs.begin(), [](const std::string& value) -> std::size_t { return TSCRC::UPPER_HASH(value); });

        std::sort(hashs.begin(), hashs.end());
        hashs.erase(std::unique(hashs.begin(), hashs.end()), hashs.end());

        std::size_t collisions(rand_str.size() - hashs.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

        ASSERT_EQ(collisions, size_t(0));
    }
    //
    // 100000
    //
    {
        std::size_t count(100000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count, true);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<std::size_t> hashs(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), hashs.begin(), [](const std::string& value) -> std::size_t { return TSCRC::UPPER_HASH(value); });

        std::sort(hashs.begin(), hashs.end());
        hashs.erase(std::unique(hashs.begin(), hashs.end()), hashs.end());

        std::size_t collisions(rand_str.size() - hashs.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

#ifdef PROJECT_IMAGE_X86
        ASSERT_LE(collisions, size_t(5));
#else
        ASSERT_EQ(collisions, size_t(0));
#endif
    }
    //
    // 1000000
    //
    {
        std::size_t count(1000000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count, true);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<std::size_t> hashs(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), hashs.begin(), [](const std::string& value) -> std::size_t { return TSCRC::UPPER_HASH(value); });

        std::sort(hashs.begin(), hashs.end());
        hashs.erase(std::unique(hashs.begin(), hashs.end()), hashs.end());

        std::size_t collisions(rand_str.size() - hashs.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

#ifdef PROJECT_IMAGE_X86
        ASSERT_LE(collisions, size_t(150));
#else
        ASSERT_EQ(collisions, size_t(0));
#endif
    }
}
#endif
// ---------------------------------------------------------------------------
#ifdef CRC_CHECK
TEST(TCRC, HASH_Generator)
{
    //
    // 1000
    //
    {
        std::size_t count(1000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<std::size_t> hashs(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), hashs.begin(), [](const std::string& value) { return TSCRC::HASH(value); });

        std::sort(hashs.begin(), hashs.end());
        hashs.erase(std::unique(hashs.begin(), hashs.end()), hashs.end());

        std::size_t collisions(rand_str.size() - hashs.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

        ASSERT_EQ(collisions, size_t(0));
    }
    //
    // 10000
    //
    {
        std::size_t count(10000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<std::size_t> hashs(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), hashs.begin(), [](const std::string& value) { return TSCRC::HASH(value); });

        std::sort(hashs.begin(), hashs.end());
        hashs.erase(std::unique(hashs.begin(), hashs.end()), hashs.end());

        std::size_t collisions(rand_str.size() - hashs.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

        ASSERT_EQ(collisions, size_t(0));
    }
    //
    // 100000
    //
    {
        std::size_t count(100000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<std::size_t> hashs(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), hashs.begin(), [](const std::string& value) { return TSCRC::HASH(value); });

        std::sort(hashs.begin(), hashs.end());
        hashs.erase(std::unique(hashs.begin(), hashs.end()), hashs.end());

        std::size_t collisions(rand_str.size() - hashs.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

#ifdef PROJECT_IMAGE_X86
        ASSERT_LE(collisions, size_t(5));
#else
        ASSERT_EQ(collisions, size_t(0));
#endif
    }
    //
    // 1000000
    //
    {
        std::size_t count(1000000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<std::size_t> hashs(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), hashs.begin(), [](const std::string& value) { return TSCRC::HASH(value); });

        std::sort(hashs.begin(), hashs.end());
        hashs.erase(std::unique(hashs.begin(), hashs.end()), hashs.end());

        std::size_t collisions(rand_str.size() - hashs.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

#ifdef PROJECT_IMAGE_X86
        ASSERT_EQ(collisions, size_t(150));
#else
        ASSERT_EQ(collisions, size_t(0));
#endif
    }
}
#endif
// ---------------------------------------------------------------------------
#ifdef CRC_CHECK
TEST(TCRC, HASH_AS_32_Generator)
{
    //
    // 1000
    //
    {
        std::size_t count(1000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<uint32_t> hashs(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), hashs.begin(), [](const std::string& value) { return static_cast<uint32_t>(TSCRC::HASH(value)); });

        std::sort(hashs.begin(), hashs.end());
        hashs.erase(std::unique(hashs.begin(), hashs.end()), hashs.end());

        std::size_t collisions(rand_str.size() - hashs.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

        ASSERT_EQ(collisions, size_t(0));
    }
    //
    // 10000
    //
    {
        std::size_t count(10000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<uint32_t> hashs(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), hashs.begin(), [](const std::string& value) { return static_cast<uint32_t>(TSCRC::HASH(value)); });

        std::sort(hashs.begin(), hashs.end());
        hashs.erase(std::unique(hashs.begin(), hashs.end()), hashs.end());

        std::size_t collisions(rand_str.size() - hashs.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

        ASSERT_EQ(collisions, size_t(0));
    }
    //
    // 100000
    //
    {
        std::size_t count(100000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<uint32_t> hashs(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), hashs.begin(), [](const std::string& value) { return static_cast<uint32_t>(TSCRC::HASH(value)); });

        std::sort(hashs.begin(), hashs.end());
        hashs.erase(std::unique(hashs.begin(), hashs.end()), hashs.end());

        std::size_t collisions(rand_str.size() - hashs.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

        ASSERT_LE(collisions, size_t(10));
    }
    //
    // 1000000
    //
    {
        std::size_t count(1000000);

        std::vector<std::string> rand_str;

        MakeRandomStrings(rand_str, count);

        ASSERT_EQ(std::size(rand_str), count);

        std::sort(rand_str.begin(), rand_str.end());

        rand_str.erase(std::unique(rand_str.begin(), rand_str.end()), rand_str.end());

        std::vector<uint32_t> hashs(std::size(rand_str), 0);

        std::transform(rand_str.begin(), rand_str.end(), hashs.begin(), [](const std::string& value) { return static_cast<uint32_t>(TSCRC::HASH(value)); });

        std::sort(hashs.begin(), hashs.end());
        hashs.erase(std::unique(hashs.begin(), hashs.end()), hashs.end());

        std::size_t collisions(rand_str.size() - hashs.size());

        std::cerr << "[          ] [ INFO ] Collisions from " << rand_str.size() << " strings: " << collisions << std::endl;

        ASSERT_LE(collisions, size_t(200));
    }
}
#endif
// ---------------------------------------------------------------------------
TEST(TCRC, InSysHASH)
{
    //
    // TSCRC (eng)
    //
    {
        std::string input("Hello World\n");
        uint32_t output(0x18E815A);

        auto result = TSCRC::InSysHASH(input);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
    //
    // TWCRC (eng)
    //
    {
        std::wstring input(L"Hello World\n");
        uint32_t output(0x18E815A);

        auto result = TWCRC::InSysHASH(input);

        ASSERT_EQ(typeid(decltype(output)), typeid(decltype(result)));
        ASSERT_EQ(output, result);
    }
}
#pragma endregion
// ---------------------------------------------------------------------------
#pragma region FileSystem
// ---------------------------------------------------------------------------
//
// Класс для тестирования методов класса TIniStringStorage
//
template <typename StorageClass> class TTestIniStorage : public StorageClass
{
public:
    using StorageClass::ini;

    uint32_t MakeHash(const std::string& value, const std::locale& loc = std::locale())
    {
        if constexpr(std::is_same<StorageClass, Framework::FileSystem::TIniHashStorage<>>::value)
        {
            return StorageClass::MakeHash(value, loc);
        }
        else
        {
            return 0;
        }
    }
};
// ---------------------------------------------------------------------------
TEST(FileSystem, TIniStringStorage_GetGroups)
{
    TTestIniStorage<Framework::FileSystem::TIniStringStorage<>> ini_string_storage;

    std::vector<std::string> strings;

    for (int i(-100); i < 101; i++)
    {
        std::string str = TSConverter::ToString(i);

        ini_string_storage.ini.push_back({ str, {} });

        strings.push_back(str);
    }

    std::vector<std::string> groups;

    ini_string_storage.GetGroups(groups);

    ASSERT_TRUE(strings == groups);
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TIniStringStorage_GetGroup_01)
{
    TTestIniStorage<Framework::FileSystem::TIniStringStorage<>> ini_string_storage;

    std::vector<std::string> strings;

    for (int i(-100); i < 101; i++)
    {
        std::string str = TSConverter::ToString(i);

        ini_string_storage.ini.push_back({ str, {} });

        strings.push_back(str);
    }

    for (size_t i(0); i < std::size(ini_string_storage.ini); i++)
    {
        ASSERT_EQ(static_cast<void*>(&ini_string_storage.ini.at(i).second), ini_string_storage.GetGroup(strings.at(i), false));
    }

    strings.clear();
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TIniStringStorage_GetGroup_02)
{
    TTestIniStorage<Framework::FileSystem::TIniStringStorage<>> ini_string_storage;

    ASSERT_TRUE(ini_string_storage.ini.empty());

    std::vector<std::string> strings;

    for (int i(-100); i < 101; i++)
    {
        std::string str = TSConverter::ToString(i);

        ASSERT_NE(ini_string_storage.GetGroup(str, true), nullptr);

        strings.push_back(str);
    }

    std::vector<std::string> groups;

    ini_string_storage.GetGroups(groups);

    ASSERT_TRUE(strings == groups);
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TIniStringStorage_GetValues)
{
    size_t size_group(10);
    size_t size_keys(100);

    TTestIniStorage<Framework::FileSystem::TIniStringStorage<>> ini_string_storage;

    for (size_t i(0); i < size_group; i++)
    {
        std::vector<std::pair<std::string, std::string>> key_value;

        for (size_t k(0); k < size_keys; k++)
        {
            std::string key = TSConverter::ToString(k);
            std::string value = TSConverter::ToString(k * 2);

            key_value.push_back( { key, value } );
        }

        std::string group = TSConverter::ToString(i);

        ini_string_storage.ini.push_back( { group, key_value } );
    }

    std::vector<std::pair<std::string, std::string>> key_value_result;

    for (size_t i(0); i < size_group; i++)
    {
        std::string group = TSConverter::ToString(i);

        void* group_handle = ini_string_storage.GetGroup(group, false);

        ASSERT_NE(group_handle, nullptr);

        ini_string_storage.GetValues(group_handle, key_value_result);

        ASSERT_EQ(std::size(key_value_result), size_keys);

        for (size_t k(0); k < std::size(key_value_result); k++)
        {
            ASSERT_EQ(key_value_result.at(k).first, TSConverter::ToString(k));
            ASSERT_EQ(key_value_result.at(k).second, TSConverter::ToString(k * 2));
        }
    }
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TIniStringStorage_GetValue)
{
    std::string* value(nullptr);

    void* group_handle(nullptr);

    TTestIniStorage<Framework::FileSystem::TIniStringStorage<>> ini_string_storage;

    std::vector<std::pair<std::string, std::string>> key_value = {
        { "Key1", "Value1" },
        { "Key2", "Value2" },
        { "Key3", "Value3" }
    };

    ini_string_storage.ini.push_back( { "Group1", key_value } );
    ini_string_storage.ini.push_back( { "Group2", key_value } );
    ini_string_storage.ini.push_back( { "Group3", key_value } );
    //
    // Group3
    //
    {
        group_handle = ini_string_storage.GetGroup("Group3", false);
        ASSERT_NE(group_handle, nullptr);

        value = ini_string_storage.GetValue(group_handle, "Key3");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value3"));

        value = ini_string_storage.GetValue(group_handle, "Key2");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value2"));

        value = ini_string_storage.GetValue(group_handle, "Key1");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value1"));

        value = ini_string_storage.GetValue(group_handle, "kEy1");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value1"));

        value = ini_string_storage.GetValue(group_handle, "key_1");
        ASSERT_EQ(value, nullptr);
    }
    //
    // Group1
    //
    {
        group_handle = ini_string_storage.GetGroup("Group1", false);
        ASSERT_NE(group_handle, nullptr);

        value = ini_string_storage.GetValue(group_handle, "Key3");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value3"));

        value = ini_string_storage.GetValue(group_handle, "Key2");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value2"));

        value = ini_string_storage.GetValue(group_handle, "Key1");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value1"));

        value = ini_string_storage.GetValue(group_handle, "kEy1");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value1"));

        value = ini_string_storage.GetValue(group_handle, "key_1");
        ASSERT_EQ(value, nullptr);
    }
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TIniStringStorage_AddValue)
{
    TTestIniStorage<Framework::FileSystem::TIniStringStorage<>> ini_string_storage;

    void* group_handle =  ini_string_storage.GetGroup("Group1", true);

    ASSERT_NE(group_handle, nullptr);

    ini_string_storage.AddValue(group_handle, "Key1", "Value1");
    ini_string_storage.AddValue(group_handle, "Key2", "Value2");

    ini_string_storage.AddValue(group_handle, "Key1", "Value1");
    ini_string_storage.AddValue(group_handle, "Key2", "Value2");

    group_handle =  ini_string_storage.GetGroup("Group2", true);

    ini_string_storage.AddValue(group_handle, "Key1", "Value1");
    ini_string_storage.AddValue(group_handle, "Key2", "Value2");

    ASSERT_EQ(ini_string_storage.ini.size(), 2);

    ASSERT_EQ(ini_string_storage.ini.at(0).first, std::string("Group1"));
    ASSERT_EQ(ini_string_storage.ini.at(1).first, std::string("Group2"));
    //
    // Group1
    //
    ASSERT_EQ(ini_string_storage.ini.at(0).second.size(), 4);

    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(0).first, std::string("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(0).second, std::string("Value1"));

    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(1).first, std::string("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(1).second, std::string("Value2"));

    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(2).first, std::string("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(2).second, std::string("Value1"));

    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(3).first, std::string("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(3).second, std::string("Value2"));
    //
    // Group2
    //
    ASSERT_EQ(ini_string_storage.ini.at(1).second.size(), 2);

    ASSERT_EQ(ini_string_storage.ini.at(1).second.at(0).first, std::string("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(1).second.at(0).second, std::string("Value1"));

    ASSERT_EQ(ini_string_storage.ini.at(1).second.at(1).first, std::string("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(1).second.at(1).second, std::string("Value2"));
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TIniStringStorage_MergeValue)
{
    TTestIniStorage<Framework::FileSystem::TIniStringStorage<>> ini_string_storage;

    void* group_handle =  ini_string_storage.GetGroup("Group1", true);

    ASSERT_NE(group_handle, nullptr);

    ASSERT_EQ(ini_string_storage.ini.size(), 1);
    ASSERT_EQ(ini_string_storage.ini.at(0).first, std::string("Group1"));

    ini_string_storage.MergeValue(group_handle, "Key1", "Value1");
    ini_string_storage.MergeValue(group_handle, "Key2", "Value2");

    ASSERT_EQ(ini_string_storage.ini.at(0).second.size(), 2);

    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(0).first, std::string("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(0).second, std::string("Value1"));

    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(1).first, std::string("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(1).second, std::string("Value2"));

    ini_string_storage.MergeValue(group_handle, "Key1", "Value10");
    ini_string_storage.MergeValue(group_handle, "Key2", "Value20");

    ASSERT_EQ(ini_string_storage.ini.at(0).second.size(), 2);

    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(0).first, std::string("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(0).second, std::string("Value10"));

    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(1).first, std::string("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(0).second.at(1).second, std::string("Value20"));
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TIniHashStorage_GetGroups)
{
    TTestIniStorage<Framework::FileSystem::TIniHashStorage<>> ini_string_storage;

    std::vector<std::string> strings;

    for (int i(-100); i < 101; i++)
    {
        std::string str = TSConverter::ToString(i);

        ini_string_storage.ini.push_back({ str, ini_string_storage.MakeHash(str), {} });

        strings.push_back(str);
    }

    std::vector<std::string> groups;

    ini_string_storage.GetGroups(groups);

    ASSERT_TRUE(strings == groups);
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TIniHashStorage_GetGroup_01)
{
    TTestIniStorage<Framework::FileSystem::TIniHashStorage<>> ini_string_storage;

    std::vector<std::string> strings;

    for (int i(-100); i < 101; i++)
    {
        std::string str = TSConverter::ToString(i);

        ini_string_storage.ini.push_back({ str, ini_string_storage.MakeHash(str), {} });

        strings.push_back(str);
    }

    for (size_t i(0); i < std::size(ini_string_storage.ini); i++)
    {
        ASSERT_EQ(static_cast<void*>(&ini_string_storage.ini.at(i).key_value_list), ini_string_storage.GetGroup(strings.at(i), false));
    }

    strings.clear();
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TIniHashStorage_GetGroup_02)
{
    TTestIniStorage<Framework::FileSystem::TIniHashStorage<>> ini_string_storage;

    ASSERT_TRUE(ini_string_storage.ini.empty());

    std::vector<std::string> strings;

    for (int i(-100); i < 101; i++)
    {
        std::string str = TSConverter::ToString(i);

        ASSERT_NE(ini_string_storage.GetGroup(str, true), nullptr);

        strings.push_back(str);
    }

    std::vector<std::string> groups;

    ini_string_storage.GetGroups(groups);

    ASSERT_TRUE(strings == groups);
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TIniHashStorage_GetValues)
{
    TTestIniStorage<Framework::FileSystem::TIniHashStorage<>> ini_string_storage;

    ini_string_storage.ini.push_back(
        {
            "0", ini_string_storage.MakeHash("0"),
            {
                { "0", ini_string_storage.MakeHash("0"), "0" },
                { "1", ini_string_storage.MakeHash("1"), "2" },
                { "2", ini_string_storage.MakeHash("2"), "4" },
                { "3", ini_string_storage.MakeHash("3"), "6" },
                { "4", ini_string_storage.MakeHash("4"), "8" },
                { "5", ini_string_storage.MakeHash("5"), "10" }
            }
        }
    );

    ini_string_storage.ini.push_back(
        {
            "1", ini_string_storage.MakeHash("1"),
            {
                { "0", ini_string_storage.MakeHash("0"), "0" },
                { "1", ini_string_storage.MakeHash("1"), "2" },
                { "2", ini_string_storage.MakeHash("2"), "4" },
                { "3", ini_string_storage.MakeHash("3"), "6" },
                { "4", ini_string_storage.MakeHash("4"), "8" },
                { "5", ini_string_storage.MakeHash("5"), "10" }
            }
        }
    );

    std::vector<std::pair<std::string, std::string>> key_value_result;

    for (size_t i(0); i < 2; i++)
    {
        std::string group = TSConverter::ToString(i);

        void* group_handle = ini_string_storage.GetGroup(group, false);

        ASSERT_NE(group_handle, nullptr);

        ini_string_storage.GetValues(group_handle, key_value_result);

        ASSERT_EQ(std::size(key_value_result), 6);

        for (size_t k(0); k < 6; k++)
        {
            ASSERT_EQ(key_value_result.at(k).first, TSConverter::ToString(k));
            ASSERT_EQ(key_value_result.at(k).second, TSConverter::ToString(k * 2));
        }
    }
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TIniHashStorage_GetValue)
{
    std::string* value(nullptr);

    void* group_handle(nullptr);

    TTestIniStorage<Framework::FileSystem::TIniHashStorage<>> ini_string_storage;

    ini_string_storage.ini.push_back(
        {
            "Group1", ini_string_storage.MakeHash("Group1"),
            {
                { "Key1", ini_string_storage.MakeHash("Key1"), "Value1" },
                { "Key2", ini_string_storage.MakeHash("Key2"), "Value2" },
                { "Key3", ini_string_storage.MakeHash("Key3"), "Value3" }
            }
        }
    );

    ini_string_storage.ini.push_back(
        {
            "Group2", ini_string_storage.MakeHash("Group2"),
            {
                { "Key1", ini_string_storage.MakeHash("Key1"), "Value1" },
                { "Key2", ini_string_storage.MakeHash("Key2"), "Value2" },
                { "Key3", ini_string_storage.MakeHash("Key3"), "Value3" }
            }
        }
    );

    ini_string_storage.ini.push_back(
        {
            "Group3", ini_string_storage.MakeHash("Group3"),
            {
                { "Key1", ini_string_storage.MakeHash("Key1"), "Value1" },
                { "Key2", ini_string_storage.MakeHash("Key2"), "Value2" },
                { "Key3", ini_string_storage.MakeHash("Key3"), "Value3" }
            }
        }
    );
    //
    // Group3
    //
    {
        group_handle = ini_string_storage.GetGroup("Group3", false);
        ASSERT_NE(group_handle, nullptr);

        value = ini_string_storage.GetValue(group_handle, "Key3");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value3"));

        value = ini_string_storage.GetValue(group_handle, "Key2");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value2"));

        value = ini_string_storage.GetValue(group_handle, "Key1");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value1"));

        value = ini_string_storage.GetValue(group_handle, "kEy1");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value1"));

        value = ini_string_storage.GetValue(group_handle, "key_1");
        ASSERT_EQ(value, nullptr);
    }
    //
    // Group1
    //
    {
        group_handle = ini_string_storage.GetGroup("Group1", false);
        ASSERT_NE(group_handle, nullptr);

        value = ini_string_storage.GetValue(group_handle, "Key3");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value3"));

        value = ini_string_storage.GetValue(group_handle, "Key2");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value2"));

        value = ini_string_storage.GetValue(group_handle, "Key1");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value1"));

        value = ini_string_storage.GetValue(group_handle, "kEy1");
        ASSERT_NE(value, nullptr);
        ASSERT_EQ(*value, std::string("Value1"));

        value = ini_string_storage.GetValue(group_handle, "key_1");
        ASSERT_EQ(value, nullptr);
    }
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TIniHashStorage_AddValue)
{
    TTestIniStorage<Framework::FileSystem::TIniHashStorage<>> ini_string_storage;

    void* group_handle =  ini_string_storage.GetGroup("Group1", true);

    ASSERT_NE(group_handle, nullptr);

    ini_string_storage.AddValue(group_handle, "Key1", "Value1");
    ini_string_storage.AddValue(group_handle, "Key2", "Value2");

    ini_string_storage.AddValue(group_handle, "Key1", "Value1");
    ini_string_storage.AddValue(group_handle, "Key2", "Value2");

    group_handle =  ini_string_storage.GetGroup("Group2", true);

    ini_string_storage.AddValue(group_handle, "Key1", "Value1");
    ini_string_storage.AddValue(group_handle, "Key2", "Value2");

    ASSERT_EQ(ini_string_storage.ini.size(), 2);

    ASSERT_EQ(ini_string_storage.ini.at(0).name, std::string("Group1"));
    ASSERT_EQ(ini_string_storage.ini.at(0).hash, ini_string_storage.MakeHash("Group1"));
    ASSERT_EQ(ini_string_storage.ini.at(1).name, std::string("Group2"));
    ASSERT_EQ(ini_string_storage.ini.at(1).hash, ini_string_storage.MakeHash("Group2"));
    //
    // Group1
    //
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.size(), 4);

    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(0).name, std::string("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(0).hash, ini_string_storage.MakeHash("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(0).value, std::string("Value1"));

    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(1).name, std::string("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(1).hash, ini_string_storage.MakeHash("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(1).value, std::string("Value2"));

    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(2).name, std::string("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(2).hash, ini_string_storage.MakeHash("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(2).value, std::string("Value1"));

    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(3).name, std::string("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(3).hash, ini_string_storage.MakeHash("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(3).value, std::string("Value2"));
    //
    // Group2
    //
    ASSERT_EQ(ini_string_storage.ini.at(1).key_value_list.size(), 2);

    ASSERT_EQ(ini_string_storage.ini.at(1).key_value_list.at(0).name, std::string("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(1).key_value_list.at(0).hash, ini_string_storage.MakeHash("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(1).key_value_list.at(0).value, std::string("Value1"));

    ASSERT_EQ(ini_string_storage.ini.at(1).key_value_list.at(1).name, std::string("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(1).key_value_list.at(1).hash, ini_string_storage.MakeHash("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(1).key_value_list.at(1).value, std::string("Value2"));
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TIniHashStorage_MergeValue)
{
    TTestIniStorage<Framework::FileSystem::TIniHashStorage<>> ini_string_storage;

    void* group_handle =  ini_string_storage.GetGroup("Group1", true);

    ASSERT_NE(group_handle, nullptr);

    ASSERT_EQ(ini_string_storage.ini.size(), 1);
    ASSERT_EQ(ini_string_storage.ini.at(0).name, std::string("Group1"));
    ASSERT_EQ(ini_string_storage.ini.at(0).hash, ini_string_storage.MakeHash("Group1"));

    ini_string_storage.MergeValue(group_handle, "Key1", "Value1");
    ini_string_storage.MergeValue(group_handle, "Key2", "Value2");

    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.size(), 2);

    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(0).name, std::string("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(0).hash, ini_string_storage.MakeHash("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(0).value, std::string("Value1"));

    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(1).name, std::string("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(1).hash, ini_string_storage.MakeHash("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(1).value, std::string("Value2"));

    ini_string_storage.MergeValue(group_handle, "Key1", "Value10");
    ini_string_storage.MergeValue(group_handle, "Key2", "Value20");

    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.size(), 2);

    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(0).name, std::string("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(0).hash, ini_string_storage.MakeHash("Key1"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(0).value, std::string("Value10"));

    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(1).name, std::string("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(1).hash, ini_string_storage.MakeHash("Key2"));
    ASSERT_EQ(ini_string_storage.ini.at(0).key_value_list.at(1).value, std::string("Value20"));
}
// ---------------------------------------------------------------------------
//
// Класс для тестирования методов класса TIniBase
//
template <typename T, typename StorageClass> class TTestIniBase : public Framework::FileSystem::TIniBase<T, StorageClass>
{
public:
    using Framework::FileSystem::TIniBase<T, StorageClass>::base_interface;
};
// ---------------------------------------------------------------------------
TEST(FileSystem, TSIniBase_GetGroups)
{
    //
    // TIniStringStorage
    //
    {
        TTestIniBase<std::string, Framework::FileSystem::TIniStringStorage<std::string>> ini_base;

        ini_base.base_interface->GetGroup("Group1", true, std::locale());
        ini_base.base_interface->GetGroup("Group2", true, std::locale());
        ini_base.base_interface->GetGroup("Group3", true, std::locale());

        std::vector<std::string> groups;

        ini_base.GetGroups(groups);

        ASSERT_EQ(groups.size(), 3);
        ASSERT_EQ(groups.at(0), std::string("Group1"));
        ASSERT_EQ(groups.at(1), std::string("Group2"));
        ASSERT_EQ(groups.at(2), std::string("Group3"));
    }
    //
    // TIniHashStorage
    //
    {
        TTestIniBase<std::string, Framework::FileSystem::TIniHashStorage<std::string>> ini_base;

        ini_base.base_interface->GetGroup("Group1", true, std::locale());
        ini_base.base_interface->GetGroup("Group2", true, std::locale());
        ini_base.base_interface->GetGroup("Group3", true, std::locale());

        std::vector<std::string> groups;

        ini_base.GetGroups(groups);

        ASSERT_EQ(groups.size(), 3);
        ASSERT_EQ(groups.at(0), std::string("Group1"));
        ASSERT_EQ(groups.at(1), std::string("Group2"));
        ASSERT_EQ(groups.at(2), std::string("Group3"));
    }
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TWIniBase_GetGroups)
{
    //
    // TIniStringStorage
    //
    {
        TTestIniBase<std::wstring, Framework::FileSystem::TIniStringStorage<std::wstring>> ini_base;

        ini_base.base_interface->GetGroup("Group1", true, std::locale());
        ini_base.base_interface->GetGroup("Group2", true, std::locale());
        ini_base.base_interface->GetGroup("Group3", true, std::locale());

        std::vector<std::wstring> groups;

        ini_base.GetGroups(groups);

        ASSERT_EQ(groups.size(), 3);
        ASSERT_EQ(groups.at(0), std::wstring(L"Group1"));
        ASSERT_EQ(groups.at(1), std::wstring(L"Group2"));
        ASSERT_EQ(groups.at(2), std::wstring(L"Group3"));
    }
    //
    // TIniHashStorage
    //
    {
        TTestIniBase<std::wstring, Framework::FileSystem::TIniHashStorage<std::wstring>> ini_base;

        ini_base.base_interface->GetGroup("Group1", true, std::locale());
        ini_base.base_interface->GetGroup("Group2", true, std::locale());
        ini_base.base_interface->GetGroup("Group3", true, std::locale());

        std::vector<std::wstring> groups;

        ini_base.GetGroups(groups);

        ASSERT_EQ(groups.size(), 3);
        ASSERT_EQ(groups.at(0), std::wstring(L"Group1"));
        ASSERT_EQ(groups.at(1), std::wstring(L"Group2"));
        ASSERT_EQ(groups.at(2), std::wstring(L"Group3"));
    }
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TSIniBase_GetValues)
{
    void* group_handle(nullptr);
    //
    // TIniStringStorage
    //
    {
        TTestIniBase<std::string, Framework::FileSystem::TIniStringStorage<std::string>> ini_base;

        group_handle = ini_base.base_interface->GetGroup("Group1", true, std::locale());
        ASSERT_NE(group_handle, nullptr);
        ini_base.base_interface->MergeValue(group_handle, "Key1", "value1", std::locale());
        ini_base.base_interface->MergeValue(group_handle, "Key2", "value2", std::locale());

        group_handle = ini_base.base_interface->GetGroup("Group2", true, std::locale());
        ASSERT_NE(group_handle, nullptr);
        ini_base.base_interface->MergeValue(group_handle, "Key3", "value3", std::locale());
        ini_base.base_interface->MergeValue(group_handle, "Key4", "value4", std::locale());

        std::vector<std::pair<std::string, std::string>> key_value;

        ASSERT_TRUE(ini_base.GetValues("Group1", key_value));
        ASSERT_EQ(key_value.size(), 2);
        ASSERT_EQ(key_value.at(0).first, std::string("Key1"));
        ASSERT_EQ(key_value.at(0).second, std::string("value1"));
        ASSERT_EQ(key_value.at(1).first, std::string("Key2"));
        ASSERT_EQ(key_value.at(1).second, std::string("value2"));

        ASSERT_TRUE(ini_base.GetValues("Group2", key_value));
        ASSERT_EQ(key_value.size(), 2);
        ASSERT_EQ(key_value.at(0).first, std::string("Key3"));
        ASSERT_EQ(key_value.at(0).second, std::string("value3"));
        ASSERT_EQ(key_value.at(1).first, std::string("Key4"));
        ASSERT_EQ(key_value.at(1).second, std::string("value4"));

        ASSERT_FALSE(ini_base.GetValues("Group10", key_value));
    }
    //
    // TIniHashStorage
    //
    {
        TTestIniBase<std::string, Framework::FileSystem::TIniHashStorage<std::string>> ini_base;

        group_handle = ini_base.base_interface->GetGroup("Group1", true, std::locale());
        ASSERT_NE(group_handle, nullptr);
        ini_base.base_interface->MergeValue(group_handle, "Key1", "value1", std::locale());
        ini_base.base_interface->MergeValue(group_handle, "Key2", "value2", std::locale());

        group_handle = ini_base.base_interface->GetGroup("Group2", true, std::locale());
        ASSERT_NE(group_handle, nullptr);
        ini_base.base_interface->MergeValue(group_handle, "Key3", "value3", std::locale());
        ini_base.base_interface->MergeValue(group_handle, "Key4", "value4", std::locale());

        std::vector<std::pair<std::string, std::string>> key_value;

        ASSERT_TRUE(ini_base.GetValues("Group1", key_value));
        ASSERT_EQ(key_value.size(), 2);
        ASSERT_EQ(key_value.at(0).first, std::string("Key1"));
        ASSERT_EQ(key_value.at(0).second, std::string("value1"));
        ASSERT_EQ(key_value.at(1).first, std::string("Key2"));
        ASSERT_EQ(key_value.at(1).second, std::string("value2"));

        ASSERT_TRUE(ini_base.GetValues("Group2", key_value));
        ASSERT_EQ(key_value.size(), 2);
        ASSERT_EQ(key_value.at(0).first, std::string("Key3"));
        ASSERT_EQ(key_value.at(0).second, std::string("value3"));
        ASSERT_EQ(key_value.at(1).first, std::string("Key4"));
        ASSERT_EQ(key_value.at(1).second, std::string("value4"));

        ASSERT_FALSE(ini_base.GetValues("Group10", key_value));
    }
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TWIniBase_GetValues)
{
    void* group_handle(nullptr);
    //
    // TIniStringStorage
    //
    {
        TTestIniBase<std::wstring, Framework::FileSystem::TIniStringStorage<std::wstring>> ini_base;

        group_handle = ini_base.base_interface->GetGroup("Group1", true, std::locale());
        ASSERT_NE(group_handle, nullptr);
        ini_base.base_interface->MergeValue(group_handle, "Key1", "value1", std::locale());
        ini_base.base_interface->MergeValue(group_handle, "Key2", "value2", std::locale());

        group_handle = ini_base.base_interface->GetGroup("Group2", true, std::locale());
        ASSERT_NE(group_handle, nullptr);
        ini_base.base_interface->MergeValue(group_handle, "Key3", "value3", std::locale());
        ini_base.base_interface->MergeValue(group_handle, "Key4", "value4", std::locale());

        std::vector<std::pair<std::wstring, std::wstring>> key_value;

        ASSERT_TRUE(ini_base.GetValues(L"Group1", key_value));
        ASSERT_EQ(key_value.size(), 2);
        ASSERT_EQ(key_value.at(0).first, std::wstring(L"Key1"));
        ASSERT_EQ(key_value.at(0).second, std::wstring(L"value1"));
        ASSERT_EQ(key_value.at(1).first, std::wstring(L"Key2"));
        ASSERT_EQ(key_value.at(1).second, std::wstring(L"value2"));

        ASSERT_TRUE(ini_base.GetValues(L"Group2", key_value));
        ASSERT_EQ(key_value.size(), 2);
        ASSERT_EQ(key_value.at(0).first, std::wstring(L"Key3"));
        ASSERT_EQ(key_value.at(0).second, std::wstring(L"value3"));
        ASSERT_EQ(key_value.at(1).first, std::wstring(L"Key4"));
        ASSERT_EQ(key_value.at(1).second, std::wstring(L"value4"));

        ASSERT_FALSE(ini_base.GetValues(L"Group10", key_value));
    }
    //
    // TIniHashStorage
    //
    {
        TTestIniBase<std::wstring, Framework::FileSystem::TIniHashStorage<std::wstring>> ini_base;

        group_handle = ini_base.base_interface->GetGroup("Group1", true, std::locale());
        ASSERT_NE(group_handle, nullptr);
        ini_base.base_interface->MergeValue(group_handle, "Key1", "value1", std::locale());
        ini_base.base_interface->MergeValue(group_handle, "Key2", "value2", std::locale());

        group_handle = ini_base.base_interface->GetGroup("Group2", true, std::locale());
        ASSERT_NE(group_handle, nullptr);
        ini_base.base_interface->MergeValue(group_handle, "Key3", "value3", std::locale());
        ini_base.base_interface->MergeValue(group_handle, "Key4", "value4", std::locale());

        std::vector<std::pair<std::wstring, std::wstring>> key_value;

        ASSERT_TRUE(ini_base.GetValues(L"Group1", key_value));
        ASSERT_EQ(key_value.size(), 2);
        ASSERT_EQ(key_value.at(0).first, std::wstring(L"Key1"));
        ASSERT_EQ(key_value.at(0).second, std::wstring(L"value1"));
        ASSERT_EQ(key_value.at(1).first, std::wstring(L"Key2"));
        ASSERT_EQ(key_value.at(1).second, std::wstring(L"value2"));

        ASSERT_TRUE(ini_base.GetValues(L"Group2", key_value));
        ASSERT_EQ(key_value.size(), 2);
        ASSERT_EQ(key_value.at(0).first, std::wstring(L"Key3"));
        ASSERT_EQ(key_value.at(0).second, std::wstring(L"value3"));
        ASSERT_EQ(key_value.at(1).first, std::wstring(L"Key4"));
        ASSERT_EQ(key_value.at(1).second, std::wstring(L"value4"));

        ASSERT_FALSE(ini_base.GetValues(L"Group10", key_value));
    }
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TSIniBase_GetValue)
{
    void* group_handle(nullptr);
    //
    // TIniStringStorage
    //
    {
        TTestIniBase<std::string, Framework::FileSystem::TIniStringStorage<std::string>> ini_base;

        group_handle = ini_base.base_interface->GetGroup("Group1", true, std::locale());
        ASSERT_NE(group_handle, nullptr);

        ini_base.base_interface->MergeValue(group_handle, "uint8_t", TSConverter::ToString(std::numeric_limits<uint8_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "uint16_t", TSConverter::ToString(std::numeric_limits<uint16_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "uint32_t", TSConverter::ToString(std::numeric_limits<uint32_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "uint64_t", TSConverter::ToString(std::numeric_limits<uint64_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int8_t", TSConverter::ToString(std::numeric_limits<int8_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int16_t", TSConverter::ToString(std::numeric_limits<int16_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int32_t", TSConverter::ToString(std::numeric_limits<int32_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int64_t", TSConverter::ToString(std::numeric_limits<int64_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "float", TSConverter::ToString(std::numeric_limits<float>::max(), std::locale(), std::numeric_limits<float>::max_digits10), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "double", TSConverter::ToString(std::numeric_limits<double>::max(), std::locale(), std::numeric_limits<double>::max_digits10), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "string", "Hello World", std::locale());
        ini_base.base_interface->MergeValue(group_handle, "path", "c:\\Test\\Test.exe", std::locale());

        ASSERT_EQ(ini_base.GetValue<uint8_t>("Group1", "uint8_t", 0), std::numeric_limits<uint8_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint16_t>("Group1", "uint16_t", 0), std::numeric_limits<uint16_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint32_t>("Group1", "uint32_t", 0), std::numeric_limits<uint32_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint64_t>("Group1", "uint64_t", 0), std::numeric_limits<uint64_t>::max());
        ASSERT_EQ(ini_base.GetValue<int8_t>("Group1", "int8_t", 0), std::numeric_limits<int8_t>::min());
        ASSERT_EQ(ini_base.GetValue<int16_t>("Group1", "int16_t", 0), std::numeric_limits<int16_t>::min());
        ASSERT_EQ(ini_base.GetValue<int32_t>("Group1", "int32_t", 0), std::numeric_limits<int32_t>::min());
        ASSERT_EQ(ini_base.GetValue<int64_t>("Group1", "int64_t", 0), std::numeric_limits<int64_t>::min());
        ASSERT_FLOAT_EQ(ini_base.GetValue<float>("Group1", "float", 0.0), std::numeric_limits<float>::max());
        ASSERT_DOUBLE_EQ(ini_base.GetValue<double>("Group1", "double", 0.0), std::numeric_limits<double>::max());
        ASSERT_EQ(ini_base.GetValue<std::string>("Group1", "string", ""), std::string("Hello World"));
        ASSERT_EQ(ini_base.GetValue<std::wstring>("Group1", "string", L""), std::wstring(L"Hello World"));
        ASSERT_EQ(ini_base.GetValue("Group1", "path", stdfs::path()), stdfs::path("c:\\Test\\Test.exe"));

        ASSERT_EQ(ini_base.GetValue("Group1", "path_temp", uint8_t(100)), uint8_t(100));
    }
    //
    // TIniHashStorage
    //
    {
        TTestIniBase<std::string, Framework::FileSystem::TIniHashStorage<std::string>> ini_base;

        group_handle = ini_base.base_interface->GetGroup("Group1", true, std::locale());
        ASSERT_NE(group_handle, nullptr);

        ini_base.base_interface->MergeValue(group_handle, "uint8_t", TSConverter::ToString(std::numeric_limits<uint8_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "uint16_t", TSConverter::ToString(std::numeric_limits<uint16_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "uint32_t", TSConverter::ToString(std::numeric_limits<uint32_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "uint64_t", TSConverter::ToString(std::numeric_limits<uint64_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int8_t", TSConverter::ToString(std::numeric_limits<int8_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int16_t", TSConverter::ToString(std::numeric_limits<int16_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int32_t", TSConverter::ToString(std::numeric_limits<int32_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int64_t", TSConverter::ToString(std::numeric_limits<int64_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "float", TSConverter::ToString(std::numeric_limits<float>::max(), std::locale(), std::numeric_limits<float>::max_digits10), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "double", TSConverter::ToString(std::numeric_limits<double>::max(), std::locale(), std::numeric_limits<double>::max_digits10), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "string", "Hello World", std::locale());
        ini_base.base_interface->MergeValue(group_handle, "path", "c:\\Test\\Test.exe", std::locale());

        ASSERT_EQ(ini_base.GetValue<uint8_t>("Group1", "uint8_t", 0), std::numeric_limits<uint8_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint16_t>("Group1", "uint16_t", 0), std::numeric_limits<uint16_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint32_t>("Group1", "uint32_t", 0), std::numeric_limits<uint32_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint64_t>("Group1", "uint64_t", 0), std::numeric_limits<uint64_t>::max());
        ASSERT_EQ(ini_base.GetValue<int8_t>("Group1", "int8_t", 0), std::numeric_limits<int8_t>::min());
        ASSERT_EQ(ini_base.GetValue<int16_t>("Group1", "int16_t", 0), std::numeric_limits<int16_t>::min());
        ASSERT_EQ(ini_base.GetValue<int32_t>("Group1", "int32_t", 0), std::numeric_limits<int32_t>::min());
        ASSERT_EQ(ini_base.GetValue<int64_t>("Group1", "int64_t", 0), std::numeric_limits<int64_t>::min());
        ASSERT_FLOAT_EQ(ini_base.GetValue<float>("Group1", "float", 0.0), std::numeric_limits<float>::max());
        ASSERT_DOUBLE_EQ(ini_base.GetValue<double>("Group1", "double", 0.0), std::numeric_limits<double>::max());
        ASSERT_EQ(ini_base.GetValue<std::string>("Group1", "string", ""), std::string("Hello World"));
        ASSERT_EQ(ini_base.GetValue<std::wstring>("Group1", "string", L""), std::wstring(L"Hello World"));
        ASSERT_EQ(ini_base.GetValue("Group1", "path", stdfs::path()), stdfs::path("c:\\Test\\Test.exe"));

        ASSERT_EQ(ini_base.GetValue("Group1", "path_temp", uint8_t(100)), uint8_t(100));
    }
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TWIniBase_GetValue)
{
    void* group_handle(nullptr);
    //
    // TIniStringStorage
    //
    {
        TTestIniBase<std::wstring, Framework::FileSystem::TIniStringStorage<std::wstring>> ini_base;

        group_handle = ini_base.base_interface->GetGroup("Group1", true, std::locale());
        ASSERT_NE(group_handle, nullptr);

        ini_base.base_interface->MergeValue(group_handle, "uint8_t", TSConverter::ToString(std::numeric_limits<uint8_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "uint16_t", TSConverter::ToString(std::numeric_limits<uint16_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "uint32_t", TSConverter::ToString(std::numeric_limits<uint32_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "uint64_t", TSConverter::ToString(std::numeric_limits<uint64_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int8_t", TSConverter::ToString(std::numeric_limits<int8_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int16_t", TSConverter::ToString(std::numeric_limits<int16_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int32_t", TSConverter::ToString(std::numeric_limits<int32_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int64_t", TSConverter::ToString(std::numeric_limits<int64_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "float", TSConverter::ToString(std::numeric_limits<float>::max(), std::locale(), std::numeric_limits<float>::max_digits10), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "double", TSConverter::ToString(std::numeric_limits<double>::max(), std::locale(), std::numeric_limits<double>::max_digits10), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "string", "Hello World", std::locale());
        ini_base.base_interface->MergeValue(group_handle, "path", "c:\\Test\\Test.exe", std::locale());

        ASSERT_EQ(ini_base.GetValue<uint8_t>(L"Group1", L"uint8_t", 0), std::numeric_limits<uint8_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint16_t>(L"Group1", L"uint16_t", 0), std::numeric_limits<uint16_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint32_t>(L"Group1", L"uint32_t", 0), std::numeric_limits<uint32_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint64_t>(L"Group1", L"uint64_t", 0), std::numeric_limits<uint64_t>::max());
        ASSERT_EQ(ini_base.GetValue<int8_t>(L"Group1", L"int8_t", 0), std::numeric_limits<int8_t>::min());
        ASSERT_EQ(ini_base.GetValue<int16_t>(L"Group1", L"int16_t", 0), std::numeric_limits<int16_t>::min());
        ASSERT_EQ(ini_base.GetValue<int32_t>(L"Group1", L"int32_t", 0), std::numeric_limits<int32_t>::min());
        ASSERT_EQ(ini_base.GetValue<int64_t>(L"Group1", L"int64_t", 0), std::numeric_limits<int64_t>::min());
        ASSERT_FLOAT_EQ(ini_base.GetValue<float>(L"Group1", L"float", 0.0), std::numeric_limits<float>::max());
        ASSERT_DOUBLE_EQ(ini_base.GetValue<double>(L"Group1", L"double", 0.0), std::numeric_limits<double>::max());
        ASSERT_EQ(ini_base.GetValue<std::string>(L"Group1", L"string", ""), std::string("Hello World"));
        ASSERT_EQ(ini_base.GetValue<std::wstring>(L"Group1", L"string", L""), std::wstring(L"Hello World"));
        ASSERT_EQ(ini_base.GetValue(L"Group1", L"path", stdfs::path()), stdfs::path(L"c:\\Test\\Test.exe"));

        ASSERT_EQ(ini_base.GetValue(L"Group1", L"path_temp", uint8_t(100)), uint8_t(100));
    }
    //
    // TIniHashStorage
    //
    {
        TTestIniBase<std::wstring, Framework::FileSystem::TIniHashStorage<std::wstring>> ini_base;

        group_handle = ini_base.base_interface->GetGroup("Group1", true, std::locale());
        ASSERT_NE(group_handle, nullptr);

        ini_base.base_interface->MergeValue(group_handle, "uint8_t", TSConverter::ToString(std::numeric_limits<uint8_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "uint16_t", TSConverter::ToString(std::numeric_limits<uint16_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "uint32_t", TSConverter::ToString(std::numeric_limits<uint32_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "uint64_t", TSConverter::ToString(std::numeric_limits<uint64_t>::max(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int8_t", TSConverter::ToString(std::numeric_limits<int8_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int16_t", TSConverter::ToString(std::numeric_limits<int16_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int32_t", TSConverter::ToString(std::numeric_limits<int32_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "int64_t", TSConverter::ToString(std::numeric_limits<int64_t>::min(), std::locale()), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "float", TSConverter::ToString(std::numeric_limits<float>::max(), std::locale(), std::numeric_limits<float>::max_digits10), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "double", TSConverter::ToString(std::numeric_limits<double>::max(), std::locale(), std::numeric_limits<double>::max_digits10), std::locale());
        ini_base.base_interface->MergeValue(group_handle, "string", "Hello World", std::locale());
        ini_base.base_interface->MergeValue(group_handle, "path", "c:\\Test\\Test.exe", std::locale());

        ASSERT_EQ(ini_base.GetValue<uint8_t>(L"Group1", L"uint8_t", 0), std::numeric_limits<uint8_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint16_t>(L"Group1", L"uint16_t", 0), std::numeric_limits<uint16_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint32_t>(L"Group1", L"uint32_t", 0), std::numeric_limits<uint32_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint64_t>(L"Group1", L"uint64_t", 0), std::numeric_limits<uint64_t>::max());
        ASSERT_EQ(ini_base.GetValue<int8_t>(L"Group1", L"int8_t", 0), std::numeric_limits<int8_t>::min());
        ASSERT_EQ(ini_base.GetValue<int16_t>(L"Group1", L"int16_t", 0), std::numeric_limits<int16_t>::min());
        ASSERT_EQ(ini_base.GetValue<int32_t>(L"Group1", L"int32_t", 0), std::numeric_limits<int32_t>::min());
        ASSERT_EQ(ini_base.GetValue<int64_t>(L"Group1", L"int64_t", 0), std::numeric_limits<int64_t>::min());
        ASSERT_FLOAT_EQ(ini_base.GetValue<float>(L"Group1", L"float", 0.0), std::numeric_limits<float>::max());
        ASSERT_DOUBLE_EQ(ini_base.GetValue<double>(L"Group1", L"double", 0.0), std::numeric_limits<double>::max());
        ASSERT_EQ(ini_base.GetValue<std::string>(L"Group1", L"string", ""), std::string("Hello World"));
        ASSERT_EQ(ini_base.GetValue<std::wstring>(L"Group1", L"string", L""), std::wstring(L"Hello World"));
        ASSERT_EQ(ini_base.GetValue(L"Group1", L"path", stdfs::path()), stdfs::path(L"c:\\Test\\Test.exe"));

        ASSERT_EQ(ini_base.GetValue(L"Group1", L"path_temp", uint8_t(100)), uint8_t(100));
    }
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TSIniBase_SetValue)
{
    void* group_handle(nullptr);
    //
    // TIniStringStorage
    //
    {
        TTestIniBase<std::string, Framework::FileSystem::TIniStringStorage<std::string>> ini_base;

        ini_base.SetValue("Group1", "uint8_t", std::numeric_limits<uint8_t>::max());
        ini_base.SetValue("Group1", "uint16_t", std::numeric_limits<uint16_t>::max());
        ini_base.SetValue("Group1", "uint32_t", std::numeric_limits<uint32_t>::max());
        ini_base.SetValue("Group1", "uint64_t", std::numeric_limits<uint64_t>::max());
        ini_base.SetValue("Group1", "int8_t", std::numeric_limits<int8_t>::min());
        ini_base.SetValue("Group1", "int16_t", std::numeric_limits<int16_t>::min());
        ini_base.SetValue("Group1", "int32_t", std::numeric_limits<int32_t>::min());
        ini_base.SetValue("Group1", "int64_t", std::numeric_limits<int64_t>::min());
        ini_base.SetValue("Group1", "float1", std::numeric_limits<float>::max());
        ini_base.SetValue("Group1", "float2", float(1.5));
        ini_base.SetValue("Group1", "double1", std::numeric_limits<double>::max());
        ini_base.SetValue("Group1", "double2", double(0.05));
        ini_base.SetValue("Group1", "string", std::string("Hello World"));
        ini_base.SetValue("Group1", "string", std::wstring(L"Hello World"));
        ini_base.SetValue("Group1", "path", stdfs::path("c:\\Test\\Test.exe"));

        ASSERT_EQ(ini_base.GetValue<uint8_t>("Group1", "uint8_t", 0), std::numeric_limits<uint8_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint16_t>("Group1", "uint16_t", 0), std::numeric_limits<uint16_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint32_t>("Group1", "uint32_t", 0), std::numeric_limits<uint32_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint64_t>("Group1", "uint64_t", 0), std::numeric_limits<uint64_t>::max());
        ASSERT_EQ(ini_base.GetValue<int8_t>("Group1", "int8_t", 0), std::numeric_limits<int8_t>::min());
        ASSERT_EQ(ini_base.GetValue<int16_t>("Group1", "int16_t", 0), std::numeric_limits<int16_t>::min());
        ASSERT_EQ(ini_base.GetValue<int32_t>("Group1", "int32_t", 0), std::numeric_limits<int32_t>::min());
        ASSERT_EQ(ini_base.GetValue<int64_t>("Group1", "int64_t", 0), std::numeric_limits<int64_t>::min());
        ASSERT_FLOAT_EQ(ini_base.GetValue<float>("Group1", "float1", 0.0), std::numeric_limits<float>::max());
        ASSERT_FLOAT_EQ(ini_base.GetValue<float>("Group1", "float2", 0.0), float(1.5));
        ASSERT_DOUBLE_EQ(ini_base.GetValue<double>("Group1", "double1", 0.0), std::numeric_limits<double>::max());
        ASSERT_DOUBLE_EQ(ini_base.GetValue<double>("Group1", "double2", 0.0), double(0.05));
        ASSERT_EQ(ini_base.GetValue<std::string>("Group1", "string", ""), std::string("Hello World"));
        ASSERT_EQ(ini_base.GetValue<std::wstring>("Group1", "string", L""), std::wstring(L"Hello World"));
        ASSERT_EQ(ini_base.GetValue("Group1", "path", stdfs::path()), stdfs::path("c:\\Test\\Test.exe"));
    }
    //
    // TIniHashStorage
    //
    {
        TTestIniBase<std::string, Framework::FileSystem::TIniHashStorage<std::string>> ini_base;

        ini_base.SetValue("Group1", "uint8_t", std::numeric_limits<uint8_t>::max());
        ini_base.SetValue("Group1", "uint16_t", std::numeric_limits<uint16_t>::max());
        ini_base.SetValue("Group1", "uint32_t", std::numeric_limits<uint32_t>::max());
        ini_base.SetValue("Group1", "uint64_t", std::numeric_limits<uint64_t>::max());
        ini_base.SetValue("Group1", "int8_t", std::numeric_limits<int8_t>::min());
        ini_base.SetValue("Group1", "int16_t", std::numeric_limits<int16_t>::min());
        ini_base.SetValue("Group1", "int32_t", std::numeric_limits<int32_t>::min());
        ini_base.SetValue("Group1", "int64_t", std::numeric_limits<int64_t>::min());
        ini_base.SetValue("Group1", "float1", std::numeric_limits<float>::max());
        ini_base.SetValue("Group1", "float2", float(1.5));
        ini_base.SetValue("Group1", "double1", std::numeric_limits<double>::max());
        ini_base.SetValue("Group1", "double2", double(0.05));
        ini_base.SetValue("Group1", "string", std::string("Hello World"));
        ini_base.SetValue("Group1", "string", std::wstring(L"Hello World"));
        ini_base.SetValue("Group1", "path", stdfs::path("c:\\Test\\Test.exe"));

        ASSERT_EQ(ini_base.GetValue<uint8_t>("Group1", "uint8_t", 0), std::numeric_limits<uint8_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint16_t>("Group1", "uint16_t", 0), std::numeric_limits<uint16_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint32_t>("Group1", "uint32_t", 0), std::numeric_limits<uint32_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint64_t>("Group1", "uint64_t", 0), std::numeric_limits<uint64_t>::max());
        ASSERT_EQ(ini_base.GetValue<int8_t>("Group1", "int8_t", 0), std::numeric_limits<int8_t>::min());
        ASSERT_EQ(ini_base.GetValue<int16_t>("Group1", "int16_t", 0), std::numeric_limits<int16_t>::min());
        ASSERT_EQ(ini_base.GetValue<int32_t>("Group1", "int32_t", 0), std::numeric_limits<int32_t>::min());
        ASSERT_EQ(ini_base.GetValue<int64_t>("Group1", "int64_t", 0), std::numeric_limits<int64_t>::min());
        ASSERT_FLOAT_EQ(ini_base.GetValue<float>("Group1", "float1", 0.0), std::numeric_limits<float>::max());
        ASSERT_FLOAT_EQ(ini_base.GetValue<float>("Group1", "float2", 0.0), float(1.5));
        ASSERT_DOUBLE_EQ(ini_base.GetValue<double>("Group1", "double1", 0.0), std::numeric_limits<double>::max());
        ASSERT_DOUBLE_EQ(ini_base.GetValue<double>("Group1", "double2", 0.0), double(0.05));
        ASSERT_EQ(ini_base.GetValue<std::string>("Group1", "string", ""), std::string("Hello World"));
        ASSERT_EQ(ini_base.GetValue<std::wstring>("Group1", "string", L""), std::wstring(L"Hello World"));
        ASSERT_EQ(ini_base.GetValue("Group1", "path", stdfs::path()), stdfs::path("c:\\Test\\Test.exe"));
    }
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TWIniBase_SetValue)
{
    void* group_handle(nullptr);
    //
    // TIniStringStorage
    //
    {
        TTestIniBase<std::wstring, Framework::FileSystem::TIniStringStorage<std::wstring>> ini_base;

        ini_base.SetValue(L"Group1", L"uint8_t", std::numeric_limits<uint8_t>::max());
        ini_base.SetValue(L"Group1", L"uint16_t", std::numeric_limits<uint16_t>::max());
        ini_base.SetValue(L"Group1", L"uint32_t", std::numeric_limits<uint32_t>::max());
        ini_base.SetValue(L"Group1", L"uint64_t", std::numeric_limits<uint64_t>::max());
        ini_base.SetValue(L"Group1", L"int8_t", std::numeric_limits<int8_t>::min());
        ini_base.SetValue(L"Group1", L"int16_t", std::numeric_limits<int16_t>::min());
        ini_base.SetValue(L"Group1", L"int32_t", std::numeric_limits<int32_t>::min());
        ini_base.SetValue(L"Group1", L"int64_t", std::numeric_limits<int64_t>::min());
        ini_base.SetValue(L"Group1", L"float1", std::numeric_limits<float>::max());
        ini_base.SetValue(L"Group1", L"float2", float(1.5));
        ini_base.SetValue(L"Group1", L"double1", std::numeric_limits<double>::max());
        ini_base.SetValue(L"Group1", L"double2", double(0.05));
        ini_base.SetValue(L"Group1", L"string", std::string("Hello World"));
        ini_base.SetValue(L"Group1", L"string", std::wstring(L"Hello World"));
        ini_base.SetValue(L"Group1", L"path", stdfs::path("c:\\Test\\Test.exe"));

        ASSERT_EQ(ini_base.GetValue<uint8_t>(L"Group1", L"uint8_t", 0), std::numeric_limits<uint8_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint16_t>(L"Group1", L"uint16_t", 0), std::numeric_limits<uint16_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint32_t>(L"Group1", L"uint32_t", 0), std::numeric_limits<uint32_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint64_t>(L"Group1", L"uint64_t", 0), std::numeric_limits<uint64_t>::max());
        ASSERT_EQ(ini_base.GetValue<int8_t>(L"Group1", L"int8_t", 0), std::numeric_limits<int8_t>::min());
        ASSERT_EQ(ini_base.GetValue<int16_t>(L"Group1", L"int16_t", 0), std::numeric_limits<int16_t>::min());
        ASSERT_EQ(ini_base.GetValue<int32_t>(L"Group1", L"int32_t", 0), std::numeric_limits<int32_t>::min());
        ASSERT_EQ(ini_base.GetValue<int64_t>(L"Group1", L"int64_t", 0), std::numeric_limits<int64_t>::min());
        ASSERT_FLOAT_EQ(ini_base.GetValue<float>(L"Group1", L"float1", 0.0), std::numeric_limits<float>::max());
        ASSERT_FLOAT_EQ(ini_base.GetValue<float>(L"Group1", L"float2", 0.0), float(1.5));
        ASSERT_DOUBLE_EQ(ini_base.GetValue<double>(L"Group1", L"double1", 0.0), std::numeric_limits<double>::max());
        ASSERT_DOUBLE_EQ(ini_base.GetValue<double>(L"Group1", L"double2", 0.0), double(0.05));
        ASSERT_EQ(ini_base.GetValue<std::string>(L"Group1", L"string", ""), std::string("Hello World"));
        ASSERT_EQ(ini_base.GetValue<std::wstring>(L"Group1", L"string", L""), std::wstring(L"Hello World"));
        ASSERT_EQ(ini_base.GetValue(L"Group1", L"path", stdfs::path()), stdfs::path("c:\\Test\\Test.exe"));
    }
    //
    // TIniHashStorage
    //
    {
        TTestIniBase<std::wstring, Framework::FileSystem::TIniHashStorage<std::wstring>> ini_base;

        ini_base.SetValue(L"Group1", L"uint8_t", std::numeric_limits<uint8_t>::max());
        ini_base.SetValue(L"Group1", L"uint16_t", std::numeric_limits<uint16_t>::max());
        ini_base.SetValue(L"Group1", L"uint32_t", std::numeric_limits<uint32_t>::max());
        ini_base.SetValue(L"Group1", L"uint64_t", std::numeric_limits<uint64_t>::max());
        ini_base.SetValue(L"Group1", L"int8_t", std::numeric_limits<int8_t>::min());
        ini_base.SetValue(L"Group1", L"int16_t", std::numeric_limits<int16_t>::min());
        ini_base.SetValue(L"Group1", L"int32_t", std::numeric_limits<int32_t>::min());
        ini_base.SetValue(L"Group1", L"int64_t", std::numeric_limits<int64_t>::min());
        ini_base.SetValue(L"Group1", L"float1", std::numeric_limits<float>::max());
        ini_base.SetValue(L"Group1", L"float2", float(1.5));
        ini_base.SetValue(L"Group1", L"double1", std::numeric_limits<double>::max());
        ini_base.SetValue(L"Group1", L"double2", double(0.05));
        ini_base.SetValue(L"Group1", L"string", std::string("Hello World"));
        ini_base.SetValue(L"Group1", L"string", std::wstring(L"Hello World"));
        ini_base.SetValue(L"Group1", L"path", stdfs::path("c:\\Test\\Test.exe"));

        ASSERT_EQ(ini_base.GetValue<uint8_t>(L"Group1", L"uint8_t", 0), std::numeric_limits<uint8_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint16_t>(L"Group1", L"uint16_t", 0), std::numeric_limits<uint16_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint32_t>(L"Group1", L"uint32_t", 0), std::numeric_limits<uint32_t>::max());
        ASSERT_EQ(ini_base.GetValue<uint64_t>(L"Group1", L"uint64_t", 0), std::numeric_limits<uint64_t>::max());
        ASSERT_EQ(ini_base.GetValue<int8_t>(L"Group1", L"int8_t", 0), std::numeric_limits<int8_t>::min());
        ASSERT_EQ(ini_base.GetValue<int16_t>(L"Group1", L"int16_t", 0), std::numeric_limits<int16_t>::min());
        ASSERT_EQ(ini_base.GetValue<int32_t>(L"Group1", L"int32_t", 0), std::numeric_limits<int32_t>::min());
        ASSERT_EQ(ini_base.GetValue<int64_t>(L"Group1", L"int64_t", 0), std::numeric_limits<int64_t>::min());
        ASSERT_FLOAT_EQ(ini_base.GetValue<float>(L"Group1", L"float1", 0.0), std::numeric_limits<float>::max());
        ASSERT_FLOAT_EQ(ini_base.GetValue<float>(L"Group1", L"float2", 0.0), float(1.5));
        ASSERT_DOUBLE_EQ(ini_base.GetValue<double>(L"Group1", L"double1", 0.0), std::numeric_limits<double>::max());
        ASSERT_DOUBLE_EQ(ini_base.GetValue<double>(L"Group1", L"double2", 0.0), double(0.05));
        ASSERT_EQ(ini_base.GetValue<std::string>(L"Group1", L"string", ""), std::string("Hello World"));
        ASSERT_EQ(ini_base.GetValue<std::wstring>(L"Group1", L"string", L""), std::wstring(L"Hello World"));
        ASSERT_EQ(ini_base.GetValue(L"Group1", L"path", stdfs::path()), stdfs::path("c:\\Test\\Test.exe"));
    }
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TSIniReader)
{
    std::string error;
    stdfs::path _path(stdfs::current_path().append("TSIniReader.ini"));

    if (stdfs::exists(_path))
    {
        stdfs::remove(_path);
    }

    std::string buffer = Framework::String::TStringFormater::Format(
        "[LMZ_SERVER]\nXmlPath={0}\nMultiOrOneTh={1}\nViewFrequency={2}\n[TEST]\nString={3}\nWString={4}\nDouble={5}", 
        _path.string(), false, 10, "Hello World", L"Hello World", 10.545
    );

    if (std::ofstream _file(_path.string(), std::ios::out | std::ios::trunc); _file.is_open())
    {
        _file << buffer;
        _file.close();
    }

    Framework::FileSystem::TIniReader<std::string> ini_reader;

    ASSERT_TRUE(ini_reader.Parse(_path, error));

    ASSERT_EQ(ini_reader.GetValue("LMZ_SERVER", "XmlPath", stdfs::current_path()), _path);
    ASSERT_FALSE(ini_reader.GetValue("LMZ_SERVER", "MultiOrOneTh", true));
    ASSERT_EQ(ini_reader.GetValue("LMZ_SERVER", "ViewFrequency", int32_t(0)), 10);
    ASSERT_EQ(ini_reader.GetValue("TEST", "String", std::string()), std::string("Hello World"));
    ASSERT_EQ(ini_reader.GetValue("TEST", "WString", std::wstring()), std::wstring(L"Hello World"));
    ASSERT_DOUBLE_EQ(ini_reader.GetValue("TEST", "Double", double(0)), double(10.545));

    ASSERT_TRUE(stdfs::exists(_path));

    if (stdfs::exists(_path))
    {
        stdfs::remove(_path);
    }

    ASSERT_FALSE(stdfs::exists(_path));
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TSIniReaderWithComments)
{
    std::string error;
    stdfs::path _path(stdfs::current_path().append("TSIniReader.ini"));

    if (stdfs::exists(_path))
    {
        stdfs::remove(_path);
    }

    std::string buffer = Framework::String::TStringFormater::Format(
        "#Секция параметров\n[LMZ_SERVER]\n#Путь к XML файлу\nXmlPath={0}\nMultiOrOneTh={1} ; Включена многопоточность \nViewFrequency={2} # Частота обновления интерфейса\n[TEST]\nString={3}\nWString={4}\nDouble={5}", 
        _path.string(), false, 10, "Hello World", L"Hello World", 10.545
    );

    if (std::ofstream _file(_path.string(), std::ios::out | std::ios::trunc); _file.is_open())
    {
        _file << buffer;
        _file.close();
    }

    Framework::FileSystem::TIniReader<std::string> ini_reader;

    ASSERT_TRUE(ini_reader.Parse(_path, error));

    ASSERT_EQ(ini_reader.GetValue("LMZ_SERVER", "XmlPath", stdfs::current_path()), _path);
    ASSERT_FALSE(ini_reader.GetValue("LMZ_SERVER", "MultiOrOneTh", true));
    ASSERT_EQ(ini_reader.GetValue("LMZ_SERVER", "ViewFrequency", int32_t(0)), 10);
    ASSERT_EQ(ini_reader.GetValue("TEST", "String", std::string()), std::string("Hello World"));
    ASSERT_EQ(ini_reader.GetValue("TEST", "WString", std::wstring()), std::wstring(L"Hello World"));
    ASSERT_DOUBLE_EQ(ini_reader.GetValue("TEST", "Double", double(0)), double(10.545));

    ASSERT_TRUE(stdfs::exists(_path));

    if (stdfs::exists(_path))
    {
        stdfs::remove(_path);
    }

    ASSERT_FALSE(stdfs::exists(_path));
}
// ---------------------------------------------------------------------------
TEST(FileSystem, BadTSIniReader)
{
    std::string error;
    stdfs::path _path(stdfs::current_path().append("BadTSIniWriterTSIniReader.ini"));

    if (stdfs::exists(_path))
    {
        stdfs::remove(_path);
    }

    std::string buffer = Framework::String::TStringFormater::Format("[LMZ_SERVER]\nXmlPath={0}\nLogPath={1}\nValuesPath", _path.string(), false);

    if (std::ofstream _file(_path.string(), std::ios::out | std::ios::trunc); _file.is_open())
    {
        _file << buffer;
        _file.close();
    }

    Framework::FileSystem::TIniReader<std::string> ini_reader;

    ASSERT_FALSE(ini_reader.Parse(_path, error));

    ASSERT_TRUE(stdfs::exists(_path));

    if (stdfs::exists(_path))
    {
        stdfs::remove(_path);
    }

    ASSERT_FALSE(stdfs::exists(_path));
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TSIniWriterTSIniReader)
{
    stdfs::path _path(stdfs::current_path().append("stemp.ini"));

    if (stdfs::exists(_path))
    {
        stdfs::remove(_path);
    }

    std::string error;
    Framework::FileSystem::TIniWriter<std::string> ini_writer;

    ini_writer.SetValue("LMZ_SERVER", "XmlPath", _path);
    ini_writer.SetValue("LMZ_SERVER", "MultiOrOneTh", false);
    ini_writer.SetValue("LMZ_SERVER", "ViewFrequency", 10);
    ini_writer.SetValue("TEST", "String", "Hello World");
    ini_writer.SetValue("TEST", "WString", L"Hello World");
    ini_writer.SetValue("TEST", "Double", 10.545);

    ASSERT_TRUE(ini_writer.Write(_path, error));

    Framework::FileSystem::TIniReader<std::string> ini_reader;

    ASSERT_TRUE(ini_reader.Parse(_path, error));

    ASSERT_EQ(ini_reader.GetValue("LMZ_SERVER", "XmlPath", stdfs::current_path()), _path);
    ASSERT_FALSE(ini_reader.GetValue("LMZ_SERVER", "MultiOrOneTh", true));
    ASSERT_EQ(ini_reader.GetValue("LMZ_SERVER", "ViewFrequency", int32_t(0)), 10);
    ASSERT_EQ(ini_reader.GetValue("TEST", "String", std::string()), std::string("Hello World"));
    ASSERT_EQ(ini_reader.GetValue("TEST", "WString", std::wstring()), std::wstring(L"Hello World"));
    ASSERT_DOUBLE_EQ(ini_reader.GetValue("TEST", "Double", double(0)), double(10.545));

    ASSERT_TRUE(stdfs::exists(_path));

    if (stdfs::exists(_path))
    {
        stdfs::remove(_path);
    }

    ASSERT_FALSE(stdfs::exists(_path));
}
// ---------------------------------------------------------------------------
TEST(FileSystem, TWIniWriterTWIniReader)
{
    stdfs::path _path(stdfs::current_path().append("wtemp.ini"));

    if (stdfs::exists(_path))
    {
        stdfs::remove(_path);
    }

    std::wstring error;
    Framework::FileSystem::TIniWriter<std::wstring> ini_writer;

    ini_writer.SetValue(L"LMZ_SERVER", L"XmlPath", _path);
    ini_writer.SetValue(L"LMZ_SERVER", L"MultiOrOneTh", false);
    ini_writer.SetValue(L"LMZ_SERVER", L"ViewFrequency", 10);
    ini_writer.SetValue(L"TEST", L"String", "Hello World");
    ini_writer.SetValue(L"TEST", L"WString", L"Hello World");
    ini_writer.SetValue(L"TEST", L"Double", 10.545);

    ASSERT_TRUE(ini_writer.Write(_path, error));

    Framework::FileSystem::TIniReader<std::wstring> ini_reader;

    ASSERT_TRUE(ini_reader.Parse(_path, error));

    ASSERT_EQ(ini_reader.GetValue(L"LMZ_SERVER", L"XmlPath", stdfs::current_path()), _path);
    ASSERT_FALSE(ini_reader.GetValue(L"LMZ_SERVER", L"MultiOrOneTh", true));
    ASSERT_EQ(ini_reader.GetValue(L"LMZ_SERVER", L"ViewFrequency", int32_t(0)), 10);
    ASSERT_EQ(ini_reader.GetValue(L"TEST", L"String", std::string()), std::string("Hello World"));
    ASSERT_EQ(ini_reader.GetValue(L"TEST", L"WString", std::wstring()), std::wstring(L"Hello World"));
    ASSERT_DOUBLE_EQ(ini_reader.GetValue(L"TEST", L"Double", double(0)), double(10.545));

    ASSERT_TRUE(stdfs::exists(_path));

    if (stdfs::exists(_path))
    {
        stdfs::remove(_path);
    }

    ASSERT_FALSE(stdfs::exists(_path));
}
#pragma endregion
// ---------------------------------------------------------------------------
