# Simpletron
Fazendo um computador sem precisar soldar algum componente, ele possui uma linguagem própria chamada SML. Vi esse exercício no livro C: como programar, de Paul Deitei e Harvey Deitel. O programa simula um computador capaz de ler, escrever, somar, diminuir, multiplicar, dividir, mudar a posição dos valores na memória, ele também gera um arquivo chamado output.txt com as leituras e resultados, e o dump, que mostra o conteúdo dos registradores e da memória após a execução, nele você consegue ver cada operação realizada em sequência e onde foram colocados os resultados. Fique a vontade para modificar e melhorar. 

Como a linguagem SML funciona:

Ela é composta de palavras de 4 dígitos, os dois primeiros dígitos são o código de operação, e os dois últimos são o local da memória onde a operação será feita. 
Primeiro o programa precisa ser carregado na memória, depois ele é executado. Essas são as operações que podem ser feitas(nada te impede de criar mais):

10 - Leitura de um valor em um local da memória

11 - Escrita de um valor de um local da memória no terminal

20 - Coloca uma palavra de um lugar da memória no acumulador

21 - Pega o valor do acumulador e coloca em um local da memória

30 - Soma um valor de um lugar da memória no acumulador e deixa o resultado no acumulador

31 - Subtrai um valor de um lugar da memória no acumulador e deixa o resultado no acumulador

32 - Divide um valor de um lugar da memória no acumulador e deixa o resultado no acumulador

33 - Multiplica um valor de um lugar da memória no acumulador e deixa o resultado no acumulador

40 - Desvia para um local da memória

41 - Desvia para um local da memória se o acumulador for negativo

42 - Desvia para um local da memória se o acumulador for zero

43 - Finaliza e mostra o conteúdo dos registradores e da memória

Exemplo de um programa sendo carregado na memória, que lê dois números e mostra a soma:

1007 (lê um número no local 07 da memória)

1008 (lê um número no local 08 da memória)

2007 (coloca o número da posição 07 no acumulador)

3008 (soma o número da posição)

2109 (coloca o que está no acumulador na posição 09 da memória)

1109 (mostra o que está na posição 09 da memória)

4300 (finaliza e mostra o conteúdo dos registradores e da memória)

-99999 (finaliza a carga de instruções do programa na memória)
