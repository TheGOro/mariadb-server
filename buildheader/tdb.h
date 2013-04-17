#ifndef _DB_H
#define _DB_H
/* This code generated by make_db_h.   Copyright (c) 2007, 2008 Tokutek */
#ident "Copyright (c) 2007, 2008 Tokutek Inc.  All rights reserved."
#include <sys/types.h>
/*stdio is needed for the FILE* in db->verify*/
#include <stdio.h>
#include <stdint.h>
#if defined(__cplusplus)
extern "C" {
#endif
#define TOKUDB 1
#define TOKUDB_NATIVE_H 1
#define DB_VERSION_MAJOR 4
#define DB_VERSION_MINOR 6
#define DB_VERSION_PATCH 19
#ifndef _TOKUDB_WRAP_H
#define DB_VERSION_STRING "Tokutek: TokuDB 4.6.19"
#else
#define DB_VERSION_STRING_ydb "Tokutek: TokuDB (wrapped bdb)"
#endif
#ifndef TOKU_OFF_T_DEFINED
#define TOKU_OFF_T_DEFINED
typedef int64_t toku_off_t;
#endif
typedef struct __toku_db_env DB_ENV;
typedef struct __toku_db_key_range DB_KEY_RANGE;
typedef struct __toku_db_lsn DB_LSN;
typedef struct __toku_db DB;
typedef struct __toku_db_txn DB_TXN;
typedef struct __toku_db_txn_active DB_TXN_ACTIVE;
typedef struct __toku_db_txn_stat DB_TXN_STAT;
typedef struct __toku_dbc DBC;
typedef struct __toku_dbt DBT;
typedef u_int32_t db_recno_t;
typedef int(*YDB_CALLBACK_FUNCTION)(DBT const*, DBT const*, void*);
typedef int(*YDB_HEAVISIDE_CALLBACK_FUNCTION)(DBT const *key, DBT const *value, void *extra_f, int r_h);
typedef int(*YDB_HEAVISIDE_FUNCTION)(const DBT *key, const DBT *value, void *extra_h);
#include <tdb-internal.h>
#ifndef __BIGGEST_ALIGNMENT__
  #define __BIGGEST_ALIGNMENT__ 16
#endif
typedef struct __toku_db_btree_stat64 {
  u_int64_t bt_nkeys; /* how many unique keys (guaranteed only to be an estimate, even when flattened)          */
  u_int64_t bt_ndata; /* how many key-value pairs (an estimate, but exact when flattened)                       */
  u_int64_t bt_dsize; /* how big are the keys+values (not counting the lengths) (an estimate, unless flattened) */
  u_int64_t bt_fsize; /* how big is the underlying file                                                         */
} DB_BTREE_STAT64;
typedef struct __toku_loader DB_LOADER;
struct __toku_loader_internal;
struct __toku_loader {
  struct __toku_loader_internal *i;
  int (*set_error_callback)(DB_LOADER *loader, void (*error_cb)(DB *db, int i, int err, DBT *key, DBT *val, void *error_extra), void *error_extra); /* set the error callback */
  int (*set_poll_function)(DB_LOADER *loader, int (*poll_func)(void *extra, float progress), void *poll_extra);             /* set the polling function */
  int (*put)(DB_LOADER *loader, DBT *key, DBT* val);                                                      /* give a row to the loader */
  int (*close)(DB_LOADER *loader);                                                                        /* finish loading, free memory */
  int (*abort)(DB_LOADER *loader);                                                                        /* abort loading, free memory */
};
typedef struct __toku_engine_status {
  char             now[26];                 /* time of engine status query (i.e. now)  */ 
  u_int64_t        ydb_lock_ctr;            /* how many times has ydb lock been taken/released */ 
  u_int64_t        max_possible_sleep;      /* max possible sleep time for ydb lock scheduling (constant) */ 
  u_int64_t        processor_freq_mhz;      /* clock frequency in MHz */ 
  u_int64_t        max_requested_sleep;     /* max sleep time requested, can be larger than max possible */ 
  u_int64_t        times_max_sleep_used;    /* number of times the max_possible_sleep was used to sleep */ 
  u_int64_t        total_sleepers;          /* total number of times a client slept for ydb lock scheduling */ 
  u_int64_t        total_sleep_time;        /* total time spent sleeping for ydb lock scheduling */ 
  u_int64_t        max_waiters;             /* max number of simultaneous client threads kept waiting for ydb lock  */ 
  u_int64_t        total_waiters;           /* total number of times a client thread waited for ydb lock  */ 
  u_int64_t        total_clients;           /* total number of separate client threads that use ydb lock  */ 
  u_int64_t        time_ydb_lock_held_unavailable;  /* number of times a thread migrated and theld is unavailable */ 
  u_int64_t        max_time_ydb_lock_held;  /* max time a client thread held the ydb lock  */ 
  u_int64_t        total_time_ydb_lock_held;/* total time client threads held the ydb lock  */ 
  u_int32_t        checkpoint_period;       /* delay between automatic checkpoints  */ 
  u_int32_t        checkpoint_footprint;    /* state of checkpoint procedure        */ 
  char             checkpoint_time_begin[26]; /* time of last checkpoint begin      */ 
  char             checkpoint_time_begin_complete[26]; /* time of last complete checkpoint begin      */ 
  char             checkpoint_time_end[26]; /* time of last checkpoint end      */ 
  u_int64_t        cachetable_lock_taken;   /* how many times has cachetable lock been taken */ 
  u_int64_t        cachetable_lock_released;/* how many times has cachetable lock been released */ 
  u_int64_t        cachetable_hit;          /* how many cache hits   */ 
  u_int64_t        cachetable_miss;         /* how many cache misses */ 
  u_int64_t        cachetable_misstime;     /* how many usec spent waiting for disk read because of cache miss */ 
  u_int64_t        cachetable_waittime;     /* how many usec spent waiting for another thread to release cache line */ 
  u_int64_t        cachetable_wait_reading; /* how many times get_and_pin waits for a node to be read */ 
  u_int64_t        cachetable_wait_writing; /* how many times get_and_pin waits for a node to be written */ 
  u_int64_t        cachetable_wait_checkpoint; /* how many times get_and_pin waits for a node to be written for a checkpoint*/ 
  u_int64_t        puts;                    /* how many times has a newly created node been put into the cachetable */ 
  u_int64_t        prefetches;              /* how many times has a block been prefetched into the cachetable */ 
  u_int64_t        maybe_get_and_pins;      /* how many times has maybe_get_and_pin(_clean) been called */ 
  u_int64_t        maybe_get_and_pin_hits;  /* how many times has get_and_pin(_clean) returned with a node */ 
  int64_t          cachetable_size_current; /* sum of the sizes of the nodes represented in the cachetable */ 
  int64_t          cachetable_size_limit;   /* the limit to the sum of the node sizes */ 
  int64_t          cachetable_size_writing; /* the sum of the sizes of the nodes being written */ 
  int64_t          get_and_pin_footprint;   /* state of get_and_pin procedure */ 
  u_int32_t        range_locks_max;         /* max total number of range locks */ 
  u_int32_t        range_locks_max_per_index;  /* max range locks per dictionary */ 
  u_int32_t        range_locks_curr;        /* total range locks currently in use */ 
  u_int32_t        range_lock_escalation_successes;       /* number of times range locks escalation succeeded */ 
  u_int32_t        range_lock_escalation_failures;        /* number of times range locks escalation failed */ 
  u_int64_t        inserts;                 /* ydb row insert operations            */ 
  u_int64_t        deletes;                 /* ydb row delete operations            */ 
  u_int64_t        commits;                 /* ydb txn commit operations            */ 
  u_int64_t        aborts;                  /* ydb txn abort operations             */ 
  u_int64_t        point_queries;           /* ydb point queries                    */ 
  u_int64_t        sequential_queries;      /* ydb sequential queries               */ 
  u_int64_t        fsync_count;             /* number of times fsync performed      */ 
  u_int64_t        fsync_time;              /* total time required to fsync         */ 
  u_int64_t        logger_ilock_ctr;        /* how many times has logger input lock been taken or released  */ 
  u_int64_t        logger_olock_ctr;        /* how many times has logger output condition lock been taken or released  */ 
  u_int64_t        logger_swap_ctr;         /* how many times have logger buffers been swapped  */ 
  char             enospc_most_recent[26];  /* time of most recent ENOSPC error return from disk write  */ 
  u_int64_t        enospc_threads_blocked;  /* how many threads are currently blocked by ENOSPC */ 
  u_int64_t        enospc_total;            /* how many times has ENOSPC been returned by disk write */ 
  u_int64_t        enospc_seal_ctr;         /* how many times has ENOSPC been returned to user (red zone) */ 
  u_int64_t        enospc_seal_state;       /* state of ydb-level seal (0 = green, 1 = yellow, 2 = red) */ 
} ENGINE_STATUS;
typedef enum {
 DB_BTREE=1,
 DB_UNKNOWN=5
} DBTYPE;
#ifndef _TOKUDB_WRAP_H
#define DB_VERB_DEADLOCK 1
#define DB_VERB_RECOVERY 8
#define DB_VERB_REPLICATION 32
#define DB_VERB_WAITSFOR 64
#define DB_ARCH_ABS 1
#define DB_ARCH_LOG 4
#define DB_CREATE 1
#define DB_CXX_NO_EXCEPTIONS 1
#define DB_EXCL 16384
#define DB_PRIVATE 8388608
#define DB_RDONLY 32
#define DB_RECOVER 64
#define DB_RUNRECOVERY -30975
#define DB_THREAD 128
#define DB_TXN_NOSYNC 512
#define DB_LOCK_DEFAULT 1
#define DB_LOCK_OLDEST 7
#define DB_LOCK_RANDOM 8
#define DB_DUP 32768
#define DB_DUPSORT 65536
#define DB_KEYFIRST 13
#define DB_KEYLAST 14
#define DB_NOOVERWRITE 20
#define DB_NODUPDATA 19
#define DB_YESOVERWRITE 1
#define DB_NOOVERWRITE_NO_ERROR 2
#define DB_OPFLAGS_MASK 255
#define DB_AUTO_COMMIT 33554432
#define DB_INIT_LOCK 131072
#define DB_INIT_LOG 262144
#define DB_INIT_MPOOL 524288
#define DB_CLOSE_DONT_TRIM_LOG 1048576
#define DB_INIT_TXN 2097152
#define DB_KEYEXIST -30996
#define DB_LOCK_DEADLOCK -30995
#define DB_LOCK_NOTGRANTED -30994
#define DB_NOTFOUND -30989
#define DB_SECONDARY_BAD -30974
#define DB_DONOTINDEX -30998
#define DB_BUFFER_SMALL -30999
#define DB_BADFORMAT -30500
#define DB_DELETE_ANY 65536
#define DB_TRUNCATE_WITHCURSORS 131072
#define DB_FIRST 7
#define DB_GET_BOTH 8
#define DB_GET_BOTH_RANGE 10
#define DB_LAST 15
#define DB_CURRENT 6
#define DB_NEXT 16
#define DB_NEXT_DUP 17
#define DB_NEXT_NODUP 18
#define DB_PREV 23
#define DB_PREV_DUP 24
#define DB_PREV_NODUP 25
#define DB_SET 26
#define DB_SET_RANGE 27
#define DB_CURRENT_BINDING 253
#define DB_SET_RANGE_REVERSE 252
#define DB_GET_BOTH_RANGE_REVERSE 251
#define DB_RMW 1073741824
#define DB_PRELOCKED 0x00800000
#define DB_PRELOCKED_WRITE 0x00400000
#define DB_DBT_APPMALLOC 1
#define DB_DBT_DUPOK 2
#define DB_DBT_MALLOC 8
#define DB_DBT_MULTIPLE 16
#define DB_DBT_REALLOC 64
#define DB_DBT_USERMEM 256
#define DB_LOG_AUTOREMOVE 524288
#define DB_TXN_WRITE_NOSYNC 4096
#define DB_TXN_NOWAIT 1024
#define DB_TXN_SYNC 16384
#define DB_READ_UNCOMMITTED 134217728
#define DB_READ_COMMITTED 67108864
#define DB_INHERIT_ISOLATION 1
#endif
/* TOKUDB specific error codes */
#define TOKUDB_OUT_OF_LOCKS -100000
#define TOKUDB_SUCCEEDED_EARLY -100001
#define TOKUDB_DICTIONARY_TOO_OLD -100004
#define TOKUDB_DICTIONARY_TOO_NEW -100005
#define TOKUDB_DICTIONARY_NO_HEADER -100006
#define TOKUDB_FOUND_BUT_REJECTED -100002
#define TOKUDB_USER_CALLBACK_ERROR -100003
/* LOADER flags */
#define LOADER_USE_PUTS 1
/* in wrap mode, top-level function txn_begin is renamed, but the field isn't renamed, so we have to hack it here.*/
#ifdef _TOKUDB_WRAP_H
#undef txn_begin
#endif
struct __toku_db_env {
  struct __toku_db_env_internal *i;
#define db_env_struct_i(x) ((x)->i)
  int (*checkpointing_set_period)             (DB_ENV*, u_int32_t) /* Change the delay between automatic checkpoints.  0 means disabled. */;
  int (*checkpointing_get_period)             (DB_ENV*, u_int32_t*) /* Retrieve the delay between automatic checkpoints.  0 means disabled. */;
  int (*checkpointing_postpone)               (DB_ENV*) /* Use for 'rename table' or any other operation that must be disjoint from a checkpoint */;
  int (*checkpointing_resume)                 (DB_ENV*) /* Alert tokudb 'postpone' is no longer necessary */;
  int (*checkpointing_begin_atomic_operation) (DB_ENV*) /* Begin a set of operations (that must be atomic as far as checkpoints are concerned). i.e. inserting into every index in one table */;
  int (*checkpointing_end_atomic_operation)   (DB_ENV*) /* End   a set of operations (that must be atomic as far as checkpoints are concerned). */;
  int (*set_default_bt_compare)  (DB_ENV*,int (*bt_compare) (DB *, const DBT *, const DBT *)) /* Set default (key) comparison function for all DBs in this environment.  Required for RECOVERY since you cannot open the DBs manually. */;
  int (*set_default_dup_compare) (DB_ENV*,int (*bt_compare) (DB *, const DBT *, const DBT *)) /* Set default (val) comparison function for all DBs in this environment.  Required for RECOVERY since you cannot open the DBs manually. */;
  int (*get_engine_status)                    (DB_ENV*, ENGINE_STATUS*) /* Fill in status struct */;
  int (*get_engine_status_text)               (DB_ENV*, char*, int)     /* Fill in status text */;
  int (*get_iname)                            (DB_ENV* env, DBT* dname_dbt, DBT* iname_dbt) /* FOR TEST ONLY: lookup existing iname */;
  int (*create_loader)                        (DB_ENV *env, DB_TXN *txn, DB_LOADER **blp, DB *src_db, int N, DB *dbs[/*N*/], uint32_t db_flags[/*N*/], uint32_t dbt_flags[/*N*/], uint32_t loader_flags);
  void *app_private;
  int (*put_multiple)                         (DB_ENV *env, DB *src_db, DB_TXN *txn,
                                             const DBT *key, const DBT *val,
                                             uint32_t num_dbs, DB **db_array, DBT *keys, DBT *vals, uint32_t *flags_array,
                                             void *extra) /* Insert into multiple dbs */;
  int (*set_generate_row_callback_for_put)    (DB_ENV *env, 
                                             int (*generate_row_for_put)(DB *dest_db, DB *src_db,
                                                                         DBT *dest_key, DBT *dest_val,
                                                                         const DBT *src_key, const DBT *src_val,
                                                                         void *extra));
  int (*del_multiple)                         (DB_ENV *env, DB *src_db, DB_TXN *txn,
                                             const DBT *key, const DBT *val,
                                             uint32_t num_dbs, DB **db_array, DBT *keys, uint32_t *flags_array,
                                             void *extra) /* Insert into multiple dbs */;
  int (*set_generate_row_callback_for_del)    (DB_ENV *env, 
                                             int (*generate_row_for_del)(DB *dest_db, DB *src_db,
                                                                         DBT *dest_key,
                                                                         const DBT *src_key, const DBT *src_val,
                                                                         void *extra));
  int (*get_redzone)                          (DB_ENV *env, int *redzone) /* get the redzone limit */;
  int (*set_redzone)                          (DB_ENV *env, int redzone) /* set the redzone limit in percent of total space */;
  void *api1_internal;
  int  (*close) (DB_ENV *, u_int32_t);
  int  (*dbremove) (DB_ENV *, DB_TXN *, const char *, const char *, u_int32_t);
  int  (*dbrename) (DB_ENV *, DB_TXN *, const char *, const char *, const char *, u_int32_t);
  void (*err) (const DB_ENV *, int, const char *, ...);
  int (*get_cachesize) (DB_ENV *, u_int32_t *, u_int32_t *, int *);
  int (*get_flags) (DB_ENV *, u_int32_t *);
  int  (*get_lg_max) (DB_ENV *, u_int32_t*);
  int  (*get_lk_max_locks) (DB_ENV *, u_int32_t *);
  int  (*log_archive) (DB_ENV *, char **[], u_int32_t);
  int  (*log_flush) (DB_ENV *, const DB_LSN *);
  int  (*open) (DB_ENV *, const char *, u_int32_t, int);
  int  (*set_cachesize) (DB_ENV *, u_int32_t, u_int32_t, int);
  int  (*set_data_dir) (DB_ENV *, const char *);
  void (*set_errcall) (DB_ENV *, void (*)(const DB_ENV *, const char *, const char *));
  void (*set_errfile) (DB_ENV *, FILE*);
  void (*set_errpfx) (DB_ENV *, const char *);
  int  (*set_flags) (DB_ENV *, u_int32_t, int);
  int  (*set_lg_bsize) (DB_ENV *, u_int32_t);
  int  (*set_lg_dir) (DB_ENV *, const char *);
  int  (*set_lg_max) (DB_ENV *, u_int32_t);
  int  (*set_lk_detect) (DB_ENV *, u_int32_t);
  int  (*set_lk_max_locks) (DB_ENV *, u_int32_t);
  int  (*set_tmp_dir) (DB_ENV *, const char *);
  int  (*set_verbose) (DB_ENV *, u_int32_t, int);
  int  (*txn_begin) (DB_ENV *, DB_TXN *, DB_TXN **, u_int32_t);
  int  (*txn_checkpoint) (DB_ENV *, u_int32_t, u_int32_t, u_int32_t);
  int  (*txn_stat) (DB_ENV *, DB_TXN_STAT **, u_int32_t);
};
struct __toku_db_key_range {
  double less;
  double equal;
  double greater;
};
struct __toku_db_lsn {
};
struct __toku_dbt {
  void*data;
  u_int32_t size;
  u_int32_t ulen;
  u_int32_t flags;
};
typedef int (*toku_dbt_upgradef)(DB*,
                                 u_int32_t old_version, const DBT *old_descriptor, const DBT *old_key, const DBT *old_val,
                                 u_int32_t new_version, const DBT *new_descriptor, const DBT *new_key, const DBT *new_val);
//One header is included in 'data'
//One header is included in 'additional for checkpoint'
typedef struct __toku_db_fragmentation {
  uint64_t file_size_bytes;               //Total file size in bytes
  uint64_t data_bytes;                    //Compressed User Data in bytes
  uint64_t data_blocks;                   //Number of blocks of compressed User Data
  uint64_t checkpoint_bytes_additional;   //Additional bytes used for checkpoint system
  uint64_t checkpoint_blocks_additional;  //Additional blocks used for checkpoint system 
  uint64_t unused_bytes;                  //Unused space in file
  uint64_t unused_blocks;                 //Number of contiguous regions of unused space
  uint64_t largest_unused_block;          //Size of largest contiguous unused space
} *TOKU_DB_FRAGMENTATION, TOKU_DB_FRAGMENTATION_S;
struct __toku_db {
  struct __toku_db_internal *i;
#define db_struct_i(x) ((x)->i)
  int (*key_range64)(DB*, DB_TXN *, DBT *, u_int64_t *less, u_int64_t *equal, u_int64_t *greater, int *is_exact);
  int (*stat64)(DB *, DB_TXN *, DB_BTREE_STAT64 *);
  void *app_private;
  DB_ENV *dbenv;
  int (*pre_acquire_read_lock)(DB*, DB_TXN*, const DBT*, const DBT*, const DBT*, const DBT*);
  int (*pre_acquire_table_lock)(DB*, DB_TXN*);
  const DBT* (*dbt_pos_infty)(void) /* Return the special DBT that refers to positive infinity in the lock table.*/;
  const DBT* (*dbt_neg_infty)(void)/* Return the special DBT that refers to negative infinity in the lock table.*/;
  int (*delboth) (DB*, DB_TXN*, DBT*, DBT*, u_int32_t) /* Delete the key/value pair. */;
  int (*row_size_supported) (DB*, u_int32_t) /* Test whether a row size is supported. */;
  const DBT *descriptor /* saved row/dictionary descriptor for aiding in comparisons */;
  int (*set_descriptor) (DB*, u_int32_t version, const DBT* descriptor, toku_dbt_upgradef dbt_userformat_upgrade) /* set row/dictionary descriptor for a db.  Available only while db is open */;
  int (*getf_set)(DB*, DB_TXN*, u_int32_t, DBT*, YDB_CALLBACK_FUNCTION, void*) /* same as DBC->c_getf_set without a persistent cursor) */;
  int (*getf_get_both)(DB*, DB_TXN*, u_int32_t, DBT*, DBT*, YDB_CALLBACK_FUNCTION, void*) /* same as DBC->c_getf_get_both without a persistent cursor) */;
  int (*flatten)(DB*, DB_TXN*) /* Flatten a dictionary, similar to (but faster than) a table scan */;
  int (*get_fragmentation)(DB*,TOKU_DB_FRAGMENTATION);
  void *api_internal;
  int (*close) (DB*, u_int32_t);
  int (*cursor) (DB *, DB_TXN *, DBC **, u_int32_t);
  int (*del) (DB *, DB_TXN *, DBT *, u_int32_t);
  int (*fd) (DB *, int *);
  int (*get) (DB *, DB_TXN *, DBT *, DBT *, u_int32_t);
  int (*get_flags) (DB *, u_int32_t *);
  int (*get_pagesize) (DB *, u_int32_t *);
  int (*key_range) (DB *, DB_TXN *, DBT *, DB_KEY_RANGE *, u_int32_t);
  int (*open) (DB *, DB_TXN *, const char *, const char *, DBTYPE, u_int32_t, int);
  int (*put) (DB *, DB_TXN *, DBT *, DBT *, u_int32_t);
  int (*remove) (DB *, const char *, const char *, u_int32_t);
  int (*rename) (DB *, const char *, const char *, const char *, u_int32_t);
  int (*set_bt_compare) (DB *, int (*)(DB *, const DBT *, const DBT *));
  int (*set_dup_compare) (DB *, int (*)(DB *, const DBT *, const DBT *));
  void (*set_errfile) (DB *, FILE*);
  int (*set_flags) (DB *, u_int32_t);
  int (*set_pagesize) (DB *, u_int32_t);
  int (*stat) (DB *, void *, u_int32_t);
  int (*truncate) (DB *, DB_TXN *, u_int32_t *, u_int32_t);
  int (*verify) (DB *, const char *, const char *, FILE *, u_int32_t);
};
struct __toku_db_txn_active {
  u_int32_t txnid;
  DB_LSN lsn;
};
typedef struct __toku_txn_progress {
  uint64_t entries_total;
  uint64_t entries_processed;
  uint8_t  is_commit;
  uint8_t  stalled_on_checkpoint;
} *TOKU_TXN_PROGRESS, TOKU_TXN_PROGRESS_S;
typedef void(*TXN_PROGRESS_POLL_FUNCTION)(TOKU_TXN_PROGRESS, void*);
struct txn_stat {
  u_int64_t rollback_raw_count;
};
struct __toku_db_txn {
  DB_ENV *mgrp /*In TokuDB, mgrp is a DB_ENV not a DB_TXNMGR*/;
  DB_TXN *parent;
  int (*txn_stat)(DB_TXN *, struct txn_stat **);
  struct { void *next, *prev; } open_txns;
  int (*commit_with_progress)(DB_TXN*, uint32_t, TXN_PROGRESS_POLL_FUNCTION, void*);
  int (*abort_with_progress)(DB_TXN*, TXN_PROGRESS_POLL_FUNCTION, void*);
  void *api_internal;
  int (*abort) (DB_TXN *);
  int (*commit) (DB_TXN*, u_int32_t);
  u_int32_t (*id) (DB_TXN *);
  char iic[0] __attribute__((aligned(__BIGGEST_ALIGNMENT__)));
#define db_txn_struct_i(x) ((struct __toku_db_txn_internal *)(&(x)->iic))
};
struct __toku_db_txn_stat {
  u_int32_t st_nactive;
  DB_TXN_ACTIVE *st_txnarray;
};
struct __toku_dbc {
  DB *dbp;
  int (*c_getf_first)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_last)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_next)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_next_dup)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_next_nodup)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_prev)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_prev_dup)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_prev_nodup)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_current)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_current_binding)(DBC *, u_int32_t, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_heaviside)(DBC *, u_int32_t, YDB_HEAVISIDE_CALLBACK_FUNCTION f, void *extra_f, YDB_HEAVISIDE_FUNCTION h, void *extra_h, int direction);
  int (*c_getf_set)(DBC *, u_int32_t, DBT *, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_set_range)(DBC *, u_int32_t, DBT *, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_set_range_reverse)(DBC *, u_int32_t, DBT *, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_get_both)(DBC *, u_int32_t, DBT *, DBT *, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_get_both_range)(DBC *, u_int32_t, DBT *, DBT *, YDB_CALLBACK_FUNCTION, void *);
  int (*c_getf_get_both_range_reverse)(DBC *, u_int32_t, DBT *, DBT *, YDB_CALLBACK_FUNCTION, void *);
  int (*c_close) (DBC *);
  int (*c_count) (DBC *, db_recno_t *, u_int32_t);
  int (*c_del) (DBC *, u_int32_t);
  int (*c_get) (DBC *, DBT *, DBT *, u_int32_t);
  char iic[0] __attribute__((aligned(__BIGGEST_ALIGNMENT__)));
#define dbc_struct_i(x) ((struct __toku_dbc_internal *)(&(x)->iic))
};
#ifdef _TOKUDB_WRAP_H
#define txn_begin txn_begin_tokudb
#endif
int db_env_create(DB_ENV **, u_int32_t) __attribute__((__visibility__("default")));
int db_create(DB **, DB_ENV *, u_int32_t) __attribute__((__visibility__("default")));
char *db_strerror(int) __attribute__((__visibility__("default")));
const char *db_version(int*,int *,int *) __attribute__((__visibility__("default")));
int log_compare (const DB_LSN*, const DB_LSN *) __attribute__((__visibility__("default")));
int db_env_set_func_fsync (int (*)(int)) __attribute__((__visibility__("default")));
int toku_set_trace_file (char *fname) __attribute__((__visibility__("default")));
int toku_close_trace_file (void) __attribute__((__visibility__("default")));
int db_env_set_func_free (void (*)(void*)) __attribute__((__visibility__("default")));
int db_env_set_func_malloc (void *(*)(size_t)) __attribute__((__visibility__("default")));
int db_env_set_func_pwrite (ssize_t (*)(int, const void *, size_t, toku_off_t)) __attribute__((__visibility__("default")));
int db_env_set_func_write (ssize_t (*)(int, const void *, size_t)) __attribute__((__visibility__("default")));
int db_env_set_func_realloc (void *(*)(void*, size_t)) __attribute__((__visibility__("default")));
void db_env_set_checkpoint_callback (void (*)(void*), void*) __attribute__((__visibility__("default")));
void db_env_set_checkpoint_callback2 (void (*)(void*), void*) __attribute__((__visibility__("default")));
void db_env_set_recover_callback (void (*)(void*), void*) __attribute__((__visibility__("default")));
void db_env_set_recover_callback2 (void (*)(void*), void*) __attribute__((__visibility__("default")));
#if defined(__cplusplus)
}
#endif
#endif
