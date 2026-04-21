from collections import deque
import networkx as nx
import matplotlib.pyplot as plt
import os

# ==========================================
# 1. CAMINHO DA PASTA DE SAÍDA
# ==========================================

PASTA_OUTPUT = r"D:\Projetos\GitHub\UFPA\transistor-de-fronteira-camtuc\mineracao-de-dados\dfs-bfs-implementacao\output\figures\python"

# Cria a pasta caso ela não exista para evitar erros
if not os.path.exists(PASTA_OUTPUT):
    os.makedirs(PASTA_OUTPUT)

# ==========================================
# 1. DEFINIÇÃO DE DADOS E ESTRUTURA
# ==========================================

# Árvore modelada conforme o Slide 36 da Aula do dia 16/04/2026
ARVORE_ESTRUTURA = {
    'A': ['B', 'E', 'Z'],
    'B': ['C', 'L'],
    'C': ['D', 'M'],
    'D': [],
    'M': [],
    'L': [],
    'E': ['F', 'N'],
    'F': ['G'],
    'G': ['H'],
    'H': [],
    'N': [],
    'Z': ['I', 'O'],
    'I': ['J'],
    'J': ['K', 'Q'],
    'K': [],
    'Q': [],
    'O': ['P'],
    'P': []
}

# Coordenadas fixas para garantir layout de cima para baixo (Hierárquico)
POSICAO_NOS = {
    'A': (0, 10),
    'B': (-5, 8), 'E': (0, 8), 'Z': (5, 8),
    'C': (-6, 6), 'L': (-4, 6), 'F': (-1, 6), 'N': (1, 6), 'I': (4, 6), 'O': (6, 6),
    'D': (-7, 4), 'M': (-5, 4), 'G': (-1, 4), 'J': (4, 4), 'P': (6, 4),
    'H': (-1, 2), 'K': (3, 2), 'Q': (5, 2)
}

# ==========================================
# 2. LÓGICA DE ALGORITMOS (BUSCAS)
# ==========================================

def busca_em_profundidade(grafo, inicio, visitados=None):
    """Percorre a árvore verticalmente até o nó mais profundo."""
    if visitados is None:
        visitados = []
    if inicio not in visitados:
        visitados.append(inicio)
        for vizinho in grafo[inicio]:
            busca_em_profundidade(grafo, vizinho, visitados)
    return visitados

def busca_em_largura(grafo, inicio):
    """Percorre a árvore horizontalmente, nível por nível."""
    visitados = []
    fila_espera = deque([inicio])
    visitados.append(inicio)

    while fila_espera:
        no_atual = fila_espera.popleft()
        for vizinho in grafo[no_atual]:
            if vizinho not in visitados:
                visitados.append(vizinho)
                fila_espera.append(vizinho)
    return visitados

def buscar_no_especifico(alvo):
    """Realiza as buscas e retorna o caminho exato até encontrar o alvo."""
    if alvo not in ARVORE_ESTRUTURA:
        return None, None
    
    percurso_dfs = busca_em_profundidade(ARVORE_ESTRUTURA, 'A')
    percurso_bfs = busca_em_largura(ARVORE_ESTRUTURA, 'A')
    
    # Recorta o caminho até o ponto onde o alvo foi encontrado
    caminho_dfs = percurso_dfs[:percurso_dfs.index(alvo) + 1]
    caminho_bfs = percurso_bfs[:percurso_bfs.index(alvo) + 1]
    
    return caminho_dfs, caminho_bfs

# ==========================================
# 3. FUNÇÕES VISUAIS E GERAÇÃO DE IMAGENS
# ==========================================

def plotar_estrutura_completa(grafo_dict):
    """Gera a visualização da árvore original completa."""
    G = nx.DiGraph()
    for pai, filhos in grafo_dict.items():
        for filho in filhos:
            G.add_edge(pai, filho)
    
    plt.figure(figsize=(12, 7))
    nx.draw(G, POSICAO_NOS, with_labels=True, node_size=1800, node_color="#7ae2ff", 
            font_size=11, font_weight="bold", arrows=True, edge_color="#bbbbbb", width=1.5)
    plt.title("Mapa da Árvore Modelada")
    plt.show()

def salvar_texto_como_imagem(res_dfs, res_bfs, nome_arquivo="resultado_percursos.png"):
    """Transforma a lista de percursos em uma imagem de texto formatada."""
    texto_dfs = f"Ordem DFS (Profundidade): {' -> '.join(res_dfs)}"
    texto_bfs = f"Ordem BFS (Largura):      {' -> '.join(res_bfs)}"
    
    fig, ax = plt.subplots(figsize=(12, 2))
    ax.set_axis_off()

    conteudo = (
        "RESULTADOS DOS PERCURSOS\n"
        "----------------------------------------------------------------------------------------------------\n"
        f"{texto_dfs}\n\n"
        f"{texto_bfs}"
    )

    plt.text(0.01, 0.5, conteudo, family='monospace', fontsize=10, verticalalignment='center', linespacing=1.8)
    
    caminho_arquivo = os.path.join(PASTA_OUTPUT, nome_arquivo)
    plt.savefig(caminho_arquivo, bbox_inches='tight', dpi=300, facecolor='white')

    plt.show()

def salvar_busca_como_imagem(alvo, res_dfs, res_bfs, nome_arquivo="resultado_busca.png"):
    """Gera imagem com detalhes e estatísticas da busca por um alvo."""
    fig, ax = plt.subplots(figsize=(10, 3))
    ax.set_axis_off()

    titulo = f"RELATÓRIO DE BUSCA - ALVO: [ {alvo} ]"
    divisoria = "-" * 120
    texto_dfs = f"Ordem DFS (Profundidade): {' -> '.join(res_dfs)} ({len(res_dfs)} nós)"
    texto_bfs = f"Ordem BFS (Largura):      {' -> '.join(res_bfs)} ({len(res_bfs)} nós)"

    conteudo = f"{titulo}\n{divisoria}\n\n {texto_dfs}\n\n {texto_bfs}"

    plt.text(0.05, 0.5, conteudo, family='monospace', fontsize=11, 
             verticalalignment='center', linespacing=2, fontweight='bold')

    nome_final = f"resultado_busca_{alvo}.png"
    caminho_arquivo = os.path.join(PASTA_OUTPUT, nome_final)
    plt.savefig(caminho_arquivo, bbox_inches='tight', dpi=300, facecolor='#f9f9f9')


    plt.show()

def desenhar_comparativo_visual(caminho_dfs, caminho_bfs, alvo):
    """Gera dois gráficos lado a lado destacando o caminho percorrido."""
    G = nx.DiGraph()
    for pai, filhos in ARVORE_ESTRUTURA.items():
        for filho in filhos: G.add_edge(pai, filho)
    
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(18, 7))

    for ax, caminho, titulo in zip([ax1, ax2], [caminho_dfs, caminho_bfs], ["Busca Profundidade (DFS)", "Busca Largura (BFS)"]):
        cores = ['#e74c3c' if n == alvo else '#2ecc71' if n in caminho else '#3498db' for n in G.nodes()]

        nx.draw(G, POSICAO_NOS, ax=ax, with_labels=True, node_size=1000, node_color=cores, 
                font_weight="bold", arrows=True, edge_color="gray")
        ax.set_title(f"{titulo}\nNós visitados: {len(caminho)} | Ordem: {' -> '.join(caminho)}")
    plt.show()

def desenhar_percurso_unico(caminho, alvo, titulo):
    """Desenha um gráfico individual de um percurso."""
    G = nx.DiGraph()
    for pai, filhos in ARVORE_ESTRUTURA.items():
        for filho in filhos: G.add_edge(pai, filho)
    
    plt.figure(figsize=(10, 7))
    cores = ['#e74c3c' if n == alvo else '#2ecc71' if n in caminho else '#3498db' for n in G.nodes()]
    
    nx.draw(G, POSICAO_NOS, with_labels=True, node_size=1200, node_color=cores, 
            font_weight="bold", arrows=True, edge_color="gray", width=1.5)
    
    plt.title(f"{titulo}\nNós visitados: {len(caminho)} | Ordem: {' -> '.join(caminho)}")
    plt.show()

# ==========================================
# 4. BLOCO DE TESTES (SÓ RODA SE EXECUTADO DIRETAMENTE)
# ==========================================
if __name__ == "__main__":
    print("--- Teste de Percursos Completos ---")
    print(f"DFS Completo: {' -> '.join(busca_em_profundidade(ARVORE_ESTRUTURA, 'A'))}")
    print(f"BFS Completo: {' -> '.join(busca_em_largura(ARVORE_ESTRUTURA, 'A'))}")

    ALVO_EXEMPLO = "G"
    resultado_d, resultado_b = buscar_no_especifico(ALVO_EXEMPLO)
    print(f"\n--- Teste de Busca por Alvo ({ALVO_EXEMPLO}) ---")
    print(f"Caminho DFS: {resultado_d}")
    print(f"Caminho BFS: {resultado_b}")
