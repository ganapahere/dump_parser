#ifndef _LIST_H_
#define _LIST_H_

#define SUCCESS	0
#define FAILURE	-1
typedef struct node node_t;
typedef node_t list_t;
typedef pdir_t* data_t;
typedef int status_t;

struct node {
	data_t data;
	node_t *prev;
	node_t *next;
};

list_t *create_list(void);
status_t insert_beg(list_t *p_list, data_t new_data);
status_t insert_end(list_t *p_list, data_t new_data);
status_t del_beg(list_t *p_list, data_t *p_del_data);
status_t del_end(list_t *p_list, data_t *p_del_data);
void destroy_list(list_t **pp_list);

static bool is_list_empty(list_t *p_list);
static void generic_insert(node_t *p_beg, node_t *p_mid, node_t *p_end);
static void generic_delete(node_t *p_del);
node_t *get_new_node(data_t new_data);
void *xmalloc(size_t size);
#endif
