#include "node.h"
#include <stdexcept>

bool EventComparisonNode::Evaluate(const Date& date, 
		const std::string& event) const{
		if (cmp_ == Comparison::Less){
			return value_ > event;
		} else if (cmp_ == Comparison::Equal){
			return value_ == event;
		} else if (cmp_ == Comparison::Greater){
			return value_ < event;
		} else if (cmp_ == Comparison::LessOrEqual){
			return value_ >= event;
		} else if (cmp_ == Comparison::GreaterOrEqual){
			return value_ <= event;
		}	
		return value_ != event;
}

bool DateComparisonNode::Evaluate(const Date& date, 
		const std::string& event) const{
		if (cmp_ == Comparison::Less){
			return date_ > date;
		} else if (cmp_ == Comparison::Equal){
			return date_ == date;
		} else if (cmp_ == Comparison::Greater){
			return date_ < date;
		} else if (cmp_ == Comparison::LessOrEqual){
			return date_ >= date;
		} else if (cmp_ == Comparison::GreaterOrEqual){
			return date_ <= date;
		}	
		return date_ != date;
}

bool LogicalOperationNode::Evaluate(const Date& date, 
		const std::string& event) const{
		if (logical_operation_ == LogicalOperation::Or){
			return left_->Evaluate(date, event)
				|| current_precedence_->Evaluate(date, event);
		}	
		return left_->Evaluate(date, event)
			&& current_precedence_->Evaluate(date, event);
}

bool EmptyNode::Evaluate(const Date& date,
		const std::string& event) const{
	return true;
}

EmptyNode::EmptyNode(){
}
