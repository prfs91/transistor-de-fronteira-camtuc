from pathlib import Path
import numpy as np
from IPython.display import HTML, display

def gerar_laudo_estatistico_iris(df):
    """
    Realiza a análise estatística multivariada automatizada do Dataset Iris
    e emite um relatório executivo em HTML adaptável de alto contraste.
    """
    # 1. Identificação das espécies únicas
    especies = df['Name'].unique()
    features = ['SepalLength', 'SepalWidth', 'PetalLength', 'PetalWidth']
    
    # 2. Construção da Matriz de Médias e Desvios Padrão
    resumo_estatistico = {}
    for esp in especies:
        resumo_estatistico[esp] = {}
        df_esp = df[df['Name'] == esp]
        for feat in features:
            resumo_estatistico[esp][feat] = {
                'media': df_esp[feat].mean(),
                'std': df_esp[feat].std()
            }
            
    # 3. Algoritmo de Identificação de Assinatura Morfológica
    lideres_por_feature = {}
    for feat in features:
        valores_medios = {esp: resumo_estatistico[esp][feat]['media'] for esp in especies}
        maior_especie = max(valores_medios, key=valores_medios.get)
        menor_especie = min(valores_medios, key=valores_medios.get)
        lideres_por_feature[feat] = {'maior': maior_especie, 'menor': menor_especie}

    # 4. Verificação de Sobreposição ou Separação de Clusters (Pétalas vs Sépalas)
    gap_petal_length = resumo_estatistico['Iris-virginica']['PetalLength']['media'] - resumo_estatistico['Iris-versicolor']['PetalLength']['media']
    
    if gap_petal_length > (resumo_estatistico['Iris-virginica']['PetalLength']['std'] + resumo_estatistico['Iris-versicolor']['PetalLength']['std']):
        texto_separacao = "<strong>📈 Alta Discretização Macroscópica:</strong> As dimensões de pétala (comprimento e largura) atuam como discriminadores lineares perfeitos, isolando os grupos sem sobreposição estatística significativa."
        classe_separacao = "border-left: 5px solid #059669; background-color: rgba(5, 150, 105, 0.08);"
    else:
        texto_separacao = "<strong>🔄 Zonas de Intersecção Multivariada:</strong> Existe sobreposição de densidade amostral entre Iris-versicolor e Iris-virginica nos atributos de Sépala, exigindo fronteiras não-lineares para classificação perfeita."
        classe_separacao = "border-left: 5px solid #d97706; background-color: rgba(217, 119, 6, 0.08);"

    # 5. Estruturação da Renderização Dinâmica em HTML Estilizado
    html_linhas = ""
    for feat in features:
        html_linhas += f"""
        <tr>
            <td style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2);"><strong>{feat}</strong> (Média &plusmn; DP)</td>
            <td style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: center;">{resumo_estatistico[especies[0]][feat]['media']:.2f} &plusmn; {resumo_estatistico[especies[0]][feat]['std']:.2f}</td>
            <td style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: center;">{resumo_estatistico[especies[1]][feat]['media']:.2f} &plusmn; {resumo_estatistico[especies[1]][feat]['std']:.2f}</td>
            <td style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: center;">{resumo_estatistico[especies[2]][feat]['media']:.2f} &plusmn; {resumo_estatistico[especies[2]][feat]['std']:.2f}</td>
        </tr>
        """

    html_output = f"""
    <div style="font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Arial, sans-serif; line-height: 1.6; margin-top: 20px; color: inherit;">
        <h3 style="color: inherit; border-bottom: 2px solid rgba(128, 128, 128, 0.2); padding-bottom: 8px;">📋 Diagnóstico Estatístico Automatizado (Iris Dataset)</h3>
        
        <table style="width: 100%; border-collapse: collapse; margin-bottom: 20px; background-color: transparent; color: inherit;">
            <tr style="background-color: rgba(128, 128, 128, 0.05);">
                <th style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: left;">Dimensão Morfológica</th>
                <th style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: center; color: #0056b3;">{especies[0]}</th>
                <th style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: center; color: #d97706;">{especies[1]}</th>
                <th style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: center; color: #2e7d32;">{especies[2]}</th>
            </tr>
            {html_linhas}
        </table>

        <div style="{classe_separacao} padding: 14px; border-radius: 4px; margin-bottom: 14px; font-size: 13.5px; color: inherit;">
            {texto_separacao}
        </div>

        <div style="border-left: 5px solid #0056b3; background-color: rgba(0, 86, 179, 0.04); padding: 14px; border-radius: 4px; font-size: 13.5px; color: inherit;">
            <strong>🎯 Assinatura de Agrupamentos:</strong> A espécie <strong>{lideres_por_feature['PetalLength']['maior']}</strong> apresenta os maiores índices volumétricos de pétala, enquanto a espécie <strong>{lideres_por_feature['PetalLength']['menor']}</strong> demonstra nanismo morfológico relativo nestas características, atuando como um cluster isolado.
        </div>
    </div>
    """
    display(HTML(html_output))