#include "commands.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

// Função para converter o conteúdo do buffer para CSV
void converter_para_csv(const std::string& buffer, const std::string& arquivo_saida) {
    std::stringstream ss(buffer);
    std::ofstream saida(arquivo_saida);
    std::string linha;

    if (!saida.is_open()) {
        std::cerr << "[Erro] Não foi possível abrir o arquivo de saída: " << arquivo_saida << "\n";
        return;
    }

    while (std::getline(ss, linha)) {
        // Ignora linhas vazias
        if (linha.empty()) {
            saida << "\n";
            continue;
        }

        // Substitui espaços por vírgulas apenas nas linhas não vazias
        for (char& c : linha) {
            if (c == ' ') c = ',';
        }
        saida << linha << "\n";
    }

    saida.close();
    std::cout << "[Info] Arquivo convertido para CSV: " << arquivo_saida << "\n";
}

// Função para converter o conteúdo do buffer para JSON
void converter_para_json(const std::string& buffer, const std::string& arquivo_saida) {
    std::stringstream ss(buffer);
    std::ofstream saida(arquivo_saida);
    std::string linha;

    if (!saida.is_open()) {
        std::cerr << "[Erro] Não foi possível abrir o arquivo de saída: " << arquivo_saida << "\n";
        return;
    }

    saida << "[\n";
    bool primeiro = true;

    while (std::getline(ss, linha)) {
        // Ignora linhas vazias
        if (linha.empty()) continue;

        if (!primeiro) {
            saida << ",\n";
        }
        primeiro = false;

        // Divide a linha em palavras separadas por espaços
        std::stringstream linha_stream(linha);
        std::string palavra;
        std::vector<std::string> colunas;

        while (linha_stream >> palavra) {
            colunas.push_back(palavra);
        }

        // Cria um objeto JSON para cada linha
        saida << "  {";
        for (size_t i = 0; i < colunas.size(); ++i) {
            saida << "\"coluna" << i + 1 << "\": \"" << colunas[i] << "\"";
            if (i < colunas.size() - 1) {
                saida << ", ";
            }
        }
        saida << "}";
    }

    saida << "\n]\n";

    saida.close();
    std::cout << "[Info] Arquivo convertido para JSON: " << arquivo_saida << "\n";
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