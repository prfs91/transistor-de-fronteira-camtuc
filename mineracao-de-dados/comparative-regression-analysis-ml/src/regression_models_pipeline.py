# ==========================================================
# PIPELINE DE MODELOS DE REGRESSÃO
# comparative-regression-analysis-ml
# ==========================================================

# ==========================================================
# VERIFICAÇÃO DE DEPENDÊNCIAS
# ==========================================================

import sys
import subprocess
import importlib

PACOTES = {
    "pandas": "pandas",
    "numpy": "numpy",
    "matplotlib": "matplotlib",
    "seaborn": "seaborn",
    "scikit-learn": "sklearn"
}

for nome_pip, nome_importacao in PACOTES.items():

    try:
        importlib.import_module(nome_importacao)

    except ImportError:

        print(f"[INSTALANDO] {nome_pip}")

        subprocess.check_call([
            sys.executable,
            "-m",
            "pip",
            "install",
            nome_pip
        ])

# ==========================================================
# IMPORTAÇÃO DAS BIBLIOTECAS
# ==========================================================

# Manipulação de dados
import pandas as pd
import numpy as np

# Visualização
import matplotlib.pyplot as plt
import seaborn as sns

# Dataset
from sklearn.datasets import load_iris

# Divisão dos dados
from sklearn.model_selection import (
    train_test_split,
    cross_val_score
)

# Pré-processamento
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline

# Modelos
from sklearn.linear_model import LinearRegression
from sklearn.svm import SVR
from sklearn.gaussian_process import GaussianProcessRegressor
from sklearn.gaussian_process.kernels import RBF

# Métricas
from sklearn.metrics import (
    r2_score,
    mean_absolute_error,
    mean_squared_error,
    root_mean_squared_error
)

# Bibliotecas nativas do Python
from pathlib import Path
import time # Tempo computacional


# ==========================================================
# FUNÇÕES DE CARREGAMENTO E PREPARAÇÃO
# ==========================================================

def carregar_dataset_iris():
    """
    Carrega o dataset Iris e retorna um DataFrame.
    """

    iris = load_iris()

    base_dados = pd.DataFrame(
        iris.data,
        columns=iris.feature_names
    )

    base_dados["species"] = iris.target

    return base_dados


def salvar_dataset_csv(base_dados, caminho_arquivo):
    """
    Salva o dataset em formato CSV.
    """

    base_dados.to_csv(
        caminho_arquivo,
        index=False
    )


def definir_variaveis(
    base_dados,
    coluna_x="sepal length (cm)",
    coluna_y="petal length (cm)"
):
    """
    Define variáveis independentes e dependentes.
    """

    X = base_dados[[coluna_x]]
    y = base_dados[coluna_y]

    return X, y


def dividir_dados(
    X,
    y,
    tamanho_teste=0.2,
    random_state=40
):
    """
    Divide os dados em treino e teste.
    """

    return train_test_split(
        X,
        y,
        test_size=tamanho_teste,
        random_state=random_state
    )

# ==========================================================
# FUNÇÕES DE TREINAMENTO
# ==========================================================

def treinar_regressao_linear(
    X_treino,
    y_treino
):
    """
    Treina modelo de Regressão Linear.
    """

    inicio = time.time()

    modelo = LinearRegression(fit_intercept=True)

    modelo.fit(
        X_treino,
        y_treino
    )

    fim = time.time()

    tempo_treinamento = fim - inicio

    return modelo, tempo_treinamento


def treinar_svr(
    X_treino,
    y_treino,
    kernel="rbf",
    C=100,
    epsilon=0.1,
    gamma="scale"
):
    """
    Treina modelo Support Vector Regression.
    """

    inicio = time.time()

    modelo = make_pipeline(
        StandardScaler(),
        SVR(
            kernel=kernel,
            C=C,
            epsilon=epsilon,
            gamma=gamma
        )
    )

    modelo.fit(
        X_treino,
        y_treino
    )

    fim = time.time()

    tempo_treinamento = fim - inicio

    return modelo, tempo_treinamento


def treinar_gpr(
    X_treino,
    y_treino,
    length_scale=1.0,
    bounds=(1e-1, 1e3),
    alpha=1e-2,
    random_state=42
):
    """
    Treina modelo Gaussian Process Regression.
    """

    kernel = RBF(
        length_scale=length_scale,
        length_scale_bounds=bounds
    )

    inicio = time.time()

    modelo = GaussianProcessRegressor(
        kernel=kernel,
        alpha=alpha,
        random_state=random_state
    )

    modelo.fit(
        X_treino,
        y_treino
    )

    fim = time.time()

    tempo_treinamento = fim - inicio

    return modelo, tempo_treinamento

# ==========================================================
# FUNÇÕES DE PREDIÇÃO
# ==========================================================

def realizar_predicoes(
    modelo,
    X_teste
):
    """
    Realiza predições simples.
    """

    return modelo.predict(X_teste)


def realizar_predicoes_gpr(
    modelo,
    X_teste
):
    """
    Realiza predições com desvio padrão no GPR.
    """

    return modelo.predict(
        X_teste,
        return_std=True
    )

# ==========================================================
# FUNÇÕES DE MÉTRICAS
# ==========================================================

def calcular_metricas(
    y_real,
    y_predito
):
    """
    Calcula métricas de regressão.
    """

    r2 = r2_score(
        y_real,
        y_predito
    )

    mae = mean_absolute_error(
        y_real,
        y_predito
    )

    mse = mean_squared_error(
        y_real,
        y_predito
    )

    rmse = root_mean_squared_error(
        y_real,
        y_predito
    )

    return {
        "R2": r2,
        "MAE": mae,
        "MSE": mse,
        "RMSE": rmse
    }

# ==========================================================
# VALIDAÇÃO CRUZADA
# ==========================================================

def executar_validacao_cruzada(
    modelo,
    X,
    y,
    folds=5
):
    """
    Executa validação cruzada.
    """

    scores = cross_val_score(
        modelo,
        X,
        y,
        cv=folds,
        scoring="r2"
    )

    return scores

# ==========================================================
# DATAFRAME DE MÉTRICAS
# ==========================================================

def criar_dataframe_metricas(
    metricas_linear,
    metricas_svr,
    metricas_gpr
):
    """
    Cria DataFrame comparativo de métricas.
    """

    dataframe_metricas = pd.DataFrame({
        "Modelo": [
            "Linear",
            "SVR",
            "GPR"
        ],

        "R²": [
            metricas_linear["R2"],
            metricas_svr["R2"],
            metricas_gpr["R2"]
        ],

        "MAE": [
            metricas_linear["MAE"],
            metricas_svr["MAE"],
            metricas_gpr["MAE"]
        ],

        "MSE": [
            metricas_linear["MSE"],
            metricas_svr["MSE"],
            metricas_gpr["MSE"]
        ],

        "RMSE": [
            metricas_linear["RMSE"],
            metricas_svr["RMSE"],
            metricas_gpr["RMSE"]
        ]
    })

    return dataframe_metricas

# ==========================================================
# DATAFRAME DE TEMPO COMPUTACIONAL
# ==========================================================

def criar_dataframe_tempos(
    tempo_linear,
    tempo_svr,
    tempo_gpr
):
    """
    Cria DataFrame comparativo de tempo.
    """

    dataframe_tempos = pd.DataFrame({
        "Modelo": [
            "Linear",
            "SVR",
            "GPR"
        ],

        "Tempo": [
            tempo_linear,
            tempo_svr,
            tempo_gpr
        ]
    })

    return dataframe_tempos

# ==========================================================
# FUNÇÕES DE RESÍDUOS
# ==========================================================

def calcular_residuos(
    y_real,
    y_predito
):
    """
    Calcula resíduos do modelo.
    """

    return y_real - y_predito

# ==========================================================
# FUNÇÕES DE VISUALIZAÇÃO
# ==========================================================

def plotar_heatmap(
    base_dados,
    salvar=False,
    caminho_saida=None
):
    """
    Gera heatmap de correlação.
    """

    plt.figure(figsize=(10, 8))

    matriz_correlacao = base_dados.corr(
        numeric_only=True
    )

    sns.heatmap(
        matriz_correlacao,
        annot=True,
        cmap="coolwarm",
        fmt=".2f",
        linewidths=0.5
    )

    plt.title(
        "Heatmap de Correlação das Variáveis",
        fontsize=14
    )

    # Ajusta automaticamente os espaçamentos
    plt.tight_layout()

    # ======================================================
    # SALVAR FIGURA
    # ======================================================

    if salvar and caminho_saida is not None:

        plt.savefig(
            caminho_saida,
            dpi=300,
            bbox_inches="tight"
        )

        print(f"Figura salva em: {caminho_saida}")

    plt.show()

def plotar_comparacao_metricas(
    dataframe_metricas,
    metrica,
    salvar=False,
    caminho_saida=None
):
    """
    Plota comparação entre métricas.
    """

    plt.figure(figsize=(9, 6))

    # ======================================================
    # BARRAS
    # ======================================================

    barras = plt.bar(
        dataframe_metricas["Modelo"],
        dataframe_metricas[metrica],
        alpha=0.8
    )

    # ======================================================
    # VALORES SOBRE AS BARRAS
    # ======================================================

    for barra in barras:

        altura = barra.get_height()

        plt.text(
            barra.get_x() + barra.get_width() / 2,
            altura + 0.01,
            f"{altura:.3f}",
            ha="center",
            va="bottom",
            fontsize=10,
            fontweight="bold"
        )

    # ======================================================
    # TÍTULO E EIXOS
    # ======================================================

    plt.title(
        f"Comparação da Métrica {metrica}",
        fontsize=14,
        fontweight="bold"
    )

    plt.xlabel(
        "Modelos de Regressão",
        fontsize=11
    )

    plt.ylabel(
        metrica,
        fontsize=11
    )

    # ======================================================
    # GRADE HORIZONTAL
    # ======================================================

    plt.grid(
        axis="y",
        linestyle="--",
        alpha=0.5
    )

    # ======================================================
    # EXPLICAÇÃO DIDÁTICA
    # ======================================================

    if metrica == "R²":

        texto_explicativo = (
            "Quanto maior o valor de R², "
            "melhor o desempenho do modelo."
        )

    else:

        texto_explicativo = (
            f"Quanto menor o valor de {metrica}, "
            "menor o erro do modelo."
        )

    plt.figtext(
        0.5,
        -0.03,
        texto_explicativo,
        ha="center",
        fontsize=10
    )

    plt.tight_layout()

    # ======================================================
    # SALVAR FIGURA
    # ======================================================

    if salvar and caminho_saida is not None:

        plt.savefig(
            caminho_saida,
            dpi=300,
            bbox_inches="tight"
        )

        print(
            f"Figura salva em: {caminho_saida}"
        )
    
    plt.show()

def plotar_painel_comparativo_metricas(
    dataframe_metricas,
    salvar=False,
    caminho_saida=None
):
    """
    Gera painel comparativo 2x2 das métricas
    de regressão.
    """

    # ======================================================
    # DADOS
    # ======================================================

    modelos_nomes = dataframe_metricas["Modelo"]

    valores_r2 = dataframe_metricas["R²"]
    valores_mse = dataframe_metricas["MSE"]
    valores_rmse = dataframe_metricas["RMSE"]
    valores_mae = dataframe_metricas["MAE"]

    cores_modelos = [
        "steelblue",
        "darkorange",
        "mediumpurple"
    ]

    # ======================================================
    # FIGURA PRINCIPAL
    # ======================================================

    fig, axes = plt.subplots(
        2,
        2,
        figsize=(14, 10)
    )

    fig.suptitle(
        (
            "Comparação de Métricas "
            "— Regressão Linear × SVR × GPR"
        ),
        fontsize=16,
        fontweight="bold"
    )

    # ======================================================
    # FUNÇÃO AUXILIAR
    # ======================================================

    def configurar_barras(
        eixo,
        valores,
        titulo,
        ylabel,
        maior_melhor=True
    ):

        barras = eixo.bar(
            modelos_nomes,
            valores,
            color=cores_modelos,
            edgecolor="black",
            linewidth=0.7,
            alpha=0.85
        )

        eixo.set_title(
            titulo,
            fontweight="bold"
        )

        eixo.set_ylabel(
            ylabel
        )

        eixo.grid(
            axis="y",
            linestyle="--",
            alpha=0.5
        )

        # ==================================================
        # VALORES SOBRE AS BARRAS
        # ==================================================

        for barra, valor in zip(barras, valores):

            eixo.text(
                barra.get_x() + barra.get_width() / 2,
                valor,
                f"{valor:.4f}",
                ha="center",
                va="bottom",
                fontsize=10,
                fontweight="bold"
            )

        # ==================================================
        # MELHOR MODELO
        # ==================================================

        if maior_melhor:

            indice_melhor = np.argmax(valores)

        else:

            indice_melhor = np.argmin(valores)

        barras[indice_melhor].set_edgecolor(
            "gold"
        )

        barras[indice_melhor].set_linewidth(3)

    # ======================================================
    # R²
    # ======================================================

    configurar_barras(
        axes[0, 0],
        valores_r2,
        "R² (↑ maior é melhor)",
        "R²",
        maior_melhor=True
    )

    axes[0, 0].set_ylim(0, 1.1)

    # ======================================================
    # MSE
    # ======================================================

    configurar_barras(
        axes[0, 1],
        valores_mse,
        "MSE (↓ menor é melhor)",
        "MSE",
        maior_melhor=False
    )

    # ======================================================
    # RMSE
    # ======================================================

    configurar_barras(
        axes[1, 0],
        valores_rmse,
        "RMSE (↓ menor é melhor)",
        "RMSE",
        maior_melhor=False
    )

    # ======================================================
    # MAE
    # ======================================================

    configurar_barras(
        axes[1, 1],
        valores_mae,
        "MAE (↓ menor é melhor)",
        "MAE",
        maior_melhor=False
    )

    # ======================================================
    # TEXTO DIDÁTICO
    # ======================================================

    plt.figtext(
        0.5,
        0.01,
        (
            "Borda dourada indica o melhor modelo "
            "para cada métrica."
        ),
        ha="center",
        fontsize=11
    )

    plt.tight_layout()

    # ======================================================
    # SALVAR FIGURA
    # ======================================================

    if salvar and caminho_saida is not None:

        plt.savefig(
            caminho_saida,
            dpi=300,
            bbox_inches="tight"
        )

        print(
            f"Figura salva em: {caminho_saida}"
        )

    plt.show()

def plotar_tempos_computacionais(
    dataframe_tempos,
    salvar=False,
    caminho_saida=None
):
    """
    Plota gráfico de tempo computacional.
    """

    plt.figure(figsize=(9, 6))

    # ======================================================
    # BARRAS
    # ======================================================

    barras = plt.bar(
        dataframe_tempos["Modelo"],
        dataframe_tempos["Tempo"],
        alpha=0.8
    )

    # ======================================================
    # VALORES SOBRE AS BARRAS
    # ======================================================

    for barra in barras:

        altura = barra.get_height()

        plt.text(
            barra.get_x() + barra.get_width() / 2,
            altura,
            f"{altura:.5f}s",
            ha="center",
            va="bottom",
            fontsize=10,
            fontweight="bold"
        )

    # ======================================================
    # TÍTULO E EIXOS
    # ======================================================

    plt.title(
        "Comparação de Tempo de Treinamento",
        fontsize=14,
        fontweight="bold"
    )

    plt.xlabel(
        "Modelos de Regressão",
        fontsize=11
    )

    plt.ylabel(
        "Tempo (segundos)",
        fontsize=11
    )

    # ======================================================
    # GRADE
    # ======================================================

    plt.grid(
        axis="y",
        linestyle="--",
        alpha=0.5
    )

    # ======================================================
    # TEXTO DIDÁTICO
    # ======================================================

    plt.figtext(
        0.5,
        -0.03,
        (
            "Menores tempos indicam maior eficiência computacional "
            "durante o treinamento."
        ),
        ha="center",
        fontsize=10
    )

    plt.tight_layout()

    # ======================================================
    # SALVAR FIGURA
    # ======================================================

    if salvar and caminho_saida is not None:

        plt.savefig(
            caminho_saida,
            dpi=300,
            bbox_inches="tight"
        )

        print(
            f"Figura salva em: {caminho_saida}"
        )
    plt.show()

def plotar_residuos(
    y_predito,
    residuos,
    titulo,
    salvar=False,
    caminho_saida=None
):
    """
    Plota análise de resíduos.
    """

    plt.figure(figsize=(10, 6))

    plt.scatter(
        y_predito,
        residuos,
        alpha=0.7
    )

    # Linha horizontal central
    plt.axhline(
        y=0,
        linestyle="--",
        linewidth=2
    )

    plt.title(
        titulo,
        fontsize=14,
        fontweight="bold"
    )

    plt.xlabel(
        "Valores Preditos",
        fontsize=11
    )

    plt.ylabel(
        "Resíduos",
        fontsize=11
    )

    # Grade horizontal
    plt.grid(
        linestyle="--",
        alpha=0.5
    )

    # Explicação didática
    plt.figtext(
        0.5,
        -0.03,
        (
            "Resíduos próximos de zero indicam "
            "melhor ajuste do modelo."
        ),
        ha="center",
        fontsize=10
    )

    plt.tight_layout()

    # ======================================================
    # SALVAR FIGURA
    # ======================================================

    if salvar and caminho_saida is not None:

        plt.savefig(
            caminho_saida,
            dpi=300,
            bbox_inches="tight"
        )

        print(
            f"Figura salva em: {caminho_saida}"
        )

    plt.show()

def plotar_painel_residuos(
    y_teste,
    y_pred_linear,
    y_pred_svr,
    y_pred_gpr,
    salvar=False,
    caminho_saida=None
):
    """
    Gera painel comparativo de resíduos
    para os modelos de regressão.
    """

    # ======================================================
    # CÁLCULO DOS RESÍDUOS
    # ======================================================

    residuos_linear = (
        y_teste - y_pred_linear
    )

    residuos_svr = (
        y_teste - y_pred_svr
    )

    residuos_gpr = (
        y_teste - y_pred_gpr
    )

    # ======================================================
    # FIGURA PRINCIPAL
    # ======================================================

    fig, eixos = plt.subplots(
        1,
        3,
        figsize=(18, 6)
    )

    fig.suptitle(
        (
            "Análise de Resíduos dos Modelos\n"
            "Ideal: distribuição aleatória ao redor da linha zero"
        ),
        fontsize=14,
        fontweight="bold"
    )

    # ======================================================
    # CONFIGURAÇÕES DOS MODELOS
    # ======================================================

    configuracoes_modelos = [

        (
            "Regressão Linear",
            y_pred_linear,
            residuos_linear,
            "steelblue",
            eixos[0]
        ),

        (
            "Support Vector Regression (SVR)",
            y_pred_svr,
            residuos_svr,
            "darkorange",
            eixos[1]
        ),

        (
            "Gaussian Process Regression (GPR)",
            y_pred_gpr,
            residuos_gpr,
            "mediumpurple",
            eixos[2]
        )
    ]

    # ======================================================
    # PLOTAGEM
    # ======================================================

    for (
        nome_modelo,
        valores_preditos,
        residuos,
        cor,
        eixo
    ) in configuracoes_modelos:

        eixo.scatter(
            valores_preditos,
            residuos,
            color=cor,
            alpha=0.75,
            edgecolors="black",
            linewidth=0.5,
            s=70
        )

        # ==================================================
        # LINHA ZERO
        # ==================================================

        eixo.axhline(
            y=0,
            color="black",
            linestyle="--",
            linewidth=1.5
        )

        # ==================================================
        # RMSE
        # ==================================================

        valor_rmse = np.sqrt(
            mean_squared_error(
                y_teste,
                valores_preditos
            )
        )

        # ==================================================
        # TÍTULO
        # ==================================================

        eixo.set_title(
            (
                f"{nome_modelo}\n"
                f"RMSE = {valor_rmse:.4f} cm"
            ),
            fontweight="bold"
        )

        # ==================================================
        # EIXOS
        # ==================================================

        eixo.set_xlabel(
            "Valor Predito (cm)"
        )

        eixo.set_ylabel(
            "Resíduo (Real − Predito)"
        )

        # ==================================================
        # GRADE
        # ==================================================

        eixo.grid(
            linestyle="--",
            alpha=0.5
        )

    # ======================================================
    # TEXTO DIDÁTICO
    # ======================================================

    plt.figtext(
        0.5,
        0.01,
        (
            "Resíduos próximos da linha zero indicam "
            "melhor capacidade de ajuste do modelo."
        ),
        ha="center",
        fontsize=11
    )

    plt.tight_layout()

    # ======================================================
    # SALVAR FIGURA
    # ======================================================

    if salvar and caminho_saida is not None:

        plt.savefig(
            caminho_saida,
            dpi=300,
            bbox_inches="tight"
        )

        print(
            f"Figura salva em: {caminho_saida}"
        )

    plt.show()

def plotar_gpr_intervalos_confianca(
    modelo_gpr,
    X_treino,
    X_teste,
    y_teste,
    especies_teste,
    salvar=False,
    caminho_saida=None
):
    """
    Gera gráfico do Gaussian Process Regression
    com intervalos de confiança de 68% e 95%.
    """

    # ======================================================
    # GERAÇÃO DA GRADE
    # ======================================================

    X_grade = np.linspace(
        X_treino.min(),
        X_treino.max(),
        300
    ).reshape(-1, 1)

    # ======================================================
    # PREDIÇÕES GPR
    # ======================================================

    y_predito_grade, desvio_padrao = (
        modelo_gpr.predict(
            X_grade,
            return_std=True
        )
    )

    # ======================================================
    # MÁSCARAS DAS ESPÉCIES
    # ======================================================

    mascara_setosa = (
        especies_teste == "setosa"
    )

    mascara_versicolor = (
        especies_teste == "versicolor"
    )

    mascara_virginica = (
        especies_teste == "virginica"
    )

    # ======================================================
    # FIGURA
    # ======================================================

    plt.figure(figsize=(12, 7))

    # ======================================================
    # PONTOS REAIS
    # ======================================================

    plt.scatter(
        X_teste[mascara_setosa],
        y_teste[mascara_setosa],
        color="green",
        label="Setosa (teste)",
        zorder=5,
        s=70
    )

    plt.scatter(
        X_teste[mascara_versicolor],
        y_teste[mascara_versicolor],
        color="blue",
        label="Versicolor (teste)",
        zorder=5,
        s=70
    )

    plt.scatter(
        X_teste[mascara_virginica],
        y_teste[mascara_virginica],
        color="red",
        label="Virginica (teste)",
        zorder=5,
        s=70
    )

    # ======================================================
    # CURVA GPR
    # ======================================================

    plt.plot(
        X_grade,
        y_predito_grade,
        color="mediumpurple",
        linewidth=2.5,
        label="Previsão GPR"
    )

    # ======================================================
    # INTERVALO 95%
    # ======================================================

    plt.fill_between(
        X_grade[:, 0],
        y_predito_grade - 1.96 * desvio_padrao,
        y_predito_grade + 1.96 * desvio_padrao,
        alpha=0.20,
        color="mediumpurple",
        label="Intervalo de Confiança 95%"
    )

    # ======================================================
    # INTERVALO 68%
    # ======================================================

    plt.fill_between(
        X_grade[:, 0],
        y_predito_grade - desvio_padrao,
        y_predito_grade + desvio_padrao,
        alpha=0.35,
        color="mediumpurple",
        label="Intervalo de Confiança 68%"
    )

    # ======================================================
    # TÍTULO E EIXOS
    # ======================================================

    plt.title(
        (
            "Gaussian Process Regression (GPR)\n"
            "Predição com Intervalos de Confiança"
        ),
        fontsize=14,
        fontweight="bold"
    )

    plt.xlabel(
        "Comprimento da Pétala (cm)",
        fontsize=11
    )

    plt.ylabel(
        "Comprimento da Sépala (cm)",
        fontsize=11
    )

    # ======================================================
    # GRADE
    # ======================================================

    plt.grid(
        linestyle="--",
        alpha=0.5
    )

    # ======================================================
    # LEGENDA
    # ======================================================

    plt.legend(
        loc="upper left"
    )

    # ======================================================
    # TEXTO DIDÁTICO
    # ======================================================

    plt.figtext(
        0.5,
        -0.03,
        (
            "Regiões mais largas indicam maior "
            "incerteza nas predições do modelo."
        ),
        ha="center",
        fontsize=10
    )

    plt.tight_layout()

    # ======================================================
    # SALVAR FIGURA
    # ======================================================

    if salvar and caminho_saida is not None:

        plt.savefig(
            caminho_saida,
            dpi=300,
            bbox_inches="tight"
        )

        print(
            f"Figura salva em: {caminho_saida}"
        )

    plt.show()

def plotar_curvas_aprendizado(
    X,
    y,
    salvar=False,
    caminho_saida=None
):
    """
    Gera curvas de aprendizado para os modelos
    de regressão.
    """

    # ======================================================
    # IMPORTAÇÃO LOCAL
    # ======================================================

    from sklearn.model_selection import (
        learning_curve
    )

    from sklearn.gaussian_process.kernels import (
        ConstantKernel as C
    )

    # ======================================================
    # FIGURA PRINCIPAL
    # ======================================================

    figura, eixos = plt.subplots(
        1,
        3,
        figsize=(18, 6)
    )

    figura.suptitle(
        (
            "Curvas de Aprendizado dos Modelos\n"
            "Avaliação da evolução do desempenho "
            "com aumento dos dados de treino"
        ),
        fontsize=14,
        fontweight="bold"
    )

    # ======================================================
    # CONFIGURAÇÃO DOS MODELOS
    # ======================================================

    configuracoes_modelos = [

        (
            "Regressão Linear",
            LinearRegression(),
            "steelblue",
            eixos[0]
        ),

        (
            "Support Vector Regression (SVR)",
            make_pipeline(
                StandardScaler(),
                SVR(
                    kernel="rbf",
                    C=1.0,
                    epsilon=0.1
                )
            ),
            "darkorange",
            eixos[1]
        ),

        (
            "Gaussian Process Regression (GPR)",
            GaussianProcessRegressor(
                kernel=C(1.0) * RBF(1.0),
                alpha=1e-2,
                n_restarts_optimizer=5,
                random_state=42
            ),
            "mediumpurple",
            eixos[2]
        )
    ]

    # ======================================================
    # GERAÇÃO DAS CURVAS
    # ======================================================

    for (
        nome_modelo,
        modelo,
        cor,
        eixo
    ) in configuracoes_modelos:

        (
            tamanhos_treino,
            scores_treino,
            scores_validacao
        ) = learning_curve(

            modelo,
            X,
            y,

            train_sizes=np.linspace(
                0.1,
                1.0,
                10
            ),

            cv=5,
            scoring="r2"
        )

        # ==================================================
        # MÉDIAS
        # ==================================================

        media_treino = (
            scores_treino.mean(axis=1)
        )

        media_validacao = (
            scores_validacao.mean(axis=1)
        )

        # ==================================================
        # DESVIOS PADRÃO
        # ==================================================

        desvio_treino = (
            scores_treino.std(axis=1)
        )

        desvio_validacao = (
            scores_validacao.std(axis=1)
        )

        # ==================================================
        # CURVA DE TREINO
        # ==================================================

        eixo.plot(
            tamanhos_treino,
            media_treino,
            "o-",
            color=cor,
            label="Treino",
            linewidth=2
        )

        # ==================================================
        # CURVA DE VALIDAÇÃO
        # ==================================================

        eixo.plot(
            tamanhos_treino,
            media_validacao,
            "s--",
            color="gray",
            label="Validação",
            linewidth=2
        )

        # ==================================================
        # INTERVALOS DE VARIAÇÃO
        # ==================================================

        eixo.fill_between(
            tamanhos_treino,
            media_treino - desvio_treino,
            media_treino + desvio_treino,
            alpha=0.15,
            color=cor
        )

        eixo.fill_between(
            tamanhos_treino,
            media_validacao - desvio_validacao,
            media_validacao + desvio_validacao,
            alpha=0.15,
            color="gray"
        )

        # ==================================================
        # TÍTULO
        # ==================================================

        eixo.set_title(
            nome_modelo,
            fontweight="bold"
        )

        # ==================================================
        # EIXOS
        # ==================================================

        eixo.set_xlabel(
            "Quantidade de Amostras de Treino"
        )

        eixo.set_ylabel(
            "R²"
        )

        eixo.set_ylim(
            -0.1,
            1.05
        )

        # ==================================================
        # GRADE
        # ==================================================

        eixo.grid(
            linestyle="--",
            alpha=0.5
        )

        # ==================================================
        # LEGENDA
        # ==================================================

        eixo.legend(
            fontsize=9
        )

    # ======================================================
    # TEXTO DIDÁTICO
    # ======================================================

    plt.figtext(
        0.5,
        0.01,
        (
            "Curvas mais próximas indicam melhor "
            "capacidade de generalização do modelo."
        ),
        ha="center",
        fontsize=11
    )

    plt.tight_layout()

    # ======================================================
    # SALVAR FIGURA
    # ======================================================

    if salvar and caminho_saida is not None:

        plt.savefig(
            caminho_saida,
            dpi=300,
            bbox_inches="tight"
        )

        print(
            f"Figura salva em: {caminho_saida}"
        )

    plt.show()

def plotar_painel_real_vs_previsto(
    y_teste,
    y_pred_linear,
    y_pred_svr,
    y_pred_gpr,
    salvar=False,
    caminho_saida=None
):
    """
    Gera painel comparativo entre valores
    reais e previstos dos modelos.
    """

    # ======================================================
    # FIGURA PRINCIPAL
    # ======================================================

    figura, eixos = plt.subplots(
        1,
        3,
        figsize=(18, 6)
    )

    figura.suptitle(
        (
            "Valores Reais × Valores Previstos\n"
            "Quanto mais próximos da diagonal, "
            "melhor o desempenho do modelo"
        ),
        fontsize=14,
        fontweight="bold"
    )

    # ======================================================
    # CONFIGURAÇÃO DOS MODELOS
    # ======================================================

    configuracoes_modelos = [

        (
            "Regressão Linear",
            y_pred_linear,
            "steelblue",
            eixos[0]
        ),

        (
            "Support Vector Regression (SVR)",
            y_pred_svr,
            "darkorange",
            eixos[1]
        ),

        (
            "Gaussian Process Regression (GPR)",
            y_pred_gpr,
            "mediumpurple",
            eixos[2]
        )
    ]

    # ======================================================
    # LIMITES DOS EIXOS
    # ======================================================

    limite_minimo = min(
        y_teste.min(),
        y_pred_linear.min(),
        y_pred_svr.min(),
        y_pred_gpr.min()
    ) - 0.05

    limite_maximo = max(
        y_teste.max(),
        y_pred_linear.max(),
        y_pred_svr.max(),
        y_pred_gpr.max()
    ) + 0.05

    # ======================================================
    # PLOTAGEM
    # ======================================================

    for (
        nome_modelo,
        valores_preditos,
        cor,
        eixo
    ) in configuracoes_modelos:

        # ==================================================
        # SCATTER
        # ==================================================

        eixo.scatter(
            y_teste,
            valores_preditos,
            color=cor,
            alpha=0.75,
            edgecolors="black",
            linewidth=0.5,
            s=70
        )

        # ==================================================
        # LINHA IDEAL
        # ==================================================

        eixo.plot(
            [limite_minimo, limite_maximo],
            [limite_minimo, limite_maximo],
            "k--",
            linewidth=1.8,
            label="Linha Ideal"
        )

        # ==================================================
        # R²
        # ==================================================

        valor_r2 = r2_score(
            y_teste,
            valores_preditos
        )

        # ==================================================
        # LIMITES
        # ==================================================

        eixo.set_xlim(
            limite_minimo,
            limite_maximo
        )

        eixo.set_ylim(
            limite_minimo,
            limite_maximo
        )

        # ==================================================
        # EIXOS
        # ==================================================

        eixo.set_xlabel(
            "Valor Real (cm)"
        )

        eixo.set_ylabel(
            "Valor Predito (cm)"
        )

        # ==================================================
        # TÍTULO
        # ==================================================

        eixo.set_title(
            (
                f"{nome_modelo}\n"
                f"R² = {valor_r2:.4f}"
            ),
            fontweight="bold"
        )

        # ==================================================
        # GRADE
        # ==================================================

        eixo.grid(
            linestyle="--",
            alpha=0.5
        )

        # ==================================================
        # LEGENDA
        # ==================================================

        eixo.legend(
            fontsize=9
        )

    # ======================================================
    # TEXTO DIDÁTICO
    # ======================================================

    plt.figtext(
        0.5,
        0.01,
        (
            "Pontos mais próximos da diagonal indicam "
            "menor erro de predição."
        ),
        ha="center",
        fontsize=11
    )

    plt.tight_layout()

    # ======================================================
    # SALVAR FIGURA
    # ======================================================

    if salvar and caminho_saida is not None:

        plt.savefig(
            caminho_saida,
            dpi=300,
            bbox_inches="tight"
        )

        print(
            f"Figura salva em: {caminho_saida}"
        )

    plt.show()

def plotar_gpr_com_incerteza(
    X_teste,
    y_teste,
    y_pred_gpr,
    desvio_padrao,
    especies_teste,
    salvar=False,
    caminho_saida=None
):
    """
    Gera gráfico do Gaussian Process Regression
    com intervalo de confiança.
    """
    # ======================================================
    # EXTRAÇÃO DA FEATURE DO EIXO X
    # ======================================================

    valores_x = (
        X_teste.iloc[:, 0]
    )

    # ======================================================
    # ORDENAÇÃO DOS DADOS
    # ======================================================

    indices_ordenados = (
        valores_x.argsort()
    )

    X_ordenado = (
        valores_x.iloc[indices_ordenados]
    )

    y_predito_ordenado = (
        y_pred_gpr[indices_ordenados]
    )

    desvio_ordenado = (
        desvio_padrao[indices_ordenados]
    )

    # ======================================================
    # MÁSCARAS DAS ESPÉCIES
    # ======================================================

    mascara_setosa = (
        especies_teste == "setosa"
    )

    mascara_versicolor = (
        especies_teste == "versicolor"
    )

    mascara_virginica = (
        especies_teste == "virginica"
    )

    # ======================================================
    # FIGURA
    # ======================================================

    plt.figure(figsize=(12, 7))

    # ======================================================
    # PONTOS REAIS
    # ======================================================

    plt.scatter(
        valores_x.loc[mascara_setosa],
        y_teste.loc[mascara_setosa],
        color="green",
        label="Setosa",
        s=70,
        edgecolors="black",
        linewidth=0.5
    )

    plt.scatter(
        valores_x.loc[mascara_versicolor],
        y_teste.loc[mascara_versicolor],
        color="blue",
        label="Versicolor",
        s=70,
        edgecolors="black",
        linewidth=0.5
    )

    plt.scatter(
        valores_x.loc[mascara_virginica],
        y_teste.loc[mascara_virginica],
        color="red",
        label="Virginica",
        s=70,
        edgecolors="black",
        linewidth=0.5
    )

    # ======================================================
    # CURVA GPR
    # ======================================================

    plt.plot(
        X_ordenado,
        y_predito_ordenado,
        color="mediumpurple",
        linewidth=2.5,
        label="Predição GPR"
    )

    # ======================================================
    # INTERVALO DE CONFIANÇA 95%
    # ======================================================

    plt.fill_between(
        X_ordenado,

        y_predito_ordenado
        - 1.96 * desvio_ordenado,

        y_predito_ordenado
        + 1.96 * desvio_ordenado,

        alpha=0.25,
        color="mediumpurple",

        label=(
            "Intervalo de Confiança 95%"
        )
    )

    # ======================================================
    # TÍTULO
    # ======================================================

    plt.title(
        (
            "Gaussian Process Regression (GPR)\n"
            "Predição com Intervalo de Confiança"
        ),
        fontsize=14,
        fontweight="bold"
    )

    # ======================================================
    # EIXOS
    # ======================================================

    plt.xlabel(
        "Comprimento da Sépala (cm)",
        fontsize=11
    )

    plt.ylabel(
        "Comprimento da Pétala (cm)",
        fontsize=11
    )

    # ======================================================
    # GRADE
    # ======================================================

    plt.grid(
        linestyle="--",
        alpha=0.5
    )

    # ======================================================
    # LEGENDA
    # ======================================================

    plt.legend(
        loc="upper left"
    )

    # ======================================================
    # TEXTO DIDÁTICO
    # ======================================================

    plt.figtext(
        0.5,
        -0.03,
        (
            "Faixas mais largas indicam maior "
            "incerteza do modelo nas previsões."
        ),
        ha="center",
        fontsize=10
    )

    plt.tight_layout()

    # ======================================================
    # SALVAR FIGURA
    # ======================================================

    if salvar and caminho_saida is not None:

        plt.savefig(
            caminho_saida,
            dpi=300,
            bbox_inches="tight"
        )

        print(
            f"Figura salva em: {caminho_saida}"
        )

    plt.show()

def plotar_svr_predicoes(
    X_teste,
    y_teste,
    y_pred_svr,
    especies_teste,
    salvar=False,
    caminho_saida=None
):
    """
    Gera gráfico das predições do modelo
    Support Vector Regression (SVR).
    """

    # ======================================================
    # ORDENAÇÃO DOS DADOS
    # ======================================================

    indices_ordenados = (
        X_teste.iloc[:, 0].argsort()
    )

    X_ordenado = (
        X_teste.iloc[indices_ordenados]
    )

    y_predito_ordenado = (
        y_pred_svr[indices_ordenados]
    )

    # ======================================================
    # MÁSCARAS DAS ESPÉCIES
    # ======================================================

    mascara_setosa = (
        especies_teste == "setosa"
    )

    mascara_versicolor = (
        especies_teste == "versicolor"
    )

    mascara_virginica = (
        especies_teste == "virginica"
    )

    # ======================================================
    # FIGURA
    # ======================================================

    plt.figure(figsize=(12, 7))

    # ======================================================
    # PONTOS REAIS
    # ======================================================

    plt.scatter(
        X_teste[mascara_setosa],
        y_teste[mascara_setosa],
        color="green",
        label="Setosa",
        s=70,
        edgecolors="black",
        linewidth=0.5
    )

    plt.scatter(
        X_teste[mascara_versicolor],
        y_teste[mascara_versicolor],
        color="blue",
        label="Versicolor",
        s=70,
        edgecolors="black",
        linewidth=0.5
    )

    plt.scatter(
        X_teste[mascara_virginica],
        y_teste[mascara_virginica],
        color="red",
        label="Virginica",
        s=70,
        edgecolors="black",
        linewidth=0.5
    )

    # ======================================================
    # CURVA SVR
    # ======================================================

    plt.plot(
        X_ordenado,
        y_predito_ordenado,
        color="darkorange",
        linewidth=2.5,
        label="Predição SVR (Kernel RBF)"
    )

    # ======================================================
    # TÍTULO
    # ======================================================

    plt.title(
        (
            "Support Vector Regression (SVR)\n"
            "Predição Não Linear com Kernel RBF"
        ),
        fontsize=14,
        fontweight="bold"
    )

    # ======================================================
    # EIXOS
    # ======================================================

    plt.xlabel(
        "Comprimento da Sépala (cm)",
        fontsize=11
    )

    plt.ylabel(
        "Comprimento da Pétala (cm)",
        fontsize=11
    )

    # ======================================================
    # GRADE
    # ======================================================

    plt.grid(
        linestyle="--",
        alpha=0.5
    )

    # ======================================================
    # LEGENDA
    # ======================================================

    plt.legend(
        loc="upper left"
    )

    # ======================================================
    # TEXTO DIDÁTICO
    # ======================================================

    plt.figtext(
        0.5,
        -0.03,
        (
            "O SVR utiliza um kernel para modelar "
            "relações não lineares entre os dados."
        ),
        ha="center",
        fontsize=10
    )

    plt.tight_layout()

    # ======================================================
    # SALVAR FIGURA
    # ======================================================

    if salvar and caminho_saida is not None:

        plt.savefig(
            caminho_saida,
            dpi=300,
            bbox_inches="tight"
        )

        print(
            f"Figura salva em: {caminho_saida}"
        )

    plt.show()

def plotar_regressao_linear_predicoes(
    X_teste,
    y_teste,
    y_pred_linear,
    especies_teste,
    salvar=False,
    caminho_saida=None
):
    """
    Gera gráfico das predições do modelo
    de Regressão Linear.
    """

    # ======================================================
    # ORDENAÇÃO DOS DADOS
    # ======================================================

    indices_ordenados = (
        X_teste[:, 0].argsort()
    )

    X_ordenado = (
        X_teste.iloc[indices_ordenados]
    )

    y_predito_ordenado = (
        y_pred_linear[indices_ordenados]
    )

    # ======================================================
    # MÁSCARAS DAS ESPÉCIES
    # ======================================================

    mascara_setosa = (
        especies_teste == "setosa"
    )

    mascara_versicolor = (
        especies_teste == "versicolor"
    )

    mascara_virginica = (
        especies_teste == "virginica"
    )

    # ======================================================
    # FIGURA
    # ======================================================

    plt.figure(figsize=(12, 7))

    # ======================================================
    # PONTOS REAIS
    # ======================================================

    plt.scatter(
        X_teste.loc[mascara_setosa].iloc[:, 0],
        y_teste[mascara_setosa],
        color="green",
        label="Setosa",
        s=70,
        edgecolors="black",
        linewidth=0.5
    )

    plt.scatter(
        X_teste.loc[mascara_versicolor].iloc[:, 0],
        y_teste[mascara_versicolor],
        color="blue",
        label="Versicolor",
        s=70,
        edgecolors="black",
        linewidth=0.5
    )

    plt.scatter(
        X_teste.loc[mascara_virginica].iloc[:, 0],
        y_teste[mascara_virginica],
        color="red",
        label="Virginica",
        s=70,
        edgecolors="black",
        linewidth=0.5
    )

    # ======================================================
    # LINHA DE REGRESSÃO
    # ======================================================

    plt.plot(
        X_ordenado.iloc[:, 0],
        y_predito_ordenado,
        color="black",
        linewidth=2.5,
        label="Linha de Regressão Linear"
    )

    # ======================================================
    # TÍTULO
    # ======================================================

    plt.title(
        (
            "Regressão Linear\n"
            "Ajuste Linear dos Dados"
        ),
        fontsize=14,
        fontweight="bold"
    )

    # ======================================================
    # EIXOS
    # ======================================================

    plt.xlabel(
        "Comprimento da Sépala (cm)",
        fontsize=11
    )

    plt.ylabel(
        "Comprimento da Pétala (cm)",
        fontsize=11
    )

    # ======================================================
    # GRADE
    # ======================================================

    plt.grid(
        linestyle="--",
        alpha=0.5
    )

    # ======================================================
    # LEGENDA
    # ======================================================

    plt.legend(
        loc="upper left"
    )

    # ======================================================
    # TEXTO DIDÁTICO
    # ======================================================

    plt.figtext(
        0.5,
        -0.03,
        (
            "A Regressão Linear busca encontrar "
            "a melhor reta para representar "
            "a relação entre os dados."
        ),
        ha="center",
        fontsize=10
    )

    plt.tight_layout()

    # ======================================================
    # SALVAR FIGURA
    # ======================================================

    if salvar and caminho_saida is not None:

        plt.savefig(
            caminho_saida,
            dpi=300,
            bbox_inches="tight"
        )

        print(
            f"Figura salva em: {caminho_saida}"
        )

    plt.show()

def plotar_distribuicao_iris(
    base_dados,
    salvar=False,
    caminho_saida=None
):
    """
    Gera gráfico de distribuição das espécies
    do conjunto de dados Iris.
    """

    # ======================================================
    # FIGURA
    # ======================================================

    plt.figure(figsize=(12, 7))

    # ======================================================
    # SCATTERPLOT
    # ======================================================

    grafico = sns.scatterplot(
        data=base_dados,

        x="petal length (cm)",
        y="petal width (cm)",

        hue="species",

        palette="viridis",

        s=80,

        edgecolor="black",
        linewidth=0.5
    )

    # ======================================================
    # TÍTULO
    # ======================================================

    plt.title(
        (
            "Distribuição das Espécies do Dataset Iris\n"
            "Comprimento × Largura da Pétala"
        ),
        fontsize=14,
        fontweight="bold"
    )

    # ======================================================
    # EIXOS
    # ======================================================

    plt.xlabel(
        "Comprimento da Pétala (cm)",
        fontsize=11
    )

    plt.ylabel(
        "Largura da Pétala (cm)",
        fontsize=11
    )

    # ======================================================
    # GRADE
    # ======================================================

    plt.grid(
        linestyle="--",
        alpha=0.5
    )

    # ======================================================
    # LEGENDA
    # ======================================================

    plt.legend(
        title="Espécies",
        loc="lower right"
    )

    # ======================================================
    # TEXTO DIDÁTICO
    # ======================================================

    plt.figtext(
        0.5,
        -0.03,
        (
            "Cada cor representa uma espécie "
            "diferente do conjunto Iris."
        ),
        ha="center",
        fontsize=10
    )

    plt.tight_layout()

    # ======================================================
    # SALVAR FIGURA
    # ======================================================

    if salvar and caminho_saida is not None:

        plt.savefig(
            caminho_saida,
            dpi=300,
            bbox_inches="tight"
        )

        print(
            f"Figura salva em: {caminho_saida}"
        )

    plt.show()


# ==========================================================
# EXECUÇÃO DIRETA
# ==========================================================

if __name__ == "__main__":

    print("=" * 60)
    print("PIPELINE DE REGRESSÃO EXECUTADO COM SUCESSO")
    print("=" * 60)

    base_dados = carregar_dataset_iris()

    print("\nDataset carregado.")
    print(base_dados.head())