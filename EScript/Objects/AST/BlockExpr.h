// BlockExpr.h
// This file is part of the EScript programming language.
// See copyright notice in EScript.h
// ------------------------------------------------------
#ifndef BLOCK_H
#define BLOCK_H

#include "../Object.h"
#include "Statement.h"

#include <deque>
#include <set>

namespace EScript {
namespace AST {

/*! [BlockExpr]  ---|> [Object] */
class BlockExpr : public Object {
		ES_PROVIDES_TYPE_NAME(BlockExpr)
	public:
		typedef std::deque<Statement > statementList;
		typedef statementList::iterator statementCursor;
		typedef statementList::const_iterator cStatementCursor;
		typedef std::set<StringId>  declaredVariableMap_t;

		BlockExpr(int lineNr=-1);
		virtual ~BlockExpr();

		statementList & getStatements()                 {   return statements;  }
		const statementList & getStatements()const      {   return statements;  }
		int getLine()const								{	return line;	}


		/*! returns false if variable was already declared */
		bool declareVar(StringId id);
		const declaredVariableMap_t * getVars()const 	{ 	return vars;    }
		bool isLocalVar(StringId id)					{	return vars==NULL ? false : vars->count(id)>0;	}
		void addStatement(const Statement & s);
		bool hasLocalVars()const						{	return vars!=NULL && !vars->empty(); }
		size_t getNumLocalVars()const					{	return vars==NULL ? 0 : vars->size(); }

		/// ---|> [Object]
		virtual internalTypeId_t _getInternalTypeId()const {	return _TypeIds::TYPE_BLOCK_STATEMENT; }
	private:
		declaredVariableMap_t * vars;
		statementList statements;
		int line;
};
}
}

#endif // BLOCK_H