#include "utils.hpp"

std::string extrair_entre_aspas(const std::string& linha) {
    auto ini = linha.find('"');
    auto fim = linha.rfind('"');
    return linha.substr(ini + 1, fim - ini - 1);
}

std::pair<std::string, std::string> extrair_duas_strings(const std::string& linha) {
    size_t asp1 = linha.find('"');
    size_t asp2 = linha.find('"', asp1 + 1);
    size_t asp3 = linha.find('"', asp2 + 1);
    size_t asp4 = linha.find('"', asp3 + 1);

    std::string s1 = linha.substr(asp1 + 1, asp2 - asp1 - 1);
    std::string s2 = linha.substr(asp3 + 1, asp4 - asp3 - 1);
    return {s1, s2};
}
