#include <map>
#include <string>
#include <list>
#include <cstring>

#include "stocks.h"

static const int MAX_STOCK_LEN = 5;

struct trade {
    double time;
    char symbol[MAX_STOCK_LEN + 1];
    double price;
    unsigned int quantity;
};

struct trades_log {
    std::list<trade> trades;
    double window;

    trades_log(): window(60) {};

    int new_trade(double time, const char * symbol, double price, unsigned int quantity);
    void clear();
    void set_time_window(double w);
    unsigned int total_quantity() const;
    double high_price() const;
    double low_price() const;
    double stock_high_price(const char * symbol) const;
    double stock_low_price(const char * symbol) const;
    double stock_avg_price(const char * symbol) const;

    void trim();
};

struct trades_log * new_log() {
    return new trades_log();
}

void delete_log(struct trades_log * l) {
    delete(l);
}

int new_trade(struct trades_log * l,
	      double time, const char * symbol, double price, unsigned int quantity) {
    return l->new_trade(time, symbol, price, quantity);
}

void clear(struct trades_log * l) {
    l->clear();
}

void set_time_window(struct trades_log * l, double w) {
    l->set_time_window(w);
}

unsigned int total_quantity(const struct trades_log * l) {
    return l->total_quantity();
}

double high_price(const struct trades_log * l) {
    return l->high_price();
}

double low_price(const struct trades_log * l) {
    return l->low_price();
}

double stock_high_price(const struct trades_log * l, const char * symbol) {
    return l->stock_high_price(symbol);
}

double stock_low_price(const struct trades_log * l, const char * symbol) {
    return l->stock_low_price(symbol);
}

double stock_avg_price(const struct trades_log * l, const char * symbol) {
    return l->stock_avg_price(symbol);
}

void trades_log::trim() {
    for (auto i = trades.begin(); i != trades.end() && i->time < (trades.back().time - window);
	 i = trades.begin())
	trades.erase(i);
}

int trades_log::new_trade(double time, const char * symbol, double price, unsigned int quantity) {
    if (quantity <= 0 || price <= 0)
	return 0;
    if (!trades.empty() && time < trades.back().time)
	return 0;
    trade t;
    t.time = time;
    t.price = price;
    t.quantity = quantity;
    int i;
    for (i = 0; i < MAX_STOCK_LEN && symbol[i] != 0; ++i)
	t.symbol[i] = symbol[i];
    t.symbol[i] = 0;
    trades.push_back(t);
    trim();
    return 1;
}

void trades_log::clear() {
    trades.clear();
}

void trades_log::set_time_window(double w) {
    window = w;
    trim();
}

unsigned int trades_log::total_quantity() const {
    unsigned int q = 0;
    for (const trade & t : trades)
	q += t.quantity;
    return q;
}

double trades_log::high_price() const {
    double p = 0;
    for (const trade & t : trades)
	if (p < t.price)
	    p = t.price;
    return p;
}

double trades_log::low_price() const {
    double p = 0;
    for (const trade & t : trades)
	if (p == 0 || p > t.price)
	    p = t.price;
    return p;
}

double trades_log::stock_high_price(const char * symbol) const {
    double p = 0;
    for (const trade & t : trades)
	if (strcmp(symbol, t.symbol)==0 && p < t.price)
	    p = t.price;
    return p;
}

double trades_log::stock_low_price(const char * symbol) const {
    double p = 0;
    for (const trade & t : trades)
	if (strcmp(symbol, t.symbol)==0 && (p == 0 || p > t.price))
	    p = t.price;
    return p;
}

double trades_log::stock_avg_price(const char * symbol) const {
    double p = 0;
    unsigned int count = 0;
    for (const trade & t : trades)
	if (strcmp(symbol, t.symbol)==0) {
	    p += t.price;
	    count += 1;
	}
    return (count == 0) ? 0 : p/count;
}
