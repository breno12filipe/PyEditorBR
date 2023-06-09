#include <string>
#include <unordered_map>

std::unordered_map<int, std::string> keyCodeMap = {
    {65, "a"}, {66, "b"}, {67, "c"}, {68, "d"}, {69, "e"}, {70, "f"}, {71, "g"},
    {72, "h"}, {73, "i"}, {74, "j"}, {75, "k"}, {76, "l"}, {77, "m"}, {78, "n"},
    {79, "o"}, {80, "p"}, {81, "q"}, {82, "r"}, {83, "s"}, {84, "t"}, {85, "u"},
    {86, "v"}, {87, "x"}, {88, "w"}, {89, "y"}, {90, "z"},
};

std::unordered_map<std::string, std::string> pythonKeyWords = {
    {"False", ""},   {"None", ""},     {"True", ""},     {"and", ""},
    {"as", ""},      {"assert", ""},   {"async", ""},    {"await", ""},
    {"break", ""},   {"class", ""},    {"continue", ""}, {"def", ""},
    {"del", ""},     {"elif", ""},     {"else", ""},     {"except", ""},
    {"finally", ""}, {"for", ""},      {"from", ""},     {"global", ""},
    {"if", ""},      {"import", ""},   {"in", ""},       {"is", ""},
    {"lambda", ""},  {"nonlocal", ""}, {"not", ""},      {"or", ""},
    {"pass", ""},    {"raise", ""},    {"return", ""},   {"try", ""},
    {"while", ""},   {"with", ""},     {"yield", ""},
};
