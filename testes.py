import subprocess
import time
import matplotlib.pyplot as plt


TAM_ENTRADAS = [1000, 50000, 100000, 500000, 1000000]
EXECUCOES = 100

def executar_teste(tam, opcao, busca_val):
    print(f"testando para {opcao}")
    # formatacao da entrada para o c
    elementos_vetor = " ".join(str(i) for i in range(0, tam))# range para garantir o vetor ordenado
    if opcao == 1:
        entrada = f"{tam}\n{elementos_vetor}\n{opcao}\n5\n"        
    else:
        entrada = f"{tam}\n{elementos_vetor}\n{opcao}\n{busca_val}\n5\n"

    tempos = []
    for _ in range(EXECUCOES):
        inicio = time.perf_counter()
        subprocess.run(
            ["./trabalho1"],
            input=entrada,
            text=True,
            capture_output=True
        )
        fim = time.perf_counter()
        tempos.append(fim - inicio)

    return sum(tempos) / EXECUCOES

def main():
    subprocess.run(["gcc", "trabalho1.c", "-o", "trabalho1"], check=True) 

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


if __name__ == "__main__":
    main()