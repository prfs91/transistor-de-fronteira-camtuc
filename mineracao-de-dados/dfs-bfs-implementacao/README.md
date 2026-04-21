# 🌳 Visualizador de Algoritmos de Busca (DFS & BFS)

Este repositório contém as implementações de algoritmos de busca em árvores para a disciplina de Mineração de Dados (UFPA). O projeto permite visualizar o percurso das buscas tanto via terminal quanto através de gráficos gerados automaticamente.

---

## 🛠️ Requisitos Globais (Obrigatório)

Para que ambos os projetos (C e Python) gerem as imagens da árvore, é necessário instalar o motor gráfico **Graphviz**:

1.  **Instalação**: [Baixe aqui o instalador .exe](https://graphviz.org)
2.  **Configuração**: Durante a instalação, marque a opção **"Add Graphviz to the system PATH for all users"**.
3.  **Reinicialização**: Após instalar, feche e abra o VS Code novamente.

---

## 🧩 Extensões Recomendadas (VS Code)

Para facilitar o desenvolvimento, instale estas extensões no VS Code:
*   `ms-vscode.cpptools` - **C/C++** (Microsoft)
*   `ms-python.python` - **Python** (Microsoft)
*   `tintinweb.graphviz-interactive-preview` - **Graphviz Interactive Preview**
*   `yzhang.markdown-all-in-one` - **Markdown All in One**

---

## 📁 Estrutura de Pastas de Saída

O código espera que a seguinte estrutura exista para salvar os resultados:
```text
projeto/
├── output/
    └── figures/
        └── c/
            ├── dot/
            └── png/
```

## 💻 Execução: Projeto em C

O programa em C realiza alocação dinâmica de nós e exporta o resultado visual para a pasta `figures/c/`.

### Compilação e Execução
Abra o terminal na pasta `output` e execute:

```powershell
# 1. Compilar o código
gcc ../percurso_arvore.c -o percurso_arvore.exe

# 2. Executar o programa
./percurso_arvore.exe
```

> **Dica:** Se o terminal estiver "poluído" com mensagens do ambiente virtual, use o comando `cls` antes de rodar o `.exe` para garantir que o `scanf` funcione corretamente.

---

## 🐍 Execução: Projeto em Python

O código em Python utiliza bibliotecas de grafos para análise e exportação.

### Preparação do Ambiente
Certifique-se de estar com o ambiente virtual ativo e as bibliotecas instaladas:

```powershell
# 1. Ativar o ambiente virtual
.\.venv\Scripts\activate

# 2. Instalar dependências
pip install networkx graphviz matplotlib
```
### Rodar o script

```powershell
python nome_do_seu_trabalho.py
```
## 📊 Funcionalidades

*   **Árvore Completa:** Geração de imagem da estrutura original.
*   **Busca DFS/BFS:** Varredura completa com contagem de nós no terminal.
*   **Destaque Visual:** O nó alvo fica em **Salmão**, o caminho percorrido em **Verde** e o restante em **Branco**.
*   **Boas Práticas:** Código refatorado, modularizado e com tratamento de erro para nós inexistentes.
