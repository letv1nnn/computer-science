# Building Async Runtime

Implementation of my own runtime. I've initially build a basic async runtime environment that accepts futures and created tasks and runnables. The runnables were put on the queue to be processed by consumer threads, and the tasks was returned back to the main function, which can be blocked to wait for the result of the task.

Then, I've implemented an advanced async runtime with several queues, specifically, high priority and low priority. I've done a task stealing on them, so both queues are working, in spite of even if passed futures were priority specified. 
