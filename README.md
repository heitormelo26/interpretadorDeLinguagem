# interpretadorDeLinguagem
Esse código refere-se implementação de um interpretador de uma linguagem de programação fictícia. O programa recebe um txt com o código da linguagem abaixo e o executa em C++.

A linguagem fictícia apresenta a seguinte sintaxe:

| Sintaxe  | Exemplo |
| ------------- | ------------- |
| Var id tipo. (tipo=int,char)  | Var v1 int. |
| Atribua id_var valor.  | Atribua v1 1. |
| Operação  op1 (Operacao = Add/sub/or/xor/and/not)| Add v1 v2. |
| Imprima  d1,id2,id3  | Imprima v1.  |
| Leia  id_var  | Leia  v1. 
| Pare.  | Pare. 
| ? id_var id_v1,id_v2 : val1,val2. | ? res v1,v2:10,20.


O comando ? indica que:  Se id_v1-id_v2 = 1 atribua val2 senao val 0|? res v1,v2:10,20.

Exemplo de código executável no txt:<br/>
Var a int.<br/>
Var   b int.<br/> 
Var c int.<br/> 
Leia  a.<br/> 
Leia b.<br/> 
Atribua c a.<br/> 
Add  c b.<br/> 
Escreva  a,b,c.<br/> 
Pare.<br/> 
