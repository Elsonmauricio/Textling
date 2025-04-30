#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "utils.hpp"
#include "commands.hpp"

using namespace std;

// Definição da função exibir_menu fora do main
void exibir_menu() {
    cout << "Comandos disponíveis:\n";
    cout << "  open \"arquivo.txt\" - Abre um arquivo\n";
    cout << "  replace \"antigo\" \"novo\" - Substitui texto\n";
    cout << "  save \"arquivo.txt\" - Salva o arquivo\n";
    cout << "  filter \"palavra\" - Filtra linhas com uma palavra\n";
    cout << "  convert \"arquivo.txt\" \"saida.csv\" - Converte para CSV\n";
    cout << "  convert \"arquivo.txt\" \"saida.json\" - Converte para JSON\n";
    cout << "  exit - Encerra o programa\n";
}

int main() {
    string linha;
    string buffer;  // conteúdo do arquivo sendo manipulado

    exibir_menu();
    cout << "Digite comandos (Ctrl+D para sair):\n";

    while (getline(cin, linha)) {
        if (linha.substr(0, 4) == "open") {
            string nome = extrair_entre_aspas(linha);
            buffer = abrir_arquivo(nome);
        } else if (linha.substr(0, 7) == "replace") {
            auto partes = extrair_duas_strings(linha);
            substituir(buffer, partes.first, partes.second);
        } else if (linha.substr(0, 4) == "save") {
            string nome = extrair_entre_aspas(linha);
            salvar_arquivo(nome, buffer);
        } else if (linha.substr(0, 7) == "convert") {
            auto partes = extrair_duas_strings(linha);
            if (partes.second.find(".csv") != std::string::npos) {
                converter_para_csv(buffer, partes.second);
            } else if (partes.second.find(".json") != std::string::npos) {
                converter_para_json(buffer, partes.second);
            } else {
                std::cout << "[Erro] Formato de saída não suportado: " << partes.second << "\n";
            }
        } else if (linha == "exit") {
            break;
        } else {
            cout << "[Erro] Comando inválido: " << linha << "\n";
        }
    }

    return 0;
}
