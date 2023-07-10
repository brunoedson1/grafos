#/bin/bash

# Guloso, Guloso randomizado adaptativo e Guloso randomizado adaptativo reativo

g++ -g *.cpp -o execGrupo14.exe

arquivos=(
    "instancias\brock200_2.txt" 
    "instancias\p_hat300-1.txt"
    "instancias\brock400_2.txt"
    "instancias\brock400_4.txt"
    "instancias\p_hat700-3.txt"
    "instancias\MANN_a45.txt"
    "instancias\hamming10-4.txt"
    "instancias\p_hat1500-3.txt"
    "instancias\keller6.txt"
    "instancias\C4000.txt"
)


for arquivo in "${arquivos[@]}"
    do
        .\\execGrupo14 "$arquivo" saida.txt 0 0 1 g
    done


# .\\execGrupo14 brock200_2.txt saida.txt 0 0 1 g &&
# .\\execGrupo14 p_hat300-1.txt saida.txt 0 0 1 g &&
# .\\execGrupo14 brock400_2.txt saida.txt 0 0 1 g &&
# .\\execGrupo14 brock400_4.txt saida.txt 0 0 1 g &&
# .\\execGrupo14 p_hat700-3.txt saida.txt 0 0 1 g &&
# .\\execGrupo14 MANN_a45.txt saida.txt 0 0 1 g &&
# .\\execGrupo14 hamming10-4.txt saida.txt 0 0 1 g &&
# .\\execGrupo14 p_hat1500-3.txt saida.txt 0 0 1 g &&
# .\\execGrupo14 keller6.txt saida.txt 0 0 1 g &&
# .\\execGrupo14 C4000.txt saida.txt 0 0 1 g

alphas=(0.05 0.1 0.15 0.3 0.5)

for arquivo in "${arquivos[@]}"
    do
        for alpha in "${alphas[@]}"
            do
                for ((i=0;i<10;i++))
                    do
                        echo "$alpha"
                        .\\execGrupo14 "$arquivo" saida.txt 0 0 1 a "$alpha"
                    done
            done
    done
    
    
for arquivo in "${arquivos[@]}"
    do
        for ((i=0;i<10;i++))
            do
                .\\execGrupo14 "$arquivo" saida.txt 0 0 1 r
            done
    done