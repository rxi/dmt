#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct dmt_node_t {
  struct dmt_node_t *prev, *next;
  const char *file;
  size_t line;
  size_t size;
} dmt_node_t;


dmt_node_t *dmt_head;



int _dmt_has_node(dmt_node_t *n) {
  dmt_node_t *node = dmt_head;
  while (node != NULL) {
    if (node == n) return 1;
    node = node->next;
  }
  return 0;
}



void *_dmt_alloc(size_t sz, const char *file, unsigned line, int zeroset) {
  dmt_node_t *node = NULL;
  
  if (zeroset) {
    node = calloc(sizeof(*node) + sz, 1);
  } else {
    node = malloc(sizeof(*node) + sz);
    memset(node, 0, sizeof(*node));
  }

  node->line = line;
  node->file = file;
  node->size = sz;

  if (dmt_head) {
    dmt_head->prev = node;
    node->next = dmt_head;
  }
  dmt_head = node;

  return (char*)node + sizeof(*node);
}



void *_dmt_realloc(void *ptr, size_t sz, const char *file, unsigned line) {
  dmt_node_t *node = (dmt_node_t*)((char*)ptr - sizeof(*node));

  if (!_dmt_has_node(node)) {
    printf("Bad realloc: %p %s, line %u\n", ptr, file, line);
    abort();
  }

  node = realloc(node, sz);
  node->size = sz;
  if (node->prev) node->prev->next = node;
  if (node->next) node->next->prev = node;

  return node;
}



void _dmt_free(void *ptr, const char *file, unsigned line) {
  dmt_node_t *node = (dmt_node_t*)((char*)ptr - sizeof(*node));

  if (!_dmt_has_node(node)) {
    printf("Bad free: %p %s, line %u\n", ptr, file, line);
    abort();
  }

  if (node->prev == NULL) {
    dmt_head = node->next;
  } else {
    node->prev->next = node->next;
    if (node->next) {
      node->next->prev = node->prev;
    }
  }

  free(node);
}



void dmt_dump(FILE *fp) {
  dmt_node_t *node = dmt_head;
  size_t total = 0;

  if (!fp) fp = stdout;

  while (node != NULL) {
    fprintf(
      fp, 
      "Unfreed: %p %s, line %u (%u bytes)\n", 
      (char*)node + sizeof(*node), 
      node->file, 
      node->line,
      node->size);

    total += node->size;
    node = node->next;
  }

  fprintf(fp, "Total unfreed: %u bytes\n", total);
}



size_t dmt_usage(void) {
  dmt_node_t *node = dmt_head;
  size_t total = 0;

  while (node != NULL) {
    total += node->size;
    node = node->next;
  } 

  return total;
}
