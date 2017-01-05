/*-
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 1996, 2011 Oracle and/or its affiliates.  All rights reserved.
 *
 * $Id$
 */
#include "db_config.h"
#include "db_int.h"
#include "dbinc/db_page.h"
#include "dbinc/lock.h"
#include "dbinc/mp.h"
#include "dbinc/crypto.h"
#include "dbinc/btree.h"
#include "dbinc/hash.h"
#pragma hdrstop
#include "dbinc/txn.h"
/*
 * __txn_env_create --
 *	Transaction specific initialization of the DB_ENV structure.
 *
 * PUBLIC: int __txn_env_create(DB_ENV *);
 */
int __txn_env_create(DB_ENV*dbenv)
{
	/*
	 * !!!
	 * Our caller has not yet had the opportunity to reset the panic
	 * state or turn off mutex locking, and so we can neither check
	 * the panic state or acquire a mutex in the DB_ENV create path.
	 */
	dbenv->tx_max = 0;
	return 0;
}
/*
 * __txn_env_destroy --
 *	Transaction specific destruction of the DB_ENV structure.
 *
 * PUBLIC: void __txn_env_destroy(DB_ENV *);
 */
void __txn_env_destroy(DB_ENV*dbenv)
{
	COMPQUIET(dbenv, NULL);
}

/*
 * PUBLIC: int __txn_get_tx_max(DB_ENV *, uint32 *);
 */
int __txn_get_tx_max(DB_ENV*dbenv, uint32 * tx_maxp)
{
	ENV * env = dbenv->env;
	ENV_NOT_CONFIGURED(env, env->tx_handle, "DB_ENV->get_tx_max", DB_INIT_TXN);
	if(TXN_ON(env)) {
		/* Cannot be set after open, no lock required to read. */
		*tx_maxp = ((DB_TXNREGION *)env->tx_handle->reginfo.primary)->maxtxns;
	}
	else
		*tx_maxp = dbenv->tx_max;
	return 0;
}
/*
 * __txn_set_tx_max --
 *	DB_ENV->set_tx_max.
 *
 * PUBLIC: int __txn_set_tx_max(DB_ENV *, uint32);
 */
int __txn_set_tx_max(DB_ENV*dbenv, uint32 tx_max)
{
	ENV * env = dbenv->env;
	ENV_ILLEGAL_AFTER_OPEN(env, "DB_ENV->set_tx_max");
	dbenv->tx_max = tx_max;
	return 0;
}
/*
 * PUBLIC: int __txn_get_tx_timestamp __P((DB_ENV *, __time64_t *));
 */
int __txn_get_tx_timestamp(DB_ENV*dbenv, __time64_t * timestamp)
{
	*timestamp = dbenv->tx_timestamp;
	return 0;
}
/*
 * __txn_set_tx_timestamp --
 *	Set the transaction recovery timestamp.
 *
 * PUBLIC: int __txn_set_tx_timestamp __P((DB_ENV *, __time64_t *));
 */
int __txn_set_tx_timestamp(DB_ENV*dbenv, __time64_t * timestamp)
{
	ENV * env = dbenv->env;
	ENV_ILLEGAL_AFTER_OPEN(env, "DB_ENV->set_tx_timestamp");
	dbenv->tx_timestamp = *timestamp;
	return 0;
}