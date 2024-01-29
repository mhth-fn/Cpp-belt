#pragma once

#include <iostream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <sstream>


namespace Ini {
    using namespace std;

    using Section = unordered_map<string, string>;

    class Document {
    public:
    Section& AddSection(string name);
    const Section& GetSection(const string& name) const;
    size_t SectionCount() const;

    private:
    unordered_map<string, Section> sections;
};
    pair<string, string> ReadSection(string_view line);
    
    string ReadSectionName(string_view line);

    Document Load(istream& input);
}