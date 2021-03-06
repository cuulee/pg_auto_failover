/*-------------------------------------------------------------------------
 *
 * stc/monitor/formation_metadata.h
 *
 * Declarations for public functions and types related to formation metadata.
 *
 * Copyright (c) Microsoft Corporation. All rights reserved.
 * Licensed under the PostgreSQL License.
 *
 *-------------------------------------------------------------------------
 */

#pragma once

#include "access/xlogdefs.h"
#include "datatype/timestamp.h"

#include "health_check.h"
#include "replication_state.h"

#define AUTO_FAILOVER_FORMATION_TABLE_NAME "formation"

/* column indexes for pgautofailover.node */
#define Natts_pgautofailover_formation 4
#define Anum_pgautofailover_formation_formationid 1
#define Anum_pgautofailover_formation_kind 2
#define Anum_pgautofailover_formation_dbname 3
#define Anum_pgautofailover_formation_opt_secondary 4


/* formation.kind: "pgsql" or "citus" */
typedef enum FormationKind
{
	FORMATION_KIND_UNKNOWN = 0,
	FORMATION_KIND_PGSQL,
	FORMATION_KIND_CITUS
} FormationKind;


/*
 * AutoFailoverFormation represents a formation that is being managed by the
 * pg_auto_failover monitor.
 */
typedef struct AutoFailoverFormation
{
	char *formationId;
	FormationKind kind;
	char dbname[NAMEDATALEN];
	bool opt_secondary;
} AutoFailoverFormation;


/* public function declarations */
extern AutoFailoverFormation *GetFormation(const char *formationId);
extern void AddFormation(const char *formationId, FormationKind kind, Name dbname,
							  bool optionSecondary);
extern void RemoveFormation(const char *formationId);
extern void SetFormationKind(const char *formationId, FormationKind kind);
extern void SetFormationDBName(const char *formationId, const char *dbname);
extern void SetFormationOptSecondary(const char *formationId, bool optSecondary);
extern bool IsCitusFormation(AutoFailoverFormation *formation);

extern FormationKind FormationKindFromString(const char *kind);
extern char *FormationKindToString(FormationKind kind);
extern FormationKind FormationKindFromNodeKindString(const char *nodeKind);
