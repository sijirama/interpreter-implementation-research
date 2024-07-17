
#ifndef CUSTOM_ANY_HPP
#define CUSTOM_ANY_HPP

#include <any>
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
        return str.empty() ? "nil" : str;
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
};

#endif
