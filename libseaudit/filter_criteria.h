/* Copyright (C) 2004 Tresys Technology, LLC
 * see file 'COPYING' for use and warranty information */

/* 
 * Author: Kevin Carr <kcarr@tresys.com> and Karl MacMillan <kmacmillan@tresys.com>
 * Date: February 06, 2004
 * 
 * This file contains the data structure definitions for storing
 * filter criterias.
 *
 * filter_criteria.h
 */

#ifndef LIBSEAUDIT_CRITERIA_H
#define LIBSEAUDIT_CRITERIA_H

#include <time.h>
#include "auditlog.h"
#include "../libapol/util.h"

struct seaudit_criteria;
/* callback type for printing criteria */
typedef void (*seaudit_criteria_print_t)(struct seaudit_criteria *criteria, FILE *stream, int tabs);
/* callback type for criteria */
typedef bool_t(*seaudit_criteria_action_t)(msg_t *msg, struct seaudit_criteria *criteria, audit_log_t *log); 
/* callback type for criteria cleanup */
typedef void (*seaudit_criteria_destroy_t)(struct seaudit_criteria *criteria);

/*
 * generic criteria structure */
typedef struct seaudit_criteria {  
	unsigned int msg_types;                 /* message types for the criteria */
	seaudit_criteria_action_t criteria_act; /* function to perform the criteria matching */
	seaudit_criteria_print_t print;
	seaudit_criteria_destroy_t destroy;     /* function to free the criteria type */
	void *data;                             /* data for the criteria ie. date_criteria_t */
	bool_t dirty;
} seaudit_criteria_t;

/* create a criteria */
seaudit_criteria_t* src_type_criteria_create(char **types, int num_types);
seaudit_criteria_t* tgt_type_criteria_create(char **types, int num_types);
seaudit_criteria_t* src_role_criteria_create(char **roles, int num_roles);
seaudit_criteria_t* tgt_role_criteria_create(char **roles, int num_roles);
seaudit_criteria_t* src_user_criteria_create(char **users, int num_users);
seaudit_criteria_t* tgt_user_criteria_create(char **users, int num_users);
seaudit_criteria_t* class_criteria_create(char **classes, int num_classes);
seaudit_criteria_t* exe_criteria_create(const char *exe);
seaudit_criteria_t* host_criteria_create(const char *host);
seaudit_criteria_t* path_criteria_create(const char *path);
seaudit_criteria_t* netif_criteria_create(const char *netif);
seaudit_criteria_t* ipaddr_criteria_create(const char *ipaddr); /* a generic match-any IP criteria */
seaudit_criteria_t* ports_criteria_create(int port);            /* a generic match-any port criteria */

const char **strs_criteria_get_strs(seaudit_criteria_t *criteria, int *size);
#define src_type_criteria_get_strs(criteria, size) strs_criteria_get_strs(criteria, size)
#define tgt_type_criteria_get_strs(criteria, size) strs_criteria_get_strs(criteria, size)
#define src_user_criteria_get_strs(criteria, size) strs_criteria_get_strs(criteria, size)
#define tgt_user_criteria_get_strs(criteria, size) strs_criteria_get_strs(criteria, size)
#define src_role_criteria_get_strs(criteria, size) strs_criteria_get_strs(criteria, size)
#define tgt_role_criteria_get_strs(criteria, size) strs_criteria_get_strs(criteria, size)
#define class_criteria_get_strs(criteria, size) strs_criteria_get_strs(criteria, size)

const char *glob_criteria_get_str(seaudit_criteria_t *criteria);
#define exe_criteria_get_str(criteria) glob_criteria_get_str(criteria)
#define path_criteria_get_str(criteria) glob_criteria_get_str(criteria)
#define ipaddr_criteria_get_str(criteria) glob_criteria_get_str(criteria)
#define host_criteria_get_str(criteria) glob_criteria_get_str(criteria)

const char *netif_criteria_get_str(seaudit_criteria_t *criteria);
int ports_criteria_get_val(seaudit_criteria_t *criteria);
void seaudit_criteria_print(seaudit_criteria_t *criteria, FILE *stream, int tabs);

/* destroy a criteria */
void seaudit_criteria_destroy(seaudit_criteria_t *ftr);


#endif