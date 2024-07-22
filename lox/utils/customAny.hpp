
#ifndef CUSTOM_ANY_HPP
#define CUSTOM_ANY_HPP

#include <any>
#include <cstring>
#include <limits>
#include <memory>
#include <sstream>
#include <string>

class CustomAny {
  private:
    std::any value;

    template <typename T> static std::string to_string_impl(const T& t) {
        std::ostringstream oss;
        oss << t;
        return oss.str();
    }

    std::string checkEmptyAndReturnNil(const std::string& str) const {
        // return str.empty() ? "nil" : str;
        return str.size() == 0 ? "nil" : str;
        // return str;
    }

  public:
    // General template constructor
    template <typename T> CustomAny(T&& val) : value(std::forward<T>(val)) {}

    CustomAny(const char* val) : value(std::string(val)) {}

    // Constructor for const char*
    CustomAny(char* val) : value(std::string(val)) {}

    template <typename T> T get() const {
        if (typeid(T) != value.type()) {
            throw std::bad_cast();
        }
        return std::any_cast<T>(value);
    }

    template <typename T> bool is() const { return value.type() == typeid(T); }

    std::string convertPKctoString(const char* val) { return std::string(val); }

    bool isNull() const { return !value.has_value(); }

    std::string toString() const {
        if (is<std::shared_ptr<std::string>>())
            return *get<std::shared_ptr<std::string>>();
        if (is<std::shared_ptr<int>>())
            return std::to_string(*get<std::shared_ptr<int>>());
        if (is<std::shared_ptr<double>>())
            return std::to_string(*get<std::shared_ptr<double>>());
        if (is<std::shared_ptr<bool>>())
            return *get<std::shared_ptr<bool>>() ? "true" : "false";
        if (is<std::shared_ptr<char>>())
            return std::string(1, *get<std::shared_ptr<char>>());
        if (is<std::shared_ptr<float>>())
            return std::to_string(*get<std::shared_ptr<float>>());

        // if (is<std::string>())
        //     return get<std::string>();
        // if (is<const char*>())
        //     return std::string(get<const char*>());

        if (is<std::string>())
            return checkEmptyAndReturnNil(get<std::string>());
        if (is<const char*>())
            return checkEmptyAndReturnNil(std::string(get<const char*>()));

        if (is<int>())
            return std::to_string(get<int>());
        if (is<double>())
            return std::to_string(get<double>());
        if (is<bool>())
            return get<bool>() ? "true" : "false";
        if (is<char>())
            return std::string(1, get<char>());
        if (is<float>())
            return std::to_string(get<float>());
        // Add more types if needed
        return "Unknown type";
    }
    std::string get() const {
        if (is<std::shared_ptr<std::string>>())
            return *get<std::shared_ptr<std::string>>();
        if (is<std::shared_ptr<int>>())
            return std::to_string(*get<std::shared_ptr<int>>());
        if (is<std::shared_ptr<double>>())
            return std::to_string(*get<std::shared_ptr<double>>());
        if (is<std::shared_ptr<bool>>())
            return *get<std::shared_ptr<bool>>() ? "true" : "false";
        if (is<std::shared_ptr<char>>())
            return std::string(1, *get<std::shared_ptr<char>>());
        if (is<std::shared_ptr<float>>())
            return std::to_string(*get<std::shared_ptr<float>>());

        if (is<std::string>())
            return get<std::string>();
        if (is<const char*>())
            return std::string(get<const char*>());
        if (is<int>())
            return std::to_string(get<int>());
        if (is<double>())
            return std::to_string(get<double>());
        if (is<bool>())
            return get<bool>() ? "true" : "false";
        if (is<char>())
            return std::string(1, get<char>());
        if (is<float>())
            return std::to_string(get<float>());
        // Add more types if needed
        return "Unknown type";
    }

    bool has_value() const { return value.has_value(); }

    const std::type_info& getType() const { return value.type(); }

    const std::type_info& type() const { return value.type(); }

    double toDouble() const {
        if (is<double>()) {
            return get<double>();
        } else if (is<int>()) {
            return static_cast<double>(get<int>());
        } else if (is<float>()) {
            return static_cast<double>(get<float>());
        } else if (is<std::string>()) {
            try {
                return std::stod(get<std::string>());
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Cannot convert string to double");
            }
        } else if (isNull()) {
            throw std::runtime_error("Cannot convert null to double");
        } else {
            throw std::runtime_error("Unsupported type for double conversion");
        }
    }

    bool equals(const CustomAny& other) const {
        // If both are null, they're equal
        if (isNull() && other.isNull()) {
            return true;
        }

        // If one is null and the other isn't, they're not equal
        if (isNull() || other.isNull()) {
            return false;
        }

        // If types are different, they're not equal
        if (value.type() != other.value.type()) {
            // Special case: compare int and double
            if ((is<int>() && other.is<double>()) ||
                (is<double>() && other.is<int>())) {
                return std::abs(toDouble() - other.toDouble()) <
                       std::numeric_limits<double>::epsilon();
            }
            return false;
        }

        // Compare based on type
        if (is<double>()) {
            return std::abs(get<double>() - other.get<double>()) <
                   std::numeric_limits<double>::epsilon();
        } else if (is<int>()) {
            return get<int>() == other.get<int>();
        } else if (is<std::string>()) {
            return get<std::string>() == other.get<std::string>();
        } else if (is<bool>()) {
            return get<bool>() == other.get<bool>();
        }

        // For types we don't explicitly handle, use std::any's comparison
        return value.type() == other.value.type() &&
               std::memcmp(std::any_cast<void>(&value),
                           std::any_cast<void>(&other.value),
                           value.type().hash_code()) == 0;
    }
};

#endif
