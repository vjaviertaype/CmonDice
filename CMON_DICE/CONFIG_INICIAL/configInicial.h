#ifndef CONFIGINICIAL_H_INCLUDED
#define CONFIGINICIAL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../estructuras.h"
#include "../macros.h"

int cargarConfig(const char *,tConfig *,unsigned);
int validarConfig(tConfig *);
void mostrarConfig(tConfig *);
#endif // CONFIGINICIAL_H_INCLUDED
