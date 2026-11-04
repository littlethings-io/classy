#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace cc
{

// Super class, base klasse for andre klasser der arver den og skal overskrive den metode
class message
{
  public:
    virtual ~message() = default;
};

// Dispatcher er en buffer som gemmer på tilføjede beskeder og sender dem ud når den bliver bedt om
// det.
class dispatcher
{
    std::vector<message*> messages_;
};

// SMS er en message.
class sms
{
  public:
    sms(const std::string&, const std::string&, const std::string&);

  private:
    std::string message_;
    std::string receiver_mobile_;
    std::string sender_mobile_;
};

// Email er en message.
class email
{
  public:
    email(const std::string&, const std::string&, const std::string&);

  private:
    std::string message_;
    std::string receiver_email_;
    std::string sender_email_;
};

} // namespace cc