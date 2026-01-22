from multiprocessing import Process, current_process 

def print_sum(a, b):
    print(f"Sum: {a + b} (PID: {current_process().pid}, NAME: {current_process().name})")

def spawning_multiple_child_processes():
    print(f"Current process identifier: {current_process().pid}")
    number_of_processes = int(input("How many processes do you want to spawn: "))
    [Process(target=(print_sum), args=(1, i), name=str(i)).start() for i in range(number_of_processes)]
    
if __name__ == "__main__":
    spawning_multiple_child_processes()

