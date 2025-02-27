#pragma once

#include <utility>
#include <vector>

#include "ast_element.hpp"

namespace mizcore {

class ASTBlock;
class ASTToken;

class ASTComponent : public ASTElement
{
  public:
    // ctor, dtor
    ASTComponent() = default;
    ~ASTComponent() override = default;
    ASTComponent(ASTComponent const&) = delete;
    ASTComponent(ASTComponent&&) = delete;
    ASTComponent& operator=(ASTComponent const&) = delete;
    ASTComponent& operator=(ASTComponent&&) = delete;

  public:
    // attributes
    ASTBlock* GetParent() const { return parent_; }
    void SetParent(ASTBlock* parent) { parent_ = parent; }

    bool IsError() const { return is_error_; }
    void SetError(bool is_error) { is_error_ = is_error; }

    virtual ASTToken* GetRangeFirstToken() const = 0;
    virtual ASTToken* GetRangeLastToken() const = 0;

    // operations
    void ToJson(nlohmann::json& json) const override = 0;

  private:
    ASTBlock* parent_ = nullptr;
    bool is_error_ = false;
};

} // namespace mizcore
