#include <string>
#include "stdlib.h"

#include "../includes/waiter.h"
#include "../includes/externs.h"

using namespace std;

Waiter::Waiter(int id,std::string filename):id(id),myIO(filename){
}

Waiter::~Waiter()
{
}

//gets next Order(s) from file_IO
int Waiter::getNext(ORDER &anOrder){
	return myIO.getNext(anOrder);
}

void Waiter::beWaiter() {
	b_WaiterIsFinished = false;
	ORDER order;

	while (getNext(order) == SUCCESS){
		unique_lock<mutex> lck(mutex_order_inQ);
		order_in_Q.push(order);
		cv_order_inQ.notify_all();
	}
	unique_lock<mutex> lck(mutex_order_inQ);
	b_WaiterIsFinished = true;
	cv_order_inQ.notify_all();

}
