#include "xtal.h"

#ifndef XTAL_NO_PARSER

namespace xtal{

const ExprPtr& ep(const AnyPtr& a){
	if(type(a)==TYPE_TREE_NODE){
		return unchecked_ptr_cast<Expr>(a);
	}
	return unchecked_ptr_cast<Expr>(null);
}

const AnyPtr& Expr::at(uint_t i){
	if(size()<=i){
		resize(i+1);
	}
	return Array::at(i);
}

void Expr::set_at(uint_t i, const AnyPtr& v){
	if(size()<=i){
		resize(i+1);
	}
	Array::set_at(i, v); 
}

void ExprBuilder::splice(int_t tag, int_t num){
	int_t nn = root_->size()-num;
	if(nn<0 || nn>=(int_t)linenos_.size()){
		splice(tag, num, lineno_);
	}
	else{
		splice(tag, num, linenos_[nn]);
	}
}

void ExprBuilder::splice(int_t tag, int_t num, int_t lineno){
	ExprPtr ret = xnew<Expr>(tag, lineno);
	
	if((int_t)root_->size()<num){
		root_->resize(num);
	}

	for(uint_t i=root_->size()-num; i<root_->size(); ++i){
		ret->push_back(root_->at(i));
	}

	linenos_.resize(root_->size()-num);
	root_->resize(root_->size()-num);
	linenos_.push_back(lineno);
	root_->push_back(ret);
}

void ExprBuilder::push(const AnyPtr& v){
	linenos_.push_back(lineno_);
	root_->push_back(v);
}

}

#endif