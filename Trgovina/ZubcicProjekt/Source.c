#include <stdio.h>
#include <stdlib.h>
#include "Header.h"

int main()
{
	PROIZVOD* pr = NULL;
	pr = memorija();
	ucitavanje(pr);
	meni(pr);


	return 0;
}