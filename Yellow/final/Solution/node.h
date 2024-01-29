#pragma once

#include <memory>
#include <string>
#include "date.h"

enum class Comparison{
Less,
LessOrEqual,
Greater,
GreaterOrEqual,
Equal,
NotEqual
};

enum class LogicalOperation{
Or,
And
};

class Node{
public:
	virtual bool Evaluate(const Date& date, 
			const std::string& event) const = 0;
};

class DateComparisonNode : public Node{
public: 
	DateComparisonNode(const Comparison& cmp, const Date& date) 
		: cmp_(cmp),
		date_(date) {}
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	Date  date_;
	Comparison cmp_;
};

class EventComparisonNode : public Node {
public: 
	EventComparisonNode(const Comparison& cmp, const std::string& value)
		: value_(value),
		cmp_(cmp) {}
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	std::string value_;
	Comparison cmp_;
};

class LogicalOperationNode : public Node{
public:
	LogicalOperationNode(const LogicalOperation& logical_operation, 
			std::shared_ptr<Node> left, std::shared_ptr<Node> current_precedence)
		: logical_operation_(logical_operation),
		left_(left), current_precedence_(current_precedence) {}
	bool Evaluate(const Date& date, const std::string& event) const override;
private:
	LogicalOperation logical_operation_;
	std::shared_ptr<Node> left_;
	std::shared_ptr<Node> current_precedence_;

};

class EmptyNode : public Node {
public: 
	EmptyNode();
	bool Evaluate(const Date& date, const std::string& event) const override;
};
