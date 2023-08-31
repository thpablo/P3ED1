# Descrição
Projeto desenvolvido para o terceiro trabalho prático da matéria de Estrutura de Dados 1 da Universidade Federal de Ouro Preto. O código encontra o menor e maior caminho de um labirinto utilizando a estrutura de dados árvore.

# Pré-Requisitos

- [X] Compilador C (GCC)
- [X] CMake (optional)

# Compilação
Use o seguinte comando caso tenha instalado Make:
`make`
Ou compile manualmente:
`gcc *.c -c` 
`gcc *.o -o exe`

# Uso
Para usar os testes disponíveis no repositório, basta usar passando o caminho para a pasta e o teste desejável, por exemplo:

`exe < tests/ceg-7-11.in`

*Note: Você pode ver a saída referente ao caso de teste usado utilizando o comando `cat teste.out` caso esteja no linux* 

Caso queira dar uma entrada diferente dos testes, deve utilizar o comando:

`exe`
E informar as dimensões do labirinto, sendo primeiro a altura e em seguida a largura, além da escolha de maior ou menor caminho.
- *g: Irá procurar o maior caminho.*
- *s: Irá procurar o menor caminho.*
- *f: Irá listar todas posições possíveis que o rato pode caminhos, ordenadas por níveis na árvore.*

Após isso, o labirinto seguindo o padrão de paredes serem representadas por astericos '*' e a posição inicial do rato indicada com a letra M. A saída é sempre a última posição inferior direita. Exemplo:
```
7 7
g
*******
*M*   *
* * * *
* * * *
* * * *
*      
*******
```