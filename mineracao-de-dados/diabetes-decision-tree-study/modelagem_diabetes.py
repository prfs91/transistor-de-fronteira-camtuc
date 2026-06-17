import pandas as pd                                             # Manipulação de tabelas e dados
import matplotlib.pyplot as plt                                 # Geração de gráficos
import ipywidgets as widgets                                    # Componentes interativos (menus/botões)
from matplotlib.lines import Line2D                             # Legendas customizadas
from IPython.display import display                             # Exibição de objetos no Notebook
from sklearn.tree import DecisionTreeClassifier, plot_tree      # Modelo de Árvore e visualização
from sklearn.model_selection import train_test_split            # Divisão treino/teste
from sklearn.metrics import (
    accuracy_score,                                             # Cálculo de acertos totais
    f1_score,                                                   # Equilíbrio entre precisão e recall
    precision_score,                                            # Qualidade dos acertos positivos
    recall_score,                                               # Capacidade de detectar positivos
    confusion_matrix,                                           # Matriz de erros e acertos
    ConfusionMatrixDisplay,                                     # Visualização da matriz
    roc_curve,                                                  # Coordenadas da Curva ROC
    roc_auc_score                                               # Cálculo da área sob a curva (AUC)
)

# ==========================================
# 1. CONSTANTES E CONFIGURAÇÕES
# ==========================================

SPLIT_TECNICO = 0.25                                            # Define que 25% dos dados serão usados para teste no experimento profissional

TRADUCAO_COLUNAS = {                                            # Dicionário para renomear os nomes originais das colunas para português
    'Pregnancies': 'Gravidez',
    'Glucose': 'Glicose',
    'BloodPressure': 'Pressao',
    'SkinThickness': 'Pele',
    'Insulin': 'Insulina',
    'BMI': 'IMC',
    'DiabetesPedigreeFunction': 'Historico',
    'Age': 'Idade',
    'Outcome': 'Resultado'
}

# Experimento Profissional: Foco em Profundidade (Split Fixo)
EXP_PROFISSIONAL = [
    {"crit": "gini", "depth": 3, "label": "Gini / Prof. 3"},
    {"crit": "gini", "depth": 5, "label": "Gini / Prof. 5"},
    {"crit": "entropy", "depth": 3, "label": "Entropia / Prof. 3"},
    {"crit": "entropy", "depth": 5, "label": "Entropia / Prof. 5"}
]

# Experimento Acadêmico: Foco em Split (Profundidade Livre)
EXP_ACADEMICO = [
    {"crit": "gini", "split": 0.3, "label": "Gini / 70-30"},
    {"crit": "gini", "split": 0.2, "label": "Gini / 80-20"},
    {"crit": "entropy", "split": 0.3, "label": "Entropia / 70-30"},
    {"crit": "entropy", "split": 0.2, "label": "Entropia / 80-20"}
]

# ==========================================
# 2. PROCESSAMENTO E MODELAGEM
# ==========================================

def separar_recursos_e_alvo(df, coluna_alvo='Resultado'):
    """Executa os modelos e retorna DataFrame com métricas e objetos inclusos."""
    X = df.drop(coluna_alvo, axis=1)
    y = df[coluna_alvo]
    return X, y

def executar_experimentos(X, y, lista_configs, eh_profissional=True):
    """Executa os modelos, calcula métricas e retorna DataFrame com objetos inclusos."""
    resultados = []
    
    for conf in lista_configs:
        # Define parâmetros baseado no tipo de experimento
        split_atual = SPLIT_TECNICO if eh_profissional else conf["split"]
        profundidade = conf.get("depth") # None se não existir (árvore livre)
        
        X_treino, X_teste, y_treino, y_teste = train_test_split(
            X, y, test_size=split_atual, random_state=1
        )
        
        clf = DecisionTreeClassifier(
            criterion=conf["crit"], 
            max_depth=profundidade, 
            random_state=1
        )
        clf.fit(X_treino, y_treino)
        y_pred = clf.predict(X_teste)
        
        resultados.append({
            "Configuracao": conf["label"],
            "Acurácia": accuracy_score(y_teste, y_pred),
            "Precisão": precision_score(y_teste, y_pred),
            "Recall": recall_score(y_teste, y_pred),
            "F1-Score": f1_score(y_teste, y_pred),
            "modelo": clf,           # Objeto para plot_tree
            "X_teste": X_teste,      # Grafico ROC
            "y_real": y_teste,       # Dados para Matriz
            "y_previsto": y_pred     # Dados para Matriz
        })
        
    return pd.DataFrame(resultados).set_index("Configuracao")

def plotar_comparativo_metricas(df_res, titulo, eixo_x):
    """Gera gráfico com destaque no melhor valor de cada categoria (2 casas decimais)."""
    metricas = ['Acurácia', 'Precisão', 'Recall', 'F1-Score']
    
    ax = df_res[metricas].plot(kind='bar', figsize=(12, 6), rot=0, width=0.9)

    maximos_por_coluna = df_res[metricas].max().values

    qtd_modelos = len(df_res)
    
    for i, p in enumerate(ax.patches):
        valor = p.get_height()
        if valor > 0: # Evita plotar sobre barras vazias
            indice_metrica = i // qtd_modelos

            valor_maximo_da_categoria = maximos_por_coluna[indice_metrica]

            e_o_melhor = (valor == valor_maximo_da_categoria)

            # Define a cor: Azul Marinho para o melhor, Preto para os outros
            cor_fonte = '#000080' if e_o_melhor else 'black'
            peso_fonte = 'bold' if e_o_melhor else 'normal'
            tamanho_fonte = 10 if e_o_melhor else 9

            ax.annotate(f'{valor:.2%}', 
                        (p.get_x() + p.get_width() / 2., valor), 
                        ha='center', va='bottom', 
                        xytext=(0, 5), 
                        textcoords='offset points',
                        fontsize=tamanho_fonte, 
                        color=cor_fonte, # Aplica a cor de destaque
                        fontweight=peso_fonte)

    plt.title(titulo)
    plt.ylabel('Valores (0 a 1)')
    plt.xlabel(eixo_x)
    plt.legend(loc='lower right', fontsize='small')
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    plt.ylim(0, 1.1) # Aumentado para o texto não sair da imagem
    plt.tight_layout()
    plt.show()

def plotar_comparativo_unificado(df_prof, df_acad, metrica='Acurácia'):
    """
    Cria um gráfico de barras comparando uma métrica específica entre 
    os dois experimentos para cada configuração de critério.
    """

    # 1. Criamos os nomes combinados para o eixo X
    # Pegamos os nomes do Profissional (Gini / Prof. 3) e do Acadêmico (70-30)
    nomes_prof = df_prof.index.tolist()
    # Extraímos apenas a parte do split do nome acadêmico (ex: '70-30')
    nomes_acad = [n.split('/')[-1].strip() for n in df_acad.index]
    
    # Montamos o novo índice: "Gini: Prof. 3 | 70-30"
    indice_combinado = [
        f"{p.replace(' / ', ': ')} | {a}" 
        for p, a in zip(nomes_prof, nomes_acad)
    ]

    # 1. Preparação dos dados para alinhar por Critério (Gini/Entropia)
    # Criamos um DataFrame temporário para cruzar os dados
    df_comp = pd.DataFrame({
        'Profissional (Fixo 25%)': df_prof[metrica].values,
        'Acadêmico (Livre)': df_acad[metrica].values
    }, index=indice_combinado)

    # 2. Plotagem
    ax = df_comp.plot(kind='bar', figsize=(14, 7), color=['teal', 'orange'], rot=0, width=0.9)
    
    # 3. Identificação do valor máximo global para destaque
    valor_maximo_geral = df_comp.max().max()

    # 4. Adicionando rótulos de valores com lógica de destaque
    for p in ax.patches:
        valor = p.get_height()
        if valor > 0:
            # Verifica se é o melhor valor do gráfico para destacar
            e_o_melhor = (valor == valor_maximo_geral)

            # Estilização: Azul Marinho e Negrito para o melhor, Preto para o resto
            cor_fonte = '#000080' if e_o_melhor else 'black'
            peso_fonte = 'bold' if e_o_melhor else 'normal'
            tamanho_fonte = 11 if e_o_melhor else 10

            ax.annotate(f'{valor:.2%}', 
                        (p.get_x() + p.get_width() / 2., valor), 
                        ha='center', va='bottom', 
                        xytext=(0, 5), 
                        textcoords='offset points',
                        fontsize=tamanho_fonte, 
                        color=cor_fonte, 
                        fontweight=peso_fonte)

    # 5. Configurações de layout e títulos
    plt.title(f'Duelo Direto: {metrica} (Profissional vs Acadêmico)', fontsize=15)
    plt.ylabel(f'Valor da {metrica}')
    plt.xlabel('Configurações de Critério')
    plt.legend(loc='lower right')
    plt.grid(axis='y', linestyle='--', alpha=0.3)
    plt.ylim(0, 1.1)
    plt.tight_layout()
    plt.show()

# ==============================================================================
# 3. INTERATIVIDADE E DETALHAMENTO
# ==============================================================================

def criar_interface_comparativa(funcao_plot, df_prof, df_acad, colunas=None):
    """
    Cria uma interface universal com dois menus suspensos para comparar modelos.
    """
    opcoes = [f"Profissional: {n}" for n in df_prof.index] + \
             [f"Acadêmico: {n}" for n in df_acad.index]

    # Criamos os menus com nomes claros
    menu_esq = widgets.Dropdown(options=opcoes, description='Modelo Esq:', value=opcoes[0])
    menu_dir = widgets.Dropdown(options=opcoes, description='Modelo Dir:', value=opcoes[-1])

    # Layout lado a lado
    ui = widgets.HBox([menu_esq, menu_dir])
    ui.layout.justify_content = 'space-around'

    # Mapeamento de argumentos para a função de plotagem
    params = {
        'escolha_esq': menu_esq, 
        'escolha_dir': menu_dir,
        'df_prof': widgets.fixed(df_prof),
        'df_acad': widgets.fixed(df_acad)
    }
    
    # Se a função precisar das colunas (como a de Importância), nós passamos
    if colunas is not None:
        params['colunas'] = widgets.fixed(colunas)

    saida = widgets.interactive_output(funcao_plot, params)
    display(ui, saida)

def plotar_importancias_lado_a_lado(escolha_esq, escolha_dir, df_prof, df_acad, colunas):
    """Comparativo de importância com labels internos em cinza escuro."""
    # Aumentamos o wspace para os gráficos não se chocarem
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(24, 10))
    plt.subplots_adjust(wspace=0.5) 

    def extrair(escolha):
        prefixo = "Profissional: " if escolha.startswith("Profissional:") else "Acadêmico: "
        nome = escolha.replace(prefixo, "")
        df = df_prof if "Profissional" in escolha else df_acad
        return df.loc[nome], nome

    # --- Processamento Lado Esquerdo (Teal) ---
    dados_esq, nome_esq = extrair(escolha_esq)
    imp_esq = pd.Series(dados_esq['modelo'].feature_importances_, index=colunas).sort_values()
    imp_esq.plot(kind='barh', ax=ax1, color='teal', width=0.8)
    
    ax1.set_title(f"Importância: {nome_esq}", fontsize=20, pad=20) # Título maior
    ax1.tick_params(axis='both', labelsize=14) # Nomes das variáveis maiores

    for p in ax1.patches:
        valor = p.get_width()
        # Posicionamos à direita da barra (valor + pequeno espaço)
        ax1.annotate(f'{valor:.2%}', 
                     (valor + 0.02, p.get_y() + p.get_height() / 2),
                     ha='left', va='center', fontsize=13, fontweight='bold',
                     color='white',
                     bbox=dict(boxstyle='round,pad=0.4', fc='#333333', ec='none', alpha=0.9))

    # --- Processamento Lado Direito (Orange) ---
    dados_dir, nome_dir = extrair(escolha_dir)
    imp_dir = pd.Series(dados_dir['modelo'].feature_importances_, index=colunas).sort_values()
    imp_dir.plot(kind='barh', ax=ax2, color='orange', width=0.8)
    
    ax2.set_title(f"Importância: {nome_dir}", fontsize=20, pad=20)
    ax2.tick_params(axis='both', labelsize=14)

    for p in ax2.patches:
        valor = p.get_width()
        ax2.annotate(f'{valor:.2%}', 
                     (valor + 0.02, p.get_y() + p.get_height() / 2),
                     ha='left', va='center', fontsize=13, fontweight='bold',
                     color='white',
                     bbox=dict(boxstyle='round,pad=0.4', fc='#333333', ec='none', alpha=0.9))
    
    # Ajuste de limite para as etiquetas grandes não sumirem
    limite_x = max(imp_esq.max(), imp_dir.max()) + 0.20
    ax1.set_xlim(0, limite_x)
    ax2.set_xlim(0, limite_x)

    plt.show()

def plotar_matrizes_lado_a_lado(escolha_esq, escolha_dir, df_prof, df_acad):
    """Gera duas matrizes de confusão lado a lado para comparação."""
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(16, 6))

    def extrair(escolha):
        if escolha.startswith("Profissional:"):
            nome = escolha.replace("Profissional: ", "")
            return df_prof.loc[nome], nome
        nome = escolha.replace("Acadêmico: ", "")
        return df_acad.loc[nome], nome

    # Esquerda
    d_esq, n_esq = extrair(escolha_esq)
    cm_esq = confusion_matrix(d_esq['y_real'], d_esq['y_previsto'])
    ConfusionMatrixDisplay(cm_esq, display_labels=['Saudável', 'Diabético']).plot(cmap='Blues', ax=ax1, colorbar=False)
    ax1.set_title(f"Esquerda: {n_esq}")

    # Direita
    d_dir, n_dir = extrair(escolha_dir)
    cm_dir = confusion_matrix(d_dir['y_real'], d_dir['y_previsto'])
    ConfusionMatrixDisplay(cm_dir, display_labels=['Saudável', 'Diabético']).plot(cmap='Oranges', ax=ax2, colorbar=False)
    ax2.set_title(f"Direita: {n_dir}")

    plt.tight_layout()
    plt.show()

def plotar_roc_lado_a_lado(escolha_esq, escolha_dir, df_prof, df_acad):
    """Compara as curvas ROC de dois modelos lado a lado com AUC em destaque."""
    fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(20, 8))
    plt.subplots_adjust(wspace=0.3)

    def extrair_e_plotar(escolha, ax, cor):
        prefixo = "Profissional: " if escolha.startswith("Profissional:") else "Acadêmico: "
        nome = escolha.replace(prefixo, "")
        df = df_prof if "Profissional" in escolha else df_acad
        dados = df.loc[nome]
        
        # Cálculo da ROC
        prob = dados['modelo'].predict_proba(dados['X_teste'])[:, 1]
        tfp, tvp, _ = roc_curve(dados['y_real'], prob)
        auc = roc_auc_score(dados['y_real'], prob)
        
        ax.plot(tfp, tvp, color=cor, lw=4, label=f'AUC = {auc:.2%}')
        ax.plot([0, 1], [0, 1], color='#333333', linestyle='--', lw=2) # Referência cinza escuro
        ax.set_title(f"Curva ROC: {nome}", fontsize=16)
        ax.set_xlabel("Falsos Positivos", fontsize=12)
        ax.set_ylabel("Verdadeiros Positivos", fontsize=12)
        ax.legend(loc="lower right", fontsize=14, frameon=True, facecolor='white')
        ax.grid(alpha=0.2)

    extrair_e_plotar(escolha_esq, ax1, 'teal')
    extrair_e_plotar(escolha_dir, ax2, 'orange')
    plt.show()

# ==============================================================================
# 4. DUELO E VEREDITOS
# ==============================================================================

def criar_interface_quadrupla(df_prof, df_acad):
    """Cria interface com 4 menus suspensos para o duelo ROC."""
    opcoes = [f"Profissional: {n}" for n in df_prof.index] + \
             [f"Acadêmico: {n}" for n in df_acad.index]

    # Criando 4 menus (Dropdowns)
    menus = [widgets.Dropdown(options=opcoes, description=f'Mod {i+1}:', value=opcoes[i]) for i in range(4)]

    # Organiza em duas linhas (2 em cima, 2 embaixo)
    linha1 = widgets.HBox([menus[0], menus[1]])
    linha2 = widgets.HBox([menus[2], menus[3]])
    ui = widgets.VBox([linha1, linha2])
    ui.layout.align_items = 'center'

    saida = widgets.interactive_output(plotar_roc_quadrupla_sobreposta, {
        'mod1': menus[0], 'mod2': menus[1], 'mod3': menus[2], 'mod4': menus[3],
        'df_prof': widgets.fixed(df_prof), 'df_acad': widgets.fixed(df_acad)
    })
    
    display(ui, saida)

def plotar_roc_quadrupla_sobreposta(mod1, mod2, mod3, mod4, df_prof, df_acad):
    """Sobrepõe até 4 curvas ROC no mesmo gráfico para um duelo completo."""
    plt.figure(figsize=(12, 9))
    
    escolhas = [mod1, mod2, mod3, mod4]
    # Cores distintas para diferenciar os 4 modelos
    cores = ['#004d40', '#00acc1', '#e65100', '#ffb300'] # Teal escuro, Cyan, Laranja, Amarelo
    
    def extrair_dados(escolha):
        prefixo = "Profissional: " if escolha.startswith("Profissional:") else "Acadêmico: "
        nome = escolha.replace(prefixo, "")
        df = df_prof if "Profissional" in escolha else df_acad
        return df.loc[nome], nome

    for i, escolha in enumerate(escolhas):
        dados, nome = extrair_dados(escolha)
        prob = dados['modelo'].predict_proba(dados['X_teste'])[:, 1]
        tfp, tvp, _ = roc_curve(dados['y_real'], prob)
        auc = roc_auc_score(dados['y_real'], prob)
        
        plt.plot(tfp, tvp, color=cores[i], lw=3, label=f'{nome} (AUC = {auc:.2%})')

    # Linha de referência (Aleatório)
    plt.plot([0, 1], [0, 1], color='#333333', linestyle='--', lw=2, label='Referência (50%)')

    plt.title('Duelo Global de Curvas ROC: Comparativo de 4 Modelos', fontsize=16, pad=20)
    plt.xlabel('Taxa de Falsos Positivos', fontsize=12)
    plt.ylabel('Taxa de Verdadeiros Positivos (Recall)', fontsize=12)
    plt.legend(loc="lower right", fontsize=11, frameon=True, shadow=True)
    plt.grid(alpha=0.2)
    plt.tight_layout()
    plt.show()

def gerar_tabela_comparativa_completa(df_prof, df_acad):
    """
    Gera um ranking completo com todas as métricas, ordenado pela 
    relevância técnica e clínica (AUC e Recall).
    """
    from sklearn.metrics import roc_auc_score
    lista_completa = []

    # Função interna para extrair dados de cada experimento
    def extrair_metricas(df, estrategia):
        for nome, linha in df.iterrows():
            # Cálculo do AUC (Poder de separação)
            prob = linha['modelo'].predict_proba(linha['X_teste'])[:, 1]
            auc_val = roc_auc_score(linha['y_real'], prob)
            
            lista_completa.append({
                'Estratégia': estrategia,
                'Configuração': nome,
                'AUC': auc_val,            # 1º Importância: Capacidade global
                'Recall': linha['Recall'],   # 2º Importância: Segurança (achar doentes)
                'F1-Score': linha['F1-Score'], # 3º Importância: Equilíbrio
                'Precisão': linha['Precisão'], # 4º Importância: Confiança no positivo
                'Acurácia': linha['Acurácia']  # 5º Importância: Acerto geral
            })

    # Processa os dois blocos de dados
    extrair_metricas(df_prof, 'Profissional')
    extrair_metricas(df_acad, 'Acadêmica')

    # Cria o DataFrame e ordena pelo AUC (Poder de Discriminação)
    df_ranking = pd.DataFrame(lista_completa).sort_values(by='AUC', ascending=False)
    
    # Formatação para porcentagem com 2 casas decimais para facilitar a leitura
    colunas_percent = ['AUC', 'Recall', 'F1-Score', 'Precisão', 'Acurácia']
    for col in colunas_percent:
        df_ranking[col] = df_ranking[col].map('{:.2%}'.format)
    
    return df_ranking

def gerar_conclusao_detalhada(df_resultados, tipo="Profissional"):
    """
    Gera um veredito técnico e detalhado unindo métricas de equilíbrio e poder global.
    """
    # Identificação dos líderes (Lógica interna)
    idx_campeao = df_resultados['F1-Score'].idxmax()
    res = df_resultados.loc[idx_campeao]
    
    # Cálculo do AUC para a conclusão
    prob = res['modelo'].predict_proba(res['X_teste'])[:, 1]
    auc_val = roc_auc_score(res['y_real'], prob)

    print(f"{'='*110}")
    print(f"📌 VEREDITO FINAL OTIMIZADO: EXPERIMENTO {tipo.upper()}")
    print(f"{'='*110}")
    print(f"🏆 MODELO CAMPEÃO: {idx_campeao}")
    print(f"💡 ESTRATÉGIA: {'Controle de Profundidade' if tipo=='Profissional' else 'Crescimento Livre'}")
    print(f"{'-'*110}")

    # --- TABULAÇÃO ALINHADA ---
    # O :<45 reserva 45 caracteres de largura para a primeira parte
    print(f"📊 {f'AUC (Poder de Separação): {auc_val:.2%}':<45} -> Avalia a habilidade global de distinguir classes.")
    print(f"⚖️ {f'F1-Score (Equilíbrio Técnico): {res['F1-Score']:.2%}':<45} -> Melhor indicador de estabilidade do modelo.")
    print(f"🎯 {f'Acurácia (Assertividade Geral): {res['Acurácia']:.2%}':<45} -> Porcentagem total de acertos (Saudáveis + Diabéticos).")
    print(f"🩺 {f'Recall (Segurança Clínica): {res['Recall']:.2%}':<45} -> Capacidade de encontrar doentes reais (Sensibilidade).")
    print(f"✅ {f'Precisão (Confiabilidade): {res['Precisão']:.2%}':<45} -> Confiança ao afirmar que um paciente tem diabetes.")
    
    print(f"{'-'*110}")

    print("📝 JUSTIFICATIVA TÉCNICA DETALHADA:")
    
    if tipo.lower() == "profissional":
        print(f"O modelo '{idx_campeao}' foi eleito por sua excelente capacidade de GENERALIZAÇÃO. Com um AUC de {auc_val:.2%}, ele")
        print("demonstra um alto poder intrínseco de distinguir pacientes saudáveis de diabéticos sem precisar de uma")
        print("estrutura complexa. A escolha baseada no F1-Score garante que o modelo não é apenas assertivo, mas sim")
        print("equilibrado, evitando o erro médico de ignorar doentes (Falsos Negativos) ou gerar alarmes excessivos.")
        print("Sua estrutura enxuta é a mais recomendada para implementação em triagem hospitalar devido à sua alta")
        print("estabilidade e facilidade de interpretação clínica.")
    else:
        print(f"O modelo '{idx_campeao}' destacou-se no cenário acadêmico por sua CAPACIDADE EXPLICATIVA. Ao permitir o")
        print(f"crescimento livre da árvore, o algoritmo explorou nuances profundas dos dados, atingindo um Recall de")
        print(f"{res['Recall']:.2%}, o que é vital na detecção de doenças. Entretanto, o AUC de {auc_val:.2%} indica que parte dessa")
        print("performance pode ser sensível à variação dos dados de treino (Split). É um modelo valioso para pesquisa")
        print("e entendimento de correlações complexas, mas exige monitoramento constante contra o 'overfitting'.")
    
    print(f"{'='*110}\n")