#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void defineVisitor(std::ofstream& out, const std::string& baseName,
                   const std::vector<std::string>& types) {
    out << "    template<typename R>\n";
    out << "    class Visitor {\n";
    out << "    public:\n";
    out << "        virtual ~Visitor() = default;\n";
    for (const auto& type : types) {
        std::string typeName = type.substr(0, type.find(':'));
        out << "        virtual R visit" << typeName << baseName << "(const "
            << typeName << "& " << baseName  << ") = 0;\n";
    }
    out << "    };\n\n";
}

void defineType(std::ofstream& out, const std::string& baseName,
                const std::string& className, const std::string& fieldList) {
    out << "class " << className << " : public " << baseName << " {\n";
    out << "public:\n";
    out << "    " << className << "(" << fieldList << ") {\n";
    // Store parameters in fields
    std::istringstream fieldsStream(fieldList);
    std::string field;
    while (std::getline(fieldsStream, field, ',')) {
        std::istringstream fieldStream(field);
        std::string type, name;
        fieldStream >> type >> name;
        out << "        this->" << name << " = " << name << ";\n";
    }
    out << "    }\n\n";

    // Visitor pattern
    out << "    template<typename R>\n";
    out << "    R accept(Visitor<R>& visitor) const override {\n";
    out << "        return visitor.visit" << className << baseName
        << "(*this);\n";
    out << "    }\n\n";

    // Fields
    std::istringstream fieldsStream2(fieldList);
    while (std::getline(fieldsStream2, field, ',')) {
        std::istringstream fieldStream(field);
        std::string type, name;
        fieldStream >> type >> name;
        out << "    " << type << " " << name << ";\n";
    }
    out << "};\n\n";
}

void defineAst(const std::string& outputDir, const std::string& baseName,
               const std::vector<std::string>& types) {
    std::string path = outputDir + "/" + baseName + ".h";
    std::ofstream out(path);

    out << "#ifndef " << baseName << "_H\n";
    out << "#define " << baseName << "_H\n\n";
    out << "#include <string>\n";
    out << "#include <memory>\n";
    out << "#include <vector>\n\n";

    out << "class " << baseName << " {\n";
    out << "public:\n";
    out << "    virtual ~" << baseName << "() = default;\n\n";

    defineVisitor(out, baseName, types);

    out << "    template<typename R>\n";
    out << "    virtual R accept(Visitor<R>& visitor) const = 0;\n";
    out << "};\n\n";

    for (const auto& type : types) {
        std::string className = type.substr(0, type.find(':'));
        std::string fields = type.substr(type.find(':') + 1);
        defineType(out, baseName, className, fields);
    }

    out << "#endif\n";
    out.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: generate_ast <output directory>\n";
        return 64;
    }
    std::string outputDir = argv[1];

    defineAst(
        outputDir, "Expr",
        {"Binary : std::shared_ptr<Expr> left, std::string operatorToken, "
         "std::shared_ptr<Expr> right",
         "Grouping : std::shared_ptr<Expr> expression",
         "Literal : std::string value",
         "Unary : std::string operatorToken, std::shared_ptr<Expr> right"});

    return 0;
}
