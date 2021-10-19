#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <list>
#include <vector>

#include "rooms.h"

using namespace std;

struct event {
    int start;
    int finish;
    string description;
    event(int s, int f, const char * d) : start(s), finish(f), description(d) {};
};

struct room_descr {
    int floor;
    int number;
    int capacity;
    list<event> events;
    room_descr(int f, int n, int c) : floor(f), number(n), capacity(c) {};
    bool make_reservation(room * r, schedule * t, const char * description);
    int cancel_reservation(int start);
    void print_schedule(ostream & output, int start, int finish) const;
};

bool operator < (const room_descr & r1, const room_descr & r2) {
    if (r1.capacity < r2.capacity)
	return true;
    if (r1.capacity > r2.capacity)
	return false;
    if (r1.floor < r2.floor)
	return true;
    if (r1.floor > r2.floor)
	return false;
    if (r1.number < r2.number)
	return true;
    return false;
}

bool room_descr::make_reservation(room * r, schedule * t, const char * description) {
    int start = t->start;
    auto itr = events.begin();
    for (; itr != events.end(); ++itr) {
	if (start + t->duration <= itr->start) {
	    break;
	} else if (itr->finish > start) {
	    start = itr->finish;
	    if (start + t->duration > t->finish)
		return false;
	}
    }
    r->floor = floor;
    r->number = number;
    r->capacity = capacity;
    t->start = start;
    t->finish = start + t->duration;
    events.insert(itr, event(start, start + t->duration, description));
    return true;
}

int room_descr::cancel_reservation(int start) {
    for (auto itr = events.begin(); itr != events.end(); ++itr) {
	if (itr->start == start) {
	    events.erase(itr);
	    return 1;
	}
    }
    return 0;
};

void room_descr::print_schedule(ostream & output, int start, int finish) const {
    output << "room " << number << " floor " << floor << ":\n";
    for (auto & e : events) 
	if (e.finish > start && e.start < finish) 
	    output << "event " << e.start << " " << e.finish << " " << e.description << "\n";
    output << std::flush;
}

vector<room_descr> rooms;

struct room_id {
    int floor;
    int number;

    room_id(int f, int n): floor(f), number(n) {};
};

bool operator < (const room_id & r1, const room_id & r2) {
    return r1.floor < r2.floor || (r1.floor == r2.floor && r1.number < r2.number);
}

map<room_id, unsigned int> rooms_idx;

void clear() {
    rooms.clear();
    rooms_idx.clear();
}

void add_rooms(const room * begin, const room * end) {
    for (const room * r = begin; r != end; ++r) {
	auto idx_itr_bool = rooms_idx.insert(make_pair(room_id(r->floor, r->number),rooms.size()));
	if (idx_itr_bool.second) { // new room
	    rooms.push_back(room_descr(r->floor, r->number, r->capacity));
	} else {
	    rooms[idx_itr_bool.second].capacity = r->capacity;
	}
    }
    sort(rooms.begin(), rooms.end());
    for(unsigned int i = 0; i < rooms.size(); ++i)
	rooms_idx[room_id(rooms[i].floor, rooms[i].number)] = i;
}

int make_reservation(room * r, schedule * t, const char * description) {
    for (auto & d : rooms) 
	if ((r->floor == ANY_FLOOR || d.floor == r->floor)
	    && (r->number == ANY_ROOM_NUMBER || d.number == r->number)
	    && (r->capacity == ANY_CAPACITY || r->capacity <= d.capacity))
	    if (d.make_reservation(r, t, description))
		return 1;
    return 0;
}

int cancel_reservation(int floor, int number, int start) {
    auto idx_itr = rooms_idx.find(room_id(floor, number));
    if (idx_itr != rooms_idx.end())
	return rooms[idx_itr->second].cancel_reservation(start);
    return 0;
}

void print_schedule(ostream & output, int floor, int number, int start, int finish) {
    for (auto & idx_pair : rooms_idx) {
	const room_descr & d = rooms[idx_pair.second];
	if ((floor == ANY_FLOOR || d.floor == floor)
	    && (number == ANY_ROOM_NUMBER || d.number == number))
	    d.print_schedule(output, start, finish);
    }
}
