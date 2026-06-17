def executar_experimento(X, y, lista_configs, eh_profissional=True):
    """
    Executa os testes, calcula métricas e retorna um DataFrame formatado.
    """
    resultados_lista = []
    
    for conf in lista_configs:
        # Define o split: fixo para profissional, personalizado para acadêmico
        tamanho_teste = SPLIT_TECNICO if eh_profissional else conf["split"]
        # Define a profundidade: conforme a lista ou None (livre)
        profundidade = conf.get("depth") 
        
        # Divisão de Treino e Teste
        X_treino, X_teste, y_treino, y_teste = train_test_split(
            X, y, test_size=tamanho_teste, random_state=1
        )
        
        # Treinamento do Modelo
        modelo_clf = DecisionTreeClassifier(
            criterion=conf["crit"], 
            max_depth=profundidade, 
            random_state=1
        )
        modelo_clf.fit(X_treino, y_treino)
        
        # Predição
        y_previsto = modelo_clf.predict(X_teste)
        
        # Consolidação dos resultados do modelo atual
        resultados_lista.append({
            "Configuração": conf["label"],
            "Acurácia": accuracy_score(y_teste, y_previsto),
            "Precisão": precision_score(y_teste, y_previsto),
            "Recall": recall_score(y_teste, y_previsto),
            "F1-Score": f1_score(y_teste, y_previsto),
            "modelo": modelo_clf,       # Guardamos para plotar árvore
            "y_real": y_teste,          # Guardamos para matriz de confusão
            "y_previsto": y_previsto    # Guardamos para matriz de confusão
        })
    
    # --- A MÁGICA DA TRANSFORMAÇÃO AQUI ---
    # Cria o DataFrame e já define a coluna 'Configuração' como o índice (index)
    df_final = pd.DataFrame(resultados_lista).set_index("Configuração")
    
    return df_final