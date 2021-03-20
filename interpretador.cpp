#include<iostream>
#include<string.h>
#include<fstream>
#include<stdlib.h>


using namespace std;



struct bo{
	char* texto;
	int tam; // numeracao da ultima casa
	int parou; //indica a casa do verto que parou
}; 

struct var{
	char *nome;
	char *tipo;
	struct var *prox;
	int valorInt;
	char *valorChar;
};



typedef struct bo bo;


struct var* criaLista(struct var *cabeca){
	cabeca = (struct var*)malloc(sizeof(struct var));
	cabeca->prox = NULL;
	return cabeca;
}


void insereFinal(struct var *L,struct var *x){
	
	if(L == NULL){
//	cout<<"Var = NULL\n";
		return;	
	}
	
	struct var *p=L->prox;
	
	if(p==NULL){
	    L->prox=x;
	    L->prox->prox=NULL;
	}else{
    	while(p->prox!=NULL){
    		p=p->prox;
    	}
    p->prox=x;
    x->prox=NULL;
	}
}

struct var* retornaPorNome(struct var *L,char *chave){
	if(L == NULL){
//	cout<<"Var = NULL\n";
		return NULL;	
	}
	
	struct var *p = L->prox;
	struct var *q = L;
	while( p != NULL && strcmp(p->nome,chave) != 0 ){
		q = p;
		p = p->prox;
		if(p->prox == NULL){
			if(strcmp(p->nome,chave) != 0 ){
				p = NULL;
			}
			break;
		}	
	}
	if(p == NULL){
    	//printf(" -- Valor ja foi retirado!! \n");
	}
	return p; 
}

void imprimeFila(struct var *T, int x){
	if(x==0){
		if(T->prox==NULL){
	//	cout<<"NULL";
			return;	
		}
		int i=0;
		struct var *p=T->prox;
		while(p!=NULL){
	//		if(strcmp(p->tipo,"char") == 0) cout<<"Nome: "<<p->nome<<" Tipo: "<<p->tipo<<" ValorCh: "<<p->valorChar;
	//		if(strcmp(p->tipo,"int") == 0) cout<<"Nome: "<<p->nome<<" Tipo: "<<p->tipo<<" ValorIt: "<<p->valorInt;
			p=p->prox;
	//		if (p!=NULL) cout<<"\n";
		}
	}else{
		if(T->prox==NULL){
			cout<<"NULL";
			return;	
		}
		int i=0;
		struct var *p=T->prox;
		while(p!=NULL){
	//		if(strcmp(p->tipo,"char") == 0) cout<<"Nome: "<<p->nome<<" Tipo: "<<p->tipo<<" ValorCh: "<<p->valorChar;
	//		if(strcmp(p->tipo,"int") == 0) cout<<"Nome: "<<p->nome<<" Tipo: "<<p->tipo<<" ValorIt: "<<p->valorInt;
			
			p=p->prox;
	//		if (p!=NULL) cout<<"\n";
		}
	}
}

void imprimeBo(struct bo vet){
	int i = 0;
	for(i = 0; i<vet.tam ; i++){
		cout<<vet.texto[i];
	}
}

struct bo criaBo(int tam){
	
	struct bo aux;
	aux.texto = (char*) malloc(sizeof(char)*tam);
	aux.tam = tam;
	aux.parou = -1;
	return aux;
}

char* retornaTextoBo(struct bo vet){
	int i = 0;
	char *aux = (char*) malloc(sizeof(char)*vet.tam);
	for(i = 0; i<vet.tam ; i++){
		aux[i] = vet.texto[i];
	}
	
	return aux;
}

char* split(struct bo *bo, struct bo *aux){
		
	int i = bo->parou+1, k=0;
	char *texto = (char*) malloc(sizeof(char)*bo->tam);
//	cout<<"\nI = "<<i<<"  ";
	
	while(bo->texto[i] != ' ' && bo->texto[i] != '.'&& bo->texto[i] != ',' && bo->texto[i] != ':' && i <= bo->tam){
		
		texto[k] = bo->texto[i];
//		cout<<" texto = "<<texto<<"  ";
		i++;
		k++;
			
	}
	
	bo->parou = i;
	aux->parou = i;
	
//	cout<<"  Final: "<<texto<<"  ";
	
	return texto;
}

void interpretacao(char **comandos, int qtdComandos , int *qtdChar){
	
	int k,i,t, palavras = 0;
	struct bo bo;
	struct bo aux = criaBo(100);
	struct var* listaVar = criaLista(listaVar);
	
	
	for(i = 0; i < qtdComandos; i++){
		
		bo = criaBo(qtdChar[i]-1);
		aux = criaBo(qtdChar[i]-1);
		bo.parou = -1;
		aux.parou = -1;
		palavras = 0;
		
		if(comandos[i][qtdChar[i]-1] != '.'){
			cout<<"Erro na linha "<< i+1 <<" falta do .";
			exit(1);
		} 
		
		for(t = 0; t < qtdChar[i] ; t++){
			bo.texto[t] = comandos[i][t];
		}
		
		char* aux2 = (char*) malloc(sizeof(char)*bo.tam);
	
		aux2 = split(&bo,&aux);
		
		if(strcmp("Var",aux2) == 0){
			
			struct var* var = (struct var*) malloc(sizeof(struct var));
			var->prox = NULL;
	//		cout<<"\tComandoVar";
			
			while(bo.parou < bo.tam){
					
					aux2 = split(&bo,&aux);
					palavras++;
					
					if(palavras == 1){

						var->nome = aux2;
						
					}else{
						if(palavras == 2){
							if(strcmp("int",aux2) == 0){
								
							var->tipo = aux2;
							insereFinal(listaVar,var);	
							
							}else{
								if(strcmp("char",aux2) == 0){
									
									var->tipo = aux2;
									insereFinal(listaVar,var);
									
								}else{
									cout<<"\n\n\tSintaxe de Var incorreta.";
									exit(1);
								}
								
							}
						}
					}
							
				}		
		}else{
			if(strcmp("Atribua",aux2) == 0){
				
			//	cout<<"\tComandoAtribua";
				
				while(bo.parou < bo.tam){
					
					struct var* auxTeste ;
					aux2 = split(&bo,&aux);
					palavras++;
					char *te =  (char*) malloc(sizeof(char)*4);
					
					
				//	cout<<"\n \n Palavras: "<< palavras;
					
					if(palavras == 1){
						
						auxTeste = retornaPorNome(listaVar,aux2);
						
						strcpy(te,auxTeste->tipo);
						
						if(auxTeste == NULL) {
							cout<<"Varivel nao declarada";
							exit(1);
						}	
					}
					if(palavras == 2){
						
						if(aux2[0] == 39){
							
							if(strcmp("char",auxTeste->tipo) == 0){
								
								auxTeste->valorChar = aux2;
								
							}else{
								cout<<"\n\n \tTipo de variavel errado na atribuicao.";
								exit(1);
							}
						}else{
							if(strcmp("int",auxTeste->tipo) == 0){
								int x = atoi(aux2); 
								auxTeste->valorInt = x;
								imprimeFila(listaVar,0);
							}else{
								cout<<"\n\n \tTipo de variavel errado na atribuicao.";
								exit(1);
							}
						}
							
					}
					
				}
			}else{
				
				if(strcmp("Add",aux2) == 0 || strcmp("Sub",aux2) == 0 ){
					int x = 0;
					if(strcmp("Add",aux2) == 0){
				//		cout<<"\tComandoAdd";
						x = 1;
					} 
					if(strcmp("Sub",aux2) == 0) {
				//		cout<<"\tComandoSub";
						x = 2;
					}
					while(bo.parou < bo.tam){
						
						char *op1,*op2;
						palavras++;
						struct var* auxTeste;
						struct var* auxTeste2;
					
						aux2 = split(&bo,&aux);
					//	cout<<"Parou:"<< bo.parou<<"Tam:"<< bo.tam;
						
						if(palavras == 1){
							op1 = aux2;
						}
						
						if(palavras == 2){
							op2 = aux2;
							auxTeste = retornaPorNome(listaVar,op1);
							auxTeste2 = retornaPorNome(listaVar,op2);
							if(strcmp("int",auxTeste->tipo) == 0 && strcmp("int",auxTeste2->tipo) == 0){
								
								if(x == 1){
									auxTeste->valorInt = auxTeste->valorInt + auxTeste2->valorInt;
								}
								if(x == 2){
									auxTeste->valorInt = auxTeste->valorInt - auxTeste2->valorInt;
								}
								
							}else{
								cout<<"Variaveis devem ser inteiras";
								exit(1);
							}
						}
					}	
				
				}else{
					if(strcmp("Not",aux2) == 0){
					//	cout<<"\tComandoNot";
						struct var* auxTeste;
						
						while(bo.parou < bo.tam){
							
							aux2 = split(&bo,&aux);
							auxTeste = retornaPorNome(listaVar,aux2);
							
							if(strcmp("int",auxTeste->tipo) == 0){
								auxTeste->valorInt = !auxTeste->valorInt;
							}else{
								cout<<"Variavel deve ser inteira";
								exit(1);
							}	
						}	
					}else{
						if(strcmp("And",aux2) == 0 || strcmp("Or",aux2) == 0 || strcmp("Xor",aux2) == 0){
							int x = 0;
							if(strcmp("And",aux2) == 0){
							//	cout<<"\tComandoAnd";
								x = 1;
							} 
							if(strcmp("Or",aux2) == 0) {
							//	cout<<"\tComandoOr";
								x = 2;
							}
							if(strcmp("Xor",aux2) == 0) {
							//	cout<<"\tComandoXor";
								x = 3;
							}
							while(bo.parou < bo.tam){
								
								char *op1,*op2;
								palavras++;
								struct var* auxTeste;
								struct var* auxTeste2;
							
								aux2 = split(&bo,&aux);
							//	cout<<"Parou:"<< bo.parou<<"Tam:"<< bo.tam;
								
								if(palavras == 1){
									op1 = aux2;
								}
								
								if(palavras == 2){
									
									op2 = aux2;

									auxTeste = retornaPorNome(listaVar,op1);
									auxTeste2 = retornaPorNome(listaVar,op2);

									if(auxTeste2 == NULL){
										if(strcmp("int",auxTeste->tipo) == 0){
										int x = atoi(op2);

										if(x == 1){
											auxTeste->valorInt = (auxTeste->valorInt&&x);
										}
										if(x == 2){
											auxTeste->valorInt = (auxTeste->valorInt||x);
										}
										if(x == 3){
											auxTeste->valorInt = (auxTeste->valorInt^x);
										}
									}
									}else{
										if(strcmp("int",auxTeste->tipo) == 0 && strcmp("int",auxTeste2->tipo) == 0){
										
										if(x == 1){
											auxTeste->valorInt = (auxTeste->valorInt&&auxTeste2->valorInt);
										}
										if(x == 2){
											auxTeste->valorInt = (auxTeste->valorInt||auxTeste2->valorInt);
										}
										if(x == 3){
											auxTeste->valorInt = (auxTeste->valorInt^auxTeste2->valorInt);
										}
									}else{
										cout<<"Sintaxe invalida para comando, deve ser int";
									} 	
								}
							}	
							}	
							}else{
							if(strcmp("Imprima",aux2) == 0){
							//	cout<<"\tComandoImprima";
								while(bo.parou < bo.tam){
									
									struct var* auxTeste ;
									aux2 = split(&bo,&aux);
									auxTeste = retornaPorNome(listaVar,aux2);
									
									cout<<"\nImprimindo: "<<aux2<<"\n";
									if(strcmp(auxTeste->tipo,"char") == 0) cout<<aux2<<" = "<<auxTeste->valorChar;
									if(strcmp(auxTeste->tipo,"int") == 0) cout<<aux2<<" = "<<auxTeste->valorInt;
								}	
							}else{
								if(strcmp("Leia",aux2) == 0){
								//	cout<<"\tComandoLeia";
									struct var* auxTeste ;
									while(bo.parou < bo.tam){
										aux2 = split(&bo,&aux);
										auxTeste = retornaPorNome(listaVar,aux2);
										if(auxTeste != NULL){
												cout<<"\n Digite o valor da variavel: ";
											if(strcmp(auxTeste->tipo,"char") == 0){
											
												char *x = (char*)malloc(sizeof(char)*10);
												cin>> x;
												auxTeste->valorChar = x;
												
											}else{
												
												int x ;
												cin>> x;
												auxTeste->valorInt = x;
											}
											
											 
										}else{
											cout<<"Variavel nao pode ser lida, pois nao foi declarada";
										}
									}	
								}else{
									if(strcmp("Pare",aux2) == 0){
										
										cout<<"\n\n\tParando programa, apos comando pare";
										exit(1);
																			
									}else{
										if(strcmp("?",aux2) == 0){
										//	cout<<"\tComando?";
											while(bo.parou < bo.tam){
												
												
												char *op1,*op2,*op3,*op4,*op5;
												palavras++;
												struct var* auxTeste;
												struct var* auxTeste2;
												struct var* auxTeste3;
												
												aux2 = split(&bo,&aux);
												
												//cout<<"\nTermo: "<<aux2;
												if(palavras == 1){
													op1 = aux2;
												}
												
												if(palavras == 2){
													op2 = aux2;
												}
												
												if(palavras == 3){
													op3 = aux2;
												}	
												
												if(palavras == 4){
													op4 = aux2;
												}
												
												if(palavras == 5){
													op5 = aux2;
													
													auxTeste = retornaPorNome(listaVar,op3);
													auxTeste2 = retornaPorNome(listaVar,op2);
													auxTeste3 = retornaPorNome(listaVar,op1);
													
													if(auxTeste == NULL || auxTeste2 == NULL || auxTeste3 == NULL ){
														cout<<"Variaveis nao declaradas para comando -> ?";
													}else{
														if(strcmp("int",auxTeste->tipo) == 0 && strcmp("int",auxTeste2->tipo) == 0 && strcmp("int",auxTeste3->tipo) == 0){
														int x1 = auxTeste3->valorInt,
														x2 = auxTeste->valorInt,
														x3 = auxTeste2->valorInt, 
														x4 = atoi(op4), 
														x5 = atoi(op5);
														int sum = x2 - x3;
														//cout<<"\n"<<auxTeste->nome<<"-"<<auxTeste2->nome<<"Valor: "<<sum;
														//cout<<"\n"<<auxTeste->valorInt<<"-"<<auxTeste2->valorInt<<"Valor: "<<sum;
														if(sum == 1){
															
															auxTeste3->valorInt = x5;
														}else{
															auxTeste3->valorInt = x4;
														}
														
													}else{
														cout<<"Variaveis devem ser inteiras";
														exit(1);
													}
													}	
												}
											}	
										}else{
											cout<<"Comando desconhecido, erro no sistema";
											exit(1);
										}
									} 
								} 
							 	
							} 
						
						} 
					
					} 
			
				} 
			
			} 
		 
		}
	//	cout<<"\n";	
	}
	
	
//	imprimeFila(listaVar,0);
	
	
}




int main(){
	
	
    fstream codigo;
	string texto = "";
	string comando = "";
	int qtdComandos = 0, i=0, k=0, t=0;
	int qtdChar[1000];	

	codigo.open("teste.txt");
	while(getline(codigo, comando)){ 
	
		if(comando != ""){
			texto = texto + comando + ";";
			qtdChar[i] = comando.length();
			i++;
			qtdComandos++;
		}

	}
	codigo.close();
	char **comandos = (char**) malloc(sizeof(char*)*qtdComandos);
	
	
	 for(int i = 0; i < qtdComandos; i++)
    {
        comandos[i] = (char*) malloc(sizeof(char) * 300);
    }
    
	i = 0;

	
	for(i = 0; i < texto.length(); i++){
		if(texto[i] == ';'){
			k = 0;
			t++;
				
		}else{
			comandos[t][k] = texto[i];			
			k++;
		}		
	}
	
	
	interpretacao(comandos,qtdComandos,qtdChar);
	
}
