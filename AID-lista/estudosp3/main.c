#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "product.h"

int main(){
	Product p1, p2, p3, p4, p5;
	strcpy(p1.name, "Feijao");
	p1.qtd = 3;
	p1.price = 10.5;

	strcpy(p2.name, "Arroz");
	p2.qtd = 3;
	p2.price = 10.5;

	strcpy(p3.name, "Carne");
	p3.qtd = 3;
	p3.price = 10.5;

	strcpy(p4.name, "Batata");
	p4.qtd = 3;
	p4.price = 10.5;

	strcpy(p5.name, "Maca");
	p5.qtd = 3;
	p5.price = 10.5;

	No* fila = initp();
	fila = addp(fila, p1);
	fila = addp(fila, p2);
	fila = addp(fila, p3);
	show(fila);

	char ns[50];
	strcpy(ns, "Arroz");

	popp(fila);
		show(fila);
	pops(fila, "Arroz");
		show(fila);
	popp(fila);
	show(fila);

	fila = addp(fila, p4);
	fila = addp(fila, p5);
	fila = addp(fila, p1);
	pops(fila, "Maca");
	show(fila);

	freep(fila);
	return 0;
}	