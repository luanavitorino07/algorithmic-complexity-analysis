import subprocess
import matplotlib.pyplot as plt

TAMANHOS = [1000, 50000, 100000, 500000, 1000000]
CASOS = [
    "Inserções no Início",
    "Acesso por Índice",
    "Remoções no Início",
    "Remoções no Meio",
    "Percurso Completo"
]

def rodar_benchmark(executavel):
    print(f"rodando {executavel}")
    dados = {}
    for tam in TAMANHOS:
        print(f"  -> testando tamanho {tam}...")
        resultado = subprocess.run(
            [executavel],
            input=str(tam),
            text=True,
            capture_output=True,
            check=True
        )
        linhas = resultado.stdout.strip().split("\n")
        for linha in linhas:
            if "|" in linha and "Tamanho" not in linha and "---" not in linha:
                partes = [p.strip() for p in linha.split("|")]
                if len(partes) == 6:
                    t = int(partes[0])
                    tempos = [float(val) for val in partes[1:]]
                    dados[t] = tempos
    return dados

def gerar_graficos(res_seq, res_enc):
    for i, caso in enumerate(CASOS):
        plt.figure(figsize=(9, 6))
        
        tamanhos_disponiveis = [tam for tam in TAMANHOS if tam in res_seq and tam in res_enc]
        tempos_seq = [res_seq[tam][i] for tam in tamanhos_disponiveis]
        tempos_enc = [res_enc[tam][i] for tam in tamanhos_disponiveis]

        plt.plot(tamanhos_disponiveis, tempos_seq, marker='o', label="Lista Sequencial")
        plt.plot(tamanhos_disponiveis, tempos_enc, marker='s', label="Lista Encadeada")

        plt.xlabel("Tamanho da entrada (n)")
        plt.ylabel("Tempo médio de execução (s)")
        plt.title(f"Comparação de Desempenho — {caso}")
        plt.xticks(tamanhos_disponiveis)
        plt.ticklabel_format(style='plain', axis='x')
        plt.legend()
        plt.grid(True, alpha=0.3)
        
        nome_ficheiro = f"grafico_caso_{i+1}.png"
        plt.savefig(nome_ficheiro, dpi=150)
        plt.close()

def main():
    print("A compilar os códigos de benchmark...")
    subprocess.run(["gcc", "Lista_Sequencial/benchmark_sequencial.c", "Lista_Sequencial/ListaSequencial.c", "-o", "bench_seq", "-O3"], check=True)
    subprocess.run(["gcc", "Lista_Encadeada/benchmark_encadeada.c", "Lista_Encadeada/ListaEncadeada.c", "-o", "bench_enc", "-O3"], check=True)

    print("A executar benchmark da Lista Sequencial...")
    res_seq = rodar_benchmark("./bench_seq")

    print("A executar benchmark da Lista Encadeada...")
    res_enc = rodar_benchmark("./bench_enc")

    print("\n" + "="*115)
    print(f"{'Tamanho':<10} | {'Implementação':<18} | {'Caso 1 (s)':<13} | {'Caso 2 (s)':<13} | {'Caso 3 (s)':<13} | {'Caso 4 (s)':<13} | {'Caso 5 (s)':<13}")
    print("="*115)
    
    for tam in TAMANHOS:
        if tam in res_seq:
            t_seq = res_seq[tam]
            print(f"{tam:<10} | {'Sequencial':<18} | {t_seq[0]:<13.9f} | {t_seq[1]:<13.9f} | {t_seq[2]:<13.9f} | {t_seq[3]:<13.9f} | {t_seq[4]:<13.9f}")
        if tam in res_enc:
            t_enc = res_enc[tam]
            print(f"{tam:<10} | {'Encadeada':<18} | {t_enc[0]:<13.9f} | {t_enc[1]:<13.9f} | {t_enc[2]:<13.9f} | {t_enc[3]:<13.9f} | {t_enc[4]:<13.9f}")
        print("-" * 115)

    print("\nA gerar gráficos comparativos...")
    gerar_graficos(res_seq, res_enc)
    print("Processo concluído com sucesso! Gráficos guardados como 'grafico_caso_X.png'.")

if __name__ == "__main__":
    main()