# Documentação do Projeto: Mini Linguagem de Manipulação de Arquivos

Este projeto implementa uma mini linguagem de comandos para manipulação de arquivos de texto. Ele permite realizar operações como abrir, salvar, substituir palavras, filtrar linhas e converter arquivos para os formatos CSV e JSON. A seguir, está a documentação detalhada de cada parte do código.

---

## **1. Arquivo main.cpp**

### **Descrição**
Este é o ponto de entrada do programa. Ele exibe um menu de comandos disponíveis e processa as entradas do usuário em um loop.

### **Funções**

#### `void exibir_menu()`
- **Descrição**: Exibe os comandos disponíveis para o usuário.
- **Comandos suportados**:
  - `open "arquivo.txt"`: Abre um arquivo.
  - `replace "antigo" "novo"`: Substitui todas as ocorrências de uma palavra por outra.
  - `save "arquivo.txt"`: Salva o conteúdo manipulado em um arquivo.
  - `filter "palavra"`: Filtra e exibe linhas que contêm uma palavra específica.
  - `convert "arquivo.txt" "saida.csv"`: Converte o conteúdo para CSV.
  - `convert "arquivo.txt" "saida.json"`: Converte o conteúdo para JSON.
  - `exit`: Encerra o programa.

#### `int main()`
- **Descrição**: 
  - Lê comandos do usuário em um loop.
  - Processa os comandos chamando funções apropriadas.
- **Variáveis principais**:
  - `linha`: Armazena o comando digitado pelo usuário.
  - `buffer`: Armazena o conteúdo do arquivo em memória.
  - `arquivo_carregado`: Indica se um arquivo foi carregado.

---

## **2. Arquivo utils.hpp e utils.cpp**

### **Descrição**
Contém funções auxiliares para manipulação de strings.

### **Funções**

#### `std::string extrair_entre_aspas(const std::string& linha)`
- **Descrição**: Extrai o texto entre aspas de uma string.
- **Parâmetro**: `linha` - String de entrada.
- **Retorno**: Texto entre aspas.

#### `std::pair<std::string, std::string> extrair_duas_strings(const std::string& linha)`
- **Descrição**: Extrai dois textos entre aspas de uma string.
- **Parâmetro**: `linha` - String de entrada.
- **Retorno**: Par de strings extraídas.

---

## **3. Arquivo commands.hpp e commands.cpp**

### **Descrição**
Contém as implementações das operações principais do programa.

### **Funções**

#### `std::string abrir_arquivo(const std::string& nome)`
- **Descrição**: Abre um arquivo e lê seu conteúdo.
- **Parâmetro**: `nome` - Nome do arquivo.
- **Retorno**: Conteúdo do arquivo como string.

#### `void salvar_arquivo(const std::string& nome, const std::string& conteudo)`
- **Descrição**: Salva o conteúdo em um arquivo.
- **Parâmetros**:
  - `nome`: Nome do arquivo.
  - `conteudo`: Conteúdo a ser salvo.

#### `void substituir(std::string& texto, const std::string& de, const std::string& para)`
- **Descrição**: Substitui todas as ocorrências de uma palavra por outra.
- **Parâmetros**:
  - `texto`: Texto onde a substituição será feita.
  - `de`: Palavra a ser substituída.
  - `para`: Palavra substituta.

#### `void filtrar_linhas(const std::string& palavra, const std::string& buffer)`
- **Descrição**: Filtra e exibe linhas que contêm uma palavra específica.
- **Parâmetros**:
  - `palavra`: Palavra a ser buscada.
  - `buffer`: Conteúdo do arquivo.

#### `void converter_para_csv(const std::string& buffer, const std::string& arquivo_saida)`
- **Descrição**: Converte o conteúdo do buffer para o formato CSV.
- **Parâmetros**:
  - `buffer`: Conteúdo do arquivo.
  - `arquivo_saida`: Nome do arquivo de saída.

#### `void converter_para_json(const std::string& buffer, const std::string& arquivo_saida)`
- **Descrição**: Converte o conteúdo do buffer para o formato JSON.
- **Parâmetros**:
  - `buffer`: Conteúdo do arquivo.
  - `arquivo_saida`: Nome do arquivo de saída.

---

## **4. Arquivo entrada.txt**

### **Descrição**
Arquivo de exemplo usado para testes. Contém:
- Erros simulados.
- Dados tabulares com nomes, idades e cidades.

---

## **5. Arquivo launch.json**

### **Descrição**
Configuração para depuração no Visual Studio Code.

### **Principais Configurações**
- `program`: Caminho para o executável gerado.
- `cwd`: Diretório de trabalho.
- `MIMode`: Define o uso do depurador GDB.

---

## **6. Arquivo task.json**

### **Descrição**
Configuração de tarefas para compilar o código no Visual Studio Code.

### **Principais Configurações**
- `command`: Comando para compilar (`g++`).
- `args`: Argumentos para o compilador, incluindo o arquivo de entrada e o nome do executável.

---

## **Fluxo Geral do Programa**

1. O programa exibe o menu de comandos.
2. O usuário digita um comando.
3. O comando é processado no loop principal do `main`.
4. Funções específicas são chamadas para executar a operação desejada.
5. O programa continua até o usuário digitar `exit`.

---

## **Exemplo de Uso**

### Entrada:
```plaintext
open "entrada.txt"
replace "erro" "problema"
save "saida.txt"
convert "saida.txt" "saida.csv"
exit
```

### Saída:
```plaintext
[Debug] Conteúdo do arquivo:
problema1: conexão perdida
problema2: arquivo não encontrado

nome idade cidade
João 25 São Paulo
Maria 30 Rio de Janeiro
Carlos 22 Belo Horizonte
Ana 28 Porto Alegre

[Sucesso] Arquivo convertido para CSV: saida.csv
```

---

## **Possíveis Melhorias**
1. Adicionar suporte a mais formatos de conversão.
2. Implementar tratamento de erros mais robusto.
3. Permitir comandos encadeados em uma única linha.
4. Adicionar suporte a arquivos binários.

---

Essa documentação cobre todos os aspectos do código e fornece uma visão clara de sua funcionalidade.