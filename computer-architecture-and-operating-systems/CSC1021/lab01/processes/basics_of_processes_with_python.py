from multiprocessing import Process, current_process

def prints_current_process():
    print(f"Current process id is {current_process().pid}")

def creating_a_child_process():
    print(f"Current process id is {current_process().pid} (parent process).")
    print("Child processes:")
    child_processes = [Process(target=prints_current_process, args=()) for _ in range(3)]
    for process in child_processes:
        process.start()

if __name__ == "__main__":
    creating_a_child_process()
