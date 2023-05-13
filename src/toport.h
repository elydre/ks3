#ifndef TOPORT_H
#define TOPORT_H

char *tp_get_file_content(char *filename);

void *tp_malloc(size_t size);
void *tp_realloc(void *ptr, size_t size);
void tp_free(void *ptr);

#endif
