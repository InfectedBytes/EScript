// InstructionBlock.cpp
// This file is part of the EScript programming language.
// See copyright notice in EScript.h
// ------------------------------------------------------
#include "InstructionBlock.h"
#include "../Objects/Callables/UserFunction.h"
#include <sstream>

namespace EScript{


StringId InstructionBlock::getLocalVarName(const int index)const{
	if(index <0 || index>=static_cast<int>(localVariables.size()))
		return StringId();
	return localVariables.at(static_cast<size_t>(index));

}
UserFunction * InstructionBlock::getUserFunction(const uint32_t index)const{
	if(index<=internalFunctions.size()){
		return dynamic_cast<UserFunction*>(internalFunctions.at(index).get());
	}else{
		return NULL;
	}
}

void InstructionBlock::emplace(InstructionBlock & other){
	using namespace std;
	swap(other.localVariables,localVariables);
	swap(other.stringConstants,stringConstants);
	swap(other.instructions,instructions);
	swap(other.internalFunctions,internalFunctions);
}

std::string InstructionBlock::toString()const{
	std::ostringstream out;
	
	if(!localVariables.empty()){
		out << "Local variables:";
		uint32_t i=0;
		for(std::vector<StringId>::const_iterator it = localVariables.begin();it!=localVariables.end();++it){
			out << " $"<<i<<"('" << it->toString() << "')";
			++i;
		}
		out << "\n";
	}
	
	if(!stringConstants.empty()){
		out << "String constants:";
		uint32_t i=0;
		for(std::vector<std::string>::const_iterator it = stringConstants.begin();it!=stringConstants.end();++it){
			out << " #"<<i<<"(\"" << *it << "\")";
			++i;
		}
		out << "\n";
	}
	out << "---\n";
//		std::vector<std::string> stringConstants;
	{
		uint32_t i=0;
		for(std::vector<Instruction>::const_iterator it = instructions.begin();it!=instructions.end();++it){
			out << (i++) << "\t" << it->toString(*this) << "\n";
		}

	}
	if(!internalFunctions.empty()){
		out << "Functions:\n-------\n";
		for(uint32_t i = 0;i<internalFunctions.size();++i){
			UserFunction * uFun = getUserFunction(i);
			if(uFun){
				out << "<Function #"<<i<<"\n";
				out << uFun->getInstructions().toString();
				out << "Function #"<<i<<">\n";
			}
		}
		out << "-------\n\n";
	}
	return out.str();
}

}