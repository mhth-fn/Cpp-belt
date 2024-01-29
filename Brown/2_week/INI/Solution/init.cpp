#include "ini.h"


namespace Ini {
    
    Section& Document::AddSection(string name){
        return sections[name];
    }

    const Section& Document::GetSection(const string& name) const{
        return sections.at(name);
    }

    size_t Document::SectionCount() const{
        return sections.size();
    }

    string ReadSectionName(string_view line){
       line.remove_prefix(1);
       line.remove_suffix(1);

       return {line.begin(), line.end()}; 
    }

    pair<string, string> ReadSection(string_view line){
        size_t pos = line.find("=");
        string_view left = line.substr(0, pos);
        string_view right = line.substr(pos + 1, std::string::npos);

        return {{left.begin(), left.end()}, 
        {right.begin(), right.end()}};
    }

    Document Load(istream& input){
        Document res;
        Section* section;
        string line;
        while (input){
            getline(input, line);
            if (line.empty()){
                continue;
            } else if (line[0] == '['){
                section = &res.AddSection(ReadSectionName(line));
            } else{
                pair tmp = ReadSection(line);
                (*section)[tmp.first] = tmp.second;
            }
                
            }
        return res;
    }

}

