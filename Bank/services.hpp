#pragma once

#include <memory>

class Bank;


std::unique_ptr<Bank> make_bank();


