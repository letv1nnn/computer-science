from multiprocessing import *

def say_hi(lock, name):
    lock.acquire()
    print(f"Hi, {name}, from process: {current_process().pid}")
    lock.release()

def many_greetings():
    main_lock = Lock()
    
    print(f"Ho from process: {current_process().pid} (main process)")
    [Process(target=(say_hi), args=(main_lock, "p"+str(i))).start() for i in range(10)]

if __name__ == "__main__":
    many_greetings()
