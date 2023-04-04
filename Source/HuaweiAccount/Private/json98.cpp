/****************************************************************************
 Copyright (c) 2015-2016 Nite Luo
 Licensed under the MIT License <http://opensource.org/licenses/MIT>.

 For issues and features please visit

 https://github.com/darkdukey/simple-json

 ****************************************************************************/
#include "json98.h"
#include <stdio.h>
#include <stdlib.h>
#include "assert.h"

using namespace std;

namespace json
{

#define MAX_DEPTH 100
#define MAX_DIGITS 15

    Json Json::nul_json;

    int Json::int_value() const
    {
        return (int)_d;
    }

    int Json::int_value(int v) const
    {
        if (is_null())
        {
            return v;
        }

        return int_value();
    }

    long Json::long_value() const
    {
        return (long)_d;
    }

    long Json::long_value(long v) const
    {
        if (is_null())
        {
            return v;
        }

        return long_value();
    }

    bool Json::bool_value() const
    {
        return _b;
    }

    bool Json::bool_value(bool v) const
    {
        if (is_null())
        {
            return v;
        }

        return bool_value();
    }

    float Json::float_value() const
    {
        return (float)_d;
    }

    float Json::float_value(float v) const
    {
        if (is_null())
        {
            return v;
        }

        return float_value();
    }

    double Json::double_value() const
    {
        return _d;
    }

    double Json::double_value(double v) const
    {
        if (is_null())
        {
            return v;
        }

        return double_value();
    }

    const Json::string_type &Json::string_value() const
    {
        return _s;
    }

    const Json::string_type &Json::string_value(const Json::string_type &v) const
    {
        if (is_null())
        {
            return v;
        }

        return string_value();
    }

    const Json::array_type &Json::array_items() const
    {
        return _a;
    }

    const Json::object_type &Json::object_items() const
    {
        return _o;
    }

    string encode(const string &value)
    {
        string out = "\"";
        for (size_t i = 0; i < value.length(); i++)
        {
            const char ch = value[i];
            if (ch == '\\')
            {
                out += "\\\\";
            }
            else if (ch == '"')
            {
                out += "\\\"";
            }
            else if (ch == '\b')
            {
                out += "\\b";
            }
            else if (ch == '\f')
            {
                out += "\\f";
            }
            else if (ch == '\n')
            {
                out += "\\n";
            }
            else if (ch == '\r')
            {
                out += "\\r";
            }
            else if (ch == '\t')
            {
                out += "\\t";
            }
            else if (static_cast<uint8_t>(ch) <= 0x1f)
            {
                char buf[8];
                snprintf(buf, sizeof buf, "\\u%04x", ch);
                out += buf;
            }
            else if (static_cast<uint8_t>(ch) == 0xe2 && static_cast<uint8_t>(value[i + 1]) == 0x80 && static_cast<uint8_t>(value[i + 2]) == 0xa8)
            {
                out += "\\u2028";
                i += 2;
            }
            else if (static_cast<uint8_t>(ch) == 0xe2 && static_cast<uint8_t>(value[i + 1]) == 0x80 && static_cast<uint8_t>(value[i + 2]) == 0xa9)
            {
                out += "\\u2029";
                i += 2;
            }
            else
            {
                out += ch;
            }
        }
        out += "\"";

        return out;
    }

    const Json::string_type Json::dump() const
    {
        char buf[100];
        switch (type())
        {
        case NUL:
            return "null";
        case INT:
            snprintf(buf, sizeof(buf), "%d", int_value());
            return buf;
        case NUMBER:
            snprintf(buf, sizeof(buf), "%f", float_value());
            return buf;
        case BOOL:
            return _b ? "true" : "false";
        case STRING:
            return encode(_s);
        case ARRAY:
        {
            Json::string_type s("[");
            const Json::array_type &a = _a;
            for (Json::array_type::const_iterator it = a.begin(); it != a.end(); ++it)
            {
                const Json &j = *it;
                s += j.dump() + ",";
            }
            size_t l = s.length();
            if (s[l - 1] == ',')
                s = s.substr(0, l - 1);
            s.push_back(']');
            return s;
        }
        case OBJECT:
        {
            Json::string_type s("{");
            const Json::object_type &o = _o;
            for (Json::object_type::const_iterator it = o.begin(); it != o.end(); ++it)
            {
                const Json::string_type &k = (*it).first;
                const Json &j = (*it).second;
                s += "\"" + k + "\":" + j.dump() + ",";
            }
            size_t l = s.length();
            if (s[l - 1] == ',')
                s = s.substr(0, l - 1);
            s.push_back('}');
            return s;
        }
        default:
            return ""; // not use these for now
        }
    }

    const Json &Json::operator[](size_t i) const
    {
        return _a[i];
    }

    Json &Json::operator[](size_t i)
    {
        return _a[i];
    }

    const Json &Json::operator[](const string &key) const
    {
        auto it = _o.find(key);
        return it == _o.end() ? nul_json : (*it).second;
    }

    Json &Json::operator[](const std::string &key)
    {
        if (is_null())
        {
            _type = OBJECT;
        }

        auto it = _o.find(key);
        if (it == _o.end())
        {
            _o[key] = nul_json;
        }

        return _o[key];
    }

    //
    // Parser
    //

    struct JsonParser
    {
        JsonParser(const Json::string_type &in)
            : i(0), str(in), err(), failed(false)
        {
        }

        Json::string_type fail(const Json::string_type &msg)
        {
            if (!failed)
                err = msg;
            failed = true;
            return Json::string_type(msg);
        }

        template <typename T>
        T fail(const Json::string_type &msg, const T &err_ret)
        {
            if (!failed)
                err = msg;
            failed = true;
            return err_ret;
        }

        Json::string_type esc(char c)
        {
            char buf[12];
            if (static_cast<uint8_t>(c) >= 0x20 && static_cast<uint8_t>(c) <= 0x7f)
            {
                snprintf(buf, sizeof buf, "'%c' (%d)", c, c);
            }
            else
            {
                snprintf(buf, sizeof buf, "(%d)", c);
            }
            return Json::string_type(buf);
        }

        bool in_range(long x, long lower, long upper)
        {
            return (x >= lower && x <= upper);
        }

        void consume_whitespace()
        {
            const size_t count = str.size();
            while (i < count && (str[i] == ' ' || str[i] == '\r' || str[i] == '\n' || str[i] == '\t'))
                i++;
        }

        char get_next_token()
        {
            consume_whitespace();
            if (i == str.size())
                return fail("unexpected end of input", 0);

            return str[i++];
        }

        void encode_utf8(long pt, Json::string_type &out)
        {
            if (pt < 0)
                return;

            if (pt < 0x80)
            {
                out += pt;
            }
            else if (pt < 0x800)
            {
                out += (pt >> 6) | 0xC0;
                out += (pt & 0x3F) | 0x80;
            }
            else if (pt < 0x10000)
            {
                out += (pt >> 12) | 0xE0;
                out += ((pt >> 6) & 0x3F) | 0x80;
                out += (pt & 0x3F) | 0x80;
            }
            else
            {
                out += (pt >> 18) | 0xF0;
                out += ((pt >> 12) & 0x3F) | 0x80;
                out += ((pt >> 6) & 0x3F) | 0x80;
                out += (pt & 0x3F) | 0x80;
            }
        }

        Json::string_type parse_string()
        {
            Json::string_type out;
            long last_escaped_codepoint = -1;

            while (true)
            {
                if (i == str.size())
                    return fail("unexpected end of input in string");

                char ch = str[i++];

                if (ch == '"')
                {
                    encode_utf8(last_escaped_codepoint, out);
                    return out;
                }

                if (in_range(ch, 0, 0x1f))
                    return fail("unescaped " + esc(ch) + " in string");

                // The usual case: non-escaped characters
                if (ch != '\\')
                {
                    encode_utf8(last_escaped_codepoint, out);
                    last_escaped_codepoint = -1;
                    out += ch;
                    continue;
                }

                // Handle escapes
                if (i == str.size())
                    return fail("unexpected end of input in string");

                ch = str[i++];

                if (ch == 'u')
                {
                    // Extract 4-byte escape sequence
                    Json::string_type esc = str.substr(i, 4);
                    for (int j = 0; j < 4; j++)
                    {
                        if (!in_range(esc[j], 'a', 'f') && !in_range(esc[j], 'A', 'F') && !in_range(esc[j], '0', '9'))
                            return fail("bad \\u escape: " + esc);
                    }

                    long codepoint = strtol(esc.data(), NULL, 16);

                    // JSON specifies that characters outside the BMP shall be encoded as a pair
                    // of 4-hex-digit \u escapes encoding their surrogate pair components. Check
                    // whether we're in the middle of such a beast: the previous codepoint was an
                    // escaped lead (high) surrogate, and this is a trail (low) surrogate.
                    if (in_range(last_escaped_codepoint, 0xD800, 0xDBFF) && in_range(codepoint, 0xDC00, 0xDFFF))
                    {
                        // Reassemble the two surrogate pairs into one astral-plane character, per
                        // the UTF-16 algorithm.
                        encode_utf8((((last_escaped_codepoint - 0xD800) << 10) | (codepoint - 0xDC00)) + 0x10000, out);
                        last_escaped_codepoint = -1;
                    }
                    else
                    {
                        encode_utf8(last_escaped_codepoint, out);
                        last_escaped_codepoint = codepoint;
                    }

                    i += 4;
                    continue;
                }

                encode_utf8(last_escaped_codepoint, out);
                last_escaped_codepoint = -1;

                if (ch == 'b')
                {
                    out += '\b';
                }
                else if (ch == 'f')
                {
                    out += '\f';
                }
                else if (ch == 'n')
                {
                    out += '\n';
                }
                else if (ch == 'r')
                {
                    out += '\r';
                }
                else if (ch == 't')
                {
                    out += '\t';
                }
                else if (ch == '"' || ch == '\\' || ch == '/')
                {
                    out += ch;
                }
                else
                {
                    return fail("invalid escape character " + esc(ch));
                }
            }
        }

        Json parse_number()
        {
            size_t start_pos = i;

            if (str[i] == '-')
                i++;

            // Integer part
            if (str[i] == '0')
            {
                i++;
                if (in_range(str[i], '0', '9'))
                    return fail("leading 0s not permitted in numbers");
            }
            else if (in_range(str[i], '1', '9'))
            {
                i++;
                while (in_range(str[i], '0', '9'))
                    i++;
            }
            else
            {
                return fail("invalid " + esc(str[i]) + " in number");
            }

            if (str[i] != '.' && str[i] != 'e' && str[i] != 'E' && (i - start_pos) <= MAX_DIGITS)
            {
                return Json(strtod(str.c_str() + start_pos, nullptr));
            }

            // Decimal part
            if (str[i] == '.')
            {
                i++;
                if (!in_range(str[i], '0', '9'))
                    return fail("at least one digit required in fractional part");

                while (in_range(str[i], '0', '9'))
                    i++;
            }

            // Exponent part
            if (str[i] == 'e' || str[i] == 'E')
            {
                i++;

                if (str[i] == '+' || str[i] == '-')
                    i++;

                if (!in_range(str[i], '0', '9'))
                    return fail("at least one digit required in exponent");

                while (in_range(str[i], '0', '9'))
                    i++;
            }

            float v;
            sscanf(str.c_str() + start_pos, "%f", &v);
            return v;

            // return utils::atof(str.c_str() + start_pos);
        }

        Json expect(const Json::string_type &expected, Json res)
        {
            assert(i != 0);
            i--;
            if (str.compare(i, expected.length(), expected) == 0)
            {
                i += expected.length();
                return res;
            }
            else
            {
                return fail("parse error: expected " + expected + ", got " + str.substr(i, expected.length()));
            }
        }

        Json parse_json(int depth)
        {
            if (depth > MAX_DEPTH)
            {
                return fail("exceeded maximum nesting depth");
            }

            char ch = get_next_token();
            if (failed)
                return Json();

            if (ch == '-' || (ch >= '0' && ch <= '9'))
            {
                i--;
                return parse_number();
            }

            if (ch == 't')
                return expect("true", true);

            if (ch == 'f')
                return expect("false", false);

            if (ch == 'n')
                return expect("null", Json());

            if (ch == '"')
                return parse_string();

            if (ch == '{')
            {
                Json::object_type data;
                ch = get_next_token();
                if (ch == '}')
                    return data;

                while (1)
                {
                    if (ch != '"')
                        return fail("expected '\"' in object, got " + esc(ch));

                    Json::string_type key = parse_string();
                    if (failed)
                        return Json();

                    ch = get_next_token();
                    if (ch != ':')
                        return fail("expected ':' in object, got " + esc(ch));

                    data[key] = parse_json(depth + 1);
                    if (failed)
                        return Json();

                    ch = get_next_token();
                    if (ch == '}')
                        break;
                    if (ch != ',')
                        return fail("expected ',' in object, got " + esc(ch));

                    ch = get_next_token();
                }
                return data;
            }

            if (ch == '[')
            {
                Json::array_type data;
                ch = get_next_token();
                if (ch == ']')
                    return data;

                while (1)
                {
                    i--;
                    data.push_back(parse_json(depth + 1));
                    if (failed)
                        return Json();

                    ch = get_next_token();
                    if (ch == ']')
                        break;
                    if (ch != ',')
                        return fail("expected ',' in list, got " + esc(ch));

                    ch = get_next_token();
                    (void)ch;
                }
                return data;
            }

            return fail("expected value, got " + esc(ch));
        }

        /* State
         */
        size_t i;
        Json::string_type str;
        Json::string_type err;
        bool failed;
    };

    const Json &Json::JsonAtPath(const std::string &path) const
    {

        using namespace std;

        string s = path;
        if (s.empty())
            return Json::nul_json;

        vector<string> components;

        const char c = '/';
        string::size_type i = 0;
        string::size_type j = s.find(c);

        if (j == string::npos)
        {
            components.push_back(s);
        }
        else
            while (j != string::npos)
            {
                components.push_back(s.substr(i, j - i));
                i = ++j;
                j = s.find(c, j);

                if (j == string::npos)
                    components.push_back(s.substr(i, s.length()));
            }

        auto last = components.back();
        components.pop_back();

        const Json *element = this;
        for (vector<string>::iterator it = components.begin(); it != components.end(); ++it)
        {
            std::string &ch = *it;
            const Json &json = (*element)[ch];
            if (json.type() == Json::NUL)
            {
                // _LOGE("Json", "getJsonAtPath: failed to find %s in path %s\n", c.c_str(), path.c_str());
                return Json::nul_json;
            }
            element = &json;
        }

        return (*element)[last];
    }

    //
    // Parse
    //

    Json Json::parse(const Json::string_type &in)
    {
        JsonParser parser(in);
        Json result = parser.parse_json(0);

        // Check for any trailing garbage
        parser.consume_whitespace();

        if (parser.i != in.size())
        {
            // TODO create a error message json
            // return parser.fail("unexpected trailing " + parser.esc(in[parser.i]));
            result.set_valid(false);
        }

        return result;
    }

}
