#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No{
	char c;
	struct No* next;
}No;

No* pushp(No* cabeca, char c){
	No* novo = (No*) malloc(sizeof(No));
	novo->c = c;
	if (cabeca == NULL){
		novo->next = NULL;
	} else {
		novo->next = cabeca;
	}
	return novo;
}

char popp(No** cabeca){
	No* r = *cabeca;
	if (r != NULL) {
		*cabeca = r->next;
	
		char z = r->c;
		free(r);
	
		return z;	
	}
}

int verifys(char s[1001]){
	No* pilha = NULL;

	int i = 0;
	while(s[i] != '\0'){
		char c = s[i];
		if(c == '[' || c == '{' || c == '('){
			pilha = pushp(pilha, c);
		}else if (c == ']' || c == '}' || c == ')'){
			if (pilha == NULL) return 0;
			char cp = popp(&pilha);
			if (!((c == ']' && cp == '[') || (c == '}' && cp == '{') || (c == ')' && cp == '('))){
				return 0;
			}
		}
		i++;
	}
	return pilha == NULL;
}

int main(){
	char s[1001];
	while (fgets(s, 1001, stdin) != NULL) {
        printf("%s\n", verifys(s) ? "correct" : "incorrect");
    }

	return 0;
}