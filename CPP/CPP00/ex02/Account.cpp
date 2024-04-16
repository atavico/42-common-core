/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atarsi <atarsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 20:03:30 by atarsi            #+#    #+#             */
/*   Updated: 2023/01/24 20:51:01 by atarsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

int Account::getNbAccounts(void)
{
    return (_nbAccounts);
}
int Account::getTotalAmount(void)
{
    return (_totalAmount);
}
int Account::getNbDeposits(void)
{
    return (_totalNbDeposits);
}
int Account::getNbWithdrawals(void)
{
    return (_totalNbWithdrawals);
}
void Account::displayAccountsInfos(void)
{
    _displayTimestamp();
    std::cout << "account: " << _nbAccounts;
    std::cout << "total: " << _totalAmount;
    std::cout << "total deposit: " << _totalNbDeposits;
    std::cout << "total Withdrawals: " << _totalNbWithdrawals;
    std::cout << std::endl;
}

void    Account::makeDeposit(int deposit)
{
    _displayTimestamp();
    std::cout << "index: " << _accountIndex;
    std::cout << "amount: " << _amount;
    std::cout << "deposit: " << deposit;
    std::cout << "amount: " << _amount + deposit;
    std::cout << "N. deposits: " << _nbDeposits + 1;
    std::cout << std::endl;
    _totalAmount += deposit;
    _amount += deposit;
    _nbDeposits++;
    _totalNbDeposits++;
}

void    Account::displayStatus(void)const
{
    _displayTimestamp();
    std::cout << "index: " << _accountIndex;
    std::cout << "amount: " << _amount;
    std::cout << "deposit: " << _nbDeposits;
    std::cout << "withdrawls: " << _nbWithdrawals;
    std::cout << std::endl;
}

bool    Account::makeWithdrawal(int withdrawal)
{
    _displayTimestamp();
    std::cout << "index: " << _accountIndex;
    std::cout << "amount: " << _amount;
    if (_amount >= withdrawal)
    {
        std::cout << "Withdrawal" << withdrawal;
        std::cout << "amount: " << _amount - withdrawal;
        std::cout << "Nb. Withdrawals: " << _nbWithdrawals + 1;
        std::cout << std::endl;
        _amount -= withdrawal;
        _totalAmount -= withdrawal;
        _nbWithdrawals++;
        _totalNbWithdrawals++;
        return (true);
    }
    std::cout << "REFUSED\n";
    return (false);
}

int Account::checkAmount(void)const
{
    return (_amount);
}

void Account::_displayTimestamp(void)
{
    time_t      timer = time(NULL);
    struct tm   *stamp = localtime(&timer);

    std::cout << "[" << (stamp->tm_year + 1900);
	std::cout << std::setfill('0') << std::setw(2) << (stamp->tm_mon + 1);
	std::cout << std::setfill('0') << std::setw(2) << stamp->tm_mday << "_";
	std::cout << std::setfill('0') << std::setw(2) << stamp->tm_hour;
	std::cout << std::setfill('0') << std::setw(2) << stamp->tm_min;
	std::cout << std::setfill('0') << std::setw(2) << stamp->tm_sec;
	std::cout << "] ";
}

Account::Account (int initial_deposit)
{
    _accountIndex = _nbAccounts;
    _nbAccounts++;
    _amount = initial_deposit;
    _totalAmount += _amount;
    _nbDeposits = 0;
    _nbWithdrawals = 0;
    _displayTimestamp();
    std::cout << "index: " << _accountIndex;
    std::cout << "amount: " << _amount;
    std::cout << "created\n";
}

Account::~Account(void)
{
    _displayTimestamp();
    std::cout << "index: " << _accountIndex;
    std::cout << "amount: " << _amount;
    std::cout << "closed\n";
}