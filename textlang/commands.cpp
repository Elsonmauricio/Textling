#include "commands.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// Função auxiliar para escapar strings para JSON
string escape_json(const string &s) {
    string output;
    for (char c : s) {
        switch (c) {
            case '"': output += "\\\""; break;
            case '\\': output += "\\\\"; break;
            case '\b': output += "\\b"; break;
            case '\f': output += "\\f"; break;
            case '\n': output += "\\n"; break;
            case '\r': output += "\\r"; break;
            case '\t': output += "\\t"; break;
            default: output += c;
        }
    }
    return output;
}

void converter_para_csv(const std::string& buffer, const std::string& arquivo_saida) {
    ofstream saida(arquivo_saida);
    if (!saida) {
        cerr << "[Erro] Não foi possível criar o arquivo: " << arquivo_saida << endl;
        return;
    }

    istringstream ss(buffer);
    string linha;
    bool primeira_linha = true;
    vector<size_t> tamanhos_colunas;

    // Primeira passada para determinar tamanhos de colunas (se for tabela)
    while (getline(ss, linha)) {
        if (linha.empty()) continue;
        
        istringstream linha_stream(linha);
        vector<string> colunas;
        string coluna;
        
        while (getline(linha_stream, coluna, ' ')) {
            if (!coluna.empty()) {
                colunas.push_back(coluna);
            }
        }

        if (primeira_linha) {
            tamanhos_colunas.resize(colunas.size(), 0);
            primeira_linha = false;
        }

        for (size_t i = 0; i < min(colunas.size(), tamanhos_colunas.size()); ++i) {
            tamanhos_colunas[i] = max(tamanhos_colunas[i], colunas[i].size());
        }
    }

    // Segunda passada para escrever o CSV
    ss.clear();
    ss.str(buffer);
    while (getline(ss, linha)) {
        if (linha.empty()) {
            saida << "\n";
            continue;
        }

        istringstream linha_stream(linha);
        string coluna;
        bool primeira_coluna = true;

        while (getline(linha_stream, coluna, ' ')) {
            if (coluna.empty()) continue;
            
            if (!primeira_coluna) {
                saida << ",";
            }
            primeira_coluna = false;
            
            // Se contiver vírgula ou aspas, coloca entre aspas
            if (coluna.find_first_of(",\"") != string::npos) {
                saida << "\"" << coluna << "\"";
            } else {
                saida << coluna;
            }
        }
        saida << "\n";
    }

    cout << "[Sucesso] Arquivo convertido para CSV: " << arquivo_saida << endl;
}

void converter_para_json(const std::string& buffer, const std::string& arquivo_saida) {
    ofstream saida(arquivo_saida);
    if (!saida) {
        cerr << "[Erro] Não foi possível criar o arquivo: " << arquivo_saida << endl;
        return;
    }

    istringstream ss(buffer);
    string linha;
    bool primeiro_objeto = true;

    saida << "[\n";

    while (getline(ss, linha)) {
        if (linha.empty()) continue;

        if (!primeiro_objeto) {
            saida << ",\n";
        }
        primeiro_objeto = false;

        istringstream linha_stream(linha);
        string palavra;
        vector<string> colunas;
        
        while (linha_stream >> palavra) {
            colunas.push_back(escape_json(palavra));
        }

        saida << "  {";
        for (size_t i = 0; i < colunas.size(); ++i) {
            if (i > 0) saida << ", ";
            saida << "\"coluna" << (i+1) << "\": \"" << colunas[i] << "\"";
        }
        saida << "}";
    }

    saida << "\n]\n";
    cout << "[Sucesso] Arquivo convertido para JSON: " << arquivo_saida << endl;
}


std::string abrir_arquivo(const std::string& nome) {
    std::ifstream arquivo(nome);
    if (!arquivo.is_open()) {
        std::cerr << "[Erro] Não foi possível abrir o arquivo: " << nome << "\n";
        return "";
    }

    std::stringstream buffer;
    buffer << arquivo.rdbuf(); // Lê todo o conteúdo do arquivo para o buffer
    std::cout << "[Debug] Conteúdo do arquivo:\n" << buffer.str() << "\n";
    return buffer.str();
}

void salvar_arquivo(const std::string& nome, const std::string& conteudo) {
    std::ofstream arquivo(nome);
    if (!arquivo.is_open()) {
        std::cerr << "[Erro] Não foi possível salvar o arquivo: " << nome << "\n";
        return;
    }
    arquivo << conteudo;
}

void substituir(std::string& texto, const std::string& de, const std::string& para) {
    size_t pos = 0;
    while ((pos = texto.find(de, pos)) != std::string::npos) {
        texto.replace(pos, de.length(), para);
        pos += para.length();
    }
}

void filtrar_linhas(const std::string& palavra, const std::string& buffer) {
    std::stringstream ss(buffer);
    std::string linha;
    while (std::getline(ss, linha)) {
        if (linha.find(palavra) != std::string::npos) {
            std::cout << linha << "\n";
        }
    }
}