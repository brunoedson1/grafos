#/bin/bash

# Guloso, Guloso randomizado adaptativo e Guloso randomizado adaptativo reativo

g++ -fdiagnostics-color=always -g *.cpp -o execGrupo14

for((i = 0; i < 10; i++))
do
    ./execGrupo14 instancias/brock200_2.txt saida.txt 0 0 1 &&
    ./execGrupo14 instancias/C4000.txt saida.txt 0 0 1 &&
    ./execGrupo14 instancias/brock400_4.txt saida.txt 0 0 1 &&
    ./execGrupo14 instancias/keller6.txt saida.txt 0 0 1 &&
    ./execGrupo14 instancias/p_hat300-1.txt saida.txt 0 0 1 &&
    ./execGrupo14 instancias/MANN_a45.txt saida.txt 0 0 1 &&
    ./execGrupo14 instancias/brock400_2.txt saida.txt 0 0 1 &&
    ./execGrupo14 instancias/hamming10-4.txt saida.txt 0 0 1 &&
    ./execGrupo14 instancias/p_hat1500-3.txt saida.txt 0 0 1 &&
    ./execGrupo14 instancias/p_hat700-3.txt saida.txt 0 0 1
done