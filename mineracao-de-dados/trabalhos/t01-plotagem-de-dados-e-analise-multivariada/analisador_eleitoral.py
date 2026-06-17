from IPython.display import HTML, display

def gerar_relatorio_completo(candidato_a, candidato_b, margem_erro=1):
    """
    Processa dados eleitorais temporais com caminhos relativos universais
    e exibe o painel estatístico em HTML adaptável de alto contraste.
    """
    # 1. Extração Estatística de Pontos e Picos de Amostragem
    pos_inicial_A, pos_inicial_B = candidato_a[0], candidato_b[0]
    pos_final_A, pos_final_B = candidato_a[-1], candidato_b[-1]
    max_A, max_B = max(candidato_a), max(candidato_b)
    pesq_max_A = candidato_a.index(max_A) + 1
    pesq_max_B = candidato_b.index(max_B) + 1

    # 2. Algoritmo de Detecção Dinâmica de Cruzamento de Trajetórias (Troca de Liderança)
    cruzamentos = []
    for i in range(1, len(candidato_a)):
        lider_anterior = "A" if candidato_a[i - 1] > candidato_b[i - 1] else "B"
        lider_atual = "A" if candidato_a[i] > candidato_b[i] else "B"
        if candidato_a[i - 1] == candidato_b[i - 1]:
            lider_anterior = "Empate"

        if lider_anterior != lider_atual and lider_anterior != "Empate":
            cruzamentos.append(f"Pesquisa {i+1}")

    # Estilização de Alto Contraste para o Cruzamento
    if cruzamentos:
        texto_cruzamento = f"<strong>🔄 Inversão de Cenário Detectada:</strong> Houve mudança direta na liderança durante a transição para a(s) seguinte(s) amostra(s): {', '.join(cruzamentos)}."
        classe_cruzamento = "border-left: 5px solid #d97706; background-color: rgba(217, 119, 6, 0.08); color: inherit;"
    else:
        texto_cruzamento = "<strong>📈 Estabilidade de Trajetória:</strong> Não foram detectadas inversões de liderança direta. Um candidato manteve a hegemonia em todo o espectro temporal analisado."
        classe_cruzamento = "border-left: 5px solid #059669; background-color: rgba(5, 150, 105, 0.08); color: inherit;"

    # 3. Algoritmo de Avaliação Em Tempo Real de Empate Técnico
    limite_empate = 2 * margem_erro
    pesquisas_empate = []

    for i in range(len(candidato_a)):
        if abs(candidato_a[i] - candidato_b[i]) <= limite_empate:
            pesquisas_empate.append(f"P{i+1}")

    # Estilização de Alto Contraste para o Empate Técnico
    if pesquisas_empate:
        texto_empate = f"<strong>⚖️ Zonas de Empate Técnico:</strong> Os candidatos encontram-se em situação de equivalência estatística na(s) amostra(s): {', '.join(pesquisas_empate)} (Diferença &le; {limite_empate}%)."
        classe_empate = "border-left: 5px solid #dc2626; background-color: rgba(220, 38, 38, 0.08); color: inherit;"
    else:
        texto_empate = f"<strong>❌ Distanciamento Estatístico Conclusivo:</strong> Em todas as medições avaliadas, a distância real entre os concorrentes foi superior à margem crítica estabelecida de {limite_empate}%, descartando cenários de empate técnico."
        classe_empate = "border-left: 5px solid #059669; background-color: rgba(5, 150, 105, 0.08); color: inherit;"

    # 4. Estruturação da Renderização do Painel Executivo
    html_output = f"""
    <div style="font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto, Helvetica, Arial, sans-serif; line-height: 1.6; margin-top: 20px; color: inherit;">
        <h3 style="color: inherit; border-bottom: 2px solid rgba(128, 128, 128, 0.2); padding-bottom: 8px;">📋 Painel Analítico Automatizado (Laudo Técnico)</h3>
        
        <table style="width: 100%; border-collapse: collapse; margin-bottom: 20px; background-color: transparent; color: inherit;">
            <tr style="background-color: rgba(128, 128, 128, 0.05);">
                <th style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: left;">Métrica Estatística</th>
                <th style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: center; color: #0056b3;">Candidato A</th>
                <th style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: center; color: #d97706;">Candidato B</th>
            </tr>
            <tr>
                <td style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2);"><strong>Ponto Amostral Inicial (Pesquisa 1)</strong></td>
                <td style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: center;">{pos_inicial_A}%</td>
                <td style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: center;">{pos_inicial_B}%</td>
            </tr>
            <tr>
                <td style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2);"><strong>Ponto Amostral Final (Pesquisa 7)</strong></td>
                <td style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: center;">{pos_final_A}%</td>
                <td style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: center;">{pos_final_B}%</td>
            </tr>
            <tr>
                <td style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2);"><strong>Pico Absoluto de Intenções</strong></td>
                <td style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: center;">{max_A}% <span style="font-size: 11px; opacity: 0.7;">(Pesq. {pesq_max_A})</span></td>
                <td style="padding: 10px; border: 1px solid rgba(128, 128, 128, 0.2); text-align: center;">{max_B}% <span style="font-size: 11px; opacity: 0.7;">(Pesq. {pesq_max_B})</span></td>
            </tr>
        </table>

        <div style="{classe_cruzamento} padding: 14px; border-radius: 4px; margin-bottom: 14px; font-size: 13.5px; box-shadow: 0 1px 3px rgba(0,0,0,0.05);">
            {texto_cruzamento}
        </div>

        <div style="{classe_empate} padding: 14px; border-radius: 4px; font-size: 13.5px; box-shadow: 0 1px 3px rgba(0,0,0,0.05);">
            {texto_empate}
        </div>
    </div>
    """
    display(HTML(html_output))