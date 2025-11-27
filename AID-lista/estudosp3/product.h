typedef struct Product {
	char name[50];
	int qtd;
	float price;
}Product;

typedef struct No{
	Product dado;
	struct No* proximo;
}No;

No* initp();
No* addp(No* cabeca, Product valor);
void popp(No* cabeca);
void pops(No* cabeca, char name[50]);
void show(No* cabeca);
void freep(No* cabeca);