import subprocess
import matplotlib.pyplot as plt

TAM_ENTRADAS = [1000, 50000, 100000, 500000, 1000000]
EXECUCOES = 100

def executar_teste(tam, opcao, busca_val):
    print(f"testando opcao {opcao}, tamanho {tam}")
    elementos_vetor = " ".join(str(i) for i in range(0, tam))  # range garante vetor ordenado

    if opcao == 1:
        entrada = f"{tam}\n{elementos_vetor}\n{opcao}\n5\n"
    else:
        entrada = f"{tam}\n{elementos_vetor}\n{opcao}\n{busca_val}\n5\n"

    tempos = []
    atrib = 0
    comp = 0
    
    for _ in range(EXECUCOES):
        resultado = subprocess.run(
            ["./trabalho1_bench"],
            input=entrada,
            text=True,
            capture_output=True
        )

        
        saida = resultado.stdout.strip().split("|")
        tempo = float(saida[0].strip())
        atrib = int(saida[1].strip())
        comp = int(saida[2].strip())

        tempos.append(tempo)

    tempo_medio = sum(tempos) / len(tempos)
    return tempo_medio, atrib, comp


def grafico_geral(resultados):
    plt.figure(figsize=(10, 9))
    for nome, res in resultados.items():
        tempos = [r[0] for r in res]
        plt.plot(TAM_ENTRADAS, tempos, marker='o', label=nome)

    plt.xlabel("Tamanho da entrada (n)")
    plt.ylabel("Tempo médio de execução (s)")  
    plt.title("Tempo de execução por tamanho de entrada — Pior Caso")
    
    plt.xticks(TAM_ENTRADAS)
    plt.ticklabel_format(style='plain', axis='x') 
    
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.savefig("grafico_tempos.png", dpi=150)
    plt.show()


def grafico_binarias(resultados):
    plt.figure(figsize=(10, 9))
    tempos_it = [d[0] for d in resultados["Busca Binária Iterativa"]]
    tempos_rec = [d[0] for d in resultados["Busca Binária Recursiva"]]
    
    plt.plot(TAM_ENTRADAS, tempos_it, marker='o', label="Busca Binária Iterativa")
    plt.plot(TAM_ENTRADAS, tempos_rec, marker='o', label="Busca Binária Recursiva")
    
    plt.xlabel("Tamanho da entrada (n)")
    plt.ylabel("Tempo médio de execução (s)")  
    plt.title("Tempo de execução — Buscas Binárias (Pior Caso)")
    
    plt.xticks(TAM_ENTRADAS)
    plt.ticklabel_format(style='plain', axis='x')
    
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.savefig("grafico_tempos_binarias.png", dpi=150)
    plt.show()


def main():
    subprocess.run(["gcc", "trabalho1_bench.c", "-o", "trabalho1_bench"], check=True)

    resultados = {
        "Inversão": [],
        "Busca Sequencial": [],
        "Busca Binária Iterativa": [],
        "Busca Binária Recursiva": []
    }

    for tam in TAM_ENTRADAS:
        print(f"testando para {tam}")
        
        resultados["Inversão"].append(executar_teste(tam, 1, 0))

        pior_caso = tam + 1 

        resultados["Busca Sequencial"].append(executar_teste(tam, 2, pior_caso))
        resultados["Busca Binária Iterativa"].append(executar_teste(tam, 3, pior_caso))
        resultados["Busca Binária Recursiva"].append(executar_teste(tam, 4, pior_caso))

   
    print("\n" + "="*80)
    print(f"{'Operação':<26} | {'Tamanho':<10} | {'Tempo (s)':<15} | {'Atribuições':<12} | {'Comparações':<12}")
    print("="*80)
    for nome in resultados:
        for i, tam in enumerate(TAM_ENTRADAS):
            t, a, c = resultados[nome][i]
            print(f"{nome:<26} | {tam:<10} | {t:<15.9f} | {a:<12} | {c:<12}")
        print("-" * 80)

    grafico_geral(resultados)
    grafico_binarias(resultados)


if __name__ == "__main__":
    main()