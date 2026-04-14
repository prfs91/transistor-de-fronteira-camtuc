import matplotlib.pyplot as plt
import numpy as np

fig, ax = plt.subplots()

frutas = ['maça','pera','uva']
quantidade = [10,20,50]
bar_label = ['maça','pera','uva']
bar_colors = ['tab:red', 'tab:orange', 'tab:green']

erro = [q * 0.01 for q in quantidade]

ax.bar(frutas, 
       quantidade, 
       label=bar_label, 
       color=bar_colors, 
       edgecolor='black', 
       linewidth=1,
       yerr=erro,
       capsize=12)

ax.plot(frutas, quantidade, color)

plt.xlabel('Variedades das Frutas', fontsize=18, color='blue')
plt.ylabel('Quantidade das Frutas', fontsize=18, color='blue')
plt.xticks(fontsize=12)
plt.title('Frutas disponíveis hoje', fontsize=30, color='red')
plt.yticks(np.arange(0,50,5), fontsize=12)
plt.grid(True)

plt.show()