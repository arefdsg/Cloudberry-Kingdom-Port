#ifndef _SCHEDULER_PC_H_
#define _SCHEDULER_PC_H_

#include <ForwardDeclarations.h>

class SchedulerPc
{

	// Internal bits.
	struct SchedulerInternal *internal_;

private:

	/// No copying.
	SchedulerPc( const SchedulerPc & ) { }

	/// No assignment.
	SchedulerPc &operator = ( const SchedulerPc & ) { return *this; }

public:

	SchedulerPc();
	~SchedulerPc();

	/**
	 * @see Scheduler::MainThread()
	 */
	void MainThread();

	/**
	 * @see Scheduler::RunJob()
	 */
	void RunJob( Job *job );

	/**
	 * @see Scheduler::RunJobASAP()
	 */
	void RunJobASAP( Job *job );

	/**
	 * @see Scheduler::CreateResource()
	 */
	void CreateResource( ResourceHolder *holder, Resource *resource );

	/**
	 * @see Scheduler::CreateGpuResource()
	 */
	void CreateGpuResource( ResourceHolder *holder, Resource *resource );

	/// Do worker thread processing.
	void WorkerThread();

private:

};

#endif
