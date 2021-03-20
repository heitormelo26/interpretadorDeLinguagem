# interpretadorDeLinguagem
Esse código refere-se implementação de um interpretador de uma linguagem de programação fictícia.

A linguagem fictícia apresenta a seguinte sintaxe:

      Sintaxe                              Exemplo

1. Var id  tipo. (Obs.:  tipo=int,char)  ->  Var v1 int.
2. Atribua  id_var   valor.              ->  Atribua v1 1. 
3. Add 02| sub | or | xor | and | not    ->  Add v1 v2.  
      Operação  op1
4. Imprima  d1,id2,id3                   -> Imprima v1.
5. Leia  id_var                          -> Leia  v1.
6. Pare.                                 -> Pare.
7. ? id_var id_v1,id_v2 : val1,val2.     -> ? res v1,v2:10,20. 
      Se id_v1-id_v2 = 1 atribua val2 
          senao val 0



Exemplo de programa executável:

Var a int. 
Var b int. 
Var c int. 
Leia a. 
Leia b. 
Atribua c a. 
Add c b. 
Escreva a,´+´,b,´=´,c. 
Pare. 
