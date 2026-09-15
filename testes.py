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
    for _ in range(EXECUCOES):
        resultado = subprocess.run(
            ["./trabalho1_bench"],
            input=entrada,
            text=True,
            capture_output=True
        )

        tempo = float(resultado.stdout.strip())
        tempos.append(tempo)

    return sum(tempos) / len(tempos)


def grafico_geral(resultados):
    plt.figure(figsize=(10, 9))
    for nome, tempos in resultados.items():
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
    plt.plot(TAM_ENTRADAS, resultados["Busca Binária Iterativa"], marker='o', label="Busca Binária Iterativa")
    plt.plot(TAM_ENTRADAS, resultados["Busca Binária Recursiva"], marker='o', label="Busca Binária Recursiva")
    
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

    print(resultados)

    grafico_geral(resultados)
    grafico_binarias(resultados)


if __name__ == "__main__":
    main()