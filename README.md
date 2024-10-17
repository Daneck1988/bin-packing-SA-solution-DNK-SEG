# Solução para o problema Bin Packing

Este projeto é a solução do Danilo Barcelos e do Allann Cintra para o 2º Desafio em Otimização com Meta-heurística. Ele segue esta seguinte estrutura de arquivos:

- A pasta "src" contém o código-fonte do programa da solução
- A pasta "Docs" contém o arquivo do Writer que foi convertido em PDF para submissão
- A pasta "test" contém os casos de teste utilizados. Ela contém o conjunto completo de casos de teste, o conjunto reduzido para debugging, e o arquivo contendo as soluções ótimas de todos os casos
- Na pasta raiz você encontrará os scripts que ajudam a testar vários casos de teste de forma rápida

# Modo de Usar

## No Linux

Compile o programa usando makefile `> make`, ou manualmente `> g++ src/main.cpp src/random.cpp src/sa.cpp -o build/sabp`. Após isso você pode rodar o programa manualmente `> build/sabp`, digitando o caso de teste no terminal, ou usando o script "run.sh".

Para usar ele, basta chamá-lo. Por padrão ele busca o executável no lugar onde o makefile compila, e os testes em `test/reduced`. Caso queira mudar onde ele busca as coisas, pode-se usar estas variáveis:

- EXEC: Caminho do executável
- TEST_FOLDER: Caminho da pasta que contém casos de teste. Cada caso deve ser um arquivo de texto
- SOLUTIONS_FILE: Caminho do arquivo de soluções

Aqui vai um exemplo de comando para usar o script, supondo que todos os arquivos necessários estão em `/tmp/files`:

`EXEC=/tmp/files/exec.out TEST_FOLDER=/tmp/files/tests SOLUTIONS_FILE=/tmp/files/solucoes.txt ./run.sh`

NOTA: O script bash não diz quanto tempo cada caso de teste levou

## No Windows

Compile o programa manualmente, pois o makefile não funciona no Windows `> g++ src/main.cpp src/random.cpp src/sa.cpp -o build/sabp.exe`. Após isso você pode rodar o programa manualmente `> build\sabp.exe`, digitando o caso de teste no terminal, ou usando o script "run.bat".

Para usar ele, basta chamálo. Por padrão ele busca o executável no lugar onde ele estaria se o makefile funcionasse no Windows (`build\sabp.exe`), e os testes em `test\reduced`. Caso queira mudar seu comportamento, pode-se usar estas variáveis:

- EXEC: Caminho do executável (Parece que precisa estar em aspas? Batch é estranho)
- TEST_FOLDER: Caminho da pasta que contém casos de teste. Cada caso deve ser um arquivo de texto
- SOLUTIONS_FILE: Caminho do arquivo de soluções

Aqui vai um exemplo de comando para usar o script, supondo que todos os arquivos necessários estão em `C:\arquivos`:

`set EXEC="C:\arquivos\prog.exe"&& set TEST_FOLDER=C:\arquivos\testes&& set SOLUTIONS_FILE=C:\arquivos\testes\Solucoes.txt&& set ARGS=i&& run.bat`

Este script não procura o arquivo de soluções por padrão, mas diz quantos segundos cada caso de teste levou para ser processado. Se a saída deste script for redirecionada para um arquivo, e um arquivo de soluções foi especificado, pode-se usar o script getstats.py para obter estatísticas do teste.

***

O programa imprime o número de caixas da melhor solução encontrada, quantas iterações foram calculadas e em qual a melhor solução foi encontrada, e os conteúdos de todas as caixas.

Pode-se desabilitar a impressão das informações sobre as iterações usando o argumento `-i`, e a impressão dos conteúdos das caixas com o argumento `-c`. Todos os scripts estão programados para usar `-ic` nos argumentos, para facilitar o processamento da saída e porque essas informações adicionais são irrelevantes para o cálculo da performance do programa.