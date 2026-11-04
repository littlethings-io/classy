#include "test_module.hpp"

namespace cc {

// Constructor for EMAIL
email::email(const std::string &message, const std::string &receiver, const std::string &sender)
    : message_(message), receiver_email_(receiver), sender_email_(sender) {
}

// Constructor for SMS
sms::sms(const std::string &message, const std::string &receiver, const std::string &sender)
    : message_(message), receiver_mobile_(receiver), sender_mobile_(sender) {
}


}