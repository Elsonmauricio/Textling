#pragma once
#include <string>

std::string abrir_arquivo(const std::string& nome);
void salvar_arquivo(const std::string& nome, const std::string& conteudo);
void substituir(std::string& texto, const std::string& de, const std::string& para);
void filtrar_linhas(const std::string& palavra, const std::string& buffer);

// Declarações das funções de conversão
void converter_para_csv(const std::string& buffer, const std::string& arquivo_saida);
void converter_para_json(const std::string& buffer, const std::string& arquivo_saida);
