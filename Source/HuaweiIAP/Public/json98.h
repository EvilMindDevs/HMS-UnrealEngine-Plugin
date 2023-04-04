
/****************************************************************************
 Copyright (c) 2015-2016 Nite Luo
 Licensed under the MIT License <http://opensource.org/licenses/MIT>.

 For issues and features please visit

 https://github.com/darkdukey/simple-json

 ****************************************************************************/

#ifndef _JSON_98_H_
#define _JSON_98_H_

#include <string>
#include <vector>
#include <map>

// 0x00 HI ME LO
// 00   01 00 00
#define JSON_98_VERSION 0x00010000

namespace json98
{

    class Json
    {
    public:
        typedef std::string string_type;
        typedef std::vector<Json> array_type;
        typedef std::map<string_type, Json> object_type;

        enum Type
        {
            NUL,
            INT,
            NUMBER,
            BOOL,
            STRING,
            ARRAY,
            OBJECT
        };

        Json()
            : _type(NUL), _valid(true) {}

        Json(std::nullptr_t)
            : _type(NUL), _valid(true) {}

        Json(int i)
            : _type(INT), _d(i), _valid(true) {}

        Json(double d)
            : _type(NUMBER), _d(d), _valid(true) {}

        Json(bool b)
            : _type(BOOL), _b(b), _valid(true) {}

        Json(const string_type &s)
            : _type(STRING), _s(s), _valid(true) {}

        Json(const array_type &a)
            : _type(ARRAY), _a(a), _valid(true) {}

        Json(const char *a)
            : _type(STRING), _s(std::string(a)), _valid(true) {}

        Json(const object_type &o)
            : _type(OBJECT), _o(o), _valid(true) {}

        Json(const Json &j)
        {
            *this = j;
        }

        Json(const std::map<std::string, std::string> _p) : _type(OBJECT)
        {
            _o = object_type();
            for (std::map<std::string, std::string>::const_iterator p = _p.begin(); p != _p.end(); ++p)
            {
                std::pair<std::string, std::string> i = (*p);
                _o.insert(i);
            }
        }

        Json &operator=(const Json &rhs)
        {
            auto &lhs = *this;
            lhs._type = rhs.type();
            switch (lhs._type)
            {
            case NUL:
                break;
            case INT:
                lhs._d = rhs._d;
                break;
            case NUMBER:
                lhs._d = rhs._d;
                break;
            case BOOL:
                lhs._b = rhs._b;
                break;
            case STRING:
                lhs._s = string_type(rhs._s);
                break;
            case ARRAY:
                lhs._a = array_type(rhs._a);
                break;
            case OBJECT:
                lhs._o = object_type(rhs._o);
                break;
            }
            return lhs;
        }

        virtual ~Json() {}

        Type type() const
        {
            return _type;
        }

        bool is_null() const
        {
            return type() == NUL;
        }

        bool is_valid() const
        {
            return _valid;
        }

        void set_valid(bool v)
        {
            _valid = v;
        }

        // @brief parse the string in as Json
        static Json parse(const std::string &in);

        // @brief return the integer value from the Json value.
        // if this value is not type NUMBER then the result is undefined.
        int int_value() const;

        int int_value(int default_value) const;

        long long_value() const;

        long long_value(long default_value) const;

        bool bool_value() const;

        bool bool_value(bool default_value) const;

        // @brief return the float value from the Json value.
        // if this value is not type NUMBER then the result is undefined.
        float float_value() const;

        float float_value(float default_value) const;

        // @brief return the double value from the Json value.
        // if this value is not type NUMBER then the result is undefined.
        double double_value() const;

        double double_value(double default_value) const;

        // @brief return the string value from the Json value.
        // if this value is not type STRING then the result is undefined.
        const string_type &string_value() const;

        const string_type &string_value(const string_type &default_value) const;

        // @brief return the array value from the Json value.
        // if this value is not type ARRAY then the result is undefined.
        const array_type &array_items() const;

        // @brief return the object value from the Json value.
        // if this value is not type OBJECT then the result is undefined.
        const object_type &object_items() const;

        // @brief dump the object to a string.
        // Currently this is only partially implemented.
        const string_type dump() const;

        // @brief return a reference to arr[i] if this is an array, Json() otherwise.
        const Json &operator[](size_t i) const;

        Json &operator[](size_t i);

        // @brief return a reference to obj[key] if this is an object, Json() otherwise.
        const Json &operator[](const std::string &key) const;

        Json &operator[](const std::string &key);

        // @brief a nul object that can used for return values.
        static Json nul_json;

        Type getType() const
        {
            return _type;
        }

        const Json &JsonAtPath(const std::string &path) const;

    protected:
        union
        {
            double _d;
            bool _b;
        };
        string_type _s;
        array_type _a;
        object_type _o;

        Type _type;
        bool _valid;
    };

    typedef std::map<std::string, Json>::iterator Json_it;

}

#endif //_JSON_98_H_
