import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.lines import Line2D
from sklearn.tree import DecisionTreeClassifier, plot_tree
from sklearn.model_selection import train_test_split
from sklearn.metrics import (
    accuracy_score, f1_score, precision_score, 
    recall_score, confusion_matrix, ConfusionMatrixDisplay,
    roc_curve, roc_auc_score
)


# ==========================================
# 1. CONSTANTES E CONFIGURAÇÕES
# ==========================================

SPLIT_TECNICO = 0.25

TRADUCAO_COLUNAS = {
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
# 2. FUNÇÕES DE PROCESSAMENTO E MODELAGEM
# ==========================================

def separar_recursos_e_alvo(df, coluna_alvo='Resultado'):
    """Separa o DataFrame em variáveis explicativas (X) e alvo (y)."""
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

# ==========================================
# 3. FUNÇÕES DE VISUALIZAÇÃO (GRÁFICOS)
# ==========================================

def plotar_comparativo_metricas(df_res, titulo, eixo_x):
    """Gera gráfico de barras comparando o desempenho das configurações."""
    metricas = ['Acurácia', 'Precisão', 'Recall', 'F1-Score']
    ax = df_res[metricas].plot(kind='bar', figsize=(12, 6), rot=0)
    
    plt.title(titulo)
    plt.ylabel('Valores (0 a 1)')
    plt.xlabel(eixo_x)
    plt.legend(loc='lower right')
    plt.grid(axis='y', linestyle='--', alpha=0.7)
    plt.tight_layout()
    plt.show()

def plotar_importancia_variaveis(modelo, colunas, titulo_config):
    """Plota a importância de cada variável no modelo escolhido."""
    plt.figure(figsize=(10, 5))
    importancia = pd.Series(modelo.feature_importances_, index=colunas)
    importancia.sort_values().plot(kind='barh', color='teal')
    
    plt.title(f"Importância das Variáveis: {titulo_config}")
    plt.xlabel("Grau de Importância (0 a 1)")
    plt.ylabel("Atributos do Dataset")
    plt.grid(axis='x', linestyle='--', alpha=0.5)
    plt.tight_layout()
    plt.show()

def plotar_matriz_confusao(y_real, y_previsto, titulo_config):
    """Gera a matriz de confusão para avaliar erros e acertos."""
    plt.figure(figsize=(8, 6))
    cm = confusion_matrix(y_real, y_previsto)
    disp = ConfusionMatrixDisplay(confusion_matrix=cm, display_labels=['Saudável', 'Diabético'])
    
    disp.plot(cmap='Blues', ax=plt.gca())
    plt.title(f"Matriz de Confusão: {titulo_config}")
    plt.grid(False)
    plt.show()

def visualizar_arvore(modelo, colunas, titulo_config):
    """Gera imagem da árvore de decisão em alta resolução."""
    plt.figure(figsize=(55, 18), dpi=120) 
    plot_tree(modelo, 
              feature_names=colunas,  
              class_names=['Saudável', 'Diabético'],
              filled=True, rounded=True, max_depth=3,      
              fontsize=25, precision=2, impurity=False) 
    
    plt.title(f"Árvore de Decisão: {titulo_config}", fontsize=24)
    plt.show()

def plotar_comparativo_final(melhor_prof, melhor_acad):
    """
    Gera um gráfico comparando a melhor performance de cada experimento.
    """
    plt.figure(figsize=(8, 5))
    
    experimentos = ['Profissional (Estável)', 'Acadêmico (Livre)']
    valores = [melhor_prof, melhor_acad]
    cores = ['teal', 'orange']
    
    # Criando as barras
    barras = plt.bar(experimentos, valores, color=cores, alpha=0.8)
    
    # Adicionando o valor em cima da barra
    for barra in barras:
        yval = barra.get_height()
        plt.text(barra.get_x() + barra.get_width()/2, yval + 0.01, 
                 f'{yval:.2%}', ha='center', va='bottom', fontweight='bold')

    plt.title('Duelo de Performance: Melhor Acurácia de Cada Experimento')
    plt.ylabel('Acurácia (%)')
    plt.ylim(0, 1.0) # Escala de 0 a 100%
    plt.grid(axis='y', linestyle='--', alpha=0.3)
    
    plt.show()

def plotar_curva_roc(modelo, X_teste, y_real, titulo_config):
    """
    Gera o gráfico da Curva ROC e calcula o valor AUC.
    """
    # Para a Curva ROC, precisamos das probabilidades (predict_proba)
    # Pegamos apenas a probabilidade da classe 1 (Diabético)
    y_probabilidade = modelo.predict_proba(X_teste)[:, 1]
    
    # Calculamos a taxa de falsos positivos e verdadeiros positivos
    tfp, tvp, _ = roc_curve(y_real, y_probabilidade)
    auc = roc_auc_score(y_real, y_probabilidade)
    
    plt.figure(figsize=(8, 6))
    plt.plot(tfp, tvp, color='darkorange', lw=2, label=f'Curva ROC (AUC = {auc:.2f})')
    plt.plot([0, 1], [0, 1], color='navy', lw=2, linestyle='--') # Linha aleatória
    
    plt.xlim([0.0, 1.0])
    plt.ylim([0.0, 1.05])
    plt.xlabel('Taxa de Falsos Positivos (1 - Especificidade)')
    plt.ylabel('Taxa de Verdadeiros Positivos (Sensibilidade/Recall)')
    plt.title(f'Curva ROC: {titulo_config}')
    plt.legend(loc="lower right")
    plt.grid(alpha=0.3)
    plt.show()

def plotar_comparativo_roc(modelo_prof, X_prof, y_prof, modelo_acad, X_acad, y_acad):
    """
    Plota as curvas ROC do modelo Profissional e Acadêmico no mesmo gráfico.
    """
    plt.figure(figsize=(9, 7))
    
    # Dados do Modelo Profissional
    prob_prof = modelo_prof.predict_proba(X_prof)[:, 1]
    tfp_p, tvp_p, _ = roc_curve(y_prof, prob_prof)
    auc_prof = roc_auc_score(y_prof, prob_prof)
    
    # Dados do Modelo Acadêmico
    prob_acad = modelo_acad.predict_proba(X_acad)[:, 1]
    tfp_a, tvp_a, _ = roc_curve(y_acad, prob_acad)
    auc_acad = roc_auc_score(y_acad, prob_acad)
    
    # Plotagem das linhas
    plt.plot(tfp_p, tvp_p, color='teal', lw=3, label=f'Profissional (AUC = {auc_prof:.2f})')
    plt.plot(tfp_a, tvp_a, color='orange', lw=3, label=f'Acadêmico (AUC = {auc_acad:.2f})')
    
    # Linha de referência (aleatória)
    plt.plot([0, 1], [0, 1], color='gray', lw=1, linestyle='--')
    
    plt.title('Duelo de Curvas ROC: Profissional vs Acadêmico', fontsize=14)
    plt.xlabel('Taxa de Falsos Positivos')
    plt.ylabel('Taxa de Verdadeiros Positivos (Recall)')
    plt.legend(loc="lower right")
    plt.grid(alpha=0.2)
    plt.show()

def plotar_roc_multiplos(df_resultados, titulo):
    """
    Plota as curvas ROC de todos os modelos contidos no DataFrame de resultados.
    """
    plt.figure(figsize=(10, 8))
    
    # Percorre cada linha do DataFrame (cada configuração testada)
    for rotulo, linha in df_resultados.iterrows():
        modelo = linha['modelo']
        X_teste = linha['X_teste']
        y_real = linha['y_real']
        
        # Calcula as métricas da curva
        probabilidades = modelo.predict_proba(X_teste)[:, 1]
        tfp, tvp, _ = roc_curve(y_real, probabilidades)
        auc = roc_auc_score(y_real, probabilidades)
        
        # Plota a linha com o nome da configuração e o valor do AUC
        plt.plot(tfp, tvp, lw=2, label=f'{rotulo} (AUC = {auc:.2f})')

    # Linha de referência aleatória
    plt.plot([0, 1], [0, 1], color='gray', lw=1, linestyle='--')
    
    plt.title(f'Comparativo ROC: {titulo}')
    plt.xlabel('Taxa de Falsos Positivos')
    plt.ylabel('Taxa de Verdadeiros Positivos (Recall)')
    plt.legend(loc="lower right", fontsize='small')
    plt.grid(alpha=0.2)
    plt.show()

def plotar_duelo_geral(df_prof, df_acad):
    """
    Une todos os resultados em um único gráfico para comparação total.
    """
    # Unimos as tabelas adicionando uma coluna para identificar a origem
    df_prof_temp = df_prof.copy()
    df_acad_temp = df_acad.copy()
    
    # Criamos o DataFrame unificado apenas com a métrica de Acurácia
    df_unificado = pd.concat([df_prof_temp['Acurácia'], df_acad_temp['Acurácia']])
    
    plt.figure(figsize=(15, 6))
    
    # Definimos cores diferentes: Tons de azul para Profissional, Tons de laranja para Acadêmico
    cores = ['teal'] * len(df_prof) + ['orange'] * len(df_acad)
    
    ax = df_unificado.plot(kind='bar', color=cores, alpha=0.8, rot=45)
    
    # Adicionando os valores em cima das barras
    for p in ax.patches:
        ax.annotate(f'{p.get_height():.2%}', 
                    (p.get_x() + p.get_width() / 2., p.get_height()), 
                    ha='center', va='center', xytext=(0, 9), 
                    textcoords='offset points', fontsize=10, fontweight='bold')

    plt.title('Comparativo Geral: Todos os Modelos (Profissional vs Acadêmico)')
    plt.ylabel('Acurácia (%)')
    plt.xlabel('Configurações Testadas')
    plt.ylim(0, 1.0)
    plt.grid(axis='y', linestyle='--', alpha=0.3)
    plt.tight_layout()
    plt.show()

def plotar_duelo_geral_destacado(df_prof, df_acad):
    """
    Plota todos os modelos destacando com cores fortes os vencedores de cada grupo.
    """
    # Unificamos as acurácias
    df_unificado = pd.concat([df_prof['Acurácia'], df_acad['Acurácia']])
    
    # Identificamos quem é o melhor de cada grupo
    idx_melhor_prof = df_prof['Acurácia'].idxmax()
    idx_melhor_acad = df_acad['Acurácia'].idxmax()
    
    # Definimos a lógica de cores
    # Profissional: Verde Escuro (Melhor), Verde Claro (Outros)
    # Acadêmico: Laranja Escuro (Melhor), Laranja Claro (Outros)
    cores = []
    for nome in df_unificado.index:
        if nome == idx_melhor_prof:
            cores.append('#004d40') # Teal escuro
        elif nome in df_prof.index:
            cores.append('#80cbc4') # Teal claro
        elif nome == idx_melhor_acad:
            cores.append('#e65100') # Laranja escuro
        else:
            cores.append('#ffcc80') # Laranja claro

    plt.figure(figsize=(15, 7))
    ax = df_unificado.plot(kind='bar', color=cores, alpha=0.9, rot=45)
    
    # Adicionando os valores e um marcador especial nos vencedores
    for i, p in enumerate(ax.patches):
        valor = p.get_height()
        nome_atual = df_unificado.index[i]
        
        # Se for um dos vencedores, coloca a fonte em negrito e um destaque
        peso_fonte = 'bold' if (nome_atual in [idx_melhor_prof, idx_melhor_acad]) else 'normal'
        
        ax.annotate(f'{valor:.2%}', 
                    (p.get_x() + p.get_width() / 2., valor), 
                    ha='center', va='bottom', xytext=(0, 5), 
                    textcoords='offset points', fontsize=11, fontweight=peso_fonte)

    plt.title('Comparativo Geral: Destaque dos Melhores Modelos', fontsize=16)
    plt.ylabel('Acurácia (%)')
    plt.ylim(0, 1.0)
    plt.grid(axis='y', linestyle='--', alpha=0.3)
    
    # Legenda customizada
    from matplotlib.lines import Line2D
    legend_elements = [
        Line2D([0], [0], color='#004d40', lw=4, label='Melhor Profissional'),
        Line2D([0], [0], color='#e65100', lw=4, label='Melhor Acadêmico')
    ]
    plt.legend(handles=legend_elements, loc='upper left')
    
    plt.tight_layout()
    plt.show()



def plotar_duelo_geral_ordenado(df_prof, df_acad):
    """
    Une, ordena por acurácia e plota os modelos com legenda completa para as 4 cores.
    """
    # 1. Unificamos e ordenamos as acurácias
    df_unificado = pd.concat([df_prof['Acurácia'], df_acad['Acurácia']]).sort_values()
    
    # 2. Identificamos os vencedores de cada grupo
    idx_melhor_prof = df_prof['Acurácia'].idxmax()
    idx_melhor_acad = df_acad['Acurácia'].idxmax()
    
    # 3. Definição das Cores
    cor_prof_top = '#004d40'  # Teal Escuro
    cor_prof_norm = '#80cbc4' # Teal Claro
    cor_acad_top = '#e65100'  # Laranja Escuro
    cor_acad_norm = '#ffcc80' # Laranja Claro
    
    cores = []
    for nome in df_unificado.index:
        if nome == idx_melhor_prof:
            cores.append(cor_prof_top)
        elif nome in df_prof.index:
            cores.append(cor_prof_norm)
        elif nome == idx_melhor_acad:
            cores.append(cor_acad_top)
        else:
            cores.append(cor_acad_norm)

    # 4. Plotagem
    plt.figure(figsize=(15, 8))
    ax = df_unificado.plot(kind='bar', color=cores, alpha=0.9, rot=45)
    
    # Rótulos de porcentagem
    for i, p in enumerate(ax.patches):
        valor = p.get_height()
        nome_atual = df_unificado.index[i]
        peso = 'bold' if (nome_atual in [idx_melhor_prof, idx_melhor_acad]) else 'normal'
        ax.annotate(f'{valor:.2%}', (p.get_x() + p.get_width()/2., valor), 
                    ha='center', va='bottom', xytext=(0, 5), 
                    textcoords='offset points', fontsize=11, fontweight=peso)

    # 5. LEGENDA COMPLETA (4 CORES)
    elementos_legenda = [
        Line2D([0], [0], color=cor_prof_top, lw=8, label='Melhor Profissional'),
        Line2D([0], [0], color=cor_prof_norm, lw=8, label='Outros Profissionais'),
        Line2D([0], [0], color=cor_acad_top, lw=8, label='Melhor Acadêmico'),
        Line2D([0], [0], color=cor_acad_norm, lw=8, label='Outros Acadêmicos')
    ]
    plt.legend(handles=elementos_legenda, loc='upper left', title="Categorias e Destaques")

    plt.title('Ranking Geral de Performance: Profissional vs Acadêmico', fontsize=16)
    plt.ylabel('Acurácia (%)')
    plt.ylim(0, 1.1)
    plt.grid(axis='y', linestyle='--', alpha=0.3)
    plt.tight_layout()
    plt.show()




# ==========================================
# 4. EXECUÇÃO (MODO SCRIPT)
# ==========================================
if __name__ == "__main__":
    print("Biblioteca de Diabetes carregada com sucesso.")
    print("Importe as funções no seu Notebook (.ipynb) para começar.")
