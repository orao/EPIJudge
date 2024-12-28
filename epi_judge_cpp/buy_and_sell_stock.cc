#include <vector>

#include "test_framework/generic_test.h"
using std::vector;
double BuyAndSellStockOnce(const vector<double>& prices) {
  double max_profit = 0.0;
  double profit = 0.0;
  int min = 0;

  for (int i = 0; i < prices.size(); ++i) {

    if (prices[i] > prices[min]) {
      profit = prices[i] - prices[min];
    } else if (prices[i] < prices[min]) {
      min = i;
    }
    if (profit > max_profit)
      max_profit = profit;
  }
  return max_profit;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"prices"};
  return GenericTestMain(args, "buy_and_sell_stock.cc",
                         "buy_and_sell_stock.tsv", &BuyAndSellStockOnce,
                         DefaultComparator{}, param_names);
}
