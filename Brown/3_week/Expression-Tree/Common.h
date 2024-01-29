#pragma once

#include <memory>
#include <string>

// Базовый класс арифметического выражения
class Expression {
public:
  virtual ~Expression() = default;

  // Вычисляет значение выражения
  virtual int Evaluate() const = 0;

  // Форматирует выражение как строку
  // Каждый узел берётся в скобки, независимо от приоритета
  virtual std::string ToString() const = 0;
};

using ExpressionPtr = std::unique_ptr<Expression>;
