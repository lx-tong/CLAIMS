/*
 * Daemon.h
 *
 *  Created on: Feb 20, 2014
 *      Author: wangli
 */

#ifndef DAEMON_H_
#define DAEMON_H_
#include <vector>
#include <string>
#include <list>
#ifdef DMALLOC
#include "dmalloc.h"
#endif
#include "../common/Block/ResultSet.h"
#include "../utility/lock.h"

#define EXECUTED_RESULT_STATUS_OK 0
#define EXECUTED_RESULT_STATUS_ERROR 1

struct remote_command{
	std::string cmd;
	int socket_fd;
};
struct executed_result{
	bool status;	// ture is OK
	int fd;
	ResultSet* result;
	std::string error_info;
	std::string info;
};
class Daemon {
public:

	static Daemon* getInstance();
	static void* worker(void*);

	void addRemoteCommand(const remote_command& rc);

	executed_result getExecutedResult();
private:
	Daemon();
	virtual ~Daemon();
	remote_command getRemoteCommand();
	void addExecutedResult(const executed_result& item);
private:
	static Daemon* instance_;
	std::list<remote_command> remote_command_queue_;
	semaphore semaphore_command_queue_;

	std::list<executed_result> executed_result_queue_;
	semaphore semaphore_result_queue_;

	Lock lock_;
};

#endif /* DAEMON_H_ */
